
#ifndef WHACKAMOLESFML_GAME_H
#define WHACKAMOLESFML_GAME_H

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game(sf::RenderWindow& window);
	~Game();
	bool init();
	void update(float dt);
	void render();
	void mouseClicked(sf::Event event);
	void mouseButtonReleased(sf::Event event);
	void keyPressed(sf::Event event);
	void newAnimal();
	void dragSprite(sf::Sprite* sprite);


private:
	bool collisionCheck(sf::Vector2i click, sf::Sprite sprite);
	bool stampCollision(sf::Sprite* sprite);
	void stampPassport(sf::Event event);
	void spawn();
	
	sf::RenderWindow& window;

	sf::Sprite background;
	sf::Texture background_texture;
	sf::Sprite bird;
	sf::Texture bird_texture;
	sf::Sprite* character = new sf::Sprite;
	sf::Sprite* passport = new sf::Sprite;
	sf::Texture* animals = new sf::Texture[3];
	sf::Texture* passports = new sf::Texture[3];
	sf::Sprite* dragged = nullptr;
	sf::Sprite* accepted_stamp = new sf::Sprite;
	sf::Sprite* rejected_stamp = new sf::Sprite;
	sf::Sprite* accepted_button = new sf::Sprite;
	sf::Sprite* rejected_button = new sf::Sprite;
	sf::Texture* a_stamp_texture = new sf::Texture;
	sf::Texture* r_stamp_texture = new sf::Texture;
	sf::Texture* a_button_texture = new sf::Texture;
	sf::Texture* r_button_texture = new sf::Texture;

	sf::Font font;
	sf::Text title_text;
	sf::Clock clocku;



	sf::Text menu_text;
	sf::Text play_option;
	sf::Text quit_option;
	sf::Text score_text;

	bool in_menu;
	bool play_selected = true;
	bool reverse = false;
	bool passport_accepted = false;
	bool passport_rejected = false;
	bool should_accept = false;
	bool can_stamp = false;

	float speed = 200;
	//float* drag_offset = (dragged->getPosition().x, dragged->getPosition().y);

	sf::Vector2u windowSize = window.getSize();

	int score = 0;

};

#endif // WHACKAMOLESFML_GAME_H
