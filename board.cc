#include <iostream>
#include "board.hh"
#include <algorithm>
#include <iterator>

#define updateUnit(old,unit) 
/* initilize board */
Board::Board(){
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      myBoard[i][j] = new Empty();
    }
  }

	delete myBoard[3][3];
	delete myBoard[4][4];
	delete myBoard[3][4];
	delete myBoard[4][3];

      	myBoard[3][3] = new WhiteUnit();
	myBoard[4][4] = new WhiteUnit();
	myBoard[3][4] = new BlackUnit();
	myBoard[4][3] = new BlackUnit();

        count = 4;
	blackcount = 2;
	whitecount = 2;
}
/* create a new board with the same state as the board in the argument*/
Board::Board(Board& board) {
	for (int i = 0; i < rows; i++) {
	  for (int j = 0; j < columns; j++)
			myBoard[i][j] = board.myBoard[i][j]->getCopy();
	}
	count = board.count;
	blackcount = board.blackcount;
	whitecount = board.whitecount;
}

Board::~Board() {
	for (int i = 0; i < rows; i++) {
	  for (int j = 0; j < columns; j++)
			delete myBoard[i][j];
	}
}
		
int Board::getCount(){
	return count;
}
		
int Board::getBlackCount(){
	return blackcount;
}
		
int Board::getWhiteCount(){
	return whitecount;
}
/* Get the legalmoves for the player with the specific unit(either whiteunit or blackunit)
return pairs with int that correspond to the locations of the board*/		
std::vector<std::pair<int,int> > Board::getLegalMoves(const Unit& unit){
	legalMoves.clear();	
	    for(int i=0;i<rows;i++){
	        for(int j=0;j<columns;j++){
	            if(*myBoard[i][j] == Empty()){
			if (j + 1 < columns && *myBoard[i][j+1] != Empty() && *myBoard[i][j+1] != unit) {
				for(int k=j+2;k<columns;k++){//right
		                        if(*myBoard[i][k] == unit) {
						legalMoves.push_back(std::pair<int,int>(i,j));
						goto foundLegal;
					}
		                        if(*myBoard[i][k] == Empty()) 
						break;
		                }					
			}
			if (j - 1 > -1 && *myBoard[i][j-1] != Empty() && *myBoard[i][j-1] != unit) {
				for(int k=j-2;k>-1;k--){//left
		                        if(*myBoard[i][k] == unit) {
						legalMoves.push_back(std::pair<int,int>(i,j));
						goto foundLegal;
					}
		                        if(*myBoard[i][k] == Empty()) 
						break;
		                }					
			}
			if (i - 1 > -1 && *myBoard[i-1][j] != Empty() && *myBoard[i-1][j] != unit) {
				for(int k=i-2;k>-1;k--){//up
		                        if(*myBoard[k][j] == unit) {
						legalMoves.push_back(std::pair<int,int>(i,j));
						goto foundLegal;
					}
		                        if(*myBoard[k][j] == Empty()) 
						break;
		                }					
			}
			if (i + 1 < rows && *myBoard[i+1][j] != Empty() && *myBoard[i+1][j] != unit) {
				for(int k=i+2;k<rows;k++){//down
		                        if(*myBoard[k][j] == unit) {
						legalMoves.push_back(std::pair<int,int>(i,j));
						goto foundLegal;
					}
		                        if(*myBoard[k][j] == Empty()) 
						break;
		                }					
			}
			if (i - 1 > -1 && j + 1 < columns && *myBoard[i-1][j+1] != Empty() && *myBoard[i-1][j+1] != unit) {
				for(int k = i - 2 , h = j + 2; k > -1 && h < columns; k--, h++){//up-right
		                        if(*myBoard[k][h] == unit) {
						legalMoves.push_back(std::pair<int,int>(i,j));
						goto foundLegal;
					}
		                        if(*myBoard[k][h] == Empty()) 
						break;
		                }					
			}
			if (i + 1 < rows && j + 1 < columns && *myBoard[i+1][j+1] != Empty() && *myBoard[i+1][j+1] != unit) {
				for(int k = i + 2 , h = j + 2; k < rows && h < columns; k++, h++){//down-right
		                        if(*myBoard[k][h] == unit) {
						legalMoves.push_back(std::pair<int,int>(i,j));
						goto foundLegal;
					}
		                        if(*myBoard[k][h] == Empty()) 
						break;
		                }					
			}
			if (i + 1 < rows && j - 1 > -1 && *myBoard[i+1][j-1] != Empty() && *myBoard[i+1][j-1] != unit) {
				for(int k = i + 2 , h = j - 2; k < rows && h > -1; k++, h--){//down-left
		                        if(*myBoard[k][h] == unit) {
						legalMoves.push_back(std::pair<int,int>(i,j));
						goto foundLegal;
					}
		                        if(*myBoard[k][h] == Empty()) 
						break;
		                }					
			}
			if (i - 1 > -1 && j - 1 > -1 && *myBoard[i-1][j-1] != Empty() && *myBoard[i-1][j-1] != unit) {
				for(int k = i - 2 , h = j - 2; k > -1 && h > -1; k--, h--){//up-left
		                        if(*myBoard[k][h] == unit) {
						legalMoves.push_back(std::pair<int,int>(i,j));
						goto foundLegal;
					}
		                        if(*myBoard[k][h] == Empty()) 
						break;
		                }					
			}
		    foundLegal: ;
	            }
	        }
	    }
	    return legalMoves;

    }
