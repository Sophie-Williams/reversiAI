
#include "reversiai.hh"

/* Decide a move and make it*/
void ReversiAI::decide() {
	startTime = std::clock();
	int i = 1;
	std::pair<int,int> decision;
	while (!isTimedOut() && i < 65 - theBoard->getCount()) {
		std::pair<int,int> pair = miniMax(i++);
		if (pair != TIMEOUT)
			decision = pair;

	}
	std::cout << "AI chose: " << decision.first << (char) (decision.second + 'A') << ", depth " << i << ", time " << (std::clock() - startTime)/ (double) CLOCKS_PER_SEC << std::endl;
	
	theBoard->makeMove(decision, WhiteUnit());
}

/*Simple evalFunction used by the Minimax algorithm*/
int ReversiAI::evalFunction(Board& board) {
	return board.getWhiteCount()-board.getBlackCount();
}

/* Get the move that get the best score with the Minimax algorithm*/
std::pair<int,int> ReversiAI::miniMax(int depth) {
	std::pair<int, int> decision;
	int max = -65;
	std::vector< std::pair<int,int> > v = theBoard->getLegalMoves(WhiteUnit());
	for (int i = 0; i < v.size(); i++) {
		Board newBoard(*theBoard);
		newBoard.makeMove(v[i], WhiteUnit());
		int value = getMin(newBoard, depth - 1, max);
		//out of time
		if (value == timeOutFlag) {
			return TIMEOUT;//std::pair<int,int>(-1,-1);
		} 
		if (value > max) {
			max = value;
			decision = v[i];
		}
	}
	//std::cout << "Maxvalue: " << max << std::endl;
	// if max == -1 no legal moveas are available
	return max != -65 ? decision : std::pair<int,int>(0,0);
}

/* Get max in the Minimax algorithm*/
int ReversiAI::getMax(Board& board,int depth,int min) {
	if (depth < 1 || board.getCount() == 64){
		return evalFunction(board);
	}
	int max = -65;
	std::vector< std::pair<int,int> > v = board.getLegalMoves(WhiteUnit());
	for (int i = 0; i < v.size(); i++) {
		Board newBoard(board);
		newBoard.makeMove(v[i], WhiteUnit());
		int value = getMin(newBoard, depth - 1, max);
		if (isTimedOut())
 			return timeOutFlag;
		max = (value > max) ? value : max;
		if (max > min) //alpha-pruning
			break;
	}
		 
	return max != -65 ? max : getMin(board, depth - 1, max);

}

/* Get min in the Minimax algorithm*/
int ReversiAI::getMin(Board& board,int depth,int max) {
	if (depth < 1 || board.getCount() == 64){
		return evalFunction(board);
	}
	int min = 65;
	std::vector< std::pair<int,int> > v = board.getLegalMoves(BlackUnit());
	for (int i = 0; i < v.size(); i++) {
		Board newBoard(board);
		newBoard.makeMove(v[i], BlackUnit());
		int value = getMax(newBoard, depth - 1, min);
		if (isTimedOut())
 			return timeOutFlag;
		min = (value < min) ? value : min;
		if (min < max) //alpha-pruning
			break;
	}

	return min != 65 ? min : getMax(board, depth - 1, min);
}
/*check if the AI is out of time*/
bool ReversiAI::isTimedOut() {
	return allowedTime < 1000*(std::clock() - startTime)/ (double) CLOCKS_PER_SEC; 
}

/*An AI that just make random decision*/
void ReversiAI::randomDecision() {	

	if (!theBoard->getLegalMoves(WhiteUnit()).empty())
		theBoard->makeMove(theBoard->getLegalMoves(WhiteUnit())[0], WhiteUnit());
	else //when no moves are available
		theBoard->makeMove(std::pair<int,int>(0,0), WhiteUnit());
}


