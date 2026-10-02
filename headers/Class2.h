#ifndef __CLASS2__H
#define __CLASS2__H

#include "Base.h"

// Подчинённый класс базового класса
class Class2: public Base {
	public:
		Class2(Base* parent, string name);
		~Class2();
};

#endif
