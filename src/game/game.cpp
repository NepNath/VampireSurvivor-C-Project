#include "game.hpp"
#include "src/menu/ui/window.hpp"
#include <SFML/Graphics.hpp>
#include <print>

namespace game::main
{
    int run()
    {
        struct Vector2
        {
            float x;
            float y;
        };

        struct Mouvement
        {
            Vector2 direction;
            float speed;
        };

        struct ProjectileBody
        {
            Vector2 position;
            float width;
            float height;
        };

        // ------ unsorted variables ------
        sf::RenderWindow window(sf::VideoMode(1280, 720), "buhh", sf::Style::Default);
        sf::Image icon;

        sf::Texture playerTexture;

        sf::Clock clock;


        // ------ sprite sheet details ------
        const int spriteFrameWidth = 64;
        const int spriteFrameHeight = 64;

        int currentFrame = 1;
        int maxFrame = 8;

        int directionIndex = 1;

        float animationTimer = .0f;
        float animationSpeed = .1f;

        float speed = 200.0f;

        if (!playerTexture.loadFromFile("assets/characterset8.png"))
        {
            std::println("Erreur : Impossible de charger characterset.png");
        }

        sf::Sprite playerSprite(playerTexture);

        // ------ projectile variables ------




        // ------  ------
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
            bool isMoving = false;

            sf::Time deltaTime = clock.restart();
            float deltaTimeSeconds = deltaTime.asSeconds();

            sf::Vector2f movement(0.0f, 0.0f);

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

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                movement.x -= 1.0f;
                isMoving = true;
                directionIndex = 4;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                movement.x += 1.0f;
                isMoving = true;
                directionIndex = 2;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            {
                movement.y -= 1.0f;
                isMoving = true;
                directionIndex = 4;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                movement.y += 1.0f;
                isMoving = true;
                directionIndex = 3;
            }

            if (isMoving)
            {
                animationTimer += deltaTimeSeconds;

                // Si le chrono dépasse la vitesse définie, on change d'image
                if (animationTimer >= animationSpeed)
                {
                    animationTimer = 0.0f; // On réinitialise le chrono
                    currentFrame++;        // On passe à l'image suivante

                    if (currentFrame >= maxFrame)
                    {
                        currentFrame = 1; // On boucle sur la première image
                    }
                }
            }

            int rectLeft = currentFrame * spriteFrameWidth;
            int rectTop = directionIndex * spriteFrameWidth;

            playerSprite.setTextureRect(sf::IntRect(rectLeft, rectTop, spriteFrameWidth, spriteFrameHeight));

            playerSprite.move(movement * speed * deltaTimeSeconds);
                
            window.clear(sf::Color::Black);
            window.draw(playerSprite);
            window.display();
        }
        return 0;
    }
}