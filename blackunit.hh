
#ifndef BLACKUNIT_H
#define BLACKUNIT_H

#include "unit.hh"

class BlackUnit : public Unit {
	public:
		int value() const;
		std::string getSymbol() const;
		Unit* getCopy() const {return new BlackUnit();}
	private:
};



#endif

