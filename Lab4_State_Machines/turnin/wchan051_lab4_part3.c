/*	Author: wchan051
 *  Partner(s) Name: Jonathan Picazo
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Init, s0, s1, s2, s3, s4} state;

void Tick() {
    switch(state) {
	case(Init):
	    state = s0;
	    break;
	case(s0): //press # symbol
	    if((PINA & 0x04) && !(PINA & 0x78) && !(PINA & 0x01) && !(PINA & 0x02) && !(PINA & 0x80)) {
		state = s1;
	    }
	    break;
	case(s1): //let go of #
	    if(!PINA) {
		state = s2;
	    }
	    break;
	case(s2): //y
	    if((PINA & 0x02) && !(PINA & 0x78) && !(PINA & 0x01) && !(PINA & 0x04) && !(PINA & 0x80)) {
		state = s3;
	    }
	    break;
	case(s3): //unlock
	    if((PINA & 0x80) && !(PINA & 0x78) && !(PINA & 0x01) && !(PINA & 0x04) && !(PINA & 0x02)) {
		state = s4;
	    }
	    break;
	case(s4): //lock
	    state = s0;
	    break;
	default:
	    break;
    }

    switch(state) {
	case(Init):
	    break;
	case(s0): 
	    PORTC = 0x00;
	    break;
	case(s1):
	    PORTC = 0x01;
	    break;
	case(s2):
	    PORTC = 0x02;
	    break;
	case(s3):
	    PORTB = 0x01;
	    PORTC = 0x03;
	    break;
	case(s4):
	    PORTB = 0x00;
	    PORTC = 0x04;
	    break;
	default:
	    break;
    }
}

int main(){
	state = Init;
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	while(1) {
            Tick();
        }
}
