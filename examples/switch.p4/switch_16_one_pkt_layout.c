#define BITSLICE(x, a, b) ((x) >> (b)) & ((1 << ((a)-(b)+1)) - 1)
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

int assert_forward = 1;
int action_run;

void end_assertions();

void parse_arp_rarp();
void parse_eompls();
void parse_erspan_t3();
void parse_ethernet();
void parse_fabric_header();
void parse_fabric_header_cpu();
void parse_fabric_header_mirror();
void parse_fabric_header_multicast();
void parse_fabric_header_unicast();
void parse_fabric_payload_header();
void parse_fabric_sflow_header();
void parse_geneve();
void parse_gpe_int_header();
void parse_gre();
void parse_gre_ipv4();
void parse_gre_ipv6();
void parse_icmp();
void parse_inner_ethernet();
void parse_inner_icmp();
void parse_inner_ipv4();
void parse_inner_ipv6();
void parse_inner_tcp();
void parse_inner_udp();
void parse_int_header();
void parse_int_val();
void parse_ipv4();
void parse_ipv4_in_ip();
void parse_ipv6();
void parse_ipv6_in_ip();
void parse_llc_header();
void parse_mpls();
void parse_mpls_bos();
void parse_mpls_inner_ipv4();
void parse_mpls_inner_ipv6();
void parse_nvgre();
void parse_qinq();
void parse_qinq_vlan();
void parse_set_prio_high();
void parse_set_prio_med();
void parse_sflow();
void parse_snap_header();
void parse_tcp();
void parse_udp();
void parse_vlan();
void parse_vxlan();
void parse_vxlan_gpe();
void start();
void accept();
void reject();
void NoAction_0_5652839();
void NoAction_1_5652849();
void NoAction_131_5652850();
void NoAction_132_5652851();
void NoAction_133_5652852();
void NoAction_134_5652853();
void NoAction_135_5652854();
void NoAction_136_5652855();
void NoAction_137_5652856();
void NoAction_138_5652857();
void NoAction_139_5652858();
void NoAction_140_5652859();
void NoAction_141_5652860();
void NoAction_142_5652861();
void NoAction_143_5652862();
void NoAction_144_5652863();
void NoAction_145_5652864();
void NoAction_146_5652865();
void NoAction_147_5652866();
void NoAction_148_5652867();
void NoAction_149_5652868();
void NoAction_150_5652869();
void NoAction_151_5652870();
void NoAction_152_5652871();
void NoAction_153_5652872();
void NoAction_154_5652873();
void NoAction_155_5652874();
void NoAction_156_5652875();
void NoAction_157_5652876();
void NoAction_158_5652877();
void NoAction_159_5652878();
void NoAction_160_5652879();
void NoAction_161_5652880();
void NoAction_162_5652881();
void NoAction_163_5652882();
void NoAction_164_5652883();
void NoAction_165_5652884();
void NoAction_166_5652885();
void NoAction_167_5652886();
void NoAction_168_5652887();
void NoAction_169_5652888();
void NoAction_170_5652889();
void NoAction_171_5652890();
void egress_port_type_normal_0_5652891(uint32_t ifindex, uint8_t qos_group,
				       uint32_t if_label);
void egress_port_type_fabric_0_5652931(uint32_t ifindex);
void egress_port_type_cpu_0_5652961(uint32_t ifindex);
void egress_port_mapping_5652991();
void _nop_8_5653055();
void _set_mirror_nhop_5653065(uint32_t nhop_idx);
void _set_mirror_bd_5653083(uint32_t bd);
void _sflow_pkt_to_cpu_5653101(uint32_t reason_code);
void _mirror_0_5653145();
void _nop_9_5653216();
void _nop_10_5653226();
void _set_replica_copy_bridged_5653227();
void _outer_replica_from_rid_5653243(uint32_t bd, uint32_t tunnel_index,
				     uint8_t tunnel_type, uint8_t header_count);
void _inner_replica_from_rid_5653318(uint32_t bd, uint32_t tunnel_index,
				     uint8_t tunnel_type, uint8_t header_count);
void _replica_type_0_5653393();
void _rid_0_5653462();
void _nop_11_5653525();
void _remove_vlan_single_tagged_5653535();
void _remove_vlan_double_tagged_5653568();
void _vlan_decap_0_5653612();
void _decap_inner_udp_5653699();
void _decap_inner_tcp_5653724();
void _decap_inner_icmp_5653757();
void _decap_inner_unknown_5653790();
void _decap_vxlan_inner_ipv4_5653808();
void _decap_vxlan_inner_ipv6_5653864();
void _decap_vxlan_inner_non_ip_5653920();
void _decap_genv_inner_ipv4_5653969();
void _decap_genv_inner_ipv6_5654025();
void _decap_genv_inner_non_ip_5654081();
void _decap_nvgre_inner_ipv4_5654130();
void _decap_nvgre_inner_ipv6_5654194();
void _decap_nvgre_inner_non_ip_5654258();
void _decap_gre_inner_ipv4_5654315();
void _decap_gre_inner_ipv6_5654362();
void _decap_gre_inner_non_ip_5654409();
void _decap_ip_inner_ipv4_5654452();
void _decap_ip_inner_ipv6_5654491();
void _decap_mpls_inner_ipv4_pop1_5654530();
void _decap_mpls_inner_ipv6_pop1_5654572();
void _decap_mpls_inner_ethernet_ipv4_pop1_5654614();
void _decap_mpls_inner_ethernet_ipv6_pop1_5654665();
void _decap_mpls_inner_ethernet_non_ip_pop1_5654716();
void _decap_mpls_inner_ipv4_pop2_5654752();
void _decap_mpls_inner_ipv6_pop2_5654805();
void _decap_mpls_inner_ethernet_ipv4_pop2_5654858();
void _decap_mpls_inner_ethernet_ipv6_pop2_5654920();
void _decap_mpls_inner_ethernet_non_ip_pop2_5654982();
void _decap_mpls_inner_ipv4_pop3_5655029();
void _decap_mpls_inner_ipv6_pop3_5655093();
void _decap_mpls_inner_ethernet_ipv4_pop3_5655157();
void _decap_mpls_inner_ethernet_ipv6_pop3_5655230();
void _decap_mpls_inner_ethernet_non_ip_pop3_5655303();
void _tunnel_decap_process_inner_0_5655361();
void _tunnel_decap_process_outer_0_5655461();
void _nop_12_5655708();
void _nop_13_5655718();
void _set_l2_rewrite_5655719();
void _set_l2_rewrite_with_tunnel_5655753(uint32_t tunnel_index,
					 uint8_t tunnel_type);
void _set_l3_rewrite_5655803(uint32_t bd, uint8_t mtu_index, uint64_t dmac);
void _set_l3_rewrite_with_tunnel_5655850(uint32_t bd, uint64_t dmac,
					 uint32_t tunnel_index,
					 uint8_t tunnel_type);
void _set_mpls_swap_push_rewrite_l2_5655905(uint32_t label,
					    uint32_t tunnel_index,
					    uint8_t header_count);
void _set_mpls_push_rewrite_l2_5655966(uint32_t tunnel_index,
				       uint8_t header_count);
void _set_mpls_swap_push_rewrite_l3_5656016(uint32_t bd, uint64_t dmac,
					    uint32_t label,
					    uint32_t tunnel_index,
					    uint8_t header_count);
void _set_mpls_push_rewrite_l3_5656084(uint32_t bd, uint64_t dmac,
				       uint32_t tunnel_index,
				       uint8_t header_count);
void _rewrite_ipv4_multicast_6057736();
void _rewrite_ipv6_multicast_5656171();
void _rewrite_0_5656181();
void _rewrite_multicast_0_5714227();
void _nop_14_5656379();
void _set_egress_bd_properties_5656389(uint32_t smac_idx, uint8_t nat_mode,
				       uint32_t bd_label);
void _egress_bd_map_0_5714383();
void _nop_15_5656480();
void _set_mpls_exp_marking_5656490(uint8_t exp);
void _set_ip_dscp_marking_5656508(uint8_t dscp);
void _set_vlan_pcp_marking_5656526(uint8_t pcp);
void _egress_qos_map_0_5714507();
void _nop_16_5656623();
void _ipv4_unicast_rewrite_5656633();
void _ipv4_multicast_rewrite_5656672();
void _ipv6_unicast_rewrite_5656713();
void _ipv6_multicast_rewrite_5656752();
void _mpls_rewrite_5656793();
void _rewrite_smac_5656829(uint64_t smac);
void _l3_rewrite_0_5714815();
void _smac_rewrite_0_5714962();
void _mtu_miss_5657029();
void _ipv4_mtu_check_5657045(uint32_t l3_mtu);
void _ipv6_mtu_check_5657068(uint32_t l3_mtu);
void _mtu_0_5715078();
void _int_set_header_0_bos_5657182();
void _int_set_header_1_bos_5657198();
void _int_set_header_2_bos_5657214();
void _int_set_header_3_bos_5657230();
void _int_set_header_4_bos_5657246();
void _int_set_header_5_bos_5657262();
void _int_set_header_6_bos_5657278();
void _int_set_header_7_bos_5657294();
void _nop_17_5657310();
void _nop_18_5657320();
void _nop_19_5657321();
void _nop_20_5657322();
void _int_transit_5657323(uint32_t switch_id);
void _int_src_5657377(uint32_t switch_id, uint8_t hop_cnt, uint8_t ins_cnt,
		      uint8_t ins_mask0003, uint8_t ins_mask0407,
		      uint32_t ins_byte_cnt, uint8_t total_words);
void _int_reset_5657512();
void _int_set_header_0003_i0_5657558();
void _int_set_header_0003_i1_5657568();
void _int_set_header_0003_i2_5657602();
void _int_set_header_0003_i3_5657630();
void _int_set_header_0003_i4_5657677();
void _int_set_header_0003_i5_5657710();
void _int_set_header_0003_i6_5657761();
void _int_set_header_0003_i7_5657807();
void _int_set_header_0003_i8_5657874();
void _int_set_header_0003_i9_5657902();
void _int_set_header_0003_i10_5657949();
void _int_set_header_0003_i11_5657991();
void _int_set_header_0003_i12_5658054();
void _int_set_header_0003_i13_5658100();
void _int_set_header_0003_i14_5658167();
void _int_set_header_0003_i15_5658229();
void _int_set_header_0407_i0_5658312();
void _int_set_header_0407_i1_5658322();
void _int_set_header_0407_i2_5658346();
void _int_set_header_0407_i3_5658370();
void _int_set_header_0407_i4_5658402();
void _int_set_header_0407_i5_5658429();
void _int_set_header_0407_i6_5658465();
void _int_set_header_0407_i7_5658501();
void _int_set_header_0407_i8_5658548();
void _int_set_header_0407_i9_5658576();
void _int_set_header_0407_i10_5658613();
void _int_set_header_0407_i11_5658650();
void _int_set_header_0407_i12_5658698();
void _int_set_header_0407_i13_5658739();
void _int_set_header_0407_i14_5658791();
void _int_set_header_0407_i15_5658843();
void _int_set_e_bit_5658906();
void _int_update_total_hop_cnt_5658922();
void _int_bos_0_5716966();
void _int_insert_0_5717116();
void _int_inst_3_5717208();
void _int_inst_4_5717351();
void _int_inst_5_5717500();
void _int_inst_6_5717553();
void _int_meta_header_update_0_5717606();
void _nop_21_5659617();
void _set_nat_src_rewrite_5659627(uint32_t src_ip);
void _set_nat_dst_rewrite_5659662(uint32_t dst_ip);
void _set_nat_src_dst_rewrite_5659695(uint32_t src_ip, uint32_t dst_ip);
void _set_nat_src_udp_rewrite_5659736(uint32_t src_ip, uint32_t src_port);
void _set_nat_dst_udp_rewrite_5659777(uint32_t dst_ip, uint32_t dst_port);
void _set_nat_src_dst_udp_rewrite_5659818(uint32_t src_ip, uint32_t dst_ip,
					  uint32_t src_port, uint32_t dst_port);
void _set_nat_src_tcp_rewrite_5659875(uint32_t src_ip, uint32_t src_port);
void _set_nat_dst_tcp_rewrite_5659916(uint32_t dst_ip, uint32_t dst_port);
void _set_nat_src_dst_tcp_rewrite_5659957(uint32_t src_ip, uint32_t dst_ip,
					  uint32_t src_port, uint32_t dst_port);
void _egress_nat_0_5718078();
void _nop_22_5660133();
void _egress_bd_stats_2_5718217();
void _nop_23_5660215();
void _nop_24_5660225();
void _nop_25_5660226();
void _set_egress_dst_port_range_id_5660227(uint8_t range_id);
void _set_egress_src_port_range_id_5660245(uint8_t range_id);
void _set_egress_tcp_port_fields_5660263();
void _set_egress_udp_port_fields_5660291();
void _set_egress_icmp_port_fields_5660319();
void _egress_l4_dst_port_0_5718410();
void _egress_l4_src_port_0_5718470();
void _egress_l4port_fields_0_5660452();
void _nop_26_5660552();
void _nop_27_5660562();
void _nop_28_5660563();
void _nop_29_5660564();
void _nop_30_5660565();
void _nop_31_5660566();
void _nop_32_5660567();
void _set_egress_tunnel_vni_5660568(uint32_t vnid);
void _rewrite_tunnel_dmac_5660586(uint64_t dmac);
void _rewrite_tunnel_ipv4_dst_5660604(uint32_t ip);
void _rewrite_tunnel_ipv6_dst_5660622(uint64_t ip);
void _inner_ipv4_udp_rewrite_5660640();
void _inner_ipv4_tcp_rewrite_5660695();
void _inner_ipv4_icmp_rewrite_5660750();
void _inner_ipv4_unknown_rewrite_5660805();
void _inner_ipv6_udp_rewrite_5660845();
void _inner_ipv6_tcp_rewrite_5660894();
void _inner_ipv6_icmp_rewrite_5660951();
void _inner_ipv6_unknown_rewrite_5661008();
void _inner_non_ip_rewrite_5661050();
void _fabric_rewrite_5661071(uint32_t tunnel_index);
void _ipv4_vxlan_rewrite_5661089();
void _ipv4_genv_rewrite_5661251();
void _ipv4_nvgre_rewrite_6063072();
void _ipv4_gre_rewrite_5661596();
void _ipv4_ip_rewrite_5661672();
void _ipv6_gre_rewrite_5661734();
void _ipv6_ip_rewrite_5661814();
void _ipv6_nvgre_rewrite_6063525();
void _ipv6_vxlan_rewrite_5662018();
void _ipv6_genv_rewrite_5662163();
void _mpls_ethernet_push1_rewrite_5662328();
void _mpls_ip_push1_rewrite_5662361();
void _mpls_ethernet_push2_rewrite_5662387();
void _mpls_ip_push2_rewrite_5662420();
void _mpls_ethernet_push3_rewrite_5662446();
void _mpls_ip_push3_rewrite_5662479();
void _ipv4_erspan_t3_rewrite_5662505();
void _ipv6_erspan_t3_rewrite_5662666();
void _tunnel_mtu_check_5662812(uint32_t l3_mtu);
void _tunnel_mtu_miss_5662835();
void _cpu_rx_rewrite_5662851();
void _set_tunnel_rewrite_details_5662961(uint32_t outer_bd,
					 uint32_t smac_idx,
					 uint32_t dmac_idx,
					 uint32_t sip_index,
					 uint32_t dip_index);
void _set_mpls_rewrite_push1_5663011(uint32_t label1, uint8_t exp1,
				     uint8_t ttl1, uint32_t smac_idx,
				     uint32_t dmac_idx);
void _set_mpls_rewrite_push2_5663079(uint32_t label1, uint8_t exp1,
				     uint8_t ttl1, uint32_t label2,
				     uint8_t exp2, uint8_t ttl2,
				     uint32_t smac_idx, uint32_t dmac_idx);
void _set_mpls_rewrite_push3_5663189(uint32_t label1, uint8_t exp1,
				     uint8_t ttl1, uint32_t label2,
				     uint8_t exp2, uint8_t ttl2,
				     uint32_t label3, uint8_t exp3,
				     uint8_t ttl3, uint32_t smac_idx,
				     uint32_t dmac_idx);
void _fabric_unicast_rewrite_5663341();
void _fabric_multicast_rewrite_5663477(uint32_t fabric_mgid);
void _rewrite_tunnel_smac_5663627(uint64_t smac);
void _rewrite_tunnel_ipv4_src_5663645(uint32_t ip);
void _rewrite_tunnel_ipv6_src_5663663(uint64_t ip);
void _egress_vni_0_5721844();
void _tunnel_dmac_rewrite_0_5721916();
void _tunnel_dst_rewrite_0_5721975();
void _tunnel_encap_process_inner_0_5663868();
void _tunnel_encap_process_outer_0_5722200();
void _tunnel_mtu_0_5722391();
void _tunnel_rewrite_0_5722450();
void _tunnel_smac_rewrite_0_5722545();
void _tunnel_src_rewrite_0_5722604();
void _nop_33_5664479();
void _nop_34_5664489();
void _nop_35_5664490();
void _egress_acl_deny_5664491(uint32_t acl_copy_reason);
void _egress_acl_deny_3_5664515(uint32_t acl_copy_reason);
void _egress_acl_deny_4_5664533(uint32_t acl_copy_reason);
void _egress_acl_permit_5664551(uint32_t acl_copy_reason);
void _egress_acl_permit_3_5664569(uint32_t acl_copy_reason);
void _egress_acl_permit_4_5664582(uint32_t acl_copy_reason);
void _egress_ip_acl_0_5722787();
void _egress_ipv6_acl_0_5722926();
void _egress_mac_acl_0_5723063();
void _int_update_vxlan_gpe_ipv4_5664944();
void _int_add_update_vxlan_gpe_ipv4_5664996();
void _nop_36_5665069();
void _int_outer_encap_0_5723311();
void _set_egress_packet_vlan_untagged_5665180();
void _set_egress_packet_vlan_tagged_5665190(uint32_t vlan_id);
void _set_egress_packet_vlan_double_tagged_5665240(uint32_t s_tag,
						   uint32_t c_tag);
void _egress_vlan_xlate_0_5723560();
void _egress_filter_check_5665394();
void _set_egress_filter_drop_5665446();
void _egress_filter_0_5665462();
void _egress_filter_drop_0_5665496();
void _nop_37_5665530();
void _drop_packet_5665540();
void _egress_copy_to_cpu_5665556();
void _egress_redirect_to_cpu_5665597();
void _egress_copy_to_cpu_with_reason_5709531(uint32_t reason_code);
void _egress_redirect_to_cpu_with_reason_5709602(uint32_t reason_code);
void _egress_mirror_5709685(uint32_t session_id);
void _egress_mirror_drop_5709753(uint32_t session_id);
void _egress_system_acl_0_5724062();
void NoAction_172_5667254();
void NoAction_173_5667255();
void NoAction_174_5667256();
void NoAction_175_5667257();
void NoAction_176_5667258();
void NoAction_177_5667259();
void NoAction_178_5667260();
void NoAction_179_5667261();
void NoAction_180_5667262();
void NoAction_181_5667263();
void NoAction_182_5667264();
void NoAction_183_5667265();
void NoAction_184_5667266();
void NoAction_185_5667267();
void NoAction_186_5667268();
void NoAction_187_5667269();
void NoAction_188_5667270();
void NoAction_189_5667271();
void NoAction_190_5667272();
void NoAction_191_5667273();
void NoAction_192_5667274();
void NoAction_193_5667275();
void NoAction_194_5667276();
void NoAction_195_5667277();
void NoAction_196_5667278();
void NoAction_197_5667279();
void NoAction_198_5667280();
void NoAction_199_5667281();
void NoAction_200_5667282();
void NoAction_201_5667283();
void NoAction_202_5667284();
void NoAction_203_5667285();
void NoAction_204_5667286();
void NoAction_205_5667287();
void NoAction_206_5667288();
void NoAction_207_5667289();
void NoAction_208_5667290();
void NoAction_209_5667291();
void NoAction_210_5667292();
void NoAction_211_5667293();
void NoAction_212_5667294();
void NoAction_213_5667295();
void NoAction_214_5667296();
void NoAction_215_5667297();
void NoAction_216_5667298();
void NoAction_217_5667299();
void NoAction_218_5667300();
void NoAction_219_5667301();
void NoAction_220_5667302();
void NoAction_221_5667303();
void NoAction_222_5667304();
void NoAction_223_5667305();
void NoAction_224_5667306();
void NoAction_225_5667307();
void NoAction_226_5667308();
void NoAction_227_5667309();
void NoAction_228_5667310();
void NoAction_229_5667311();
void NoAction_230_5667312();
void NoAction_231_5667313();
void NoAction_232_5667314();
void NoAction_233_5667315();
void NoAction_234_5667316();
void NoAction_235_5667317();
void NoAction_236_5667318();
void NoAction_237_5667319();
void NoAction_238_5667320();
void NoAction_239_5667321();
void NoAction_240_5667322();
void NoAction_241_5667323();
void NoAction_242_5667324();
void NoAction_243_5667325();
void NoAction_244_5667326();
void NoAction_245_5667327();
void NoAction_246_5667328();
void NoAction_247_5667329();
void NoAction_248_5667330();
void NoAction_249_5667331();
void NoAction_250_5667332();
void NoAction_251_5667333();
void NoAction_252_5667334();
void NoAction_253_5667335();
void NoAction_254_5667336();
void NoAction_255_5667337();
void NoAction_256_5667338();
void NoAction_257_5667339();
void rmac_hit_0_5667340();
void rmac_miss_0_5667356();
void rmac_5763151();
void _set_ifindex_5667439(uint32_t ifindex, uint8_t port_type);
void _set_ingress_port_properties_5667465(uint32_t if_label,
					  uint8_t qos_group,
					  uint8_t tc_qos_group, uint8_t tc,
					  uint8_t color, uint8_t trust_dscp,
					  uint8_t trust_pcp);
void _ingress_port_mapping_0_5763316();
void _ingress_port_properties_0_5763369();
void _malformed_outer_ethernet_packet_5667633(uint8_t drop_reason);
void _set_valid_outer_unicast_packet_untagged_5667657();
void _set_valid_outer_unicast_packet_single_tagged_5667682();
void _set_valid_outer_unicast_packet_double_tagged_5667722();
void _set_valid_outer_unicast_packet_qinq_tagged_5667762();
void _set_valid_outer_multicast_packet_untagged_5667799();
void _set_valid_outer_multicast_packet_single_tagged_5667824();
void _set_valid_outer_multicast_packet_double_tagged_5667864();
void _set_valid_outer_multicast_packet_qinq_tagged_5667904();
void _set_valid_outer_broadcast_packet_untagged_5667941();
void _set_valid_outer_broadcast_packet_single_tagged_5667966();
void _set_valid_outer_broadcast_packet_double_tagged_5668006();
void _set_valid_outer_broadcast_packet_qinq_tagged_5668046();
void _validate_outer_ethernet_0_5763871();
void _set_valid_outer_ipv4_packet_0_5668250();
void _set_malformed_outer_ipv4_packet_0_5668284(uint8_t drop_reason);
void _validate_outer_ipv4_packet_5764101();
void _set_valid_outer_ipv6_packet_0_5668385();
void _set_malformed_outer_ipv6_packet_0_5668419(uint8_t drop_reason);
void _validate_outer_ipv6_packet_5764247();
void _set_valid_mpls_label1_0_5668520();
void _set_valid_mpls_label2_0_5668554();
void _set_valid_mpls_label3_0_5668588();
void _validate_mpls_packet_5764437();
void _set_config_parameters_5668783(uint8_t enable_dod);
void _switch_config_params_0_5668845();
void _set_bd_properties_5668883(uint32_t bd, uint32_t vrf,
				uint32_t stp_group, uint8_t learning_enabled,
				uint32_t bd_label, uint32_t stats_idx,
				uint32_t rmac_group,
				uint8_t ipv4_unicast_enabled,
				uint8_t ipv6_unicast_enabled,
				uint8_t ipv4_urpf_mode,
				uint8_t ipv6_urpf_mode,
				uint8_t igmp_snooping_enabled,
				uint8_t mld_snooping_enabled,
				uint8_t ipv4_multicast_enabled,
				uint8_t ipv6_multicast_enabled,
				uint32_t mrpf_group, uint32_t ipv4_mcast_key,
				uint8_t ipv4_mcast_key_type,
				uint32_t ipv6_mcast_key,
				uint8_t ipv6_mcast_key_type);
void _port_vlan_mapping_miss_5669060();
void _port_vlan_mapping_0_5764924();
void _set_stp_state_5669191(uint8_t stp_state);
void _spanning_tree_0_5765071();
void _nop_38_5669270();
void _nop_39_5669280();
void _set_ingress_tc_5669281(uint8_t tc);
void _set_ingress_tc_2_5669299(uint8_t tc);
void _set_ingress_color_5669312(uint8_t color);
void _set_ingress_color_2_5669330(uint8_t color);
void _set_ingress_tc_and_color_5669343(uint8_t tc, uint8_t color);
void _set_ingress_tc_and_color_2_5669369(uint8_t tc, uint8_t color);
void _ingress_qos_map_dscp_0_5765257();
void _ingress_qos_map_pcp_0_5765341();
void _on_miss_9_5669548();
void _ipsg_miss_5669558();
void _ipsg_0_5765450();
void _ipsg_permit_special_0_5765540();
void _int_sink_update_vxlan_gpe_v4_5669726();
void _nop_40_5669781();
void _int_set_src_5669791();
void _int_set_no_src_5669807();
void _int_sink_gpe_5742384(uint32_t mirror_id);
void _int_no_sink_5670156();
void _int_sink_update_outer_0_5766058();
void _int_source_0_5766147();
void _int_terminate_0_5766284();
void _nop_41_5670516();
void _sflow_ing_pkt_to_cpu_5743245(uint32_t sflow_i2e_mirror_id);
void _sflow_ing_take_sample_0_5766498();
void _nop_42_5670658();
void _sflow_ing_session_enable_5670675(uint32_t rate_thr, uint32_t session_id);
void _sflow_ingress_0_5766625();
void _non_ip_lkp_5670809();
void _non_ip_lkp_2_5670837();
void _ipv4_lkp_5670858();
void _ipv4_lkp_2_5670940();
void _ipv6_lkp_5671015();
void _ipv6_lkp_2_5671097();
void _on_miss_10_5671172();
void _outer_rmac_hit_5671182();
void _nop_43_5671198();
void _tunnel_lookup_miss_5671208();
void _terminate_tunnel_inner_non_ip_5671218(uint32_t bd, uint32_t bd_label,
					    uint32_t stats_idx);
void _terminate_tunnel_inner_ethernet_ipv4_5671273(uint32_t bd, uint32_t vrf,
						   uint32_t rmac_group,
						   uint32_t bd_label,
						   uint8_t
						   ipv4_unicast_enabled,
						   uint8_t ipv4_urpf_mode,
						   uint8_t
						   igmp_snooping_enabled,
						   uint32_t stats_idx,
						   uint8_t
						   ipv4_multicast_enabled,
						   uint32_t mrpf_group);
void _terminate_tunnel_inner_ipv4_5671393(uint32_t vrf, uint32_t rmac_group,
					  uint8_t ipv4_urpf_mode,
					  uint8_t ipv4_unicast_enabled,
					  uint8_t ipv4_multicast_enabled,
					  uint32_t mrpf_group);
void _terminate_tunnel_inner_ethernet_ipv6_5671490(uint32_t bd, uint32_t vrf,
						   uint32_t rmac_group,
						   uint32_t bd_label,
						   uint8_t
						   ipv6_unicast_enabled,
						   uint8_t ipv6_urpf_mode,
						   uint8_t
						   mld_snooping_enabled,
						   uint32_t stats_idx,
						   uint8_t
						   ipv6_multicast_enabled,
						   uint32_t mrpf_group);
void _terminate_tunnel_inner_ipv6_5671610(uint32_t vrf, uint32_t rmac_group,
					  uint8_t ipv6_unicast_enabled,
					  uint8_t ipv6_urpf_mode,
					  uint8_t ipv6_multicast_enabled,
					  uint32_t mrpf_group);
void _adjust_lkp_fields_0_5671707();
void _outer_rmac_0_5767703();
void _tunnel_0_5767775();
void _tunnel_lookup_miss_2_5671974();
void _nop_44_5672049();
void _nop_45_5672059();
void _terminate_cpu_packet_0_5672060();
void _switch_fabric_unicast_packet_0_5672130();
void _terminate_fabric_unicast_packet_0_5672164();
void _switch_fabric_multicast_packet_0_5672261();
void _terminate_fabric_multicast_packet_0_5672286();
void _set_ingress_ifindex_properties_0_5672380();
void _non_ip_over_fabric_0_5672390();
void _ipv4_over_fabric_0_5672427();
void _ipv6_over_fabric_0_5672500();
void _fabric_ingress_dst_lkp_5768505();
void _fabric_ingress_src_lkp_5768584();
void _native_packet_over_fabric_5672707();
void _nop_46_5672786();
void _set_tunnel_termination_flag_1_5672796();
void _set_tunnel_vni_and_termination_flag_1_5672812(uint32_t tunnel_vni);
void _on_miss_11_5672836();
void _src_vtep_hit_1_5672846(uint32_t ifindex);
void _ipv4_dest_vtep_5768802();
void _ipv4_src_vtep_5768891();
void _nop_47_5673024();
void _set_tunnel_termination_flag_2_5673034();
void _set_tunnel_vni_and_termination_flag_2_5673050(uint32_t tunnel_vni);
void _on_miss_12_5673074();
void _src_vtep_hit_2_5673084(uint32_t ifindex);
void _ipv6_dest_vtep_5769052();
void _ipv6_src_vtep_5769141();
void _terminate_eompls_0_5673262(uint32_t bd, uint8_t tunnel_type);
void _terminate_vpls_0_5673303(uint32_t bd, uint8_t tunnel_type);
void _terminate_ipv4_over_mpls_0_5673344(uint32_t vrf, uint8_t tunnel_type);
void _terminate_ipv6_over_mpls_0_5673418(uint32_t vrf, uint8_t tunnel_type);
void _terminate_pw_0_5673492(uint32_t ifindex);
void _forward_mpls_0_5673528(uint32_t nexthop_index);
void _mpls_5769538();
void _nop_48_5673683();
void _nop_49_5673693();
void _on_miss_13_5673694();
void _outer_multicast_route_s_g_hit_1_5673704(uint32_t mc_index,
					      uint32_t mcast_rpf_group);
void _outer_multicast_bridge_s_g_hit_1_5673747(uint32_t mc_index);
void _outer_multicast_route_sm_star_g_hit_1_5673777(uint32_t mc_index,
						    uint32_t mcast_rpf_group);
void _outer_multicast_route_bidir_star_g_hit_1_5673826(uint32_t mc_index,
						       uint32_t
						       mcast_rpf_group);
void _outer_multicast_bridge_star_g_hit_1_5673875(uint32_t mc_index);
void _outer_ipv4_multicast_5769871();
void _outer_ipv4_multicast_star_g_5769978();
void _nop_50_5674093();
void _nop_51_5674103();
void _on_miss_14_5674104();
void _outer_multicast_route_s_g_hit_2_5674114(uint32_t mc_index,
					      uint32_t mcast_rpf_group);
void _outer_multicast_bridge_s_g_hit_2_5674157(uint32_t mc_index);
void _outer_multicast_route_sm_star_g_hit_2_5674187(uint32_t mc_index,
						    uint32_t mcast_rpf_group);
void _outer_multicast_route_bidir_star_g_hit_2_5674236(uint32_t mc_index,
						       uint32_t
						       mcast_rpf_group);
void _outer_multicast_bridge_star_g_hit_2_5674285(uint32_t mc_index);
void _outer_ipv6_multicast_5770295();
void _outer_ipv6_multicast_star_g_5770402();
void _nop_52_5674518();
void _set_storm_control_meter_5674528(uint32_t meter_idx);
void _storm_control_0_5770554();
void _nop_53_5674627();
void _set_unicast_5674637();
void _set_unicast_and_ipv6_src_is_link_local_5674653();
void _set_multicast_5674675();
void _set_multicast_and_ipv6_src_is_link_local_5674702();
void _set_broadcast_5674735();
void _set_malformed_packet_5674762(uint8_t drop_reason);
void _validate_packet_0_5770785();
void _nop_114_5674933();
void _nop_115_5674943();
void _set_ingress_dst_port_range_id_5674944(uint8_t range_id);
void _set_ingress_src_port_range_id_5674962(uint8_t range_id);
void _ingress_l4_dst_port_0_5771004();
void _ingress_l4_src_port_0_5771064();
void _nop_116_5675094();
void _nop_117_5675104();
void _dmac_hit_5675105(uint32_t ifindex);
void _dmac_multicast_hit_5675135(uint32_t mc_index);
void _dmac_miss_5675159();
void _dmac_redirect_nexthop_5675181(uint32_t nexthop_index);
void _dmac_redirect_ecmp_5675211(uint32_t ecmp_index);
void _dmac_drop_5675241();
void _smac_miss_5675257();
void _smac_hit_5675273(uint32_t ifindex);
void _dmac_0_5771325();
void _smac_0_5771430();
void _nop_118_5675469();
void _acl_deny_5675479(uint32_t acl_stats_index, uint32_t acl_meter_index,
		       uint32_t acl_copy_reason, uint8_t nat_mode,
		       uint8_t ingress_cos, uint8_t tc, uint8_t color);
void _acl_permit_5675551(uint32_t acl_stats_index, uint32_t acl_meter_index,
			 uint32_t acl_copy_reason, uint8_t nat_mode,
			 uint8_t ingress_cos, uint8_t tc, uint8_t color);
void _acl_redirect_nexthop_5675617(uint32_t nexthop_index,
				   uint32_t acl_stats_index,
				   uint32_t acl_meter_index,
				   uint32_t acl_copy_reason,
				   uint8_t nat_mode, uint8_t ingress_cos,
				   uint8_t tc, uint8_t color);
void _acl_redirect_ecmp_5675703(uint32_t ecmp_index,
				uint32_t acl_stats_index,
				uint32_t acl_meter_index,
				uint32_t acl_copy_reason, uint8_t nat_mode,
				uint8_t ingress_cos, uint8_t tc, uint8_t color);
void _acl_mirror_5750005(uint32_t session_id, uint32_t acl_stats_index,
			 uint32_t acl_meter_index, uint8_t nat_mode,
			 uint8_t ingress_cos, uint8_t tc, uint8_t color);
void _mac_acl_0_5771917();
void _nop_119_5676001();
void _nop_120_5676011();
void _acl_deny_0_5676012(uint32_t acl_stats_index, uint32_t acl_meter_index,
			 uint32_t acl_copy_reason, uint8_t nat_mode,
			 uint8_t ingress_cos, uint8_t tc, uint8_t color);
void _acl_deny_4_5676084(uint32_t acl_stats_index, uint32_t acl_meter_index,
			 uint32_t acl_copy_reason, uint8_t nat_mode,
			 uint8_t ingress_cos, uint8_t tc, uint8_t color);
void _acl_permit_0_5676150(uint32_t acl_stats_index,
			   uint32_t acl_meter_index,
			   uint32_t acl_copy_reason, uint8_t nat_mode,
			   uint8_t ingress_cos, uint8_t tc, uint8_t color);
void _acl_permit_4_5676216(uint32_t acl_stats_index,
			   uint32_t acl_meter_index,
			   uint32_t acl_copy_reason, uint8_t nat_mode,
			   uint8_t ingress_cos, uint8_t tc, uint8_t color);
void _acl_redirect_nexthop_0_5676277(uint32_t nexthop_index,
				     uint32_t acl_stats_index,
				     uint32_t acl_meter_index,
				     uint32_t acl_copy_reason,
				     uint8_t nat_mode, uint8_t ingress_cos,
				     uint8_t tc, uint8_t color);
void _acl_redirect_nexthop_4_5676363(uint32_t nexthop_index,
				     uint32_t acl_stats_index,
				     uint32_t acl_meter_index,
				     uint32_t acl_copy_reason,
				     uint8_t nat_mode, uint8_t ingress_cos,
				     uint8_t tc, uint8_t color);
void _acl_redirect_ecmp_0_5676442(uint32_t ecmp_index,
				  uint32_t acl_stats_index,
				  uint32_t acl_meter_index,
				  uint32_t acl_copy_reason, uint8_t nat_mode,
				  uint8_t ingress_cos, uint8_t tc,
				  uint8_t color);
void _acl_redirect_ecmp_4_5676528(uint32_t ecmp_index,
				  uint32_t acl_stats_index,
				  uint32_t acl_meter_index,
				  uint32_t acl_copy_reason, uint8_t nat_mode,
				  uint8_t ingress_cos, uint8_t tc,
				  uint8_t color);
void _acl_mirror_0_5751199(uint32_t session_id, uint32_t acl_stats_index,
			   uint32_t acl_meter_index, uint8_t nat_mode,
			   uint8_t ingress_cos, uint8_t tc, uint8_t color);
void _acl_mirror_4_5751339(uint32_t session_id, uint32_t acl_stats_index,
			   uint32_t acl_meter_index, uint8_t nat_mode,
			   uint8_t ingress_cos, uint8_t tc, uint8_t color);
void _ip_acl_0_5772828();
void _ipv6_acl_0_5773009();
void _nop_121_5677099();
void _racl_deny_5677109(uint32_t acl_stats_index, uint32_t acl_copy_reason,
			uint8_t ingress_cos, uint8_t tc, uint8_t color);
void _racl_permit_5677165(uint32_t acl_stats_index, uint32_t acl_copy_reason,
			  uint8_t ingress_cos, uint8_t tc, uint8_t color);
void _racl_redirect_nexthop_5677215(uint32_t nexthop_index,
				    uint32_t acl_stats_index,
				    uint32_t acl_copy_reason,
				    uint8_t ingress_cos, uint8_t tc,
				    uint8_t color);
void _racl_redirect_ecmp_5677285(uint32_t ecmp_index,
				 uint32_t acl_stats_index,
				 uint32_t acl_copy_reason,
				 uint8_t ingress_cos, uint8_t tc,
				 uint8_t color);
void _ipv4_racl_0_5773444();
void _on_miss_15_5677480();
void _ipv4_urpf_hit_5677490(uint32_t urpf_bd_group);
void _ipv4_urpf_hit_2_5677523(uint32_t urpf_bd_group);
void _urpf_miss_5677550();
void _ipv4_urpf_0_5773669();
void _ipv4_urpf_lpm_0_5773741();
void _on_miss_16_5677700();
void _on_miss_17_5677710();
void _fib_hit_nexthop_5677711(uint32_t nexthop_index);
void _fib_hit_nexthop_0_5677741(uint32_t nexthop_index);
void _fib_hit_ecmp_5677764(uint32_t ecmp_index);
void _fib_hit_ecmp_0_5677794(uint32_t ecmp_index);
void _ipv4_fib_0_5773933();
void _ipv4_fib_lpm_0_5774011();
void _nop_122_5677963();
void _racl_deny_0_5677973(uint32_t acl_stats_index, uint32_t acl_copy_reason,
			  uint8_t ingress_cos, uint8_t tc, uint8_t color);
void _racl_permit_0_5678029(uint32_t acl_stats_index,
			    uint32_t acl_copy_reason, uint8_t ingress_cos,
			    uint8_t tc, uint8_t color);
void _racl_redirect_nexthop_0_5678079(uint32_t nexthop_index,
				      uint32_t acl_stats_index,
				      uint32_t acl_copy_reason,
				      uint8_t ingress_cos, uint8_t tc,
				      uint8_t color);
