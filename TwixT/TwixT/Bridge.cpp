#include "Bridge.h"

Bridge::Bridge(Pillar start, Pillar end, QColor color, QWidget* parent) :
	Piece{color,parent}
{
	p_start = start.getCoordinates();
	p_end = end.getCoordinates();
}
