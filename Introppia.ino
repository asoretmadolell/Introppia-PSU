/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/*                                                                           */
/* Introppia PSU v0.7                                                        */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* An Arduino-based power supply for tattooists.                             */
/*                                                                           */
/*****************************************************************************/

#include "Arduino.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "src/CMenu.h"

/***************************************************************************/
/*                                                                         */
/* Defines                                                                 */
/*                                                                         */
/***************************************************************************/
// Rotary encoder
#define RESW_PIN    2
#define RECLK_PIN   3
#define REDT_PIN    4

// MOSFET
#define GATE_PIN    9
#define POT_PIN     A0

/***************************************************************************/
/*                                                                         */
/* Globals                                                                 */
/*                                                                         */
/***************************************************************************/
// Buttons
volatile bool buttonPressed = false;
volatile bool knobTurnedCW = false;
volatile bool knobTurnedCCW = false;

// LCD screen
LiquidCrystal_I2C myLcd( 0x27, 16, 2 );

// Menu
const int NumOfPages = 2;
String PageType[ NumOfPages ] = { "Voltage", "Contrast" };
CMenu menu( NumOfPages, PageType );

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
    myLcd.print( "v0.7  Hola, Vir!" );
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
    Serial.print( "Level: " );
    Serial.print( menu.GetLevel(), DEC );
    Serial.print( " Page: " );
    Serial.print( menu.GetPage()->GetPageIndex(), DEC );
    Serial.print( " Type: " );
    Serial.print( menu.GetPage()->GetPageType() );
    Serial.print( " Value: " );
    if( menu.GetPage()->GetPageType() == "Voltage" )
    {
        Serial.print( menu.GetPage()->GetVoltageValue(), DEC );
    }
    else
    {
        Serial.print( menu.GetPage()->GetDefaultValue(), DEC );
    }
    Serial.println();

    if( buttonPressed )
    {
        switch( menu.GetLevel() )
        {
            case 0:
                menu.SetLevel( 1 );
                menu.Print( menu.GetPage() );
                break;
            case 1:
                menu.SetLevel( 2 );
                menu.Print( menu.GetPage() );
                break;
            default:
                menu.SetLevel( 0 );
                myLcd.clear();
                break;
        }
        buttonPressed = false;
    }

    if( knobTurnedCW )
    {
        switch( menu.GetLevel() )
        {
            case 1:
                menu.IncrementCurrentPageIndex();
                menu.Print( menu.GetPage() );
                break;
            case 2:
                menu.IncrementValueFromPage();
                menu.Print( menu.GetPage() );
                break;
            default:
                break;
        }
        knobTurnedCW = false;
    }

    if( knobTurnedCCW )
    {
        switch( menu.GetLevel() )
        {
            case 1:
                menu.DecrementCurrentPageIndex();
                menu.Print( menu.GetPage() );
                break;
            case 2:
                menu.DecrementValueFromPage();
                menu.Print( menu.GetPage() );
                break;
            default:
                break;
        }
        knobTurnedCCW = false;
    }
}

/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/* isr0()                                                                    */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
void isr0()
{
    buttonPressed = true;
}

/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/* isr1()                                                                    */
/*                                                                           */
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
