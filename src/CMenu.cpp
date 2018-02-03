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
/* CMenuPage::CMenuPage()                                                  */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
CMenuPage::CMenuPage()
{
    m_VoltageValue = m_DefaultValue = m_PageIndex = 0;
}

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenuPage::IncrementValue()                                             */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
void CMenuPage::IncrementValue()
{
    if( m_PageType == "Voltage" )
    {
        if( m_VoltageValue < MAX_VOLTAGE ) m_VoltageValue += 0.5;
    }
    else
    {
        m_DefaultValue++;
    }
}

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenuPage::DecrementValue()                                             */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
void CMenuPage::DecrementValue()
{
    if( m_PageType == "Voltage" )
    {
        if( m_VoltageValue > 0) m_VoltageValue -= 0.5;
    }
    else
    {
        m_DefaultValue--;
    }
}

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenu::CMenu()                                                          */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
CMenu::CMenu( int NumOfPages, String PageType[] )
{
    m_Level = 0;
    m_CurrentPageIndex = 0;
    m_TotalPages = NumOfPages;

    for( int i = 0; i < m_TotalPages && i < MAX_PAGES; i++ )
    {
        m_pPages[ i ] = new CMenuPage;
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
    CMenuPage* MenuPage = GetPage( PageIndex );
    MenuPage->IncrementValue();
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
    CMenuPage* MenuPage = GetPage( PageIndex );
    MenuPage->DecrementValue();
}

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenu::Print()                                                          */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
void CMenu::Print( CMenuPage* MenuPage )
{
    myLcd.clear();
    myLcd.setCursor( 0, 0 );
    myLcd.print( "Level " );
    myLcd.print( this->GetLevel(), DEC );
    myLcd.print( ", Page " );
    myLcd.print( MenuPage->GetPageIndex(), DEC );
    myLcd.setCursor( 0, 1 );
    myLcd.print( MenuPage->GetPageType() );
    myLcd.print( ": " );
    if( MenuPage->GetPageType() == "Voltage" )
    {
        myLcd.print( MenuPage->GetVoltageValue(), 2 );
    }
    else
    {
        myLcd.print( MenuPage->GetDefaultValue(), DEC );
    }
    myLcd.print( MenuPage->GetUnit() );
}
