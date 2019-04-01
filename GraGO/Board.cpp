#include "Board.h"



void Board::takeOutStone(unsigned x, unsigned y)
{
	
	board[x][y]->setColor(FieldColor::EMPTY);
	
}

Board::Board(BoardSize size) :boardSize(size) 
{
	

	board = new Field**[boardSize];
	for (int i = 0; i < boardSize; i++) {
		board[i] = new Field*[boardSize];
		for (unsigned j = 0; j < boardSize; ++j) {
			board[i][j] = new Field(i,j);

		}
	}

	
}


Board::~Board()
{
	
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++)
			delete board[i][j];
		delete[] board[i];
	}
	delete[] board;
}

Field* Board::getStoneAtPosition(unsigned column, unsigned row) const
{
	if (!areRowAndColumnCorrect(column, row))
		throw out_of_range("column or row out of range");
	else
		return board[column][row];
				
}

Field * Board::getFieldAtPosition(unsigned column, unsigned row) const
{
	if (!areRowAndColumnCorrect(column, row))
		throw out_of_range("column or row out of range");

	return board[column][row];
}



bool Board::isMoveCorrect(unsigned column, unsigned row,FieldColor color) const
{
	try {
		if (getStoneAtPosition(column, row)->getColor()!=FieldColor::EMPTY)
			return false; //pole juz zajete
	}
	catch (out_of_range e) {
		return false; //podana kolumna lub wiersz sa zbyt duze
	}
	
	return true;

}

bool Board::areRowAndColumnCorrect(unsigned column, unsigned row) const
{
	if (row >= boardSize || column >= boardSize)
		return false;
	return true;
}

pair<vector<Field*>*, vector<Field*>*> Board::getReachedAndChain(unsigned column,unsigned row) const
{	
	//funkcja analizuje plansze dla kazdego rodzaju pol - puste, biale lub czarne
	//wspolrzedne column i row okreslaja pole wzgledem ktorego ma zostac przeprowadzona analiza
	pair<vector<Field*>*, vector<Field*>*> toReturn(nullptr, nullptr);
	Field* startField;
	try {
		startField = getFieldAtPosition(column, row);
	}
	catch (out_of_range e) {
		return toReturn;
	}
	vector<Field*>* reached = new vector<Field*>; //pola wokol lancucha 
	vector<Field*>* chain = new vector<Field*>; //lancuch pol lub kamieni jednego koloru
	//chain->push_back(startField);
	stack<Field*> current; //stos do przechowywania potencjalnych sasiadow

	current.push(startField); //rzutowanie "w dol"
	
	while (!current.empty()) { //algorytm typu flood-fill do znajdywania lancucha pol jednakowego rodzaju oraz ich "otoczenia" = chain i reached
		
		Field* currentField = current.top();
		current.pop();
		if(std::find(chain->begin(), chain->end(), currentField) == chain->end())
			chain->push_back(currentField);
		
		vector<Field*> *neighbors = getNeighbors(currentField);
		for (auto& neighbor : *neighbors) {
			
			if (startField->getColor() == neighbor->getColor()  && std::find(chain->begin(), chain->end(), neighbor)==chain->end()) {
				//taki sam kolor pionow && analizowany pion nie zostal jeszcze dodany do lancucha
				current.push(neighbor);
			}
			else if (neighbor->getColor() != startField->getColor() &&std::find(reached->begin(), reached->end(), neighbor) == reached->end()) //&& not present
				reached->push_back(neighbor);
		}
		delete neighbors;
	}

	toReturn.first = reached;
	toReturn.second = chain;
	return toReturn; //po zwroceniu koniecznie zwolnic *reached i *chain
}

vector<Field*>* Board::getNeighbors(unsigned column, unsigned row) const
{
	vector<Field*>* neighbors= new vector<Field*>;
	const int moves[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };
	Field* field;
	for (int i = 0; i < 4; i++) {
		
		try { 
			field = getFieldAtPosition(column + moves[i][0], row + moves[i][1]); //funkcja zwraca pole
		}
		catch (out_of_range e) {
			continue;
		}
		neighbors->push_back(field);
		
	}
	return neighbors;

}

vector<Field*>* Board::getNeighbors(Field * field) const
{
	return getNeighbors(field->getPositionX(),field->getPositionY());
}



BoardSize Board::getBoardSize() const
{
	return boardSize;
}

