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
CMenu::CMenu( int NumOfPages, int PageType[] )
{
    m_CurrentPageIndex = m_Level = 0;
    m_TotalPages = NumOfPages;

    for( int i = 0; i < m_TotalPages && i < MAX_PAGES; i++ )
    {
        switch( PageType[ i ] )
        {
            case 1:
                m_pPages[ i ] = new CMenuPagePwm;
                break;
            case 2:
                m_pPages[ i ] = new CMenuPagePedal;
                break;
            case 3:
                m_pPages[ i ] = new CMenuPageContrast;
                break;
            default:
                break;
        }
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
    myLcd.print( this->GetPage()->GetName() );
    myLcd.print( ": " );
    switch( this->GetPage()->GetType() )
    {
        case 1:
        {
            CMenuPagePwm* pagePwm = (CMenuPagePwm*)this->GetPage();
            myLcd.print( pagePwm->GetPwm(), DEC );
            break;
        }
        case 2:
        {
            CMenuPagePedal* pagePedal = (CMenuPagePedal*)this->GetPage();
            myLcd.print( pagePedal->GetPedal() );
            break;
        }
        case 3:
        {
            CMenuPageContrast* pageContrast = (CMenuPageContrast*)this->GetPage();
            myLcd.print( pageContrast->GetContrast(), DEC );
            break;
        }
        default:
            break;
    }
    myLcd.print( this->GetPage()->GetUnit() );
}
