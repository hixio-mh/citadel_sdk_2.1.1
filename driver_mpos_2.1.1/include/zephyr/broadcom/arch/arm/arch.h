/*
 * Copyright (c) 2013-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief ARM specific kernel interface header
 *
 * This header contains the ARM specific kernel interface.  It is
 * included by the kernel interface architecture-abstraction header
 * (include/arc/cpu.h)
 */

#ifndef _ARM_ARCH__H_
#define _ARM_ARCH__H_

/* Add include for DTS generated information */
#include <generated_dts_board.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ARM GPRs are often designated by two different names */
#define sys_define_gpr_with_alias(name1, name2) union { u32_t name1, name2; }

/* APIs need to support non-byte addressable architectures */

#define OCTET_TO_SIZEOFUNIT(X) (X)
#define SIZEOFUNIT_TO_OCTET(X) (X)

#ifdef CONFIG_CPU_CORTEX_M
#include <arch/arm/cortex_m/irq.h>
#include <arch/arm/cortex_m/misc.h>
#include <arch/arm/cortex_m/sys_io.h>
#elif defined(CONFIG_CPU_CORTEX_A)
#include <arch/arm/cortex_a/asm_inline.h>
#include <arch/arm/cortex_a/irq.h>
#include <arch/arm/cortex_a/sys_io.h>
#include <arch/arm/cortex_a/misc.h>
#else
#error Undefined ARM CPU architecture
#endif

#define STACK_ALIGN  4

#ifdef __cplusplus
}
#endif

#endif /* _ARM_ARCH__H_ */
