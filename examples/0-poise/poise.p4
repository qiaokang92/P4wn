/**************************************************
***************** starter.p4 **********************
**************************************************/

/* -*- P4_14 -*- */

#include <tofino/intrinsic_metadata.p4>
#include <tofino/constants.p4>
#include <tofino/stateful_alu_blackbox.p4>
#include <tofino/primitives.p4>

#define Receiver FLOW_LRN_DIGEST_RCVR

#define TYPE_IPV4  0x800
#define MAX_RECIR_TIMES 1
#define RECIR_PORT 132
#define DROP_PORT  0

// Decision constants
// clean packets
#define FWD1              1
// DIP 1
#define FWD2              2
// DIP 2
#define FWD3              3
// Bad packets
#define FWD4              4
#define APPLY_BLACKLIST   4
#define UNSEEN            0

// Table constants
// TODO: update when ways and pack pragmas added to conn table
#define MAX_CONN_TABLE_SIZE 100000

// Cache constants
#define CACHE_SIZE 65536
// Changed for 32-bit timestamps

// For testing, TIMTOUT is set to 65 us * 100,000 = 6.5 s
// In deployment, it should be ~500 ms (the time delay that a connection gets
// inserted to conn_tab)
#define CACHE_TIMEOUT 100000

// BF constants
#define BF_SIZE 65536
#define BF_CACHE_SIZE 3
#define BF_KEY1 56
#define BF_KEY2 32
#define BF_KEY3 478

#define egressSpec_t 9
#define macAddr_t 48
#define ip4Addr_t 32
#define ip6Addr_t 128

// The maximum number of times we will try to recirculate a packet on BF miss
#define MAX_RESUB 3

header_type custom_metadata_t {
    fields {
        // higher 32 bits of ingress timestamp
        tstamp_high_32: 32;

        // Boolean whether the timestamp of CACHE indicates it is outdated
        tstamp_high_32_outdated: 16;

        // The src ip found in the cache
        cache_src_ip: ip4Addr_t;

        // The src port found in the cache
        cache_src_port: 16;

        // The protocol found in the cache
        cache_protoc: 8;

        // The register index matched in the connection table
        conn_idx: 24;

        // The decision number of the packet.
        //  1) for a context packet this is calculated
        //  2) for a data packet this is looked up
        p_dec: 4;

        // The decision found in the cache
        cache_dec: 4;

        // Separately keep track of the decision for the digest so we can
        // modify p_dec safely.
        digest_dec: 4;

        // Indicate the 1st/2nd/3rd BF hit
        bf_1_val: 1;
        bf_2_val: 1;
        bf_3_val: 1;

        // Indicates if this is a context packet
        is_context: 1;

        // Indicates if we got a cache hit after missing the connection table
        cache_hit: 2;

        // The number of times we've resubmitted this packet
        resub_num: 2;

        // decision made based on poise headers
        h1_dec: 4;
        h2_dec: 4;
    }
}

#define CACHE_COLL 0
#define CACHE_EMPTY 1
#define CACHE_HIT 2

header_type ethernet_t {
    fields {
        dstAddr: macAddr_t;
        srcAddr: macAddr_t;
        etherType: 16;
    }
}

// Minimal IPV4 header: 20 bytes
header_type ipv4_t {
    fields {
        version: 4;
        ihl: 4;
        diffserv: 8;
        totalLen: 16;
        identification: 16;
        flags: 3;
        fragOffset: 13;
        ttl: 8;
        protocol: 8;
        hdrChecksum: 16;
        srcAddr: ip4Addr_t;
        dstAddr: ip4Addr_t;
    }
}

// Minimal TCP header: 20 bytes
header_type tcp_t {
    fields {
        srcPort: 16;
        dstPort: 16;
        seq_no: 32;
        ack_no: 32;
        offset: 4;
        reserved: 4;
        control_b: 8;
        window: 16;
        checksum: 16;
        urgentPtr: 16;
    }
}

// Debugging log headers, see update_log action
header_type log_t {
   fields {
      recir_counter: 8;
      cache_status: 16;
      decision: 16;
      outdated: 16;
      ts_high_32: 32;
      ts_ingress_48: 48;
      ts_egress_48: 48;
   }
}

