/*******************************************************************
 *Horse by www.varind.com 2014 
 *based on:
 *
 *SoftServo sketch for Adafruit Trinket.
 * 
 * Required library is the Adafruit_SoftServo library
 * available at https://github.com/adafruit/Adafruit_SoftServo
 * The standard Arduino IDE servo library will not work with 8 bit
 * AVR microcontrollers like Trinket and Gemma due to differences
 * in available timer hardware and programming. We simply refresh
 * by piggy-backing on the timer0 millis() counter
 * 
 *******************************************************************/

#include <Adafruit_SoftServo.h>  // SoftwareServo (works on non PWM pins)
#define SERVO1PIN 3 //Waist
#define SERVO2PIN 4 //Legs

Adafruit_SoftServo myServo1, myServo2;  //create TWO servo objects

void setup() {
  // Set up the interrupt that will refresh the servo for us automagically
  OCR0A = 0xAF;            // any number is OK
  TIMSK |= _BV(OCIE0A);    // Turn on the compare interrupt (below!)

  myServo1.attach(SERVO1PIN);
  myServo1.write(90);
  myServo2.attach(SERVO2PIN);
  myServo2.write(90);
  delay(15);
}

void loop()  {
    myServo1.write(15);  // Move Waist
    delay(100);  
    myServo2.write(40);  // Move Legs
    delay(150);
    myServo1.write(140);
    delay(100);  
    myServo2.write(130);  
    delay(150);
}

volatile uint8_t counter = 0;

SIGNAL(TIMER0_COMPA_vect) {
  // this gets called every 2 milliseconds
  counter += 2;
  // every 20 milliseconds, refresh the servos!
  if (counter >= 20) {
    counter = 0;
    myServo1.refresh();
    myServo2.refresh();
  }
}
