#include "Settings.h"



Settings::Settings() :fullscreen(false), boardSize(BoardSize::SIZE_13x13), komi(false) {
	setResolution(RES_1280x720);
	loadSettingsFromFile();

}
Settings::~Settings() {
	saveSettingsToFile();
}

void Settings::setResolution(WindowResoultion resolution)
{
	this->resolution = resolution;
	
	switch (resolution) {
	case RES_800x600:
		windowSizeX = 800;
		windowSizeY = 600;
		break;
	case RES_1024x756:
		windowSizeX = 1024;
		windowSizeY = 756;
		break;
	case RES_1280x720:
		windowSizeX = 1280;
		windowSizeY = 720;
		break;
	case RES_1600x900:
		windowSizeX = 1600;
		windowSizeY = 900;
		break;
	case RES_1920x1080:
		windowSizeX = 1920;
		windowSizeY = 1080;
		break;
	default:
		break;
	}
}

WindowResoultion Settings::getResolution() const
{
	return resolution;
}

unsigned Settings::getWindowSizeX() const
{
	return windowSizeX;
}

unsigned Settings::getWindowSizeY() const
{
	return windowSizeY;
}

bool Settings::getFullscreen() const
{
	return fullscreen;
}

void Settings::setFullscreen(bool useFullscreen)
{

	fullscreen = useFullscreen;	
	callback();
}

BoardSize Settings::getBoardSize() const
{
	return boardSize;
}

void Settings::setBoardSize(BoardSize bSize)
{
	if(bSize == BoardSize::SIZE_5x5 || bSize == BoardSize::SIZE_9x9 
		|| bSize== BoardSize::SIZE_11x11 || bSize == BoardSize::SIZE_13x13 || bSize == BoardSize::SIZE_19x19)
		boardSize = bSize;
}

bool Settings::getKomi() const
{
	return komi;
}

void Settings::setKomi(bool k)
{
	
	komi = k;
}

void Settings::setIP(std::string newIp)
{
	ip = newIp;
}

const std::string & Settings::getIp() const
{
	return ip;
}



void Settings::loadSettingsFromFile()
{
	std::fstream file;
	file.open(settingsFilePath, std::ios::in);

	if (file.good()) {
		int size, resolution;
		file >> size;
		file >> resolution;
		std::string fullscreen, komi;
		
		file >> fullscreen;
		file >> komi;
		file >> ip;
		setBoardSize((static_cast<BoardSize>(size)));
		setResolution(static_cast<WindowResoultion>(resolution));
		if (fullscreen == "tak")
			this->fullscreen = (true); //else - domyslne wartosci
	
		if (komi == "tak")
			setKomi(true);
		


	}
	file.close();
}

void Settings::saveSettingsToFile()
{
	std::fstream file(settingsFilePath, std::ios::out | std::ios::in);
	file.seekg(std::ios::beg);
	if (file.good()) {
		file << boardSize << "\n";
		file << static_cast<int>(resolution) << "\n";
		file << (fullscreen ? "tak" : "nie") << "\n";
		file << (komi ? "tak" : "nie") << "\n";
		file <<  ip << "\n";

	}	
	file.close();
	
}

