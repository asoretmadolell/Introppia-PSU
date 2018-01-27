#include "Arduino.h"

/*****************************************************************************/
/*                                                                           */
/* Introppia PSU                                                             */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* An Arduino-based power supply for tattooists.                             */
/*                                                                           */
/*****************************************************************************/

// Rotary encoder
#define RECLK_PIN 2
#define REDT_PIN 3
#define RESW_PIN 8

// MOSFET
#define GATE_PIN 9
#define POT_PIN A0


static long virtualPosition = 0; // without STATIC it doesn't count correctly

/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/* setup()                                                                   */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
void setup()
{
    // Rotary encoder
    pinMode( RECLK_PIN, INPUT );
    pinMode( REDT_PIN, INPUT );
    pinMode( RESW_PIN, INPUT_PULLUP );
    attachInterrupt( digitalPinToInterrupt( RECLK_PIN ), isr0, RISING );

    // MOSFET
    pinMode( GATE_PIN, OUTPUT );
    digitalWrite( GATE_PIN, LOW );

    Serial.begin( 9600 );
}

/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/* loop()                                                                    */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
void loop()
{
//    int speed;
//    speed = map( analogRead( POT_PIN ), 0, 1024, 0, 255 );
//    Serial.println( speed );
//    analogWrite( GATE_PIN, speed );
    if( !digitalRead( RESW_PIN ) )
    {
        virtualPosition = 0;
    }
    Serial.println( virtualPosition );
}

/*****************************************************************************/
/*                                                                           */
/* isr0()                                                                    */
/*                                                                           */
/*****************************************************************************/
void isr0()
{
    detachInterrupt( 0 ); // this is to avoid interrupting an interrupt

    // If interrupts come faster than 2ms, assume it's a bounce and ignore
    static unsigned long lastInterruptTime = 0;
    unsigned long interruptTime = millis();
    if( interruptTime - lastInterruptTime > 2 )
    {
        if( !digitalRead( REDT_PIN ) )
        {
            virtualPosition++;
        }
        else
        {
            virtualPosition--;
        }
    }
    lastInterruptTime = interruptTime;

    attachInterrupt( digitalPinToInterrupt( RECLK_PIN ), isr0, RISING );
}
