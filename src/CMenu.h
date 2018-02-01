#ifndef CMENU_H_
#define CMENU_H_

#include "Arduino.h"

/***************************************************************************/
/*                                                                         */
/* Defines                                                                 */
/*                                                                         */
/***************************************************************************/
#define MAX_PAGES   20

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/*                                                                         */
/* CMenuPage Class                                                         */
/*                                                                         */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
class CMenuPage
{
private:
    int       m_Page;
    int       m_Value;
    String    m_Unit;
    String    m_ValueName;

public:
              CMenuPage();
    virtual   ~CMenuPage() {}

    int       GetPage() { return m_Page; }
    void      SetPage( int Page ) { m_Page = Page; }
    int       GetValue() { return m_Value; }
    void      SetValue( int Value ) { m_Value = Value; }
    String    GetUnit() { return m_Unit; }
    void      SetUnit( String Unit ) { m_Unit = Unit; }
    String    GetValueName() { return m_ValueName; }
    void      SetValueName( String ValueName ) { m_ValueName = ValueName; }
};

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/*                                                                         */
/* CMenu Class                                                             */
/*                                                                         */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
class CMenu
{
private:
    int         m_Level;
    int         m_CurrentPageIndex;
    int         m_TotalPages;
    CMenuPage*  m_pPages[ MAX_PAGES ];

public:
                CMenu( int NumOfPages );
    virtual     ~CMenu();

    int         GetLevel() { return m_Level; }
    void        SetLevel( int Level ) { m_Level = Level; }
    int         GetCurrentPageIndex() { return m_CurrentPageIndex; }
    void        SetCurrentPageIndex( int CurrentPageIndex ) { m_CurrentPageIndex = CurrentPageIndex; }
    int         GetTotalPages() { return m_TotalPages; }
    void        SetTotalPages( int TotalPages) { m_TotalPages = TotalPages; }
    CMenuPage*  GetPage( int PageIndex ) { return m_pPages[ PageIndex ]; }

    void        IncrementValueFromPage( int PageIndex );
    void        DecrementValueFromPage( int PageIndex );
    void        Print();
};

#endif /* CMENU_H_ */