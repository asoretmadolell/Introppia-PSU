#include "Arduino.h"
#include "CMenu.h"

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenuPage::CMenuPage()                                                  */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
CMenuPage::CMenuPage()
{
    m_Page = m_Value = 0;
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
    }

//    m_pPages[ 0 ]->SetLevel( 5 );
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
/* CMenu::IncrementValueFromPage()                                         */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
void CMenu::IncrementValueFromPage( int pageIndex )
{
    CMenuPage* MenuPage = GetPage( pageIndex );
    MenuPage->SetValue( MenuPage->GetValue() + 1 );
}

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenu::DecrementValueFromPage()                                         */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
void CMenu::DecrementValueFromPage( int pageIndex )
{
    CMenuPage* MenuPage = GetPage( pageIndex );
    MenuPage->SetValue( MenuPage->GetValue() - 1 );
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
//    printf( "Level = %d\n", m_Level );
}
