#ifndef __APP__H
#define __APP__H

#include "Base.h"
#include "Class2.h"
#include "Class3.h"
#include "Class4.h"
#include "Class5.h"
#include "Class6.h"

// Класс для запуска приложения
class App: public Base {
	public:
		App(Base* parent);
		~App();

		void build_tree();
		int execute();
};

#endif
