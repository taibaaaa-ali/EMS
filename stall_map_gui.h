#ifndef STALL_MAP_GUI_H
#define STALL_MAP_GUI_H

int showStallMapGUI(const bool* bookedStalls);

#endif

#ifdef USE_SFML
#include <SFML/Graphics.hpp>
#endif
#include <iostream>

int showStallMapGUI(const bool* bookedStalls)
{
#ifdef USE_SFML
    try
    {
        sf::RenderWindow window(sf::VideoMode(600, 400), "Select Your Stall");
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) 
            throw std::runtime_error("Font not found");

        sf::RectangleShape stalls[6];
        sf::Text labels[6];
        int positions[6][2] = { {100,60}, {400,60}, {100,180}, {400,180}, {200,320}, {300,320} };
        sf::Color available(150, 200, 255); 
        sf::Color taken(160, 160, 160);     

        for (int i = 0; i < 6; ++i)
        {
            stalls[i].setSize(sf::Vector2f(80, 60));
            stalls[i].setPosition(positions[i][0], positions[i][1]);
            stalls[i].setFillColor(bookedStalls && bookedStalls[i + 1] ? taken : available);
            stalls[i].setOutlineThickness(3);
            stalls[i].setOutlineColor(sf::Color::Black);

            labels[i].setFont(font);
            if (bookedStalls && bookedStalls[i + 1])
                labels[i].setString("-");
            else
                labels[i].setString(std::to_string(i + 1));
            labels[i].setCharacterSize(24);
            labels[i].setFillColor(sf::Color::Black);
            labels[i].setPosition(positions[i][0] + 30, positions[i][1] + 15);
        }

        sf::Text instructions;
        instructions.setFont(font);
        instructions.setString("Click on an available stall (blue) to select (1-6)");
        instructions.setCharacterSize(20);
        instructions.setFillColor(sf::Color::Black);
        instructions.setPosition(70, 10);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    for (int i = 0; i < 6; ++i)
                    {
                        if (!(bookedStalls && bookedStalls[i + 1]))
                        {
                            if (stalls[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
                            {
                                window.close();
                                return i + 1;
                            }
                        }
                    }
                }
            }

            window.clear(sf::Color(220, 230, 240));
            window.draw(instructions);
            for (int i = 0; i < 6; ++i)
            {
                window.draw(stalls[i]);
                window.draw(labels[i]);
            }
            window.display();
        }
        return 0;
    }
    catch (...)
    {
    }
#endif

    std::cout << "\n[Simplified] SFML not available, using ASCII fallback.\n";
    std::cout << "+-----------+\n";
    std::cout << "| ";
    std::cout << (bookedStalls && bookedStalls[1] ? " - " : "[1]");
    std::cout << "   ";
    std::cout << (bookedStalls && bookedStalls[2] ? " - " : "[2]");
    std::cout << " |\n|           |\n| ";
    std::cout << (bookedStalls && bookedStalls[3] ? " - " : "[3]");
    std::cout << "   ";
    std::cout << (bookedStalls && bookedStalls[4] ? " - " : "[4]");
    std::cout << " |\n|           |\n| ";
    std::cout << (bookedStalls && bookedStalls[5] ? " - " : "[5]");
    std::cout << " ";
    std::cout << (bookedStalls && bookedStalls[6] ? " - " : "[6]");
    std::cout << "   |\n";
    std::cout << "+-----------+\n";
    std::cout << "Select a stall ID (1-6): ";
    int stallID;
    std::cin >> stallID;
    return stallID;
}
