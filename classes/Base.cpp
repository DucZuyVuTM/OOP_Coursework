#include "../headers/Base.h"

Base::Base(Base* parent, string name) {
	this -> name   = name;
	this -> parent = parent;

	if (parent) parent -> children.push_back(this);
}

bool Base::set_name(string name) {
	if (parent)
		for (int i = 0; i < parent -> children.size(); i++)
			if (parent -> children[i] -> get_name() == name)
				return false;

	this -> name = name;
	return true;
}

string Base::get_name() {
	return name;
}

Base* Base::get_child_by_name(string name) {
	for (int i = 0; i < children.size(); i++)
		if (children[i] -> get_name() == name)
			return children[i];

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
	int size = children.size();

	if (size != 0 || !parent) {
		cout << endl << get_name();

		for (int i = 0; i < size; i++) {
			cout << "  " << children[i] -> get_name();

			if (i == size - 1) children[i] -> display();
		}
	}
}

Base::~Base() {
	for (int i = 0; i < children.size(); i++)
		delete children[i];
}
