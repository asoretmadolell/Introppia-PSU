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
    m_PageIndex = m_Value = 0;
}

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenu::CMenu()                                                          */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
CMenu::CMenu( int NumOfPages )
{
    m_Level = 0;
    m_CurrentPageIndex = 0;
    m_TotalPages = NumOfPages;

    for( int i = 0; i < m_TotalPages && i < MAX_PAGES; i++ )
    {
        m_pPages[ i ] = new CMenuPage;
        m_pPages[ i ]->SetPageIndex( i );
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
    MenuPage->SetValue( MenuPage->GetValue() + 1 );
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
    MenuPage->SetValue( MenuPage->GetValue() - 1 );
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
    myLcd.print( "Value " );
    myLcd.print( MenuPage->GetValue(), DEC );
}
