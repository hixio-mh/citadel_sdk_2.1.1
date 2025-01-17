/*
 * Copyright (c) 2017 Broadcom Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Cortex-A public kernel miscellaneous
 *
 * ARM-specific kernel miscellaneous interface. Included by arm/arch.h.
 */

#ifndef _ARCH_ARM_CORTEXA_MISC_H_
#define _ARCH_ARM_CORTEXA_MISC_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE
extern void k_cpu_idle(void);

extern u32_t _timer_cycle_get_32(void);
#define _arch_k_cycle_get_32()	_timer_cycle_get_32()
#endif

#ifdef __cplusplus
}
#endif

#endif /* _ARCH_ARM_CORTEXA_MISC_H_ */
