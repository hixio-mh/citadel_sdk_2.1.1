/******************************************************************************
 * Copyright 20XX Broadcom. All Rights Reserved.
 * The term "Broadcom" refers to Broadcom Inc. and/or its subsidiaries.
 *
 * This program is the proprietary software of Broadcom and/or
 * its licensors, and may only be used, duplicated, modified or distributed
 * pursuant to the terms and conditions of a separate, written license
 * agreement executed between you and Broadcom (an "Authorized License").
 * Except as set forth in an Authorized License, Broadcom grants no license
 * (express or implied), right to use, or waiver of any kind with respect to
 * the Software, and Broadcom expressly reserves all rights in and to the
 * Software and all intellectual property rights therein.  IF YOU HAVE NO
 * AUTHORIZED LICENSE, THEN YOU HAVE NO RIGHT TO USE THIS SOFTWARE IN ANY
 * WAY, AND SHOULD IMMEDIATELY NOTIFY BROADCOM AND DISCONTINUE ALL USE OF
 * THE SOFTWARE.
 *
 * Except as expressly set forth in the Authorized License,
 *
 * 1. This program, including its structure, sequence and organization,
 * constitutes the valuable trade secrets of Broadcom, and you shall use
 * all reasonable efforts to protect the confidentiality thereof, and to
 * use this information only in connection with your use of Broadcom
 * integrated circuit products.
 *
 * 2. TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED
 * "AS IS" AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES,
 * REPRESENTATIONS OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR
 * OTHERWISE, WITH RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY
 * DISCLAIMS ANY AND ALL IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY,
 * NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, LACK OF VIRUSES,
 * ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR
 * CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING
 * OUT OF USE OR PERFORMANCE OF THE SOFTWARE.
 *
 * 3. TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL
 * BROADCOM OR ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL,
 * SPECIAL, INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR
 * IN ANY WAY RELATING TO YOUR USE OF OR INABILITY TO USE THE SOFTWARE EVEN
 * IF BROADCOM HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES; OR (ii)
 * ANY AMOUNT IN EXCESS OF THE AMOUNT ACTUALLY PAID FOR THE SOFTWARE ITSELF
 * OR U.S. $1, WHICHEVER IS GREATER. THESE LIMITATIONS SHALL APPLY
 * NOTWITHSTANDING ANY FAILURE OF ESSENTIAL PURPOSE OF ANY LIMITED REMEDY.
 ******************************************************************************/
#include "M0.h"