void _racl_redirect_ecmp_0_5678149(uint32_t ecmp_index,
				   uint32_t acl_stats_index,
				   uint32_t acl_copy_reason,
				   uint8_t ingress_cos, uint8_t tc,
				   uint8_t color);
void _ipv6_racl_0_5774344();
void _on_miss_18_5678344();
void _ipv6_urpf_hit_5678354(uint32_t urpf_bd_group);
void _ipv6_urpf_hit_2_5678387(uint32_t urpf_bd_group);
void _urpf_miss_0_5678414();
void _ipv6_urpf_0_5774569();
void _ipv6_urpf_lpm_0_5774641();
void _on_miss_19_5678564();
void _on_miss_20_5678574();
void _fib_hit_nexthop_5_5678575(uint32_t nexthop_index);
void _fib_hit_nexthop_6_5678605(uint32_t nexthop_index);
void _fib_hit_ecmp_5_5678628(uint32_t ecmp_index);
void _fib_hit_ecmp_6_5678658(uint32_t ecmp_index);
void _ipv6_fib_0_5774833();
void _ipv6_fib_lpm_0_5774911();
void _nop_123_5678827();
void _urpf_bd_miss_5678837();
void _urpf_bd_0_5775014();
void _on_miss_21_5678948();
void _multicast_bridge_s_g_hit_1_5678958(uint32_t mc_index);
void _nop_124_5678982();
void _multicast_bridge_star_g_hit_1_5678992(uint32_t mc_index);
void _ipv4_multicast_bridge_5775182();
void _ipv4_multicast_bridge_star_g_5775266();
void _on_miss_22_5679160();
void _multicast_route_s_g_hit_1_5679177(uint32_t mc_index,
					uint32_t mcast_rpf_group);
void _ipv4_multicast_route_5775404();
void _multicast_route_star_g_miss_1_5679308();
void _multicast_route_sm_star_g_hit_1_5679331(uint32_t mc_index,
					      uint32_t mcast_rpf_group);
void _multicast_route_bidir_star_g_hit_1_5679381(uint32_t mc_index,
						 uint32_t mcast_rpf_group);
void _ipv4_multicast_route_star_g_5775614();
void _on_miss_23_5679536();
void _multicast_bridge_s_g_hit_2_5679546(uint32_t mc_index);
void _nop_125_5679570();
void _multicast_bridge_star_g_hit_2_5679580(uint32_t mc_index);
void _ipv6_multicast_bridge_5775791();
void _ipv6_multicast_bridge_star_g_5775874();
void _on_miss_33_5679748();
void _multicast_route_s_g_hit_2_5679765(uint32_t mc_index,
					uint32_t mcast_rpf_group);
void _ipv6_multicast_route_5776012();
void _multicast_route_star_g_miss_2_5679896();
void _multicast_route_sm_star_g_hit_2_5679919(uint32_t mc_index,
					      uint32_t mcast_rpf_group);
void _multicast_route_bidir_star_g_hit_2_5679969(uint32_t mc_index,
						 uint32_t mcast_rpf_group);
void _ipv6_multicast_route_star_g_5776222();
void _on_miss_34_5680096();
void _on_miss_35_5680106();
void _on_miss_36_5680107();
void _set_dst_nat_nexthop_index_5680108(uint32_t nexthop_index,
					uint8_t nexthop_type,
					uint32_t nat_rewrite_index);
void _set_dst_nat_nexthop_index_2_5680148(uint32_t nexthop_index,
					  uint8_t nexthop_type,
					  uint32_t nat_rewrite_index);
void _nop_126_5680182();
void _set_src_nat_rewrite_index_5680192(uint32_t nat_rewrite_index);
void _set_src_nat_rewrite_index_2_5680210(uint32_t nat_rewrite_index);
void _set_twice_nat_nexthop_index_5680223(uint32_t nexthop_index,
					  uint8_t nexthop_type,
					  uint32_t nat_rewrite_index);
void _set_twice_nat_nexthop_index_2_5680263(uint32_t nexthop_index,
					    uint8_t nexthop_type,
					    uint32_t nat_rewrite_index);
void _nat_dst_0_5776506();
void _nat_flow_0_5776602();
void _nat_src_0_5776733();
void _nat_twice_0_5776828();
void _nop_127_5680713();
void _meter_index_2_5776984();
void _compute_lkp_ipv4_hash_5680789();
void _compute_lkp_ipv6_hash_5680887();
void _compute_lkp_non_ip_hash_5680985();
void _computed_two_hashes_5681031();
void _computed_one_hash_5681060();
void _compute_ipv4_hashes_0_5777352();
void _compute_ipv6_hashes_0_5777402();
void _compute_non_ip_hashes_0_5777451();
void _compute_other_hashes_0_5777500();
void _meter_permit_5681306();
void _meter_deny_5681323();
void _meter_action_0_5777609();
void _update_ingress_bd_stats_5681436();
void _ingress_bd_stats_2_5681458();
void _acl_stats_update_5681515();
void _acl_stats_2_5681537();
void _nop_128_5681589();
void _storm_control_stats_2_5777874();
void _nop_129_5681671();
void _set_l2_redirect_action_5681681();
void _set_fib_redirect_action_5681727();
void _set_cpu_redirect_action_5681779();
void _set_acl_redirect_action_5681818();
void _set_racl_redirect_action_5681864();
void _set_nat_redirect_action_5681916();
void _set_multicast_route_action_5681962();
void _set_multicast_bridge_action_5682005();
void _set_multicast_flood_5682036();
void _set_multicast_drop_5682058();
void _fwd_result_0_5778353();
void _nop_130_5682321();
void _nop_131_5682331();
void _set_ecmp_nexthop_details_5682332(uint32_t ifindex, uint32_t bd,
				       uint32_t nhop_index, uint8_t tunnel);
void _set_ecmp_nexthop_details_for_post_routed_flood_5682396(uint32_t bd,
							     uint32_t
							     uuc_mc_index,
							     uint32_t
							     nhop_index);
void _set_nexthop_details_5682447(uint32_t ifindex, uint32_t bd,
				  uint8_t tunnel);
void _set_nexthop_details_for_post_routed_flood_5682503(uint32_t bd,
							uint32_t uuc_mc_index);
void _ecmp_group_0_5778848();
void _nexthop_0_5778930();
void _nop_132_5682686();
void _set_bd_flood_mc_index_5682696(uint32_t mc_index);
void _bd_flood_0_5779023();
void _set_lag_miss_5682781();
void _set_lag_port_5682791(uint32_t port);
void _set_lag_remote_port_5682808(uint8_t device, uint32_t port);
void _lag_group_0_5779148();
void _nop_133_5682911();
void _generate_learn_notify_5682921();
void _learn_notify_0_5779273();
void _nop_134_5683031();
void _set_fabric_lag_port_5683041(uint32_t port);
void _set_fabric_multicast_5683058(uint8_t fabric_mgid);
void _fabric_lag_0_5779404();
void _nop_135_5683151();
void _set_icos_5683161(uint8_t icos);
void _set_queue_5683179(uint8_t qid);
void _set_icos_and_queue_5683197(uint8_t icos, uint8_t qid);
void _traffic_class_0_5779554();
void _drop_stats_update_5683347();
void _nop_136_5683369();
void _copy_to_cpu_5683379(uint8_t qid, uint32_t meter_id, uint8_t icos);
void _redirect_to_cpu_5683450(uint8_t qid, uint32_t meter_id, uint8_t icos);
void _copy_to_cpu_with_reason_5759878(uint32_t reason_code, uint8_t qid,
				      uint32_t meter_id, uint8_t icos);
void _redirect_to_cpu_with_reason_5759995(uint32_t reason_code, uint8_t qid,
					  uint32_t meter_id, uint8_t icos);
void _drop_packet_0_5683688();
void _drop_packet_with_reason_5683704(uint32_t drop_reason);
void _negative_mirror_5683730(uint32_t session_id);
void _drop_stats_4_5683771();
void _system_acl_0_5780142();

typedef struct {
	uint32_t ingress_port:9;
	uint32_t egress_spec:9;
	uint32_t egress_port:9;
	uint32_t clone_spec:32;
	uint32_t instance_type:32;
	uint8_t drop:1;
	uint32_t recirculate_port:16;
	uint32_t packet_length:32;
	uint32_t enq_timestamp:32;
	uint32_t enq_qdepth:19;
	uint32_t deq_timedelta:32;
	uint32_t deq_qdepth:19;
	uint64_t ingress_global_timestamp:48;
	uint32_t lf_field_list:32;
	uint32_t mcast_grp:16;
	uint8_t resubmit_flag:1;
	uint32_t egress_rid:16;
	uint8_t checksum_error:1;
} standard_metadata_t;

void mark_to_drop()
{
	assert_forward = 0;
	end_assertions();
	exit(0);
}

typedef struct {
	uint8_t acl_deny:1;
	uint8_t racl_deny:1;
	uint32_t acl_nexthop:16;
	uint32_t racl_nexthop:16;
	uint8_t acl_nexthop_type:2;
	uint8_t racl_nexthop_type:2;
	uint8_t acl_redirect:1;
	uint8_t racl_redirect:1;
	uint32_t if_label:16;
	uint32_t bd_label:16;
	uint32_t acl_stats_index:14;
	uint32_t egress_if_label:16;
	uint32_t egress_bd_label:16;
	uint8_t ingress_src_port_range_id:8;
	uint8_t ingress_dst_port_range_id:8;
	uint8_t egress_src_port_range_id:8;
	uint8_t egress_dst_port_range_id:8;
} acl_metadata_t;

typedef struct {
	uint32_t ifindex_check:16;
	uint32_t bd:16;
	uint32_t inner_bd:16;
} egress_filter_metadata_t;

typedef struct {
	uint8_t bypass:1;
	uint8_t port_type:2;
	uint32_t payload_length:16;
	uint32_t smac_idx:9;
	uint32_t bd:16;
	uint32_t outer_bd:16;
	uint64_t mac_da:48;
	uint8_t routed:1;
	uint32_t same_bd_check:16;
	uint8_t drop_reason:8;
	uint32_t ifindex:16;
} egress_metadata_t;

typedef struct {
	uint8_t packetType:3;
	uint8_t fabric_header_present:1;
	uint32_t reason_code:16;
	uint8_t dst_device:8;
	uint32_t dst_port:16;
} fabric_metadata_t;

typedef struct {
	uint8_t enable_dod:1;
} global_config_metadata_t;

typedef struct {
	uint32_t hash1:16;
	uint32_t hash2:16;
	uint32_t entropy_hash:16;
} hash_metadata_t;

typedef struct {
	uint32_t ingress_tstamp:32;
	uint32_t mirror_session_id:16;
} i2e_metadata_t;

typedef struct {
	uint32_t ingress_port:9;
	uint32_t ifindex:16;
	uint32_t egress_ifindex:16;
	uint8_t port_type:2;
	uint32_t outer_bd:16;
	uint32_t bd:16;
	uint8_t drop_flag:1;
	uint8_t drop_reason:8;
	uint8_t control_frame:1;
	uint32_t bypass_lookups:16;
	uint32_t sflow_take_sample:32;
} ingress_metadata_t;

typedef struct {
	uint32_t switch_id:32;
	uint8_t insert_cnt:8;
	uint32_t insert_byte_cnt:16;
	uint32_t gpe_int_hdr_len:16;
	uint8_t gpe_int_hdr_len8:8;
	uint32_t instruction_cnt:16;
} int_metadata_t;

typedef struct {
	uint8_t sink:1;
	uint8_t source:1;
} int_metadata_i2e_t;

typedef struct {
	uint8_t resubmit_flag:1;
	uint64_t ingress_global_timestamp:48;
	uint32_t mcast_grp:16;
	uint8_t deflection_flag:1;
	uint8_t deflect_on_drop:1;
	uint8_t enq_congest_stat:2;
	uint8_t deq_congest_stat:2;
	uint32_t mcast_hash:13;
	uint32_t egress_rid:16;
	uint32_t lf_field_list:32;
	uint8_t priority:3;
	uint8_t ingress_cos:3;
	uint8_t packet_color:2;
	uint8_t qid:5;
} ingress_intrinsic_metadata_t;

typedef struct {
	uint32_t lkp_ipv4_sa:32;
	uint32_t lkp_ipv4_da:32;
	uint8_t ipv4_unicast_enabled:1;
	uint8_t ipv4_urpf_mode:2;
} ipv4_metadata_t;

typedef struct {
	uint64_t lkp_ipv6_sa:64;
	uint64_t lkp_ipv6_da:64;
	uint8_t ipv6_unicast_enabled:1;
	uint8_t ipv6_src_is_link_local:1;
	uint8_t ipv6_urpf_mode:2;
} ipv6_metadata_t;

typedef struct {
	uint64_t lkp_mac_sa:48;
	uint64_t lkp_mac_da:48;
	uint8_t lkp_pkt_type:3;
	uint32_t lkp_mac_type:16;
	uint8_t lkp_pcp:3;
	uint32_t l2_nexthop:16;
	uint8_t l2_nexthop_type:2;
	uint8_t l2_redirect:1;
	uint8_t l2_src_miss:1;
	uint32_t l2_src_move:16;
	uint32_t stp_group:10;
	uint8_t stp_state:3;
	uint32_t bd_stats_idx:16;
	uint8_t learning_enabled:1;
	uint8_t port_vlan_mapping_miss:1;
	uint32_t same_if_check:16;
} l2_metadata_t;

typedef struct {
	uint8_t lkp_ip_type:2;
	uint8_t lkp_ip_version:4;
	uint8_t lkp_ip_proto:8;
	uint8_t lkp_dscp:8;
	uint8_t lkp_ip_ttl:8;
	uint32_t lkp_l4_sport:16;
	uint32_t lkp_l4_dport:16;
	uint32_t lkp_outer_l4_sport:16;
	uint32_t lkp_outer_l4_dport:16;
	uint32_t vrf:16;
	uint32_t rmac_group:10;
	uint8_t rmac_hit:1;
	uint8_t urpf_mode:2;
	uint8_t urpf_hit:1;
	uint8_t urpf_check_fail:1;
	uint32_t urpf_bd_group:16;
	uint8_t fib_hit:1;
	uint32_t fib_nexthop:16;
	uint8_t fib_nexthop_type:2;
	uint32_t same_bd_check:16;
	uint32_t nexthop_index:16;
	uint8_t routed:1;
	uint8_t outer_routed:1;
	uint8_t mtu_index:8;
	uint8_t l3_copy:1;
	uint32_t l3_mtu_check:16;
	uint32_t egress_l4_sport:16;
	uint32_t egress_l4_dport:16;
} l3_metadata_t;

typedef struct {
	uint8_t packet_color:2;
	uint32_t meter_index:16;
} meter_metadata_t;

typedef struct {
	uint8_t ipv4_mcast_key_type:1;
	uint32_t ipv4_mcast_key:16;
	uint8_t ipv6_mcast_key_type:1;
	uint32_t ipv6_mcast_key:16;
	uint8_t outer_mcast_route_hit:1;
	uint8_t outer_mcast_mode:2;
	uint8_t mcast_route_hit:1;
	uint8_t mcast_bridge_hit:1;
	uint8_t ipv4_multicast_enabled:1;
	uint8_t ipv6_multicast_enabled:1;
	uint8_t igmp_snooping_enabled:1;
	uint8_t mld_snooping_enabled:1;
	uint32_t bd_mrpf_group:16;
	uint32_t mcast_rpf_group:16;
	uint8_t mcast_mode:2;
	uint32_t multicast_route_mc_index:16;
	uint32_t multicast_bridge_mc_index:16;
	uint8_t inner_replica:1;
	uint8_t replica:1;
	uint32_t mcast_grp:16;
} multicast_metadata_t;

typedef struct {
	uint8_t ingress_nat_mode:2;
	uint8_t egress_nat_mode:2;
	uint32_t nat_nexthop:16;
	uint8_t nat_nexthop_type:2;
	uint8_t nat_hit:1;
	uint32_t nat_rewrite_index:14;
	uint8_t update_checksum:1;
	uint8_t update_inner_checksum:1;
	uint32_t l4_len:16;
} nat_metadata_t;

typedef struct {
	uint8_t nexthop_type:2;
} nexthop_metadata_t;

typedef struct {
	uint8_t ingress_qos_group:5;
	uint8_t tc_qos_group:5;
	uint8_t egress_qos_group:5;
	uint8_t lkp_tc:8;
	uint8_t trust_dscp:1;
	uint8_t trust_pcp:1;
} qos_metadata_t;

typedef struct {
	uint64_t enq_timestamp:48;
	uint32_t enq_qdepth:16;
	uint32_t deq_timedelta:32;
	uint32_t deq_qdepth:16;
} queueing_metadata_t;

typedef struct {
	uint8_t ipsg_enabled:1;
	uint8_t ipsg_check_fail:1;
} security_metadata_t;

typedef struct {
	uint32_t sflow_session_id:16;
} sflow_meta_t;

typedef struct {
	uint8_t ingress_tunnel_type:5;
	uint32_t tunnel_vni:24;
	uint8_t mpls_enabled:1;
	uint32_t mpls_label:20;
	uint8_t mpls_exp:3;
	uint8_t mpls_ttl:8;
	uint8_t egress_tunnel_type:5;
	uint32_t tunnel_index:14;
	uint32_t tunnel_src_index:9;
	uint32_t tunnel_smac_index:9;
	uint32_t tunnel_dst_index:14;
	uint32_t tunnel_dmac_index:14;
	uint32_t vnid:24;
	uint8_t tunnel_terminate:1;
	uint8_t tunnel_if_check:1;
	uint8_t egress_header_count:4;
	uint8_t inner_ip_proto:8;
	uint8_t skip_encap_inner:1;
} tunnel_metadata_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t version:3;
	uint8_t diag:5;
	uint8_t state:2;
	uint8_t p:1;
	uint8_t f:1;
	uint8_t c:1;
	uint8_t a:1;
	uint8_t d:1;
	uint8_t m:1;
	uint8_t detectMult:8;
	uint8_t len:8;
	uint32_t myDiscriminator:32;
	uint32_t yourDiscriminator:32;
	uint32_t desiredMinTxInterval:32;
	uint32_t requiredMinRxInterval:32;
	uint32_t requiredMinEchoRxInterval:32;
} bfd_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t zero:4;
	uint32_t reserved:12;
	uint32_t seqNo:16;
} eompls_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t version:4;
	uint32_t vlan:12;
	uint8_t priority:6;
	uint32_t span_id:10;
	uint32_t timestamp:32;
	uint32_t sgt:16;
	uint32_t ft_d_other:16;
} erspan_header_t3_t_0;

typedef struct {
	uint8_t isValid:1;
	uint64_t dstAddr:48;
	uint64_t srcAddr:48;
	uint32_t etherType:16;
} ethernet_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t packetType:3;
	uint8_t headerVersion:2;
	uint8_t packetVersion:2;
	uint8_t pad1:1;
	uint8_t fabricColor:3;
	uint8_t fabricQos:5;
	uint8_t dstDevice:8;
	uint32_t dstPortOrGroup:16;
} fabric_header_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t egressQueue:5;
	uint8_t txBypass:1;
	uint8_t reserved:2;
	uint32_t ingressPort:16;
	uint32_t ingressIfindex:16;
	uint32_t ingressBd:16;
	uint32_t reasonCode:16;
	uint32_t mcast_grp:16;
} fabric_header_cpu_t;

typedef struct {
	uint8_t isValid:1;
	uint32_t rewriteIndex:16;
	uint32_t egressPort:10;
	uint8_t egressQueue:5;
	uint8_t pad:1;
} fabric_header_mirror_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t routed:1;
	uint8_t outerRouted:1;
	uint8_t tunnelTerminate:1;
	uint8_t ingressTunnelType:5;
	uint32_t ingressIfindex:16;
	uint32_t ingressBd:16;
	uint32_t mcastGrp:16;
} fabric_header_multicast_t;

typedef struct {
	uint8_t isValid:1;
	uint32_t sflow_session_id:16;
	uint32_t sflow_egress_ifindex:16;
} fabric_header_sflow_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t routed:1;
	uint8_t outerRouted:1;
	uint8_t tunnelTerminate:1;
	uint8_t ingressTunnelType:5;
	uint32_t nexthopIndex:16;
} fabric_header_unicast_t;

typedef struct {
	uint8_t isValid:1;
	uint32_t etherType:16;
} fabric_payload_header_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t version:4;
	uint8_t type_:4;
	uint8_t sof:8;
	uint32_t rsvd1:32;
	uint32_t ts_upper:32;
	uint32_t ts_lower:32;
	uint32_t size_:32;
	uint8_t eof:8;
	uint32_t rsvd2:24;
} fcoe_header_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t ver:2;
	uint8_t optLen:6;
	uint8_t oam:1;
	uint8_t critical:1;
	uint8_t reserved:6;
	uint32_t protoType:16;
	uint32_t vni:24;
	uint8_t reserved2:8;
} genv_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t C:1;
	uint8_t R:1;
	uint8_t K:1;
	uint8_t S:1;
	uint8_t s:1;
	uint8_t recurse:3;
	uint8_t flags:5;
	uint8_t ver:3;
	uint32_t proto:16;
} gre_t;

typedef struct {
	uint8_t isValid:1;
	uint32_t typeCode:16;
	uint32_t hdrChecksum:16;
} icmp_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t version:4;
	uint8_t ihl:4;
	uint8_t diffserv:8;
	uint32_t totalLen:16;
	uint32_t identification:16;
	uint8_t flags:3;
	uint32_t fragOffset:13;
	uint8_t ttl:8;
	uint8_t protocol:8;
	uint32_t hdrChecksum:16;
	uint32_t srcAddr:32;
	uint32_t dstAddr:32;
} ipv4_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t version:4;
	uint8_t trafficClass:8;
	uint32_t flowLabel:20;
	uint32_t payloadLen:16;
	uint8_t nextHdr:8;
	uint8_t hopLimit:8;
	uint64_t srcAddr:64;
	uint64_t dstAddr:64;
} ipv6_t;

typedef struct {
	uint8_t isValid:1;
	uint32_t srcPort:16;
	uint32_t dstPort:16;
	uint32_t verifTag:32;
	uint32_t checksum:32;
} sctp_t;

typedef struct {
	uint8_t isValid:1;
	uint32_t srcPort:16;
	uint32_t dstPort:16;
	uint32_t seqNo:32;
	uint32_t ackNo:32;
	uint8_t dataOffset:4;
	uint8_t res:4;
	uint8_t flags:8;
	uint32_t window:16;
	uint32_t checksum:16;
	uint32_t urgentPtr:16;
} tcp_t;

typedef struct {
	uint8_t isValid:1;
	uint32_t srcPort:16;
	uint32_t dstPort:16;
	uint32_t length_:16;
	uint32_t checksum:16;
} udp_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t bos:1;
	uint32_t egress_port_id:31;
} int_egress_port_id_header_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t bos:1;
	uint32_t egress_port_tx_utilization:31;
} int_egress_port_tx_utilization_header_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t ver:2;
	uint8_t rep:2;
	uint8_t c:1;
	uint8_t e:1;
	uint8_t rsvd1:5;
	uint8_t ins_cnt:5;
	uint8_t max_hop_cnt:8;
	uint8_t total_hop_cnt:8;
	uint8_t instruction_mask_0003:4;
	uint8_t instruction_mask_0407:4;
	uint8_t instruction_mask_0811:4;
	uint8_t instruction_mask_1215:4;
	uint32_t rsvd2:16;
} int_header_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t bos:1;
	uint32_t hop_latency:31;
} int_hop_latency_header_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t bos:1;
	uint32_t ingress_port_id_1:15;
	uint32_t ingress_port_id_0:16;
} int_ingress_port_id_header_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t bos:1;
	uint32_t ingress_tstamp:31;
} int_ingress_tstamp_header_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t bos:1;
	uint32_t q_congestion:31;
} int_q_congestion_header_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t bos:1;
	uint8_t q_occupancy1:7;
	uint32_t q_occupancy0:24;
} int_q_occupancy_header_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t bos:1;
	uint32_t switch_id:31;
} int_switch_id_header_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t flags:8;
	uint32_t nonce:24;
	uint32_t lsbsInstanceId:32;
} lisp_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t dsap:8;
	uint8_t ssap:8;
	uint8_t control_:8;
} llc_header_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t oam:1;
	uint8_t context:1;
	uint8_t flags:6;
	uint8_t reserved:8;
	uint32_t protoType:16;
	uint32_t spath:24;
	uint8_t sindex:8;
} nsh_t;

typedef struct {
	uint8_t isValid:1;
	uint32_t network_platform:32;
	uint32_t network_shared:32;
	uint32_t service_platform:32;
	uint32_t service_shared:32;
} nsh_context_t;

typedef struct {
	uint8_t isValid:1;
	uint32_t tni:24;
	uint8_t flow_id:8;
} nvgre_t;

typedef struct {
	uint8_t isValid:1;
	uint64_t ib_grh:64;
	uint64_t ib_bth:64;
} roce_header_t;

typedef struct {
	uint8_t isValid:1;
	uint64_t ib_bth:64;
} roce_v2_header_t;

typedef struct {
	uint8_t isValid:1;
	uint32_t version:32;
	uint32_t addrType:32;
	uint32_t ipAddress:32;
	uint32_t subAgentId:32;
	uint32_t seqNumber:32;
	uint32_t uptime:32;
	uint32_t numSamples:32;
} sflow_hdr_t;

typedef struct {
	uint8_t isValid:1;
	uint32_t enterprise:20;
	uint32_t format:12;
	uint32_t flowDataLength:32;
	uint32_t headerProtocol:32;
	uint32_t frameLength:32;
	uint32_t bytesRemoved:32;
	uint32_t headerSize:32;
} sflow_raw_hdr_record_t;

typedef struct {
	uint8_t isValid:1;
	uint32_t enterprise:20;
	uint32_t format:12;
	uint32_t sampleLength:32;
	uint32_t seqNumer:32;
	uint8_t srcIdType:8;
	uint32_t srcIdIndex:24;
	uint32_t samplingRate:32;
	uint32_t samplePool:32;
	uint32_t numDrops:32;
	uint32_t inputIfindex:32;
	uint32_t outputIfindex:32;
	uint32_t numFlowRecords:32;
} sflow_sample_t;

typedef struct {
	uint8_t isValid:1;
	uint32_t oui:24;
	uint32_t type_:16;
} snap_header_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t version:2;
	uint8_t reserved:2;
	uint8_t multiDestination:1;
	uint8_t optLength:5;
	uint8_t hopCount:6;
	uint32_t egressRbridge:16;
	uint32_t ingressRbridge:16;
} trill_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t direction:1;
	uint8_t pointer:1;
	uint32_t destVif:14;
	uint8_t looped:1;
	uint8_t reserved:1;
	uint8_t version:2;
	uint32_t srcVif:12;
} vntag_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t flags:8;
	uint32_t reserved:24;
	uint32_t vni:24;
	uint8_t reserved2:8;
} vxlan_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t flags:8;
	uint32_t reserved:16;
	uint8_t next_proto:8;
	uint32_t vni:24;
	uint8_t reserved2:8;
} vxlan_gpe_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t int_type:8;
	uint8_t rsvd:8;
	uint8_t len:8;
	uint8_t next_proto:8;
} vxlan_gpe_int_header_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t bos:1;
	uint32_t val:31;
} int_value_t;

typedef struct {
	uint8_t isValid:1;
	uint32_t label:20;
	uint8_t exp:3;
	uint8_t bos:1;
	uint8_t ttl:8;
} mpls_t;

typedef struct {
	uint8_t isValid:1;
	uint8_t pcp:3;
	uint8_t cfi:1;
	uint32_t vid:12;
	uint32_t etherType:16;
} vlan_tag_t;

typedef struct {
	acl_metadata_t acl_metadata;
	egress_filter_metadata_t egress_filter_metadata;
	egress_metadata_t egress_metadata;
	fabric_metadata_t fabric_metadata;
	global_config_metadata_t global_config_metadata;
	hash_metadata_t hash_metadata;
	i2e_metadata_t i2e_metadata;
	ingress_metadata_t ingress_metadata;
	int_metadata_t int_metadata;
	int_metadata_i2e_t int_metadata_i2e;
	ipv4_metadata_t ipv4_metadata;
	ipv6_metadata_t ipv6_metadata;
	l2_metadata_t l2_metadata;
	l3_metadata_t l3_metadata;
	meter_metadata_t meter_metadata;
	multicast_metadata_t multicast_metadata;
	nat_metadata_t nat_metadata;
	nexthop_metadata_t nexthop_metadata;
	qos_metadata_t qos_metadata;
	queueing_metadata_t queueing_metadata;
	security_metadata_t security_metadata;
	sflow_meta_t sflow_metadata;
	tunnel_metadata_t tunnel_metadata;
} metadata;

ingress_intrinsic_metadata_t intrinsic_metadata;

typedef struct {
	bfd_t bfd;
	eompls_t eompls;
	erspan_header_t3_t_0 erspan_t3_header;
	ethernet_t ethernet;
	fabric_header_t fabric_header;
	fabric_header_cpu_t fabric_header_cpu;
	fabric_header_mirror_t fabric_header_mirror;
	fabric_header_multicast_t fabric_header_multicast;
	fabric_header_sflow_t fabric_header_sflow;
	fabric_header_unicast_t fabric_header_unicast;
	fabric_payload_header_t fabric_payload_header;
	fcoe_header_t fcoe;
	genv_t genv;
	gre_t gre;
	icmp_t icmp;
	ethernet_t inner_ethernet;
	icmp_t inner_icmp;
	ipv4_t inner_ipv4;
	ipv6_t inner_ipv6;
	sctp_t inner_sctp;
	tcp_t inner_tcp;
	udp_t inner_udp;
	int_egress_port_id_header_t int_egress_port_id_header;
	 int_egress_port_tx_utilization_header_t
	    int_egress_port_tx_utilization_header;
	int_header_t int_header;
	int_hop_latency_header_t int_hop_latency_header;
	int_ingress_port_id_header_t int_ingress_port_id_header;
	int_ingress_tstamp_header_t int_ingress_tstamp_header;
	int_q_congestion_header_t int_q_congestion_header;
	int_q_occupancy_header_t int_q_occupancy_header;
	int_switch_id_header_t int_switch_id_header;
	ipv4_t ipv4;
	ipv6_t ipv6;
	lisp_t lisp;
	llc_header_t llc_header;
	nsh_t nsh;
	nsh_context_t nsh_context;
	nvgre_t nvgre;
	udp_t outer_udp;
	roce_header_t roce;
	roce_v2_header_t roce_v2;
	sctp_t sctp;
	sflow_hdr_t sflow;
	sflow_raw_hdr_record_t sflow_raw_hdr_record;
	sflow_sample_t sflow_sample;
	snap_header_t snap_header;
	tcp_t tcp;
	trill_t trill;
	udp_t udp;
	vntag_t vntag;
	vxlan_t vxlan;
	vxlan_gpe_t vxlan_gpe;
	vxlan_gpe_int_header_t vxlan_gpe_int_header;
	int int_val_index;
	int_value_t int_val[24];
	int mpls_index;
	mpls_t mpls[3];
	int vlan_tag__index;
	vlan_tag_t vlan_tag_[2];
} headers;

headers hdr;
metadata meta;
standard_metadata_t standard_metadata;

uint8_t tmp_0;

void parse_arp_rarp()
{
	parse_set_prio_med();
}

void parse_eompls()
{
	meta.tunnel_metadata.ingress_tunnel_type = 6;
	parse_inner_ethernet();
}

void parse_erspan_t3()
{
	//Extract hdr.erspan_t3_header
	hdr.erspan_t3_header.isValid = 1;
	parse_inner_ethernet();
}

void parse_ethernet()
{
	//Extract hdr.ethernet
	hdr.ethernet.isValid = 1;
	hdr.ethernet.etherType = 2048;
	if (((hdr.ethernet.etherType & 65024) == (0 & 65024))) {
		parse_llc_header();
	} else if (((hdr.ethernet.etherType & 64000) == (0 & 64000))) {
		parse_llc_header();
	} else if ((hdr.ethernet.etherType == 36864)) {
		parse_fabric_header();
	} else if ((hdr.ethernet.etherType == 33024)) {
		parse_vlan();
	} else if ((hdr.ethernet.etherType == 37120)) {
		parse_qinq();
	} else if ((hdr.ethernet.etherType == 34887)) {
		parse_mpls();
	} else if ((hdr.ethernet.etherType == 2048)) {
		parse_ipv4();
	} else if ((hdr.ethernet.etherType == 34525)) {
		parse_ipv6();
	} else if ((hdr.ethernet.etherType == 2054)) {
		parse_arp_rarp();
	} else if ((hdr.ethernet.etherType == 35020)) {
		parse_set_prio_high();
	} else if ((hdr.ethernet.etherType == 34825)) {
		parse_set_prio_high();
	} else {
		accept();
	}
}

void parse_fabric_header()
{
	//Extract hdr.fabric_header
	hdr.fabric_header.isValid = 1;
	if ((hdr.fabric_header.packetType == 1)) {
		parse_fabric_header_unicast();
	} else if ((hdr.fabric_header.packetType == 2)) {
		parse_fabric_header_multicast();
	} else if ((hdr.fabric_header.packetType == 3)) {
		parse_fabric_header_mirror();
	} else if ((hdr.fabric_header.packetType == 5)) {
		parse_fabric_header_cpu();
	} else {
		accept();
	}
}

void parse_fabric_header_cpu()
{
	//Extract hdr.fabric_header_cpu
	hdr.fabric_header_cpu.isValid = 1;
	meta.ingress_metadata.bypass_lookups = hdr.fabric_header_cpu.reasonCode;
	if ((hdr.fabric_header_cpu.reasonCode == 4)) {
		parse_fabric_sflow_header();
	} else {
		parse_fabric_payload_header();
	}
}

void parse_fabric_header_mirror()
{
	//Extract hdr.fabric_header_mirror
	hdr.fabric_header_mirror.isValid = 1;
	parse_fabric_payload_header();
}

void parse_fabric_header_multicast()
{
	//Extract hdr.fabric_header_multicast
	hdr.fabric_header_multicast.isValid = 1;
	parse_fabric_payload_header();
}

void parse_fabric_header_unicast()
{
	//Extract hdr.fabric_header_unicast
	hdr.fabric_header_unicast.isValid = 1;
	parse_fabric_payload_header();
}

void parse_fabric_payload_header()
{
	//Extract hdr.fabric_payload_header
	hdr.fabric_payload_header.isValid = 1;
	if (((hdr.fabric_payload_header.etherType & 65024) == (0 & 65024))) {
		parse_llc_header();
	} else
	    if (((hdr.fabric_payload_header.etherType & 64000) ==
		 (0 & 64000))) {
		parse_llc_header();
	} else if ((hdr.fabric_payload_header.etherType == 33024)) {
		parse_vlan();
	} else if ((hdr.fabric_payload_header.etherType == 37120)) {
		parse_qinq();
	} else if ((hdr.fabric_payload_header.etherType == 34887)) {
		parse_mpls();
	} else if ((hdr.fabric_payload_header.etherType == 2048)) {
		parse_ipv4();
	} else if ((hdr.fabric_payload_header.etherType == 34525)) {
		parse_ipv6();
	} else if ((hdr.fabric_payload_header.etherType == 2054)) {
		parse_arp_rarp();
	} else if ((hdr.fabric_payload_header.etherType == 35020)) {
		parse_set_prio_high();
	} else if ((hdr.fabric_payload_header.etherType == 34825)) {
		parse_set_prio_high();
	} else {
		accept();
	}
}

void parse_fabric_sflow_header()
{
	//Extract hdr.fabric_header_sflow
	hdr.fabric_header_sflow.isValid = 1;
	parse_fabric_payload_header();
}

void parse_geneve()
{
	//Extract hdr.genv
	hdr.genv.isValid = 1;
	meta.tunnel_metadata.tunnel_vni = hdr.genv.vni;
	meta.tunnel_metadata.ingress_tunnel_type = 4;
	if ((hdr.genv.ver == 0) && (hdr.genv.optLen == 0)
	    && (hdr.genv.protoType == 25944)) {
		parse_inner_ethernet();
	}
}

void parse_gpe_int_header()
{
	//Extract hdr.vxlan_gpe_int_header
	hdr.vxlan_gpe_int_header.isValid = 1;
	meta.int_metadata.gpe_int_hdr_len =
	    (uint32_t) hdr.vxlan_gpe_int_header.len;
	parse_int_header();
}

void parse_gre()
{
	//Extract hdr.gre
	hdr.gre.isValid = 1;
	if ((hdr.gre.C == 0) && (hdr.gre.R == 0) && (hdr.gre.K == 1)
	    && (hdr.gre.S == 0) && (hdr.gre.s == 0) && (hdr.gre.recurse == 0)
	    && (hdr.gre.flags == 0) && (hdr.gre.ver == 0)
	    && (hdr.gre.proto == 25944)) {
		parse_nvgre();
	} else if ((hdr.gre.C == 0) && (hdr.gre.R == 0) && (hdr.gre.K == 0)
		   && (hdr.gre.S == 0) && (hdr.gre.s == 0)
		   && (hdr.gre.recurse == 0)
		   && (hdr.gre.flags == 0) && (hdr.gre.ver == 0)
		   && (hdr.gre.proto == 2048)) {
		parse_gre_ipv4();
	} else if ((hdr.gre.C == 0) && (hdr.gre.R == 0) && (hdr.gre.K == 0)
		   && (hdr.gre.S == 0) && (hdr.gre.s == 0)
		   && (hdr.gre.recurse == 0)
		   && (hdr.gre.flags == 0) && (hdr.gre.ver == 0)
		   && (hdr.gre.proto == 34525)) {
		parse_gre_ipv6();
	} else if ((hdr.gre.C == 0) && (hdr.gre.R == 0) && (hdr.gre.K == 0)
		   && (hdr.gre.S == 0) && (hdr.gre.s == 0)
		   && (hdr.gre.recurse == 0)
		   && (hdr.gre.flags == 0) && (hdr.gre.ver == 0)
		   && (hdr.gre.proto == 8939)) {
		parse_erspan_t3();
	} else {
		accept();
	}
}

void parse_gre_ipv4()
{
	meta.tunnel_metadata.ingress_tunnel_type = 2;
	parse_inner_ipv4();
}

void parse_gre_ipv6()
{
	meta.tunnel_metadata.ingress_tunnel_type = 2;
	parse_inner_ipv6();
}

void parse_icmp()
{
	//Extract hdr.icmp
	hdr.icmp.isValid = 1;
	meta.l3_metadata.lkp_outer_l4_sport = hdr.icmp.typeCode;
	if (((hdr.icmp.typeCode & 65024) == (33280 & 65024))) {
		parse_set_prio_med();
	} else if (((hdr.icmp.typeCode & 64512) == (33792 & 64512))) {
		parse_set_prio_med();
	} else if (((hdr.icmp.typeCode & 65280) == (34816 & 65280))) {
		parse_set_prio_med();
	} else {
		accept();
	}
}

void parse_inner_ethernet()
{
	//Extract hdr.inner_ethernet
	hdr.inner_ethernet.isValid = 1;
	meta.l2_metadata.lkp_mac_sa = hdr.inner_ethernet.srcAddr;
	meta.l2_metadata.lkp_mac_da = hdr.inner_ethernet.dstAddr;
	if ((hdr.inner_ethernet.etherType == 2048)) {
		parse_inner_ipv4();
	} else if ((hdr.inner_ethernet.etherType == 34525)) {
		parse_inner_ipv6();
	} else {
		accept();
	}
}

