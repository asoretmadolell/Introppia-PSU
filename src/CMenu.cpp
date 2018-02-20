#include "Arduino.h"
#include <LiquidCrystal_I2C.h>

#include "CMenu_Classes.h"

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
CMenu::CMenu( int NumOfPages, String PageType[] )
{
    m_CurrentPageIndex = m_Level = 0;
    m_TotalPages = NumOfPages;

    for( int i = 0; i < m_TotalPages && i < MAX_PAGES; i++ )
    {
        if( PageType[ i ] == "Voltage" )
        {
            m_pPages[ i ] = new CMenuPageVoltage;
        }
        else
        {
            m_pPages[ i ] = new CMenuPageBase;
        }
        m_pPages[ i ]->SetPageIndex( i );
        m_pPages[ i ]->SetPageType( PageType[ i ] );
    }
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
    for( int i = 0; i < MAX_PAGES; i++ )
    {
        if( m_pPages[ i ] ) delete m_pPages[ i ];
    }
}

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenu::IncrementPageIndex()                                             */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
void CMenu::IncrementCurrentPageIndex()
{
    if( m_CurrentPageIndex < m_TotalPages - 1 ) m_CurrentPageIndex++;
}

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenu::DecrementPageIndex()                                             */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
void CMenu::DecrementCurrentPageIndex()
{
    if( m_CurrentPageIndex > 0 ) m_CurrentPageIndex--;
}

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenu::IncrementValueFromPage()                                         */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
void CMenu::IncrementValueFromPage( int PageIndex )
{
    if( PageIndex == -1 ) PageIndex = m_CurrentPageIndex;
    GetPage( PageIndex )->IncrementValue();
}

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenu::DecrementValueFromPage()                                         */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
void CMenu::DecrementValueFromPage( int PageIndex )
{
    if( PageIndex == -1 ) PageIndex = m_CurrentPageIndex;
    GetPage( PageIndex )->DecrementValue();
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
    myLcd.print( this->GetLevel(), DEC );
    myLcd.print( ", Page " );
    myLcd.print( this->GetCurrentPageIndex(), DEC );
    myLcd.setCursor( 0, 1 );
    myLcd.print( this->GetPage()->GetPageType() );
    myLcd.print( ": " );
    if( this->GetPage()->GetPageType() == "Voltage" )
    {
        CMenuPageVoltage* MPV = (CMenuPageVoltage*)this->GetPage();
        myLcd.print( MPV->GetValue(), 2 );
    }
    else
    {
        myLcd.print( this->GetPage()->GetValue(), DEC );
    }
    myLcd.print( this->GetPage()->GetUnit() );
}
