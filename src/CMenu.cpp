#include "Arduino.h"
#include <LiquidCrystal_I2C.h>
#include "CMenu.h"

/***************************************************************************/
/*                                                                         */
/* Globals                                                                 */
/*                                                                         */
/***************************************************************************/
// LCD screen
extern LiquidCrystal_I2C myLcd;

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenu::CMenu()                                                          */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
CMenu::CMenu()
{
     m_pCurrentPage = new CMenuPage;
}

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenu::~CMenu()                                                         */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
CMenu::~CMenu()
{
     if( m_pCurrentPage ) delete m_pCurrentPage;
}

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenu::Print()                                                          */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
void CMenu::Print()
{
     myLcd.clear();
     myLcd.setCursor( 0, 0 );
     myLcd.print( "Level " );
     myLcd.print( GetLevel(), DEC );
     myLcd.print( ", Page 1 ", DEC );
     myLcd.setCursor( 0, 1 );
     myLcd.print( "Voltage: " );
     myLcd.print( GetCurrentPage()->GetVoltage(), DEC );
     myLcd.setCursor( 0, 2 );
     myLcd.print( "Value: " );
     myLcd.print( GetCurrentPage()->GetValue(), DEC );
     myLcd.print( "Unit: " );
     myLcd.print( GetCurrentPage()->GetUnit(), DEC );
}

