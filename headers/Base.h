#ifndef __BASE__H
#define __BASE__H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Base {
	private:
		string name;
		Base* parent;
		vector <Base*> children;
	public:
		Base(Base* parent, string name = "Base object");
		~Base();

		bool set_name(string name);
		string get_name();
		Base* get_child_by_name(string name);
		Base* get_child_by_index(int index);
		Base* get_parent();
		void display();
};

#endif
