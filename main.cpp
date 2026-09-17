#include "headers/App.h"

int main()
{
	// program here
	App app(nullptr);
	app.build_tree();
	return(app.execute());
}
