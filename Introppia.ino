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

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Rotary encoder
#define RESW_PIN 2
#define RECLK_PIN 3
#define REDT_PIN 4

// MOSFET
#define GATE_PIN 9
#define POT_PIN A0

// LCD screen
LiquidCrystal_I2C myLcd( 0x27, 16, 2 );

// Menu logic
volatile bool buttonPressed = false;
volatile bool knobTurnedCW = false;
volatile bool knobTurnedCCW = false;
const int menuLevelTotal = 2;
int menuLevel = 0;
const int menuPageTotal = 2;
int menuPage = 0;
const int menuPageValueTotal = 2;
int menuPageValue[ menuPageTotal ];

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
    attachInterrupt( digitalPinToInterrupt( RESW_PIN ), isr0, RISING );
    attachInterrupt( digitalPinToInterrupt( RECLK_PIN ), isr1, RISING );

    // MOSFET
    pinMode( GATE_PIN, OUTPUT );
    digitalWrite( GATE_PIN, LOW );

    Serial.begin( 9600 );
    Wire.begin();
    myLcd.begin( 16, 2 );

    myLcd.backlight();
    myLcd.setCursor( 0, 0 );
    myLcd.print( "Introppia PSU" );
    myLcd.setCursor( 0, 1 );
    myLcd.print( "v0.3  Hola, Vir!" );
//    delay( 2000 );
//    myLcd.clear();
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

    Serial.print( menuLevel, DEC );
    Serial.print( menuPage, DEC );
    Serial.print( menuPageValue[ menuPage ], DEC );
    Serial.println();

    if( buttonPressed )
    {
        switch( menuLevel )
        {
            case 0:
                menuLevel = 1;
                printMenu( &menuLevel, &menuPage, &menuPageValue[ menuPage ] );
                break;
            case 1:
                menuLevel = 2;
                printMenu( &menuLevel, &menuPage, &menuPageValue[ menuPage ] );
                break;
            default:
                menuLevel = 0;
                myLcd.clear();
                break;
        }
        buttonPressed = false;
    }

    if( knobTurnedCW )
    {
        switch( menuLevel )
        {
            case 1:
                if( menuPage < menuPageTotal - 1 ) menuPage++;
                printMenu( &menuLevel, &menuPage, &menuPageValue[ menuPage ] );
                break;
            case 2:
                menuPageValue[ menuPage ]++;
                printMenu( &menuLevel, &menuPage, &menuPageValue[ menuPage ] );
                break;
            default:
                break;
        }
        knobTurnedCW = false;
    }

    if( knobTurnedCCW )
    {
        switch( menuLevel )
        {
            case 1:
                if( menuPage > 0 ) menuPage--;
                printMenu( &menuLevel, &menuPage, &menuPageValue[ menuPage ] );
                break;
            case 2:
                menuPageValue[ menuPage ]--;
                printMenu( &menuLevel, &menuPage, &menuPageValue[ menuPage ] );
                break;
            default:
                break;
        }
        knobTurnedCCW = false;
    }
}

/*****************************************************************************/
/*                                                                           */
/* printMenu()                                                               */
/*                                                                           */
/*****************************************************************************/
void printMenu( int* menuLevel, int* menuPage, int* menuPageValue )
{
    myLcd.clear();
    myLcd.setCursor( 0, 0 );
    myLcd.print( "Level " );
    myLcd.print( *menuLevel, DEC );
    myLcd.print( ", Page " );
    myLcd.print( *menuPage, DEC );
    myLcd.setCursor( 0, 1 );
    myLcd.print( "Value " );
    myLcd.print( *menuPageValue, DEC );
}

/*****************************************************************************/
/*                                                                           */
/* isr0()                                                                    */
/*                                                                           */
/*****************************************************************************/
void isr0()
{
    buttonPressed = true;
}

/*****************************************************************************/
/*                                                                           */
/* isr1()                                                                    */
/*                                                                           */
/*****************************************************************************/
void isr1()
{
    detachInterrupt( digitalPinToInterrupt( RECLK_PIN ) ); // this is to avoid interrupting an interrupt

    // If interrupts come faster than 2ms, assume it's a bounce and ignore
    static unsigned long lastInterruptTime = 0;
    unsigned long interruptTime = millis();
    if( interruptTime - lastInterruptTime > 2 )
    {
        if( !digitalRead( REDT_PIN ) )
        {
            knobTurnedCW = true;
        }
        else
        {
            knobTurnedCCW = true;
        }
    }
    lastInterruptTime = interruptTime;

    attachInterrupt( digitalPinToInterrupt( RECLK_PIN ), isr1, RISING );
}
