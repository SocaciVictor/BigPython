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

void Buldozer::addBasesPoint(const Point& point)
{
    m_basesPoint.insert(point);
}

void Buldozer::addBluePillarsPoint(const Point& point)
{
    m_bluePillarsPoint.insert(point);
    m_basesPoint.erase(point);
}

void Buldozer::addRedPillarsPoint(const Point& point)
{
    m_redPillarsPoint.insert(point);
    m_basesPoint.erase(point);
}

const Point& Buldozer::coinToss()
{
    //verific daca mananc un pillar sau nu;
    if (generateRandomNumber(1, 100) <= eatProbability()) {
        //verific daca pillarul mancat va fi albastru sau nu;
        if (generateRandomNumber(1, 100) <= eatBlueProbability()) {
            auto it = m_bluePillarsPoint.begin();
            std::advance(it, generateRandomNumber(0, m_bluePillarsPoint.size() - 1));
            Point point = *it;
            m_bluePillarsPoint.erase(it);
            m_basesPoint.insert(point);
            m_bluePillarsEat++;
            return point;
        }
        else {
            auto it = m_redPillarsPoint.begin();
            std::advance(it, generateRandomNumber(0, m_redPillarsPoint.size() - 1));
            Point point = *it;
            m_redPillarsPoint.erase(it);
            m_basesPoint.insert(point);
            m_redPillarsEat++;
            return point;
        }
    }
    else {
        auto it = m_basesPoint.begin();
        std::advance(it, generateRandomNumber(0, m_basesPoint.size() - 1));
        return *it;
    }
}
