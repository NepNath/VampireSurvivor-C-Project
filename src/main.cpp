#include <SFML/Graphics.hpp>
#include <print>


void center_horizontally(const auto& parent, auto& child)
{
    const auto parentBoundingBox = parent.getLocalBounds();
    const sf::Vector2f parentLocalCenter{parentBoundingBox.left + parentBoundingBox.width * 0.5f,
                                         parentBoundingBox.top + parentBoundingBox.height * 0.5f};

    const sf::Vector2f parentGlobalCenter = parent.getTransform().transformPoint(parentLocalCenter);

    const auto childBoundingBox = child.getLocalBounds();
    const auto childOrigin = child.getOrigin();
    child.setOrigin(childBoundingBox.left + childBoundingBox.width * 0.5f, childOrigin.y);

    const auto childPosition = child.getPosition();
    child.setPosition(parentGlobalCenter.x, childPosition.y);
}

void center_vertically(const auto& parent, auto& child)
{
    const auto parentBoundingBox = parent.getLocalBounds();
    const sf::Vector2f parentLocalCenter{parentBoundingBox.left + parentBoundingBox.width * 0.5f,
                                         parentBoundingBox.top + parentBoundingBox.height * 0.5f};

    const sf::Vector2f parentGlobalCenter = parent.getTransform().transformPoint(parentLocalCenter);

    const auto childBoundingBox = child.getLocalBounds();
    const auto childOrigin = child.getOrigin();
    child.setOrigin(childOrigin.x, childBoundingBox.top + childBoundingBox.height * 0.5f);

    const auto childPosition = child.getPosition();
    child.setPosition(childPosition.x, parentGlobalCenter.y);
}


int main()
{
    int windowWidth = 800, windowHeight = 600;

    sf::Image icon;
    sf::Font font;

    int selectedButton;
    

    //---------------------------- Menu play button ----------------------------
    float menuPlayButtonWidth = 200.0f, menuPlayButtonHeight = 50.0f;
    sf::RectangleShape menuPlayButton(sf::Vector2f(menuPlayButtonWidth, menuPlayButtonHeight));
    menuPlayButton.setFillColor(sf::Color(150, 150, 150));
    menuPlayButton.setOutlineColor(sf::Color(255, 255, 255));
    menuPlayButton.setOutlineThickness(2.0f);

    menuPlayButton.setPosition((windowWidth - menuPlayButton.getSize().x) / 2.0f,(windowHeight - menuPlayButton.getSize().y) / 2.0f);

    sf::Text playButtonText; 
    playButtonText.setFont(font);
    playButtonText.setString("Play");
    playButtonText.setCharacterSize(20);
    center_horizontally(menuPlayButton, playButtonText);
    center_vertically(menuPlayButton, playButtonText);
    playButtonText.setFillColor(sf::Color::White);



    //---------------------------- Menu quit button ----------------------------
    float menuQuitButtonWidth = 200.0f, menuQuitButtonHeight = 50.0f;
    sf::RectangleShape menuQuitButton(sf::Vector2f(menuQuitButtonWidth, menuQuitButtonHeight));
    menuQuitButton.setFillColor(sf::Color(150, 0, 0));
    menuQuitButton.setOutlineColor(sf::Color(255, 0, 0));
    menuQuitButton.setOutlineThickness(2.0f);
    menuQuitButton.setPosition((windowWidth - menuQuitButton.getSize().x) / 2.0f,(windowHeight - menuQuitButton.getSize().y) / 2.0f);
    menuQuitButton.setPosition(windowWidth / 2.0f, windowHeight / 1.6f);

    //title text
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString("An absolutly incredible game (lie)");
    titleText.setCharacterSize(25);
    titleText.setPosition(windowWidth / 2.f, windowHeight);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition( 180, 100);

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "buhh", sf::Style::Default);

 


    if (icon.loadFromFile("assets/icon.png"))
    {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    else
    {
        std::println("Failed to load icon image");
    }

    if (font.loadFromFile("assets/font.ttf"))
    {
        
    }
    else if (!font.loadFromFile("assets/font.ttf"))
    {
        std::println("Failed to load font");
    }

    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {

        // gestion d'événements
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Demande de fermeture (croix de fermeture, alt+f4, etc.)
            if (event.type == sf::Event::Closed)
            {
                window.close();
                std::println("window has been closed");
                // return 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
                std::println("Escape key pressed, closing window");
                // return 0;
            }
            

          
            //d'autre évènements peuvent être gérés ici
        }

        // Effacement de l'ancienne frame (framebuffer)
        window.clear(sf::Color::Black);

        // ... Ici on dessine les objets, sprites, textes, formes, etc. ...
        
        window.draw(menuPlayButton);
        window.draw(playButtonText);
        
        window.draw(menuQuitButton);
        window.draw(titleText);
         
        window.display(); // Affichage de la nouvelle frame
    }

    return 0;
}

