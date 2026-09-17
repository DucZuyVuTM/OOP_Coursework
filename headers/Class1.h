#ifndef __CLASS1__H
#define __CLASS1__H

#include "Base.h"

class Class1: public Base {
	public:
		Class1(Base* parent, string name);
		~Class1();
};

#endif
