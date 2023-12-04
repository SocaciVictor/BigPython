#pragma once

class GameElement
{
private:
	GameElement* m_parent;
public:
	GameElement(GameElement* parent = nullptr);
	GameElement* getParent() const noexcept;
};

