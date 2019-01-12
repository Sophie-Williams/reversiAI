
#ifndef REVERSAI_H
#define REVERSIAI_H


//#include "unit.hh"
#include <ctime>
#include "board.hh"
#include "empty.hh"
#include "blackunit.hh"
#include "whiteunit.hh"
#include <vector>

/* constant for when a timeout occur*/
#define TIMEOUT std::pair<int,int>(-1,-1)

class ReversiAI {
	public:
		ReversiAI(Board* board,int thoughtTime) : theBoard(board), allowedTime(thoughtTime) {}
		int evalFunction(Board& board);
		std::pair<int, int> miniMax(int depth);
		void decide();
		void randomDecision();
	private:
		Board* theBoard;
		int allowedTime;
		std::clock_t startTime;
		static const int timeOutFlag = -100;
		bool isTimedOut();
		int getMax(Board& board,int depth,int min);
		int getMin(Board& board,int depth,int max);

};


#endif
