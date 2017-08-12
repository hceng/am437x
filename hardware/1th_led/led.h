
#ifndef  __LED_H__
#define  __LED_H__

/**************************************************
                    TI_BOARD
---------------------------------------------------
Ball     Color       Mode             Pin
---------------------------------------------------
H24     D7_Blue      0x07     uart3_txd(GPIO5_3)
H25     D8_Blue      0x07     uart3_rxd(GPIO5_2)
K24     D9_Green     0x07     uart3_rtsn(GPIO5_1)
H22     D10_Red      0x07     uart3_ctsn(GPIO5_0)
**************************************************/


extern void led_init(void);

extern void  led_on();
extern void  led_off();

extern void led1_on();
extern void led1_off();

extern void led2_on();
extern void led2_off();

extern void led3_on();
extern void led3_off();

extern void led4_on();
extern void led4_off();


#endif


