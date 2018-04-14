#ifndef CMENU_H_
#define CMENU_H_

#include "Arduino.h"
#include <map>

/***************************************************************************/
/*                                                                         */
/* Defines                                                                 */
/*                                                                         */
/***************************************************************************/
#define MAX_PAGES   20
#define MAX_PWM     255
#define MAX_VOLTAGE 12

enum { Default, Pwm, Pedal, Contrast };

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

public:
              CMenuPageBase();
    virtual   ~CMenuPageBase() {}

    int       GetPageIndex() { return m_PageIndex; }
    void      SetPageIndex( int PageIndex ) { m_PageIndex = PageIndex; }

    // Overridable methods
    virtual String  GetName() { return "Unknown"; }
    virtual int     GetType() { return Default; }
    virtual String  GetUnit() { return "Unknown"; }

    // Pure methods
    virtual void    IncrementValue() = 0;
    virtual void    DecrementValue() = 0;
};

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/*                                                                         */
/* CMenuPagePwm Class                                                      */
/*                                                                         */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
class CMenuPagePwm : public CMenuPageBase
{
private:
    int     m_PwmValue;

public:
            CMenuPagePwm();
    virtual ~CMenuPagePwm() {}

    // Base overridden methods
    virtual String  GetName() { return "Pwm"; }
    virtual int     GetType() { return Pwm; }
    virtual String  GetUnit() { return "Bits"; }

    // Base pure methods
    virtual void    IncrementValue();
    virtual void    DecrementValue();

    // Class methods
            int     GetPwm() { return m_PwmValue; }
            void    SetPwm( int PwmValue ) { m_PwmValue = PwmValue; }
};

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/*                                                                         */
/* CMenuPagePedal Class                                                    */
/*                                                                         */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
class CMenuPagePedal : public CMenuPageBase
{
private:
    bool    m_PedalValue;

public:
            CMenuPagePedal();
    virtual ~CMenuPagePedal() {}

    // Base overridden methods
    virtual String  GetName() { return "Pedal"; }
    virtual int     GetType() { return Pedal; }
    virtual String  GetUnit() { return ""; }

    // Base pure methods
    virtual void    IncrementValue();
    virtual void    DecrementValue();

    // Class pure methods
            bool    GetPedal() { return m_PedalValue; }
            void    SetPedal( bool PedalValue ) { m_PedalValue = PedalValue; }
};

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/*                                                                         */
/* CMenuPageContrast Class                                                 */
/*                                                                         */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
class CMenuPageContrast : public CMenuPageBase
{
private:
    int     m_ContrastValue;

public:
            CMenuPageContrast();
    virtual ~CMenuPageContrast() {}

    // Base overridden methods
    virtual String  GetName() { return "Contrast"; }
    virtual int     GetType() { return Contrast; }
    virtual String  GetUnit() { return "Bits"; }

    // Base pure methods
    virtual void    IncrementValue();
    virtual void    DecrementValue();

    // Class pure methods
            int     GetContrast() { return m_ContrastValue; }
            void    SetContrast( int ContrastValue ) { m_ContrastValue = ContrastValue; }
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
                    CMenu( int NumOfPages, int PageType[] );
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