/* Make a move 
Change the state of the board */		
bool Board::makeMove(std::pair<int,int> placement,const Unit& unit){	
	getLegalMoves(unit);
	if (!legalMoves.empty()) {
		if (std::find(legalMoves.begin(), legalMoves.end(), placement) != legalMoves.end()) {
			delete myBoard[placement.first][placement.second];
			myBoard[placement.first][placement.second] = unit.getCopy();
			count++;
			unit.value() == 1 ? whitecount++ : blackcount++; 		
			for (int i = placement.first - 1; i >= 0; i--) {
				if (*myBoard[i][placement.second] == unit) {
					for (int j = i + 1; j < placement.first; j++) {//up
						delete myBoard[j][placement.second];
						myBoard[j][placement.second] = unit.getCopy();
						whitecount += unit.value();
						blackcount -= unit.value();	
					}
					break;	
				}
				else if (*myBoard[i][placement.second] == Empty()) {
					break;
				}
			}

			for (int i = placement.first + 1; i < rows; i++) {
				if (*myBoard[i][placement.second] == unit) {
					for (int j = i - 1; j > placement.first; j--) {//down
						delete myBoard[j][placement.second];
						myBoard[j][placement.second] = unit.getCopy();
						whitecount += unit.value();
						blackcount -= unit.value();
					}
					break;	
				}
				else if (*myBoard[i][placement.second] == Empty()) {
					break;
				}
			}

			for (int i = placement.second - 1; i >= 0; i--) {
				if (*myBoard[placement.first][i] == unit) {
					for (int j = i + 1; j < placement.second; j++) {//left
						delete myBoard[placement.first][j];
						myBoard[placement.first][j] = unit.getCopy();
						whitecount += unit.value();
						blackcount -= unit.value();	
					}
					break;	
				}
				else if (*myBoard[placement.first][i] == Empty()) {
					break;
				}
			}

			for (int i = placement.second + 1; i < columns; i++) {
				if (*myBoard[placement.first][i] == unit) {
					for (int j = i - 1; j > placement.second; j--) {//right
						delete myBoard[placement.first][j];
						myBoard[placement.first][j] = unit.getCopy();
						whitecount += unit.value();
						blackcount -= unit.value();	
					}	
					break;
				}
				else if (*myBoard[placement.first][i] == Empty()) {
					break;
				}
			}

			for (int i = placement.first - 1, j = placement.second - 1; i >= 0 && j >= 0; i--, j--) {
				if (*myBoard[i][j] == unit) {
					for (int k = i + 1, h = j + 1; k < placement.first && h < placement.second; k++, h++) {//up-left
						delete myBoard[k][h];
						myBoard[k][h] = unit.getCopy();
						whitecount += unit.value();
						blackcount -= unit.value();
					}
					break;	
				}
				else if (*myBoard[i][j] == Empty()) {
					break;
				}
			}

			for (int i = placement.first - 1, j = placement.second + 1; i >= 0 && j < columns; i--, j++) {
				if (*myBoard[i][j] == unit) {
					for (int k = i + 1, h = j - 1; k < placement.first && h > placement.second; k++, h--) {//up-right
						delete myBoard[k][h];
						myBoard[k][h] = unit.getCopy();
						whitecount += unit.value();
						blackcount -= unit.value();	
					}
					break;	
				}
				else if (*myBoard[i][j] == Empty()) {
					break;
				}
			}
		
			for (int i = placement.first + 1, j = placement.second + 1; i < rows && j < columns; i++, j++) {
				if (*myBoard[i][j] == unit) {
					for (int k = i - 1, h = j - 1; k > placement.first && h > placement.second; k--, h--) {//down-right
						delete myBoard[k][h];
						myBoard[k][h] = unit.getCopy();
						whitecount += unit.value();
						blackcount -= unit.value();
					}
					break;	
				}
				else if (*myBoard[i][j] == Empty()) {
					break;
				}
			}

			for (int i = placement.first + 1, j = placement.second - 1; i < rows && j >= 0; i++, j--) {
				if (*myBoard[i][j] == unit) {
					for (int k = i - 1, h = j + 1; k > placement.first && h < placement.second; k--, h++) {//down-left					
						delete myBoard[k][h];
						myBoard[k][h] = unit.getCopy();
						whitecount += unit.value();
						blackcount -= unit.value();

					}	
					break;
				}
				else if (*myBoard[i][j] == Empty()) {
					break;
				}
			}

			legalMoves.clear();
			return true;
		}
		else {
			std::cout << "This move is not legal!" << std::endl;
			return false;
		}
	}
	else {
		std::cout << "You do not got any legal move available!" << std::endl;
		legalMoves.clear();
		return true;	
	}
}

/*Print board*/		
std::ostream& operator<<(std::ostream& os, const Board& obj){
	os << "   ";
	for (char ch = 'A'; ch < 'I'; ch++) 
	  	os << " " << ch;     
  	os << std::endl << "   ------------------" << std::endl;
	for (int i = 0; i < obj.rows; i++) {
		os << " " << i << " |";
		for (int j = 0; j < obj.columns; j++) {
		  os << *obj.myBoard[i][j] << " "; 
		}
		os << "|" << std::endl;
	}
	os << "   ------------------" << std::endl;
	  return os;
}