// One byte flag to distinguish data/context packets:
// 0: data packets
// 1: context packets
header_type flag_t{
    fields {
        f: 8;
    }
}

// Poise context headers
// each header contains a fixed 16-bit field
header_type poise_h1_t{
    fields {
        v: 16;
    }
}

header_type poise_h2_t {
    fields {
        v: 16;
    }
}

header_type poise_h3_t {
    fields {
        v: 16;
    }
}

header    ethernet_t   ethernet;
header    ipv4_t       ipv4;
header    tcp_t        tcp;
header    log_t        log;
header    flag_t       flag;
header    poise_h1_t   poise_h1;
header    poise_h2_t   poise_h2;
header    poise_h3_t   poise_h3;
metadata  custom_metadata_t meta;

// Table registers
register conn_decision {
    width: 8;
    instance_count: MAX_CONN_TABLE_SIZE;
}

// Registers to hold the Cache
register cache_dec {    // Decision of cache entry
    width: 8;
    instance_count : CACHE_SIZE;
}
  // High 32 bits of timestamp
register cache_tstamp_high_32 {
    width: 32;
    instance_count : CACHE_SIZE;
}
register cache_src_ip {     // Src ip of cache entry
    width: ip4Addr_t;
    instance_count : CACHE_SIZE;
}
register cache_src_port {   // Src port of cache entry
    width: 16;
    instance_count: CACHE_SIZE;
}
register cache_protoc {     // Protocol of cache entry
    width: 8;
    instance_count: CACHE_SIZE;
}

// Registers for BF
register bf_1 {
    width: 1;
    instance_count: BF_SIZE;
}
register bf_2 {
    width: 1;
    instance_count: BF_SIZE;
}
register bf_3 {
    width: 1;
    instance_count: BF_SIZE;
}

parser start {
    return parse_ethernet;
}

parser parse_ethernet {
    extract(ethernet);
    return select(ethernet.etherType) {
        TYPE_IPV4: parse_ipv4;
        default: MyIngress;
    }
}

parser parse_ipv4 {
    extract(ipv4);
    return parse_tcp;
}

parser parse_tcp {
    extract(tcp);
    return parse_log;
}

parser parse_log {
   extract(log);
   return parse_flag;
}

parser parse_flag {
   extract(flag);
   return select(flag.f) {
      // data packets
      0: MyIngress;
      // context packets
      default: parse_h1;
   }
}

parser parse_h1 {
    extract(poise_h1);
    return parse_h2;
}

parser parse_h2 {
    extract(poise_h2);
    return parse_h3;
}

parser parse_h3 {
    extract(poise_h3);
    return MyIngress;
}

/******************************************************
*************** policy.p4 starts **********************
*******************************************************/

action set_h1_dec(dec) {
    modify_field(meta.h1_dec, dec);
}

// policy5: block if screen is off
// poise_h1.h1: camera status (1: on, 0: off)

// populate evaluate_h1_tab table like this:
// key                                   action
// 0 (off)                             set_h1_dec(FWD4)
// otherwise                           set_h1_dec(FWD1)

table evaluate_h1_tab {
    reads {
       poise_h1.v: exact;
    }
    actions{set_h1_dec;}
    default_action: set_h1_dec(FWD1);
    size: 2;
}

// populate evaluate_ctx_tab table like this:
// key                                   action
// h1_dec = FWD1                      set_fwd1
// otherwise                          set_fwd4

table evaluate_ctx_tab {
    reads {
        meta.h1_dec: exact;
    }
    actions {set_fwd1;
             set_fwd4;}
    default_action: set_fwd4;
    size: 2;
}

/******************************************************
************** footer.p4 starts *************************
*******************************************************/

action forward_to_port(port){
   modify_field(ig_intr_md_for_tm.ucast_egress_port, port);
}

action nop() {}

action my_drop() {
    // mark_for_drop();
    // for debugging, we always forward dropped packets to port 2
    forward_to_port(DROP_PORT);
}

// Read value from register-indexed connection tables
action set_conn_idx(conn_idx) {
    modify_field(meta.conn_idx, conn_idx);
}

table conn_tab {
    reads {
        ipv4.srcAddr: exact;
        tcp.srcPort: exact;
        ipv4.protocol: exact;
    }
    actions {
        set_conn_idx;
        nop;
    }
    default_action: nop;
    size: MAX_CONN_TABLE_SIZE;
    support_timeout: true;
}