void parse_inner_icmp()
{
	//Extract hdr.inner_icmp
	hdr.inner_icmp.isValid = 1;
	meta.l3_metadata.lkp_l4_sport = hdr.inner_icmp.typeCode;
	accept();
}

void parse_inner_ipv4()
{
	//Extract hdr.inner_ipv4
	hdr.inner_ipv4.isValid = 1;
	meta.ipv4_metadata.lkp_ipv4_sa = hdr.inner_ipv4.srcAddr;
	meta.ipv4_metadata.lkp_ipv4_da = hdr.inner_ipv4.dstAddr;
	meta.l3_metadata.lkp_ip_proto = hdr.inner_ipv4.protocol;
	meta.l3_metadata.lkp_ip_ttl = hdr.inner_ipv4.ttl;
	if ((hdr.inner_ipv4.fragOffset == 0) && (hdr.inner_ipv4.ihl == 5)
	    && (hdr.inner_ipv4.protocol == 1)) {
		parse_inner_icmp();
	} else if ((hdr.inner_ipv4.fragOffset == 0) && (hdr.inner_ipv4.ihl == 5)
		   && (hdr.inner_ipv4.protocol == 6)) {
		parse_inner_tcp();
	} else if ((hdr.inner_ipv4.fragOffset == 0) && (hdr.inner_ipv4.ihl == 5)
		   && (hdr.inner_ipv4.protocol == 17)) {
		parse_inner_udp();
	} else {
		accept();
	}
}

void parse_inner_ipv6()
{
	//Extract hdr.inner_ipv6
	hdr.inner_ipv6.isValid = 1;
	meta.ipv6_metadata.lkp_ipv6_sa = hdr.inner_ipv6.srcAddr;
	meta.ipv6_metadata.lkp_ipv6_da = hdr.inner_ipv6.dstAddr;
	meta.l3_metadata.lkp_ip_proto = hdr.inner_ipv6.nextHdr;
	meta.l3_metadata.lkp_ip_ttl = hdr.inner_ipv6.hopLimit;
	if ((hdr.inner_ipv6.nextHdr == 58)) {
		parse_inner_icmp();
	} else if ((hdr.inner_ipv6.nextHdr == 6)) {
		parse_inner_tcp();
	} else if ((hdr.inner_ipv6.nextHdr == 17)) {
		parse_inner_udp();
	} else {
		accept();
	}
}

void parse_inner_tcp()
{
	//Extract hdr.inner_tcp
	hdr.inner_tcp.isValid = 1;
	meta.l3_metadata.lkp_l4_sport = hdr.inner_tcp.srcPort;
	meta.l3_metadata.lkp_l4_dport = hdr.inner_tcp.dstPort;
	accept();
}

void parse_inner_udp()
{
	//Extract hdr.inner_udp
	hdr.inner_udp.isValid = 1;
	meta.l3_metadata.lkp_l4_sport = hdr.inner_udp.srcPort;
	meta.l3_metadata.lkp_l4_dport = hdr.inner_udp.dstPort;
	accept();
}

void parse_int_header()
{
	//Extract hdr.int_header
	hdr.int_header.isValid = 1;
	meta.int_metadata.instruction_cnt = (uint32_t) hdr.int_header.ins_cnt;
	if ((hdr.int_header.rsvd1 == 0) && (hdr.int_header.total_hop_cnt == 0)) {
		accept();
	} else if (((hdr.int_header.rsvd1 & 15) == (0 & 15))
		   && ((hdr.int_header.total_hop_cnt & 0) == (0 & 0))) {
		parse_int_val();
	} else {
		accept();
	}
}

void parse_int_val()
{
	//Extract hdr.int_val.next
	hdr.int_val[hdr.int_val_index].isValid = 1;
	hdr.int_val_index++;
	if ((hdr.int_val[hdr.int_val_index - 1].bos == 0)) {
		parse_int_val();
	} else if ((hdr.int_val[hdr.int_val_index - 1].bos == 1)) {
		parse_inner_ethernet();
	}
}

void parse_ipv4()
{
	//Extract hdr.ipv4
	hdr.ipv4.isValid = 1;
   // Specify ipv4+TCP
   hdr.ipv4.fragOffset = 0;
   hdr.ipv4.ihl = 5;
   hdr.ipv4.protocol = 6;
	if ((hdr.ipv4.fragOffset == 0) && (hdr.ipv4.ihl == 5)
	    && (hdr.ipv4.protocol == 1)) {
		parse_icmp();
	} else if ((hdr.ipv4.fragOffset == 0) && (hdr.ipv4.ihl == 5)
		   && (hdr.ipv4.protocol == 6)) {
		parse_tcp();
	} else if ((hdr.ipv4.fragOffset == 0) && (hdr.ipv4.ihl == 5)
		   && (hdr.ipv4.protocol == 17)) {
		parse_udp();
	} else if ((hdr.ipv4.fragOffset == 0) && (hdr.ipv4.ihl == 5)
		   && (hdr.ipv4.protocol == 47)) {
		parse_gre();
	} else if ((hdr.ipv4.fragOffset == 0) && (hdr.ipv4.ihl == 5)
		   && (hdr.ipv4.protocol == 4)) {
		parse_ipv4_in_ip();
	} else if ((hdr.ipv4.fragOffset == 0) && (hdr.ipv4.ihl == 5)
		   && (hdr.ipv4.protocol == 41)) {
		parse_ipv6_in_ip();
	} else if ((hdr.ipv4.fragOffset == 0) && (hdr.ipv4.ihl == 0)
		   && (hdr.ipv4.protocol == 2)) {
		parse_set_prio_med();
	} else if ((hdr.ipv4.fragOffset == 0) && (hdr.ipv4.ihl == 0)
		   && (hdr.ipv4.protocol == 88)) {
		parse_set_prio_med();
	} else if ((hdr.ipv4.fragOffset == 0) && (hdr.ipv4.ihl == 0)
		   && (hdr.ipv4.protocol == 89)) {
		parse_set_prio_med();
	} else if ((hdr.ipv4.fragOffset == 0) && (hdr.ipv4.ihl == 0)
		   && (hdr.ipv4.protocol == 103)) {
		parse_set_prio_med();
	} else if ((hdr.ipv4.fragOffset == 0) && (hdr.ipv4.ihl == 0)
		   && (hdr.ipv4.protocol == 112)) {
		parse_set_prio_med();
	} else {
		accept();
	}
}

void parse_ipv4_in_ip()
{
	meta.tunnel_metadata.ingress_tunnel_type = 3;
	parse_inner_ipv4();
}

void parse_ipv6()
{
	//Extract hdr.ipv6
	hdr.ipv6.isValid = 1;
	if ((hdr.ipv6.nextHdr == 58)) {
		parse_icmp();
	} else if ((hdr.ipv6.nextHdr == 6)) {
		parse_tcp();
	} else if ((hdr.ipv6.nextHdr == 4)) {
		parse_ipv4_in_ip();
	} else if ((hdr.ipv6.nextHdr == 17)) {
		parse_udp();
	} else if ((hdr.ipv6.nextHdr == 47)) {
		parse_gre();
	} else if ((hdr.ipv6.nextHdr == 41)) {
		parse_ipv6_in_ip();
	} else if ((hdr.ipv6.nextHdr == 88)) {
		parse_set_prio_med();
	} else if ((hdr.ipv6.nextHdr == 89)) {
		parse_set_prio_med();
	} else if ((hdr.ipv6.nextHdr == 103)) {
		parse_set_prio_med();
	} else if ((hdr.ipv6.nextHdr == 112)) {
		parse_set_prio_med();
	} else {
		accept();
	}
}

void parse_ipv6_in_ip()
{
	meta.tunnel_metadata.ingress_tunnel_type = 3;
	parse_inner_ipv6();
}

void parse_llc_header()
{
	//Extract hdr.llc_header
	hdr.llc_header.isValid = 1;
	if ((hdr.llc_header.dsap == 170) && (hdr.llc_header.ssap == 170)) {
		parse_snap_header();
	} else if ((hdr.llc_header.dsap == 254) && (hdr.llc_header.ssap == 254)) {
		parse_set_prio_med();
	} else {
		accept();
	}
}

void parse_mpls()
{
	//Extract hdr.mpls.next
	hdr.mpls[hdr.mpls_index].isValid = 1;
	hdr.mpls_index++;
	if ((hdr.mpls[hdr.mpls_index - 1].bos == 0)) {
		parse_mpls();
	} else if ((hdr.mpls[hdr.mpls_index - 1].bos == 1)) {
		parse_mpls_bos();
	} else {
		accept();
	}
}

void parse_mpls_bos()
{
	klee_make_symbolic(&tmp_0, sizeof(tmp_0), "tmp_0");

	if ((BITSLICE(tmp_0, 3, 0) == 4)) {
		parse_mpls_inner_ipv4();
	} else if ((BITSLICE(tmp_0, 3, 0) == 6)) {
		parse_mpls_inner_ipv6();
	} else {
		parse_eompls();
	}
}

void parse_mpls_inner_ipv4()
{
	meta.tunnel_metadata.ingress_tunnel_type = 9;
	parse_inner_ipv4();
}

void parse_mpls_inner_ipv6()
{
	meta.tunnel_metadata.ingress_tunnel_type = 9;
	parse_inner_ipv6();
}

void parse_nvgre()
{
	//Extract hdr.nvgre
	hdr.nvgre.isValid = 1;
	meta.tunnel_metadata.ingress_tunnel_type = 5;
	meta.tunnel_metadata.tunnel_vni = hdr.nvgre.tni;
	parse_inner_ethernet();
}

void parse_qinq()
{
	//Extract hdr.vlan_tag_[0]
	hdr.vlan_tag_[0].isValid = 1;
	if ((hdr.vlan_tag_[0].etherType == 33024)) {
		parse_qinq_vlan();
	} else {
		accept();
	}
}

void parse_qinq_vlan()
{
	//Extract hdr.vlan_tag_[1]
	hdr.vlan_tag_[1].isValid = 1;
	if ((hdr.vlan_tag_[1].etherType == 34887)) {
		parse_mpls();
	} else if ((hdr.vlan_tag_[1].etherType == 2048)) {
		parse_ipv4();
	} else if ((hdr.vlan_tag_[1].etherType == 34525)) {
		parse_ipv6();
	} else if ((hdr.vlan_tag_[1].etherType == 2054)) {
		parse_arp_rarp();
	} else if ((hdr.vlan_tag_[1].etherType == 35020)) {
		parse_set_prio_high();
	} else if ((hdr.vlan_tag_[1].etherType == 34825)) {
		parse_set_prio_high();
	} else {
		accept();
	}
}

void parse_set_prio_high()
{
	intrinsic_metadata.priority = 5;
	accept();
}

void parse_set_prio_med()
{
	intrinsic_metadata.priority = 3;
	accept();
}

void parse_sflow()
{
	//Extract hdr.sflow
	hdr.sflow.isValid = 1;
	accept();
}

void parse_snap_header()
{
	//Extract hdr.snap_header
	hdr.snap_header.isValid = 1;
	if ((hdr.snap_header.type_ == 33024)) {
		parse_vlan();
	} else if ((hdr.snap_header.type_ == 37120)) {
		parse_qinq();
	} else if ((hdr.snap_header.type_ == 34887)) {
		parse_mpls();
	} else if ((hdr.snap_header.type_ == 2048)) {
		parse_ipv4();
	} else if ((hdr.snap_header.type_ == 34525)) {
		parse_ipv6();
	} else if ((hdr.snap_header.type_ == 2054)) {
		parse_arp_rarp();
	} else if ((hdr.snap_header.type_ == 35020)) {
		parse_set_prio_high();
	} else if ((hdr.snap_header.type_ == 34825)) {
		parse_set_prio_high();
	} else {
		accept();
	}
}

void parse_tcp()
{
	//Extract hdr.tcp
	hdr.tcp.isValid = 1;
	meta.l3_metadata.lkp_outer_l4_sport = hdr.tcp.srcPort;
	meta.l3_metadata.lkp_outer_l4_dport = hdr.tcp.dstPort;
   /*
	if ((hdr.tcp.dstPort == 179)) {
		parse_set_prio_med();
	} else if ((hdr.tcp.dstPort == 639)) {
		parse_set_prio_med();
	} else {
		accept();
	}
   */
   // specify TCP packet
   accept();
}

void parse_udp()
{
	//Extract hdr.udp
	hdr.udp.isValid = 1;
	meta.l3_metadata.lkp_outer_l4_sport = hdr.udp.srcPort;
	meta.l3_metadata.lkp_outer_l4_dport = hdr.udp.dstPort;
	if ((hdr.udp.dstPort == 4789)) {
		parse_vxlan();
	} else if ((hdr.udp.dstPort == 6081)) {
		parse_geneve();
	} else if ((hdr.udp.dstPort == 4790)) {
		parse_vxlan_gpe();
	} else if ((hdr.udp.dstPort == 67)) {
		parse_set_prio_med();
	} else if ((hdr.udp.dstPort == 68)) {
		parse_set_prio_med();
	} else if ((hdr.udp.dstPort == 546)) {
		parse_set_prio_med();
	} else if ((hdr.udp.dstPort == 547)) {
		parse_set_prio_med();
	} else if ((hdr.udp.dstPort == 520)) {
		parse_set_prio_med();
	} else if ((hdr.udp.dstPort == 521)) {
		parse_set_prio_med();
	} else if ((hdr.udp.dstPort == 1985)) {
		parse_set_prio_med();
	} else if ((hdr.udp.dstPort == 6343)) {
		parse_sflow();
	} else {
		accept();
	}
}

void parse_vlan()
{
	//Extract hdr.vlan_tag_[0]
	hdr.vlan_tag_[0].isValid = 1;
	if ((hdr.vlan_tag_[0].etherType == 34887)) {
		parse_mpls();
	} else if ((hdr.vlan_tag_[0].etherType == 2048)) {
		parse_ipv4();
	} else if ((hdr.vlan_tag_[0].etherType == 34525)) {
		parse_ipv6();
	} else if ((hdr.vlan_tag_[0].etherType == 2054)) {
		parse_arp_rarp();
	} else if ((hdr.vlan_tag_[0].etherType == 35020)) {
		parse_set_prio_high();
	} else if ((hdr.vlan_tag_[0].etherType == 34825)) {
		parse_set_prio_high();
	} else {
		accept();
	}
}

void parse_vxlan()
{
	//Extract hdr.vxlan
	hdr.vxlan.isValid = 1;
	meta.tunnel_metadata.ingress_tunnel_type = 1;
	meta.tunnel_metadata.tunnel_vni = hdr.vxlan.vni;
	parse_inner_ethernet();
}

void parse_vxlan_gpe()
{
	//Extract hdr.vxlan_gpe
	hdr.vxlan_gpe.isValid = 1;
	meta.tunnel_metadata.ingress_tunnel_type = 12;
	meta.tunnel_metadata.tunnel_vni = hdr.vxlan_gpe.vni;
	if (((hdr.vxlan_gpe.flags & 8) == (8 & 8))
	    && ((hdr.vxlan_gpe.next_proto & 255) == (5 & 255))) {
		parse_gpe_int_header();
	} else {
		parse_inner_ethernet();
	}
}

void start()
{
	parse_ethernet();
}

void accept()
{

}

void reject()
{
	assert_forward = 0;
	end_assertions();
	exit(0);
}

void ParserImpl()
{
	klee_make_symbolic(&hdr, sizeof(hdr), "hdr");
	// klee_make_symbolic(&meta, sizeof(meta), "meta");
	klee_make_symbolic(&intrinsic_metadata, sizeof(intrinsic_metadata), "intrinsic_metadata");
	klee_make_symbolic(&standard_metadata, sizeof(standard_metadata),
			   "standard_metadata");

	start();
}

typedef struct {
	uint32_t field:16;
	uint32_t field_0:16;
	uint32_t field_1:16;
	uint32_t field_2:9;
} tuple_0;

typedef struct {
	uint32_t field_3:32;
	uint32_t field_4:16;
} tuple_1;

//Control

void egress()
{
	if ((intrinsic_metadata.deflection_flag == 0)
	    && (meta.egress_metadata.bypass == 0)) {
		if ((standard_metadata.instance_type != 0)
		    && (standard_metadata.instance_type != 5)) {
			_mirror_0_5653145();
		} else {
			if ((intrinsic_metadata.egress_rid != 0)) {
				_rid_0_5653462();
				_replica_type_0_5653393();

			}
		}
		egress_port_mapping_5652991();
		if (action_run == 5652891) {
			if ((standard_metadata.instance_type == 0)
			    || (standard_metadata.instance_type == 5)) {
				_vlan_decap_0_5653612();
			}
			if ((meta.tunnel_metadata.tunnel_terminate == 1)) {
				if ((meta.multicast_metadata.inner_replica == 1)
				    || (meta.multicast_metadata.replica == 0)) {
					_tunnel_decap_process_outer_0_5655461();
					_tunnel_decap_process_inner_0_5655361();

				}
			}
			if ((meta.egress_metadata.routed == 0)
			    || (meta.l3_metadata.nexthop_index != 0)) {
				_rewrite_0_5656181();
			} else {
				_rewrite_multicast_0_5714227();
			}
			_egress_bd_map_0_5714383();
			if (((meta.ingress_metadata.bypass_lookups & 8) == 0)) {
				_egress_qos_map_0_5714507();
			}
			if ((meta.egress_metadata.routed == 1)) {
				_l3_rewrite_0_5714815();
				_smac_rewrite_0_5714962();

			}
			_mtu_0_5715078();
			_int_insert_0_5717116();
			if (action_run == 5657323) {
				if ((meta.int_metadata.insert_cnt != 0)) {
					_int_inst_3_5717208();
					_int_inst_4_5717351();
					_int_inst_5_5717500();
					_int_inst_6_5717553();
					_int_bos_0_5716966();

				}
				_int_meta_header_update_0_5717606();

			}
			if ((meta.nat_metadata.ingress_nat_mode != 0)
			    && (meta.nat_metadata.ingress_nat_mode !=
				meta.nat_metadata.egress_nat_mode)) {
				_egress_nat_0_5718078();
			}
			_egress_bd_stats_2_5718217();

		}
		_egress_l4port_fields_0_5660452();
		_egress_l4_src_port_0_5718470();
		_egress_l4_dst_port_0_5718410();
		if ((meta.fabric_metadata.fabric_header_present == 0)
		    && (meta.tunnel_metadata.egress_tunnel_type != 0)) {
			_egress_vni_0_5721844();
			if ((meta.tunnel_metadata.egress_tunnel_type != 15)
			    && (meta.tunnel_metadata.egress_tunnel_type != 16)) {
				_tunnel_encap_process_inner_0_5663868();
			}
			_tunnel_encap_process_outer_0_5722200();
			_tunnel_rewrite_0_5722450();
			_tunnel_mtu_0_5722391();
			_tunnel_src_rewrite_0_5722604();
			_tunnel_dst_rewrite_0_5721975();
			_tunnel_smac_rewrite_0_5722545();
			_tunnel_dmac_rewrite_0_5721916();

		}
		if ((meta.egress_metadata.port_type == 0)) {
			if (hdr.ipv4.isValid) {
				_egress_ip_acl_0_5722787();
			} else {
				if (hdr.ipv6.isValid) {
					_egress_ipv6_acl_0_5722926();
				} else {
					_egress_mac_acl_0_5723063();
				}
			}
		}
		if ((meta.int_metadata.insert_cnt != 0)) {
			_int_outer_encap_0_5723311();
		}
		if ((meta.egress_metadata.port_type == 0)) {
			_egress_vlan_xlate_0_5723560();
		}
		_egress_filter_0_5665462();
		if ((meta.multicast_metadata.inner_replica == 1)) {
			if ((meta.tunnel_metadata.ingress_tunnel_type == 0)
			    && (meta.tunnel_metadata.egress_tunnel_type == 0)
			    && (meta.egress_filter_metadata.bd == 0)
			    && (meta.egress_filter_metadata.ifindex_check == 0)
			    || (meta.tunnel_metadata.ingress_tunnel_type != 0)
			    && (meta.tunnel_metadata.egress_tunnel_type != 0)
			    && (meta.egress_filter_metadata.inner_bd == 0)) {
				_egress_filter_drop_0_5665496();
			}
		}

	}
	if ((meta.egress_metadata.port_type == 0)) {
		if ((meta.egress_metadata.bypass == 0)) {
			_egress_system_acl_0_5724062();
		}
	}
}

// Action
void NoAction_0_5652839()
{
	action_run = 5652839;

}

// Action
void NoAction_1_5652849()
{
	action_run = 5652849;

}

// Action
void NoAction_131_5652850()
{
	action_run = 5652850;

}

// Action
void NoAction_132_5652851()
{
	action_run = 5652851;

}

// Action
void NoAction_133_5652852()
{
	action_run = 5652852;

}

// Action
void NoAction_134_5652853()
{
	action_run = 5652853;

}

// Action
void NoAction_135_5652854()
{
	action_run = 5652854;

}

// Action
void NoAction_136_5652855()
{
	action_run = 5652855;

}

// Action
void NoAction_137_5652856()
{
	action_run = 5652856;

}

// Action
void NoAction_138_5652857()
{
	action_run = 5652857;

}

// Action
void NoAction_139_5652858()
{
	action_run = 5652858;

}

// Action
void NoAction_140_5652859()
{
	action_run = 5652859;

}

// Action
void NoAction_141_5652860()
{
	action_run = 5652860;

}

// Action
void NoAction_142_5652861()
{
	action_run = 5652861;

}

// Action
void NoAction_143_5652862()
{
	action_run = 5652862;

}

// Action
void NoAction_144_5652863()
{
	action_run = 5652863;

}

// Action
void NoAction_145_5652864()
{
	action_run = 5652864;

}

// Action
void NoAction_146_5652865()
{
	action_run = 5652865;

}

// Action
void NoAction_147_5652866()
{
	action_run = 5652866;

}

// Action
void NoAction_148_5652867()
{
	action_run = 5652867;

}

// Action
void NoAction_149_5652868()
{
	action_run = 5652868;

}

// Action
void NoAction_150_5652869()
{
	action_run = 5652869;

}

// Action
void NoAction_151_5652870()
{
	action_run = 5652870;

}

// Action
void NoAction_152_5652871()
{
	action_run = 5652871;

}

// Action
void NoAction_153_5652872()
{
	action_run = 5652872;

}

// Action
void NoAction_154_5652873()
{
	action_run = 5652873;

}

// Action
void NoAction_155_5652874()
{
	action_run = 5652874;

}

// Action
void NoAction_156_5652875()
{
	action_run = 5652875;

}

// Action
void NoAction_157_5652876()
{
	action_run = 5652876;

}

// Action
void NoAction_158_5652877()
{
	action_run = 5652877;

}

// Action
void NoAction_159_5652878()
{
	action_run = 5652878;

}

// Action
void NoAction_160_5652879()
{
	action_run = 5652879;

}

// Action
void NoAction_161_5652880()
{
	action_run = 5652880;

}

// Action
void NoAction_162_5652881()
{
	action_run = 5652881;

}

// Action
void NoAction_163_5652882()
{
	action_run = 5652882;

}

// Action
void NoAction_164_5652883()
{
	action_run = 5652883;

}

// Action
void NoAction_165_5652884()
{
	action_run = 5652884;

}

// Action
void NoAction_166_5652885()
{
	action_run = 5652885;

}

// Action
void NoAction_167_5652886()
{
	action_run = 5652886;

}

// Action
void NoAction_168_5652887()
{
	action_run = 5652887;

}

// Action
void NoAction_169_5652888()
{
	action_run = 5652888;

}

// Action
void NoAction_170_5652889()
{
	action_run = 5652889;

}

// Action
void NoAction_171_5652890()
{
	action_run = 5652890;

}

// Action
void
egress_port_type_normal_0_5652891(uint32_t ifindex, uint8_t qos_group,
				  uint32_t if_label)
{
	action_run = 5652891;
	meta.egress_metadata.port_type = 0;
	meta.egress_metadata.ifindex = ifindex;
	meta.qos_metadata.egress_qos_group = qos_group;
	meta.acl_metadata.egress_if_label = if_label;

}

// Action
void egress_port_type_fabric_0_5652931(uint32_t ifindex)
{
	action_run = 5652931;
	meta.egress_metadata.port_type = 1;
	meta.egress_metadata.ifindex = ifindex;
	meta.tunnel_metadata.egress_tunnel_type = 15;

}

// Action
void egress_port_type_cpu_0_5652961(uint32_t ifindex)
{
	action_run = 5652961;
	meta.egress_metadata.port_type = 2;
	meta.egress_metadata.ifindex = ifindex;
	meta.tunnel_metadata.egress_tunnel_type = 16;

}

// Action
void _nop_8_5653055()
{
	action_run = 5653055;

}

// Action
void _set_mirror_nhop_5653065(uint32_t nhop_idx)
{
	action_run = 5653065;
	meta.l3_metadata.nexthop_index = nhop_idx;

}

// Action
void _set_mirror_bd_5653083(uint32_t bd)
{
	action_run = 5653083;
	meta.egress_metadata.bd = bd;

}

// Action
void _sflow_pkt_to_cpu_5653101(uint32_t reason_code)
{
	action_run = 5653101;
	hdr.fabric_header_sflow.isValid = 1;
	hdr.fabric_header_sflow.sflow_session_id =
	    meta.sflow_metadata.sflow_session_id;
	hdr.fabric_header_sflow.sflow_egress_ifindex =
	    meta.ingress_metadata.egress_ifindex;
	meta.fabric_metadata.reason_code = reason_code;

}

// Action
void _nop_9_5653216()
{
	action_run = 5653216;

}

// Action
void _nop_10_5653226()
{
	action_run = 5653226;

}

// Action
void _set_replica_copy_bridged_5653227()
{
	action_run = 5653227;
	meta.egress_metadata.routed = 0;

}

// Action
void
_outer_replica_from_rid_5653243(uint32_t bd, uint32_t tunnel_index,
				uint8_t tunnel_type, uint8_t header_count)
{
	action_run = 5653243;
	meta.egress_metadata.bd = bd;
	meta.multicast_metadata.replica = 1;
	meta.multicast_metadata.inner_replica = 0;
	meta.egress_metadata.routed = meta.l3_metadata.outer_routed;
	meta.egress_metadata.same_bd_check =
	    (bd ^ meta.ingress_metadata.outer_bd);
	meta.tunnel_metadata.tunnel_index = tunnel_index;
	meta.tunnel_metadata.egress_tunnel_type = tunnel_type;
	meta.tunnel_metadata.egress_header_count = header_count;

}

// Action
void
_inner_replica_from_rid_5653318(uint32_t bd, uint32_t tunnel_index,
				uint8_t tunnel_type, uint8_t header_count)
{
	action_run = 5653318;
	meta.egress_metadata.bd = bd;
	meta.multicast_metadata.replica = 1;
	meta.multicast_metadata.inner_replica = 1;
	meta.egress_metadata.routed = meta.l3_metadata.routed;
	meta.egress_metadata.same_bd_check = (bd ^ meta.ingress_metadata.bd);
	meta.tunnel_metadata.tunnel_index = tunnel_index;
	meta.tunnel_metadata.egress_tunnel_type = tunnel_type;
	meta.tunnel_metadata.egress_header_count = header_count;

}

// Action
void _nop_11_5653525()
{
	action_run = 5653525;

}

// Action
void _remove_vlan_single_tagged_5653535()
{
	action_run = 5653535;
	hdr.ethernet.etherType = hdr.vlan_tag_[0].etherType;
	hdr.vlan_tag_[0].isValid = 0;

}

// Action
void _remove_vlan_double_tagged_5653568()
{
	action_run = 5653568;
	hdr.ethernet.etherType = hdr.vlan_tag_[1].etherType;
	hdr.vlan_tag_[0].isValid = 0;
	hdr.vlan_tag_[1].isValid = 0;

}

// Action
void _decap_inner_udp_5653699()
{
	action_run = 5653699;
	hdr.udp = hdr.inner_udp;
	hdr.inner_udp.isValid = 0;

}

// Action
void _decap_inner_tcp_5653724()
{
	action_run = 5653724;
	hdr.tcp = hdr.inner_tcp;
	hdr.inner_tcp.isValid = 0;
	hdr.udp.isValid = 0;

}

// Action
void _decap_inner_icmp_5653757()
{
	action_run = 5653757;
	hdr.icmp = hdr.inner_icmp;
	hdr.inner_icmp.isValid = 0;
	hdr.udp.isValid = 0;

}

// Action
void _decap_inner_unknown_5653790()
{
	action_run = 5653790;
	hdr.udp.isValid = 0;

}

// Action
void _decap_vxlan_inner_ipv4_5653808()
{
	action_run = 5653808;
	hdr.ethernet = hdr.inner_ethernet;
	hdr.ipv4 = hdr.inner_ipv4;
	hdr.vxlan.isValid = 0;
	hdr.ipv6.isValid = 0;
	hdr.inner_ethernet.isValid = 0;
	hdr.inner_ipv4.isValid = 0;

}

// Action
void _decap_vxlan_inner_ipv6_5653864()
{
	action_run = 5653864;
	hdr.ethernet = hdr.inner_ethernet;
	hdr.ipv6 = hdr.inner_ipv6;
	hdr.vxlan.isValid = 0;
	hdr.ipv4.isValid = 0;
	hdr.inner_ethernet.isValid = 0;
	hdr.inner_ipv6.isValid = 0;

}

// Action
void _decap_vxlan_inner_non_ip_5653920()
{
	action_run = 5653920;
	hdr.ethernet = hdr.inner_ethernet;
	hdr.vxlan.isValid = 0;
	hdr.ipv4.isValid = 0;
	hdr.ipv6.isValid = 0;
	hdr.inner_ethernet.isValid = 0;

}

// Action
void _decap_genv_inner_ipv4_5653969()
{
	action_run = 5653969;
	hdr.ethernet = hdr.inner_ethernet;
	hdr.ipv4 = hdr.inner_ipv4;
	hdr.genv.isValid = 0;
	hdr.ipv6.isValid = 0;
	hdr.inner_ethernet.isValid = 0;
	hdr.inner_ipv4.isValid = 0;

}

// Action
void _decap_genv_inner_ipv6_5654025()
{
	action_run = 5654025;
	hdr.ethernet = hdr.inner_ethernet;
	hdr.ipv6 = hdr.inner_ipv6;
	hdr.genv.isValid = 0;
	hdr.ipv4.isValid = 0;
	hdr.inner_ethernet.isValid = 0;
	hdr.inner_ipv6.isValid = 0;

}

// Action
void _decap_genv_inner_non_ip_5654081()
{
	action_run = 5654081;
	hdr.ethernet = hdr.inner_ethernet;
	hdr.genv.isValid = 0;
	hdr.ipv4.isValid = 0;
	hdr.ipv6.isValid = 0;
	hdr.inner_ethernet.isValid = 0;

}

// Action
void _decap_nvgre_inner_ipv4_5654130()
{
	action_run = 5654130;
	hdr.ethernet = hdr.inner_ethernet;
	hdr.ipv4 = hdr.inner_ipv4;
	hdr.nvgre.isValid = 0;
	hdr.gre.isValid = 0;
	hdr.ipv6.isValid = 0;
	hdr.inner_ethernet.isValid = 0;
	hdr.inner_ipv4.isValid = 0;

}

// Action
void _decap_nvgre_inner_ipv6_5654194()
{
	action_run = 5654194;
	hdr.ethernet = hdr.inner_ethernet;
	hdr.ipv6 = hdr.inner_ipv6;
	hdr.nvgre.isValid = 0;
	hdr.gre.isValid = 0;
	hdr.ipv4.isValid = 0;
	hdr.inner_ethernet.isValid = 0;
	hdr.inner_ipv6.isValid = 0;

}

// Action
void _decap_nvgre_inner_non_ip_5654258()
{
	action_run = 5654258;
	hdr.ethernet = hdr.inner_ethernet;
	hdr.nvgre.isValid = 0;
	hdr.gre.isValid = 0;
	hdr.ipv4.isValid = 0;
	hdr.ipv6.isValid = 0;
	hdr.inner_ethernet.isValid = 0;

}

// Action
void _decap_gre_inner_ipv4_5654315()
{
	action_run = 5654315;
	hdr.ipv4 = hdr.inner_ipv4;
	hdr.gre.isValid = 0;
	hdr.ipv6.isValid = 0;
	hdr.inner_ipv4.isValid = 0;
	hdr.ethernet.etherType = 2048;

}

// Action
void _decap_gre_inner_ipv6_5654362()
{
	action_run = 5654362;
	hdr.ipv6 = hdr.inner_ipv6;
	hdr.gre.isValid = 0;
	hdr.ipv4.isValid = 0;
	hdr.inner_ipv6.isValid = 0;
	hdr.ethernet.etherType = 34525;

}

// Action
void _decap_gre_inner_non_ip_5654409()
{
	action_run = 5654409;
	hdr.ethernet.etherType = hdr.gre.proto;
	hdr.gre.isValid = 0;
	hdr.ipv4.isValid = 0;
	hdr.inner_ipv6.isValid = 0;

}

// Action
void _decap_ip_inner_ipv4_5654452()
{
	action_run = 5654452;
	hdr.ipv4 = hdr.inner_ipv4;
	hdr.ipv6.isValid = 0;
	hdr.inner_ipv4.isValid = 0;
	hdr.ethernet.etherType = 2048;

}

// Action
void _decap_ip_inner_ipv6_5654491()
{
	action_run = 5654491;
	hdr.ipv6 = hdr.inner_ipv6;
	hdr.ipv4.isValid = 0;
	hdr.inner_ipv6.isValid = 0;
	hdr.ethernet.etherType = 34525;

}

// Action
void _decap_mpls_inner_ipv4_pop1_5654530()
{
	action_run = 5654530;
	hdr.mpls[0].isValid = 0;
	hdr.ipv4 = hdr.inner_ipv4;
	hdr.inner_ipv4.isValid = 0;
	hdr.ethernet.etherType = 2048;

}

// Action
void _decap_mpls_inner_ipv6_pop1_5654572()
{
	action_run = 5654572;
	hdr.mpls[0].isValid = 0;
	hdr.ipv6 = hdr.inner_ipv6;
	hdr.inner_ipv6.isValid = 0;
	hdr.ethernet.etherType = 34525;

}

// Action
void _decap_mpls_inner_ethernet_ipv4_pop1_5654614()
{
	action_run = 5654614;
	hdr.mpls[0].isValid = 0;
	hdr.ethernet = hdr.inner_ethernet;
	hdr.ipv4 = hdr.inner_ipv4;
	hdr.inner_ethernet.isValid = 0;
	hdr.inner_ipv4.isValid = 0;

}

// Action
void _decap_mpls_inner_ethernet_ipv6_pop1_5654665()
{
	action_run = 5654665;
	hdr.mpls[0].isValid = 0;
	hdr.ethernet = hdr.inner_ethernet;
	hdr.ipv6 = hdr.inner_ipv6;
	hdr.inner_ethernet.isValid = 0;
	hdr.inner_ipv6.isValid = 0;

}

// Action
void _decap_mpls_inner_ethernet_non_ip_pop1_5654716()
{
	action_run = 5654716;
	hdr.mpls[0].isValid = 0;
	hdr.ethernet = hdr.inner_ethernet;
	hdr.inner_ethernet.isValid = 0;

}

// Action
void _decap_mpls_inner_ipv4_pop2_5654752()
{
	action_run = 5654752;
	hdr.mpls[0].isValid = 0;
	hdr.mpls[1].isValid = 0;
	hdr.ipv4 = hdr.inner_ipv4;
	hdr.inner_ipv4.isValid = 0;
	hdr.ethernet.etherType = 2048;

}

// Action
void _decap_mpls_inner_ipv6_pop2_5654805()
{
	action_run = 5654805;
	hdr.mpls[0].isValid = 0;
	hdr.mpls[1].isValid = 0;
	hdr.ipv6 = hdr.inner_ipv6;
	hdr.inner_ipv6.isValid = 0;
	hdr.ethernet.etherType = 34525;

}

// Action
void _decap_mpls_inner_ethernet_ipv4_pop2_5654858()
{
	action_run = 5654858;
	hdr.mpls[0].isValid = 0;
	hdr.mpls[1].isValid = 0;
	hdr.ethernet = hdr.inner_ethernet;
	hdr.ipv4 = hdr.inner_ipv4;
	hdr.inner_ethernet.isValid = 0;
	hdr.inner_ipv4.isValid = 0;

}

// Action
void _decap_mpls_inner_ethernet_ipv6_pop2_5654920()
{
	action_run = 5654920;
	hdr.mpls[0].isValid = 0;
	hdr.mpls[1].isValid = 0;
	hdr.ethernet = hdr.inner_ethernet;
	hdr.ipv6 = hdr.inner_ipv6;
	hdr.inner_ethernet.isValid = 0;
	hdr.inner_ipv6.isValid = 0;

}

// Action
void _decap_mpls_inner_ethernet_non_ip_pop2_5654982()
{
	action_run = 5654982;
	hdr.mpls[0].isValid = 0;
	hdr.mpls[1].isValid = 0;
	hdr.ethernet = hdr.inner_ethernet;
	hdr.inner_ethernet.isValid = 0;

}

// Action
void _decap_mpls_inner_ipv4_pop3_5655029()
{
	action_run = 5655029;
	hdr.mpls[0].isValid = 0;
	hdr.mpls[1].isValid = 0;
	hdr.mpls[2].isValid = 0;
	hdr.ipv4 = hdr.inner_ipv4;
	hdr.inner_ipv4.isValid = 0;
	hdr.ethernet.etherType = 2048;

}

// Action
void _decap_mpls_inner_ipv6_pop3_5655093()
{
	action_run = 5655093;
	hdr.mpls[0].isValid = 0;
	hdr.mpls[1].isValid = 0;
	hdr.mpls[2].isValid = 0;
	hdr.ipv6 = hdr.inner_ipv6;
	hdr.inner_ipv6.isValid = 0;
	hdr.ethernet.etherType = 34525;

}

// Action
void _decap_mpls_inner_ethernet_ipv4_pop3_5655157()
{
	action_run = 5655157;
	hdr.mpls[0].isValid = 0;
	hdr.mpls[1].isValid = 0;
	hdr.mpls[2].isValid = 0;
	hdr.ethernet = hdr.inner_ethernet;
	hdr.ipv4 = hdr.inner_ipv4;
	hdr.inner_ethernet.isValid = 0;
	hdr.inner_ipv4.isValid = 0;

}

// Action
void _decap_mpls_inner_ethernet_ipv6_pop3_5655230()
{
	action_run = 5655230;
	hdr.mpls[0].isValid = 0;
	hdr.mpls[1].isValid = 0;
	hdr.mpls[2].isValid = 0;
	hdr.ethernet = hdr.inner_ethernet;
	hdr.ipv6 = hdr.inner_ipv6;
	hdr.inner_ethernet.isValid = 0;
	hdr.inner_ipv6.isValid = 0;

}

// Action
void _decap_mpls_inner_ethernet_non_ip_pop3_5655303()
{
	action_run = 5655303;
	hdr.mpls[0].isValid = 0;
	hdr.mpls[1].isValid = 0;
	hdr.mpls[2].isValid = 0;
	hdr.ethernet = hdr.inner_ethernet;
	hdr.inner_ethernet.isValid = 0;

}

// Action
void _nop_12_5655708()
{
	action_run = 5655708;

}

// Action
void _nop_13_5655718()
{
	action_run = 5655718;

}

// Action
void _set_l2_rewrite_5655719()
{
	action_run = 5655719;
	meta.egress_metadata.routed = 0;
	meta.egress_metadata.bd = meta.ingress_metadata.bd;
	meta.egress_metadata.outer_bd = meta.ingress_metadata.bd;

}

