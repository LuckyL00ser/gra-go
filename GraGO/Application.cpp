#include "Application.h"



Application::Application():stateManager(std::bind(&Application::exitApplication,this))
{
	initialize();
}
void Application::setFullscreenMode() {

	window.create(sf::VideoMode(appSettings.getWindowSizeX(), appSettings.getWindowSizeY()),
		"Gra GO",
		appSettings.getFullscreen() ? sf::Style::Fullscreen : sf::Style::Default);
	window.setFramerateLimit(60);
	
}
Application::~Application()
{
	delete utilities;
}
void Application::exitApplication() {
	window.close();
	
}
void Application::initialize()
{
	appSettings.setCallback(std::bind(&Application::setFullscreenMode, this));
	window.create(sf::VideoMode(appSettings.getWindowSizeX(),appSettings.getWindowSizeY()),
								"Gra GO", appSettings.getFullscreen()?  sf::Style::Fullscreen : sf::Style::Close);
	
	window.setFramerateLimit(60);
	addResourcesPaths();
	utilities = new Utilities{
		window,
		sf::RenderStates::Default,
		textureManager,
		fontManager,
		appSettings
	};

	
	stateManager.pushState(make_unique<MenuState>(&stateManager, *utilities));
	
	
	

}

void Application::addResourcesPaths()
{
	textureManager.addPath("resources/menuBackground.png", ResourceIDs::TextureID::menuBackground);
	textureManager.addPath("resources/whiteStone.png", ResourceIDs::TextureID::whiteStone);
	textureManager.addPath("resources/blackStone.png", ResourceIDs::TextureID::blackStone);
	textureManager.addPath("resources/button.png", ResourceIDs::TextureID::button);
	textureManager.addPath("resources/background2.png", ResourceIDs::TextureID::menuList);
	textureManager.addPath("resources/whosTurn.png", ResourceIDs::TextureID::whosTurn);
	textureManager.addPath("resources/wait.png", ResourceIDs::TextureID::wait);
	fontManager.addPath("resources/bombard.ttf", ResourceIDs::FontID::mainFont);

}



void Application::processEvents()
{
	while (window.isOpen())
	{

		sf::Event event;
		
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				return;			
						
			}
			stateManager.update(event, window);
			
		}	
		event.type = sf::Event::Count;//neutralne zdarzenie nieobslugiwane przez zadna klase, pomaga odswiezyc wylacznie wizualny aspekt
		stateManager.update(event, window);
		render();
		
	}

}



void Application::render()
{	
	window.clear();
	stateManager.draw();
	
	window.display();
}
