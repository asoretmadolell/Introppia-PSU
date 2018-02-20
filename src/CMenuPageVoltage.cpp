#include "Arduino.h"

#include "CMenu_Classes.h"

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenuPageVoltage::CMenuPageVoltage()                                    */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
CMenuPageVoltage::CMenuPageVoltage()
{
    m_VoltageValue = 0;
}

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenuPageVoltage::IncrementValue()                                      */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
void CMenuPageVoltage::IncrementValue()
{
    if( m_VoltageValue < MAX_VOLTAGE ) m_VoltageValue += 0.5;
}

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenuPageVoltage::DecrementValue()                                      */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
void CMenuPageVoltage::DecrementValue()
{
    if( m_VoltageValue > 0) m_VoltageValue -= 0.5;
}
