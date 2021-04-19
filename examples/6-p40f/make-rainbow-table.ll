; ModuleID = 'make-rainbow-table.c'
source_filename = "make-rainbow-table.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%struct.hash_key_t = type <{ i32, i8, i16 }>

@.str = private unnamed_addr constant [5 x i8] c"%08X\00", align 1
@.str.1 = private unnamed_addr constant [8 x i8] c" %02hhX\00", align 1
@.str.2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@stderr = external global %struct._IO_FILE*, align 8
@.str.3 = private unnamed_addr constant [21 x i8] c"Usage: %s [entries]\0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define i32 @hash_function(%struct.hash_key_t*) #0 !dbg !13 {
  %2 = alloca %struct.hash_key_t*, align 8
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store %struct.hash_key_t* %0, %struct.hash_key_t** %2, align 8
  call void @llvm.dbg.declare(metadata %struct.hash_key_t** %2, metadata !27, metadata !DIExpression()), !dbg !28
  call void @llvm.dbg.declare(metadata i32* %3, metadata !29, metadata !DIExpression()), !dbg !30
  call void @llvm.dbg.declare(metadata i32* %4, metadata !31, metadata !DIExpression()), !dbg !32
  call void @llvm.dbg.declare(metadata i32* %5, metadata !33, metadata !DIExpression()), !dbg !34
  store i32 -559038730, i32* %5, align 4, !dbg !35
  store i32 -559038730, i32* %4, align 4, !dbg !36
  store i32 -559038730, i32* %3, align 4, !dbg !37
  %6 = load %struct.hash_key_t*, %struct.hash_key_t** %2, align 8, !dbg !38
  %7 = getelementptr inbounds %struct.hash_key_t, %struct.hash_key_t* %6, i32 0, i32 0, !dbg !39
  %8 = load i32, i32* %7, align 1, !dbg !39
  %9 = load i32, i32* %3, align 4, !dbg !40
  %10 = add i32 %9, %8, !dbg !40
  store i32 %10, i32* %3, align 4, !dbg !40
  %11 = load %struct.hash_key_t*, %struct.hash_key_t** %2, align 8, !dbg !41
  %12 = getelementptr inbounds %struct.hash_key_t, %struct.hash_key_t* %11, i32 0, i32 1, !dbg !42
  %13 = load i8, i8* %12, align 1, !dbg !42
  %14 = zext i8 %13 to i32, !dbg !41
  %15 = load i32, i32* %4, align 4, !dbg !43
  %16 = add i32 %15, %14, !dbg !43
  store i32 %16, i32* %4, align 4, !dbg !43
  %17 = load %struct.hash_key_t*, %struct.hash_key_t** %2, align 8, !dbg !44
  %18 = getelementptr inbounds %struct.hash_key_t, %struct.hash_key_t* %17, i32 0, i32 2, !dbg !45
  %19 = load i16, i16* %18, align 1, !dbg !45
  %20 = zext i16 %19 to i32, !dbg !44
  %21 = load i32, i32* %5, align 4, !dbg !46
  %22 = add i32 %21, %20, !dbg !46
  store i32 %22, i32* %5, align 4, !dbg !46
  %23 = load i32, i32* %4, align 4, !dbg !47
  %24 = load i32, i32* %5, align 4, !dbg !47
  %25 = xor i32 %24, %23, !dbg !47
  store i32 %25, i32* %5, align 4, !dbg !47
  %26 = load i32, i32* %4, align 4, !dbg !47
  %27 = shl i32 %26, 14, !dbg !47
  %28 = load i32, i32* %4, align 4, !dbg !47
  %29 = lshr i32 %28, 18, !dbg !47
  %30 = or i32 %27, %29, !dbg !47
  %31 = load i32, i32* %5, align 4, !dbg !47
  %32 = sub i32 %31, %30, !dbg !47
  store i32 %32, i32* %5, align 4, !dbg !47
  %33 = load i32, i32* %5, align 4, !dbg !47
  %34 = load i32, i32* %3, align 4, !dbg !47
  %35 = xor i32 %34, %33, !dbg !47
  store i32 %35, i32* %3, align 4, !dbg !47
  %36 = load i32, i32* %5, align 4, !dbg !47
  %37 = shl i32 %36, 11, !dbg !47
  %38 = load i32, i32* %5, align 4, !dbg !47
  %39 = lshr i32 %38, 21, !dbg !47
  %40 = or i32 %37, %39, !dbg !47
  %41 = load i32, i32* %3, align 4, !dbg !47
  %42 = sub i32 %41, %40, !dbg !47
  store i32 %42, i32* %3, align 4, !dbg !47
  %43 = load i32, i32* %3, align 4, !dbg !47
  %44 = load i32, i32* %4, align 4, !dbg !47
  %45 = xor i32 %44, %43, !dbg !47
  store i32 %45, i32* %4, align 4, !dbg !47
  %46 = load i32, i32* %3, align 4, !dbg !47
  %47 = shl i32 %46, 25, !dbg !47
  %48 = load i32, i32* %3, align 4, !dbg !47
  %49 = lshr i32 %48, 7, !dbg !47
  %50 = or i32 %47, %49, !dbg !47
  %51 = load i32, i32* %4, align 4, !dbg !47
  %52 = sub i32 %51, %50, !dbg !47
  store i32 %52, i32* %4, align 4, !dbg !47
  %53 = load i32, i32* %4, align 4, !dbg !47
  %54 = load i32, i32* %5, align 4, !dbg !47
  %55 = xor i32 %54, %53, !dbg !47
  store i32 %55, i32* %5, align 4, !dbg !47
  %56 = load i32, i32* %4, align 4, !dbg !47
  %57 = shl i32 %56, 16, !dbg !47
  %58 = load i32, i32* %4, align 4, !dbg !47
  %59 = lshr i32 %58, 16, !dbg !47
  %60 = or i32 %57, %59, !dbg !47
  %61 = load i32, i32* %5, align 4, !dbg !47
  %62 = sub i32 %61, %60, !dbg !47
  store i32 %62, i32* %5, align 4, !dbg !47
  %63 = load i32, i32* %5, align 4, !dbg !47
  %64 = load i32, i32* %3, align 4, !dbg !47
  %65 = xor i32 %64, %63, !dbg !47
  store i32 %65, i32* %3, align 4, !dbg !47
  %66 = load i32, i32* %5, align 4, !dbg !47
  %67 = shl i32 %66, 4, !dbg !47
  %68 = load i32, i32* %5, align 4, !dbg !47
  %69 = lshr i32 %68, 28, !dbg !47
  %70 = or i32 %67, %69, !dbg !47
  %71 = load i32, i32* %3, align 4, !dbg !47
  %72 = sub i32 %71, %70, !dbg !47
  store i32 %72, i32* %3, align 4, !dbg !47
  %73 = load i32, i32* %3, align 4, !dbg !47
  %74 = load i32, i32* %4, align 4, !dbg !47
  %75 = xor i32 %74, %73, !dbg !47
  store i32 %75, i32* %4, align 4, !dbg !47
  %76 = load i32, i32* %3, align 4, !dbg !47
  %77 = shl i32 %76, 14, !dbg !47
  %78 = load i32, i32* %3, align 4, !dbg !47
  %79 = lshr i32 %78, 18, !dbg !47
  %80 = or i32 %77, %79, !dbg !47
  %81 = load i32, i32* %4, align 4, !dbg !47
  %82 = sub i32 %81, %80, !dbg !47
  store i32 %82, i32* %4, align 4, !dbg !47
  %83 = load i32, i32* %4, align 4, !dbg !47
  %84 = load i32, i32* %5, align 4, !dbg !47
  %85 = xor i32 %84, %83, !dbg !47
  store i32 %85, i32* %5, align 4, !dbg !47
  %86 = load i32, i32* %4, align 4, !dbg !47
  %87 = shl i32 %86, 24, !dbg !47
  %88 = load i32, i32* %4, align 4, !dbg !47
  %89 = lshr i32 %88, 8, !dbg !47
  %90 = or i32 %87, %89, !dbg !47
  %91 = load i32, i32* %5, align 4, !dbg !47
  %92 = sub i32 %91, %90, !dbg !47
  store i32 %92, i32* %5, align 4, !dbg !47
  %93 = load i32, i32* %5, align 4, !dbg !49
  ret i32 %93, !dbg !50
}

