#include "../headers/Base.h"

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
	if (index < children.size()) {
		return children[index];
	}

	return nullptr;
}

// Получение указателя на родительский объект текущего объекта
Base* Base::get_parent() {
	return parent;
}

// вывод имён объектов и их иерархии на экран
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

// Денструктор класса Base
Base::~Base() {
	// Вызов деструктора подчинённых объектов
	for (auto child : children) delete child;
}
