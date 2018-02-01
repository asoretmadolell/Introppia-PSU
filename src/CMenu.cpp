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
CMenu::CMenu( int numOfPages )
{
    m_Level = 0;
    m_CurrentPage = 0;

    for( int i = 0; i < numOfPages && i < MAX_PAGES; i++ )
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
/* CMenu::Print()                                                          */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
void CMenu::Print()
{
//    printf( "Level = %d\n", m_Level );
}