; Function Attrs: nounwind readnone speculatable
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind optnone uwtable
define void @generate_entry(%struct.hash_key_t*) #0 !dbg !51 {
  %2 = alloca %struct.hash_key_t*, align 8
  %3 = alloca i16, align 2
  %4 = alloca i32, align 4
  store %struct.hash_key_t* %0, %struct.hash_key_t** %2, align 8
  call void @llvm.dbg.declare(metadata %struct.hash_key_t** %2, metadata !54, metadata !DIExpression()), !dbg !55
  call void @llvm.dbg.declare(metadata i16* %3, metadata !56, metadata !DIExpression()), !dbg !57
  %5 = load %struct.hash_key_t*, %struct.hash_key_t** %2, align 8, !dbg !58
  %6 = call i32 @hash_function(%struct.hash_key_t* %5), !dbg !59
  %7 = urem i32 %6, 64, !dbg !60
  %8 = trunc i32 %7 to i16, !dbg !59
  store i16 %8, i16* %3, align 2, !dbg !57
  %9 = load i16, i16* %3, align 2, !dbg !61
  %10 = zext i16 %9 to i32, !dbg !61
  %11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i32 0, i32 0), i32 %10), !dbg !62
  call void @llvm.dbg.declare(metadata i32* %4, metadata !63, metadata !DIExpression()), !dbg !66
  store i32 0, i32* %4, align 4, !dbg !66
  br label %12, !dbg !67

