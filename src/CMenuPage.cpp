#include "Arduino.h"

#include "CMenu_Classes.h"

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

