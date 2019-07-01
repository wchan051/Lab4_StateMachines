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

enum States {Init, pressed, released, pressed2, released2} state;

void Tick() {
    switch(state) {
	case(Init):
	    if(PINA & 0x01) {
		state = pressed;
	    }
	    break;
	case(pressed):
	    if(!(PINA & 0x01)) {
		state = released;
	    }
	    break;
	case(released):
	    if(PINA & 0x01) {
		state = pressed2;
	    }
	    break;
	case(pressed2):
	    if(!(PINA & 0x01)) {
		state = released2;
	    }
	    break;
	case(released2):
	    if(PINA & 0x01) {
		state = pressed;
	    }
	    break;
	default:
	    break;
    }

    switch(state) {
        case(Init):
	    PORTB = 0x01;
	    break;
        case(pressed):
	    PORTB = 0x01;
	    break;
        case(released):
	    break;
        case(pressed2):
	    PORTB = 0x02;
        case(released2):
	    break;
        default:
	    break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */

    /* Insert your solution below */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    while (1) {
        Tick();
    }
    return 1;
}
