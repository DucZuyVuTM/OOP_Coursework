#ifndef __CLASS6__H
#define __CLASS6__H

#include "Base.h"

// Подчинённый класс базового класса
class Class6: public Base {
	public:
		Class6(Base* parent, string name);
		~Class6();
};

#endif
