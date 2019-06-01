#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Interface {
public:
    void process();
};

void Interface::process() {
    sf::RenderWindow window(sf::VideoMode(1300, 650), "ChessPlusPlus", sf::Style::Titlebar);
    sf::Texture chessbacktext;
    if (!chessbacktext.loadFromFile("Images/chessboardback.png")) std::cout << "Chessback error\n";
    sf::Texture chessfronttext;
    if (!chessfronttext.loadFromFile("Images/chessboardfront.png")) std::cout << "Chessfront error\n";
    sf::Texture choosepiecetext;
    if (!choosepiecetext.loadFromFile("Images/choosepiece.png")) std::cout << "Choose piece error\n";
    sf::Texture chosenpiecetext;
    if (!chosenpiecetext.loadFromFile("Images/chosenpiece.png")) std::cout << "Chosen piece error\n";
    sf::Texture invalidpiecetext;
    if (!invalidpiecetext.loadFromFile("Images/invalidpiece.png")) std::cout << "Invalid piece error\n";
    sf::Texture validpiecetext;
    if (!validpiecetext.loadFromFile("Images/validpiece.png")) std::cout << "Valid piece error\n";


    sf::Sprite chessback(chessbacktext);
    sf::Sprite chessfront(chessfronttext);
    sf::Sprite choosepiece(choosepiecetext);
    sf::Sprite chosenpiece(chosenpiecetext);
    sf::Sprite invalidpiece(invalidpiecetext);
    sf::Sprite validpiece(validpiecetext);

    bool moved = false;
    int movetimer = 0;
    int MOVEBUFFER = 50;
    int MOVESPEED = 79;
    bool firstPieceSelected = false;
    bool secondPieceSelected = false;
    bool validMove = false;
    double speedFactor = 1;
    //int savex, savey;

    while (window.isOpen())
    {
        if (!window.hasFocus()) continue;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (!moved && choosepiece.getPosition().y != (MOVESPEED * -7)) {
                choosepiece.move(0.f, float(-1 * MOVESPEED * speedFactor));
                moved = true;
                movetimer = MOVEBUFFER;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (!moved && choosepiece.getPosition().y != 0) {
                choosepiece.move(0.f, float(MOVESPEED * speedFactor));
                moved = true;
                movetimer = MOVEBUFFER;
            }

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (!moved && choosepiece.getPosition().x != (MOVESPEED * -4)) {
                choosepiece.move(float(-1 * MOVESPEED * speedFactor), 0.f);
                moved = true;
                movetimer = MOVEBUFFER;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (!moved && choosepiece.getPosition().x != (MOVESPEED * 3)) {
                choosepiece.move(float(MOVESPEED * speedFactor), 0.f);
                moved = true;
                movetimer = MOVEBUFFER;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            if (!firstPieceSelected) {
                //std::cout << "firstpieceselected\n";
                firstPieceSelected = true;
                chosenpiece.setPosition(choosepiece.getPosition());
                moved = true;
                movetimer = MOVEBUFFER;
            }
            else if (!moved) {
                //std::cout << "secondpieceselected\n";
                secondPieceSelected = true;
                chosenpiece.setPosition(choosepiece.getPosition());
                moved = true;
                movetimer = MOVEBUFFER;
            }
        }

        if (secondPieceSelected) {
            bool VALID_MOVE;
            std::cin >> VALID_MOVE;

            if (VALID_MOVE) {
                validMove = true;
                validpiece.setPosition(choosepiece.getPosition());

            }
            else {
                invalidpiece.setPosition(choosepiece.getPosition());

            }
        }

        if (moved) {

            if (movetimer == 0) {
                moved = false;
            }
            else --movetimer;
        }
        //std::cout << choosepiece.getPosition().x << " " << choosepiece.getPosition().y << std::endl;

        window.clear();
        window.draw(chessback);
        window.draw(chessfront);

        window.draw(choosepiece);
        if (firstPieceSelected) {
            //std::cout << "\tfirstpieceselected is true\n";
            //savex = choosepiece.getPosition().x;
            //savey = choosepiece.getPosition().y;
            if (secondPieceSelected) {
                //std::cout << "\tsecondpieceselected is true\n";

                if (validMove) {
                    //std::cout << "\tvalid move is true\n";
                    window.draw(validpiece);
                }
                else {
                    //std::cout << "\tvalid move is not true\n";
                    window.draw(invalidpiece);

                }
                //firstPieceSelected = false;
                //secondPieceSelected = false;
            }
            else window.draw(chosenpiece);
        }
        window.display();
    }
}



#endif