; <label>:12:                                     ; preds = %25, %1
  %13 = load i32, i32* %4, align 4, !dbg !68
  %14 = sext i32 %13 to i64, !dbg !68
  %15 = icmp ult i64 %14, 7, !dbg !70
  br i1 %15, label %16, label %28, !dbg !71

; <label>:16:                                     ; preds = %12
  %17 = load %struct.hash_key_t*, %struct.hash_key_t** %2, align 8, !dbg !72
  %18 = bitcast %struct.hash_key_t* %17 to i8*, !dbg !74
  %19 = load i32, i32* %4, align 4, !dbg !75
  %20 = sext i32 %19 to i64, !dbg !74
  %21 = getelementptr inbounds i8, i8* %18, i64 %20, !dbg !74
  %22 = load i8, i8* %21, align 1, !dbg !74
  %23 = sext i8 %22 to i32, !dbg !74
  %24 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i32 0, i32 0), i32 %23), !dbg !76
  br label %25, !dbg !77

; <label>:25:                                     ; preds = %16
  %26 = load i32, i32* %4, align 4, !dbg !78
  %27 = add nsw i32 %26, 1, !dbg !78
  store i32 %27, i32* %4, align 4, !dbg !78
  br label %12, !dbg !79, !llvm.loop !80

; <label>:28:                                     ; preds = %12
  %29 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.2, i32 0, i32 0)), !dbg !82
  ret void, !dbg !83
}

declare i32 @printf(i8*, ...) #2

; Function Attrs: noinline nounwind optnone uwtable
define i32 @main(i32, i8**) #0 !dbg !84 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca i64, align 8
  %7 = alloca %struct.hash_key_t, align 1
  %8 = alloca i64, align 8
  %9 = alloca i32, align 4
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  call void @llvm.dbg.declare(metadata i32* %4, metadata !88, metadata !DIExpression()), !dbg !89
  store i8** %1, i8*** %5, align 8
  call void @llvm.dbg.declare(metadata i8*** %5, metadata !90, metadata !DIExpression()), !dbg !91
  call void @llvm.dbg.declare(metadata i64* %6, metadata !92, metadata !DIExpression()), !dbg !94
  %10 = load i32, i32* %4, align 4, !dbg !95
  %11 = icmp eq i32 %10, 1, !dbg !97
  br i1 %11, label %12, label %13, !dbg !98

; <label>:12:                                     ; preds = %2
  store i64 9223372036854775807, i64* %6, align 8, !dbg !99
  br label %28, !dbg !101

