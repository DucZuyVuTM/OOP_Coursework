#include "App.h"

// Конструктор класса App
App::App(Base* parent): Base(parent) {}

// Метод создания дерева иерархии
void App::build_tree() {
	// --- Начальное построение ---

	// Настройка имени для текущего объекта
	string root_name;
	cin >> root_name;

	set_name(root_name);

	// Читаем комбинацию (родитель, потомок, номер класса),
	// пока не встретим "endtree"
	while (true) {
		string parent_name;
		cin >> parent_name;

		if (parent_name == "endtree") break;

		string child_name;
		int class_num = 0;

		cin >> child_name >> class_num;

		// Пропустить комбинацию,
		// если родитель не найден или дубликация имён его потомков 
		Base* parent = find_unique(parent_name);

		if (!parent || parent -> get_child_by_name(child_name))
			continue;

		// Создание потомка с номером класса
		switch (class_num) {
			case 2: new Class2(parent, child_name); break;
			case 3: new Class3(parent, child_name); break;
			case 4: new Class4(parent, child_name); break;
			case 5: new Class5(parent, child_name); break;
			case 6: new Class6(parent, child_name); break;
		}
	}
	// ----------------------------

	// --- Установка состояний объектов ---

	// Читаем комбинацию (имя объекта, новый статус объекта),
	// пока не встретим конец файла (EOF condition)
	string node_name;

	while (cin >> node_name) {
		int status = 0;
		cin >> status;

		// Настройка нового статуса, если объект найдён
		Base* found = find_unique(node_name);
		if (found)
			found -> set_status(status);
	}
	// ------------------------------------
}

// Метод запуска системы
int App::execute() {
	// Вывод дерева
	cout << "Object tree" << endl;
	display_tree();

	// Вывод дерева со статусами
	cout << endl << "The tree of objects and their readiness" << endl;
	display_tree_with_status();

	return(0);
}

// Деструктор класса App
App::~App() {}
