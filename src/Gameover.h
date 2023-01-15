#pragma once

#include <SFML/Graphics.hpp>

class Gameover{
public:
	// deferencing pointers are used to access the non-copyable objects
	void printString(sf::RenderWindow *window, sf::Text *gameOverTxt, int Highscore){

		// Print "GAME OVER"
		gameOverTxt->setPosition(sf::Vector2f((float)window->getSize().x/2.5 - 70, (float)window->getSize().y/3.5));
		gameOverTxt->setScale(sf::Vector2f(2.3, 2.3));
		gameOverTxt->setOutlineColor(sf::Color(0, 71, 171)); // cobalt blue
		gameOverTxt->setString("GAME OVER");
		window->draw(*gameOverTxt);

		// Print "HIGHSCORE"
		gameOverTxt->setPosition(sf::Vector2f((float)window->getSize().x/2.5, (float)window->getSize().y/3.5 + 100));
		gameOverTxt->setScale(1.2, 1.2);
		gameOverTxt->setOutlineColor(sf::Color(154, 42, 42)); // cadmium red
		gameOverTxt->setString("HIGHSCORE: " + std::to_string(Highscore));
		window->draw(*gameOverTxt);

		// Print exiting msg
		gameOverTxt->setPosition(sf::Vector2f((float)window->getSize().x/2.5 - 70, (float)window->getSize().y/3.5 + 200));
		gameOverTxt->setScale(0.9, 0.9);
		gameOverTxt->setOutlineColor(sf::Color(46, 139, 87)); // lime green
		gameOverTxt->setString("Press ENTER to quit the game.");
		window->draw(*gameOverTxt);



		// writing highscore to the file
		std::ofstream writeFile;
		writeFile.open("assets/Highscore.txt");

		writeFile << Highscore;
		writeFile.close();

	}
};