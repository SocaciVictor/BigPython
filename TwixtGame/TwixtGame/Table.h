#pragma once
#include<string>

class Table
{
private:
	int height;
	int width;
	std::string color;
	

public:
	Table(int height,int width,std::string color);
	~Table();
	void setHeight(int height);
	void setWidth(int width);
	void setColor(std::string color);
	int getHeight();
	int getWidth();
	std::string getColor();
};