// Action
void
_set_l2_rewrite_with_tunnel_5655753(uint32_t tunnel_index, uint8_t tunnel_type)
{
	action_run = 5655753;
	meta.egress_metadata.routed = 0;
	meta.egress_metadata.bd = meta.ingress_metadata.bd;
	meta.egress_metadata.outer_bd = meta.ingress_metadata.bd;
	meta.tunnel_metadata.tunnel_index = tunnel_index;
	meta.tunnel_metadata.egress_tunnel_type = tunnel_type;

}

// Action
void _set_l3_rewrite_5655803(uint32_t bd, uint8_t mtu_index, uint64_t dmac)
{
	action_run = 5655803;
	meta.egress_metadata.routed = 1;
	meta.egress_metadata.mac_da = dmac;
	meta.egress_metadata.bd = bd;
	meta.egress_metadata.outer_bd = bd;
	meta.l3_metadata.mtu_index = mtu_index;

}

// Action
void
_set_l3_rewrite_with_tunnel_5655850(uint32_t bd, uint64_t dmac,
				    uint32_t tunnel_index, uint8_t tunnel_type)
{
	action_run = 5655850;
	meta.egress_metadata.routed = 1;
	meta.egress_metadata.mac_da = dmac;
	meta.egress_metadata.bd = bd;
	meta.egress_metadata.outer_bd = bd;
	meta.tunnel_metadata.tunnel_index = tunnel_index;
	meta.tunnel_metadata.egress_tunnel_type = tunnel_type;

}

// Action
void
_set_mpls_swap_push_rewrite_l2_5655905(uint32_t label, uint32_t tunnel_index,
				       uint8_t header_count)
{
	action_run = 5655905;
	meta.egress_metadata.routed = meta.l3_metadata.routed;
	meta.egress_metadata.bd = meta.ingress_metadata.bd;
	hdr.mpls[0].label = label;
	meta.tunnel_metadata.tunnel_index = tunnel_index;
	meta.tunnel_metadata.egress_header_count = header_count;
	meta.tunnel_metadata.egress_tunnel_type = 13;

}

// Action
void
_set_mpls_push_rewrite_l2_5655966(uint32_t tunnel_index, uint8_t header_count)
{
	action_run = 5655966;
	meta.egress_metadata.routed = meta.l3_metadata.routed;
	meta.egress_metadata.bd = meta.ingress_metadata.bd;
	meta.tunnel_metadata.tunnel_index = tunnel_index;
	meta.tunnel_metadata.egress_header_count = header_count;
	meta.tunnel_metadata.egress_tunnel_type = 13;

}

// Action
void
_set_mpls_swap_push_rewrite_l3_5656016(uint32_t bd, uint64_t dmac,
				       uint32_t label, uint32_t tunnel_index,
				       uint8_t header_count)
{
	action_run = 5656016;
	meta.egress_metadata.routed = meta.l3_metadata.routed;
	meta.egress_metadata.bd = bd;
	hdr.mpls[0].label = label;
	meta.egress_metadata.mac_da = dmac;
	meta.tunnel_metadata.tunnel_index = tunnel_index;
	meta.tunnel_metadata.egress_header_count = header_count;
	meta.tunnel_metadata.egress_tunnel_type = 14;

}

// Action
void
_set_mpls_push_rewrite_l3_5656084(uint32_t bd, uint64_t dmac,
				  uint32_t tunnel_index, uint8_t header_count)
{
	action_run = 5656084;
	meta.egress_metadata.routed = meta.l3_metadata.routed;
	meta.egress_metadata.bd = bd;
	meta.egress_metadata.mac_da = dmac;
	meta.tunnel_metadata.tunnel_index = tunnel_index;
	meta.tunnel_metadata.egress_header_count = header_count;
	meta.tunnel_metadata.egress_tunnel_type = 14;

}

// Action
void _rewrite_ipv4_multicast_6057736()
{
	action_run = 6057736;
	hdr.ethernet.dstAddr =
	    ((hdr.
	      ethernet.dstAddr & ~8388607) | ((uint64_t) BITSLICE((uint64_t)
								  hdr.ipv4.
								  dstAddr, 22,
								  0) << 0 &
					      8388607));

}

// Action
void _rewrite_ipv6_multicast_5656171()
{
	action_run = 5656171;

}

// Action
void _nop_14_5656379()
{
	action_run = 5656379;

}

// Action
void
_set_egress_bd_properties_5656389(uint32_t smac_idx, uint8_t nat_mode,
				  uint32_t bd_label)
{
	action_run = 5656389;
	meta.egress_metadata.smac_idx = smac_idx;
	meta.nat_metadata.egress_nat_mode = nat_mode;
	meta.acl_metadata.egress_bd_label = bd_label;

}

// Action
void _nop_15_5656480()
{
	action_run = 5656480;

}

// Action
void _set_mpls_exp_marking_5656490(uint8_t exp)
{
	action_run = 5656490;
	meta.l3_metadata.lkp_dscp = exp;

}

// Action
void _set_ip_dscp_marking_5656508(uint8_t dscp)
{
	action_run = 5656508;
	meta.l3_metadata.lkp_dscp = dscp;

}

// Action
void _set_vlan_pcp_marking_5656526(uint8_t pcp)
{
	action_run = 5656526;
	meta.l2_metadata.lkp_pcp = pcp;

}

// Action
void _nop_16_5656623()
{
	action_run = 5656623;

}

// Action
void _ipv4_unicast_rewrite_5656633()
{
	action_run = 5656633;
	hdr.ethernet.dstAddr = meta.egress_metadata.mac_da;
	hdr.ipv4.ttl = hdr.ipv4.ttl + 255;
	hdr.ipv4.diffserv = meta.l3_metadata.lkp_dscp;

}

// Action
void _ipv4_multicast_rewrite_5656672()
{
	action_run = 5656672;
	hdr.ethernet.dstAddr = (hdr.ethernet.dstAddr | 1101088686080);
	hdr.ipv4.ttl = hdr.ipv4.ttl + 255;
	hdr.ipv4.diffserv = meta.l3_metadata.lkp_dscp;

}

// Action
void _ipv6_unicast_rewrite_5656713()
{
	action_run = 5656713;
	hdr.ethernet.dstAddr = meta.egress_metadata.mac_da;
	hdr.ipv6.hopLimit = hdr.ipv6.hopLimit + 255;
	hdr.ipv6.trafficClass = meta.l3_metadata.lkp_dscp;

}

// Action
void _ipv6_multicast_rewrite_5656752()
{
	action_run = 5656752;
	hdr.ethernet.dstAddr = (hdr.ethernet.dstAddr | 56294136348672);
	hdr.ipv6.hopLimit = hdr.ipv6.hopLimit + 255;
	hdr.ipv6.trafficClass = meta.l3_metadata.lkp_dscp;

}

// Action
void _mpls_rewrite_5656793()
{
	action_run = 5656793;
	hdr.ethernet.dstAddr = meta.egress_metadata.mac_da;
	hdr.mpls[0].ttl = hdr.mpls[0].ttl + 255;

}

// Action
void _rewrite_smac_5656829(uint64_t smac)
{
	action_run = 5656829;
	hdr.ethernet.srcAddr = smac;

}

// Action
void _mtu_miss_5657029()
{
	action_run = 5657029;
	meta.l3_metadata.l3_mtu_check = 65535;

}

// Action
void _ipv4_mtu_check_5657045(uint32_t l3_mtu)
{
	action_run = 5657045;
	meta.l3_metadata.l3_mtu_check = l3_mtu - hdr.ipv4.totalLen;

}

// Action
void _ipv6_mtu_check_5657068(uint32_t l3_mtu)
{
	action_run = 5657068;
	meta.l3_metadata.l3_mtu_check = l3_mtu - hdr.ipv6.payloadLen;

}

// Action
void _int_set_header_0_bos_5657182()
{
	action_run = 5657182;
	hdr.int_switch_id_header.bos = 1;

}

// Action
void _int_set_header_1_bos_5657198()
{
	action_run = 5657198;
	hdr.int_ingress_port_id_header.bos = 1;

}

// Action
void _int_set_header_2_bos_5657214()
{
	action_run = 5657214;
	hdr.int_hop_latency_header.bos = 1;

}

// Action
void _int_set_header_3_bos_5657230()
{
	action_run = 5657230;
	hdr.int_q_occupancy_header.bos = 1;

}

// Action
void _int_set_header_4_bos_5657246()
{
	action_run = 5657246;
	hdr.int_ingress_tstamp_header.bos = 1;

}

// Action
void _int_set_header_5_bos_5657262()
{
	action_run = 5657262;
	hdr.int_egress_port_id_header.bos = 1;

}

// Action
void _int_set_header_6_bos_5657278()
{
	action_run = 5657278;
	hdr.int_q_congestion_header.bos = 1;

}

// Action
void _int_set_header_7_bos_5657294()
{
	action_run = 5657294;
	hdr.int_egress_port_tx_utilization_header.bos = 1;

}

// Action
void _nop_17_5657310()
{
	action_run = 5657310;

}

// Action
void _nop_18_5657320()
{
	action_run = 5657320;

}

// Action
void _nop_19_5657321()
{
	action_run = 5657321;

}

// Action
void _nop_20_5657322()
{
	action_run = 5657322;

}

// Action
void _int_transit_5657323(uint32_t switch_id)
{
	action_run = 5657323;
	meta.int_metadata.insert_cnt =
	    hdr.int_header.max_hop_cnt - hdr.int_header.total_hop_cnt;
	meta.int_metadata.switch_id = switch_id;
	meta.int_metadata.insert_byte_cnt =
	    meta.int_metadata.instruction_cnt << 2;
	meta.int_metadata.gpe_int_hdr_len8 = (uint8_t) hdr.int_header.ins_cnt;

}

// Action
void
_int_src_5657377(uint32_t switch_id, uint8_t hop_cnt, uint8_t ins_cnt,
		 uint8_t ins_mask0003, uint8_t ins_mask0407,
		 uint32_t ins_byte_cnt, uint8_t total_words)
{
	action_run = 5657377;
	meta.int_metadata.insert_cnt = hop_cnt;
	meta.int_metadata.switch_id = switch_id;
	meta.int_metadata.insert_byte_cnt = ins_byte_cnt;
	meta.int_metadata.gpe_int_hdr_len8 = total_words;
	hdr.int_header.isValid = 1;
	hdr.int_header.ver = 0;
	hdr.int_header.rep = 0;
	hdr.int_header.c = 0;
	hdr.int_header.e = 0;
	hdr.int_header.rsvd1 = 0;
	hdr.int_header.ins_cnt = ins_cnt;
	hdr.int_header.max_hop_cnt = hop_cnt;
	hdr.int_header.total_hop_cnt = 0;
	hdr.int_header.instruction_mask_0003 = ins_mask0003;
	hdr.int_header.instruction_mask_0407 = ins_mask0407;
	hdr.int_header.instruction_mask_0811 = 0;
	hdr.int_header.instruction_mask_1215 = 0;
	hdr.int_header.rsvd2 = 0;

}

// Action
void _int_reset_5657512()
{
	action_run = 5657512;
	meta.int_metadata.switch_id = 0;
	meta.int_metadata.insert_byte_cnt = 0;
	meta.int_metadata.insert_cnt = 0;
	meta.int_metadata.gpe_int_hdr_len8 = 0;
	meta.int_metadata.gpe_int_hdr_len = 0;
	meta.int_metadata.instruction_cnt = 0;

}

// Action
void _int_set_header_0003_i0_5657558()
{
	action_run = 5657558;

}

// Action
void _int_set_header_0003_i1_5657568()
{
	action_run = 5657568;
	hdr.int_q_occupancy_header.isValid = 1;
	hdr.int_q_occupancy_header.q_occupancy1 = 0;
	hdr.int_q_occupancy_header.q_occupancy0 =
	    (uint32_t) meta.queueing_metadata.enq_qdepth;

}

// Action
void _int_set_header_0003_i2_5657602()
{
	action_run = 5657602;
	hdr.int_hop_latency_header.isValid = 1;
	hdr.int_hop_latency_header.hop_latency =
	    (uint32_t) meta.queueing_metadata.deq_timedelta;

}

// Action
void _int_set_header_0003_i3_5657630()
{
	action_run = 5657630;
	hdr.int_q_occupancy_header.isValid = 1;
	hdr.int_q_occupancy_header.q_occupancy1 = 0;
	hdr.int_q_occupancy_header.q_occupancy0 =
	    (uint32_t) meta.queueing_metadata.enq_qdepth;
	hdr.int_hop_latency_header.isValid = 1;
	hdr.int_hop_latency_header.hop_latency =
	    (uint32_t) meta.queueing_metadata.deq_timedelta;

}

// Action
void _int_set_header_0003_i4_5657677()
{
	action_run = 5657677;
	hdr.int_ingress_port_id_header.isValid = 1;
	hdr.int_ingress_port_id_header.ingress_port_id_1 = 0;
	hdr.int_ingress_port_id_header.ingress_port_id_0 =
	    meta.ingress_metadata.ifindex;

}

// Action
void _int_set_header_0003_i5_5657710()
{
	action_run = 5657710;
	hdr.int_q_occupancy_header.isValid = 1;
	hdr.int_q_occupancy_header.q_occupancy1 = 0;
	hdr.int_q_occupancy_header.q_occupancy0 =
	    (uint32_t) meta.queueing_metadata.enq_qdepth;
	hdr.int_ingress_port_id_header.isValid = 1;
	hdr.int_ingress_port_id_header.ingress_port_id_1 = 0;
	hdr.int_ingress_port_id_header.ingress_port_id_0 =
	    meta.ingress_metadata.ifindex;

}

// Action
void _int_set_header_0003_i6_5657761()
{
	action_run = 5657761;
	hdr.int_hop_latency_header.isValid = 1;
	hdr.int_hop_latency_header.hop_latency =
	    (uint32_t) meta.queueing_metadata.deq_timedelta;
	hdr.int_ingress_port_id_header.isValid = 1;
	hdr.int_ingress_port_id_header.ingress_port_id_1 = 0;
	hdr.int_ingress_port_id_header.ingress_port_id_0 =
	    meta.ingress_metadata.ifindex;

}

// Action
void _int_set_header_0003_i7_5657807()
{
	action_run = 5657807;
	hdr.int_q_occupancy_header.isValid = 1;
	hdr.int_q_occupancy_header.q_occupancy1 = 0;
	hdr.int_q_occupancy_header.q_occupancy0 =
	    (uint32_t) meta.queueing_metadata.enq_qdepth;
	hdr.int_hop_latency_header.isValid = 1;
	hdr.int_hop_latency_header.hop_latency =
	    (uint32_t) meta.queueing_metadata.deq_timedelta;
	hdr.int_ingress_port_id_header.isValid = 1;
	hdr.int_ingress_port_id_header.ingress_port_id_1 = 0;
	hdr.int_ingress_port_id_header.ingress_port_id_0 =
	    meta.ingress_metadata.ifindex;

}

// Action
void _int_set_header_0003_i8_5657874()
{
	action_run = 5657874;
	hdr.int_switch_id_header.isValid = 1;
	hdr.int_switch_id_header.switch_id =
	    (uint32_t) meta.int_metadata.switch_id;

}

// Action
void _int_set_header_0003_i9_5657902()
{
	action_run = 5657902;
	hdr.int_q_occupancy_header.isValid = 1;
	hdr.int_q_occupancy_header.q_occupancy1 = 0;
	hdr.int_q_occupancy_header.q_occupancy0 =
	    (uint32_t) meta.queueing_metadata.enq_qdepth;
	hdr.int_switch_id_header.isValid = 1;
	hdr.int_switch_id_header.switch_id =
	    (uint32_t) meta.int_metadata.switch_id;

}

// Action
void _int_set_header_0003_i10_5657949()
{
	action_run = 5657949;
	hdr.int_hop_latency_header.isValid = 1;
	hdr.int_hop_latency_header.hop_latency =
	    (uint32_t) meta.queueing_metadata.deq_timedelta;
	hdr.int_switch_id_header.isValid = 1;
	hdr.int_switch_id_header.switch_id =
	    (uint32_t) meta.int_metadata.switch_id;

}

// Action
void _int_set_header_0003_i11_5657991()
{
	action_run = 5657991;
	hdr.int_q_occupancy_header.isValid = 1;
	hdr.int_q_occupancy_header.q_occupancy1 = 0;
	hdr.int_q_occupancy_header.q_occupancy0 =
	    (uint32_t) meta.queueing_metadata.enq_qdepth;
	hdr.int_hop_latency_header.isValid = 1;
	hdr.int_hop_latency_header.hop_latency =
	    (uint32_t) meta.queueing_metadata.deq_timedelta;
	hdr.int_switch_id_header.isValid = 1;
	hdr.int_switch_id_header.switch_id =
	    (uint32_t) meta.int_metadata.switch_id;

}

// Action
void _int_set_header_0003_i12_5658054()
{
	action_run = 5658054;
	hdr.int_ingress_port_id_header.isValid = 1;
	hdr.int_ingress_port_id_header.ingress_port_id_1 = 0;
	hdr.int_ingress_port_id_header.ingress_port_id_0 =
	    meta.ingress_metadata.ifindex;
	hdr.int_switch_id_header.isValid = 1;
	hdr.int_switch_id_header.switch_id =
	    (uint32_t) meta.int_metadata.switch_id;

}

// Action
void _int_set_header_0003_i13_5658100()
{
	action_run = 5658100;
	hdr.int_q_occupancy_header.isValid = 1;
	hdr.int_q_occupancy_header.q_occupancy1 = 0;
	hdr.int_q_occupancy_header.q_occupancy0 =
	    (uint32_t) meta.queueing_metadata.enq_qdepth;
	hdr.int_ingress_port_id_header.isValid = 1;
	hdr.int_ingress_port_id_header.ingress_port_id_1 = 0;
	hdr.int_ingress_port_id_header.ingress_port_id_0 =
	    meta.ingress_metadata.ifindex;
	hdr.int_switch_id_header.isValid = 1;
	hdr.int_switch_id_header.switch_id =
	    (uint32_t) meta.int_metadata.switch_id;

}

// Action
void _int_set_header_0003_i14_5658167()
{
	action_run = 5658167;
	hdr.int_hop_latency_header.isValid = 1;
	hdr.int_hop_latency_header.hop_latency =
	    (uint32_t) meta.queueing_metadata.deq_timedelta;
	hdr.int_ingress_port_id_header.isValid = 1;
	hdr.int_ingress_port_id_header.ingress_port_id_1 = 0;
	hdr.int_ingress_port_id_header.ingress_port_id_0 =
	    meta.ingress_metadata.ifindex;
	hdr.int_switch_id_header.isValid = 1;
	hdr.int_switch_id_header.switch_id =
	    (uint32_t) meta.int_metadata.switch_id;

}

// Action
void _int_set_header_0003_i15_5658229()
{
	action_run = 5658229;
	hdr.int_q_occupancy_header.isValid = 1;
	hdr.int_q_occupancy_header.q_occupancy1 = 0;
	hdr.int_q_occupancy_header.q_occupancy0 =
	    (uint32_t) meta.queueing_metadata.enq_qdepth;
	hdr.int_hop_latency_header.isValid = 1;
	hdr.int_hop_latency_header.hop_latency =
	    (uint32_t) meta.queueing_metadata.deq_timedelta;
	hdr.int_ingress_port_id_header.isValid = 1;
	hdr.int_ingress_port_id_header.ingress_port_id_1 = 0;
	hdr.int_ingress_port_id_header.ingress_port_id_0 =
	    meta.ingress_metadata.ifindex;
	hdr.int_switch_id_header.isValid = 1;
	hdr.int_switch_id_header.switch_id =
	    (uint32_t) meta.int_metadata.switch_id;

}

// Action
void _int_set_header_0407_i0_5658312()
{
	action_run = 5658312;

}

// Action
void _int_set_header_0407_i1_5658322()
{
	action_run = 5658322;
	hdr.int_egress_port_tx_utilization_header.isValid = 1;
	hdr.int_egress_port_tx_utilization_header.egress_port_tx_utilization =
	    2147483647;

}

// Action
void _int_set_header_0407_i2_5658346()
{
	action_run = 5658346;
	hdr.int_q_congestion_header.isValid = 1;
	hdr.int_q_congestion_header.q_congestion = 2147483647;

}

// Action
void _int_set_header_0407_i3_5658370()
{
	action_run = 5658370;
	hdr.int_egress_port_tx_utilization_header.isValid = 1;
	hdr.int_egress_port_tx_utilization_header.egress_port_tx_utilization =
	    2147483647;
	hdr.int_q_congestion_header.isValid = 1;
	hdr.int_q_congestion_header.q_congestion = 2147483647;

}

// Action
void _int_set_header_0407_i4_5658402()
{
	action_run = 5658402;
	hdr.int_egress_port_id_header.isValid = 1;
	hdr.int_egress_port_id_header.egress_port_id =
	    (uint32_t) standard_metadata.egress_port;

}

// Action
void _int_set_header_0407_i5_5658429()
{
	action_run = 5658429;
	hdr.int_egress_port_tx_utilization_header.isValid = 1;
	hdr.int_egress_port_tx_utilization_header.egress_port_tx_utilization =
	    2147483647;
	hdr.int_egress_port_id_header.isValid = 1;
	hdr.int_egress_port_id_header.egress_port_id =
	    (uint32_t) standard_metadata.egress_port;

}

// Action
void _int_set_header_0407_i6_5658465()
{
	action_run = 5658465;
	hdr.int_q_congestion_header.isValid = 1;
	hdr.int_q_congestion_header.q_congestion = 2147483647;
	hdr.int_egress_port_id_header.isValid = 1;
	hdr.int_egress_port_id_header.egress_port_id =
	    (uint32_t) standard_metadata.egress_port;

}

// Action
void _int_set_header_0407_i7_5658501()
{
	action_run = 5658501;
	hdr.int_egress_port_tx_utilization_header.isValid = 1;
	hdr.int_egress_port_tx_utilization_header.egress_port_tx_utilization =
	    2147483647;
	hdr.int_q_congestion_header.isValid = 1;
	hdr.int_q_congestion_header.q_congestion = 2147483647;
	hdr.int_egress_port_id_header.isValid = 1;
	hdr.int_egress_port_id_header.egress_port_id =
	    (uint32_t) standard_metadata.egress_port;

}

// Action
void _int_set_header_0407_i8_5658548()
{
	action_run = 5658548;
	hdr.int_ingress_tstamp_header.isValid = 1;
	hdr.int_ingress_tstamp_header.ingress_tstamp =
	    (uint32_t) meta.i2e_metadata.ingress_tstamp;

}

// Action
void _int_set_header_0407_i9_5658576()
{
	action_run = 5658576;
	hdr.int_egress_port_tx_utilization_header.isValid = 1;
	hdr.int_egress_port_tx_utilization_header.egress_port_tx_utilization =
	    2147483647;
	hdr.int_ingress_tstamp_header.isValid = 1;
	hdr.int_ingress_tstamp_header.ingress_tstamp =
	    (uint32_t) meta.i2e_metadata.ingress_tstamp;

}

// Action
void _int_set_header_0407_i10_5658613()
{
	action_run = 5658613;
	hdr.int_q_congestion_header.isValid = 1;
	hdr.int_q_congestion_header.q_congestion = 2147483647;
	hdr.int_ingress_tstamp_header.isValid = 1;
	hdr.int_ingress_tstamp_header.ingress_tstamp =
	    (uint32_t) meta.i2e_metadata.ingress_tstamp;

}

// Action
void _int_set_header_0407_i11_5658650()
{
	action_run = 5658650;
	hdr.int_egress_port_tx_utilization_header.isValid = 1;
	hdr.int_egress_port_tx_utilization_header.egress_port_tx_utilization =
	    2147483647;
	hdr.int_q_congestion_header.isValid = 1;
	hdr.int_q_congestion_header.q_congestion = 2147483647;
	hdr.int_ingress_tstamp_header.isValid = 1;
	hdr.int_ingress_tstamp_header.ingress_tstamp =
	    (uint32_t) meta.i2e_metadata.ingress_tstamp;

}

// Action
void _int_set_header_0407_i12_5658698()
{
	action_run = 5658698;
	hdr.int_egress_port_id_header.isValid = 1;
	hdr.int_egress_port_id_header.egress_port_id =
	    (uint32_t) standard_metadata.egress_port;
	hdr.int_ingress_tstamp_header.isValid = 1;
	hdr.int_ingress_tstamp_header.ingress_tstamp =
	    (uint32_t) meta.i2e_metadata.ingress_tstamp;

}

// Action
void _int_set_header_0407_i13_5658739()
{
	action_run = 5658739;
	hdr.int_egress_port_tx_utilization_header.isValid = 1;
	hdr.int_egress_port_tx_utilization_header.egress_port_tx_utilization =
	    2147483647;
	hdr.int_egress_port_id_header.isValid = 1;
	hdr.int_egress_port_id_header.egress_port_id =
	    (uint32_t) standard_metadata.egress_port;
	hdr.int_ingress_tstamp_header.isValid = 1;
	hdr.int_ingress_tstamp_header.ingress_tstamp =
	    (uint32_t) meta.i2e_metadata.ingress_tstamp;

}

// Action
void _int_set_header_0407_i14_5658791()
{
	action_run = 5658791;
	hdr.int_q_congestion_header.isValid = 1;
	hdr.int_q_congestion_header.q_congestion = 2147483647;
	hdr.int_egress_port_id_header.isValid = 1;
	hdr.int_egress_port_id_header.egress_port_id =
	    (uint32_t) standard_metadata.egress_port;
	hdr.int_ingress_tstamp_header.isValid = 1;
	hdr.int_ingress_tstamp_header.ingress_tstamp =
	    (uint32_t) meta.i2e_metadata.ingress_tstamp;

}

// Action
void _int_set_header_0407_i15_5658843()
{
	action_run = 5658843;
	hdr.int_egress_port_tx_utilization_header.isValid = 1;
	hdr.int_egress_port_tx_utilization_header.egress_port_tx_utilization =
	    2147483647;
	hdr.int_q_congestion_header.isValid = 1;
	hdr.int_q_congestion_header.q_congestion = 2147483647;
	hdr.int_egress_port_id_header.isValid = 1;
	hdr.int_egress_port_id_header.egress_port_id =
	    (uint32_t) standard_metadata.egress_port;
	hdr.int_ingress_tstamp_header.isValid = 1;
	hdr.int_ingress_tstamp_header.ingress_tstamp =
	    (uint32_t) meta.i2e_metadata.ingress_tstamp;

}

// Action
void _int_set_e_bit_5658906()
{
	action_run = 5658906;
	hdr.int_header.e = 1;

}

// Action
void _int_update_total_hop_cnt_5658922()
{
	action_run = 5658922;
	hdr.int_header.total_hop_cnt = hdr.int_header.total_hop_cnt + 1;

}

// Action
void _nop_21_5659617()
{
	action_run = 5659617;

}

// Action
void _set_nat_src_rewrite_5659627(uint32_t src_ip)
{
	action_run = 5659627;
	hdr.ipv4.srcAddr = src_ip;
	meta.nat_metadata.update_checksum = 1;
	meta.nat_metadata.l4_len = hdr.ipv4.totalLen + 65516;

}

// Action
void _set_nat_dst_rewrite_5659662(uint32_t dst_ip)
{
	action_run = 5659662;
	hdr.ipv4.dstAddr = dst_ip;
	meta.nat_metadata.update_checksum = 1;
	meta.nat_metadata.l4_len = hdr.ipv4.totalLen + 65516;

}

// Action
void _set_nat_src_dst_rewrite_5659695(uint32_t src_ip, uint32_t dst_ip)
{
	action_run = 5659695;
	hdr.ipv4.srcAddr = src_ip;
	hdr.ipv4.dstAddr = dst_ip;
	meta.nat_metadata.update_checksum = 1;
	meta.nat_metadata.l4_len = hdr.ipv4.totalLen + 65516;

}

// Action
void _set_nat_src_udp_rewrite_5659736(uint32_t src_ip, uint32_t src_port)
{
	action_run = 5659736;
	hdr.ipv4.srcAddr = src_ip;
	hdr.udp.srcPort = src_port;
	meta.nat_metadata.update_checksum = 1;
	meta.nat_metadata.l4_len = hdr.ipv4.totalLen + 65516;

}

// Action
void _set_nat_dst_udp_rewrite_5659777(uint32_t dst_ip, uint32_t dst_port)
{
	action_run = 5659777;
	hdr.ipv4.dstAddr = dst_ip;
	hdr.udp.dstPort = dst_port;
	meta.nat_metadata.update_checksum = 1;
	meta.nat_metadata.l4_len = hdr.ipv4.totalLen + 65516;

}

// Action
void
_set_nat_src_dst_udp_rewrite_5659818(uint32_t src_ip, uint32_t dst_ip,
				     uint32_t src_port, uint32_t dst_port)
{
	action_run = 5659818;
	hdr.ipv4.srcAddr = src_ip;
	hdr.ipv4.dstAddr = dst_ip;
	hdr.udp.srcPort = src_port;
	hdr.udp.dstPort = dst_port;
	meta.nat_metadata.update_checksum = 1;
	meta.nat_metadata.l4_len = hdr.ipv4.totalLen + 65516;

}

// Action
void _set_nat_src_tcp_rewrite_5659875(uint32_t src_ip, uint32_t src_port)
{
	action_run = 5659875;
	hdr.ipv4.srcAddr = src_ip;
	hdr.tcp.srcPort = src_port;
	meta.nat_metadata.update_checksum = 1;
	meta.nat_metadata.l4_len = hdr.ipv4.totalLen + 65516;

}

// Action
void _set_nat_dst_tcp_rewrite_5659916(uint32_t dst_ip, uint32_t dst_port)
{
	action_run = 5659916;
	hdr.ipv4.dstAddr = dst_ip;
	hdr.tcp.dstPort = dst_port;
	meta.nat_metadata.update_checksum = 1;
	meta.nat_metadata.l4_len = hdr.ipv4.totalLen + 65516;

}

// Action
void
_set_nat_src_dst_tcp_rewrite_5659957(uint32_t src_ip, uint32_t dst_ip,
				     uint32_t src_port, uint32_t dst_port)
{
	action_run = 5659957;
	hdr.ipv4.srcAddr = src_ip;
	hdr.ipv4.dstAddr = dst_ip;
	hdr.tcp.srcPort = src_port;
	hdr.tcp.dstPort = dst_port;
	meta.nat_metadata.update_checksum = 1;
	meta.nat_metadata.l4_len = hdr.ipv4.totalLen + 65516;

}

// Action
void _nop_22_5660133()
{
	action_run = 5660133;

}

// Action
void _nop_23_5660215()
{
	action_run = 5660215;

}

// Action
void _nop_24_5660225()
{
	action_run = 5660225;

}

// Action
void _nop_25_5660226()
{
	action_run = 5660226;

}

// Action
void _set_egress_dst_port_range_id_5660227(uint8_t range_id)
{
	action_run = 5660227;
	meta.acl_metadata.egress_dst_port_range_id = range_id;

}

// Action
void _set_egress_src_port_range_id_5660245(uint8_t range_id)
{
	action_run = 5660245;
	meta.acl_metadata.egress_src_port_range_id = range_id;

}

// Action
void _set_egress_tcp_port_fields_5660263()
{
	action_run = 5660263;
	meta.l3_metadata.egress_l4_sport = hdr.tcp.srcPort;
	meta.l3_metadata.egress_l4_dport = hdr.tcp.dstPort;

}

// Action
void _set_egress_udp_port_fields_5660291()
{
	action_run = 5660291;
	meta.l3_metadata.egress_l4_sport = hdr.udp.srcPort;
	meta.l3_metadata.egress_l4_dport = hdr.udp.dstPort;

}

// Action
void _set_egress_icmp_port_fields_5660319()
{
	action_run = 5660319;
	meta.l3_metadata.egress_l4_sport = hdr.icmp.typeCode;

}

// Action
void _nop_26_5660552()
{
	action_run = 5660552;

}

// Action
void _nop_27_5660562()
{
	action_run = 5660562;

}

// Action
void _nop_28_5660563()
{
	action_run = 5660563;

}

// Action
void _nop_29_5660564()
{
	action_run = 5660564;

}

// Action
void _nop_30_5660565()
{
	action_run = 5660565;

}

// Action
void _nop_31_5660566()
{
	action_run = 5660566;

}

// Action
void _nop_32_5660567()
{
	action_run = 5660567;

}

// Action
void _set_egress_tunnel_vni_5660568(uint32_t vnid)
{
	action_run = 5660568;
	meta.tunnel_metadata.vnid = vnid;

}

// Action
void _rewrite_tunnel_dmac_5660586(uint64_t dmac)
{
	action_run = 5660586;
	hdr.ethernet.dstAddr = dmac;

}

// Action
void _rewrite_tunnel_ipv4_dst_5660604(uint32_t ip)
{
	action_run = 5660604;
	hdr.ipv4.dstAddr = ip;

}

// Action
void _rewrite_tunnel_ipv6_dst_5660622(uint64_t ip)
{
	action_run = 5660622;
	hdr.ipv6.dstAddr = ip;

}

// Action
void _inner_ipv4_udp_rewrite_5660640()
{
	action_run = 5660640;
	hdr.inner_ipv4 = hdr.ipv4;
	hdr.inner_udp = hdr.udp;
	meta.egress_metadata.payload_length = hdr.ipv4.totalLen;
	hdr.udp.isValid = 0;
	hdr.ipv4.isValid = 0;
	meta.tunnel_metadata.inner_ip_proto = 4;

}

// Action
void _inner_ipv4_tcp_rewrite_5660695()
{
	action_run = 5660695;
	hdr.inner_ipv4 = hdr.ipv4;
	hdr.inner_tcp = hdr.tcp;
	meta.egress_metadata.payload_length = hdr.ipv4.totalLen;
	hdr.tcp.isValid = 0;
	hdr.ipv4.isValid = 0;
	meta.tunnel_metadata.inner_ip_proto = 4;

}

// Action
void _inner_ipv4_icmp_rewrite_5660750()
{
	action_run = 5660750;
	hdr.inner_ipv4 = hdr.ipv4;
	hdr.inner_icmp = hdr.icmp;
	meta.egress_metadata.payload_length = hdr.ipv4.totalLen;
	hdr.icmp.isValid = 0;
	hdr.ipv4.isValid = 0;
	meta.tunnel_metadata.inner_ip_proto = 4;

}

// Action
void _inner_ipv4_unknown_rewrite_5660805()
{
	action_run = 5660805;
	hdr.inner_ipv4 = hdr.ipv4;
	meta.egress_metadata.payload_length = hdr.ipv4.totalLen;
	hdr.ipv4.isValid = 0;
	meta.tunnel_metadata.inner_ip_proto = 4;

}

// Action
void _inner_ipv6_udp_rewrite_5660845()
{
	action_run = 5660845;
	hdr.inner_ipv6 = hdr.ipv6;
	hdr.inner_udp = hdr.udp;
	meta.egress_metadata.payload_length = hdr.ipv6.payloadLen + 40;
	hdr.ipv6.isValid = 0;
	meta.tunnel_metadata.inner_ip_proto = 41;

}

// Action
void _inner_ipv6_tcp_rewrite_5660894()
{
	action_run = 5660894;
	hdr.inner_ipv6 = hdr.ipv6;
	hdr.inner_tcp = hdr.tcp;
	meta.egress_metadata.payload_length = hdr.ipv6.payloadLen + 40;
	hdr.tcp.isValid = 0;
	hdr.ipv6.isValid = 0;
	meta.tunnel_metadata.inner_ip_proto = 41;

}

// Action
void _inner_ipv6_icmp_rewrite_5660951()
{
	action_run = 5660951;
	hdr.inner_ipv6 = hdr.ipv6;
	hdr.inner_icmp = hdr.icmp;
	meta.egress_metadata.payload_length = hdr.ipv6.payloadLen + 40;
	hdr.icmp.isValid = 0;
	hdr.ipv6.isValid = 0;
	meta.tunnel_metadata.inner_ip_proto = 41;

}

// Action
void _inner_ipv6_unknown_rewrite_5661008()
{
	action_run = 5661008;
	hdr.inner_ipv6 = hdr.ipv6;
	meta.egress_metadata.payload_length = hdr.ipv6.payloadLen + 40;
	hdr.ipv6.isValid = 0;
	meta.tunnel_metadata.inner_ip_proto = 41;

}

// Action
void _inner_non_ip_rewrite_5661050()
{
	action_run = 5661050;
	meta.egress_metadata.payload_length =
	    standard_metadata.packet_length + 65522;

}

// Action
void _fabric_rewrite_5661071(uint32_t tunnel_index)
{
	action_run = 5661071;
	meta.tunnel_metadata.tunnel_index = tunnel_index;

}

// Action
void _ipv4_vxlan_rewrite_5661089()
{
	action_run = 5661089;
	hdr.inner_ethernet = hdr.ethernet;
	hdr.udp.isValid = 1;
	hdr.vxlan.isValid = 1;
	hdr.udp.srcPort = meta.hash_metadata.entropy_hash;
	hdr.udp.dstPort = 4789;
	meta.l3_metadata.egress_l4_sport = meta.hash_metadata.entropy_hash;
	meta.l3_metadata.egress_l4_dport = 4789;
	hdr.udp.checksum = 0;
	hdr.udp.length_ = meta.egress_metadata.payload_length + 30;
	hdr.vxlan.flags = 8;
	hdr.vxlan.reserved = 0;
	hdr.vxlan.vni = meta.tunnel_metadata.vnid;
	hdr.vxlan.reserved2 = 0;
	hdr.ipv4.isValid = 1;
	hdr.ipv4.protocol = 17;
	hdr.ipv4.ttl = 64;
	hdr.ipv4.version = 4;
	hdr.ipv4.ihl = 5;
	hdr.ipv4.identification = 0;
	hdr.ipv4.totalLen = meta.egress_metadata.payload_length + 50;
	hdr.ethernet.etherType = 2048;

}

// Action
void _ipv4_genv_rewrite_5661251()
{
	action_run = 5661251;
	hdr.inner_ethernet = hdr.ethernet;
	hdr.udp.isValid = 1;
	hdr.genv.isValid = 1;
	hdr.udp.srcPort = meta.hash_metadata.entropy_hash;
	hdr.udp.dstPort = 6081;
	meta.l3_metadata.egress_l4_sport = meta.hash_metadata.entropy_hash;
	meta.l3_metadata.egress_l4_dport = 6081;
	hdr.udp.checksum = 0;
	hdr.udp.length_ = meta.egress_metadata.payload_length + 30;
	hdr.genv.ver = 0;
	hdr.genv.oam = 0;
	hdr.genv.critical = 0;
	hdr.genv.optLen = 0;
	hdr.genv.protoType = 25944;
	hdr.genv.vni = meta.tunnel_metadata.vnid;
	hdr.genv.reserved = 0;
	hdr.genv.reserved2 = 0;
	hdr.ipv4.isValid = 1;
	hdr.ipv4.protocol = 17;
	hdr.ipv4.ttl = 64;
	hdr.ipv4.version = 4;
	hdr.ipv4.ihl = 5;
	hdr.ipv4.identification = 0;
	hdr.ipv4.totalLen = meta.egress_metadata.payload_length + 50;
	hdr.ethernet.etherType = 2048;

}

