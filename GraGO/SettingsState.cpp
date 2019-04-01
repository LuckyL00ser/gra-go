#include "SettingsState.h"



void SettingsState::createGUI()
{
	GUI::GUIImage *img = new GUI::GUIImage(*utilities.textureManager.getResource(ResourceIDs::TextureID::menuBackground));
	img->setSize(utilities.renderWindow.getSize());
	//GUI::GUIImage* img2 = new GUI::GUIImage(*utilities.textureManager.getResource(ResourceIDs::TextureID::menuList));
	attachChildren(*img);
	//attachChildren(*img2, 0.1, 0.1, 0.8, 0.8);

	createLabels();

	createTickboxes();
	createBoardSizeButtons();
	createResolutionButtons();

	tf = new GUI::GUITextField();
	tf->setFont(*utilities.fontManager.getResource(ResourceIDs::FontID::mainFont));
	tf->setText(utilities.applicationSettings.getIp());


	GUI::GUIButton * exit = new GUI::GUIButton();
	exit->setFont(*utilities.fontManager.getResource(ResourceIDs::FontID::mainFont));
	exit->setParent(this);
	exit->setText("Menu");
	exit->setCallback(std::bind(&SettingsState::exitToMenu, this));
	attachChildren(*tf, 0.3, 0.85, 0.35, 0.1);
	attachChildren(*exit, 0.8, 0.8, 0.12, 0.1);
	
	
	
}

void SettingsState::createLabels()
{
	GUI::GUILabel* boardSizeLabel = new GUI::GUILabel();
	GUI::GUILabel* windowResolution = new GUI::GUILabel();
	GUI::GUILabel* fullscreen = new GUI::GUILabel();
	GUI::GUILabel* komiRule = new GUI::GUILabel();
	GUI::GUILabel* ip = new GUI::GUILabel();
	GUI::GUILabel* newIp = new GUI::GUILabel();
	boardSizeLabel->setText("Rozmiar planszy: ");
	windowResolution->setText("Rozdzielczosc: ");
	fullscreen->setText("Pelny ekran: ");
	komiRule->setText("Regula komi: ");
	ip->setText("Twoje ip: " + sf::IpAddress::getLocalAddress().toString());
	newIp->setText("IP serwera: ");
	boardSizeLabel->setFont(*utilities.fontManager.getResource(ResourceIDs::FontID::mainFont));
	windowResolution->setFont(*utilities.fontManager.getResource(ResourceIDs::FontID::mainFont));
	fullscreen->setFont(*utilities.fontManager.getResource(ResourceIDs::FontID::mainFont));
	komiRule->setFont(*utilities.fontManager.getResource(ResourceIDs::FontID::mainFont));
	ip->setFont(*utilities.fontManager.getResource(ResourceIDs::FontID::mainFont));
	newIp->setFont(*utilities.fontManager.getResource(ResourceIDs::FontID::mainFont));

	attachChildren(*boardSizeLabel, 0.06, 0.1, 0.2, 0.1);
	attachChildren(*windowResolution, 0.06, 0.25, 0.2, 0.1);
	attachChildren(*fullscreen, 0.06, 0.4, 0.2, 0.1);
	attachChildren(*komiRule, 0.06, 0.55, 0.2, 0.1);
	attachChildren(*ip, 0.06, 0.7, 0.35, 0.1);
	attachChildren(*newIp, 0.06, 0.85, 0.2, 0.1);
}

