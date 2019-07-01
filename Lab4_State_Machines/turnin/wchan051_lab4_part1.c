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

enum States {Init, pressed0, released0, pressed1, released1} state;


void Tick(){
	switch(state){ 
		case(Init): 
			if (PINA & 0x01) { 
				state = pressed0; 
			}
			break;
		case(pressed0):
			if (!PINA & 0x01) { 
				state = released0; 
			}
			break;
		case(released0):
			if (PINA & 0x01) {
				state = pressed1; 
			}
			break;
		case(pressed1):
			if(!PINA & 0x01) {
				state = released1; 
			}
			break;
		case(released1):
			if(PINA & 0x01) {
				state = pressed0;
			}
			break;
		default:
			break;
	}
	switch(state) { 
		case(Init):
			PORTB = 0x01;
			break;
		case(pressed0):
			PORTB = 0x01; 
			break;
		case(released0):
			break; 
		case(pressed1):
			PORTB = 0x02;
			break;
		case(released1):
			break;
		default:
			break;
	}
 }

int main() {
	state = Init;
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00; 
	while(1) {
		Tick();
	}
}
