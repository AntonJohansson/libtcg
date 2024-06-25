#include "helper2tcg/tcg_global_mappings.h"
#include "cpu.h"

extern TCGv cpu_cc_dst, cpu_cc_src, cpu_cc_src2;
extern TCGv cpu_eip;
extern TCGv_i32 cpu_cc_op;
extern TCGv cpu_regs[CPU_NB_REGS];
extern TCGv cpu_seg_base[6];
extern TCGv_i64 cpu_bndl[4];
extern TCGv_i64 cpu_bndu[4];

static const char *reg_names[CPU_NB_REGS] = {
#ifdef TARGET_X86_64
    [R_EAX] = "rax",
    [R_EBX] = "rbx",
    [R_ECX] = "rcx",
    [R_EDX] = "rdx",
    [R_ESI] = "rsi",
    [R_EDI] = "rdi",
    [R_EBP] = "rbp",
    [R_ESP] = "rsp",
    [8]  = "r8",
    [9]  = "r9",
    [10] = "r10",
    [11] = "r11",
    [12] = "r12",
    [13] = "r13",
    [14] = "r14",
    [15] = "r15",
    #else
    [R_EAX] = "eax",
    [R_EBX] = "ebx",
    [R_ECX] = "ecx",
    [R_EDX] = "edx",
    [R_ESI] = "esi",
    [R_EDI] = "edi",
    [R_EBP] = "ebp",
    [R_ESP] = "esp",
    #endif
};
static const char eip_name[] = {
#ifdef TARGET_X86_64
    "rip"
#else
    "eip"
#endif
};
static const char *seg_base_names[6] = {
    [R_CS] = "cs_base",
    [R_DS] = "ds_base",
    [R_ES] = "es_base",
    [R_FS] = "fs_base",
    [R_GS] = "gs_base",
    [R_SS] = "ss_base",
};
static const char *bnd_regl_names[4] = {
    "bnd0_lb", "bnd1_lb", "bnd2_lb", "bnd3_lb"
};
static const char *bnd_regu_names[4] = {
    "bnd0_ub", "bnd1_ub", "bnd2_ub", "bnd3_ub"
};

cpu_tcg_mapping tcg_global_mappings[] = {
    cpu_tcg_map(cpu_cc_op,    cc_op,    "cc_op"),
    cpu_tcg_map(cpu_cc_dst,   cc_dst,   "cc_dst"),
    cpu_tcg_map(cpu_cc_src,   cc_src,   "cc_src"),
    cpu_tcg_map(cpu_cc_src2,  cc_src2,  "cc_src2"),
    cpu_tcg_map(cpu_eip,      eip,      eip_name),

    cpu_tcg_map_array(cpu_regs,  regs,  reg_names),
    cpu_tcg_map_array_of_structs(cpu_seg_base, segs, base, seg_base_names),

    cpu_tcg_map_array_of_structs(cpu_bndl, bnd_regs, lb, bnd_regl_names),
    cpu_tcg_map_array_of_structs(cpu_bndu, bnd_regs, ub, bnd_regu_names),
};

size_t tcg_global_mapping_count = ARRAY_SIZE(tcg_global_mappings);
