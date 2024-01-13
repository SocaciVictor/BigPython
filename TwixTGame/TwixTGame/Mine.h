#pragma once
#include "Base.h"

class Mine : public Base
{
private:
	PieceColor m_color;
	bool m_active;
public:
	Mine() = default;
	Mine(const Point& coordinates, const bool& active, const PieceColor& color);
	void setActive(const bool& active);
	bool getActive();
	void setColor(const PieceColor& color);
	virtual PieceColor getColor() const noexcept override;
};
