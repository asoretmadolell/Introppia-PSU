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
/* CMenuPage Class                                                         */
/*                                                                         */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
class CMenuPage
{
private:
     int       m_Value;
     double    m_Voltage;
     String    m_Unit;
     String    m_ValueName;

public:
               CMenuPage();
     virtual   ~CMenuPage() {}

     //Getters & Setters
     int       GetValue() { return m_Value; }
     void      SetValue( int Value ) { m_Value = Value; }
     double    GetVoltage() { return m_Voltage; }
     void      SetVoltage( double Value ) { m_Voltage = Value; }
     String    GetUnit() { return m_Unit; }
     void      SetUnit( String Unit ) { m_Unit = Unit; }
     String    GetValueName() { return m_ValueName; }
     void      SetValueName( String ValueName ) { m_ValueName = ValueName; }

     //Operations
     void      IncrementValue() { m_Value++ }
     void      DecrementValue() { m_Value--; }
     void      IncrementVoltage() { if( m_Voltage < MAX_VOLTAGE ) m_Voltage += 0.5; }
     void      DecrementVoltage() { if( m_Voltage > 0.0 ) m_Voltage -= 0.5; }
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
    CMenuPage*  m_pCurrentPage;

public:
                CMenu();
    virtual     ~CMenu();

    int         GetLevel() { return m_Level; }
    void        SetLevel( int Level ) { m_Level = Level; }
    CMenuPage*  GetCurrentPage() { return m_pCurrentPage; }

    void        IncrementValue() { m_pPage->IncrementValue(); }
    void        DecrementValue() { m_pPage->DecrementValue(); }
    void        IncrementVoltage() { m_pPage->IncrementVoltage(); }
    void        DecrementVoltage() { m_pPage->DecrementVoltage(); }
    void        Print();
};

#endif /* CMENU_H_ */