// Read and/or write the connection table registers
blackbox stateful_alu read_conn {
    reg : conn_decision;

    // If it is a context packet, update the entry
    condition_lo: meta.is_context != 0;

    update_lo_1_predicate: condition_lo;
    update_lo_1_value: meta.p_dec;

    // If it is a data packet, read the decision into metadata
    output_dst: meta.p_dec;
    output_value: register_lo;
    output_predicate: not condition_lo;
}

action read_conn_dec() {
    read_conn.execute_stateful_alu(meta.conn_idx);
}

table read_conn_dec_tab {
    actions{read_conn_dec;}
    default_action: read_conn_dec;
    size: 1;
}

// Apply the policy based on calculated metadata
// Populate this table like this:
// key                     action
//---------------------------------
// FWD1                    forward_to_port(0)
// FWD2                    forward_to_port(1)
// FWD3                    forward_to_port(2)
// FWD4                    forward_to_port(3)
// APPLY_BLACKLIST         forward_to_port(3)
// UNSEEN                  forward_to_port(3)
table enforce_dec_tab {
    reads {
        meta.p_dec: exact;
    }
    actions {
        nop;
        forward_to_port;
        my_drop;
    }
    default_action: my_drop;
    size: 5;
}

// Read and/or write the cache
// hash calculation for cache index
field_list tup_3_fields {
    tcp.srcPort;
    ipv4.srcAddr;
    ipv4.protocol;
}
field_list_calculation cache_hash_calc {
    input {tup_3_fields;}
    algorithm : crc_16;
    output_width: 16;
}

// For context packet:
//    update the cache tstamp_high_32
// For all packets:
//    calculate whether the entry is outdated and store the result to metadata
// NOTE: output value in meta.tstamp_high_32_outdated may not be 1 when outdated,
//       it could be 0x41 or 0x81.
//       so alway use == 0 or != 0 to judge this value.
blackbox stateful_alu handle_cache_tstamp_high_32_stfu{
    reg : cache_tstamp_high_32;

    condition_lo: meta.is_context != 0;
    condition_hi: meta.tstamp_high_32 - register_lo > CACHE_TIMEOUT;

    update_lo_1_predicate: condition_lo;
    update_lo_1_value: meta.tstamp_high_32;

    output_predicate: condition_hi;
    output_dst: meta.tstamp_high_32_outdated;
    output_value: predicate;
}
action handle_cache_tstamp_high_32() {
    handle_cache_tstamp_high_32_stfu.execute_stateful_alu_from_hash(cache_hash_calc);
}
table apply_cache_tstamp_high_32_tab {
    actions {handle_cache_tstamp_high_32;}
    default_action: handle_cache_tstamp_high_32;
    size: 1;
}

// Read and/or write the cache decision
blackbox stateful_alu handle_cache_dec_stfu {
    reg: cache_dec;

    condition_lo: meta.is_context != 0;

    update_lo_1_predicate: condition_lo;
    update_lo_1_value: meta.p_dec;

    output_predicate: true;
    output_dst: meta.cache_dec;
    output_value: register_lo;
}
action handle_cache_dec() {
    handle_cache_dec_stfu.execute_stateful_alu_from_hash(cache_hash_calc);
}
table apply_cache_dec_tab {
    actions {handle_cache_dec;}
    default_action: handle_cache_dec;
    size: 1;
}

