
#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>


Game::Game(sf::RenderWindow& game_window)
    : window(game_window)
{
    srand(time(NULL));
}
Game::~Game()
{
    delete[] animals;
    delete[] passports;
    delete character;
    delete passport;

}

bool Game::init()
{
    in_menu = true;
    sf::Time time = clocku.restart();
    float dt = time.asSeconds();
    // Initialize menu text and clocks functions for delta time / framerate
    menu_text.setFont(font);
    menu_text.setCharacterSize(40); // Set your desired font size
    menu_text.setFillColor(sf::Color::Red); // Set text color
    menu_text.setString("Animal Control :"); // Text for the menu title
    menu_text.setPosition(window.getSize().x / 2.7 - menu_text.getGlobalBounds().width / 2.7, 100);

    // Initialize Play option text
    play_option.setFont(font);
    play_option.setCharacterSize(30); // Set your desired font size
    play_option.setFillColor(sf::Color::Yellow); // Set text color
    play_option.setString("Play"); // Text for the Play option
    play_option.setPosition(window.getSize().x / 2.2 - play_option.getGlobalBounds().width / 2.2, 200);

    // Initialize Quit option text
    quit_option.setFont(font);
    quit_option.setCharacterSize(30); // Set your desired font size
    quit_option.setFillColor(sf::Color(255, 255, 0, 125)); // Set text color
    quit_option.setString("Quit"); // Text for the Quit option
    quit_option.setPosition(window.getSize().x / 2.2 - quit_option.getGlobalBounds().width / 2.2, 250);
    // init sprite
    if (!background_texture.loadFromFile("Data/WhackaMole Worksheet/background.png"))
    {
        std::cout << "background texture did not load \n";
    }
    background.setTexture(background_texture);
    if (!bird_texture.loadFromFile("Data/WhackaMole Worksheet/bird.png"))
    {
        std::cout << "bird texture did not load \n";
    }
    bird.setTexture(bird_texture);

    bird.setPosition(100, 220);
    bird.setScale(0.5, 0.5);

    // init text
    if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
    {
        std::cout << "font did not load \n";
    }
    title_text.setString("Animal Control");
    title_text.setFont(font);
    title_text.setCharacterSize(100);
    title_text.setFillColor(sf::Color(216, 0, 38, 80));
    title_text.setPosition(
        window.getSize().x / 2.2 - title_text.getGlobalBounds().width / 2.2,
        window.getSize().y / 2.2 - title_text.getGlobalBounds().height / 2.2);

    score_text.setString("score:" + score);
    score_text.setFont(font);
    score_text.setCharacterSize(80);
    score_text.setFillColor(sf::Color(0, 255, 38, 80));
    score_text.setPosition(
        window.getSize().x / 8 - score_text.getGlobalBounds().width / 2,
        window.getSize().y / 16 - score_text.getGlobalBounds().height / 2);


    if (!animals[0].loadFromFile("Data/Critter Crossing Customs/elephant.png"))
    {
        std::cout << "elephant no load :'(";
    }
    if (!animals[1].loadFromFile("Data/Critter Crossing Customs/moose.png"))
    {
        std::cout << "moose gone ;(";
    }
    if (!animals[2].loadFromFile("Data/Critter Crossing Customs/penguin.png"))
    {
        std::cout << "pingu dead ;V";
    }

    if (!passports[0].loadFromFile("Data/Critter Crossing Customs/elephant passport.png"))
    {
        std::cout << "elephant illegal";
    }
    if (!passports[1].loadFromFile("Data/Critter Crossing Customs/moose passport.png"))
    {
        std::cout << "moose is definitely illegal";
    }
    if (!passports[2].loadFromFile("Data/Critter Crossing Customs/penguin passport.png"))
    {
        std::cout << "penguin might be illegal";
    }
    

    return true;

}

void Game::update(float dt)
{
    bird.move(1.0f * speed * dt, 0);

    if ((bird.getPosition().x > (window.getSize().x - bird.getGlobalBounds().width)) ||
        (bird.getPosition().x < 0))
    {
        reverse = !reverse;
    }
    if (reverse == true)
    {
        bird.move(-2.0f * speed * dt, 0);
        bird.setTextureRect(sf::IntRect(
            bird.getLocalBounds().width,
            0,
            -bird.getLocalBounds().width,
            bird.getLocalBounds().height));
    }
    else
    {
        bird.setTextureRect(sf::IntRect(
            0, 0, bird.getLocalBounds().width, bird.getLocalBounds().height));
    }
    score_text.setString("score: " + std::to_string(score));
}

void Game::render()
{
    if (in_menu == true)
    {
        window.draw(menu_text);
        window.draw(play_option);
        window.draw(quit_option);
    }
    else
    {
        window.draw(background);
        //window.draw(bird);
        //window.draw(title_text);
        window.draw(score_text);
        window.draw(*character);
        window.draw(*passport);
    }

}

void Game::mouseClicked(sf::Event event)
{

    //get the click position
    sf::Vector2i click = sf::Mouse::getPosition(window);
    // check if in bounds of bird Sprite
    if (collisionCheck(click, *passport))
    {
        if (true)
        {
            newAnimal();
            

        }

    }
}

void Game::keyPressed(sf::Event event)
{
    if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
    {
        play_selected = !play_selected;

        if (play_selected)
        {
            play_option.setFillColor(sf::Color(255, 255, 0, 255));
            quit_option.setFillColor(sf::Color(255, 255, 0, 125));
        }
        else
        {
            play_option.setFillColor(sf::Color(255, 255, 0, 125));
            quit_option.setFillColor(sf::Color(255, 255, 0, 255));
        }
    }
    else if (event.key.code == sf::Keyboard::Enter)
    {
        if (play_selected)
        {
            // Perform the action for Play
            in_menu = false;
            newAnimal();
        }
        else
        {
            // Perform the action for Quit
            window.close();
        }
    }
}




bool Game::collisionCheck(sf::Vector2i click, sf::Sprite sprite)
{
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    sf::Vector2f clickF(static_cast<float>(click.x), static_cast<float>(click.y));
    // if statement measures between two float values and sees if x and y (sprite box) detects a click within it
    if (clickF.x >= spriteBounds.left &&
        clickF.x <= spriteBounds.left + spriteBounds.width &&
        clickF.y >= spriteBounds.top &&
        clickF.y <= spriteBounds.top + spriteBounds.height)
    {
        std::cout << "Hit!" << std::endl;
        score++;
        return true;
    }
    else
    {
        return false;
    }
}

void Game::spawn()
{

    int xPos = rand() % (windowSize.x - static_cast<int>(bird.getLocalBounds().width));
    int yPos = rand() % (windowSize.y - static_cast<int>(bird.getLocalBounds().height));

    bird.setPosition(static_cast<float>(xPos), static_cast<float>(yPos));
}
void Game::newAnimal()
{
    int animal_index = rand() % 3;
    int passport_index = rand() % 3;

    if (animal_index == passport_index)
    {
        should_accept = true;
        std::cout << "Passed.\n";
        score++;
    }
    else
    {
        should_accept = false;
        std::cout << "Illegal!!\n";

    }

    character->setTexture(animals[animal_index], true);
    character->setScale(1.8, 1.8);
    character->setPosition(window.getSize().x / 20, window.getSize().y / 4);

    passport->setTexture(passports[passport_index]);
    passport->setScale(0.6, 0.6);
    passport->setPosition(window.getSize().x / 2, window.getSize().y / 3);
}
