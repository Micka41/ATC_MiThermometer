/*
 * rds_count.h
 *
 *  Created on: 20.02.2022
 *      Author: pvvx
 */

#ifndef RDS_COUNT_H_
#define RDS_COUNT_H_

#include "app_config.h"

#if	USE_TRIGGER_OUT

#ifdef GPIO_RDS

static inline uint8_t get_rds_input(void) {
	return (BM_IS_SET(reg_gpio_in(GPIO_RDS), GPIO_RDS & 0xff));
}

static inline void save_rds_input(void) {
	trg.flg.rds_input = ((BM_IS_SET(reg_gpio_in(GPIO_RDS), GPIO_RDS & 0xff))? 1 : 0);
}

static inline void rds_input_off(void) {
	gpio_setup_up_down_resistor(GPIO_RDS, PM_PIN_UP_DOWN_FLOAT);
}

static inline void rds_input_on(void) {
	gpio_setup_up_down_resistor(GPIO_RDS, PM_PIN_PULLUP_1M);
}

#if USE_WK_RDS_COUNTER

typedef struct _rds_count_t {
	uint32_t tim_disable; 	// min timeout (in 1/16 us) = CLOCK_SYS_CLOCK_1S
	uint32_t tick_disable;	// timer tick
	uint32_t report_tick; // timer reed switch count report interval
	union {		// counter
		uint8_t count_byte[4];
		uint16_t count_short[2];
		uint32_t count;
	};
	uint8_t type;	// 0 - none, 1 - switch, 2 - counter
//	uint8_t flg;	// reserved
}rds_count_t;
extern rds_count_t rds;		// Reed switch pulse counter

void rds_init(void);
void rds_suspend(void);
void rds_task(void);

#endif // defined GPIO_RDS

#endif // USE_WK_RDS_COUNTER

#endif // USE_TRIGGER_OUT

#endif /* RDS_COUNT_H_ */