unsigned Board::scoreBoard()
{
	//liczenie punktow zgodnie z zasadami Chinskimi
	//1 punkt to 1 przeciece linii nalezace do obszaru otocznego jedynie kamieniami jednego koloru - kamieniami danego gracza
	unsigned blackTerritority = 0; //terytorium nalezace do gracza czarnego
	unsigned whiteTerritority = 0; //rozmiar terytorium gracza bialego
	for (unsigned i = 0; i < boardSize; i++) {
		for (unsigned j = 0; j < boardSize; ++j) { //iteracja po calej planszy
			if (board[i][j]->getColor() == FieldColor::EMPTY) {
				//jesli pole niezbadane
				pair<vector<Field*>*, vector<Field*>*> pair = getReachedAndChain(i, j); //pobierz granice i sam obszar pustego pola
				const FieldColor reachBeginning = (*pair.first)[0]->getColor(); //"kolor" pierwszego elementu granicznego
				bool assignPointsForPlayer = true;
				for (auto& reach : (*pair.first)) { //sprawdz czy wszystkie elementy graniczne sa tego samego koloru
					if (reach->getColor() != reachBeginning) { //dwa rozne kolory "granic" obszaru, obszar niczyi
						assignPointsForPlayer = false;
						break;
					}
				}
				unsigned points = 0;
				for (auto& gainedField : (*pair.second)) { //iteracja po pustym obszarze
					gainedField->setColor(FieldColor::TERRITORITY_CHECKED); //oznacz obszar sprawdzony
					points++;
				}
				
				if (assignPointsForPlayer) {
					if (reachBeginning == FieldColor::BLACK)
						blackTerritority += points;
					else
						whiteTerritority += points;
				}
				delete pair.first;
				delete pair.second;
				//debugDraw2();
			}
			else if (board[i][j]->getColor() == FieldColor::BLACK)
				blackTerritority++;
			else if (board[i][j]->getColor() == FieldColor::WHITE)
				whiteTerritority++;
		}
	}
	
	return blackTerritority-whiteTerritority; //zwraca roznice obliczonych punktow terytorium
}

bool Board::putStone(unsigned column, unsigned row,FieldColor color) 
{
	if (isMoveCorrect(column, row, color)) {

		
		board[column][row]->setColor(color);
		vector<Field*> *neighbors = getNeighbors(column, row);

		vector<Field*> currentPlayerStones, opponentPlayerStones;
		currentPlayerStones.push_back(board[column][row]);

		for (auto& neighbor : *neighbors) {
			if (neighbor->getColor() == color)
				currentPlayerStones.push_back(neighbor);
			else if(neighbor->getColor() != color && neighbor->getColor()!=FieldColor::EMPTY)
				opponentPlayerStones.push_back(neighbor);

		}
		
		lastDeletedPositions.clear();
		
		
		//kolejnosc oponent - ja
		for (auto& opponentStone : opponentPlayerStones) {
			tryCaptureStones(opponentStone);
		}
		for (auto& stones : currentPlayerStones) { //Legalnosc ruchu?
			if (tryCaptureStones(stones)) {
				//ruch niepoprawny
				//przywroc usuniete pozycje
				for (auto& item : lastDeletedPositions) {
					board[item.first][item.second]->setColor(color);
				}
				board[column][row]->setColor(FieldColor::EMPTY);//cofa ostatni ruch
				lastDeletedPositions.clear();
				return false;
			}
		}
				
		return true;
	}
	return false;
}

const vector<std::pair<unsigned, unsigned>>* Board::getLastDeletedPositions() const
{
	return &lastDeletedPositions;
}

unsigned Board::getLastDeletedPositionsSize() const
{
	return lastDeletedPositions.size();
}





bool Board::tryCaptureStones(Field * stone)
{	
	//zwraca prawde w przypadku gdy lancuch ktory tworzy dany kamien zostaje usuniety tj. nie ma "wolnego oddechu"
	if (stone == nullptr)
		return false;

	vector<Field*>* reached, *chain;
	
	pair< vector<Field*>*, vector<Field*>*> pair = getReachedAndChain(stone->getPositionX(),stone->getPositionY());
	reached = pair.first;
	chain = pair.second;


	for (auto& item : *reached) {
		if (item->getColor() == FieldColor::EMPTY) {
			return false; //istnieje puste pole ktore styka sie z lancuchem ktorego elementem jest stone (z parametru) zatem lancuch moze istniec
			//istnieje tzw "wolny oddech dla przynajmniej jedngo z kamieni w lancuchu
		}
	}
	
	//brak "wolnego oddechu" (pustego pola) dla jakiegokolwiek elementu lancucha - kamienie znikaja, pojawiaja sie puste pola
	
	for (auto& item : *chain) {
		unsigned x, y;
		x = item->getPositionX();
		y = item->getPositionY();
		
		vector<std::pair<unsigned, unsigned>> vc;
		lastDeletedPositions.push_back(std::pair<unsigned, unsigned>(x, y));
		takeOutStone(item->getPositionX(), item->getPositionY());
	}
	
	
	delete reached;
	delete chain;
	return true;
}
