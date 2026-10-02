#include "Base.h"

// --------------------------- <Exercise1> ---------------------------

// Конструктор класса Base
Base::Base(Base* parent, string name) {
	this -> name   = name;
	this -> parent = parent;

	// Если у узла есть родитель,
	// регистрируем себя в его списке потомков
	if (parent) parent -> children.push_back(this);
}

// Установка имена текущего объекта
bool Base::set_name(string name) {
	// Проверяем, нет ли среди "братьев" узла с таким же именем 
	if (parent)
		for (auto sibling : parent -> children)
			if (sibling -> name == name)
				return false;

	this -> name = name;
	return true;
}

// Получение имена текущего объекта
string Base::get_name() {
	return name;
}

// Получение количества подчинённых объектов текущего объекта
int Base::get_child_count() {
	return children.size();
}

// Получение указателя на подчинённый объект текущего объекта по имени
Base* Base::get_child_by_name(string name) {
	// Пройти по дочерним объектам и проверить их имена
	for (auto child : children)
		if (child -> name == name)
			return child;

	return nullptr;
}

// Получение указателя на подчинённый объект текущего объекта по индексу
Base* Base::get_child_by_index(int index) {
	// Проверяем, валидный ли индекс
	if (index < children.size())
		return children[index];

	return nullptr;
}

// Получение указателя на родительский объект текущего объекта
Base* Base::get_parent() {
	return parent;
}

// Вывод имён объектов и их иерархии на экран
void Base::display() {
	// Проверяем, это конечный объект или нет
	if (children.empty() && parent) return;

	cout << endl << name;

	// Вывод имён подчинённых объектов
	for (auto child : children)
		cout << "  " << child -> name;

	// Вызов самого метода в последнем объекте
	if (!children.empty())
		children.back() -> display();
}

// Деструктор класса Base
Base::~Base() {
	// Вызов деструктора подчинённых объектов
	for (auto child : children) delete child;
}
// --------------------------- </Exercise1> ---------------------------


// --------------------------- <Exercise2> ---------------------------

// Метод вывода дерева иерархии
void Base::display_tree(int depth) {
	// Если корневой объект, не переходить на новую строку
	if (depth) cout << endl;

	// Вывод табуляции и имени объекта
	cout << string(depth * 4, ' ') << name;

	// Вывод имён подчинённых объектов
	for (auto child : children)
		child -> display_tree(depth + 1);
}

// Метод вывода дерева иерархии с их готовностью
void Base::display_tree_with_status(int depth) {
	// Если корневой объект, не переходить на новую строку
	if (depth) cout << endl;

	// Вывод табуляции и имени объекта
	cout << string(depth * 4, ' ') << name;

	// Вывод статуса объекта
	if (status)
		cout << " is ready";
	else
		cout << " is not ready";

	// Вывод имён подчинённых объектов
	for (auto child : children)
		child -> display_tree_with_status(depth + 1);
}

// Метод установки статуса объекта
void Base::set_status(int status) {
	if (status) {
		// Нужно проверить все вышестоящие элементы:
		// Включены ли они?
		for (
			Base* current = parent;
			current;
			current = current -> parent
		)
			if (!current -> status) return;
	}
	else
		// Обойти все подчинённые элементы и выключить их
		for (auto child : children)
			child -> set_status(status);

	this -> status = status;
}

// Метод поиска объекта по имени в поддереве
Base* Base::find_unique(string name) {
	Base* found = nullptr;

	// Создание очереди для итерактивного поиска
	queue <Base*> pending;
	pending.push(this);

	// Проверяем каждый элемент очереди
	while (!pending.empty()) {
		Base* current = pending.front();
		pending.pop();

		// Если найдённый объект не уникальный, возврат nullptr
		if (current -> name == name) {
			if (found) return nullptr;
			
			found = current;
		}

		// Добавление подчинённых в очередь
		for (auto child : current -> children)
			pending.push(child);
	}

	return found;
}

// Метод поиска объекта по имени во всём дереве
Base* Base::find_unique_from_root(string name) {
	// Поиск корневого объекта
	Base* root = this;

	while (root -> parent)
		root = root -> parent;

	// Поиск объекта из корневого
	return root -> find_unique(name);
}
// --------------------------- </Exercise2> ---------------------------
