/*
 rtc.c
 initialize rtc in this file
*/
#include "rtc.h"
#define REG_B 0x8B
#define REG_A 0x8A
#define RTC_COM 0x70
#define RTC_DAT 0x71
#define DESIRE_RATE 15
/*
    rtc_init(void)
    DESCRIPTION: initilize rtc
    INPUT: none
    OUTPUT: none
    SIDEEFFECT: set rate, index, and initial value of register A
*/
void rtc_init(void){
    outb(REG_B,RTC_COM);
    char reg_b = inb(RTC_DAT);
    outb(REG_B,RTC_COM);
    outb(reg_b|0x40,RTC_DAT);   // enble rtc periodic interrupt

    int rate = DESIRE_RATE;	    // rate must be above 2 and not over 15
                                // 15 sets the rate to 2HZ per second
                                // source: http://wiki.osdev.org/RTC
    outb(REG_A ,RTC_COM);		// set index to register A, disable NMI
    char reg_a=inb(RTC_DAT);	// get initial value of register A
    outb(REG_A,RTC_COM);		// reset index to A
    outb((reg_a & 0xF0) | rate, RTC_DAT); //write only our rate to A. Note, rate is the bottom 4 bits.

    return;
}