// Read and/or write the cache key (src ip, src port, protocol)
blackbox stateful_alu handle_cache_src_ip_stfu {
    reg: cache_src_ip;

    condition_lo: meta.is_context != 0;

    update_lo_1_predicate: condition_lo;
    update_lo_1_value: ipv4.srcAddr;

    output_dst: meta.cache_src_ip;
    output_predicate: true;
    output_value: register_lo;
}
blackbox stateful_alu handle_cache_src_port_stfu {
    reg: cache_src_port;

    condition_lo: meta.is_context != 0;

    update_lo_1_predicate: condition_lo;
    update_lo_1_value: tcp.srcPort;

    output_dst: meta.cache_src_port;
    output_predicate: true;
    output_value: register_lo;
}
blackbox stateful_alu handle_cache_protoc_stfu {
    reg: cache_protoc;

    condition_lo: meta.is_context != 0;

    update_lo_1_predicate: condition_lo;
    update_lo_1_value: ipv4.protocol;

    output_dst: meta.cache_protoc;
    output_predicate: true;
    output_value: register_lo;
}
action handle_cache_ip() {
    handle_cache_src_ip_stfu.execute_stateful_alu_from_hash(cache_hash_calc);
}
table apply_cache_ip_tab {
    actions {handle_cache_ip;}
    default_action: handle_cache_ip;
    size: 1;
}
action handle_cache_port() {
    handle_cache_src_port_stfu.execute_stateful_alu_from_hash(cache_hash_calc);
}
table apply_cache_port_tab {
    actions {handle_cache_port;}
    default_action: handle_cache_port;
    size: 1;
}
action handle_cache_protoc() {
    handle_cache_protoc_stfu.execute_stateful_alu_from_hash(cache_hash_calc);
}
table apply_cache_protoc_tab {
    actions {handle_cache_protoc;}
    default_action: handle_cache_protoc;
    size: 1;
}

// For reading the BF using the packet's fields (for data packets)
field_list pkt_bfk1_fields {
    tcp.srcPort;
    ipv4.srcAddr;
    ipv4.protocol;
    BF_KEY1;
}
field_list_calculation pkt_bf1_hash_calc {
    input {pkt_bfk1_fields;}
    algorithm : crc_16;
    output_width: 16;
}
field_list pkt_bfk2_fields {
    tcp.srcPort;
    ipv4.srcAddr;
    ipv4.protocol;
    BF_KEY2;
}
field_list_calculation pkt_bf2_hash_calc {
    input {pkt_bfk2_fields;}
    algorithm : crc_16;
    output_width: 16;
}

field_list pkt_bfk3_fields {
    tcp.srcPort;
    ipv4.srcAddr;
    ipv4.protocol;
    BF_KEY3;
}
field_list_calculation pkt_bf3_hash_calc {
    input {pkt_bfk3_fields;}
    algorithm : crc_16;
    output_width: 16;
}
// For writing the BF based on the values found in the cache (for context packet evictions)
field_list cache_bfk1_fields {
    meta.cache_src_port;
    meta.cache_src_ip;
    meta.cache_protoc;
    BF_KEY1;
}
field_list_calculation cache_bf1_hash_calc {
    input {cache_bfk1_fields;}
    algorithm : crc_16;
    output_width: 16;
}
field_list cache_bfk2_fields {
    meta.cache_src_port;
    meta.cache_src_ip;
    meta.cache_protoc;
    BF_KEY2;
}
field_list_calculation cache_bf2_hash_calc {
    input {cache_bfk2_fields;}
    algorithm : crc_16;
    output_width: 16;
}
field_list cache_bfk3_fields {
    meta.cache_src_port;
    meta.cache_src_ip;
    meta.cache_protoc;
    BF_KEY3;
}
field_list_calculation cache_bf3_hash_calc {
    input {cache_bfk3_fields;}
    algorithm : crc_16;
    output_width: 16;
}
// Read the BF
blackbox stateful_alu read_bf1_stfu {
    reg: bf_1;

    update_lo_1_value: read_bit;

    output_dst: meta.bf_1_val;
    output_value: alu_lo;
}
action read_bf1() {
    read_bf1_stfu.execute_stateful_alu_from_hash(pkt_bf1_hash_calc);
}
blackbox stateful_alu read_bf2_stfu {
    reg: bf_2;

    update_lo_1_value: read_bit;

    output_dst: meta.bf_2_val;
    output_value: alu_lo;
}
action read_bf2() {
    read_bf2_stfu.execute_stateful_alu_from_hash(pkt_bf2_hash_calc);
}
blackbox stateful_alu read_bf3_stfu {
    reg: bf_3;

    update_lo_1_value: read_bit;

    output_dst: meta.bf_3_val;
    output_value: alu_lo;
}
action read_bf3() {
    read_bf3_stfu.execute_stateful_alu_from_hash(pkt_bf3_hash_calc);
}
// Write the BF
blackbox stateful_alu write_bf1_stfu {
    reg: bf_1;

    update_lo_1_value: set_bit;
}
action write_bf1() {
    write_bf1_stfu.execute_stateful_alu_from_hash(cache_bf1_hash_calc);
}
blackbox stateful_alu write_bf2_stfu {
    reg: bf_2;

    update_lo_1_value: set_bit;
}
action write_bf2() {
    write_bf2_stfu.execute_stateful_alu_from_hash(cache_bf2_hash_calc);
}
blackbox stateful_alu write_bf3_stfu {
    reg: bf_3;

    update_lo_1_value: set_bit;
}
action write_bf3() {
    write_bf3_stfu.execute_stateful_alu_from_hash(cache_bf3_hash_calc);
}
table apply_bf1_read_tab {
    actions{read_bf1;}
    default_action: read_bf1;
    size: 1;
}
table apply_bf1_write_tab {
    actions{write_bf1;}
    default_action: write_bf1;
    size: 1;
}
table apply_bf2_read_tab {
    actions{read_bf2;}
    default_action: read_bf2;
    size: 1;
}
table apply_bf2_write_tab {
    actions{write_bf2;}
    default_action: write_bf2;
    size: 1;
}
table apply_bf3_read_tab {
    actions{read_bf3;}
    default_action: read_bf3;
    size: 1;
}
table apply_bf3_write_tab {
    actions{write_bf3;}
    default_action: write_bf3;
    size: 1;
}

