#include "../headers/App.h"

App::App(Base* parent): Base(parent) {}

void App::build_tree() {
	// Initial build
	string parent_name, child_name;
	Base *parent = this, *child = nullptr;

	cin >> parent_name;
	set_name(parent_name);

	while (true) {
		cin >> parent_name >> child_name;

		if (parent_name == child_name) break;

		if (child != nullptr && parent_name == child -> get_name())
			parent = child;

		if (parent -> get_child_by_name(child_name) == nullptr
			&& parent_name == parent -> get_name())
			child = new Class1(parent, child_name);
	}

	execute();
	cout << endl;

	// Change name
	int level, total_level = 1, step, index;
	string name;

	Base* current = child;

	while (current != this) {
		current = current -> get_parent();
		total_level += 1;
	}

	while (true) {
		current = child;

		cin >> level;
		if (level == 0) break;
		cin >> index >> name;
		if (level > total_level) continue;

		if (level == 1) {
			if (index == 1) set_name(name);
			continue;
		}

		if (!current && level != 1) continue;

		step = total_level - level + 1;

		while (step) {
			current = current -> get_parent();
			step -= 1;
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
