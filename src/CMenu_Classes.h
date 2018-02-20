#ifndef CMENU_H_
#define CMENU_H_

#include "Arduino.h"

/***************************************************************************/
/*                                                                         */
/* Defines                                                                 */
/*                                                                         */
/***************************************************************************/
#define MAX_PAGES   20
#define MAX_VOLTAGE 12

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/*                                                                         */
/* CMenuPageBase Class                                                     */
/*                                                                         */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
class CMenuPageBase
{
private:
    int       m_PageIndex;
    String    m_PageType;
    int       m_DefaultValue;
    String    m_Unit;
    String    m_ValueName;

public:
              CMenuPageBase();
    virtual   ~CMenuPageBase() {}

    int       GetPageIndex() { return m_PageIndex; }
    void      SetPageIndex( int PageIndex ) { m_PageIndex = PageIndex; }
    String    GetPageType() { return m_PageType; }
    void      SetPageType( String PageType ) { m_PageType = PageType; }
    int       GetValue() { return m_DefaultValue; }
    void      SetValue( int DefaultValue ) { m_DefaultValue = DefaultValue; }
    String    GetUnit() { return m_Unit; }
    void      SetUnit( String Unit ) { m_Unit = Unit; }
    String    GetValueName() { return m_ValueName; }
    void      SetValueName( String ValueName ) { m_ValueName = ValueName; }

    virtual void      IncrementValue();
    virtual void      DecrementValue();
};

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/*                                                                         */
/* CMenuPageVoltage Class                                                  */
/*                                                                         */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
class CMenuPageVoltage : public CMenuPageBase
{
private:
    double    m_VoltageValue;

public:
            CMenuPageVoltage();
    virtual ~CMenuPageVoltage() {}

            double    GetValue() { return m_VoltageValue; }
            void      SetValue( double VoltageValue ) { m_VoltageValue = VoltageValue; }

    virtual void      IncrementValue();
    virtual void      DecrementValue();
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
    int             m_Level;
    int             m_CurrentPageIndex;
    int             m_TotalPages;
    CMenuPageBase*  m_pPages[ MAX_PAGES ];

public:
                    CMenu( int NumOfPages, String PageType[] );
    virtual         ~CMenu();

    int             GetLevel() { return m_Level; }
    void            SetLevel( int Level ) { m_Level = Level; }
    int             GetCurrentPageIndex() { return m_CurrentPageIndex; }
    void            SetCurrentPageIndex( int CurrentPageIndex ) { m_CurrentPageIndex = CurrentPageIndex; }
    int             GetTotalPages() { return m_TotalPages; }
    void            SetTotalPages( int TotalPages) { m_TotalPages = TotalPages; }
    CMenuPageBase*  GetPage( int PageIndex = -1 ) { return PageIndex == -1 ? m_pPages[ m_CurrentPageIndex ] : m_pPages[ PageIndex ]; }

    void            IncrementCurrentPageIndex();
    void            DecrementCurrentPageIndex();
    void            IncrementValueFromPage( int PageIndex = -1 );
    void            DecrementValueFromPage( int PageIndex = -1 );
    void            Print();
};

#endif /* CMENU_H_ */
