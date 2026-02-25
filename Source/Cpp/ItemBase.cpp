#include "../Haeder/ItemBase.h"

ItemBase::ItemBase()
: m_price(0)
, m_iconHandle(-1)
, m_modelHandle(-1)
{
}

ItemBase::~ItemBase()
{
}

int ItemBase::GetIcon() const
{
    return m_iconHandle;
}

float ItemBase::GetPickupRadius() const
{
    return 80.0f;
}

int ItemBase::GetPrice() const
{
    return m_price;
}