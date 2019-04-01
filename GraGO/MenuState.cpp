#include "MenuState.h"

void MenuState::onStartGameClick()
{
	
	getStateManager()->pushState(make_unique<GameState>(getStateManager(), utilities));
}

void MenuState::onExitClick()
{
	getStateManager()->exitApplication();
}

void MenuState::onSettingsClick()
{
	getStateManager()->pushState(make_unique<SettingsState>(getStateManager(), utilities));
}

void MenuState::createGUI()
{
	//tworzenie interfejsu: - tlo
	GUI::GUIImage *img = new GUI::GUIImage(*utilities.textureManager.getResource(ResourceIDs::TextureID::menuBackground));
	img->setSize(utilities.renderWindow.getSize());
	GUI::GUIImage* img2 = new GUI::GUIImage(*utilities.textureManager.getResource(ResourceIDs::TextureID::menuList));
	GUI::GUIImage* blackStoneImage = new GUI::GUIImage(*utilities.textureManager.getResource(ResourceIDs::TextureID::blackStone));
	GUI::GUIImage* whiteStoneImage = new GUI::GUIImage(*utilities.textureManager.getResource(ResourceIDs::TextureID::whiteStone));
	//nazwa gru
	
	GUI::GUILabel *topLabel = new GUI::GUILabel(sf::Vector2f(0, 0), sf::Vector2f(0, 0), utilities.fontManager.getResource(ResourceIDs::FontID::mainFont), "Gra GO");
	//przyciski glownego menu
	GUI::GUIButton *startGameButton = new GUI::GUIButton(sf::Vector2f(0, 0), sf::Vector2f(0, 0), utilities.fontManager.getResource(ResourceIDs::FontID::mainFont)
		, "Rozpocznij gre",this);
	GUI::GUIButton *settingsButton = new GUI::GUIButton(sf::Vector2f(0, 0), sf::Vector2f(0, 0), utilities.fontManager.getResource(ResourceIDs::FontID::mainFont)
		, "Ustawienia", this);
	GUI::GUIButton *exitButton = new GUI::GUIButton(sf::Vector2f(0, 0), sf::Vector2f(0, 0), utilities.fontManager.getResource(ResourceIDs::FontID::mainFont)
		, "Wyjscie", this);

	GUI::GUIButton *connectButton = new GUI::GUIButton(sf::Vector2f(0, 0), sf::Vector2f(0, 0), utilities.fontManager.getResource(ResourceIDs::FontID::mainFont)
		, "Polacz", this);
	GUI::GUIButton *serverButton = new GUI::GUIButton(sf::Vector2f(0, 0), sf::Vector2f(0, 0), utilities.fontManager.getResource(ResourceIDs::FontID::mainFont)
		, "Stworz serwer", this);

	settingsButton->setBackgroundImage(*utilities.textureManager.getResource(ResourceIDs::TextureID::button));
	startGameButton->setBackgroundImage(*utilities.textureManager.getResource(ResourceIDs::TextureID::button));
	exitButton->setBackgroundImage(*utilities.textureManager.getResource(ResourceIDs::TextureID::button));
	connectButton->setBackgroundImage(*utilities.textureManager.getResource(ResourceIDs::TextureID::button));
	serverButton->setBackgroundImage(*utilities.textureManager.getResource(ResourceIDs::TextureID::button));

	//ustawianie reakcji na przyciski
	startGameButton->setCallback(std::bind(&MenuState::onStartGameClick, this));
	settingsButton->setCallback(std::bind(&MenuState::onSettingsClick, this));
	exitButton->setCallback(std::bind(&MenuState::onExitClick, this));
	connectButton->setCallback(std::bind(&MenuState::onConnectClick, this));
	serverButton->setCallback(std::bind(&MenuState::onHostClick, this));
	//formatowanie napisu
	topLabel->setBackgroundColor(sf::Color(0, 0, 0, 0));
	topLabel->setBorderThickness(10);
	topLabel->setTextColor(sf::Color::White);
	topLabel->setBorderColor(sf::Color::Transparent);
	topLabel->setTextSize(70);

	//dodawanie elementow na stos
	attachChildren(*img); //tlo - pelne wypelnienie domyslnie bez zmiany rozmiaru;
	attachChildren(*img2, 0.3, 0.26, 0.4, 0.7);
	attachChildren(*blackStoneImage, 0.05, 0.07, 0.20, (float)utilities.renderWindow.getSize().x/utilities.renderWindow.getSize().y*0.2);
	attachChildren(*whiteStoneImage, 0.75, 0.07, 0.20, (float)utilities.renderWindow.getSize().x / utilities.renderWindow.getSize().y*0.2);
	attachChildren(*topLabel, 0.20, 0.07, 0.60, 0.20);
	attachChildren(*startGameButton, 0.35, 0.3, 0.30, 0.10);
	attachChildren(*settingsButton, 0.35, 0.43, 0.30, 0.10);
	attachChildren(*connectButton, 0.35, 0.56, 0.30, 0.10);
	attachChildren(*serverButton, 0.35, 0.69, 0.30, 0.10);
	attachChildren(*exitButton, 0.35, 0.82, 0.30, 0.10);
}

void MenuState::onConnectClick()
{
	getStateManager()->pushState(make_unique<ConnectingState>(getStateManager(), utilities, false));

}

void MenuState::onHostClick()
{
	getStateManager()->pushState(make_unique<ConnectingState>(getStateManager(), utilities, true));

}

MenuState::MenuState(StateManager * state, const Utilities & utilities):BaseState(state, utilities),
GUIGroup(sf::Vector2f(0,0),sf::Vector2f(utilities.renderWindow.getSize().x, utilities.renderWindow.getSize().y),nullptr)
{
	
	createGUI();	
}

MenuState::~MenuState()
{
}

void MenuState::update(sf::Event & e, sf::RenderWindow & window)
{
	GUI::GUIGroup::update(e, window);
}

void MenuState::draw() const
{
	GUI::GUIGroup::draw(utilities.renderWindow, utilities.states);
}
