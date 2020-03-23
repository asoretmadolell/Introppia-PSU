/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/*                                                                           */
/* Introppia PSU v0.14                                                       */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "Arduino.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoSTL.h>
#include <ClickEncoder.h>
#include <TimerOne.h>

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
#define GATE_PIN    11
#define POT_PIN     A0
#define PEDAL_PIN   8

/***************************************************************************/
/*                                                                         */
/* Globals                                                                 */
/*                                                                         */
/***************************************************************************/
// Buttons
bool buttonPressed = false;
bool knobTurnedCW = false;
bool knobTurnedCCW = false;
bool pedalPressed = false;
ClickEncoder* clickEncoder = new ClickEncoder( RECLK_PIN, REDT_PIN, RESW_PIN, 4 );
int16_t clickEncoderValue;
int16_t clickEncoderLast = -1;
unsigned long lastPedalPressedTime = 0;
unsigned long pedalPressedTime;

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
    Timer1.initialize( 1000 );
    Timer1.attachInterrupt( timerIsr );
    clickEncoder->setAccelerationEnabled( false );

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
    myLcd.print( "v0.14 Hola, Vir!" );
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
//    debugMenu();
//    debugClickEncoder();



    CMenuPagePedal* pagePedal = (CMenuPagePedal*)menu.GetPage( 1 );
    if( pagePedal->GetPedal() )                 // pedal option enabled
    {
        if( !digitalRead( PEDAL_PIN ) )         // pedal changed / pressed
        {
            CMenuPagePwm* pagePwm = (CMenuPagePwm*)menu.GetPage( 0 );
            int PwmValue = pagePwm->GetPwm();
            analogWrite( GATE_PIN, PwmValue );
        }
        else                                    // pedal released
        {
            analogWrite( GATE_PIN, 0 );
        }
    }
    else                                        // pedal option disabled
    {
        if( !digitalRead( PEDAL_PIN ) )         // pedal changed / pressed
        {
            pedalPressedTime = millis();        // debounce
            if( pedalPressedTime - lastPedalPressedTime > 500 ) pedalPressed = !pedalPressed;
            lastPedalPressedTime = pedalPressedTime;

            if( pedalPressed )                  // pedal changed / pressed
            {
                CMenuPagePwm* pagePwm = (CMenuPagePwm*)menu.GetPage( 0 );
                int PwmValue = pagePwm->GetPwm();
                analogWrite( GATE_PIN, PwmValue );
            }
            else
            {
                analogWrite( GATE_PIN, 0 );
            }
        }
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

    // Menu logic

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

    // Rotary encoder logic

    clickEncoderValue += clickEncoder->getValue();

    if( clickEncoderValue > clickEncoderLast )
    {
        clickEncoderLast = clickEncoderValue;
        knobTurnedCW = true;
    }
    else if( clickEncoderValue < clickEncoderLast )
    {
        clickEncoderLast = clickEncoderValue;
        knobTurnedCCW = true;
    }
    else
    {
        knobTurnedCW = false;
        knobTurnedCCW = false;
    }

    ClickEncoder::Button button = clickEncoder->getButton();

    if( button != ClickEncoder::Open )
    {
        switch( button )
        {
            case ClickEncoder::Pressed:
                break;
            case ClickEncoder::Held:
                break;
            case ClickEncoder::Released:
                break;
            case ClickEncoder::Clicked:
                buttonPressed = true;
                break;
            case ClickEncoder::DoubleClicked:
                break;
            default:
                break;
        }
    }
}

/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/* timerIsr()                                                                */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
void timerIsr()
{
    clickEncoder->service();
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
}

/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/* debugMenu()                                                               */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
void debugMenu()
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
/* debugClickEncoder()                                                       */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
void debugClickEncoder()
{
    clickEncoderValue += clickEncoder->getValue();

    if( clickEncoderValue != clickEncoderLast )
    {
        clickEncoderLast = clickEncoderValue;
        Serial.print( "Encoder value: " );
        Serial.println( clickEncoderValue );
    }

    ClickEncoder::Button button = clickEncoder->getButton();

    if( button != ClickEncoder::Open )
    {
        Serial.print( "Button: " );
#define VERBOSECASE(label) case label: Serial.println(#label); break;
        switch( button )
        {
            VERBOSECASE( ClickEncoder::Pressed )
                ;
            VERBOSECASE( ClickEncoder::Held )
            VERBOSECASE( ClickEncoder::Released )
            VERBOSECASE( ClickEncoder::Clicked )
            case ClickEncoder::DoubleClicked:
                Serial.println( "ClickEncoder::DoubleClicked" );
                clickEncoder->setAccelerationEnabled( !clickEncoder->getAccelerationEnabled() );
                Serial.print( "  Acceleration is " );
                Serial.println( ( clickEncoder->getAccelerationEnabled() ) ? "enabled" : "disabled" );
                break;
        }
    }
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
