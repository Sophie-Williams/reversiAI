#include <iostream>
#include "board.hh"
#include "reversiai.hh"
//#include "board.cc"
//#include "unit.hh"
//#include "empty.hh"
//#include "blackunit.hh"
//#include "whiteunit.hh"
//#include "empty.cc"
//#include "blackunit.cc"
//#include "whiteunit.cc"
#include <stdlib.h> 

std::pair<int, int> convertToIntPair(std::string);

void printSuggestions(std::vector< std::pair<int,int> >); 

void printScores(int,int);

int main(int argc, char** argv) {

	std::cout << "Chose a time in ms: " << std::endl;	
	int time;
	std::cin >> time;

	Board board;
	ReversiAI ai(&board, time);

 	std::cout << board << std::endl;

	
	while (board.getCount() < 64 && !(board.getLegalMoves(WhiteUnit()).empty() && board.getLegalMoves(BlackUnit()).empty())) {
		std::string input;
		std::cout << "Your turn! " << "Chose a square (in the notation 7D, 0a...)" << std::endl;
		printSuggestions(board.getLegalMoves(BlackUnit()));	
		std::cin >> input;	
		if (input.length() > 1) {
			std::pair<int,int> pair = convertToIntPair(input);
			if (board.makeMove(pair, BlackUnit())) {
				std::cout << board << std::endl;
				printScores(board.getBlackCount(),board.getWhiteCount());
				std::cout << "Computers turn!" << std::endl;
				ai.decide();
				std::cout << board << std::endl;
				printScores(board.getBlackCount(),board.getWhiteCount());		
			}	
		}
		else {
			std::cout << "Too small string" << std::endl;	
		}
	}
	std::cout << "You got the score: " << board.getBlackCount() << std::endl;
	std::cout << "The AI got the score: " << board.getWhiteCount() << std::endl;

	if (board.getBlackCount() > board.getWhiteCount()) {
		std::cout << "Congratulations! You won!" << std::endl;	
	}
	else {
		std::cout << "You lost!!" << std::endl;	
	}
 
};

/* Utility functions */
std::pair<int, int> convertToIntPair(std::string str) {
	int a = str.at(0) - '0';
	int b = toupper(str.at(1)) - 'A';
	return std::pair<int, int>(a, b);
}

void printSuggestions(std::vector< std::pair<int,int> > suggestions) {
	std::cout << "Suggested moves: ";
	for (int i = 0; i < suggestions.size(); i++){
		std::cout << suggestions[i].first << (char) (suggestions[i].second + 'A') << ", ";
	}
        std::cout << std::endl;
}

void printScores(int black,int white) {
	std::cout << "You have: " << black << " and AI have: " << white << std::endl;
}