; <label>:13:                                     ; preds = %2
  %14 = load i32, i32* %4, align 4, !dbg !102
  %15 = icmp eq i32 %14, 2, !dbg !104
  br i1 %15, label %16, label %21, !dbg !105

; <label>:16:                                     ; preds = %13
  %17 = load i8**, i8*** %5, align 8, !dbg !106
  %18 = getelementptr inbounds i8*, i8** %17, i64 1, !dbg !106
  %19 = load i8*, i8** %18, align 8, !dbg !106
  %20 = call i64 @atoll(i8* %19) #6, !dbg !108
  store i64 %20, i64* %6, align 8, !dbg !109
  br label %27, !dbg !110

; <label>:21:                                     ; preds = %13
  %22 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !111
  %23 = load i8**, i8*** %5, align 8, !dbg !113
  %24 = getelementptr inbounds i8*, i8** %23, i64 0, !dbg !113
  %25 = load i8*, i8** %24, align 8, !dbg !113
  %26 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %22, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.3, i32 0, i32 0), i8* %25), !dbg !114
  call void @exit(i32 1) #7, !dbg !115
  unreachable, !dbg !115

; <label>:27:                                     ; preds = %16
  br label %28

; <label>:28:                                     ; preds = %27, %12
  %29 = call i64 @time(i64* null) #8, !dbg !116
  %30 = trunc i64 %29 to i32, !dbg !116
  call void @srand(i32 %30) #8, !dbg !117
  call void @llvm.dbg.declare(metadata %struct.hash_key_t* %7, metadata !118, metadata !DIExpression()), !dbg !119
  call void @llvm.dbg.declare(metadata i64* %8, metadata !120, metadata !DIExpression()), !dbg !122
  store i64 0, i64* %8, align 8, !dbg !122
  br label %31, !dbg !123

; <label>:31:                                     ; preds = %51, %28
  %32 = load i64, i64* %8, align 8, !dbg !124
  %33 = load i64, i64* %6, align 8, !dbg !126
  %34 = icmp slt i64 %32, %33, !dbg !127
  br i1 %34, label %35, label %54, !dbg !128

; <label>:35:                                     ; preds = %31
  call void @llvm.dbg.declare(metadata i32* %9, metadata !129, metadata !DIExpression()), !dbg !132
  store i32 0, i32* %9, align 4, !dbg !132
  br label %36, !dbg !133

; <label>:36:                                     ; preds = %47, %35
  %37 = load i32, i32* %9, align 4, !dbg !134
  %38 = sext i32 %37 to i64, !dbg !134
  %39 = icmp ult i64 %38, 7, !dbg !136
  br i1 %39, label %40, label %50, !dbg !137

; <label>:40:                                     ; preds = %36
  %41 = call i32 @rand() #8, !dbg !138
  %42 = trunc i32 %41 to i8, !dbg !138
  %43 = bitcast %struct.hash_key_t* %7 to i8*, !dbg !140
  %44 = load i32, i32* %9, align 4, !dbg !141
  %45 = sext i32 %44 to i64, !dbg !140
  %46 = getelementptr inbounds i8, i8* %43, i64 %45, !dbg !140
  store i8 %42, i8* %46, align 1, !dbg !142
  br label %47, !dbg !143

; <label>:47:                                     ; preds = %40
  %48 = load i32, i32* %9, align 4, !dbg !144
  %49 = add nsw i32 %48, 1, !dbg !144
  store i32 %49, i32* %9, align 4, !dbg !144
  br label %36, !dbg !145, !llvm.loop !146

; <label>:50:                                     ; preds = %36
  call void @generate_entry(%struct.hash_key_t* %7), !dbg !148
  br label %51, !dbg !149

; <label>:51:                                     ; preds = %50
  %52 = load i64, i64* %8, align 8, !dbg !150
  %53 = add nsw i64 %52, 2, !dbg !150
  store i64 %53, i64* %8, align 8, !dbg !150
  br label %31, !dbg !151, !llvm.loop !152

; <label>:54:                                     ; preds = %31
  ret i32 0, !dbg !154
}

; Function Attrs: nounwind readonly
declare i64 @atoll(i8*) #3

declare i32 @fprintf(%struct._IO_FILE*, i8*, ...) #2

