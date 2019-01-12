#ifndef WHITEUNIT_H
#define WHITEUNIT_H

#include "unit.hh"

class WhiteUnit : public Unit {
	public:
		int value() const;
		std::string getSymbol() const;
		Unit* getCopy() const {return new WhiteUnit();}
	private:
};

#endif