// Action
void _ipv4_nvgre_rewrite_6063072()
{
	action_run = 6063072;
	hdr.inner_ethernet = hdr.ethernet;
	hdr.gre.isValid = 1;
	hdr.nvgre.isValid = 1;
	hdr.gre.proto = 25944;
	hdr.gre.recurse = 0;
	hdr.gre.flags = 0;
	hdr.gre.ver = 0;
	hdr.gre.R = 0;
	hdr.gre.K = 1;
	hdr.gre.C = 0;
	hdr.gre.S = 0;
	hdr.gre.s = 0;
	hdr.nvgre.tni = meta.tunnel_metadata.vnid;
	hdr.nvgre.flow_id =
	    ((hdr.
	      nvgre.flow_id & ~255) | ((uint8_t) BITSLICE((uint8_t) meta.
							  hash_metadata.entropy_hash,
							  7, 0) << 0 & 255));
	hdr.ipv4.isValid = 1;
	hdr.ipv4.protocol = 47;
	hdr.ipv4.ttl = 64;
	hdr.ipv4.version = 4;
	hdr.ipv4.ihl = 5;
	hdr.ipv4.identification = 0;
	hdr.ipv4.totalLen = meta.egress_metadata.payload_length + 42;
	hdr.ethernet.etherType = 2048;

}

// Action
void _ipv4_gre_rewrite_5661596()
{
	action_run = 5661596;
	hdr.gre.isValid = 1;
	hdr.gre.proto = hdr.ethernet.etherType;
	hdr.ipv4.isValid = 1;
	hdr.ipv4.protocol = 47;
	hdr.ipv4.ttl = 64;
	hdr.ipv4.version = 4;
	hdr.ipv4.ihl = 5;
	hdr.ipv4.identification = 0;
	hdr.ipv4.totalLen = meta.egress_metadata.payload_length + 24;
	hdr.ethernet.etherType = 2048;

}

// Action
void _ipv4_ip_rewrite_5661672()
{
	action_run = 5661672;
	hdr.ipv4.isValid = 1;
	hdr.ipv4.protocol = meta.tunnel_metadata.inner_ip_proto;
	hdr.ipv4.ttl = 64;
	hdr.ipv4.version = 4;
	hdr.ipv4.ihl = 5;
	hdr.ipv4.identification = 0;
	hdr.ipv4.totalLen = meta.egress_metadata.payload_length + 20;
	hdr.ethernet.etherType = 2048;

}

// Action
void _ipv6_gre_rewrite_5661734()
{
	action_run = 5661734;
	hdr.gre.isValid = 1;
	hdr.gre.proto = hdr.ethernet.etherType;
	hdr.ipv6.isValid = 1;
	hdr.ipv6.version = 6;
	hdr.ipv6.nextHdr = 47;
	hdr.ipv6.hopLimit = 64;
	hdr.ipv6.trafficClass = 0;
	hdr.ipv6.flowLabel = 0;
	hdr.ipv6.payloadLen = meta.egress_metadata.payload_length + 4;
	hdr.ethernet.etherType = 34525;

}

// Action
void _ipv6_ip_rewrite_5661814()
{
	action_run = 5661814;
	hdr.ipv6.isValid = 1;
	hdr.ipv6.version = 6;
	hdr.ipv6.nextHdr = meta.tunnel_metadata.inner_ip_proto;
	hdr.ipv6.hopLimit = 64;
	hdr.ipv6.trafficClass = 0;
	hdr.ipv6.flowLabel = 0;
	hdr.ipv6.payloadLen = meta.egress_metadata.payload_length;
	hdr.ethernet.etherType = 34525;

}

// Action
void _ipv6_nvgre_rewrite_6063525()
{
	action_run = 6063525;
	hdr.inner_ethernet = hdr.ethernet;
	hdr.gre.isValid = 1;
	hdr.nvgre.isValid = 1;
	hdr.gre.proto = 25944;
	hdr.gre.recurse = 0;
	hdr.gre.flags = 0;
	hdr.gre.ver = 0;
	hdr.gre.R = 0;
	hdr.gre.K = 1;
	hdr.gre.C = 0;
	hdr.gre.S = 0;
	hdr.gre.s = 0;
	hdr.nvgre.tni = meta.tunnel_metadata.vnid;
	hdr.nvgre.flow_id =
	    ((hdr.
	      nvgre.flow_id & ~255) | ((uint8_t) BITSLICE((uint8_t) meta.
							  hash_metadata.entropy_hash,
							  7, 0) << 0 & 255));
	hdr.ipv6.isValid = 1;
	hdr.ipv6.version = 6;
	hdr.ipv6.nextHdr = 47;
	hdr.ipv6.hopLimit = 64;
	hdr.ipv6.trafficClass = 0;
	hdr.ipv6.flowLabel = 0;
	hdr.ipv6.payloadLen = meta.egress_metadata.payload_length + 22;
	hdr.ethernet.etherType = 34525;

}

// Action
void _ipv6_vxlan_rewrite_5662018()
{
	action_run = 5662018;
	hdr.inner_ethernet = hdr.ethernet;
	hdr.udp.isValid = 1;
	hdr.vxlan.isValid = 1;
	hdr.udp.srcPort = meta.hash_metadata.entropy_hash;
	hdr.udp.dstPort = 4789;
	meta.l3_metadata.egress_l4_sport = meta.hash_metadata.entropy_hash;
	meta.l3_metadata.egress_l4_dport = 4789;
	hdr.udp.checksum = 0;
	hdr.udp.length_ = meta.egress_metadata.payload_length + 30;
	hdr.vxlan.flags = 8;
	hdr.vxlan.reserved = 0;
	hdr.vxlan.vni = meta.tunnel_metadata.vnid;
	hdr.vxlan.reserved2 = 0;
	hdr.ipv6.isValid = 1;
	hdr.ipv6.version = 6;
	hdr.ipv6.nextHdr = 17;
	hdr.ipv6.hopLimit = 64;
	hdr.ipv6.trafficClass = 0;
	hdr.ipv6.flowLabel = 0;
	hdr.ipv6.payloadLen = meta.egress_metadata.payload_length + 30;
	hdr.ethernet.etherType = 34525;

}

// Action
void _ipv6_genv_rewrite_5662163()
{
	action_run = 5662163;
	hdr.inner_ethernet = hdr.ethernet;
	hdr.udp.isValid = 1;
	hdr.genv.isValid = 1;
	hdr.udp.srcPort = meta.hash_metadata.entropy_hash;
	hdr.udp.dstPort = 6081;
	meta.l3_metadata.egress_l4_sport = meta.hash_metadata.entropy_hash;
	meta.l3_metadata.egress_l4_dport = 6081;
	hdr.udp.checksum = 0;
	hdr.udp.length_ = meta.egress_metadata.payload_length + 30;
	hdr.genv.ver = 0;
	hdr.genv.oam = 0;
	hdr.genv.critical = 0;
	hdr.genv.optLen = 0;
	hdr.genv.protoType = 25944;
	hdr.genv.vni = meta.tunnel_metadata.vnid;
	hdr.genv.reserved = 0;
	hdr.genv.reserved2 = 0;
	hdr.ipv6.isValid = 1;
	hdr.ipv6.version = 6;
	hdr.ipv6.nextHdr = 17;
	hdr.ipv6.hopLimit = 64;
	hdr.ipv6.trafficClass = 0;
	hdr.ipv6.flowLabel = 0;
	hdr.ipv6.payloadLen = meta.egress_metadata.payload_length + 30;
	hdr.ethernet.etherType = 34525;

}

// Action
void _mpls_ethernet_push1_rewrite_5662328()
{
	action_run = 5662328;
	hdr.inner_ethernet = hdr.ethernet;
	//push_front(1)
	int header_stack_size = sizeof(hdr.mpls) / sizeof(hdr.mpls[0]);
	int i;
	for (i = header_stack_size - 1; i >= 0; i -= 1) {
		if (i >= 1) {
			hdr.mpls[i] = hdr.mpls[i - 1];
		} else {
			hdr.mpls[i].isValid = 0;
		}
	}
	hdr.mpls_index = hdr.mpls_index + 1;
	if (hdr.mpls_index > header_stack_size)
		hdr.mpls_index = header_stack_size;

	hdr.ethernet.etherType = 34887;

}

// Action
void _mpls_ip_push1_rewrite_5662361()
{
	action_run = 5662361;
	//push_front(1)
	int header_stack_size = sizeof(hdr.mpls) / sizeof(hdr.mpls[0]);
	int i;
	for (i = header_stack_size - 1; i >= 0; i -= 1) {
		if (i >= 1) {
			hdr.mpls[i] = hdr.mpls[i - 1];
		} else {
			hdr.mpls[i].isValid = 0;
		}
	}
	hdr.mpls_index = hdr.mpls_index + 1;
	if (hdr.mpls_index > header_stack_size)
		hdr.mpls_index = header_stack_size;

	hdr.ethernet.etherType = 34887;

}

// Action
void _mpls_ethernet_push2_rewrite_5662387()
{
	action_run = 5662387;
	hdr.inner_ethernet = hdr.ethernet;
	//push_front(2)
	int header_stack_size = sizeof(hdr.mpls) / sizeof(hdr.mpls[0]);
	int i;
	for (i = header_stack_size - 1; i >= 0; i -= 1) {
		if (i >= 2) {
			hdr.mpls[i] = hdr.mpls[i - 2];
		} else {
			hdr.mpls[i].isValid = 0;
		}
	}
	hdr.mpls_index = hdr.mpls_index + 2;
	if (hdr.mpls_index > header_stack_size)
		hdr.mpls_index = header_stack_size;

	hdr.ethernet.etherType = 34887;

}

// Action
void _mpls_ip_push2_rewrite_5662420()
{
	action_run = 5662420;
	//push_front(2)
	int header_stack_size = sizeof(hdr.mpls) / sizeof(hdr.mpls[0]);
	int i;
	for (i = header_stack_size - 1; i >= 0; i -= 1) {
		if (i >= 2) {
			hdr.mpls[i] = hdr.mpls[i - 2];
		} else {
			hdr.mpls[i].isValid = 0;
		}
	}
	hdr.mpls_index = hdr.mpls_index + 2;
	if (hdr.mpls_index > header_stack_size)
		hdr.mpls_index = header_stack_size;

	hdr.ethernet.etherType = 34887;

}

// Action
void _mpls_ethernet_push3_rewrite_5662446()
{
	action_run = 5662446;
	hdr.inner_ethernet = hdr.ethernet;
	//push_front(3)
	int header_stack_size = sizeof(hdr.mpls) / sizeof(hdr.mpls[0]);
	int i;
	for (i = header_stack_size - 1; i >= 0; i -= 1) {
		if (i >= 3) {
			hdr.mpls[i] = hdr.mpls[i - 3];
		} else {
			hdr.mpls[i].isValid = 0;
		}
	}
	hdr.mpls_index = hdr.mpls_index + 3;
	if (hdr.mpls_index > header_stack_size)
		hdr.mpls_index = header_stack_size;

	hdr.ethernet.etherType = 34887;

}

// Action
void _mpls_ip_push3_rewrite_5662479()
{
	action_run = 5662479;
	//push_front(3)
	int header_stack_size = sizeof(hdr.mpls) / sizeof(hdr.mpls[0]);
	int i;
	for (i = header_stack_size - 1; i >= 0; i -= 1) {
		if (i >= 3) {
			hdr.mpls[i] = hdr.mpls[i - 3];
		} else {
			hdr.mpls[i].isValid = 0;
		}
	}
	hdr.mpls_index = hdr.mpls_index + 3;
	if (hdr.mpls_index > header_stack_size)
		hdr.mpls_index = header_stack_size;

	hdr.ethernet.etherType = 34887;

}

// Action
void _ipv4_erspan_t3_rewrite_5662505()
{
	action_run = 5662505;
	hdr.inner_ethernet = hdr.ethernet;
	hdr.gre.isValid = 1;
	hdr.erspan_t3_header.isValid = 1;
	hdr.gre.C = 0;
	hdr.gre.R = 0;
	hdr.gre.K = 0;
	hdr.gre.S = 0;
	hdr.gre.s = 0;
	hdr.gre.recurse = 0;
	hdr.gre.flags = 0;
	hdr.gre.ver = 0;
	hdr.gre.proto = 8939;
	hdr.erspan_t3_header.timestamp = meta.i2e_metadata.ingress_tstamp;
	hdr.erspan_t3_header.span_id =
	    (uint32_t) meta.i2e_metadata.mirror_session_id;
	hdr.erspan_t3_header.version = 2;
	hdr.erspan_t3_header.sgt = 0;
	hdr.ipv4.isValid = 1;
	hdr.ipv4.protocol = 47;
	hdr.ipv4.ttl = 64;
	hdr.ipv4.version = 4;
	hdr.ipv4.ihl = 5;
	hdr.ipv4.identification = 0;
	hdr.ipv4.totalLen = meta.egress_metadata.payload_length + 50;

}

// Action
void _ipv6_erspan_t3_rewrite_5662666()
{
	action_run = 5662666;
	hdr.inner_ethernet = hdr.ethernet;
	hdr.gre.isValid = 1;
	hdr.erspan_t3_header.isValid = 1;
	hdr.gre.C = 0;
	hdr.gre.R = 0;
	hdr.gre.K = 0;
	hdr.gre.S = 0;
	hdr.gre.s = 0;
	hdr.gre.recurse = 0;
	hdr.gre.flags = 0;
	hdr.gre.ver = 0;
	hdr.gre.proto = 8939;
	hdr.erspan_t3_header.timestamp = meta.i2e_metadata.ingress_tstamp;
	hdr.erspan_t3_header.span_id =
	    (uint32_t) meta.i2e_metadata.mirror_session_id;
	hdr.erspan_t3_header.version = 2;
	hdr.erspan_t3_header.sgt = 0;
	hdr.ipv6.isValid = 1;
	hdr.ipv6.version = 6;
	hdr.ipv6.nextHdr = 47;
	hdr.ipv6.hopLimit = 64;
	hdr.ipv6.trafficClass = 0;
	hdr.ipv6.flowLabel = 0;
	hdr.ipv6.payloadLen = meta.egress_metadata.payload_length + 26;

}

// Action
void _tunnel_mtu_check_5662812(uint32_t l3_mtu)
{
	action_run = 5662812;
	meta.l3_metadata.l3_mtu_check =
	    l3_mtu - meta.egress_metadata.payload_length;

}

// Action
void _tunnel_mtu_miss_5662835()
{
	action_run = 5662835;
	meta.l3_metadata.l3_mtu_check = 65535;

}

// Action
void _cpu_rx_rewrite_5662851()
{
	action_run = 5662851;
	hdr.fabric_header.isValid = 1;
	hdr.fabric_header.headerVersion = 0;
	hdr.fabric_header.packetVersion = 0;
	hdr.fabric_header.pad1 = 0;
	hdr.fabric_header.packetType = 5;
	hdr.fabric_header_cpu.isValid = 1;
	hdr.fabric_header_cpu.ingressPort =
	    (uint32_t) meta.ingress_metadata.ingress_port;
	hdr.fabric_header_cpu.ingressIfindex = meta.ingress_metadata.ifindex;
	hdr.fabric_header_cpu.ingressBd = meta.ingress_metadata.bd;
	hdr.fabric_header_cpu.reasonCode = meta.fabric_metadata.reason_code;
	hdr.fabric_payload_header.isValid = 1;
	hdr.fabric_payload_header.etherType = hdr.ethernet.etherType;
	hdr.ethernet.etherType = 36864;

}

// Action
void
_set_tunnel_rewrite_details_5662961(uint32_t outer_bd, uint32_t smac_idx,
				    uint32_t dmac_idx, uint32_t sip_index,
				    uint32_t dip_index)
{
	action_run = 5662961;
	meta.egress_metadata.outer_bd = outer_bd;
	meta.tunnel_metadata.tunnel_smac_index = smac_idx;
	meta.tunnel_metadata.tunnel_dmac_index = dmac_idx;
	meta.tunnel_metadata.tunnel_src_index = sip_index;
	meta.tunnel_metadata.tunnel_dst_index = dip_index;

}

// Action
void
_set_mpls_rewrite_push1_5663011(uint32_t label1, uint8_t exp1, uint8_t ttl1,
				uint32_t smac_idx, uint32_t dmac_idx)
{
	action_run = 5663011;
	hdr.mpls[0].label = label1;
	hdr.mpls[0].exp = exp1;
	hdr.mpls[0].bos = 1;
	hdr.mpls[0].ttl = ttl1;
	meta.tunnel_metadata.tunnel_smac_index = smac_idx;
	meta.tunnel_metadata.tunnel_dmac_index = dmac_idx;

}

// Action
void
_set_mpls_rewrite_push2_5663079(uint32_t label1, uint8_t exp1, uint8_t ttl1,
				uint32_t label2, uint8_t exp2, uint8_t ttl2,
				uint32_t smac_idx, uint32_t dmac_idx)
{
	action_run = 5663079;
	hdr.mpls[0].label = label1;
	hdr.mpls[0].exp = exp1;
	hdr.mpls[0].ttl = ttl1;
	hdr.mpls[0].bos = 0;
	hdr.mpls[1].label = label2;
	hdr.mpls[1].exp = exp2;
	hdr.mpls[1].ttl = ttl2;
	hdr.mpls[1].bos = 1;
	meta.tunnel_metadata.tunnel_smac_index = smac_idx;
	meta.tunnel_metadata.tunnel_dmac_index = dmac_idx;

}

// Action
void
_set_mpls_rewrite_push3_5663189(uint32_t label1, uint8_t exp1, uint8_t ttl1,
				uint32_t label2, uint8_t exp2, uint8_t ttl2,
				uint32_t label3, uint8_t exp3, uint8_t ttl3,
				uint32_t smac_idx, uint32_t dmac_idx)
{
	action_run = 5663189;
	hdr.mpls[0].label = label1;
	hdr.mpls[0].exp = exp1;
	hdr.mpls[0].ttl = ttl1;
	hdr.mpls[0].bos = 0;
	hdr.mpls[1].label = label2;
	hdr.mpls[1].exp = exp2;
	hdr.mpls[1].ttl = ttl2;
	hdr.mpls[1].bos = 0;
	hdr.mpls[2].label = label3;
	hdr.mpls[2].exp = exp3;
	hdr.mpls[2].ttl = ttl3;
	hdr.mpls[2].bos = 1;
	meta.tunnel_metadata.tunnel_smac_index = smac_idx;
	meta.tunnel_metadata.tunnel_dmac_index = dmac_idx;

}

// Action
void _fabric_unicast_rewrite_5663341()
{
	action_run = 5663341;
	hdr.fabric_header.isValid = 1;
	hdr.fabric_header.headerVersion = 0;
	hdr.fabric_header.packetVersion = 0;
	hdr.fabric_header.pad1 = 0;
	hdr.fabric_header.packetType = 1;
	hdr.fabric_header.dstDevice = meta.fabric_metadata.dst_device;
	hdr.fabric_header.dstPortOrGroup = meta.fabric_metadata.dst_port;
	hdr.fabric_header_unicast.isValid = 1;
	hdr.fabric_header_unicast.tunnelTerminate =
	    meta.tunnel_metadata.tunnel_terminate;
	hdr.fabric_header_unicast.routed = meta.l3_metadata.routed;
	hdr.fabric_header_unicast.outerRouted = meta.l3_metadata.outer_routed;
	hdr.fabric_header_unicast.ingressTunnelType =
	    meta.tunnel_metadata.ingress_tunnel_type;
	hdr.fabric_header_unicast.nexthopIndex = meta.l3_metadata.nexthop_index;
	hdr.fabric_payload_header.isValid = 1;
	hdr.fabric_payload_header.etherType = hdr.ethernet.etherType;
	hdr.ethernet.etherType = 36864;

}

// Action
void _fabric_multicast_rewrite_5663477(uint32_t fabric_mgid)
{
	action_run = 5663477;
	hdr.fabric_header.isValid = 1;
	hdr.fabric_header.headerVersion = 0;
	hdr.fabric_header.packetVersion = 0;
	hdr.fabric_header.pad1 = 0;
	hdr.fabric_header.packetType = 2;
	hdr.fabric_header.dstDevice = 127;
	hdr.fabric_header.dstPortOrGroup = fabric_mgid;
	hdr.fabric_header_multicast.ingressIfindex =
	    meta.ingress_metadata.ifindex;
	hdr.fabric_header_multicast.ingressBd = meta.ingress_metadata.bd;
	hdr.fabric_header_multicast.isValid = 1;
	hdr.fabric_header_multicast.tunnelTerminate =
	    meta.tunnel_metadata.tunnel_terminate;
	hdr.fabric_header_multicast.routed = meta.l3_metadata.routed;
	hdr.fabric_header_multicast.outerRouted = meta.l3_metadata.outer_routed;
	hdr.fabric_header_multicast.ingressTunnelType =
	    meta.tunnel_metadata.ingress_tunnel_type;
	hdr.fabric_header_multicast.mcastGrp =
	    meta.multicast_metadata.mcast_grp;
	hdr.fabric_payload_header.isValid = 1;
	hdr.fabric_payload_header.etherType = hdr.ethernet.etherType;
	hdr.ethernet.etherType = 36864;

}

// Action
void _rewrite_tunnel_smac_5663627(uint64_t smac)
{
	action_run = 5663627;
	hdr.ethernet.srcAddr = smac;

}

// Action
void _rewrite_tunnel_ipv4_src_5663645(uint32_t ip)
{
	action_run = 5663645;
	hdr.ipv4.srcAddr = ip;

}

// Action
void _rewrite_tunnel_ipv6_src_5663663(uint64_t ip)
{
	action_run = 5663663;
	hdr.ipv6.srcAddr = ip;

}

// Action
void _nop_33_5664479()
{
	action_run = 5664479;

}

// Action
void _nop_34_5664489()
{
	action_run = 5664489;

}

// Action
void _nop_35_5664490()
{
	action_run = 5664490;

}

// Action
void _egress_acl_deny_5664491(uint32_t acl_copy_reason)
{
	action_run = 5664491;
	meta.acl_metadata.acl_deny = 1;
	meta.fabric_metadata.reason_code = acl_copy_reason;

}

// Action
void _egress_acl_deny_3_5664515(uint32_t acl_copy_reason)
{
	action_run = 5664515;
	meta.acl_metadata.acl_deny = 1;
	meta.fabric_metadata.reason_code = acl_copy_reason;

}

// Action
void _egress_acl_deny_4_5664533(uint32_t acl_copy_reason)
{
	action_run = 5664533;
	meta.acl_metadata.acl_deny = 1;
	meta.fabric_metadata.reason_code = acl_copy_reason;

}

// Action
void _egress_acl_permit_5664551(uint32_t acl_copy_reason)
{
	action_run = 5664551;
	meta.fabric_metadata.reason_code = acl_copy_reason;

}

// Action
void _egress_acl_permit_3_5664569(uint32_t acl_copy_reason)
{
	action_run = 5664569;
	meta.fabric_metadata.reason_code = acl_copy_reason;

}

// Action
void _egress_acl_permit_4_5664582(uint32_t acl_copy_reason)
{
	action_run = 5664582;
	meta.fabric_metadata.reason_code = acl_copy_reason;

}

// Action
void _int_update_vxlan_gpe_ipv4_5664944()
{
	action_run = 5664944;
	hdr.ipv4.totalLen =
	    hdr.ipv4.totalLen + meta.int_metadata.insert_byte_cnt;
	hdr.udp.length_ = hdr.udp.length_ + meta.int_metadata.insert_byte_cnt;
	hdr.vxlan_gpe_int_header.len =
	    hdr.vxlan_gpe_int_header.len + meta.int_metadata.gpe_int_hdr_len8;

}

// Action
void _int_add_update_vxlan_gpe_ipv4_5664996()
{
	action_run = 5664996;
	hdr.vxlan_gpe_int_header.isValid = 1;
	hdr.vxlan_gpe_int_header.int_type = 1;
	hdr.vxlan_gpe_int_header.next_proto = 3;
	hdr.vxlan_gpe.next_proto = 5;
	hdr.vxlan_gpe_int_header.len = meta.int_metadata.gpe_int_hdr_len8;
	hdr.ipv4.totalLen =
	    hdr.ipv4.totalLen + meta.int_metadata.insert_byte_cnt;
	hdr.udp.length_ = hdr.udp.length_ + meta.int_metadata.insert_byte_cnt;

}

// Action
void _nop_36_5665069()
{
	action_run = 5665069;

}

// Action
void _set_egress_packet_vlan_untagged_5665180()
{
	action_run = 5665180;

}

// Action
void _set_egress_packet_vlan_tagged_5665190(uint32_t vlan_id)
{
	action_run = 5665190;
	hdr.vlan_tag_[0].isValid = 1;
	hdr.vlan_tag_[0].etherType = hdr.ethernet.etherType;
	hdr.vlan_tag_[0].vid = vlan_id;
	hdr.ethernet.etherType = 33024;

}

// Action
void
_set_egress_packet_vlan_double_tagged_5665240(uint32_t s_tag, uint32_t c_tag)
{
	action_run = 5665240;
	hdr.vlan_tag_[1].isValid = 1;
	hdr.vlan_tag_[0].isValid = 1;
	hdr.vlan_tag_[1].etherType = hdr.ethernet.etherType;
	hdr.vlan_tag_[1].vid = c_tag;
	hdr.vlan_tag_[0].etherType = 33024;
	hdr.vlan_tag_[0].vid = s_tag;
	hdr.ethernet.etherType = 37120;

}

// Action
void _egress_filter_check_5665394()
{
	action_run = 5665394;
	meta.egress_filter_metadata.ifindex_check =
	    (meta.ingress_metadata.ifindex ^ meta.egress_metadata.ifindex);
	meta.egress_filter_metadata.bd =
	    (meta.ingress_metadata.outer_bd ^ meta.egress_metadata.outer_bd);
	meta.egress_filter_metadata.inner_bd =
	    (meta.ingress_metadata.bd ^ meta.egress_metadata.bd);

}

// Action
void _set_egress_filter_drop_5665446()
{
	action_run = 5665446;
	mark_to_drop();

}

// Action
void _nop_37_5665530()
{
	action_run = 5665530;

}

// Action
void _drop_packet_5665540()
{
	action_run = 5665540;
	mark_to_drop();

}

// Action
void _egress_copy_to_cpu_5665556()
{
	action_run = 5665556;

}

// Action
void _egress_redirect_to_cpu_5665597()
{
	action_run = 5665597;
	mark_to_drop();

}

// Action
void _egress_copy_to_cpu_with_reason_5709531(uint32_t reason_code)
{
	action_run = 5709531;
	meta.fabric_metadata.reason_code = reason_code;

}

// Action
void _egress_redirect_to_cpu_with_reason_5709602(uint32_t reason_code)
{
	action_run = 5709602;
	meta.fabric_metadata.reason_code = reason_code;
	mark_to_drop();

}

// Action
void _egress_mirror_5709685(uint32_t session_id)
{
	action_run = 5709685;
	meta.i2e_metadata.mirror_session_id = (uint32_t) session_id;

}

// Action
void _egress_mirror_drop_5709753(uint32_t session_id)
{
	action_run = 5709753;
	meta.i2e_metadata.mirror_session_id = (uint32_t) session_id;
	mark_to_drop();

}

//Table
void egress_port_mapping_5652991()
{
	if (standard_metadata.egress_port == 0x0001) {
		egress_port_type_normal_0_5652891(0x01, 0x00, 0x00);
	} else if (standard_metadata.egress_port == 0x0002) {
		egress_port_type_normal_0_5652891(0x02, 0x00, 0x00);
	} else {
		egress_port_type_normal_0_5652891(0,0,0);	// default action
	}

}

//Table
void _mirror_0_5653145()
{
	_nop_8_5653055();	// default action
}

//Table
void _replica_type_0_5653393()
{
	_nop_9_5653216();	// default action
}

//Table
void _rid_0_5653462()
{
	_nop_9_5653216();	// default action
}

//Table
void _vlan_decap_0_5653612()
{
	if (hdr.vlan_tag_[0].isValid == 1 && hdr.vlan_tag_[1].isValid == 0) {
		_remove_vlan_single_tagged_5653535();
	} else if (hdr.vlan_tag_[0].isValid == 1
		   && hdr.vlan_tag_[1].isValid == 1) {
		_remove_vlan_double_tagged_5653568();
	} else {
		_nop_9_5653216();	// default action
	}

}

//Table
void _tunnel_decap_process_inner_0_5655361()
{
	if (hdr.inner_tcp.isValid == 1 && hdr.inner_udp.isValid == 0
	    && hdr.inner_icmp.isValid == 0) {
		_decap_inner_tcp_5653724();
	} else {
		NoAction_134_5652853();	// default action
	}

}

//Table
void _tunnel_decap_process_outer_0_5655461()
{
	if (meta.tunnel_metadata.ingress_tunnel_type == 0x01
	    && hdr.inner_ipv4.isValid == 1 && hdr.inner_ipv6.isValid == 0) {
		_decap_vxlan_inner_ipv4_5653808();
	} else {
		NoAction_135_5652854();	// default action
	}

}

//Table
void _rewrite_0_5656181()
{
	if (meta.l3_metadata.nexthop_index == 0x0001) {
		_set_l2_rewrite_with_tunnel_5655753(0x00, 0x01);
	} else {
		_set_l2_rewrite_5655719();	// default action
	}

}

//Table
void _rewrite_multicast_0_5714227()
{
	_nop_9_5653216();	// default action
}

//Table
void _egress_bd_map_0_5714383()
{
	_nop_9_5653216();	// default action
}

//Table
void _egress_qos_map_0_5714507()
{
	_nop_9_5653216();	// default action
}

//Table
void _l3_rewrite_0_5714815()
{
	if (hdr.ipv4.isValid == 1 && hdr.ipv6.isValid == 0
	    && hdr.mpls[0].isValid == 0) {
		_ipv4_unicast_rewrite_5656633(100);
	} else if (hdr.ipv4.isValid == 0 && hdr.ipv6.isValid == 1
		   && hdr.mpls[0].isValid == 0) {
		_ipv6_unicast_rewrite_5656713(200);
	} else {
		_nop_9_5653216();	// default action
	}

}

//Table
void _smac_rewrite_0_5714962()
{
	if (meta.egress_metadata.smac_idx == 0x0001) {
		_rewrite_smac_5656829(0x3333333333);
	} else {
		NoAction_141_5652860();	// default action
	}

}

//Table
void _mtu_0_5715078()
{
	_mtu_miss_5657029();	// default action
}

//Table
void _int_bos_0_5716966()
{
	_nop_9_5653216();	// default action
}

//Table
void _int_insert_0_5717116()
{
	_int_reset_5657512();	// default action
}

//Table
void _int_inst_3_5717208()
{
	NoAction_145_5652864();	// default action
}

//Table
void _int_inst_4_5717351()
{
	NoAction_146_5652865();	// default action
}

//Table
void _int_inst_5_5717500()
{
	NoAction_147_5652866();	// default action
}

//Table
void _int_inst_6_5717553()
{
	NoAction_148_5652867();	// default action
}

//Table
void _int_meta_header_update_0_5717606()
{
	_int_update_total_hop_cnt_5658922();	// default action
}

//Table
void _egress_nat_0_5718078()
{
	_nop_9_5653216();	// default action
}

//Table
void _egress_bd_stats_2_5718217()
{
	_nop_9_5653216();	// default action
}

//Table
void _egress_l4_dst_port_0_5718410()
{
	_nop_9_5653216();	// default action
}

//Table
void _egress_l4_src_port_0_5718470()
{
	_nop_9_5653216();	// default action
}

//Table
void _egress_l4port_fields_0_5660452()
{
	_nop_9_5653216();	// default action
}

//Table
void _egress_vni_0_5721844()
{
	if (meta.egress_metadata.bd == 0x03e8
	    && meta.tunnel_metadata.egress_tunnel_type == 0x01) {
		_set_egress_tunnel_vni_5660568(0x1234);
	} else {
		_nop_9_5653216();	// default action
	}

}

//Table
void _tunnel_dmac_rewrite_0_5721916()
{
	if (meta.tunnel_metadata.tunnel_dmac_index == 0x0000) {
		_rewrite_tunnel_dmac_5660586(0x5555555555);
	} else {
		_nop_9_5653216();	// default action
	}

}

//Table
void _tunnel_dst_rewrite_0_5721975()
{
	if (meta.tunnel_metadata.tunnel_dst_index == 0x0000) {
		_rewrite_tunnel_ipv4_dst_5660604(0x0a0a0a02);
	} else {
		_nop_9_5653216();	// default action
	}

}

//Table
void _tunnel_encap_process_inner_0_5663868()
{
	if (hdr.ipv4.isValid == 1 && hdr.ipv6.isValid == 0
	    && hdr.tcp.isValid == 1 && hdr.udp.isValid == 0
	    && hdr.icmp.isValid == 0) {
		_inner_ipv4_tcp_rewrite_5660695();
	} else {
		NoAction_158_5652877();	// default action
	}

}

//Table
void _tunnel_encap_process_outer_0_5722200()
{
	if (meta.tunnel_metadata.egress_tunnel_type == 0x01
	    && meta.tunnel_metadata.egress_header_count == 0x00
	    && meta.multicast_metadata.replica == 0x00) {
		_ipv4_vxlan_rewrite_5661089();
	} else {
		_nop_9_5653216();	// default action
	}

}

//Table
void _tunnel_mtu_0_5722391()
{
	_tunnel_mtu_miss_5662835();	// default action
}

//Table
void _tunnel_rewrite_0_5722450()
{
	if (meta.tunnel_metadata.tunnel_index == 0x0000) {
		_set_tunnel_rewrite_details_5662961(0x0a, 0x00, 0x00, 0x00,
						    0x00);
	} else {
		_nop_9_5653216();	// default action
	}

}

//Table
void _tunnel_smac_rewrite_0_5722545()
{
	if (meta.tunnel_metadata.tunnel_smac_index == 0x0000) {
		_rewrite_tunnel_smac_5663627(0x3333333333);
	} else {
		_nop_9_5653216();	// default action
	}

}

//Table
void _tunnel_src_rewrite_0_5722604()
{
	if (meta.tunnel_metadata.tunnel_src_index == 0x0000) {
		_rewrite_tunnel_ipv4_src_5663645(0x0a0a0a01);
	} else {
		_nop_9_5653216();	// default action
	}

}

//Table
void _egress_ip_acl_0_5722787()
{
	_nop_9_5653216();	// default action
}

//Table
void _egress_ipv6_acl_0_5722926()
{
	_nop_9_5653216();	// default action
}

//Table
void _egress_mac_acl_0_5723063()
{
	_nop_9_5653216();	// default action
}

//Table
void _int_outer_encap_0_5723311()
{
	_nop_9_5653216();	// default action
}

//Table
void _egress_vlan_xlate_0_5723560()
{
	_set_egress_packet_vlan_untagged_5665180();	// default action
}

//Table
void _egress_filter_0_5665462()
{
	_egress_filter_check_5665394();	// default action
}

//Table
void _egress_filter_drop_0_5665496()
{
	_set_egress_filter_drop_5665446();	// default action
}

//Table
void _egress_system_acl_0_5724062()
{
	_nop_9_5653216();	// default action
}

typedef struct {
	uint32_t bd:16;
	uint64_t lkp_mac_sa:48;
	uint32_t ifindex:16;
} mac_learn_digest;

typedef struct {
	uint8_t field_5:1;
	uint32_t field_6:16;
} tuple_2;

typedef struct {
	tuple_0 field_7;
	uint32_t field_8:16;
	uint32_t field_9:16;
	uint32_t field_10:16;
} tuple_3;

typedef struct {
	uint32_t field_11:32;
	uint32_t field_12:32;
	uint8_t field_13:8;
	uint32_t field_14:16;
	uint32_t field_15:16;
} tuple_4;

typedef struct {
	uint64_t field_16:48;
	uint64_t field_17:48;
	uint32_t field_18:32;
	uint32_t field_19:32;
	uint8_t field_20:8;
	uint32_t field_21:16;
	uint32_t field_22:16;
} tuple_5;

typedef struct {
	uint64_t field_23:64;
	uint64_t field_24:64;
	uint8_t field_25:8;
	uint32_t field_26:16;
	uint32_t field_27:16;
} tuple_6;

typedef struct {
	uint64_t field_28:48;
	uint64_t field_29:48;
	uint64_t field_30:64;
	uint64_t field_31:64;
	uint8_t field_32:8;
	uint32_t field_33:16;
	uint32_t field_34:16;
} tuple_7;

typedef struct {
	uint32_t field_35:16;
	uint64_t field_36:48;
	uint64_t field_37:48;
	uint32_t field_38:16;
} tuple_8;

typedef struct {
	uint32_t field_39:16;
	uint8_t field_40:8;
} tuple_9;

//Control

