
#ifndef EMPTY_H
#define EMPTY_H

#include "unit.hh"

class Empty: public Unit {
	public:
		int value() const;
		std::string getSymbol() const;
		Unit* getCopy() const {return new Empty();}
	private:
};

#endif

