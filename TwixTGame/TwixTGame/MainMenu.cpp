#include "MainMenu.h"

MainMenu::MainMenu(QObject* parent) : QGraphicsScene{ 0,0,960,540,parent },
m_fundal{ QPixmap{ "../assets/fundal.png" } }
{
    m_fundal.setTransformationMode(Qt::SmoothTransformation);
    m_fundal.setScale(0.5);
    //creem butoanele si le adaugam;
    m_buttons[0] = std::make_unique<Button>("../assets/play", QPoint{ 115,190 });
    m_buttons[1] = std::make_unique<Button>("../assets/load", QPoint{ 111,260 });
    m_buttons[2] = std::make_unique<Button>("../assets/screen", QPoint{ 80,330 });
    m_buttons[3] = std::make_unique<Button>("../assets/exit", QPoint{ 122,400 });
}

void MainMenu::populateScene()
{
}