void ingress()
{
	_ingress_port_mapping_0_5763316();
	_ingress_port_properties_0_5763369();
	_validate_outer_ethernet_0_5763871();
	if (action_run == 5667633) {

	} else {
		if (hdr.ipv4.isValid) {
			_validate_outer_ipv4_packet_5764101();
		} else {
			if (hdr.ipv6.isValid) {
				_validate_outer_ipv6_packet_5764247();
			} else {
				if (hdr.mpls[0].isValid) {
					_validate_mpls_packet_5764437();
				}
			}
		}

	}
	_switch_config_params_0_5668845();
	_port_vlan_mapping_0_5764924();
	if ((meta.ingress_metadata.port_type == 0)
	    && (meta.l2_metadata.stp_group != 0)) {
		_spanning_tree_0_5765071();
	}
	if (((meta.ingress_metadata.bypass_lookups & 8) == 0)) {
		if ((meta.qos_metadata.trust_dscp == 1)) {
			_ingress_qos_map_dscp_0_5765257();
		} else {
			if ((meta.qos_metadata.trust_pcp == 1)) {
				_ingress_qos_map_pcp_0_5765341();
			}
		}
	}
	if ((meta.ingress_metadata.port_type == 0)
	    && (meta.security_metadata.ipsg_enabled == 1)) {
		_ipsg_0_5765450();
		if (action_run == 5669548) {
			_ipsg_permit_special_0_5765540();

		}
	}
	if (!hdr.int_header.isValid) {
		_int_source_0_5766147();
	} else {
		_int_terminate_0_5766284();
		_int_sink_update_outer_0_5766058();

	}
	_sflow_ingress_0_5766625();
	_sflow_ing_take_sample_0_5766498();
	if ((meta.ingress_metadata.port_type != 0)) {
		_fabric_ingress_dst_lkp_5768505();
		if ((meta.ingress_metadata.port_type == 1)) {
			if (hdr.fabric_header_multicast.isValid) {
				_fabric_ingress_src_lkp_5768584();
			}
			if ((meta.tunnel_metadata.tunnel_terminate == 0)) {
				_native_packet_over_fabric_5672707();
			}

		}

	}
	if ((meta.tunnel_metadata.ingress_tunnel_type != 0)) {
		_outer_rmac_0_5767703();
		if (action_run == 5671172) {
			if (hdr.ipv4.isValid) {
				_outer_ipv4_multicast_5769871();
				if (action_run == 5673694) {
					_outer_ipv4_multicast_star_g_5769978();

				}
			} else {
				if (hdr.ipv6.isValid) {
					_outer_ipv6_multicast_5770295();
					if (action_run == 5674104) {
						_outer_ipv6_multicast_star_g_5770402
						    ();

					}
				}
			}

		} else {
			if (hdr.ipv4.isValid) {
				_ipv4_src_vtep_5768891();
				if (action_run == 5672846) {
					_ipv4_dest_vtep_5768802();

				}
			} else {
				if (hdr.ipv6.isValid) {
					_ipv6_src_vtep_5769141();
					if (action_run == 5673084) {
						_ipv6_dest_vtep_5769052();

					}
				} else {
					if (hdr.mpls[0].isValid) {
						_mpls_5769538();
					}
				}
			}

		}
	}
	if ((meta.tunnel_metadata.tunnel_terminate == 1)
	    || (meta.multicast_metadata.outer_mcast_route_hit == 1)
	    && (meta.multicast_metadata.outer_mcast_mode == 1)
	    && (meta.multicast_metadata.mcast_rpf_group == 0)
	    || (meta.multicast_metadata.outer_mcast_mode == 2)
	    && (meta.multicast_metadata.mcast_rpf_group != 0)) {
		_tunnel_0_5767775();
		if (action_run == 5671208) {
			_tunnel_lookup_miss_2_5671974();

		}
	} else {
		_adjust_lkp_fields_0_5671707();
	}
	if ((meta.ingress_metadata.port_type == 0)) {
		_storm_control_0_5770554();
	}
	if ((meta.ingress_metadata.port_type != 1)) {
		if (!hdr.mpls[0].isValid && (meta.l3_metadata.fib_hit == 1)) {
			if (((meta.ingress_metadata.bypass_lookups & 64) == 0)
			    && (meta.ingress_metadata.drop_flag == 0)) {
				_validate_packet_0_5770785();
			}
			_ingress_l4_src_port_0_5771064();
			_ingress_l4_dst_port_0_5771004();
			if (((meta.ingress_metadata.bypass_lookups & 128) == 0)
			    && (meta.ingress_metadata.port_type == 0)) {
				_smac_0_5771430();
			}
			if (((meta.ingress_metadata.bypass_lookups & 1) == 0)) {
				_dmac_0_5771325();
			}
			if ((meta.l3_metadata.lkp_ip_type == 0)) {
				if (((meta.ingress_metadata.
				      bypass_lookups & 4) == 0)) {
					_mac_acl_0_5771917();
				}
			} else {
				if (((meta.ingress_metadata.
				      bypass_lookups & 4) == 0)) {
					if ((meta.l3_metadata.lkp_ip_type == 1)) {
						_ip_acl_0_5772828();
					} else {
						if ((meta.l3_metadata.
						     lkp_ip_type == 2)) {
							_ipv6_acl_0_5773009();
						}
					}
				}
			}
			rmac_5763151();
			if (action_run == 5667356) {
				if ((meta.l3_metadata.lkp_ip_type == 1)) {
					if (((meta.ingress_metadata.
					      bypass_lookups & 1) == 0)) {
						_ipv4_multicast_bridge_5775182
						    ();
						if (action_run == 5678948) {
							_ipv4_multicast_bridge_star_g_5775266
							    ();

						}
					}
					if (((meta.ingress_metadata.
					      bypass_lookups & 2) == 0)
					    && (meta.multicast_metadata.
						ipv4_multicast_enabled == 1)) {
						_ipv4_multicast_route_5775404();
						if (action_run == 5679160) {
							_ipv4_multicast_route_star_g_5775614
							    ();

						}
					}

				} else {
					if ((meta.l3_metadata.lkp_ip_type == 2)) {
						if (((meta.ingress_metadata.
						      bypass_lookups & 1) ==
						     0)) {
							_ipv6_multicast_bridge_5775791
							    ();
							if (action_run ==
							    5679536) {
								_ipv6_multicast_bridge_star_g_5775874
								    ();

							}
						}
						if (((meta.ingress_metadata.
						      bypass_lookups & 2) == 0)
						    && (meta.
							multicast_metadata.ipv6_multicast_enabled
							== 1)) {
							_ipv6_multicast_route_5776012
							    ();
							if (action_run ==
							    5679748) {
								_ipv6_multicast_route_star_g_5776222
								    ();

							}
						}

					}
				}

			} else {
				if (((meta.ingress_metadata.
				      bypass_lookups & 2) == 0)) {
					if ((meta.l3_metadata.lkp_ip_type == 1)
					    && (meta.ipv4_metadata.
						ipv4_unicast_enabled == 1)) {
						_ipv4_racl_0_5773444();
						if ((meta.ipv4_metadata.
						     ipv4_urpf_mode != 0)) {
							_ipv4_urpf_0_5773669();
							if (action_run ==
							    5677480) {
								_ipv4_urpf_lpm_0_5773741
								    ();

							}
						}
						_ipv4_fib_0_5773933();
						if (action_run == 5677700) {
							_ipv4_fib_lpm_0_5774011
							    ();

						}

					} else {
						if ((meta.l3_metadata.
						     lkp_ip_type == 2)
						    && (meta.ipv6_metadata.
							ipv6_unicast_enabled ==
							1)) {
							_ipv6_racl_0_5774344();
							if ((meta.ipv6_metadata.
							     ipv6_urpf_mode !=
							     0)) {
								_ipv6_urpf_0_5774569
								    ();
								if (action_run
								    ==
								    5678344) {
									_ipv6_urpf_lpm_0_5774641
									    ();

								}
							}
							_ipv6_fib_0_5774833();
							if (action_run ==
							    5678564) {
								_ipv6_fib_lpm_0_5774911
								    ();

							}

						}
					}
					if ((meta.l3_metadata.urpf_mode == 2)
					    && (meta.l3_metadata.urpf_hit == 1)) {
						_urpf_bd_0_5775014();
					}

				}

			}
			_nat_twice_0_5776828();
			if (action_run == 5680107) {
				_nat_dst_0_5776506();
				if (action_run == 5680096) {
					_nat_src_0_5776733();
					if (action_run == 5680106) {
						_nat_flow_0_5776602();

					}

				}

			}

		}
	}
	if (((meta.ingress_metadata.bypass_lookups & 16) == 0)) {
		_meter_index_2_5776984();
	}
	if ((meta.tunnel_metadata.tunnel_terminate == 0) && hdr.ipv4.isValid
	    || (meta.tunnel_metadata.tunnel_terminate == 1)
	    && hdr.inner_ipv4.isValid) {
		_compute_ipv4_hashes_0_5777352();
	} else {
		if ((meta.tunnel_metadata.tunnel_terminate == 0)
		    && hdr.ipv6.isValid
		    || (meta.tunnel_metadata.tunnel_terminate == 1)
		    && hdr.inner_ipv6.isValid) {
			_compute_ipv6_hashes_0_5777402();
		} else {
			_compute_non_ip_hashes_0_5777451();
		}
	}
	_compute_other_hashes_0_5777500();
	if (((meta.ingress_metadata.bypass_lookups & 16) == 0)) {
		_meter_action_0_5777609();
	}
	if ((meta.ingress_metadata.port_type != 1)) {
		_ingress_bd_stats_2_5681458();
		_acl_stats_2_5681537();
		_storm_control_stats_2_5777874();
		if ((meta.ingress_metadata.bypass_lookups != 65535)) {
			_fwd_result_0_5778353();
		}
		if ((meta.nexthop_metadata.nexthop_type == 1)) {
			_ecmp_group_0_5778848();
		} else {
			_nexthop_0_5778930();
		}
		if ((meta.ingress_metadata.egress_ifindex == 65535)) {
			_bd_flood_0_5779023();
		} else {
			_lag_group_0_5779148();
		}
		if ((meta.l2_metadata.learning_enabled == 1)) {
			_learn_notify_0_5779273();
		}

	}
	_fabric_lag_0_5779404();
	_traffic_class_0_5779554();
	if ((meta.ingress_metadata.port_type != 1)) {
		if (((meta.ingress_metadata.bypass_lookups & 32) == 0)) {
			_system_acl_0_5780142();
			if ((meta.ingress_metadata.drop_flag == 1)) {
				_drop_stats_4_5683771();
			}

		}
	}
}

// Action
void NoAction_172_5667254()
{
	action_run = 5667254;

}

// Action
void NoAction_173_5667255()
{
	action_run = 5667255;

}

// Action
void NoAction_174_5667256()
{
	action_run = 5667256;

}

// Action
void NoAction_175_5667257()
{
	action_run = 5667257;

}

// Action
void NoAction_176_5667258()
{
	action_run = 5667258;

}

// Action
void NoAction_177_5667259()
{
	action_run = 5667259;

}

// Action
void NoAction_178_5667260()
{
	action_run = 5667260;

}

// Action
void NoAction_179_5667261()
{
	action_run = 5667261;

}

// Action
void NoAction_180_5667262()
{
	action_run = 5667262;

}

// Action
void NoAction_181_5667263()
{
	action_run = 5667263;

}

// Action
void NoAction_182_5667264()
{
	action_run = 5667264;

}

// Action
void NoAction_183_5667265()
{
	action_run = 5667265;

}

// Action
void NoAction_184_5667266()
{
	action_run = 5667266;

}

// Action
void NoAction_185_5667267()
{
	action_run = 5667267;

}

// Action
void NoAction_186_5667268()
{
	action_run = 5667268;

}

// Action
void NoAction_187_5667269()
{
	action_run = 5667269;

}

// Action
void NoAction_188_5667270()
{
	action_run = 5667270;

}

// Action
void NoAction_189_5667271()
{
	action_run = 5667271;

}

// Action
void NoAction_190_5667272()
{
	action_run = 5667272;

}

// Action
void NoAction_191_5667273()
{
	action_run = 5667273;

}

// Action
void NoAction_192_5667274()
{
	action_run = 5667274;

}

// Action
void NoAction_193_5667275()
{
	action_run = 5667275;

}

// Action
void NoAction_194_5667276()
{
	action_run = 5667276;

}

// Action
void NoAction_195_5667277()
{
	action_run = 5667277;

}

// Action
void NoAction_196_5667278()
{
	action_run = 5667278;

}

// Action
void NoAction_197_5667279()
{
	action_run = 5667279;

}

// Action
void NoAction_198_5667280()
{
	action_run = 5667280;

}

// Action
void NoAction_199_5667281()
{
	action_run = 5667281;

}

// Action
void NoAction_200_5667282()
{
	action_run = 5667282;

}

// Action
void NoAction_201_5667283()
{
	action_run = 5667283;

}

// Action
void NoAction_202_5667284()
{
	action_run = 5667284;

}

// Action
void NoAction_203_5667285()
{
	action_run = 5667285;

}

// Action
void NoAction_204_5667286()
{
	action_run = 5667286;

}

// Action
void NoAction_205_5667287()
{
	action_run = 5667287;

}

// Action
void NoAction_206_5667288()
{
	action_run = 5667288;

}

// Action
void NoAction_207_5667289()
{
	action_run = 5667289;

}

// Action
void NoAction_208_5667290()
{
	action_run = 5667290;

}

// Action
void NoAction_209_5667291()
{
	action_run = 5667291;

}

// Action
void NoAction_210_5667292()
{
	action_run = 5667292;

}

// Action
void NoAction_211_5667293()
{
	action_run = 5667293;

}

// Action
void NoAction_212_5667294()
{
	action_run = 5667294;

}

// Action
void NoAction_213_5667295()
{
	action_run = 5667295;

}

// Action
void NoAction_214_5667296()
{
	action_run = 5667296;

}

// Action
void NoAction_215_5667297()
{
	action_run = 5667297;

}

// Action
void NoAction_216_5667298()
{
	action_run = 5667298;

}

// Action
void NoAction_217_5667299()
{
	action_run = 5667299;

}

// Action
void NoAction_218_5667300()
{
	action_run = 5667300;

}

// Action
void NoAction_219_5667301()
{
	action_run = 5667301;

}

// Action
void NoAction_220_5667302()
{
	action_run = 5667302;

}

// Action
void NoAction_221_5667303()
{
	action_run = 5667303;

}

// Action
void NoAction_222_5667304()
{
	action_run = 5667304;

}

// Action
void NoAction_223_5667305()
{
	action_run = 5667305;

}

// Action
void NoAction_224_5667306()
{
	action_run = 5667306;

}

// Action
void NoAction_225_5667307()
{
	action_run = 5667307;

}

// Action
void NoAction_226_5667308()
{
	action_run = 5667308;

}

// Action
void NoAction_227_5667309()
{
	action_run = 5667309;

}

// Action
void NoAction_228_5667310()
{
	action_run = 5667310;

}

// Action
void NoAction_229_5667311()
{
	action_run = 5667311;

}

// Action
void NoAction_230_5667312()
{
	action_run = 5667312;

}

// Action
void NoAction_231_5667313()
{
	action_run = 5667313;

}

// Action
void NoAction_232_5667314()
{
	action_run = 5667314;

}

// Action
void NoAction_233_5667315()
{
	action_run = 5667315;

}

// Action
void NoAction_234_5667316()
{
	action_run = 5667316;

}

// Action
void NoAction_235_5667317()
{
	action_run = 5667317;

}

// Action
void NoAction_236_5667318()
{
	action_run = 5667318;

}

// Action
void NoAction_237_5667319()
{
	action_run = 5667319;

}

// Action
void NoAction_238_5667320()
{
	action_run = 5667320;

}

// Action
void NoAction_239_5667321()
{
	action_run = 5667321;

}

// Action
void NoAction_240_5667322()
{
	action_run = 5667322;

}

// Action
void NoAction_241_5667323()
{
	action_run = 5667323;

}

// Action
void NoAction_242_5667324()
{
	action_run = 5667324;

}

// Action
void NoAction_243_5667325()
{
	action_run = 5667325;

}

// Action
void NoAction_244_5667326()
{
	action_run = 5667326;

}

// Action
void NoAction_245_5667327()
{
	action_run = 5667327;

}

// Action
void NoAction_246_5667328()
{
	action_run = 5667328;

}

// Action
void NoAction_247_5667329()
{
	action_run = 5667329;

}

// Action
void NoAction_248_5667330()
{
	action_run = 5667330;

}

// Action
void NoAction_249_5667331()
{
	action_run = 5667331;

}

// Action
void NoAction_250_5667332()
{
	action_run = 5667332;

}

// Action
void NoAction_251_5667333()
{
	action_run = 5667333;

}

// Action
void NoAction_252_5667334()
{
	action_run = 5667334;

}

// Action
void NoAction_253_5667335()
{
	action_run = 5667335;

}

// Action
void NoAction_254_5667336()
{
	action_run = 5667336;

}

// Action
void NoAction_255_5667337()
{
	action_run = 5667337;

}

// Action
void NoAction_256_5667338()
{
	action_run = 5667338;

}

// Action
void NoAction_257_5667339()
{
	action_run = 5667339;

}

// Action
void rmac_hit_0_5667340()
{
	action_run = 5667340;
	meta.l3_metadata.rmac_hit = 1;

}

// Action
void rmac_miss_0_5667356()
{
	action_run = 5667356;
	meta.l3_metadata.rmac_hit = 0;

}

// Action
void _set_ifindex_5667439(uint32_t ifindex, uint8_t port_type)
{
	action_run = 5667439;
	meta.ingress_metadata.ifindex = ifindex;
	meta.ingress_metadata.port_type = port_type;

}

// Action
void
_set_ingress_port_properties_5667465(uint32_t if_label, uint8_t qos_group,
				     uint8_t tc_qos_group, uint8_t tc,
				     uint8_t color, uint8_t trust_dscp,
				     uint8_t trust_pcp)
{
	action_run = 5667465;
	meta.acl_metadata.if_label = if_label;
	meta.qos_metadata.ingress_qos_group = qos_group;
	meta.qos_metadata.tc_qos_group = tc_qos_group;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;
	meta.qos_metadata.trust_dscp = trust_dscp;
	meta.qos_metadata.trust_pcp = trust_pcp;

}

// Action
void _malformed_outer_ethernet_packet_5667633(uint8_t drop_reason)
{
	action_run = 5667633;
	meta.ingress_metadata.drop_flag = 1;
	meta.ingress_metadata.drop_reason = drop_reason;

}

// Action
void _set_valid_outer_unicast_packet_untagged_5667657()
{
	action_run = 5667657;
	meta.l2_metadata.lkp_pkt_type = 1;
	meta.l2_metadata.lkp_mac_type = hdr.ethernet.etherType;

}

// Action
void _set_valid_outer_unicast_packet_single_tagged_5667682()
{
	action_run = 5667682;
	meta.l2_metadata.lkp_pkt_type = 1;
	meta.l2_metadata.lkp_mac_type = hdr.vlan_tag_[0].etherType;
	meta.l2_metadata.lkp_pcp = hdr.vlan_tag_[0].pcp;

}

// Action
void _set_valid_outer_unicast_packet_double_tagged_5667722()
{
	action_run = 5667722;
	meta.l2_metadata.lkp_pkt_type = 1;
	meta.l2_metadata.lkp_mac_type = hdr.vlan_tag_[1].etherType;
	meta.l2_metadata.lkp_pcp = hdr.vlan_tag_[0].pcp;

}

// Action
void _set_valid_outer_unicast_packet_qinq_tagged_5667762()
{
	action_run = 5667762;
	meta.l2_metadata.lkp_pkt_type = 1;
	meta.l2_metadata.lkp_mac_type = hdr.ethernet.etherType;
	meta.l2_metadata.lkp_pcp = hdr.vlan_tag_[0].pcp;

}

// Action
void _set_valid_outer_multicast_packet_untagged_5667799()
{
	action_run = 5667799;
	meta.l2_metadata.lkp_pkt_type = 2;
	meta.l2_metadata.lkp_mac_type = hdr.ethernet.etherType;

}

// Action
void _set_valid_outer_multicast_packet_single_tagged_5667824()
{
	action_run = 5667824;
	meta.l2_metadata.lkp_pkt_type = 2;
	meta.l2_metadata.lkp_mac_type = hdr.vlan_tag_[0].etherType;
	meta.l2_metadata.lkp_pcp = hdr.vlan_tag_[0].pcp;

}

// Action
void _set_valid_outer_multicast_packet_double_tagged_5667864()
{
	action_run = 5667864;
	meta.l2_metadata.lkp_pkt_type = 2;
	meta.l2_metadata.lkp_mac_type = hdr.vlan_tag_[1].etherType;
	meta.l2_metadata.lkp_pcp = hdr.vlan_tag_[0].pcp;

}

// Action
void _set_valid_outer_multicast_packet_qinq_tagged_5667904()
{
	action_run = 5667904;
	meta.l2_metadata.lkp_pkt_type = 2;
	meta.l2_metadata.lkp_mac_type = hdr.ethernet.etherType;
	meta.l2_metadata.lkp_pcp = hdr.vlan_tag_[0].pcp;

}

// Action
void _set_valid_outer_broadcast_packet_untagged_5667941()
{
	action_run = 5667941;
	meta.l2_metadata.lkp_pkt_type = 4;
	meta.l2_metadata.lkp_mac_type = hdr.ethernet.etherType;

}

// Action
void _set_valid_outer_broadcast_packet_single_tagged_5667966()
{
	action_run = 5667966;
	meta.l2_metadata.lkp_pkt_type = 4;
	meta.l2_metadata.lkp_mac_type = hdr.vlan_tag_[0].etherType;
	meta.l2_metadata.lkp_pcp = hdr.vlan_tag_[0].pcp;

}

// Action
void _set_valid_outer_broadcast_packet_double_tagged_5668006()
{
	action_run = 5668006;
	meta.l2_metadata.lkp_pkt_type = 4;
	meta.l2_metadata.lkp_mac_type = hdr.vlan_tag_[1].etherType;
	meta.l2_metadata.lkp_pcp = hdr.vlan_tag_[0].pcp;

}

// Action
void _set_valid_outer_broadcast_packet_qinq_tagged_5668046()
{
	action_run = 5668046;
	meta.l2_metadata.lkp_pkt_type = 4;
	meta.l2_metadata.lkp_mac_type = hdr.ethernet.etherType;
	meta.l2_metadata.lkp_pcp = hdr.vlan_tag_[0].pcp;

}

// Action
void _set_valid_outer_ipv4_packet_0_5668250()
{
	action_run = 5668250;
	meta.l3_metadata.lkp_ip_type = 1;
	meta.l3_metadata.lkp_dscp = hdr.ipv4.diffserv;
	meta.l3_metadata.lkp_ip_version = hdr.ipv4.version;

}

// Action
void _set_malformed_outer_ipv4_packet_0_5668284(uint8_t drop_reason)
{
	action_run = 5668284;
	meta.ingress_metadata.drop_flag = 1;
	meta.ingress_metadata.drop_reason = drop_reason;

}

// Action
void _set_valid_outer_ipv6_packet_0_5668385()
{
	action_run = 5668385;
	meta.l3_metadata.lkp_ip_type = 2;
	meta.l3_metadata.lkp_dscp = hdr.ipv6.trafficClass;
	meta.l3_metadata.lkp_ip_version = hdr.ipv6.version;

}

// Action
void _set_malformed_outer_ipv6_packet_0_5668419(uint8_t drop_reason)
{
	action_run = 5668419;
	meta.ingress_metadata.drop_flag = 1;
	meta.ingress_metadata.drop_reason = drop_reason;

}

// Action
void _set_valid_mpls_label1_0_5668520()
{
	action_run = 5668520;
	meta.tunnel_metadata.mpls_label = hdr.mpls[0].label;
	meta.tunnel_metadata.mpls_exp = hdr.mpls[0].exp;

}

// Action
void _set_valid_mpls_label2_0_5668554()
{
	action_run = 5668554;
	meta.tunnel_metadata.mpls_label = hdr.mpls[1].label;
	meta.tunnel_metadata.mpls_exp = hdr.mpls[1].exp;

}

// Action
void _set_valid_mpls_label3_0_5668588()
{
	action_run = 5668588;
	meta.tunnel_metadata.mpls_label = hdr.mpls[2].label;
	meta.tunnel_metadata.mpls_exp = hdr.mpls[2].exp;

}

// Action
void _set_config_parameters_5668783(uint8_t enable_dod)
{
	action_run = 5668783;
	intrinsic_metadata.deflect_on_drop = enable_dod;
	meta.i2e_metadata.ingress_tstamp =
	    (uint32_t) intrinsic_metadata.ingress_global_timestamp;
	meta.ingress_metadata.ingress_port = standard_metadata.ingress_port;
	meta.l2_metadata.same_if_check = meta.ingress_metadata.ifindex;
	standard_metadata.egress_spec = 511;
	//random

	uint64_t t6ec66d67_8ef8_44d0_b57e_d99e1e5a298f;
	klee_make_symbolic(&t6ec66d67_8ef8_44d0_b57e_d99e1e5a298f,
			   sizeof(t6ec66d67_8ef8_44d0_b57e_d99e1e5a298f),
			   "t6ec66d67_8ef8_44d0_b57e_d99e1e5a298f");
	meta.ingress_metadata.sflow_take_sample =
	    t6ec66d67_8ef8_44d0_b57e_d99e1e5a298f;

	klee_assume(meta.ingress_metadata.sflow_take_sample > 0
		    && meta.ingress_metadata.sflow_take_sample < 2147483647);

}

// Action
void
_set_bd_properties_5668883(uint32_t bd, uint32_t vrf, uint32_t stp_group,
			   uint8_t learning_enabled, uint32_t bd_label,
			   uint32_t stats_idx, uint32_t rmac_group,
			   uint8_t ipv4_unicast_enabled,
			   uint8_t ipv6_unicast_enabled,
			   uint8_t ipv4_urpf_mode, uint8_t ipv6_urpf_mode,
			   uint8_t igmp_snooping_enabled,
			   uint8_t mld_snooping_enabled,
			   uint8_t ipv4_multicast_enabled,
			   uint8_t ipv6_multicast_enabled,
			   uint32_t mrpf_group, uint32_t ipv4_mcast_key,
			   uint8_t ipv4_mcast_key_type,
			   uint32_t ipv6_mcast_key, uint8_t ipv6_mcast_key_type)
{
	action_run = 5668883;
	meta.ingress_metadata.bd = bd;
	meta.ingress_metadata.outer_bd = bd;
	meta.acl_metadata.bd_label = bd_label;
	meta.l2_metadata.stp_group = stp_group;
	meta.l2_metadata.bd_stats_idx = stats_idx;
	meta.l2_metadata.learning_enabled = learning_enabled;
	meta.l3_metadata.vrf = vrf;
	meta.ipv4_metadata.ipv4_unicast_enabled = ipv4_unicast_enabled;
	meta.ipv6_metadata.ipv6_unicast_enabled = ipv6_unicast_enabled;
	meta.ipv4_metadata.ipv4_urpf_mode = ipv4_urpf_mode;
	meta.ipv6_metadata.ipv6_urpf_mode = ipv6_urpf_mode;
	meta.l3_metadata.rmac_group = rmac_group;
	meta.multicast_metadata.igmp_snooping_enabled = igmp_snooping_enabled;
	meta.multicast_metadata.mld_snooping_enabled = mld_snooping_enabled;
	meta.multicast_metadata.ipv4_multicast_enabled = ipv4_multicast_enabled;
	meta.multicast_metadata.ipv6_multicast_enabled = ipv6_multicast_enabled;
	meta.multicast_metadata.bd_mrpf_group = mrpf_group;
	meta.multicast_metadata.ipv4_mcast_key_type = ipv4_mcast_key_type;
	meta.multicast_metadata.ipv4_mcast_key = ipv4_mcast_key;
	meta.multicast_metadata.ipv6_mcast_key_type = ipv6_mcast_key_type;
	meta.multicast_metadata.ipv6_mcast_key = ipv6_mcast_key;

}

// Action
void _port_vlan_mapping_miss_5669060()
{
	action_run = 5669060;
	meta.l2_metadata.port_vlan_mapping_miss = 1;

}

// Action
void _set_stp_state_5669191(uint8_t stp_state)
{
	action_run = 5669191;
	meta.l2_metadata.stp_state = stp_state;

}

// Action
void _nop_38_5669270()
{
	action_run = 5669270;

}

// Action
void _nop_39_5669280()
{
	action_run = 5669280;

}

// Action
void _set_ingress_tc_5669281(uint8_t tc)
{
	action_run = 5669281;
	meta.qos_metadata.lkp_tc = tc;

}

// Action
void _set_ingress_tc_2_5669299(uint8_t tc)
{
	action_run = 5669299;
	meta.qos_metadata.lkp_tc = tc;

}

// Action
void _set_ingress_color_5669312(uint8_t color)
{
	action_run = 5669312;
	meta.meter_metadata.packet_color = color;

}

// Action
void _set_ingress_color_2_5669330(uint8_t color)
{
	action_run = 5669330;
	meta.meter_metadata.packet_color = color;

}

// Action
void _set_ingress_tc_and_color_5669343(uint8_t tc, uint8_t color)
{
	action_run = 5669343;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;

}

// Action
void _set_ingress_tc_and_color_2_5669369(uint8_t tc, uint8_t color)
{
	action_run = 5669369;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;

}

// Action
void _on_miss_9_5669548()
{
	action_run = 5669548;

}

// Action
void _ipsg_miss_5669558()
{
	action_run = 5669558;
	meta.security_metadata.ipsg_check_fail = 1;

}

// Action
void _int_sink_update_vxlan_gpe_v4_5669726()
{
	action_run = 5669726;
	hdr.vxlan_gpe.next_proto = hdr.vxlan_gpe_int_header.next_proto;
	hdr.vxlan_gpe_int_header.isValid = 0;
	hdr.ipv4.totalLen =
	    hdr.ipv4.totalLen - meta.int_metadata.insert_byte_cnt;
	hdr.udp.length_ = hdr.udp.length_ - meta.int_metadata.insert_byte_cnt;

}

// Action
void _nop_40_5669781()
{
	action_run = 5669781;

}

// Action
void _int_set_src_5669791()
{
	action_run = 5669791;
	meta.int_metadata_i2e.source = 1;

}

// Action
void _int_set_no_src_5669807()
{
	action_run = 5669807;
	meta.int_metadata_i2e.source = 0;

}

// Action
void _int_sink_gpe_5742384(uint32_t mirror_id)
{
	action_run = 5742384;
	meta.int_metadata.insert_byte_cnt =
	    meta.int_metadata.gpe_int_hdr_len << 2;
	meta.int_metadata_i2e.sink = 1;
	meta.i2e_metadata.mirror_session_id = (uint32_t) mirror_id;
	hdr.int_header.isValid = 0;
	hdr.int_val[0].isValid = 0;
	hdr.int_val[1].isValid = 0;
	hdr.int_val[2].isValid = 0;
	hdr.int_val[3].isValid = 0;
	hdr.int_val[4].isValid = 0;
	hdr.int_val[5].isValid = 0;
	hdr.int_val[6].isValid = 0;
	hdr.int_val[7].isValid = 0;
	hdr.int_val[8].isValid = 0;
	hdr.int_val[9].isValid = 0;
	hdr.int_val[10].isValid = 0;
	hdr.int_val[11].isValid = 0;
	hdr.int_val[12].isValid = 0;
	hdr.int_val[13].isValid = 0;
	hdr.int_val[14].isValid = 0;
	hdr.int_val[15].isValid = 0;
	hdr.int_val[16].isValid = 0;
	hdr.int_val[17].isValid = 0;
	hdr.int_val[18].isValid = 0;
	hdr.int_val[19].isValid = 0;
	hdr.int_val[20].isValid = 0;
	hdr.int_val[21].isValid = 0;
	hdr.int_val[22].isValid = 0;
	hdr.int_val[23].isValid = 0;

}

// Action
void _int_no_sink_5670156()
{
	action_run = 5670156;
	meta.int_metadata_i2e.sink = 0;

}

// Action
void _nop_41_5670516()
{
	action_run = 5670516;

}

// Action
void _sflow_ing_pkt_to_cpu_5743245(uint32_t sflow_i2e_mirror_id)
{
	action_run = 5743245;
	meta.i2e_metadata.mirror_session_id = (uint32_t) sflow_i2e_mirror_id;

}

// Action
void _nop_42_5670658()
{
	action_run = 5670658;

}

// Action
void _sflow_ing_session_enable_5670675(uint32_t rate_thr, uint32_t session_id)
{
	action_run = 5670675;
	meta.ingress_metadata.sflow_take_sample =
	    rate_thr + meta.ingress_metadata.sflow_take_sample;
	meta.sflow_metadata.sflow_session_id = session_id;

}

// Action
void _non_ip_lkp_5670809()
{
	action_run = 5670809;
	meta.l2_metadata.lkp_mac_sa = hdr.ethernet.srcAddr;
	meta.l2_metadata.lkp_mac_da = hdr.ethernet.dstAddr;

}

// Action
void _non_ip_lkp_2_5670837()
{
	action_run = 5670837;
	meta.l2_metadata.lkp_mac_sa = hdr.ethernet.srcAddr;
	meta.l2_metadata.lkp_mac_da = hdr.ethernet.dstAddr;

}

// Action
void _ipv4_lkp_5670858()
{
	action_run = 5670858;
	meta.l2_metadata.lkp_mac_sa = hdr.ethernet.srcAddr;
	meta.l2_metadata.lkp_mac_da = hdr.ethernet.dstAddr;
	meta.ipv4_metadata.lkp_ipv4_sa = hdr.ipv4.srcAddr;
	meta.ipv4_metadata.lkp_ipv4_da = hdr.ipv4.dstAddr;
	meta.l3_metadata.lkp_ip_proto = hdr.ipv4.protocol;
	meta.l3_metadata.lkp_ip_ttl = hdr.ipv4.ttl;
	meta.l3_metadata.lkp_l4_sport = meta.l3_metadata.lkp_outer_l4_sport;
	meta.l3_metadata.lkp_l4_dport = meta.l3_metadata.lkp_outer_l4_dport;

}

// Action
void _ipv4_lkp_2_5670940()
{
	action_run = 5670940;
	meta.l2_metadata.lkp_mac_sa = hdr.ethernet.srcAddr;
	meta.l2_metadata.lkp_mac_da = hdr.ethernet.dstAddr;
	meta.ipv4_metadata.lkp_ipv4_sa = hdr.ipv4.srcAddr;
	meta.ipv4_metadata.lkp_ipv4_da = hdr.ipv4.dstAddr;
	meta.l3_metadata.lkp_ip_proto = hdr.ipv4.protocol;
	meta.l3_metadata.lkp_ip_ttl = hdr.ipv4.ttl;
	meta.l3_metadata.lkp_l4_sport = meta.l3_metadata.lkp_outer_l4_sport;
	meta.l3_metadata.lkp_l4_dport = meta.l3_metadata.lkp_outer_l4_dport;

}

// Action
void _ipv6_lkp_5671015()
{
	action_run = 5671015;
	meta.l2_metadata.lkp_mac_sa = hdr.ethernet.srcAddr;
	meta.l2_metadata.lkp_mac_da = hdr.ethernet.dstAddr;
	meta.ipv6_metadata.lkp_ipv6_sa = hdr.ipv6.srcAddr;
	meta.ipv6_metadata.lkp_ipv6_da = hdr.ipv6.dstAddr;
	meta.l3_metadata.lkp_ip_proto = hdr.ipv6.nextHdr;
	meta.l3_metadata.lkp_ip_ttl = hdr.ipv6.hopLimit;
	meta.l3_metadata.lkp_l4_sport = meta.l3_metadata.lkp_outer_l4_sport;
	meta.l3_metadata.lkp_l4_dport = meta.l3_metadata.lkp_outer_l4_dport;

}

// Action
void _ipv6_lkp_2_5671097()
{
	action_run = 5671097;
	meta.l2_metadata.lkp_mac_sa = hdr.ethernet.srcAddr;
	meta.l2_metadata.lkp_mac_da = hdr.ethernet.dstAddr;
	meta.ipv6_metadata.lkp_ipv6_sa = hdr.ipv6.srcAddr;
	meta.ipv6_metadata.lkp_ipv6_da = hdr.ipv6.dstAddr;
	meta.l3_metadata.lkp_ip_proto = hdr.ipv6.nextHdr;
	meta.l3_metadata.lkp_ip_ttl = hdr.ipv6.hopLimit;
	meta.l3_metadata.lkp_l4_sport = meta.l3_metadata.lkp_outer_l4_sport;
	meta.l3_metadata.lkp_l4_dport = meta.l3_metadata.lkp_outer_l4_dport;

}

// Action
void _on_miss_10_5671172()
{
	action_run = 5671172;

}

// Action
void _outer_rmac_hit_5671182()
{
	action_run = 5671182;
	meta.l3_metadata.rmac_hit = 1;

}

// Action
void _nop_43_5671198()
{
	action_run = 5671198;

}

// Action
void _tunnel_lookup_miss_5671208()
{
	action_run = 5671208;

}

// Action
void
_terminate_tunnel_inner_non_ip_5671218(uint32_t bd, uint32_t bd_label,
				       uint32_t stats_idx)
{
	action_run = 5671218;
	meta.tunnel_metadata.tunnel_terminate = 1;
	meta.ingress_metadata.bd = bd;
	meta.acl_metadata.bd_label = bd_label;
	meta.l2_metadata.bd_stats_idx = stats_idx;
	meta.l3_metadata.lkp_ip_type = 0;
	meta.l2_metadata.lkp_mac_type = hdr.inner_ethernet.etherType;

}

// Action
void
_terminate_tunnel_inner_ethernet_ipv4_5671273(uint32_t bd, uint32_t vrf,
					      uint32_t rmac_group,
					      uint32_t bd_label,
					      uint8_t ipv4_unicast_enabled,
					      uint8_t ipv4_urpf_mode,
					      uint8_t igmp_snooping_enabled,
					      uint32_t stats_idx,
					      uint8_t ipv4_multicast_enabled,
					      uint32_t mrpf_group)
{
	action_run = 5671273;
	meta.tunnel_metadata.tunnel_terminate = 1;
	meta.ingress_metadata.bd = bd;
	meta.l3_metadata.vrf = vrf;
	meta.ipv4_metadata.ipv4_unicast_enabled = ipv4_unicast_enabled;
	meta.ipv4_metadata.ipv4_urpf_mode = ipv4_urpf_mode;
	meta.l3_metadata.rmac_group = rmac_group;
	meta.acl_metadata.bd_label = bd_label;
	meta.l2_metadata.bd_stats_idx = stats_idx;
	meta.l3_metadata.lkp_ip_type = 1;
	meta.l2_metadata.lkp_mac_type = hdr.inner_ethernet.etherType;
	meta.l3_metadata.lkp_ip_version = hdr.inner_ipv4.version;
	meta.multicast_metadata.igmp_snooping_enabled = igmp_snooping_enabled;
	meta.multicast_metadata.ipv4_multicast_enabled = ipv4_multicast_enabled;
	meta.multicast_metadata.bd_mrpf_group = mrpf_group;

}

// Action
void
_terminate_tunnel_inner_ipv4_5671393(uint32_t vrf, uint32_t rmac_group,
				     uint8_t ipv4_urpf_mode,
				     uint8_t ipv4_unicast_enabled,
				     uint8_t ipv4_multicast_enabled,
				     uint32_t mrpf_group)
{
	action_run = 5671393;
	meta.tunnel_metadata.tunnel_terminate = 1;
	meta.l3_metadata.vrf = vrf;
	meta.ipv4_metadata.ipv4_unicast_enabled = ipv4_unicast_enabled;
	meta.ipv4_metadata.ipv4_urpf_mode = ipv4_urpf_mode;
	meta.l3_metadata.rmac_group = rmac_group;
	meta.l2_metadata.lkp_mac_sa = hdr.ethernet.srcAddr;
	meta.l2_metadata.lkp_mac_da = hdr.ethernet.dstAddr;
	meta.l3_metadata.lkp_ip_type = 1;
	meta.l3_metadata.lkp_ip_version = hdr.inner_ipv4.version;
	meta.multicast_metadata.bd_mrpf_group = mrpf_group;
	meta.multicast_metadata.ipv4_multicast_enabled = ipv4_multicast_enabled;

}

// Action
void
_terminate_tunnel_inner_ethernet_ipv6_5671490(uint32_t bd, uint32_t vrf,
					      uint32_t rmac_group,
					      uint32_t bd_label,
					      uint8_t ipv6_unicast_enabled,
					      uint8_t ipv6_urpf_mode,
					      uint8_t mld_snooping_enabled,
					      uint32_t stats_idx,
					      uint8_t ipv6_multicast_enabled,
					      uint32_t mrpf_group)
{
	action_run = 5671490;
	meta.tunnel_metadata.tunnel_terminate = 1;
	meta.ingress_metadata.bd = bd;
	meta.l3_metadata.vrf = vrf;
	meta.ipv6_metadata.ipv6_unicast_enabled = ipv6_unicast_enabled;
	meta.ipv6_metadata.ipv6_urpf_mode = ipv6_urpf_mode;
	meta.l3_metadata.rmac_group = rmac_group;
	meta.acl_metadata.bd_label = bd_label;
	meta.l2_metadata.bd_stats_idx = stats_idx;
	meta.l3_metadata.lkp_ip_type = 2;
	meta.l2_metadata.lkp_mac_type = hdr.inner_ethernet.etherType;
	meta.l3_metadata.lkp_ip_version = hdr.inner_ipv6.version;
	meta.multicast_metadata.bd_mrpf_group = mrpf_group;
	meta.multicast_metadata.ipv6_multicast_enabled = ipv6_multicast_enabled;
	meta.multicast_metadata.mld_snooping_enabled = mld_snooping_enabled;

}

