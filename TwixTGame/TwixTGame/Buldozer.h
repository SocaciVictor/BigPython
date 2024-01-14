#pragma once
#include "Base.h"
#include <random>

class Buldozer final
{
private:
	Point m_coordinates;
	std::unordered_set<Point, PointHash> m_basesPoint;
	std::unordered_set<Point, PointHash> m_bluePillarsPoint;
	std::unordered_set<Point, PointHash> m_redPillarsPoint;
	std::uint16_t m_bluePillarsEat;
	std::uint16_t m_redPillarsEat;
	std::random_device m_random;
	std::uint16_t eatProbability();
	std::uint16_t eatBlueProbability(); 
public:
	Buldozer() = default;
	Buldozer(const Point& coordinates, const std::uint16_t& m_bluePillarsEat=0,const std::uint16_t& m_redPillarsEat=0);
	const Point& getCoordinates() const noexcept;
	uint16_t generateRandomNumber(const uint16_t& min, const uint16_t max);
	void setCoordinates(const Point& coordinates);
	void addBasesPoint(const Point& point);
	void addBluePillarsPoint(const Point& point);
	void addRedPillarsPoint(const Point& point);
	const Point& coinToss();
	friend std::ostream& operator<<(std::ostream& output, const Buldozer& buldozer);
	friend std::istream& operator>>(std::istream& input, Buldozer& buldozer);
};