// Generate a learning digest for new connections
field_list context_fields {
    tcp.srcPort;
    ipv4.srcAddr;
    ipv4.protocol;
    meta.digest_dec;
    meta.is_context;
}
action _generate_digest() {
    generate_digest(0, context_fields);
}

table generate_diegst_tab {
    actions{_generate_digest;}
    default_action: _generate_digest;
    size: 1;
}

// When we have a cache hit, we log it in metadata and use the cache decision
// for the packet decision
action set_cache_hit() {
    modify_field(meta.p_dec, meta.cache_dec);
    modify_field(meta.cache_hit, CACHE_HIT);
}
table set_cache_hit_tab {
    actions{set_cache_hit;}
    default_action: set_cache_hit;
    size: 1;
}

// When we have a cache empty, we notify it in metadata and set the decision
// to unseen for the packet decision
action set_cache_empty() {
    modify_field(meta.digest_dec, meta.p_dec);
    modify_field(meta.p_dec, UNSEEN);
    modify_field(meta.cache_hit, CACHE_EMPTY);
}
table set_cache_empty_tab {
    actions{set_cache_empty;}
    default_action: set_cache_empty;
    size: 1;
}

action set_blacklist() {
    modify_field(meta.p_dec, APPLY_BLACKLIST);
}
action set_fwd1() {
    modify_field(meta.p_dec, FWD1);
}
action set_fwd2() {
    modify_field(meta.p_dec, FWD2);
}
action set_fwd3() {
    modify_field(meta.p_dec, FWD3);
}
action set_fwd4() {
    modify_field(meta.p_dec, FWD4);
}
action set_unseen() {
    modify_field(meta.p_dec, UNSEEN);
}

table set_blacklist_tab {
    actions{set_blacklist;}
    default_action: set_blacklist;
    size: 1;
}
table set_unseen_tab {
    actions{set_unseen;}
    default_action: set_unseen;
    size: 1;
}

// Set metadata to indicate that this is a context packet
action set_context() {
    modify_field(meta.is_context, 1);
}
table set_context_tab {
    actions{set_context;}
    default_action: set_context;
    size: 1;
}

// Set metadata to indicate that this is a data packet
action set_data() {
    modify_field(meta.is_context, 0);
}
table set_data_tab {
    actions{set_data;}
    default_action: set_data;
    size: 1;
}

// Drop the packet automatically
table drop_tab {
    actions{my_drop;}
    default_action: my_drop;
    size: 1;
}

// Use high 32-bit tstamp of the full 48 bits
field_list tstamp {
    _ingress_global_tstamp_;
}
field_list_calculation tstamp_shift {
    input {tstamp;}
    algorithm : identity_msb;
    output_width: 32;
}
action split_tstamp() {
    modify_field_with_hash_based_offset(meta.tstamp_high_32, 0, tstamp_shift, 4294967296);
}
table split_tstamp_tab {
    actions{split_tstamp;}
    default_action: split_tstamp;
    size: 1;
}