// Action
void
_terminate_tunnel_inner_ipv6_5671610(uint32_t vrf, uint32_t rmac_group,
				     uint8_t ipv6_unicast_enabled,
				     uint8_t ipv6_urpf_mode,
				     uint8_t ipv6_multicast_enabled,
				     uint32_t mrpf_group)
{
	action_run = 5671610;
	meta.tunnel_metadata.tunnel_terminate = 1;
	meta.l3_metadata.vrf = vrf;
	meta.ipv6_metadata.ipv6_unicast_enabled = ipv6_unicast_enabled;
	meta.ipv6_metadata.ipv6_urpf_mode = ipv6_urpf_mode;
	meta.l3_metadata.rmac_group = rmac_group;
	meta.l2_metadata.lkp_mac_sa = hdr.ethernet.srcAddr;
	meta.l2_metadata.lkp_mac_da = hdr.ethernet.dstAddr;
	meta.l3_metadata.lkp_ip_type = 2;
	meta.l3_metadata.lkp_ip_version = hdr.inner_ipv6.version;
	meta.multicast_metadata.bd_mrpf_group = mrpf_group;
	meta.multicast_metadata.ipv6_multicast_enabled = ipv6_multicast_enabled;

}

// Action
void _nop_44_5672049()
{
	action_run = 5672049;

}

// Action
void _nop_45_5672059()
{
	action_run = 5672059;

}

// Action
void _terminate_cpu_packet_0_5672060()
{
	action_run = 5672060;
	standard_metadata.egress_spec =
	    (uint32_t) hdr.fabric_header.dstPortOrGroup;
	meta.egress_metadata.bypass = hdr.fabric_header_cpu.txBypass;
	intrinsic_metadata.mcast_grp = hdr.fabric_header_cpu.mcast_grp;
	hdr.ethernet.etherType = hdr.fabric_payload_header.etherType;
	hdr.fabric_header.isValid = 0;
	hdr.fabric_header_cpu.isValid = 0;
	hdr.fabric_payload_header.isValid = 0;

}

// Action
void _switch_fabric_unicast_packet_0_5672130()
{
	action_run = 5672130;
	meta.fabric_metadata.fabric_header_present = 1;
	meta.fabric_metadata.dst_device = hdr.fabric_header.dstDevice;
	meta.fabric_metadata.dst_port = hdr.fabric_header.dstPortOrGroup;

}

// Action
void _terminate_fabric_unicast_packet_0_5672164()
{
	action_run = 5672164;
	standard_metadata.egress_spec =
	    (uint32_t) hdr.fabric_header.dstPortOrGroup;
	meta.tunnel_metadata.tunnel_terminate =
	    hdr.fabric_header_unicast.tunnelTerminate;
	meta.tunnel_metadata.ingress_tunnel_type =
	    hdr.fabric_header_unicast.ingressTunnelType;
	meta.l3_metadata.nexthop_index = hdr.fabric_header_unicast.nexthopIndex;
	meta.l3_metadata.routed = hdr.fabric_header_unicast.routed;
	meta.l3_metadata.outer_routed = hdr.fabric_header_unicast.outerRouted;
	hdr.ethernet.etherType = hdr.fabric_payload_header.etherType;
	hdr.fabric_header.isValid = 0;
	hdr.fabric_header_unicast.isValid = 0;
	hdr.fabric_payload_header.isValid = 0;

}

// Action
void _switch_fabric_multicast_packet_0_5672261()
{
	action_run = 5672261;
	meta.fabric_metadata.fabric_header_present = 1;
	intrinsic_metadata.mcast_grp = hdr.fabric_header.dstPortOrGroup;

}

// Action
void _terminate_fabric_multicast_packet_0_5672286()
{
	action_run = 5672286;
	meta.tunnel_metadata.tunnel_terminate =
	    hdr.fabric_header_multicast.tunnelTerminate;
	meta.tunnel_metadata.ingress_tunnel_type =
	    hdr.fabric_header_multicast.ingressTunnelType;
	meta.l3_metadata.nexthop_index = 0;
	meta.l3_metadata.routed = hdr.fabric_header_multicast.routed;
	meta.l3_metadata.outer_routed = hdr.fabric_header_multicast.outerRouted;
	intrinsic_metadata.mcast_grp =
	    hdr.fabric_header_multicast.mcastGrp;
	hdr.ethernet.etherType = hdr.fabric_payload_header.etherType;
	hdr.fabric_header.isValid = 0;
	hdr.fabric_header_multicast.isValid = 0;
	hdr.fabric_payload_header.isValid = 0;

}

// Action
void _set_ingress_ifindex_properties_0_5672380()
{
	action_run = 5672380;

}

// Action
void _non_ip_over_fabric_0_5672390()
{
	action_run = 5672390;
	meta.l2_metadata.lkp_mac_sa = hdr.ethernet.srcAddr;
	meta.l2_metadata.lkp_mac_da = hdr.ethernet.dstAddr;
	meta.l2_metadata.lkp_mac_type = hdr.ethernet.etherType;

}

// Action
void _ipv4_over_fabric_0_5672427()
{
	action_run = 5672427;
	meta.l2_metadata.lkp_mac_sa = hdr.ethernet.srcAddr;
	meta.l2_metadata.lkp_mac_da = hdr.ethernet.dstAddr;
	meta.ipv4_metadata.lkp_ipv4_sa = hdr.ipv4.srcAddr;
	meta.ipv4_metadata.lkp_ipv4_da = hdr.ipv4.dstAddr;
	meta.l3_metadata.lkp_ip_proto = hdr.ipv4.protocol;
	meta.l3_metadata.lkp_l4_sport = meta.l3_metadata.lkp_outer_l4_sport;
	meta.l3_metadata.lkp_l4_dport = meta.l3_metadata.lkp_outer_l4_dport;

}

// Action
void _ipv6_over_fabric_0_5672500()
{
	action_run = 5672500;
	meta.l2_metadata.lkp_mac_sa = hdr.ethernet.srcAddr;
	meta.l2_metadata.lkp_mac_da = hdr.ethernet.dstAddr;
	meta.ipv6_metadata.lkp_ipv6_sa = hdr.ipv6.srcAddr;
	meta.ipv6_metadata.lkp_ipv6_da = hdr.ipv6.dstAddr;
	meta.l3_metadata.lkp_ip_proto = hdr.ipv6.nextHdr;
	meta.l3_metadata.lkp_l4_sport = meta.l3_metadata.lkp_outer_l4_sport;
	meta.l3_metadata.lkp_l4_dport = meta.l3_metadata.lkp_outer_l4_dport;

}

// Action
void _nop_46_5672786()
{
	action_run = 5672786;

}

// Action
void _set_tunnel_termination_flag_1_5672796()
{
	action_run = 5672796;
	meta.tunnel_metadata.tunnel_terminate = 1;

}

// Action
void _set_tunnel_vni_and_termination_flag_1_5672812(uint32_t tunnel_vni)
{
	action_run = 5672812;
	meta.tunnel_metadata.tunnel_vni = tunnel_vni;
	meta.tunnel_metadata.tunnel_terminate = 1;

}

// Action
void _on_miss_11_5672836()
{
	action_run = 5672836;

}

// Action
void _src_vtep_hit_1_5672846(uint32_t ifindex)
{
	action_run = 5672846;
	meta.ingress_metadata.ifindex = ifindex;

}

// Action
void _nop_47_5673024()
{
	action_run = 5673024;

}

// Action
void _set_tunnel_termination_flag_2_5673034()
{
	action_run = 5673034;
	meta.tunnel_metadata.tunnel_terminate = 1;

}

// Action
void _set_tunnel_vni_and_termination_flag_2_5673050(uint32_t tunnel_vni)
{
	action_run = 5673050;
	meta.tunnel_metadata.tunnel_vni = tunnel_vni;
	meta.tunnel_metadata.tunnel_terminate = 1;

}

// Action
void _on_miss_12_5673074()
{
	action_run = 5673074;

}

// Action
void _src_vtep_hit_2_5673084(uint32_t ifindex)
{
	action_run = 5673084;
	meta.ingress_metadata.ifindex = ifindex;

}

// Action
void _terminate_eompls_0_5673262(uint32_t bd, uint8_t tunnel_type)
{
	action_run = 5673262;
	meta.tunnel_metadata.tunnel_terminate = 1;
	meta.tunnel_metadata.ingress_tunnel_type = tunnel_type;
	meta.ingress_metadata.bd = bd;
	meta.l2_metadata.lkp_mac_type = hdr.inner_ethernet.etherType;

}

// Action
void _terminate_vpls_0_5673303(uint32_t bd, uint8_t tunnel_type)
{
	action_run = 5673303;
	meta.tunnel_metadata.tunnel_terminate = 1;
	meta.tunnel_metadata.ingress_tunnel_type = tunnel_type;
	meta.ingress_metadata.bd = bd;
	meta.l2_metadata.lkp_mac_type = hdr.inner_ethernet.etherType;

}

// Action
void _terminate_ipv4_over_mpls_0_5673344(uint32_t vrf, uint8_t tunnel_type)
{
	action_run = 5673344;
	meta.tunnel_metadata.tunnel_terminate = 1;
	meta.tunnel_metadata.ingress_tunnel_type = tunnel_type;
	meta.l3_metadata.vrf = vrf;
	meta.l2_metadata.lkp_mac_sa = hdr.ethernet.srcAddr;
	meta.l2_metadata.lkp_mac_da = hdr.ethernet.dstAddr;
	meta.l3_metadata.lkp_ip_type = 1;
	meta.l2_metadata.lkp_mac_type = hdr.inner_ethernet.etherType;
	meta.l3_metadata.lkp_ip_version = hdr.inner_ipv4.version;

}

// Action
void _terminate_ipv6_over_mpls_0_5673418(uint32_t vrf, uint8_t tunnel_type)
{
	action_run = 5673418;
	meta.tunnel_metadata.tunnel_terminate = 1;
	meta.tunnel_metadata.ingress_tunnel_type = tunnel_type;
	meta.l3_metadata.vrf = vrf;
	meta.l2_metadata.lkp_mac_sa = hdr.ethernet.srcAddr;
	meta.l2_metadata.lkp_mac_da = hdr.ethernet.dstAddr;
	meta.l3_metadata.lkp_ip_type = 2;
	meta.l2_metadata.lkp_mac_type = hdr.inner_ethernet.etherType;
	meta.l3_metadata.lkp_ip_version = hdr.inner_ipv6.version;

}

// Action
void _terminate_pw_0_5673492(uint32_t ifindex)
{
	action_run = 5673492;
	meta.ingress_metadata.egress_ifindex = ifindex;
	meta.l2_metadata.lkp_mac_sa = hdr.ethernet.srcAddr;
	meta.l2_metadata.lkp_mac_da = hdr.ethernet.dstAddr;

}

// Action
void _forward_mpls_0_5673528(uint32_t nexthop_index)
{
	action_run = 5673528;
	meta.l3_metadata.fib_nexthop = nexthop_index;
	meta.l3_metadata.fib_nexthop_type = 0;
	meta.l3_metadata.fib_hit = 1;
	meta.l2_metadata.lkp_mac_sa = hdr.ethernet.srcAddr;
	meta.l2_metadata.lkp_mac_da = hdr.ethernet.dstAddr;

}

// Action
void _nop_48_5673683()
{
	action_run = 5673683;

}

// Action
void _nop_49_5673693()
{
	action_run = 5673693;

}

// Action
void _on_miss_13_5673694()
{
	action_run = 5673694;

}

// Action
void
_outer_multicast_route_s_g_hit_1_5673704(uint32_t mc_index,
					 uint32_t mcast_rpf_group)
{
	action_run = 5673704;
	intrinsic_metadata.mcast_grp = mc_index;
	meta.multicast_metadata.outer_mcast_route_hit = 1;
	meta.multicast_metadata.mcast_rpf_group =
	    (mcast_rpf_group ^ meta.multicast_metadata.bd_mrpf_group);
	meta.fabric_metadata.dst_device = 127;

}

// Action
void _outer_multicast_bridge_s_g_hit_1_5673747(uint32_t mc_index)
{
	action_run = 5673747;
	intrinsic_metadata.mcast_grp = mc_index;
	meta.tunnel_metadata.tunnel_terminate = 1;
	meta.fabric_metadata.dst_device = 127;

}

// Action
void
_outer_multicast_route_sm_star_g_hit_1_5673777(uint32_t mc_index,
					       uint32_t mcast_rpf_group)
{
	action_run = 5673777;
	meta.multicast_metadata.outer_mcast_mode = 1;
	intrinsic_metadata.mcast_grp = mc_index;
	meta.multicast_metadata.outer_mcast_route_hit = 1;
	meta.multicast_metadata.mcast_rpf_group =
	    (mcast_rpf_group ^ meta.multicast_metadata.bd_mrpf_group);
	meta.fabric_metadata.dst_device = 127;

}

// Action
void
_outer_multicast_route_bidir_star_g_hit_1_5673826(uint32_t mc_index,
						  uint32_t mcast_rpf_group)
{
	action_run = 5673826;
	meta.multicast_metadata.outer_mcast_mode = 2;
	intrinsic_metadata.mcast_grp = mc_index;
	meta.multicast_metadata.outer_mcast_route_hit = 1;
	meta.multicast_metadata.mcast_rpf_group =
	    (mcast_rpf_group | meta.multicast_metadata.bd_mrpf_group);
	meta.fabric_metadata.dst_device = 127;

}

// Action
void _outer_multicast_bridge_star_g_hit_1_5673875(uint32_t mc_index)
{
	action_run = 5673875;
	intrinsic_metadata.mcast_grp = mc_index;
	meta.tunnel_metadata.tunnel_terminate = 1;
	meta.fabric_metadata.dst_device = 127;

}

// Action
void _nop_50_5674093()
{
	action_run = 5674093;

}

// Action
void _nop_51_5674103()
{
	action_run = 5674103;

}

// Action
void _on_miss_14_5674104()
{
	action_run = 5674104;

}

// Action
void
_outer_multicast_route_s_g_hit_2_5674114(uint32_t mc_index,
					 uint32_t mcast_rpf_group)
{
	action_run = 5674114;
	intrinsic_metadata.mcast_grp = mc_index;
	meta.multicast_metadata.outer_mcast_route_hit = 1;
	meta.multicast_metadata.mcast_rpf_group =
	    (mcast_rpf_group ^ meta.multicast_metadata.bd_mrpf_group);
	meta.fabric_metadata.dst_device = 127;

}

// Action
void _outer_multicast_bridge_s_g_hit_2_5674157(uint32_t mc_index)
{
	action_run = 5674157;
	intrinsic_metadata.mcast_grp = mc_index;
	meta.tunnel_metadata.tunnel_terminate = 1;
	meta.fabric_metadata.dst_device = 127;

}

// Action
void
_outer_multicast_route_sm_star_g_hit_2_5674187(uint32_t mc_index,
					       uint32_t mcast_rpf_group)
{
	action_run = 5674187;
	meta.multicast_metadata.outer_mcast_mode = 1;
	intrinsic_metadata.mcast_grp = mc_index;
	meta.multicast_metadata.outer_mcast_route_hit = 1;
	meta.multicast_metadata.mcast_rpf_group =
	    (mcast_rpf_group ^ meta.multicast_metadata.bd_mrpf_group);
	meta.fabric_metadata.dst_device = 127;

}

// Action
void
_outer_multicast_route_bidir_star_g_hit_2_5674236(uint32_t mc_index,
						  uint32_t mcast_rpf_group)
{
	action_run = 5674236;
	meta.multicast_metadata.outer_mcast_mode = 2;
	intrinsic_metadata.mcast_grp = mc_index;
	meta.multicast_metadata.outer_mcast_route_hit = 1;
	meta.multicast_metadata.mcast_rpf_group =
	    (mcast_rpf_group | meta.multicast_metadata.bd_mrpf_group);
	meta.fabric_metadata.dst_device = 127;

}

// Action
void _outer_multicast_bridge_star_g_hit_2_5674285(uint32_t mc_index)
{
	action_run = 5674285;
	intrinsic_metadata.mcast_grp = mc_index;
	meta.tunnel_metadata.tunnel_terminate = 1;
	meta.fabric_metadata.dst_device = 127;

}

// Action
void _nop_52_5674518()
{
	action_run = 5674518;

}

// Action
void _set_storm_control_meter_5674528(uint32_t meter_idx)
{
	action_run = 5674528;

	uint64_t t7fda0314_08f9_4da4_9fcf_8d4b9e05a7ca;
	klee_make_symbolic(&t7fda0314_08f9_4da4_9fcf_8d4b9e05a7ca,
			   sizeof(t7fda0314_08f9_4da4_9fcf_8d4b9e05a7ca),
			   "t7fda0314_08f9_4da4_9fcf_8d4b9e05a7ca");
	meta.meter_metadata.packet_color =
	    t7fda0314_08f9_4da4_9fcf_8d4b9e05a7ca;

	meta.meter_metadata.meter_index = (uint32_t) meter_idx;

}

// Action
void _nop_53_5674627()
{
	action_run = 5674627;

}

// Action
void _set_unicast_5674637()
{
	action_run = 5674637;
	meta.l2_metadata.lkp_pkt_type = 1;

}

// Action
void _set_unicast_and_ipv6_src_is_link_local_5674653()
{
	action_run = 5674653;
	meta.l2_metadata.lkp_pkt_type = 1;
	meta.ipv6_metadata.ipv6_src_is_link_local = 1;

}

// Action
void _set_multicast_5674675()
{
	action_run = 5674675;
	meta.l2_metadata.lkp_pkt_type = 2;
	meta.l2_metadata.bd_stats_idx = meta.l2_metadata.bd_stats_idx + 1;

}

// Action
void _set_multicast_and_ipv6_src_is_link_local_5674702()
{
	action_run = 5674702;
	meta.l2_metadata.lkp_pkt_type = 2;
	meta.ipv6_metadata.ipv6_src_is_link_local = 1;
	meta.l2_metadata.bd_stats_idx = meta.l2_metadata.bd_stats_idx + 1;

}

// Action
void _set_broadcast_5674735()
{
	action_run = 5674735;
	meta.l2_metadata.lkp_pkt_type = 4;
	meta.l2_metadata.bd_stats_idx = meta.l2_metadata.bd_stats_idx + 2;

}

// Action
void _set_malformed_packet_5674762(uint8_t drop_reason)
{
	action_run = 5674762;
	meta.ingress_metadata.drop_flag = 1;
	meta.ingress_metadata.drop_reason = drop_reason;

}

// Action
void _nop_114_5674933()
{
	action_run = 5674933;

}

// Action
void _nop_115_5674943()
{
	action_run = 5674943;

}

// Action
void _set_ingress_dst_port_range_id_5674944(uint8_t range_id)
{
	action_run = 5674944;
	meta.acl_metadata.ingress_dst_port_range_id = range_id;

}

// Action
void _set_ingress_src_port_range_id_5674962(uint8_t range_id)
{
	action_run = 5674962;
	meta.acl_metadata.ingress_src_port_range_id = range_id;

}

// Action
void _nop_116_5675094()
{
	action_run = 5675094;

}

// Action
void _nop_117_5675104()
{
	action_run = 5675104;

}

// Action
void _dmac_hit_5675105(uint32_t ifindex)
{
	action_run = 5675105;
	meta.ingress_metadata.egress_ifindex = ifindex;
	meta.l2_metadata.same_if_check =
	    (meta.l2_metadata.same_if_check ^ ifindex);

}

// Action
void _dmac_multicast_hit_5675135(uint32_t mc_index)
{
	action_run = 5675135;
	intrinsic_metadata.mcast_grp = mc_index;
	meta.fabric_metadata.dst_device = 127;

}

// Action
void _dmac_miss_5675159()
{
	action_run = 5675159;
	meta.ingress_metadata.egress_ifindex = 65535;
	meta.fabric_metadata.dst_device = 127;

}

// Action
void _dmac_redirect_nexthop_5675181(uint32_t nexthop_index)
{
	action_run = 5675181;
	meta.l2_metadata.l2_redirect = 1;
	meta.l2_metadata.l2_nexthop = nexthop_index;
	meta.l2_metadata.l2_nexthop_type = 0;

}

// Action
void _dmac_redirect_ecmp_5675211(uint32_t ecmp_index)
{
	action_run = 5675211;
	meta.l2_metadata.l2_redirect = 1;
	meta.l2_metadata.l2_nexthop = ecmp_index;
	meta.l2_metadata.l2_nexthop_type = 1;

}

// Action
void _dmac_drop_5675241()
{
	action_run = 5675241;
	mark_to_drop();

}

// Action
void _smac_miss_5675257()
{
	action_run = 5675257;
	meta.l2_metadata.l2_src_miss = 1;

}

// Action
void _smac_hit_5675273(uint32_t ifindex)
{
	action_run = 5675273;
	meta.l2_metadata.l2_src_move =
	    (meta.ingress_metadata.ifindex ^ ifindex);

}

// Action
void _nop_118_5675469()
{
	action_run = 5675469;

}

// Action
void
_acl_deny_5675479(uint32_t acl_stats_index, uint32_t acl_meter_index,
		  uint32_t acl_copy_reason, uint8_t nat_mode,
		  uint8_t ingress_cos, uint8_t tc, uint8_t color)
{
	action_run = 5675479;
	meta.acl_metadata.acl_deny = 1;
	meta.acl_metadata.acl_stats_index = acl_stats_index;
	meta.meter_metadata.meter_index = acl_meter_index;
	meta.fabric_metadata.reason_code = acl_copy_reason;
	meta.nat_metadata.ingress_nat_mode = nat_mode;
	intrinsic_metadata.ingress_cos = ingress_cos;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;

}

// Action
void
_acl_permit_5675551(uint32_t acl_stats_index, uint32_t acl_meter_index,
		    uint32_t acl_copy_reason, uint8_t nat_mode,
		    uint8_t ingress_cos, uint8_t tc, uint8_t color)
{
	action_run = 5675551;
	meta.acl_metadata.acl_stats_index = acl_stats_index;
	meta.meter_metadata.meter_index = acl_meter_index;
	meta.fabric_metadata.reason_code = acl_copy_reason;
	meta.nat_metadata.ingress_nat_mode = nat_mode;
	intrinsic_metadata.ingress_cos = ingress_cos;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;

}

// Action
void
_acl_redirect_nexthop_5675617(uint32_t nexthop_index,
			      uint32_t acl_stats_index,
			      uint32_t acl_meter_index,
			      uint32_t acl_copy_reason, uint8_t nat_mode,
			      uint8_t ingress_cos, uint8_t tc, uint8_t color)
{
	action_run = 5675617;
	meta.acl_metadata.acl_redirect = 1;
	meta.acl_metadata.acl_nexthop = nexthop_index;
	meta.acl_metadata.acl_nexthop_type = 0;
	meta.acl_metadata.acl_stats_index = acl_stats_index;
	meta.meter_metadata.meter_index = acl_meter_index;
	meta.fabric_metadata.reason_code = acl_copy_reason;
	meta.nat_metadata.ingress_nat_mode = nat_mode;
	intrinsic_metadata.ingress_cos = ingress_cos;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;

}

// Action
void
_acl_redirect_ecmp_5675703(uint32_t ecmp_index, uint32_t acl_stats_index,
			   uint32_t acl_meter_index,
			   uint32_t acl_copy_reason, uint8_t nat_mode,
			   uint8_t ingress_cos, uint8_t tc, uint8_t color)
{
	action_run = 5675703;
	meta.acl_metadata.acl_redirect = 1;
	meta.acl_metadata.acl_nexthop = ecmp_index;
	meta.acl_metadata.acl_nexthop_type = 1;
	meta.acl_metadata.acl_stats_index = acl_stats_index;
	meta.meter_metadata.meter_index = acl_meter_index;
	meta.fabric_metadata.reason_code = acl_copy_reason;
	meta.nat_metadata.ingress_nat_mode = nat_mode;
	intrinsic_metadata.ingress_cos = ingress_cos;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;

}

// Action
void
_acl_mirror_5750005(uint32_t session_id, uint32_t acl_stats_index,
		    uint32_t acl_meter_index, uint8_t nat_mode,
		    uint8_t ingress_cos, uint8_t tc, uint8_t color)
{
	action_run = 5750005;
	meta.i2e_metadata.mirror_session_id = (uint32_t) session_id;
	meta.acl_metadata.acl_stats_index = acl_stats_index;
	meta.meter_metadata.meter_index = acl_meter_index;
	meta.nat_metadata.ingress_nat_mode = nat_mode;
	intrinsic_metadata.ingress_cos = ingress_cos;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;

}

// Action
void _nop_119_5676001()
{
	action_run = 5676001;

}

// Action
void _nop_120_5676011()
{
	action_run = 5676011;

}

// Action
void
_acl_deny_0_5676012(uint32_t acl_stats_index, uint32_t acl_meter_index,
		    uint32_t acl_copy_reason, uint8_t nat_mode,
		    uint8_t ingress_cos, uint8_t tc, uint8_t color)
{
	action_run = 5676012;
	meta.acl_metadata.acl_deny = 1;
	meta.acl_metadata.acl_stats_index = acl_stats_index;
	meta.meter_metadata.meter_index = acl_meter_index;
	meta.fabric_metadata.reason_code = acl_copy_reason;
	meta.nat_metadata.ingress_nat_mode = nat_mode;
	intrinsic_metadata.ingress_cos = ingress_cos;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;

}

// Action
void
_acl_deny_4_5676084(uint32_t acl_stats_index, uint32_t acl_meter_index,
		    uint32_t acl_copy_reason, uint8_t nat_mode,
		    uint8_t ingress_cos, uint8_t tc, uint8_t color)
{
	action_run = 5676084;
	meta.acl_metadata.acl_deny = 1;
	meta.acl_metadata.acl_stats_index = acl_stats_index;
	meta.meter_metadata.meter_index = acl_meter_index;
	meta.fabric_metadata.reason_code = acl_copy_reason;
	meta.nat_metadata.ingress_nat_mode = nat_mode;
	intrinsic_metadata.ingress_cos = ingress_cos;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;

}

// Action
void
_acl_permit_0_5676150(uint32_t acl_stats_index, uint32_t acl_meter_index,
		      uint32_t acl_copy_reason, uint8_t nat_mode,
		      uint8_t ingress_cos, uint8_t tc, uint8_t color)
{
	action_run = 5676150;
	meta.acl_metadata.acl_stats_index = acl_stats_index;
	meta.meter_metadata.meter_index = acl_meter_index;
	meta.fabric_metadata.reason_code = acl_copy_reason;
	meta.nat_metadata.ingress_nat_mode = nat_mode;
	intrinsic_metadata.ingress_cos = ingress_cos;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;

}

// Action
void
_acl_permit_4_5676216(uint32_t acl_stats_index, uint32_t acl_meter_index,
		      uint32_t acl_copy_reason, uint8_t nat_mode,
		      uint8_t ingress_cos, uint8_t tc, uint8_t color)
{
	action_run = 5676216;
	meta.acl_metadata.acl_stats_index = acl_stats_index;
	meta.meter_metadata.meter_index = acl_meter_index;
	meta.fabric_metadata.reason_code = acl_copy_reason;
	meta.nat_metadata.ingress_nat_mode = nat_mode;
	intrinsic_metadata.ingress_cos = ingress_cos;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;

}

// Action
void
_acl_redirect_nexthop_0_5676277(uint32_t nexthop_index,
				uint32_t acl_stats_index,
				uint32_t acl_meter_index,
				uint32_t acl_copy_reason, uint8_t nat_mode,
				uint8_t ingress_cos, uint8_t tc, uint8_t color)
{
	action_run = 5676277;
	meta.acl_metadata.acl_redirect = 1;
	meta.acl_metadata.acl_nexthop = nexthop_index;
	meta.acl_metadata.acl_nexthop_type = 0;
	meta.acl_metadata.acl_stats_index = acl_stats_index;
	meta.meter_metadata.meter_index = acl_meter_index;
	meta.fabric_metadata.reason_code = acl_copy_reason;
	meta.nat_metadata.ingress_nat_mode = nat_mode;
	intrinsic_metadata.ingress_cos = ingress_cos;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;

}

// Action
void
_acl_redirect_nexthop_4_5676363(uint32_t nexthop_index,
				uint32_t acl_stats_index,
				uint32_t acl_meter_index,
				uint32_t acl_copy_reason, uint8_t nat_mode,
				uint8_t ingress_cos, uint8_t tc, uint8_t color)
{
	action_run = 5676363;
	meta.acl_metadata.acl_redirect = 1;
	meta.acl_metadata.acl_nexthop = nexthop_index;
	meta.acl_metadata.acl_nexthop_type = 0;
	meta.acl_metadata.acl_stats_index = acl_stats_index;
	meta.meter_metadata.meter_index = acl_meter_index;
	meta.fabric_metadata.reason_code = acl_copy_reason;
	meta.nat_metadata.ingress_nat_mode = nat_mode;
	intrinsic_metadata.ingress_cos = ingress_cos;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;

}

// Action
void
_acl_redirect_ecmp_0_5676442(uint32_t ecmp_index, uint32_t acl_stats_index,
			     uint32_t acl_meter_index,
			     uint32_t acl_copy_reason, uint8_t nat_mode,
			     uint8_t ingress_cos, uint8_t tc, uint8_t color)
{
	action_run = 5676442;
	meta.acl_metadata.acl_redirect = 1;
	meta.acl_metadata.acl_nexthop = ecmp_index;
	meta.acl_metadata.acl_nexthop_type = 1;
	meta.acl_metadata.acl_stats_index = acl_stats_index;
	meta.meter_metadata.meter_index = acl_meter_index;
	meta.fabric_metadata.reason_code = acl_copy_reason;
	meta.nat_metadata.ingress_nat_mode = nat_mode;
	intrinsic_metadata.ingress_cos = ingress_cos;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;

}

// Action
void
_acl_redirect_ecmp_4_5676528(uint32_t ecmp_index, uint32_t acl_stats_index,
			     uint32_t acl_meter_index,
			     uint32_t acl_copy_reason, uint8_t nat_mode,
			     uint8_t ingress_cos, uint8_t tc, uint8_t color)
{
	action_run = 5676528;
	meta.acl_metadata.acl_redirect = 1;
	meta.acl_metadata.acl_nexthop = ecmp_index;
	meta.acl_metadata.acl_nexthop_type = 1;
	meta.acl_metadata.acl_stats_index = acl_stats_index;
	meta.meter_metadata.meter_index = acl_meter_index;
	meta.fabric_metadata.reason_code = acl_copy_reason;
	meta.nat_metadata.ingress_nat_mode = nat_mode;
	intrinsic_metadata.ingress_cos = ingress_cos;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;

}

// Action
void
_acl_mirror_0_5751199(uint32_t session_id, uint32_t acl_stats_index,
		      uint32_t acl_meter_index, uint8_t nat_mode,
		      uint8_t ingress_cos, uint8_t tc, uint8_t color)
{
	action_run = 5751199;
	meta.i2e_metadata.mirror_session_id = (uint32_t) session_id;
	meta.acl_metadata.acl_stats_index = acl_stats_index;
	meta.meter_metadata.meter_index = acl_meter_index;
	meta.nat_metadata.ingress_nat_mode = nat_mode;
	intrinsic_metadata.ingress_cos = ingress_cos;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;

}

// Action
void
_acl_mirror_4_5751339(uint32_t session_id, uint32_t acl_stats_index,
		      uint32_t acl_meter_index, uint8_t nat_mode,
		      uint8_t ingress_cos, uint8_t tc, uint8_t color)
{
	action_run = 5751339;
	meta.i2e_metadata.mirror_session_id = (uint32_t) session_id;
	meta.acl_metadata.acl_stats_index = acl_stats_index;
	meta.meter_metadata.meter_index = acl_meter_index;
	meta.nat_metadata.ingress_nat_mode = nat_mode;
	intrinsic_metadata.ingress_cos = ingress_cos;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;

}

// Action
void _nop_121_5677099()
{
	action_run = 5677099;

}

// Action
void
_racl_deny_5677109(uint32_t acl_stats_index, uint32_t acl_copy_reason,
		   uint8_t ingress_cos, uint8_t tc, uint8_t color)
{
	action_run = 5677109;
	meta.acl_metadata.racl_deny = 1;
	meta.acl_metadata.acl_stats_index = acl_stats_index;
	meta.fabric_metadata.reason_code = acl_copy_reason;
	intrinsic_metadata.ingress_cos = ingress_cos;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;

}

// Action
void
_racl_permit_5677165(uint32_t acl_stats_index, uint32_t acl_copy_reason,
		     uint8_t ingress_cos, uint8_t tc, uint8_t color)
{
	action_run = 5677165;
	meta.acl_metadata.acl_stats_index = acl_stats_index;
	meta.fabric_metadata.reason_code = acl_copy_reason;
	intrinsic_metadata.ingress_cos = ingress_cos;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;

}

// Action
void
_racl_redirect_nexthop_5677215(uint32_t nexthop_index,
			       uint32_t acl_stats_index,
			       uint32_t acl_copy_reason, uint8_t ingress_cos,
			       uint8_t tc, uint8_t color)
{
	action_run = 5677215;
	meta.acl_metadata.racl_redirect = 1;
	meta.acl_metadata.racl_nexthop = nexthop_index;
	meta.acl_metadata.racl_nexthop_type = 0;
	meta.acl_metadata.acl_stats_index = acl_stats_index;
	meta.fabric_metadata.reason_code = acl_copy_reason;
	intrinsic_metadata.ingress_cos = ingress_cos;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;

}

// Action
void
_racl_redirect_ecmp_5677285(uint32_t ecmp_index, uint32_t acl_stats_index,
			    uint32_t acl_copy_reason, uint8_t ingress_cos,
			    uint8_t tc, uint8_t color)
{
	action_run = 5677285;
	meta.acl_metadata.racl_redirect = 1;
	meta.acl_metadata.racl_nexthop = ecmp_index;
	meta.acl_metadata.racl_nexthop_type = 1;
	meta.acl_metadata.acl_stats_index = acl_stats_index;
	meta.fabric_metadata.reason_code = acl_copy_reason;
	intrinsic_metadata.ingress_cos = ingress_cos;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;

}

// Action
void _on_miss_15_5677480()
{
	action_run = 5677480;

}

// Action
void _ipv4_urpf_hit_5677490(uint32_t urpf_bd_group)
{
	action_run = 5677490;
	meta.l3_metadata.urpf_hit = 1;
	meta.l3_metadata.urpf_bd_group = urpf_bd_group;
	meta.l3_metadata.urpf_mode = meta.ipv4_metadata.ipv4_urpf_mode;

}

// Action
void _ipv4_urpf_hit_2_5677523(uint32_t urpf_bd_group)
{
	action_run = 5677523;
	meta.l3_metadata.urpf_hit = 1;
	meta.l3_metadata.urpf_bd_group = urpf_bd_group;
	meta.l3_metadata.urpf_mode = meta.ipv4_metadata.ipv4_urpf_mode;

}

// Action
void _urpf_miss_5677550()
{
	action_run = 5677550;
	meta.l3_metadata.urpf_check_fail = 1;

}

// Action
void _on_miss_16_5677700()
{
	action_run = 5677700;

}

// Action
void _on_miss_17_5677710()
{
	action_run = 5677710;

}

// Action
void _fib_hit_nexthop_5677711(uint32_t nexthop_index)
{
	action_run = 5677711;
	meta.l3_metadata.fib_hit = 1;
	meta.l3_metadata.fib_nexthop = nexthop_index;
	meta.l3_metadata.fib_nexthop_type = 0;

}

// Action
void _fib_hit_nexthop_0_5677741(uint32_t nexthop_index)
{
	action_run = 5677741;
	meta.l3_metadata.fib_hit = 1;
	meta.l3_metadata.fib_nexthop = nexthop_index;
	meta.l3_metadata.fib_nexthop_type = 0;

}

// Action
void _fib_hit_ecmp_5677764(uint32_t ecmp_index)
{
	action_run = 5677764;
	meta.l3_metadata.fib_hit = 1;
	meta.l3_metadata.fib_nexthop = ecmp_index;
	meta.l3_metadata.fib_nexthop_type = 1;

}

// Action
void _fib_hit_ecmp_0_5677794(uint32_t ecmp_index)
{
	action_run = 5677794;
	meta.l3_metadata.fib_hit = 1;
	meta.l3_metadata.fib_nexthop = ecmp_index;
	meta.l3_metadata.fib_nexthop_type = 1;

}

// Action
void _nop_122_5677963()
{
	action_run = 5677963;

}

// Action
void
_racl_deny_0_5677973(uint32_t acl_stats_index, uint32_t acl_copy_reason,
		     uint8_t ingress_cos, uint8_t tc, uint8_t color)
{
	action_run = 5677973;
	meta.acl_metadata.racl_deny = 1;
	meta.acl_metadata.acl_stats_index = acl_stats_index;
	meta.fabric_metadata.reason_code = acl_copy_reason;
	intrinsic_metadata.ingress_cos = ingress_cos;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;

}

// Action
void
_racl_permit_0_5678029(uint32_t acl_stats_index, uint32_t acl_copy_reason,
		       uint8_t ingress_cos, uint8_t tc, uint8_t color)
{
	action_run = 5678029;
	meta.acl_metadata.acl_stats_index = acl_stats_index;
	meta.fabric_metadata.reason_code = acl_copy_reason;
	intrinsic_metadata.ingress_cos = ingress_cos;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;

}

// Action
void
_racl_redirect_nexthop_0_5678079(uint32_t nexthop_index,
				 uint32_t acl_stats_index,
				 uint32_t acl_copy_reason,
				 uint8_t ingress_cos, uint8_t tc, uint8_t color)
{
	action_run = 5678079;
	meta.acl_metadata.racl_redirect = 1;
	meta.acl_metadata.racl_nexthop = nexthop_index;
	meta.acl_metadata.racl_nexthop_type = 0;
	meta.acl_metadata.acl_stats_index = acl_stats_index;
	meta.fabric_metadata.reason_code = acl_copy_reason;
	intrinsic_metadata.ingress_cos = ingress_cos;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;

}

// Action
void
_racl_redirect_ecmp_0_5678149(uint32_t ecmp_index, uint32_t acl_stats_index,
			      uint32_t acl_copy_reason, uint8_t ingress_cos,
			      uint8_t tc, uint8_t color)
{
	action_run = 5678149;
	meta.acl_metadata.racl_redirect = 1;
	meta.acl_metadata.racl_nexthop = ecmp_index;
	meta.acl_metadata.racl_nexthop_type = 1;
	meta.acl_metadata.acl_stats_index = acl_stats_index;
	meta.fabric_metadata.reason_code = acl_copy_reason;
	intrinsic_metadata.ingress_cos = ingress_cos;
	meta.qos_metadata.lkp_tc = tc;
	meta.meter_metadata.packet_color = color;

}

// Action
void _on_miss_18_5678344()
{
	action_run = 5678344;

}

// Action
void _ipv6_urpf_hit_5678354(uint32_t urpf_bd_group)
{
	action_run = 5678354;
	meta.l3_metadata.urpf_hit = 1;
	meta.l3_metadata.urpf_bd_group = urpf_bd_group;
	meta.l3_metadata.urpf_mode = meta.ipv6_metadata.ipv6_urpf_mode;

}

// Action
void _ipv6_urpf_hit_2_5678387(uint32_t urpf_bd_group)
{
	action_run = 5678387;
	meta.l3_metadata.urpf_hit = 1;
	meta.l3_metadata.urpf_bd_group = urpf_bd_group;
	meta.l3_metadata.urpf_mode = meta.ipv6_metadata.ipv6_urpf_mode;

}

// Action
void _urpf_miss_0_5678414()
{
	action_run = 5678414;
	meta.l3_metadata.urpf_check_fail = 1;

}

// Action
void _on_miss_19_5678564()
{
	action_run = 5678564;

}

// Action
void _on_miss_20_5678574()
{
	action_run = 5678574;

}

// Action
void _fib_hit_nexthop_5_5678575(uint32_t nexthop_index)
{
	action_run = 5678575;
	meta.l3_metadata.fib_hit = 1;
	meta.l3_metadata.fib_nexthop = nexthop_index;
	meta.l3_metadata.fib_nexthop_type = 0;

}