__attribute__ ((interrupt ("IRQ"))) int m0_aon_gpio_handler(void)
{
	s32_t ret = 0;
	u32_t irq_handled = 0;
	CITADEL_PM_ISR_ARGS_s *pm_args = CRMU_GET_PM_ISR_ARGS();
	MPROC_PM_MODE_e cur_pm_state = pm_args->tgt_pm_state;
#ifdef MPROC_PM__ADV_S_POWER_OFF_PLL
	MPROC_PM_MODE_e prv_pm_state = pm_args->prv_pm_state;
#else
	MPROC_PM_MODE_e prv_pm_state = MPROC_PM_MODE__END;
#endif

	u32_t aon_gpio_wakeup = pm_args->aon_gpio_settings.wakeup_src;
	u32_t aon_gpio_mstat = 0, valid_aon_gpio_intr = 0;

	MPROC_PM_WAKEUP_CODE_s wakeup_code;
	u32_t irq_status   = sys_read32(CRMU_MCU_INTR_STATUS);
	u32_t event_status = sys_read32(CRMU_MCU_EVENT_STATUS);
	/* Initialize wake up Code 0 */
	u32_t wakeup_msg_code0 = MAILBOX_CODE0__WAKEUP;
	/* Put some default wake up Code 1 */
	u32_t wakeup_msg_code1 = MAILBOX_CODE1__WAKEUP_TEST;

	MCU_SET_STATE_IN_WAKEUP_ENTRY_C();

	MCU_memset((void *)&wakeup_code, 0, sizeof(MPROC_PM_WAKEUP_CODE_s));

	/* AON GPIO intr from valid src */
	if (irq_status & BIT(MCU_AON_GPIO_INTR)) {
		MCU_SET_STATE_IN_WAKEUP_ENTRY_C();
		irq_handled = 1;
		/* TODO: This mask is for 6 AON GPIOs,
		 * should it be changed to 0x7ff
		 * since we have 11 AON GPIOs?
		 */
		aon_gpio_mstat = sys_read32(GP_INT_MSTAT) & AON_GPIO_INT_MASK;

		/* TODO: Is this workaround still applicable for Citadel? */
#ifdef AON_GPIO_EDGE_SENSITIVE_WORKAROUND
		/* this must be called before clearing any aon_gpio interrupt */
		valid_aon_gpio_intr =
		MCU_get_valid_aon_gpio_wakeup_interrupt(aon_gpio_wakeup);
#else
		valid_aon_gpio_intr = aon_gpio_mstat & aon_gpio_wakeup;
#endif
		/*In RUN mode*/
		if (cur_pm_state < MPROC_PM_MODE__SLEEP) {
			MCU_SET_STATE_IN_WAKEUP_ENTRY_C();
#ifdef IPROC_PM_CLEAR_AON_GPIO_INTR_IN_M0_ISR
			sys_write32(aon_gpio_mstat, GP_INT_CLR);
			MCU_SYNC();
			MCU_send_msg_to_mproc(aon_gpio_mstat,
			MAILBOX_CODE1__AON_GPIO_INTR_IN_RUN);
#else
			/* This defers clearing of the aon gpio intr to A7 */
			MCU_send_msg_to_mproc(MAILBOX_CODE0__AON_GPIO_INTR_IN_RUN,
			MAILBOX_CODE1__AON_GPIO_INTR_IN_RUN);
#endif
			goto OK_exit;
		} else /*In LP mode*/ {
			/* 1. First check none-wakeup AON_GPIOs
			 * interrupt, don't return
			 */
			if (aon_gpio_mstat & ~aon_gpio_wakeup) {
				MCU_SET_STATE_IN_WAKEUP_ENTRY_C();
				/* Don't send msg to A7 if it(A7)
				 * is in any LP mode,
				 * which may wake A7 up from SLEEP.
				 * TODO: Confirm if this is true.
				 */
#ifdef IPROC_PM_CLEAR_AON_GPIO_INTR_IN_M0_ISR
				/* clear & mask all none-wakeup AON_GPIO interrupt */
				sys_write32(~aon_gpio_wakeup, GP_INT_CLR);
				/* GP_INT_MSK will be restored after wakeup */
				sys_write32(aon_gpio_wakeup, GP_INT_MSK);
#endif
			}

			/* 2. Secondly check and clear wakeup AON_GPIOs interrupt */
			if (aon_gpio_mstat & aon_gpio_wakeup) {
				MCU_SET_STATE_IN_WAKEUP_ENTRY_C();
				/* Clear wakeup AON GPIO interrupt */
				sys_write32(aon_gpio_wakeup, GP_INT_CLR);
			}

			/* Last check valid wakeup AON_GPIOs interrupt */
			if (valid_aon_gpio_intr) {
				if ((MCU_WAKEUP_SOURCE & BIT(MCU_NVIC_AON_GPIO_INTR))) {
					u32_t i = 0;
					MCU_SET_STATE_IN_WAKEUP_ENTRY_C();
					wakeup_code.wakeup_src        = ws_aon_gpio;
					wakeup_code.info.aon_gpio.src = valid_aon_gpio_intr;
					/* Pick the first AON GPIO that has caused this wake-up
					 * and prepare code1 of the mailbox message.
					 */
					for(i = 0; i < MPROC_AON_GPIO_END; i++) {
						if(valid_aon_gpio_intr & BIT(i)) {
							wakeup_msg_code1 = MAILBOX_CODE1__WAKEUP_AON_GPIO0 + i;
							break;
						}
					}

					goto wakeup;
				}
			}
		}
	}

	if (!irq_handled) {
		MCU_SET_STATE_IN_WAKEUP_ENTRY_C();
		MCU_USER_ISR_SET_STATE(irq_status);
		MCU_USER_ISR_SET_STATE(event_status);
	}

	/* NO VALID WAKEUP interrupt occurs, just return */
	goto OK_exit;

wakeup:
	/* TODO: Should this include DRIPS too ? */
	/* Totally disable rtc and tamper to avoid
	 * conflict with SBL
	 */
	if (cur_pm_state == MPROC_PM_MODE__DEEPSLEEP
		|| cur_pm_state == MPROC_PM_MODE__DRIPS) {
		MCU_SET_STATE_IN_WAKEUP_ENTRY_C();
	}

	/* Copy back wakeup details */
	MCU_memcpy((void *)&pm_args->wakeup, (void *)&wakeup_code,
			   sizeof(MPROC_PM_WAKEUP_CODE_s));

	/* Do wakeup */
	ret = MCU_SoC_Wakeup_Handler(cur_pm_state, prv_pm_state, wakeup_msg_code0, wakeup_msg_code1);
	MCU_SET_STATE_IN_WAKEUP_ENTRY_C();

	/* Clear mailbox values, this will trigger
	 * a mbox interrupt again
	 */
	if (!ret) {
		MCU_SET_STATE_IN_WAKEUP_ENTRY_C();
		/* TODO: Does this apply to Citadel as well?
		 *
		 * On rising edge wakeup, A7 is rebooting for ds/vds,
		 * init this value
		 * before A7 reset done, otherwise, the following
		 * falling edge intr
		 * will reset A7 again.
		 *
		 * Can't we make this rising edge only?
		 */
		if (cur_pm_state > MPROC_PM_MODE__SLEEP)
			pm_args->tgt_pm_state = MPROC_PM_MODE__RUN_200;

		MCU_send_msg_to_mcu(MAILBOX_CODE0__NOTHING,
		MAILBOX_CODE1__NOTHING);
	}

	if (cur_pm_state < MPROC_PM_MODE__DEEPSLEEP)
		/* clear wakeup sources after normal wakeup */
		MCU_setup_wakeup_src(MPROC_EXIT_LP);

	MCU_SET_STATE_IN_WAKEUP_ENTRY_C();

	return 0;

OK_exit: /* NO VALID WAKEUP interrupt occurs, direct return */
	MCU_SET_STATE_IN_WAKEUP_ENTRY_C();
	return 0;
}
