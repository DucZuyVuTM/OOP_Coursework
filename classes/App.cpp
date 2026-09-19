#include "../headers/App.h"

App::App(Base* parent): Base(parent) {}

void App::build_tree() {
	// Initial build
	string parent_name;
	Base *parent = this, *child = nullptr;

	cin >> parent_name;
	set_name(parent_name);

	while (true) {
		string child_name;
		cin >> parent_name >> child_name;

		if (parent_name == child_name) break;

		if (child && parent_name == child -> get_name())
			parent = child;

		if (!parent -> get_child_by_name(child_name)
			&& parent_name == parent -> get_name())
			child = new Class1(parent, child_name);
	}

	execute();
	cout << endl;

	// Change name
	int depth = 1;

	for (Base* p = child; p && p != this; p = p -> get_parent())
		++depth;

	while (true) {
		int level = 0, index = 0;
		string name;

		cin >> level;
		if (level == 0) break;
		cin >> index >> name;

		if (level > depth) continue;

		if (level == 1) {
			if (index == 1) set_name(name);
			continue;
		}

		if (!child) continue;

		Base* current = child;
		int step = depth - level + 1;

		while (step) {
			current = current -> get_parent();
			--step;
		}

		current = current -> get_child_by_index(index - 1);

		if (current) current -> set_name(name);
	}
}

int App::execute() {
	cout << get_name();
	display();
	return(0);
}

App::~App() {}
