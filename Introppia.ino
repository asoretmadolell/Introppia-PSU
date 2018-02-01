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
#include "src/CMenu.h"

// Rotary encoder
#define RESW_PIN 2
#define RECLK_PIN 3
#define REDT_PIN 4

// MOSFET
#define GATE_PIN 9
#define POT_PIN A0

// LCD screen
LiquidCrystal_I2C myLcd( 0x27, 16, 2 );

// Menu
CMenu menu( 2 );
volatile bool buttonPressed = false;
volatile bool knobTurnedCW = false;
volatile bool knobTurnedCCW = false;
int menuLevel = 0;
const int menuPageTotal = 2;
int menuPage = 0;
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
    myLcd.print( "v0.4  Hola, Vir!" );
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

    // For debugging
    Serial.print( menuLevel, DEC );
    Serial.print( menuPage, DEC );
    Serial.print( menuPageValue[ menuPage ], DEC );
    Serial.print( " " );
    Serial.print( "Level: " );
    Serial.print( menu.GetLevel(), DEC );
    Serial.print( " Page: " );
    Serial.print( menu.GetCurrentPage(), DEC );
    Serial.print( " Value: " );
    Serial.print( menu.GetPage( menu.GetCurrentPage() )->GetValue(), DEC );
    Serial.println();

    if( buttonPressed )
    {
        switch( menuLevel )
        {
            case 0:
                menuLevel = 1;
                printMenu( &menuLevel, &menuPage, &menuPageValue[ menuPage ] );

                menu.SetLevel( 1 );
                break;
            case 1:
                menuLevel = 2;
                printMenu( &menuLevel, &menuPage, &menuPageValue[ menuPage ] );

                menu.SetLevel( 2 );
                break;
            default:
                menuLevel = 0;
                myLcd.clear();

                menu.SetLevel( 0 );
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

                if( menu.GetCurrentPage() < menuPageTotal - 1 ) menu.SetCurrentPage( menu.GetCurrentPage() + 1 );
                break;
            case 2:
                menuPageValue[ menuPage ]++;
                printMenu( &menuLevel, &menuPage, &menuPageValue[ menuPage ] );

                menu.GetPage( menu.GetCurrentPage() )->SetValue( menu.GetPage( menu.GetCurrentPage() )->GetValue() + 1 );
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

                if( menu.GetCurrentPage() > 0 ) menu.SetCurrentPage( menu.GetCurrentPage() - 1 );
                break;
            case 2:
                menuPageValue[ menuPage ]--;
                printMenu( &menuLevel, &menuPage, &menuPageValue[ menuPage ] );

                menu.GetPage( menu.GetCurrentPage() )->SetValue( menu.GetPage( menu.GetCurrentPage() )->GetValue() - 1 );
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
