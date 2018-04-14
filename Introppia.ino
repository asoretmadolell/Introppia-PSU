/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/*                                                                           */
/* Introppia PSU v0.12                                                       */
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
#include <ArduinoSTL.h>

#include "src/CMenu_Classes.h"

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
#define PEDAL_PIN   8

/***************************************************************************/
/*                                                                         */
/* Globals                                                                 */
/*                                                                         */
/***************************************************************************/
// Buttons
volatile bool buttonPressed = false;
volatile bool knobTurnedCW = false;
volatile bool knobTurnedCCW = false;
volatile static unsigned long lastInterruptTime = 0;

// LCD screen
LiquidCrystal_I2C myLcd( 0x27, 16, 2 );

// Menu
const int NumOfPages = 3;
int PageType[ NumOfPages ] = { 1, 2, 3 };
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
    pinMode( PEDAL_PIN, INPUT_PULLUP );

    Serial.begin( 9600 );
    Wire.begin();
    myLcd.begin( 16, 2 );

    myLcd.backlight();
    myLcd.setCursor( 0, 0 );
    myLcd.print( "Introppia PSU" );
    myLcd.setCursor( 0, 1 );
    myLcd.print( "v0.12  Hola, Vir!" );
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
//    debug();

    if( !digitalRead( PEDAL_PIN ) )
    {
        CMenuPagePwm* pagePwm = (CMenuPagePwm*)menu.GetPage( 0 );
        int PwmValue = pagePwm->GetPwm();
        analogWrite( GATE_PIN, PwmValue );
    }
    else
    {
        analogWrite( GATE_PIN, 0 );
    }

    /*
    int potValue = analogRead( A0 );
    int analogSpeed = map( potValue, 0, 1023, 0, 255 );
    myLcd.clear();
    myLcd.setCursor( 0, 0 );
    myLcd.print( potValue );
    myLcd.setCursor( 0, 1 );
    myLcd.print( analogSpeed );
    */

    if( buttonPressed )
    {
        switch( menu.GetLevel() )
        {
            case 0:
                menu.SetLevel( 1 );
                menu.Print();
                break;
            case 1:
                menu.SetLevel( 2 );
                menu.Print();
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
                menu.Print();
                break;
            case 2:
                menu.IncrementValueFromPage();
                menu.Print();
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
                menu.Print();
                break;
            case 2:
                menu.DecrementValueFromPage();
                menu.Print();
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

    // If interrupts come faster than Xms, assume it's a bounce and ignore
    unsigned long interruptTime = millis();
    if( interruptTime - lastInterruptTime > 15 )
    {
        digitalRead( REDT_PIN ) ? knobTurnedCW = true : knobTurnedCCW = true;
        lastInterruptTime = interruptTime;
    }

    attachInterrupt( digitalPinToInterrupt( RECLK_PIN ), isr1, RISING );
}

/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/* debug()                                                                   */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
void debug()
{
    Serial.print( "Level " );
    Serial.print( menu.GetLevel(), DEC );
    Serial.print( ", Page " );
    Serial.print( menu.GetCurrentPageIndex(), DEC );
    Serial.print( ", Type " );
    Serial.print( menu.GetPage()->GetName() );
    Serial.print( ", Value: " );
    switch( menu.GetPage()->GetType() )
    {
        case 1:
        {
            CMenuPagePwm* pagePwm = (CMenuPagePwm*)menu.GetPage();
            Serial.print( pagePwm->GetPwm(), DEC );
            break;
        }
        case 2:
        {
            CMenuPagePedal* pagePedal = (CMenuPagePedal*)menu.GetPage();
            Serial.print( pagePedal->GetPedal() );
            break;
        }
        case 3:
        {
            CMenuPageContrast* pageContrast = (CMenuPageContrast*)menu.GetPage();
            Serial.print( pageContrast->GetContrast(), DEC );
            break;
        }
        default:
            break;
    }
    Serial.print( menu.GetPage()->GetUnit() );
    Serial.println();
}

/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/* mapDouble()                                                               */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
double mapDouble( double x, double in_min, double in_max, double out_min, double out_max )
{
    return ( x - in_min ) * ( out_max - out_min ) / ( in_max - in_min ) + out_min;
}
