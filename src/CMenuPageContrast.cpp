#include "Arduino.h"

#include "CMenu_Classes.h"

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenuPageContrast::CMenuPageContrast()                                  */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
CMenuPageContrast::CMenuPageContrast()
{
    m_ContrastValue = 0;
}

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenuPageContrast::IncrementValue()                                     */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
void CMenuPageContrast::IncrementValue()
{
    if( m_ContrastValue < MAX_PWM ) m_ContrastValue += 5;
}

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenuPageContrast::DecrementValue()                                     */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
void CMenuPageContrast::DecrementValue()
{
    if( m_ContrastValue > 0) m_ContrastValue -= 5;
}
