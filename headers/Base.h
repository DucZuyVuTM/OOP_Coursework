#ifndef __BASE__H
#define __BASE__H

#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

// Базовый класс всех объектов
class Base {
	private:
		string name;              // Наименование объекта
		Base* parent;             // Указатель на головной объект
		vector <Base*> children;  // Указатели на подчиненные объекты
		int status = 0;           // Статус объекта
	public:
		// --- Exercise 1 ---
		Base(Base* parent, string name = "Base object");
		~Base();

		bool set_name(string name);
		string get_name();

		int get_child_count();
		Base* get_child_by_name(string name);
		Base* get_child_by_index(int index);
		Base* get_parent();

		void display();
		// ------------------
	
		// --- Exercise 2 ---
		void display_tree(int depth = 0);
		void display_tree_with_status(int depth = 0);
		void set_status(int status);

		Base* find_unique(string name);
		Base* find_unique_from_root(string name);
		// ------------------
};

#endif
