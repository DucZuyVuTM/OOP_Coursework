#ifndef __APP__H
#define __APP__H

#include "Base.h"
#include "Class1.h"

class App: public Base {
	public:
		App(Base* parent);
		~App();

		void build_tree();
		int execute();
};

#endif
