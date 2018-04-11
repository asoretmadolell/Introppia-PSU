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

    // Model !!!
    m_VoltagePwm[ 0 ] = 0;
    m_VoltagePwm[ 0.5 ] = 19;
    m_VoltagePwm[ 1 ] = 21;
    m_VoltagePwm[ 1.5 ] = 24;
    m_VoltagePwm[ 2 ] = 27;
    m_VoltagePwm[ 2.5 ] = 30;
    m_VoltagePwm[ 3 ] = 34;
    m_VoltagePwm[ 3.5 ] = 39;
    m_VoltagePwm[ 4 ] = 44;
    m_VoltagePwm[ 4.5 ] = 50;
    m_VoltagePwm[ 5 ] = 55;
    m_VoltagePwm[ 5.5 ] = 60;
    m_VoltagePwm[ 6 ] = 67;
    m_VoltagePwm[ 6.5 ] = 75;
    m_VoltagePwm[ 7 ] = 85;
    m_VoltagePwm[ 7.5 ] = 97;
    m_VoltagePwm[ 8 ] = 106;
    m_VoltagePwm[ 8.5 ] = 120;
    m_VoltagePwm[ 9 ] = 137;
    m_VoltagePwm[ 9.5 ] = 156;
    m_VoltagePwm[ 10 ] = 177;
    m_VoltagePwm[ 10.5 ] = 199;
    m_VoltagePwm[ 11 ] = 225;
    m_VoltagePwm[ 11.5 ] = 250;
    m_VoltagePwm[ 12 ] = 255;
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
