#include "GameElement.h"

GameElement::GameElement(GameElement* parent) : m_parent{ parent }
{
}

GameElement* GameElement::getParent() const noexcept
{
	return m_parent;
}