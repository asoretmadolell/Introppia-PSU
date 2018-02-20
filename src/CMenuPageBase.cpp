#include "Arduino.h"

#include "CMenu_Classes.h"

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenuPageBase::CMenuPageBase()                                          */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
CMenuPageBase::CMenuPageBase()
{
    m_DefaultValue = m_PageIndex = 0;
}

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenuPageBase::IncrementValue()                                         */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
void CMenuPageBase::IncrementValue()
{
    m_DefaultValue++;
}

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/* CMenuPageBase::DecrementValue()                                         */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
void CMenuPageBase::DecrementValue()
{
    m_DefaultValue--;
}
