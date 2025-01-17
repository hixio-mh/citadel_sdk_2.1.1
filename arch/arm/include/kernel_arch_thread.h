/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Per-arch thread definition
 *
 * This file contains definitions for
 *
 *  struct _thread_arch
 *  struct _callee_saved
 *  struct _caller_saved
 *
 * necessary to instantiate instances of struct k_thread.
 */

#ifndef ZEPHYR_ARCH_ARM_INCLUDE_KERNEL_ARCH_THREAD_H_
#define ZEPHYR_ARCH_ARM_INCLUDE_KERNEL_ARCH_THREAD_H_

#ifndef _ASMLANGUAGE
#include <zephyr/types.h>

struct _caller_saved {
	/*
	 * Unused for Cortex-M, which automatically saves the necessary
	 * registers in its exception stack frame.
	 */
#ifdef CONFIG_ARMV7_A
	/* On ARM Cortex-A no exception stack frame is saved on stack */
	u32_t a1;  /* r0 */
	u32_t a2;  /* r1 */
	u32_t a3;  /* r2 */
	u32_t a4;  /* r3 */
	u32_t ip;  /* r12 */
	u32_t lr;  /* r14*/
	u32_t pc;  /* r15 */
	u32_t psr; /* cpsr */
#endif /* CONFIG_ARMV7_A */
};

typedef struct _caller_saved _caller_saved_t;

struct _callee_saved {
	u32_t v1;  /* r4 */
	u32_t v2;  /* r5 */
	u32_t v3;  /* r6 */
	u32_t v4;  /* r7 */
	u32_t v5;  /* r8 */
	u32_t v6;  /* r9 */
	u32_t v7;  /* r10 */
	u32_t v8;  /* r11 */
	u32_t psp; /* r13 */
};

typedef struct _callee_saved _callee_saved_t;

#ifdef CONFIG_FLOAT
#ifdef CONFIG_CPU_CORTEX_A
#ifdef CONFIG_CPU_CORTEX_A7
struct _preempt_float {
	/* FPSCR status bits */
	u32_t fpscr;

	/* Double precision register file */
	double d[32];
};
#else
#error Unsupported ARM architecture
#endif /* CONFIG_CPU_CORTEX_A7 */
#elif defined CONFIG_CPU_CORTEX_M
struct _preempt_float {
	float  s16;
	float  s17;
	float  s18;
	float  s19;
	float  s20;
	float  s21;
	float  s22;
	float  s23;
	float  s24;
	float  s25;
	float  s26;
	float  s27;
	float  s28;
	float  s29;
	float  s30;
	float  s31;
};
#else
#error Unsupported ARM architecture
#endif /* CONFIG_CPU_CORTEX_A */
#endif /* CONFIG_FLOAT */

struct _thread_arch {

	/* interrupt locking key */
	union {
		u32_t intlock_key;
		u32_t basepri;
	};

	/* r0 in stack frame cannot be written to reliably */
	u32_t swap_return_value;

#ifdef CONFIG_FLOAT
	/*
	 * No cooperative floating point register set structure exists for
	 * the Cortex-M as it automatically saves the necessary registers
	 * in its exception stack frame.
	 */
	struct _preempt_float  preempt_float;
#endif /* CONFIG_FLOAT */

#ifdef CONFIG_USERSPACE
	u32_t mode;
	u32_t priv_stack_start;
#endif
};

typedef struct _thread_arch _thread_arch_t;

#endif /* _ASMLANGUAGE */

#endif /* _kernel_arch_thread__h_ */
