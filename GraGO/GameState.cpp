#include "GameState.h"

void GameState::endGame()
{
	getStateManager()->pushState(make_unique<GameOverState>(getStateManager(), utilities,game.getWinner(),true));
}

GameState::GameState(StateManager * manager,const Utilities& utilities):BaseState(manager, utilities), 
game(utilities.applicationSettings.getBoardSize(), utilities.applicationSettings.getKomi()? utilities.applicationSettings.komiValue : 0 ),
gameView(utilities,game,sf::Vector2f(0,0),sf::Vector2f(utilities.renderWindow.getSize().x, utilities.renderWindow.getSize().y),nullptr)
{
	game.setCallback(std::bind(&GameState::endGame, this));
	auto lamb = [this]() {
		getStateManager()->addTopToDelete();
	};
	gameView.exit->setCallback(lamb);
	
}


GameState::~GameState()
{
	
}


void GameState::update(sf::Event& e, sf::RenderWindow& window)
{
	if (e.type == sf::Event::KeyReleased && e.key.code==sf::Keyboard::P) {
		
		game.pass();
		gameView.refreshLabelsInfo();
		gameView.pass(game.getWhoMoves());
		
		e.key.code = sf::Keyboard::A;
		
	}
	
	gameView.update(e, window);
}

void GameState::draw() const
{
	gameView.draw(utilities.renderWindow,utilities.states);
	
}
