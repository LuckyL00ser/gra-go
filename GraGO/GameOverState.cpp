#include "GameOverState.h"

void GameOverState::createGUI()
{
}

GameOverState::GameOverState(StateManager * stateManager, const Utilities& utilities,Player* winner, bool nGame) : BaseState(stateManager, utilities),
GUIGroup(sf::Vector2f(utilities.renderWindow.getSize().x / 4, utilities.renderWindow.getSize().y / 4), //pozycja
	sf::Vector2f(utilities.renderWindow.getSize().x/2, utilities.renderWindow.getSize().y/2),nullptr) //rozmiar - polowa okna w kazdym wymiarze
{
	if (nGame) {
		newGame = new GUI::GUIButton(sf::Vector2f(0, 0), sf::Vector2f(0, 0), utilities.fontManager.getResource(ResourceIDs::FontID::mainFont), "Nowa gra", this);
		newGame->setColorBackgroundNormal(sf::Color::Blue);
		newGame->setCallback(std::bind(&GameOverState::createNewGame, this));
		attachChildren(*newGame, 0.25, 0.6, 0.3, 0.15);
	}
	
	backToMenu= new GUI::GUIButton(sf::Vector2f(0, 0), sf::Vector2f(0, 0), utilities.fontManager.getResource(ResourceIDs::FontID::mainFont), "Menu", this);
	label = new GUI::GUILabel(sf::Vector2f(0, 0), sf::Vector2f(0, 0), utilities.fontManager.getResource(ResourceIDs::FontID::mainFont));
	label->setText("Koniec gry");
	points = new GUI::GUILabel(sf::Vector2f(0, 0), sf::Vector2f(0, 0), utilities.fontManager.getResource(ResourceIDs::FontID::mainFont));
	string text;
	if (winner == nullptr)
		text = "Remis!";
	else if (winner->getPlayerType() == FieldColor::BLACK)
		text = "Zwyciezyl czarny! ";
	else if (winner->getPlayerType() == FieldColor::WHITE)
		text = "Zwyciezyl bialy! ";
	points->setText(text);
	
	backToMenu->setColorBackgroundNormal(sf::Color::Blue);
	
	backToMenu->setCallback(std::bind(&GameOverState::goBackToMenu, this));

	attachChildren(*label, 0.3, 0.2, 0.4, 0.15);
	attachChildren(*points, 0.2, 0.4, 0.6, 0.15);
	if(nGame)
		attachChildren(*backToMenu, 0.6, 0.6, 0.3, 0.15);
	else
		attachChildren(*backToMenu, 0.25, 0.6, 0.5, 0.15);
	
}

GameOverState::~GameOverState()
{
}

void GameOverState::update(sf::Event & e, sf::RenderWindow & window)
{
	GUIGroup::update(e, window);

}

void GameOverState::draw() const
{
	GUIGroup::draw(utilities.renderWindow, utilities.states);
	
}

void GameOverState::createNewGame()
{
	
	getStateManager()->addTopToDelete();
	getStateManager()->addTopToDelete();
	getStateManager()->pushState(make_unique<GameState>(getStateManager(), utilities));
}

void GameOverState::goBackToMenu()
{
	getStateManager()->addTopToDelete();
	getStateManager()->addTopToDelete();
	
}
