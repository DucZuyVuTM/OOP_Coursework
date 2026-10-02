#ifndef __CLASS4__H
#define __CLASS4__H

#include "Base.h"

// Подчинённый класс базового класса
class Class4: public Base {
	public:
		Class4(Base* parent, string name);
		~Class4();
};

#endif
