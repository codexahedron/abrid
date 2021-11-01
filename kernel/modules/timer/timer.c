#include <screen.h>
#include <isr.h>
#include <irq.h>
#include <timer.h>
#include <ports.h>
#include <string.h>
#include <modules.h>

#define FREQ 100

//The timer has 3 channels, 0,1,2
//0 is for IRQ0
//1 is system specific and 2 is for speaker
//2 can be used to create sound like
//these three channels are present at 0x40, 0x41, 0x42 and 0x43 is the command register

//let's keep track of number of ticks elapsed
int ticks = 0;
int seconds = 0;
//set the phase of the timer
//the value divisor is sent into the PIT to make it divide its
//frequency by this divisor, so that we get the exact clock frequency
void timer_phase(int hz){
    //create the divisor to send into the clock
    int divisor = 1193180/hz;
    //send the command byte
    out_port_byte(0x43, 0x36);

    //now these are the upper lower bytes of the divisor
    //they need to be split before they are sent.
    out_port_byte(0x40, divisor & 0xFF);
    out_port_byte(0x40, divisor >> 8);
}

//to increase the "ticks" variable, we increment it evrytime the timer fires.
//the timer PIT is connected to IRQ0, so evrytime it fires, we increment it
//by default, the timer fires 18.222 times/second.
void timer_handler(struct regs *r){
    //increment number of ticks
    ticks++;
    if(ticks % FREQ == 0){
        seconds++;
    }
}

//let's install timer handler into IRQ0
void timer_install(){
    module_t modules_timer_timer = MODULE("kernel.modules.timer.timer", "Adds PIT support for the kernel (CORE)");
    timer_phase(FREQ);
    irq_install_handler(0, timer_handler);
    INIT(modules_timer_timer);
}

void timer_wait(int val){
    unsigned int end = seconds + val;
    while(seconds < end){
        asm volatile("" : : : "memory");
    }
}

int get_tracked_seconds() {
	return seconds;
}
