#ifndef __CLASS5__H
#define __CLASS5__H

#include "Base.h"

// Подчинённый класс базового класса
class Class5: public Base {
	public:
		Class5(Base* parent, string name);
		~Class5();
};

#endif
