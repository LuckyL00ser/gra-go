#include "GameGUIView.h"



void GameGUIView::setSizeDerivered()
{

}

void GameGUIView::createBoardGUI()
{
	//tlo
	GUI::GUIImage *img = new GUI::GUIImage(*utilities.textureManager.getResource(ResourceIDs::TextureID::menuBackground));
	img->setSize(getSize());
	attachChildren(*img);
	
	//opisy graczy
	GUI::GUILabel * whitePlayerLabel = new GUI::GUILabel(sf::Vector2f(), sf::Vector2f(),
		utilities.fontManager.getResource(ResourceIDs::FontID::mainFont), "Bialy");
	GUI::GUILabel * blackPlayerLabel = new GUI::GUILabel(sf::Vector2f(), sf::Vector2f(),
		utilities.fontManager.getResource(ResourceIDs::FontID::mainFont), "Czarny");
	
	

	///tabele punktow 	
	whitePoints = new GUI::GUILabel(sf::Vector2f(), sf::Vector2f(),
		utilities.fontManager.getResource(ResourceIDs::FontID::mainFont), "Zdobyte punkty: ");
	blackPoints = new GUI::GUILabel(sf::Vector2f(), sf::Vector2f(),
		utilities.fontManager.getResource(ResourceIDs::FontID::mainFont), "Zdobyte punkty: ");

	whitePoints->setTextSize(20);
	blackPoints->setTextSize(20);

	//stan gry
	gameStateInfo = new GUI::GUILabel(sf::Vector2f(), sf::Vector2f(),
		utilities.fontManager.getResource(ResourceIDs::FontID::mainFont), "Gre rozpoczyna czarny");
	//linie
	
	float boardScaleFactor = 0.8;
	unsigned boardSize = game->getBoardSize();
	float gameBoardSizePixels = getSize().y*boardScaleFactor; //wysokosc jest zawsze mniejszym wymiarem 

	//potrzebne do stworzenia planszy o rownym rozmiarze
	//linie planszy
	float linesSpacing = gameBoardSizePixels / (boardSize); //y zawsze krotszy - dopasoanie

	float margin = (getSize().y*(1-boardScaleFactor)) / 2;

	GUIGroup* helperGroup = new GUIGroup(sf::Vector2f(margin, margin), sf::Vector2f(getSize().y*0.8, getSize().y*0.8), this);

	for (unsigned i = 0; i < game->getBoardSize(); i++) {

		GUI::GUILine* lineVertical = new GUI::GUILine(sf::Vector2f(i*linesSpacing, 0)); //linie pionowe
		GUI::GUILine* lineHorizontal = new GUI::GUILine(sf::Vector2f(0, i*linesSpacing)); //linie poziome

		lineVertical->setStartVertexPosition(sf::Vector2f(0, 0));
		lineVertical->setEndVertexPosition(sf::Vector2f(0, gameBoardSizePixels - linesSpacing));

		lineHorizontal->setStartVertexPosition(sf::Vector2f(0, 0));
		lineHorizontal->setEndVertexPosition(sf::Vector2f(gameBoardSizePixels - linesSpacing, 0));

		helperGroup->attachChildren(*lineVertical);
		helperGroup->attachChildren(*lineHorizontal);

	}
	//przyciski
	
	float buttonSpacingFactor = boardSize;
	float buttonSizeFactor = 0.9;
	
	for (unsigned i = 0; i < boardSize; i++) {
		for (unsigned j = 0; j < boardSize; j++) {
			GUI::GUIButton *button = new GUI::GUIButton(sf::Vector2f());
			button->setOrigin(sf::Vector2f(buttonSizeFactor*linesSpacing / 2, buttonSizeFactor*linesSpacing / 2));
			button->setColorBackgroundNormal(sf::Color::Transparent);
			button->setBorderColor(sf::Color::Transparent);
			button->setColorBackgroundClicked(sf::Color(128,128,128,128));
			button->setParent(helperGroup);

			auto x = [this, i, j]() {putStone(i, j); }; //wyrazenie lambda
			button->setCallback(x);

			helperGroup->attachChildren(*button, i / buttonSpacingFactor, j / buttonSpacingFactor,
				buttonSizeFactor / buttonSpacingFactor, buttonSizeFactor / buttonSpacingFactor); //przyciski pol nie "stykaja sie" - zabieg wizualny
			interactiveElements[i][j] = button;
		
			
		}
	}
	whosTurn = new GUI::GUIImage(*utilities.textureManager.getResource(ResourceIDs::TextureID::whosTurn));
	exit = new GUI::GUIButton(sf::Vector2f(0, 0), sf::Vector2f(0, 0), utilities.fontManager.getResource(ResourceIDs::mainFont),
		"Wyjscie", this);
	
	
	attachChildren(*helperGroup);
	attachChildren(*blackPlayerLabel, 0.75, 0.2, 0.15, 0.1);
	attachChildren(*blackPoints, 0.65, 0.45, 0.25, 0.05);

	attachChildren(*whitePlayerLabel, 0.75, 0.55, 0.15, 0.1);
	attachChildren(*whitePoints, 0.65, 0.8, 0.25, 0.05);
	attachChildren(*gameStateInfo, 0.35, 0.9, 0.3, 0.08);
	attachChildren(*whosTurn, 0.7, 0.2, 0.05, 0.07);
	attachChildren(*exit, 0.85, 0.9, 0.1, 0.08);
	refreshLabelsInfo();
	gameStateInfo->setText("Rozpoczyna czarny");
	lastPutStone = nullptr;
}