void SettingsState::createTickboxes()
{
	GUI::GUITickbox * fullscreenTickbox = new GUI::GUITickbox();
	GUI::GUITickbox * komiRuleTickbox = new GUI::GUITickbox();
	fullscreenTickbox->setCallback(std::bind(&SettingsState::setFullscreen, this));
	komiRuleTickbox->setCallback(std::bind(&SettingsState::setKomi, this));
	fullscreenTickbox->setFont(*utilities.fontManager.getResource(ResourceIDs::FontID::mainFont));
	komiRuleTickbox->setFont(*utilities.fontManager.getResource(ResourceIDs::FontID::mainFont));
	fullscreenTickbox->setParent(this);
	komiRuleTickbox->setParent(this);
	fullscreenTickbox->setColorBackgroundNormal(sf::Color::Transparent);
	komiRuleTickbox->setColorBackgroundNormal(sf::Color::Transparent);
	fullscreenTickbox->setCheckedFillColor(sf::Color::Yellow);
	komiRuleTickbox->setCheckedFillColor(sf::Color::Yellow);
	fullscreenTickbox->setChecked(utilities.applicationSettings.getFullscreen());
	komiRuleTickbox->setChecked(utilities.applicationSettings.getKomi());
	
	attachChildren(*fullscreenTickbox, 0.72, 0.4, 0.1, 0.1);
	attachChildren(*komiRuleTickbox, 0.72, 0.55, 0.1, 0.1);
}

void SettingsState::createResolutionButtons()
{
	GUI::GUIButton * res0, *res1, *res2, *res3, *res4;

	res0 = new GUI::GUIButton();
	res0->setFont(*utilities.fontManager.getResource(ResourceIDs::FontID::mainFont));
	res0->setText("800x600");
	res0->setParent(this);
	auto r0 = [this]() {setResolution(WindowResoultion::RES_800x600); }; //wyrazenie lambda
	res0->setCallback(r0);

	res1 = new GUI::GUIButton();
	res1->setFont(*utilities.fontManager.getResource(ResourceIDs::FontID::mainFont));
	res1->setText("1024x756");
	res1->setParent(this);
	auto r1 = [this]() {setResolution(WindowResoultion::RES_1024x756); }; //wyrazenie lambda
	res1->setCallback(r1);

	res2 = new GUI::GUIButton();
	res2->setFont(*utilities.fontManager.getResource(ResourceIDs::FontID::mainFont));
	res2->setText("1280x720");
	res2->setParent(this);
	auto r2 = [this]() {setResolution(WindowResoultion::RES_1280x720); }; //wyrazenie lambda
	res2->setCallback(r2);

	res3 = new GUI::GUIButton();
	res3->setFont(*utilities.fontManager.getResource(ResourceIDs::FontID::mainFont));
	res3->setText("1600x900");
	res3->setParent(this);
	auto r3 = [this]() {setResolution(WindowResoultion::RES_1600x900); }; //wyrazenie lambda
	res3->setCallback(r3);

	res4 = new GUI::GUIButton();
	res4->setFont(*utilities.fontManager.getResource(ResourceIDs::FontID::mainFont));
	res4->setText("1920x1080");
	res4->setParent(this);
	auto r4 = [this]() {setResolution(WindowResoultion::RES_1920x1080); }; //wyrazenie lambda
	res4->setCallback(r4);

	attachChildren(*res0, 0.27, 0.25, 0.11, 0.1);
	attachChildren(*res1, 0.4, 0.25, 0.11, 0.1);
	attachChildren(*res2, 0.53, 0.25, 0.11, 0.1);
	attachChildren(*res3, 0.66, 0.25, 0.11, 0.1);
	attachChildren(*res4, 0.79, 0.25, 0.11, 0.1);
}

