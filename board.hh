
#ifndef BOARD_H
#define BOARD_H


//#include "unit.hh"
#include "empty.hh"
#include "blackunit.hh"
#include "whiteunit.hh"
#include <vector>


class Board {
	public:
		enum{ columns = 8, rows = 8};
		Board();
		Board(Board& board);
		~Board();
		int getCount();
		int getBlackCount();
		int getWhiteCount();
		std::vector<std::pair<int,int> > getLegalMoves(const Unit& unit);
		bool makeMove(std::pair<int,int> placement,const Unit& unit);
		friend std::ostream& operator<<(std::ostream& os, const Board& obj);
	private:
		Unit* myBoard[rows][columns];
		int count;
		int blackcount;
		int whitecount;
		std::vector<std::pair<int,int> > legalMoves;
		

};


#endif


