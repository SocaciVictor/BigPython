#pragma once
#include <QWidget>
#include "MainWindow.h"


class Base : public QWidget
{
private:
	uint16_t radius;
	QPoint coordinates; //coordanatele mijlocului
	QColor background_color;
public:
	Base(QWidget* parent = nullptr);
	Base(uint16_t radius, uint16_t poz_x, uint16_t poz_y, QColor background_color, QWidget* parent = nullptr);
	Base(uint16_t &radius, QPoint &point, QColor background_color, QWidget* parent = nullptr);
	~Base();
protected:
	void styleBase();
	void enterEvent(QEnterEvent* event);
	void leaveEvent(QEvent* event);
	void mousePressEvent(QMouseEvent*) override;
};