// Action
void _fib_hit_nexthop_6_5678605(uint32_t nexthop_index)
{
	action_run = 5678605;
	meta.l3_metadata.fib_hit = 1;
	meta.l3_metadata.fib_nexthop = nexthop_index;
	meta.l3_metadata.fib_nexthop_type = 0;

}

// Action
void _fib_hit_ecmp_5_5678628(uint32_t ecmp_index)
{
	action_run = 5678628;
	meta.l3_metadata.fib_hit = 1;
	meta.l3_metadata.fib_nexthop = ecmp_index;
	meta.l3_metadata.fib_nexthop_type = 1;

}

// Action
void _fib_hit_ecmp_6_5678658(uint32_t ecmp_index)
{
	action_run = 5678658;
	meta.l3_metadata.fib_hit = 1;
	meta.l3_metadata.fib_nexthop = ecmp_index;
	meta.l3_metadata.fib_nexthop_type = 1;

}

// Action
void _nop_123_5678827()
{
	action_run = 5678827;

}

// Action
void _urpf_bd_miss_5678837()
{
	action_run = 5678837;
	meta.l3_metadata.urpf_check_fail = 1;

}

// Action
void _on_miss_21_5678948()
{
	action_run = 5678948;

}

// Action
void _multicast_bridge_s_g_hit_1_5678958(uint32_t mc_index)
{
	action_run = 5678958;
	meta.multicast_metadata.multicast_bridge_mc_index = mc_index;
	meta.multicast_metadata.mcast_bridge_hit = 1;

}

// Action
void _nop_124_5678982()
{
	action_run = 5678982;

}

// Action
void _multicast_bridge_star_g_hit_1_5678992(uint32_t mc_index)
{
	action_run = 5678992;
	meta.multicast_metadata.multicast_bridge_mc_index = mc_index;
	meta.multicast_metadata.mcast_bridge_hit = 1;

}

// Action
void _on_miss_22_5679160()
{
	action_run = 5679160;

}

// Action
void
_multicast_route_s_g_hit_1_5679177(uint32_t mc_index, uint32_t mcast_rpf_group)
{
	action_run = 5679177;
	meta.multicast_metadata.multicast_route_mc_index = mc_index;
	meta.multicast_metadata.mcast_mode = 1;
	meta.multicast_metadata.mcast_route_hit = 1;
	meta.multicast_metadata.mcast_rpf_group =
	    (mcast_rpf_group ^ meta.multicast_metadata.bd_mrpf_group);

}

// Action
void _multicast_route_star_g_miss_1_5679308()
{
	action_run = 5679308;
	meta.l3_metadata.l3_copy = 1;

}

// Action
void
_multicast_route_sm_star_g_hit_1_5679331(uint32_t mc_index,
					 uint32_t mcast_rpf_group)
{
	action_run = 5679331;
	meta.multicast_metadata.mcast_mode = 1;
	meta.multicast_metadata.multicast_route_mc_index = mc_index;
	meta.multicast_metadata.mcast_route_hit = 1;
	meta.multicast_metadata.mcast_rpf_group =
	    (mcast_rpf_group ^ meta.multicast_metadata.bd_mrpf_group);

}

// Action
void
_multicast_route_bidir_star_g_hit_1_5679381(uint32_t mc_index,
					    uint32_t mcast_rpf_group)
{
	action_run = 5679381;
	meta.multicast_metadata.mcast_mode = 2;
	meta.multicast_metadata.multicast_route_mc_index = mc_index;
	meta.multicast_metadata.mcast_route_hit = 1;
	meta.multicast_metadata.mcast_rpf_group =
	    (mcast_rpf_group | meta.multicast_metadata.bd_mrpf_group);

}

// Action
void _on_miss_23_5679536()
{
	action_run = 5679536;

}

// Action
void _multicast_bridge_s_g_hit_2_5679546(uint32_t mc_index)
{
	action_run = 5679546;
	meta.multicast_metadata.multicast_bridge_mc_index = mc_index;
	meta.multicast_metadata.mcast_bridge_hit = 1;

}

// Action
void _nop_125_5679570()
{
	action_run = 5679570;

}

// Action
void _multicast_bridge_star_g_hit_2_5679580(uint32_t mc_index)
{
	action_run = 5679580;
	meta.multicast_metadata.multicast_bridge_mc_index = mc_index;
	meta.multicast_metadata.mcast_bridge_hit = 1;

}

// Action
void _on_miss_33_5679748()
{
	action_run = 5679748;

}

// Action
void
_multicast_route_s_g_hit_2_5679765(uint32_t mc_index, uint32_t mcast_rpf_group)
{
	action_run = 5679765;
	meta.multicast_metadata.multicast_route_mc_index = mc_index;
	meta.multicast_metadata.mcast_mode = 1;
	meta.multicast_metadata.mcast_route_hit = 1;
	meta.multicast_metadata.mcast_rpf_group =
	    (mcast_rpf_group ^ meta.multicast_metadata.bd_mrpf_group);

}

// Action
void _multicast_route_star_g_miss_2_5679896()
{
	action_run = 5679896;
	meta.l3_metadata.l3_copy = 1;

}

// Action
void
_multicast_route_sm_star_g_hit_2_5679919(uint32_t mc_index,
					 uint32_t mcast_rpf_group)
{
	action_run = 5679919;
	meta.multicast_metadata.mcast_mode = 1;
	meta.multicast_metadata.multicast_route_mc_index = mc_index;
	meta.multicast_metadata.mcast_route_hit = 1;
	meta.multicast_metadata.mcast_rpf_group =
	    (mcast_rpf_group ^ meta.multicast_metadata.bd_mrpf_group);

}

// Action
void
_multicast_route_bidir_star_g_hit_2_5679969(uint32_t mc_index,
					    uint32_t mcast_rpf_group)
{
	action_run = 5679969;
	meta.multicast_metadata.mcast_mode = 2;
	meta.multicast_metadata.multicast_route_mc_index = mc_index;
	meta.multicast_metadata.mcast_route_hit = 1;
	meta.multicast_metadata.mcast_rpf_group =
	    (mcast_rpf_group | meta.multicast_metadata.bd_mrpf_group);

}

// Action
void _on_miss_34_5680096()
{
	action_run = 5680096;

}

// Action
void _on_miss_35_5680106()
{
	action_run = 5680106;

}

// Action
void _on_miss_36_5680107()
{
	action_run = 5680107;

}

// Action
void
_set_dst_nat_nexthop_index_5680108(uint32_t nexthop_index,
				   uint8_t nexthop_type,
				   uint32_t nat_rewrite_index)
{
	action_run = 5680108;
	meta.nat_metadata.nat_nexthop = nexthop_index;
	meta.nat_metadata.nat_nexthop_type = nexthop_type;
	meta.nat_metadata.nat_rewrite_index = nat_rewrite_index;
	meta.nat_metadata.nat_hit = 1;

}

// Action
void
_set_dst_nat_nexthop_index_2_5680148(uint32_t nexthop_index,
				     uint8_t nexthop_type,
				     uint32_t nat_rewrite_index)
{
	action_run = 5680148;
	meta.nat_metadata.nat_nexthop = nexthop_index;
	meta.nat_metadata.nat_nexthop_type = nexthop_type;
	meta.nat_metadata.nat_rewrite_index = nat_rewrite_index;
	meta.nat_metadata.nat_hit = 1;

}

// Action
void _nop_126_5680182()
{
	action_run = 5680182;

}

// Action
void _set_src_nat_rewrite_index_5680192(uint32_t nat_rewrite_index)
{
	action_run = 5680192;
	meta.nat_metadata.nat_rewrite_index = nat_rewrite_index;

}

// Action
void _set_src_nat_rewrite_index_2_5680210(uint32_t nat_rewrite_index)
{
	action_run = 5680210;
	meta.nat_metadata.nat_rewrite_index = nat_rewrite_index;

}

// Action
void
_set_twice_nat_nexthop_index_5680223(uint32_t nexthop_index,
				     uint8_t nexthop_type,
				     uint32_t nat_rewrite_index)
{
	action_run = 5680223;
	meta.nat_metadata.nat_nexthop = nexthop_index;
	meta.nat_metadata.nat_nexthop_type = nexthop_type;
	meta.nat_metadata.nat_rewrite_index = nat_rewrite_index;
	meta.nat_metadata.nat_hit = 1;

}

// Action
void
_set_twice_nat_nexthop_index_2_5680263(uint32_t nexthop_index,
				       uint8_t nexthop_type,
				       uint32_t nat_rewrite_index)
{
	action_run = 5680263;
	meta.nat_metadata.nat_nexthop = nexthop_index;
	meta.nat_metadata.nat_nexthop_type = nexthop_type;
	meta.nat_metadata.nat_rewrite_index = nat_rewrite_index;
	meta.nat_metadata.nat_hit = 1;

}

// Action
void _nop_127_5680713()
{
	action_run = 5680713;

	uint64_t t25afa665_3a34_45c6_b7fd_03273a53768d;
	klee_make_symbolic(&t25afa665_3a34_45c6_b7fd_03273a53768d,
			   sizeof(t25afa665_3a34_45c6_b7fd_03273a53768d),
			   "t25afa665_3a34_45c6_b7fd_03273a53768d");
	meta.meter_metadata.packet_color =
	    t25afa665_3a34_45c6_b7fd_03273a53768d;

}

// Action
void _compute_lkp_ipv4_hash_5680789()
{
	action_run = 5680789;

	uint64_t t25d906e3_7aee_4233_b227_8d8893ae36cf;
	klee_make_symbolic(&t25d906e3_7aee_4233_b227_8d8893ae36cf,
			   sizeof(t25d906e3_7aee_4233_b227_8d8893ae36cf),
			   "t25d906e3_7aee_4233_b227_8d8893ae36cf");
	meta.hash_metadata.hash1 = t25d906e3_7aee_4233_b227_8d8893ae36cf;

	uint64_t t53ba9db2_6e14_47fc_b896_514cc4daf101;
	klee_make_symbolic(&t53ba9db2_6e14_47fc_b896_514cc4daf101,
			   sizeof(t53ba9db2_6e14_47fc_b896_514cc4daf101),
			   "t53ba9db2_6e14_47fc_b896_514cc4daf101");
	meta.hash_metadata.hash2 = t53ba9db2_6e14_47fc_b896_514cc4daf101;

}

// Action
void _compute_lkp_ipv6_hash_5680887()
{
	action_run = 5680887;

	uint64_t t933700ca_8290_44ee_8bb1_080952aa3d9b;
	klee_make_symbolic(&t933700ca_8290_44ee_8bb1_080952aa3d9b,
			   sizeof(t933700ca_8290_44ee_8bb1_080952aa3d9b),
			   "t933700ca_8290_44ee_8bb1_080952aa3d9b");
	meta.hash_metadata.hash1 = t933700ca_8290_44ee_8bb1_080952aa3d9b;

	uint64_t tdec3c070_091c_436c_aad9_f616e0c476b9;
	klee_make_symbolic(&tdec3c070_091c_436c_aad9_f616e0c476b9,
			   sizeof(tdec3c070_091c_436c_aad9_f616e0c476b9),
			   "tdec3c070_091c_436c_aad9_f616e0c476b9");
	meta.hash_metadata.hash2 = tdec3c070_091c_436c_aad9_f616e0c476b9;

}

// Action
void _compute_lkp_non_ip_hash_5680985()
{
	action_run = 5680985;

	uint64_t td068efb7_c17a_4fa7_acbf_387de2da6235;
	klee_make_symbolic(&td068efb7_c17a_4fa7_acbf_387de2da6235,
			   sizeof(td068efb7_c17a_4fa7_acbf_387de2da6235),
			   "td068efb7_c17a_4fa7_acbf_387de2da6235");
	meta.hash_metadata.hash2 = td068efb7_c17a_4fa7_acbf_387de2da6235;

}

// Action
void _computed_two_hashes_5681031()
{
	action_run = 5681031;
	intrinsic_metadata.mcast_hash =
	    (uint32_t) meta.hash_metadata.hash1;
	meta.hash_metadata.entropy_hash = meta.hash_metadata.hash2;

}

// Action
void _computed_one_hash_5681060()
{
	action_run = 5681060;
	meta.hash_metadata.hash1 = meta.hash_metadata.hash2;
	intrinsic_metadata.mcast_hash =
	    (uint32_t) meta.hash_metadata.hash2;
	meta.hash_metadata.entropy_hash = meta.hash_metadata.hash2;

}

// Action
void _meter_permit_5681306()
{
	action_run = 5681306;

}

// Action
void _meter_deny_5681323()
{
	action_run = 5681323;
	mark_to_drop();

}

// Action
void _update_ingress_bd_stats_5681436()
{
	action_run = 5681436;

}

// Action
void _acl_stats_update_5681515()
{
	action_run = 5681515;

}

// Action
void _nop_128_5681589()
{
	action_run = 5681589;

}

// Action
void _nop_129_5681671()
{
	action_run = 5681671;

}

// Action
void _set_l2_redirect_action_5681681()
{
	action_run = 5681681;
	meta.l3_metadata.nexthop_index = meta.l2_metadata.l2_nexthop;
	meta.nexthop_metadata.nexthop_type = meta.l2_metadata.l2_nexthop_type;
	meta.ingress_metadata.egress_ifindex = 0;
	intrinsic_metadata.mcast_grp = 0;
	meta.fabric_metadata.dst_device = 0;

}

// Action
void _set_fib_redirect_action_5681727()
{
	action_run = 5681727;
	meta.l3_metadata.nexthop_index = meta.l3_metadata.fib_nexthop;
	meta.nexthop_metadata.nexthop_type = meta.l3_metadata.fib_nexthop_type;
	meta.l3_metadata.routed = 1;
	intrinsic_metadata.mcast_grp = 0;
	meta.fabric_metadata.reason_code = 535;
	meta.fabric_metadata.dst_device = 0;

}

// Action
void _set_cpu_redirect_action_5681779()
{
	action_run = 5681779;
	meta.l3_metadata.routed = 0;
	intrinsic_metadata.mcast_grp = 0;
	standard_metadata.egress_spec = 64;
	meta.ingress_metadata.egress_ifindex = 0;
	meta.fabric_metadata.dst_device = 0;

}

// Action
void _set_acl_redirect_action_5681818()
{
	action_run = 5681818;
	meta.l3_metadata.nexthop_index = meta.acl_metadata.acl_nexthop;
	meta.nexthop_metadata.nexthop_type = meta.acl_metadata.acl_nexthop_type;
	meta.ingress_metadata.egress_ifindex = 0;
	intrinsic_metadata.mcast_grp = 0;
	meta.fabric_metadata.dst_device = 0;

}

// Action
void _set_racl_redirect_action_5681864()
{
	action_run = 5681864;
	meta.l3_metadata.nexthop_index = meta.acl_metadata.racl_nexthop;
	meta.nexthop_metadata.nexthop_type =
	    meta.acl_metadata.racl_nexthop_type;
	meta.l3_metadata.routed = 1;
	meta.ingress_metadata.egress_ifindex = 0;
	intrinsic_metadata.mcast_grp = 0;
	meta.fabric_metadata.dst_device = 0;

}

// Action
void _set_nat_redirect_action_5681916()
{
	action_run = 5681916;
	meta.l3_metadata.nexthop_index = meta.nat_metadata.nat_nexthop;
	meta.nexthop_metadata.nexthop_type = meta.nat_metadata.nat_nexthop_type;
	meta.l3_metadata.routed = 1;
	intrinsic_metadata.mcast_grp = 0;
	meta.fabric_metadata.dst_device = 0;

}

// Action
void _set_multicast_route_action_5681962()
{
	action_run = 5681962;
	meta.fabric_metadata.dst_device = 127;
	meta.ingress_metadata.egress_ifindex = 0;
	intrinsic_metadata.mcast_grp =
	    meta.multicast_metadata.multicast_route_mc_index;
	meta.l3_metadata.routed = 1;
	meta.l3_metadata.same_bd_check = 65535;

}

// Action
void _set_multicast_bridge_action_5682005()
{
	action_run = 5682005;
	meta.fabric_metadata.dst_device = 127;
	meta.ingress_metadata.egress_ifindex = 0;
	intrinsic_metadata.mcast_grp =
	    meta.multicast_metadata.multicast_bridge_mc_index;

}

// Action
void _set_multicast_flood_5682036()
{
	action_run = 5682036;
	meta.fabric_metadata.dst_device = 127;
	meta.ingress_metadata.egress_ifindex = 65535;

}

// Action
void _set_multicast_drop_5682058()
{
	action_run = 5682058;
	meta.ingress_metadata.drop_flag = 1;
	meta.ingress_metadata.drop_reason = 44;

}

// Action
void _nop_130_5682321()
{
	action_run = 5682321;

}

// Action
void _nop_131_5682331()
{
	action_run = 5682331;

}

// Action
void
_set_ecmp_nexthop_details_5682332(uint32_t ifindex, uint32_t bd,
				  uint32_t nhop_index, uint8_t tunnel)
{
	action_run = 5682332;
	meta.ingress_metadata.egress_ifindex = ifindex;
	meta.l3_metadata.nexthop_index = nhop_index;
	meta.l3_metadata.same_bd_check = (meta.ingress_metadata.bd ^ bd);
	meta.l2_metadata.same_if_check =
	    (meta.l2_metadata.same_if_check ^ ifindex);
	meta.tunnel_metadata.tunnel_if_check =
	    (meta.tunnel_metadata.tunnel_terminate ^ tunnel);

}

// Action
void
_set_ecmp_nexthop_details_for_post_routed_flood_5682396(uint32_t bd,
							uint32_t
							uuc_mc_index,
							uint32_t nhop_index)
{
	action_run = 5682396;
	intrinsic_metadata.mcast_grp = uuc_mc_index;
	meta.l3_metadata.nexthop_index = nhop_index;
	meta.ingress_metadata.egress_ifindex = 0;
	meta.l3_metadata.same_bd_check = (meta.ingress_metadata.bd ^ bd);
	meta.fabric_metadata.dst_device = 127;

}

// Action
void _set_nexthop_details_5682447(uint32_t ifindex, uint32_t bd, uint8_t tunnel)
{
	action_run = 5682447;
	meta.ingress_metadata.egress_ifindex = ifindex;
	meta.l3_metadata.same_bd_check = (meta.ingress_metadata.bd ^ bd);
	meta.l2_metadata.same_if_check =
	    (meta.l2_metadata.same_if_check ^ ifindex);
	meta.tunnel_metadata.tunnel_if_check =
	    (meta.tunnel_metadata.tunnel_terminate ^ tunnel);

}

// Action
void
_set_nexthop_details_for_post_routed_flood_5682503(uint32_t bd,
						   uint32_t uuc_mc_index)
{
	action_run = 5682503;
	intrinsic_metadata.mcast_grp = uuc_mc_index;
	meta.ingress_metadata.egress_ifindex = 0;
	meta.l3_metadata.same_bd_check = (meta.ingress_metadata.bd ^ bd);
	meta.fabric_metadata.dst_device = 127;

}

// Action
void _nop_132_5682686()
{
	action_run = 5682686;

}

// Action
void _set_bd_flood_mc_index_5682696(uint32_t mc_index)
{
	action_run = 5682696;
	intrinsic_metadata.mcast_grp = mc_index;

}

// Action
void _set_lag_miss_5682781()
{
	action_run = 5682781;

}

// Action
void _set_lag_port_5682791(uint32_t port)
{
	action_run = 5682791;
	standard_metadata.egress_spec = port;

}

// Action
void _set_lag_remote_port_5682808(uint8_t device, uint32_t port)
{
	action_run = 5682808;
	meta.fabric_metadata.dst_device = device;
	meta.fabric_metadata.dst_port = port;

}

// Action
void _nop_133_5682911()
{
	action_run = 5682911;

}

// Action
void _generate_learn_notify_5682921()
{
	action_run = 5682921;

}

// Action
void _nop_134_5683031()
{
	action_run = 5683031;

}

// Action
void _set_fabric_lag_port_5683041(uint32_t port)
{
	action_run = 5683041;
	standard_metadata.egress_spec = port;

}

// Action
void _set_fabric_multicast_5683058(uint8_t fabric_mgid)
{
	action_run = 5683058;
	meta.multicast_metadata.mcast_grp = intrinsic_metadata.mcast_grp;

}

// Action
void _nop_135_5683151()
{
	action_run = 5683151;

}

// Action
void _set_icos_5683161(uint8_t icos)
{
	action_run = 5683161;
	intrinsic_metadata.ingress_cos = icos;

}

// Action
void _set_queue_5683179(uint8_t qid)
{
	action_run = 5683179;
	intrinsic_metadata.qid = qid;

}

// Action
void _set_icos_and_queue_5683197(uint8_t icos, uint8_t qid)
{
	action_run = 5683197;
	intrinsic_metadata.ingress_cos = icos;
	intrinsic_metadata.qid = qid;

}

// Action
void _drop_stats_update_5683347()
{
	action_run = 5683347;

}

// Action
void _nop_136_5683369()
{
	action_run = 5683369;

}

// Action
void _copy_to_cpu_5683379(uint8_t qid, uint32_t meter_id, uint8_t icos)
{
	action_run = 5683379;
	intrinsic_metadata.qid = qid;
	intrinsic_metadata.ingress_cos = icos;

	uint64_t t6d4794bd_9e6a_49fb_ba64_ef078dad9c81;
	klee_make_symbolic(&t6d4794bd_9e6a_49fb_ba64_ef078dad9c81,
			   sizeof(t6d4794bd_9e6a_49fb_ba64_ef078dad9c81),
			   "t6d4794bd_9e6a_49fb_ba64_ef078dad9c81");
	intrinsic_metadata.packet_color = t6d4794bd_9e6a_49fb_ba64_ef078dad9c81;

}

// Action
void _redirect_to_cpu_5683450(uint8_t qid, uint32_t meter_id, uint8_t icos)
{
	action_run = 5683450;
	intrinsic_metadata.qid = qid;
	intrinsic_metadata.ingress_cos = icos;

	uint64_t t482d3610_0ae8_484b_9953_6c083e96b761;
	klee_make_symbolic(&t482d3610_0ae8_484b_9953_6c083e96b761,
			   sizeof(t482d3610_0ae8_484b_9953_6c083e96b761),
			   "t482d3610_0ae8_484b_9953_6c083e96b761");
	intrinsic_metadata.packet_color =
	    t482d3610_0ae8_484b_9953_6c083e96b761;

	mark_to_drop();
	meta.fabric_metadata.dst_device = 0;

}

// Action
void
_copy_to_cpu_with_reason_5759878(uint32_t reason_code, uint8_t qid,
				 uint32_t meter_id, uint8_t icos)
{
	action_run = 5759878;
	meta.fabric_metadata.reason_code = reason_code;
	intrinsic_metadata.qid = qid;
	intrinsic_metadata.ingress_cos = icos;

	uint64_t t7ae2eb62_290b_48dd_afcf_98b4011707f4;
	klee_make_symbolic(&t7ae2eb62_290b_48dd_afcf_98b4011707f4,
			   sizeof(t7ae2eb62_290b_48dd_afcf_98b4011707f4),
			   "t7ae2eb62_290b_48dd_afcf_98b4011707f4");
	intrinsic_metadata.packet_color =
	    t7ae2eb62_290b_48dd_afcf_98b4011707f4;

}

// Action
void
_redirect_to_cpu_with_reason_5759995(uint32_t reason_code, uint8_t qid,
				     uint32_t meter_id, uint8_t icos)
{
	action_run = 5759995;
	meta.fabric_metadata.reason_code = reason_code;
	intrinsic_metadata.qid = qid;
	intrinsic_metadata.ingress_cos = icos;

	uint64_t tbce1fe65_65cc_4850_a864_8e6a3885be81;
	klee_make_symbolic(&tbce1fe65_65cc_4850_a864_8e6a3885be81,
			   sizeof(tbce1fe65_65cc_4850_a864_8e6a3885be81),
			   "tbce1fe65_65cc_4850_a864_8e6a3885be81");
	intrinsic_metadata.packet_color =
	    tbce1fe65_65cc_4850_a864_8e6a3885be81;

	mark_to_drop();
	meta.fabric_metadata.dst_device = 0;

}

// Action
void _drop_packet_0_5683688()
{
	action_run = 5683688;
	mark_to_drop();

}

// Action
void _drop_packet_with_reason_5683704(uint32_t drop_reason)
{
	action_run = 5683704;
	mark_to_drop();

}

// Action
void _negative_mirror_5683730(uint32_t session_id)
{
	action_run = 5683730;
	mark_to_drop();

}

//Table
void rmac_5763151()
{
	if (meta.l3_metadata.rmac_group == 0x0001
	    && meta.l2_metadata.lkp_mac_da == 0x003333333333) {
		rmac_hit_0_5667340();
	} else {
		rmac_miss_0_5667356();	// default action
	}

}

//Table
void _ingress_port_mapping_0_5763316()
{
	if (standard_metadata.ingress_port == 0x0001) {
		_set_ifindex_5667439(0x01, 0x00);
	} else if (standard_metadata.ingress_port == 0x0002) {
		_set_ifindex_5667439(0x02, 0x00);
	} else {
		NoAction_173_5667255();	// default action
	}

}

//Table
void _ingress_port_properties_0_5763369()
{
	if (standard_metadata.ingress_port == 0x0001) {
		_set_ingress_port_properties_5667465(0x01, 0x00, 0x00, 0x00,
						     0x00, 0x00, 0x00);
	} else if (standard_metadata.ingress_port == 0x0002) {
		_set_ingress_port_properties_5667465(0x02, 0x00, 0x00, 0x00,
						     0x00, 0x00, 0x00);
	} else {
		NoAction_174_5667256();	// default action
	}

}

//Table
void _validate_outer_ethernet_0_5763871()
{
	_set_valid_outer_unicast_packet_untagged_5667657();	// default action
}

//Table
void _validate_outer_ipv4_packet_5764101()
{
	_set_valid_outer_ipv4_packet_0_5668250();	// default action
}

//Table
void _validate_outer_ipv6_packet_5764247()
{
	_set_valid_outer_ipv6_packet_0_5668385();	// default action
}

//Table
void _validate_mpls_packet_5764437()
{
	NoAction_178_5667260();	// default action
}

//Table
void _switch_config_params_0_5668845()
{
	_set_config_parameters_5668783(1);	// default action
}

//Table
void _port_vlan_mapping_0_5764924()
{
	_port_vlan_mapping_miss_5669060();	// default action
}

//Table
void _spanning_tree_0_5765071()
{
	NoAction_181_5667263();	// default action
}

//Table
void _ingress_qos_map_dscp_0_5765257()
{
	_nop_9_5653216();	// default action
}

//Table
void _ingress_qos_map_pcp_0_5765341()
{
	_nop_9_5653216();	// default action
}

//Table
void _ipsg_0_5765450()
{
	NoAction_184_5667266();	// default action
}

//Table
void _ipsg_permit_special_0_5765540()
{
	NoAction_185_5667267();	// default action
}

//Table
void _int_sink_update_outer_0_5766058()
{
	_nop_9_5653216();	// default action
}

//Table
void _int_source_0_5766147()
{
	_int_set_no_src_5669807();	// default action
}

//Table
void _int_terminate_0_5766284()
{
	_int_no_sink_5670156();	// default action
}

//Table
void _sflow_ing_take_sample_0_5766498()
{
	_nop_9_5653216();	// default action
}

//Table
void _sflow_ingress_0_5766625()
{
	_nop_9_5653216();	// default action
}

//Table
void _adjust_lkp_fields_0_5671707()
{
	if (hdr.ipv4.isValid == 1 && hdr.ipv6.isValid == 0) {
		_ipv4_lkp_5670858();
	} else if (hdr.ipv4.isValid == 0 && hdr.ipv6.isValid == 1) {
		_ipv6_lkp_5671015();
	} else {
		_non_ip_lkp_5670809();	// default action
	}

}

//Table
void _outer_rmac_0_5767703()
{
	if (meta.l3_metadata.rmac_group == 0x0002
	    && hdr.ethernet.dstAddr == 0x003333333333) {
		_outer_rmac_hit_5671182();
	} else {
		_on_miss_9_5669548();	// default action
	}

}

//Table
void _tunnel_0_5767775()
{
	if (meta.tunnel_metadata.tunnel_vni == 0x001234
	    && meta.tunnel_metadata.ingress_tunnel_type == 0x01
	    && hdr.inner_ipv4.isValid == 1 && hdr.inner_ipv6.isValid == 0) {
		_terminate_tunnel_inner_ethernet_ipv4_5671273(0x03e8, 0x01,
							      0x00, 0x00, 0x00,
							      0x00, 0x00, 0x00,
							      0x00, 0x00);
	} else {
		_tunnel_lookup_miss_5671208();	// default action
	}

}

//Table
void _tunnel_lookup_miss_2_5671974()
{
	_non_ip_lkp_5670809();	// default action
}

//Table
void _fabric_ingress_dst_lkp_5768505()
{
	NoAction_195_5667277();	// default action
}

//Table
void _fabric_ingress_src_lkp_5768584()
{
	NoAction_196_5667278();	// default action
}

//Table
void _native_packet_over_fabric_5672707()
{
	NoAction_197_5667279();	// default action
}

//Table
void _ipv4_dest_vtep_5768802()
{
	if (meta.l3_metadata.vrf == 0x0001 && hdr.ipv4.dstAddr == 0x0a0a0a01
	    && meta.tunnel_metadata.ingress_tunnel_type == 0x01) {
		_set_tunnel_termination_flag_1_5672796();
	} else {
		_nop_9_5653216();	// default action
	}

}

//Table
void _ipv4_src_vtep_5768891()
{
	if (meta.l3_metadata.vrf == 0x0001 && hdr.ipv4.srcAddr == 0x0a0a0a02
	    && meta.tunnel_metadata.ingress_tunnel_type == 0x01) {
		_src_vtep_hit_1_5672846(0x00);
	} else {
		_on_miss_9_5669548();	// default action
	}

}

//Table
void _ipv6_dest_vtep_5769052()
{
	_nop_9_5653216();	// default action
}

//Table
void _ipv6_src_vtep_5769141()
{
	_on_miss_9_5669548();	// default action
}

//Table
void _mpls_5769538()
{
	NoAction_202_5667284();	// default action
}

//Table
void _outer_ipv4_multicast_5769871()
{
	_on_miss_9_5669548();	// default action
}

//Table
void _outer_ipv4_multicast_star_g_5769978()
{
	_nop_9_5653216();	// default action
}

//Table
void _outer_ipv6_multicast_5770295()
{
	_on_miss_9_5669548();	// default action
}

//Table
void _outer_ipv6_multicast_star_g_5770402()
{
	_nop_9_5653216();	// default action
}

//Table
void _storm_control_0_5770554()
{
	_nop_9_5653216();	// default action
}

//Table
void _validate_packet_0_5770785()
{
	_nop_9_5653216();	// default action
}

//Table
void _ingress_l4_dst_port_0_5771004()
{
	_nop_9_5653216();	// default action
}

//Table
void _ingress_l4_src_port_0_5771064()
{
	_nop_9_5653216();	// default action
}

//Table
void _dmac_0_5771325()
{
	if (meta.ingress_metadata.bd == 0x03e8
	    && meta.l2_metadata.lkp_mac_da == 0x001111111111) {
		_dmac_hit_5675105(0x01);
	} else if (meta.ingress_metadata.bd == 0x03e8
		   && meta.l2_metadata.lkp_mac_da == 0x002222222222) {
		_dmac_redirect_nexthop_5675181(0x01);
	} else {
		_dmac_miss_5675159();	// default action
	}

}

//Table
void _smac_0_5771430()
{
	if (meta.ingress_metadata.bd == 0x03e8
	    && meta.l2_metadata.lkp_mac_sa == 0x001111111111) {
		_smac_hit_5675273(0x01);
	} else if (meta.ingress_metadata.bd == 0x03e8
		   && meta.l2_metadata.lkp_mac_sa == 0x002222222222) {
		_smac_hit_5675273(0x02);
	} else {
		_smac_miss_5675257();	// default action
	}

}

//Table
void _mac_acl_0_5771917()
{
	_nop_9_5653216();	// default action
}

//Table
void _ip_acl_0_5772828()
{
	_nop_9_5653216();	// default action
}

//Table
void _ipv6_acl_0_5773009()
{
	_nop_9_5653216();	// default action
}

//Table
void _ipv4_racl_0_5773444()
{
	_nop_9_5653216();	// default action
}

//Table
void _ipv4_urpf_0_5773669()
{
	_on_miss_9_5669548();	// default action
}

//Table
void _ipv4_urpf_lpm_0_5773741()
{
	_urpf_miss_5677550();	// default action
}

//Table
void _ipv4_fib_0_5773933()
{
	_on_miss_9_5669548();	// default action
}

//Table
void _ipv4_fib_lpm_0_5774011()
{
	_on_miss_9_5669548();	// default action
}

//Table
void _ipv6_racl_0_5774344()
{
	_nop_9_5653216();	// default action
}

//Table
void _ipv6_urpf_0_5774569()
{
	_on_miss_9_5669548();	// default action
}

//Table
void _ipv6_urpf_lpm_0_5774641()
{
	_urpf_miss_5677550();	// default action
}

//Table
void _ipv6_fib_0_5774833()
{
	_on_miss_9_5669548();	// default action
}

//Table
void _ipv6_fib_lpm_0_5774911()
{
	_on_miss_9_5669548();	// default action
}

//Table
void _urpf_bd_0_5775014()
{
	_urpf_bd_miss_5678837();	// default action
}

//Table
void _ipv4_multicast_bridge_5775182()
{
	_on_miss_9_5669548();	// default action
}

//Table
void _ipv4_multicast_bridge_star_g_5775266()
{
	_nop_9_5653216();	// default action
}

//Table
void _ipv4_multicast_route_5775404()
{
	_on_miss_9_5669548();	// default action
}

//Table
void _ipv4_multicast_route_star_g_5775614()
{
	_multicast_route_star_g_miss_1_5679308();	// default action
}

//Table
void _ipv6_multicast_bridge_5775791()
{
	_on_miss_9_5669548();	// default action
}

//Table
void _ipv6_multicast_bridge_star_g_5775874()
{
	_nop_9_5653216();	// default action
}

//Table
void _ipv6_multicast_route_5776012()
{
	_on_miss_9_5669548();	// default action
}

//Table
void _ipv6_multicast_route_star_g_5776222()
{
	_multicast_route_star_g_miss_2_5679896();	// default action
}

//Table
void _nat_dst_0_5776506()
{
	_on_miss_9_5669548();	// default action
}

//Table
void _nat_flow_0_5776602()
{
	_nop_9_5653216();	// default action
}

//Table
void _nat_src_0_5776733()
{
	_on_miss_9_5669548();	// default action
}

//Table
void _nat_twice_0_5776828()
{
	_on_miss_9_5669548();	// default action
}

//Table
void _meter_index_2_5776984()
{
	_nop_9_5653216();	// default action
}

//Table
void _compute_ipv4_hashes_0_5777352()
{
	_compute_lkp_ipv4_hash_5680789();	// default action
}

//Table
void _compute_ipv6_hashes_0_5777402()
{
	_compute_lkp_ipv6_hash_5680887();	// default action
}

//Table
void _compute_non_ip_hashes_0_5777451()
{
	_compute_lkp_non_ip_hash_5680985();	// default action
}

//Table
void _compute_other_hashes_0_5777500()
{
	_computed_two_hashes_5681031();	// default action
}

//Table
void _meter_action_0_5777609()
{
	_meter_permit_5681306();	// default action
}

//Table
void _ingress_bd_stats_2_5681458()
{
	_update_ingress_bd_stats_5681436();	// default action
}

//Table
void _acl_stats_2_5681537()
{
	_acl_stats_update_5681515();	// default action
}

//Table
void _storm_control_stats_2_5777874()
{
	_nop_9_5653216();	// default action
}

//Table
void _fwd_result_0_5778353()
{
		_nop_9_5653216();	// default action
}

//Table
void _ecmp_group_0_5778848()
{
	NoAction_249_5667331();	// default action
}

//Table
void _nexthop_0_5778930()
{
	if (meta.l3_metadata.nexthop_index == 0x0001) {
		_set_nexthop_details_5682447(0x02, 0x03e8, 0x01);
	} else {
		_nop_9_5653216();	// default action
	}

}

//Table
void _bd_flood_0_5779023()
{
	if (meta.ingress_metadata.bd == 0x000a
	    && meta.l2_metadata.lkp_pkt_type == 0x01) {
		_set_bd_flood_mc_index_5682696(0x00);
	} else if (meta.ingress_metadata.bd == 0x03e8
		   && meta.l2_metadata.lkp_pkt_type == 0x01) {
		_set_bd_flood_mc_index_5682696(0x00);
	} else {
		_nop_9_5653216();	// default action
	}

}

//Table
void _lag_group_0_5779148()
{
	NoAction_252_5667334();	// default action
}

//Table
void _learn_notify_0_5779273()
{
	_nop_9_5653216();	// default action
}

//Table
void _fabric_lag_0_5779404()
{
	_nop_9_5653216();	// default action
}

//Table
void _traffic_class_0_5779554()
{
	_nop_9_5653216();	// default action
}

//Table
void _drop_stats_4_5683771()
{
	_drop_stats_update_5683347();	// default action
}

//Table
void _system_acl_0_5780142()
{
	_nop_9_5653216();	// default action
}

//Control

void DeparserImpl()
{
}

typedef struct {
	uint8_t field_41:4;
	uint8_t field_42:4;
	uint8_t field_43:8;
	uint32_t field_44:16;
	uint32_t field_45:16;
	uint8_t field_46:3;
	uint32_t field_47:13;
	uint8_t field_48:8;
	uint8_t field_49:8;
	uint32_t field_50:32;
	uint32_t field_51:32;
} tuple_10;

//Control

void verifyChecksum()
{
	verify_checksum();
	verify_checksum();
}

//Control

void computeChecksum()
{
	update_checksum();
	update_checksum();
}

void SpecifyLayout()
{
   hdr.bfd.isValid = 0;
   /*
   // TODO: should set all isValid to 0
	eompls;
	erspan_t3_header;
	ethernet;
	fabric_header;
	fabric_header_cpu;
	fabric_header_mirror;
	fabric_header_multicast;
	fabric_header_sflow;
	fabric_header_unicast;
	fabric_payload_header;
	fcoe;
	genv;
	gre;
	icmp;
	inner_ethernet;
	inner_icmp;
	inner_ipv4;
	inner_ipv6;
	inner_sctp;
	inner_tcp;
	inner_udp;
	int_egress_port_id_header;
   int_egress_port_tx_utilization_header;
	int_header;
	int_hop_latency_header;
	int_ingress_port_id_header;
	int_ingress_tstamp_header;
	int_q_congestion_header;
	int_q_occupancy_header;
	int_switch_id_header;
	ipv4;
	ipv6;
	lisp;
	llc_header;
	nsh;
	nsh_context;
	nvgre;
	outer_udp;
	roce;
	roce_v2;
	sctp;
	sflow;
	sflow_raw_hdr_record;
	sflow_sample;
	snap_header;
	tcp;
	trill;
	udp;
	vntag;
	vxlan;
	vxlan_gpe;
	vxlan_gpe_int_header;
	mpls[3];
	vlan_tag_[2];
   */
}

int main()
{
	ParserImpl();
   SpecifyLayout();
	ingress();
	egress();
	DeparserImpl();
	end_assertions();
	return 0;
}

void assert_error(int id, char msg[])
{
	klee_print_once(id, msg);
	//klee_abort();
}

void end_assertions()
{
}