action update_log() {
   modify_field(log.cache_status, meta.cache_hit);
   modify_field(log.decision, meta.p_dec);
   modify_field(log.outdated, meta.tstamp_high_32_outdated);
   modify_field(log.ts_high_32, meta.tstamp_high_32);
}

table update_log_tab {
   actions {update_log;}
   default_action: update_log;
   size: 1;
}

action update_log_ingress_tstamp() {
   modify_field(log.ts_ingress_48, _ingress_global_tstamp_);
}

table update_log_ingress_tstamp_tab {
   actions {update_log_ingress_tstamp;}
   default_action: update_log_ingress_tstamp;
   size :1;
}

action update_log_egress_tstamp() {
   modify_field(log.ts_egress_48,
                eg_intr_md_from_parser_aux.egress_global_tstamp);
}

table update_log_egress_tstamp_tab {
   actions {update_log_egress_tstamp;}
   default_action: update_log_egress_tstamp;
   size :1;
}

action do_recirculate() {
   add_to_field(log.recir_counter, 1);
   forward_to_port(RECIR_PORT);
}

table do_recirculate_tab {
   actions {do_recirculate;}
   default_action: do_recirculate;
   size :1;
}

control MyIngress {
    apply(update_log_ingress_tstamp_tab);

    if (valid(poise_h1)) {
        apply(set_context_tab);

        // Protocol specific
        apply(evaluate_h1_tab);
        apply(evaluate_ctx_tab);
        apply(drop_tab);
    } else {
       apply(set_data_tab);
    }

    apply(split_tstamp_tab);
    apply(conn_tab) {
        miss {
            // Read (data packet) or write (context packet) the cache
            apply(apply_cache_tstamp_high_32_tab);
            apply(apply_cache_ip_tab);
            apply(apply_cache_port_tab);
            apply(apply_cache_protoc_tab);
            apply(apply_cache_dec_tab);

            // Check if the cache was empty, a hit, or a collision
            if (meta.cache_dec == UNSEEN) {
               apply(set_cache_empty_tab);
            }
            // Hit the cache
            else if (meta.cache_src_ip == ipv4.srcAddr) {
                if (meta.cache_src_port == tcp.srcPort) {
                    if (meta.cache_protoc == ipv4.protocol) {
                        apply(set_cache_hit_tab);
                    }
                }
            }

            // If it's a context packet, generate a digest message
            // if there's a chance we haven't seen it
            if (meta.is_context != 0) {
                if (meta.cache_hit == CACHE_EMPTY or meta.cache_hit == CACHE_COLL) {
                    apply(generate_diegst_tab);
                }
            }

            // Collisin happens!
            // NOTE: We can change it to CACHE_EMPTY if it's hard
            // to generate collisions
            if (meta.cache_hit == CACHE_COLL) {
                // If it is a context packet and the cache decision is to
                // blacklist, update the BF
                if (meta.is_context == 1 and meta.cache_dec == APPLY_BLACKLIST) {
                    apply(apply_bf1_write_tab);
                    apply(apply_bf2_write_tab);
                    apply(apply_bf3_write_tab);
                }
                // For data packets, we read the BF
                else if (meta.is_context == 0) {
                    apply(apply_bf1_read_tab);
                    apply(apply_bf2_read_tab);
                    apply(apply_bf3_read_tab);
                    // If the BF is a hit, assume the value is to blacklist
                    if (meta.bf_1_val == 1 and meta.bf_2_val == 1
                        and meta.bf_3_val == 1) {
                       apply(set_blacklist_tab);
                    } else if (log.recir_counter < MAX_RECIR_TIMES) {
                       // Otherwise try to recirculate
                       apply(do_recirculate_tab);
                    } else {
                       // We've tried to resubmit it too many times, so
                       // we assume it's unseen
                       apply(set_unseen_tab);
                    }
                }
            }
        }
        hit {
            // On hit, read or update the connection register
            apply(read_conn_dec_tab);
        }
    }
    // Apply the decision
    if (meta.is_context == 0) {
        apply(enforce_dec_tab);
    }

    apply(update_log_tab);
}

control egress {
    apply(update_log_egress_tstamp_tab);
}
