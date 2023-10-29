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

};

