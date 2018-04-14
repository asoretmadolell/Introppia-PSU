#include "Arduino.h"

#include "CMenu_Classes.h"

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenuPagePedal::CMenuPagePedal()                                        */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
CMenuPagePedal::CMenuPagePedal()
{
    m_PedalValue = true;
}

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenuPagePedal::IncrementValue()                                        */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
void CMenuPagePedal::IncrementValue()
{
    if( m_PedalValue == false ) m_PedalValue = true;
}

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenuPagePedal::DecrementValue()                                        */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
void CMenuPagePedal::DecrementValue()
{
    if( m_PedalValue == true ) m_PedalValue = false;
}
