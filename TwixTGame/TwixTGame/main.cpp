#include <QtWidgets/QApplication>
#include <QFontDatabase>
#include "ConsoleGame.h"
#include "ConsoleTrainAiGame.h"
#include "ConsoleBuldozeristGame.h"
#include "TwixTGame.h"
#include "ConsoleMineGame.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFont appFont("Itim", 24, 1);
    app.setFont(appFont);
    TwixTGame game;
    uint16_t option; 
    do{ 
        system("CLS");
        std::cout << "Selecteaza mod de joc (0-5) : \n";
        std::cout << "1 : Grafic \n";
        std::cout << "2 : Buldozerist \n";
        std::cout << "3 : Mine \n";
        std::cout << "4 : Player vs AI \n";
        std::cout << "5 : Train AI \n";
        std::cout << "0 : Exit\n";
        std::cout << "Insereaza optiunea: ";
        std::cin >> option;
        switch (option) {
        case 1: {
            game.run();
            option = 0;
            break;
        }
        case 2: {
            ConsoleBuldozeristGame game{"saveB.txt" };
            game.run();
            break;
        }
        case 3: {
            ConsoleMineGame game{"saveM.txt" };
            game.run();
            break;
        }
        case 4: {
            ConsoleTrainAiGame game{ 6,"saveN.txt"};
            game.run();
            break;
        }
        case 5: {
            ConsoleTrainAiGame trainGame{ 6,"saveN.txt" };
            trainGame.train("RedData", "BlueData");
            break;
        }
        case 0: {
            exit(0);
            break;
        }
        default: {
            std::cout << "Optiune incorecta\n";
            system("PAUSE");
            break;
        }
        
        }
    } while (option != 0);

    return app.exec();
}