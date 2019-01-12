#ifndef UNIT_H
#define UNIT_H

#include <iostream>

class Unit {
	public:
  virtual int value() const {return 4;}
  virtual std::string getSymbol() const {return "Unit";}
  virtual Unit* getCopy() const {return new Unit();}
  bool operator==(const Unit& rhs) {return this->value()==rhs.value();}
  bool operator!=(const Unit& rhs) {return this->value()!=rhs.value();}
  friend std::ostream& operator<<(std::ostream& os, const Unit& obj) {return os << obj.getSymbol();}
};

#endif

