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

enum States {Init, increment, decrement, reset, iwait, dwait, wait} state;

unsigned char counter = 0;

void Tick(){
	switch(state) {
		case(Start): 
			state = wait; 
      break;
		case(wait):
			if((PINA & 0x01) && (PINA & 0x02)) {
			    state = reset;
      }
			else if(PINA & 0x01) {
			    state = increment;
      }
			else if(PINA & 0x02) {
			    state = decrement;
      }
			break;
		case(reset):
			state = wait; 
      break;
		case(increment):
				state = iwait; 
			break;
		case(decrement):
				state = dwait; 
			break;
		case(iwait):
			if (!PINA & 0x01)
				state = wait;
			break;
		case(dwait):
			if (!PINA & 0x02)
				state = wait;
			break; 
		default:
			break;
	}
	switch(state) {
		case(Init):
			counter = 7;
			break;
		case(wait):
			break;
		case(increment):
			if (counter < 9) {
		      counter++; 
      }
			break;
		case(decrement):
			if (counter > 0) {
			    counter--; 
      }
			break;
		case(reset):
			count = 0; 
      break;
		case(iwait):
			break;
		case(dwait):
			break;
		default:
			break;
	}
	PORTC = counter;
 }

int main(){
	state = Init;
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	while(1) {
      Tick();
  }
}
