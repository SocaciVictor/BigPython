#pragma once
#include<string>

class Table
{
private:
	int height;
	int width;
	int pozitionX;
	int pozitionY;
	std::string color;
	

public:
	//Constructor Deconstructor
	Table(int height,int width,std::string color,int pozitionX,int pozitionY);
	~Table();
	//Setteri
	void setHeight(int height);
	void setWidth(int width);
	void setColor(std::string color);
	void setPozitionX();
	void setPozitionY();
	//Geteri
	int getHeight();
	int getWidth();
	int getPozitionX();
	int getPozitionY();
	std::string getColor();
};