; Function Attrs: noreturn nounwind
declare void @exit(i32) #4

; Function Attrs: nounwind
declare void @srand(i32) #5

; Function Attrs: nounwind
declare i64 @time(i64*) #5

; Function Attrs: nounwind
declare i32 @rand() #5

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { noreturn nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind readonly }
attributes #7 = { noreturn nounwind }
attributes #8 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!9, !10, !11}
!llvm.ident = !{!12}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 6.0.0-1ubuntu2~16.04.1 (tags/RELEASE_600/final)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, retainedTypes: !3)
!1 = !DIFile(filename: "make-rainbow-table.c", directory: "/home/qiaokang/dpattacks/translation/6-p40f")
!2 = !{}
!3 = !{!4, !7}
!4 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !5, line: 51, baseType: !6)
!5 = !DIFile(filename: "/usr/include/stdint.h", directory: "/home/qiaokang/dpattacks/translation/6-p40f")
!6 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!7 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64)
!8 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!9 = !{i32 2, !"Dwarf Version", i32 4}
!10 = !{i32 2, !"Debug Info Version", i32 3}
!11 = !{i32 1, !"wchar_size", i32 4}
!12 = !{!"clang version 6.0.0-1ubuntu2~16.04.1 (tags/RELEASE_600/final)"}
!13 = distinct !DISubprogram(name: "hash_function", scope: !1, file: !1, line: 61, type: !14, isLocal: false, isDefinition: true, scopeLine: 61, flags: DIFlagPrototyped, isOptimized: false, unit: !0, variables: !2)
!14 = !DISubroutineType(types: !15)
!15 = !{!4, !16}
!16 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !17, size: 64)
!17 = !DIDerivedType(tag: DW_TAG_typedef, name: "hash_key_t", file: !1, line: 17, baseType: !18)
!18 = distinct !DICompositeType(tag: DW_TAG_structure_type, file: !1, line: 13, size: 56, elements: !19)
!19 = !{!20, !21, !24}
!20 = !DIDerivedType(tag: DW_TAG_member, name: "src_ip", scope: !18, file: !1, line: 14, baseType: !4, size: 32)
!21 = !DIDerivedType(tag: DW_TAG_member, name: "proto", scope: !18, file: !1, line: 15, baseType: !22, size: 8, offset: 32)
!22 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !5, line: 48, baseType: !23)
!23 = !DIBasicType(name: "unsigned char", size: 8, encoding: DW_ATE_unsigned_char)
!24 = !DIDerivedType(tag: DW_TAG_member, name: "src_port", scope: !18, file: !1, line: 16, baseType: !25, size: 16, offset: 40)
!25 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint16_t", file: !5, line: 49, baseType: !26)
!26 = !DIBasicType(name: "unsigned short", size: 16, encoding: DW_ATE_unsigned)
!27 = !DILocalVariable(name: "key", arg: 1, scope: !13, file: !1, line: 61, type: !16)
!28 = !DILocation(line: 61, column: 36, scope: !13)
!29 = !DILocalVariable(name: "a", scope: !13, file: !1, line: 63, type: !4)
!30 = !DILocation(line: 63, column: 12, scope: !13)
!31 = !DILocalVariable(name: "b", scope: !13, file: !1, line: 63, type: !4)
!32 = !DILocation(line: 63, column: 15, scope: !13)
!33 = !DILocalVariable(name: "c", scope: !13, file: !1, line: 63, type: !4)
!34 = !DILocation(line: 63, column: 18, scope: !13)
!35 = !DILocation(line: 65, column: 13, scope: !13)
!36 = !DILocation(line: 65, column: 9, scope: !13)
!37 = !DILocation(line: 65, column: 5, scope: !13)
!38 = !DILocation(line: 67, column: 8, scope: !13)
!39 = !DILocation(line: 67, column: 13, scope: !13)
!40 = !DILocation(line: 67, column: 5, scope: !13)
!41 = !DILocation(line: 68, column: 8, scope: !13)
!42 = !DILocation(line: 68, column: 13, scope: !13)
!43 = !DILocation(line: 68, column: 5, scope: !13)
!44 = !DILocation(line: 69, column: 8, scope: !13)
!45 = !DILocation(line: 69, column: 13, scope: !13)
!46 = !DILocation(line: 69, column: 5, scope: !13)
!47 = !DILocation(line: 71, column: 3, scope: !48)
!48 = distinct !DILexicalBlock(scope: !13, file: !1, line: 71, column: 3)
!49 = !DILocation(line: 72, column: 10, scope: !13)
!50 = !DILocation(line: 72, column: 3, scope: !13)
!51 = distinct !DISubprogram(name: "generate_entry", scope: !1, file: !1, line: 75, type: !52, isLocal: false, isDefinition: true, scopeLine: 75, flags: DIFlagPrototyped, isOptimized: false, unit: !0, variables: !2)
!52 = !DISubroutineType(types: !53)
!53 = !{null, !16}
!54 = !DILocalVariable(name: "key", arg: 1, scope: !51, file: !1, line: 75, type: !16)
!55 = !DILocation(line: 75, column: 33, scope: !51)
!56 = !DILocalVariable(name: "hash", scope: !51, file: !1, line: 77, type: !25)
!57 = !DILocation(line: 77, column: 12, scope: !51)
!58 = !DILocation(line: 77, column: 33, scope: !51)
!59 = !DILocation(line: 77, column: 19, scope: !51)
!60 = !DILocation(line: 77, column: 38, scope: !51)
!61 = !DILocation(line: 79, column: 18, scope: !51)
!62 = !DILocation(line: 79, column: 3, scope: !51)
!63 = !DILocalVariable(name: "i", scope: !64, file: !1, line: 80, type: !65)
!64 = distinct !DILexicalBlock(scope: !51, file: !1, line: 80, column: 3)
!65 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!66 = !DILocation(line: 80, column: 12, scope: !64)
!67 = !DILocation(line: 80, column: 8, scope: !64)
!68 = !DILocation(line: 80, column: 19, scope: !69)
!69 = distinct !DILexicalBlock(scope: !64, file: !1, line: 80, column: 3)
!70 = !DILocation(line: 80, column: 21, scope: !69)
!71 = !DILocation(line: 80, column: 3, scope: !64)
!72 = !DILocation(line: 81, column: 32, scope: !73)
!73 = distinct !DILexicalBlock(scope: !69, file: !1, line: 80, column: 42)
!74 = !DILocation(line: 81, column: 23, scope: !73)
!75 = !DILocation(line: 81, column: 37, scope: !73)
!76 = !DILocation(line: 81, column: 5, scope: !73)
!77 = !DILocation(line: 82, column: 3, scope: !73)
!78 = !DILocation(line: 80, column: 38, scope: !69)
!79 = !DILocation(line: 80, column: 3, scope: !69)
!80 = distinct !{!80, !71, !81}
!81 = !DILocation(line: 82, column: 3, scope: !64)
!82 = !DILocation(line: 83, column: 3, scope: !51)
!83 = !DILocation(line: 84, column: 1, scope: !51)
!84 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 86, type: !85, isLocal: false, isDefinition: true, scopeLine: 86, flags: DIFlagPrototyped, isOptimized: false, unit: !0, variables: !2)
!85 = !DISubroutineType(types: !86)
!86 = !{!65, !65, !87}
!87 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !7, size: 64)
!88 = !DILocalVariable(name: "argc", arg: 1, scope: !84, file: !1, line: 86, type: !65)
!89 = !DILocation(line: 86, column: 14, scope: !84)
!90 = !DILocalVariable(name: "argv", arg: 2, scope: !84, file: !1, line: 86, type: !87)
!91 = !DILocation(line: 86, column: 26, scope: !84)
!92 = !DILocalVariable(name: "num_entries", scope: !84, file: !1, line: 87, type: !93)
!93 = !DIBasicType(name: "long long int", size: 64, encoding: DW_ATE_signed)
!94 = !DILocation(line: 87, column: 13, scope: !84)
!95 = !DILocation(line: 88, column: 7, scope: !96)
!96 = distinct !DILexicalBlock(scope: !84, file: !1, line: 88, column: 7)
!97 = !DILocation(line: 88, column: 12, scope: !96)
!98 = !DILocation(line: 88, column: 7, scope: !84)
!99 = !DILocation(line: 89, column: 17, scope: !100)
!100 = distinct !DILexicalBlock(scope: !96, file: !1, line: 88, column: 18)
!101 = !DILocation(line: 90, column: 3, scope: !100)
!102 = !DILocation(line: 90, column: 14, scope: !103)
!103 = distinct !DILexicalBlock(scope: !96, file: !1, line: 90, column: 14)
!104 = !DILocation(line: 90, column: 19, scope: !103)
!105 = !DILocation(line: 90, column: 14, scope: !96)
!106 = !DILocation(line: 91, column: 25, scope: !107)
!107 = distinct !DILexicalBlock(scope: !103, file: !1, line: 90, column: 25)
!108 = !DILocation(line: 91, column: 19, scope: !107)
!109 = !DILocation(line: 91, column: 17, scope: !107)
!110 = !DILocation(line: 92, column: 3, scope: !107)
!111 = !DILocation(line: 93, column: 13, scope: !112)
!112 = distinct !DILexicalBlock(scope: !103, file: !1, line: 92, column: 10)
!113 = !DILocation(line: 93, column: 46, scope: !112)
!114 = !DILocation(line: 93, column: 5, scope: !112)
!115 = !DILocation(line: 94, column: 5, scope: !112)
!116 = !DILocation(line: 97, column: 9, scope: !84)
!117 = !DILocation(line: 97, column: 3, scope: !84)
!118 = !DILocalVariable(name: "key", scope: !84, file: !1, line: 99, type: !17)
!119 = !DILocation(line: 99, column: 14, scope: !84)
!120 = !DILocalVariable(name: "count", scope: !121, file: !1, line: 101, type: !93)
!121 = distinct !DILexicalBlock(scope: !84, file: !1, line: 101, column: 3)
!122 = !DILocation(line: 101, column: 18, scope: !121)
!123 = !DILocation(line: 101, column: 8, scope: !121)
!124 = !DILocation(line: 101, column: 29, scope: !125)
!125 = distinct !DILexicalBlock(scope: !121, file: !1, line: 101, column: 3)
!126 = !DILocation(line: 101, column: 37, scope: !125)
!127 = !DILocation(line: 101, column: 35, scope: !125)
!128 = !DILocation(line: 101, column: 3, scope: !121)
!129 = !DILocalVariable(name: "b", scope: !130, file: !1, line: 102, type: !65)
!130 = distinct !DILexicalBlock(scope: !131, file: !1, line: 102, column: 5)
!131 = distinct !DILexicalBlock(scope: !125, file: !1, line: 101, column: 62)
!132 = !DILocation(line: 102, column: 14, scope: !130)
!133 = !DILocation(line: 102, column: 10, scope: !130)
!134 = !DILocation(line: 102, column: 21, scope: !135)
!135 = distinct !DILexicalBlock(scope: !130, file: !1, line: 102, column: 5)
!136 = !DILocation(line: 102, column: 23, scope: !135)
!137 = !DILocation(line: 102, column: 5, scope: !130)
!138 = !DILocation(line: 103, column: 27, scope: !139)
!139 = distinct !DILexicalBlock(scope: !135, file: !1, line: 102, column: 43)
!140 = !DILocation(line: 103, column: 7, scope: !139)
!141 = !DILocation(line: 103, column: 22, scope: !139)
!142 = !DILocation(line: 103, column: 25, scope: !139)
!143 = !DILocation(line: 104, column: 5, scope: !139)
!144 = !DILocation(line: 102, column: 39, scope: !135)
!145 = !DILocation(line: 102, column: 5, scope: !135)
!146 = distinct !{!146, !137, !147}
!147 = !DILocation(line: 104, column: 5, scope: !130)
!148 = !DILocation(line: 106, column: 5, scope: !131)
!149 = !DILocation(line: 107, column: 3, scope: !131)
!150 = !DILocation(line: 101, column: 56, scope: !125)
!151 = !DILocation(line: 101, column: 3, scope: !125)
!152 = distinct !{!152, !128, !153}
!153 = !DILocation(line: 107, column: 3, scope: !121)
!154 = !DILocation(line: 109, column: 3, scope: !84)