void SettingsState::createBoardSizeButtons()
{
	GUI::GUIButton* bs5x5, *bs9x9, *bs11x11, *bs13x13, *bs19x19;
	bs5x5 = new GUI::GUIButton();
	bs5x5->setFont(*utilities.fontManager.getResource(ResourceIDs::FontID::mainFont));
	bs5x5->setText("5x5");
	bs5x5->setParent(this);
	auto x5 = [this]() {setBoardSize(BoardSize::SIZE_5x5); }; //wyrazenie lambda
	bs5x5->setCallback(x5);

	bs9x9 = new GUI::GUIButton();
	bs9x9->setFont(*utilities.fontManager.getResource(ResourceIDs::FontID::mainFont));
	bs9x9->setText("9x9");
	bs9x9->setParent(this);
	auto x9 = [this]() {setBoardSize(BoardSize::SIZE_9x9); }; //wyrazenie lambda
	bs9x9->setCallback(x9);

	bs11x11 = new GUI::GUIButton();
	bs11x11->setFont(*utilities.fontManager.getResource(ResourceIDs::FontID::mainFont));
	bs11x11->setText("11x11");
	bs11x11->setParent(this);
	auto x11 = [this]() {setBoardSize(BoardSize::SIZE_11x11); }; //wyrazenie lambda
	bs11x11->setCallback(x11);

	bs13x13 = new GUI::GUIButton();
	bs13x13->setFont(*utilities.fontManager.getResource(ResourceIDs::FontID::mainFont));
	bs13x13->setText("13x13");
	bs13x13->setParent(this);
	auto x13 = [this]() {setBoardSize(BoardSize::SIZE_13x13); }; //wyrazenie lambda
	bs13x13->setCallback(x13);

	bs19x19 = new GUI::GUIButton();
	bs19x19->setFont(*utilities.fontManager.getResource(ResourceIDs::FontID::mainFont));
	bs19x19->setText("19x19");
	bs19x19->setParent(this);
	auto x19 = [this]() {setBoardSize(BoardSize::SIZE_19x19); }; //wyrazenie lambda
	bs19x19->setCallback(x19);

	attachChildren(*bs5x5, 0.27, 0.1, 0.11, 0.1);
	attachChildren(*bs9x9, 0.4, 0.1, 0.11, 0.1);
	attachChildren(*bs11x11, 0.53, 0.1, 0.11, 0.1);
	attachChildren(*bs13x13, 0.66, 0.1, 0.11, 0.1);
	attachChildren(*bs19x19, 0.79, 0.1, 0.11, 0.1);

}

void SettingsState::setFullscreen()
{
	utilities.applicationSettings.setFullscreen(!utilities.applicationSettings.getFullscreen());
			
}

void SettingsState::setKomi()
{
	utilities.applicationSettings.setKomi(!utilities.applicationSettings.getKomi());
	

}

void SettingsState::setIP()
{
	utilities.applicationSettings.setIP(tf->getText());
}

void SettingsState::setResolution(WindowResoultion newSize)
{
	utilities.applicationSettings.setResolution(newSize);
	getStateManager()->addTopToDelete();
	getStateManager()->addTopToDelete();

	utilities.renderWindow.setSize(sf::Vector2u(utilities.applicationSettings.getWindowSizeX(), utilities.applicationSettings.getWindowSizeY()));
	utilities.renderWindow.setView(*(new sf::View(sf::Vector2f(utilities.applicationSettings.getWindowSizeX() / 2, utilities.applicationSettings.getWindowSizeY() / 2),
		sf::Vector2f(utilities.applicationSettings.getWindowSizeX(), utilities.applicationSettings.getWindowSizeY()))));


	getStateManager()->pushState(make_unique<MenuState>(getStateManager(), utilities));
	getStateManager()->pushState(make_unique<SettingsState>(getStateManager(), utilities)); //wymusza ponowne wyrysowanie z nowymi rozmiarami
}

void SettingsState::setBoardSize(BoardSize newSize)
{
	utilities.applicationSettings.setBoardSize(newSize);
}

void SettingsState::exitToMenu()
{
	utilities.applicationSettings.saveSettingsToFile();
	getStateManager()->popState();
}

SettingsState::SettingsState(StateManager* state, const  Utilities& utilities) :BaseState(state, utilities),
GUIGroup(sf::Vector2f(0, 0), sf::Vector2f(utilities.renderWindow.getSize().x, utilities.renderWindow.getSize().y), nullptr)
{
	
	createGUI();
}

SettingsState::~SettingsState()
{
	setIP();
}

void SettingsState::update(sf::Event & e, sf::RenderWindow & window)
{
	GUI::GUIGroup::update(e, window);
}

void SettingsState::draw() const
{
	GUI::GUIGroup::draw(utilities.renderWindow, utilities.states);
}
