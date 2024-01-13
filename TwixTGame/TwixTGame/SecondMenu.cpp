#include "SecondMenu.h"
#include "TwixTGame.h"

void SecondMenu::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QPainterPath path;
    path.addRoundedRect(rect(), 10, 10);
    QColor culoareCuOpacitate(71, 152, 206, 128);
    QBrush brush(culoareCuOpacitate);
    painter->setBrush(brush);
    QPen pen(Qt::black);
    pen.setWidth(4);
    painter->setPen(pen);
    painter->drawPath(path);
}

void SecondMenu::mousePressEvent(QGraphicsSceneMouseEvent* event)
{}

void SecondMenu::hoverEnterEvent(QGraphicsSceneHoverEvent * event)
{
    QGraphicsRectItem::hoverEnterEvent(event);
}

SecondMenu::SecondMenu(QGraphicsScene* parent)
{
    setZValue(3);
    setRect(100, 50, 760, 440);
    setCursor(Qt::ArrowCursor);
    m_logo.setTransformationMode(Qt::SmoothTransformation);
    m_logo.setScale(0.5);
    m_logo.setPos(175, 100);
    m_winer.setTransformationMode(Qt::SmoothTransformation);
    m_winer.setScale(0.5);
    m_winer.setPos(230, 250);
    m_buttons[0] = std::make_unique<Button>("../assets/screen2",QPoint{420,130},this);
    m_buttons[1] = std::make_unique<Button>( "../assets/load2",QPoint{180,370},this );
    m_buttons[2] = std::make_unique<Button>( "../assets/save",QPoint{385,370},this );
    m_buttons[3] = std::make_unique<Button>( "../assets/exit2",QPoint{590,370},this );
    m_buttons[4] = std::make_unique<Button>("../assets/exitbutt", QPoint{ 520,370 },this);
    m_buttons[5] = std::make_unique<Button>("../assets/newgame", QPoint{ 205,370 },this);
    QObject::connect(m_buttons[0].get(), &Button::buttonClicked, static_cast<TwixTGame*>(parent->parent()), &TwixTGame::switchScreen);
    QObject::connect(m_buttons[1].get(), &Button::buttonClicked, static_cast<GameScene*>(parent), &GameScene::resetGame);
    QObject::connect(m_buttons[2].get(), &Button::buttonClicked, static_cast<GameScene*>(parent), &GameScene::saveGame);
    QObject::connect(m_buttons[3].get(), &Button::buttonClicked, static_cast<TwixTGame*>(parent->parent()), &TwixTGame::backToMainMenu);
    QObject::connect(m_buttons[4].get(), &Button::buttonClicked, static_cast<TwixTGame*>(parent->parent()), &TwixTGame::backToMainMenu);
    QObject::connect(m_buttons[5].get(), &Button::buttonClicked, static_cast<GameScene*>(parent), &GameScene::resetGame);
    setNormal();
}

void SecondMenu::setEnd()
{
    m_buttons[0]->setVisible(false);
    m_buttons[1]->setVisible(false);
    m_buttons[2]->setVisible(false);
    m_buttons[3]->setVisible(false);
    m_buttons[4]->setVisible(true);
    m_buttons[5]->setVisible(true);
    m_winer.setVisible(true);
}

void SecondMenu::setNormal()
{
    m_winer.setVisible(false);
    m_buttons[4]->setVisible(false);
    m_buttons[5]->setVisible(false);
    m_buttons[0]->setVisible(true);
    m_buttons[1]->setVisible(true);
    m_buttons[2]->setVisible(true);
    m_buttons[3]->setVisible(true);
}

void SecondMenu::setWinner(const QString& path)
{
    m_winer.setPixmap(QPixmap{path});

}