GameGUIView::GameGUIView(const Utilities& utilities, const Game& gameRef,sf::Vector2f position, sf::Vector2f size , GUIElement* parent):
	game(const_cast<Game*>(&gameRef)),
	GUIGroup(position,size,nullptr) , utilities(utilities)
{
	setWhiteStoneTexture(utilities.textureManager.getResource(ResourceIDs::TextureID::whiteStone));
	setBlackStoneTexture(utilities.textureManager.getResource(ResourceIDs::TextureID::blackStone));
		
	unsigned boardSize = game->getBoardSize();
	interactiveElements = new GUI::GUIButton**[boardSize];
	for (unsigned i = 0; i < boardSize; i++) {
		interactiveElements[i] = new GUI::GUIButton*[boardSize];
		for (unsigned j = 0; j < boardSize; j++) {
			interactiveElements[i][j] = nullptr;
		}
	}
	
	createBoardGUI();
	
}


GameGUIView::~GameGUIView()
{
	//obiekty tablicy interactiveElements sa zwalniane przez destruktor klasy GUIGroup
}

void GameGUIView::setWhiteStoneTexture(sf::Texture * tex)
{
	whiteStoneTexture = tex;
}

void GameGUIView::setBlackStoneTexture(sf::Texture * tex)
{
	blackStoneTexture = tex;
}


bool GameGUIView::putStone(unsigned x, unsigned y)
{
	if (game->putStone(x, y)) {

		if(lastPutStone)
			lastPutStone->setBorderColor(sf::Color::Transparent);

		lastPutStone = interactiveElements[x][y];
		lastPutStone->setBorderColor(sf::Color::Red);

		
		lastPutStone->setColorBackgroundNormal(sf::Color::White);
		lastPutStone->setActive(false); //ustaw brak reakcji na zdarzenia myszy
		
		
		//ustawia teksture koloru ruchu przeciwnika bo putStone zmienia kolor po wykonaniu prawidlowego ruchu
		lastPutStone->setBackgroundImage(game->getWhoMoves() == (Moves)FieldColor::BLACK ? *whiteStoneTexture : *blackStoneTexture);
		
	
		for (auto& x : *game->getLastDeletedPositions()) { //iteracja po wszystkich pionach ktore maja zostac usuniete z planszy
			takeOutStone(x.first,x.second);
		}
		refreshLabelsInfo();
		return true;
	}
	gameStateInfo->setText("Niepoprawny ruch");
	return false;
}

void GameGUIView::pass(Moves who)
{
	if (who == Moves::BLACK_MOVE)
		gameStateInfo->setText("Bialy pasuje");
	else
		gameStateInfo->setText("Czarny pasuje");
		
}

void GameGUIView::lockAllButtons()
{
	for (unsigned i = 0; i < game->getBoardSize(); i++) {

		for (unsigned j = 0; j < game->getBoardSize(); j++) {
			interactiveElements[i][j]->setActive(false);
		}
	}
}

void GameGUIView::unlockAllButtons()
{
	for (unsigned i = 0; i < game->getBoardSize(); i++) {
		
		for (unsigned j = 0; j < game->getBoardSize(); j++) {
			if(game->getAt(i,j).getColor() == FieldColor::EMPTY)
				interactiveElements[i][j]->setActive(true);
		}
	}
}

void GameGUIView::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	GUIGroup::draw(target, states);
}

void GameGUIView::update(sf::Event & e, sf::RenderWindow & window)
{
	GUIGroup::update(e, window);
}
void GameGUIView::takeOutStone(unsigned x, unsigned y)
{
	interactiveElements[x][y]->setActive(true);
	interactiveElements[x][y]->setColorBackgroundNormal(sf::Color::Transparent);
	interactiveElements[x][y]->setBackgroundImage(sf::Texture());
}
void GameGUIView::refreshLabelsInfo()
{

	blackPoints->setText("Punkty: " + std::to_string(game->getPlayer(FieldColor::BLACK)->getPoints()));

	whitePoints->setText("Punkty: " + std::to_string(game->getPlayer(FieldColor::WHITE)->getPoints()));

	switch (game->getWhoMoves()) {
		case Moves::BLACK_MOVE:
				gameStateInfo->setText("Ruch czarnego");
				whosTurn->setPosition(getSize().x*0.7, getSize().y*0.2);
			break;
		case Moves::WHITE_MOVE:
				gameStateInfo->setText("Ruch bialego");
				whosTurn->setPosition(getSize().x*0.7, getSize().y*0.55);
			break;
	}
}

void GameGUIView::setMainLabelContent(sf::String content)
{
	gameStateInfo->setText(content);
}
