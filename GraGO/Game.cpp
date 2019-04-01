#include "Game.h"

void Game::changeGameState()
{
	switch (whoMoves) {
	case Moves::BLACK_MOVE:
		whoMoves = Moves::WHITE_MOVE;
		break;
	case Moves::WHITE_MOVE:
		whoMoves = Moves::BLACK_MOVE;
		break;
	
	}

}

void Game::endGame() 
{
	board.scoreBoard();
	whitePlayer.addPoints(komiValue);
	
		
	if (blackPlayer.getPoints() > whitePlayer.getPoints()) {
		
		winner = &blackPlayer;
	}
	else if(blackPlayer.getPoints() < whitePlayer.getPoints()){
		
		winner = &whitePlayer;
	}
	//else remis - nie rob nic
		callback(); //powiadamia obiekt agregujacy obiekt klasy Game o zaistnieniu konca gry
}





Game::Game(BoardSize size, float komiValue) :whoMoves(Moves::BLACK_MOVE), passedOnce(false),//regula - czarny zaczyna
blackPlayer(FieldColor::BLACK), whitePlayer(FieldColor::WHITE), board(size), winner(nullptr), komiValue(komiValue) {


};

Game::~Game()
{
}

BoardSize Game::getBoardSize() const
{
	 return board.getBoardSize(); 
}

Moves Game::getWhoMoves() const
{
	return whoMoves;
}






void Game::pass()
{
	//TODO:: pass przy braku pionow - error
	if (passedOnce) 
		endGame();

	changeGameState();
	passedOnce = true;
}

bool Game::putStone(unsigned x, unsigned y)
{
	if (!board.putStone(x, y, (FieldColor)whoMoves)) 
		return false;
	
	if (whoMoves == Moves::BLACK_MOVE) {
		
		blackPlayer.addPoints(board.getLastDeletedPositionsSize()); //ilosc zgarnietych kamieni 
	}
	else {
		
		whitePlayer.addPoints(board.getLastDeletedPositionsSize());
	}

		

		changeGameState();
		if (passedOnce)
			passedOnce = false;

		return true;
}

bool Game::passed() const
{
	return passedOnce;
}
const Field & Game::getAt(unsigned int x, unsigned int y)
{
	return *board.getFieldAtPosition(x, y);
}

const vector<std::pair<unsigned, unsigned>>* Game::getLastDeletedPositions() const
{
	return board.getLastDeletedPositions();
}

Player * Game::getPlayer(FieldColor color)
{
	return (color == FieldColor::BLACK ? &blackPlayer : &whitePlayer);
}

Player * Game::getWinner()
{
	return winner;
}

