#include "../headers/Base.h"

Base::Base(Base* parent, string name) {
	this -> name   = name;
	this -> parent = parent;

	if (parent) parent -> children.push_back(this);
}

bool Base::set_name(string name) {
	if (parent)
		for (auto sibling : parent -> children)
			if (sibling -> get_name() == name)
				return false;

	this -> name = name;
	return true;
}

string Base::get_name() {
	return name;
}

Base* Base::get_child_by_name(string name) {
	for (auto child : children)
		if (child -> get_name() == name)
			return child;

	return nullptr;
}

Base* Base::get_child_by_index(int index) {
	if (index < children.size()) {
		return children[index];
	}

	return nullptr;
}

Base* Base::get_parent() {
	return parent;
}

void Base::display() {
	if (children.empty() && parent) return;

	cout << endl << get_name();

	for (auto child : children)
		cout << "  " << child -> get_name();

	if (!children.empty())
		children.back() -> display();
}

Base::~Base() {
	for (auto child : children) delete child;
}
