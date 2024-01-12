#include "MainMenu.h"
#include"TwixTGame.h"

MainMenu::MainMenu(QObject* parent) : QGraphicsScene{ 0,0,960,540,parent } ,
    m_fundal{ QPixmap{ "../assets/fundal.png" } }
{
    m_fundal.setTransformationMode(Qt::SmoothTransformation);
    m_fundal.setScale(0.5);
    //creem butoanele;
    m_buttons[0] = std::make_unique<Button>("../assets/play", QPoint{20,190});
    m_buttons[1] = std::make_unique<Button>( "../assets/load",QPoint{20,254} );
    m_buttons[2] = std::make_unique<Button>("../assets/screen", QPoint{ 20,318 });
    m_buttons[3] = std::make_unique<Button>("../assets/quit", QPoint{ 20,382 });
    m_buttons[4] = std::make_unique<Button>("../assets/normalgame", QPoint{ 20,190 });
    m_buttons[5] = std::make_unique<Button>("../assets/aigame", QPoint{ 20,254 });
    m_buttons[6] = std::make_unique<Button>("../assets/back", QPoint{ 20,318 });
    //adaugam functiionalitatea butoanelor;
    QObject::connect(m_buttons[0].get(), &Button::buttonClicked, this, &MainMenu::play);
    QObject::connect(m_buttons[1].get(), &Button::buttonClicked, static_cast<TwixTGame*>(parent), &TwixTGame::load);
    QObject::connect(m_buttons[2].get(), &Button::buttonClicked, static_cast<TwixTGame*>(parent), &TwixTGame::switchScreen);
    QObject::connect(m_buttons[3].get(), &Button::buttonClicked, static_cast<TwixTGame*>(parent), &TwixTGame::exit);
    QObject::connect(m_buttons[4].get(), &Button::buttonClicked, static_cast<TwixTGame*>(parent), &TwixTGame::normalGame);
    QObject::connect(m_buttons[5].get(), &Button::buttonClicked, static_cast<TwixTGame*>(parent), &TwixTGame::aiGame);
    QObject::connect(m_buttons[6].get(), &Button::buttonClicked, this, &MainMenu::back);
    addItem(&m_fundal);
    for (uint16_t i = 0;i<4;i++)
    {
        addItem(m_buttons[i].get());
    }
}

void MainMenu::play()
{
    for (uint16_t i = 0; i < 4; i++)
    {
        removeItem(m_buttons[i].get());
    }
    for (uint16_t i = 4; i < 7; i++)
    {
        addItem(m_buttons[i].get());
    }
}

void MainMenu::back()
{
    for (uint16_t i = 4; i < 7; i++)
    {
        removeItem(m_buttons[i].get());
    }
    for (uint16_t i = 0; i < 4; i++)
    {
        addItem(m_buttons[i].get());
    }  
}
