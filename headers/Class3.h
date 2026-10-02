#ifndef __CLASS3__H
#define __CLASS3__H

#include "Base.h"

// Подчинённый класс базового класса
class Class3: public Base {
	public:
		Class3(Base* parent, string name);
		~Class3();
};

#endif
