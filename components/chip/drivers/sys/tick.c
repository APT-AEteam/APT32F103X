
/***********************************************************************//** 
 * \file  tick.c
 * \brief  Source File for tick
 * \copyright Copyright (C) 2015-2021 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-5-13<td>V1.1  <td>ZJY     <td>initial
 * </table>
 * *********************************************************************
*/
//#include <csi_config.h>
#include <sys_clk.h>
#include <drv/tick.h>
#include <drv/pin.h>
#include <drv/uart.h>
#include <drv/irq.h>
#include <drv/bt.h>
#include <csp_bt.h>

/* Private macro------------------------------------------------------*/
#define __WEAK	__attribute__((weak))

/* externs function---------------------------------------------------*/

/* externs variablesr-------------------------------------------------*/
/* Private variablesr-------------------------------------------------*/

static volatile uint64_t csi_tick = 0U;
static volatile uint32_t last_time_ms = 0U;
static volatile uint64_t last_time_us = 0U;


//static inline unsigned long long apt_coret_get_value(void)
//{
//	return  CORETIMER->MTIME;
//}

void csi_tick_increase(void)
{
    csi_tick++;
}



csi_error_t csi_tick_init(void)
{
    csi_tick = 0U;

	csi_bt_timer_init(BT3, 10000);		//初始化BT3, 定时10ms； BT定时，默认采用PEND中断
	csi_bt_start(BT3);
	
    return CSI_OK;
}

void csi_tick_uninit(void)
{
	csi_irq_disable((uint32_t *)BT3);	
}

uint32_t csi_tick_get(void)
{
    return csi_tick;
}

uint32_t csi_tick_get_ms(void)
{
    uint32_t time;
	uint16_t cnttm;
	
    while (1) 
	{
		cnttm = (csp_bt_get_cnt(BT3) * (csp_bt_get_pscr(BT3)+1) * 1000) / csi_get_pclk_freq();
		time = (csi_tick * (1000U / CONFIG_SYSTICK_HZ))+ cnttm;
        if (time >= last_time_ms) 
            break;
    }

    last_time_ms = time;
    return time;
}

static void _500usdelay(void)
{
    uint32_t start = csp_bt_get_cnt(BT3);
    uint32_t load = csp_bt_get_prdr(BT3);
    uint32_t cur;
    volatile  uint32_t cnt = csi_get_pclk_freq() / (csp_bt_get_pscr(BT3)+1) /2000U  ;

    while (1) {
        cur = csp_bt_get_cnt(BT3);

        if (start <= cur) {
            if ((cur - start) >= cnt) {
                break;
            }
        } else {
            if (((load - start) + cur) > cnt) {
                break;
            }
        }
    }
}


void _10udelay(void)
{
    uint32_t start = csp_bt_get_cnt(BT3);
    uint32_t load  = csp_bt_get_prdr(BT3);
    uint32_t cnt   = (csi_get_pclk_freq() /(csp_bt_get_pscr(BT3)+1) / 1000U / 100U);

    while (1) {
        uint32_t cur = csp_bt_get_cnt(BT3);

        if (start <= cur) {
            if ((cur - start) >= cnt) {
                break;
            }
        } else {
            if (((load - start) + cur) > cnt) {
                break;
            }
        }
    }
}
/** \brief  delay
 * 
 *  \param[in] ms: delay timer,unit: ms 
 *  \return none
 */ 
__WEAK void mdelay(uint32_t ms)
{
    while (ms) {
        ms--;
        _500usdelay();
        _500usdelay();
    }
}
/**
 * Ps: At least delay over 20us
*/
void udelay(uint32_t us)
{
	us /= 10U;
	
    while (us) {
        us--;
        _10udelay();
    }
}
/** \brief  delay, imprecise delay timer
 * 
 *  \param[in] t: delay timer; unit: 10us systick = 48M
 *  \return none
 */ 
void delay_ums(uint32_t t)
{
	volatile uint32_t i,j ,k=0;
	j = 25* t;
	for ( i = 0; i < j; i++ )
	{
		k++;
	}
}
