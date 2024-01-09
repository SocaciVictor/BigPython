#include "Buldozer.h"

std::uint16_t Buldozer::eatProbability()
{
    /*uint16_t diferenta;
    if (m_borderSize < m_bluePillarsPoint.size() + m_redPillarsPoint.size()) {
        diferenta = 1;
    }
    else {
        diferenta = m_borderSize - m_bluePillarsPoint.size() - m_redPillarsPoint.size();
    }*/
    return 50;
}

std::uint16_t Buldozer::eatBlueProbability()
{
    uint16_t probabiliti;
    if (m_bluePillarsEat > m_redPillarsEat) {
        probabiliti = 50 - 25 * (m_bluePillarsEat - m_redPillarsEat);
    }
    else {
        probabiliti = 50 + 25 * (m_redPillarsEat - m_bluePillarsEat);
    }
    return  probabiliti;
}

Buldozer::Buldozer(const Point& coordinates):
    m_coordinates{ coordinates }, m_bluePillarsEat{ 0 }, m_redPillarsEat{ 0 }
{}

const Point& Buldozer::getCoordinates() const noexcept
{
    return m_coordinates;
}

uint16_t Buldozer::generateRandomNumber(const uint16_t& min, const uint16_t max)
{
    std::mt19937 gen(m_random());

    std::uniform_int_distribution<> distrib(min, max);

    return distrib(gen);
}

void Buldozer::setCoordinates(const Point& coordinates)
{
    m_coordinates = coordinates;
}
 
