#include "game.hpp"
#include "src/menu/ui/window.hpp"
#include <SFML/Graphics.hpp>
#include <print>

namespace game::main
{
    int run()
    {
        sf::RenderWindow window(sf::VideoMode(800, 600), "buhh", sf::Style::Default);
        sf::Image icon;

        if (icon.loadFromFile("assets/icon.png"))
        {
            window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        }
        else
        {
            std::println("Failed to load icon image.");
        }

        window.setFramerateLimit(144);
        window.setVerticalSyncEnabled(true);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                switch (event.type)
                {
                    case sf::Event::Closed:
                        // Demande de fermeture (croix de fermeture, alt+f4, etc.)
                        window.close();
                        std::println("window has been closed");
                        return 0;

                    case sf::Event::KeyPressed:
                        if (event.key.code == sf::Keyboard::Escape)
                        {
                            window.close();
                            std::println("Escape key pressed, closing window");
                            return 0;
                        }
                }
            }
                

            window.clear(sf::Color::Black);

            window.display();
        }
        return 0;
    }
}