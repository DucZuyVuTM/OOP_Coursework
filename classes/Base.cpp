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


// --------------------------- <Exercise3> ---------------------------

// Метод поиска объекта по пути во всём дереве
Base* Base::find_by_path(string path) {
	if (path.empty()) return nullptr;

	// Поиск корневого объекта ("/")
	Base* root = this;

	while (root -> parent)
		root = root -> parent;

	// Обработка базового пути
	if (path == "/") return root;
	if (path == ".") return this;

	// Имя следующего объекта
	string node_name;

	// Обработка пути вида "//object_3"
	if (path[0] == '/' && path[1] == '/') {
		node_name = path.substr(2);

		return find_unique_from_root(node_name);
	}

	// Обработка пути вида ".object_3"
	if (path[0] == '.') {
		node_name = path.substr(1);

		return find_unique(node_name);
	}

	int slash_index = path.find("/", 1);     // Поиск слеша с индекса 1
	bool is_final_node = slash_index == -1;  // Является ли текущий последним в пути

	Base* next = nullptr;                    // Следующий объект

	// Обработка пути вида "/object_3..."
	if (path[0] == '/') {
		node_name = is_final_node
			? path.substr(1)                    // "/object_3"
			: path.substr(1, slash_index - 1);  // "/object_3/object_5..."

		next = root -> get_child_by_name(node_name);		
	}
	// Обработка пути вида "object_3..."
	else {
		node_name = is_final_node
			? path                          // "object_3"
			: path.substr(0, slash_index);  // "object_3/object_5..."

		next = get_child_by_name(node_name);
	}

	// Условие прекращения рекурсии:
	// объект является последним
	// или следующий объект не найдён
	if (is_final_node || !next) return next;

	// Поиск объекта в поддереве по пути с помощью рекурсии
	string next_path = path.substr(slash_index + 1);

	return next -> find_by_path(next_path);
}

// Метод переопределения родительского объекта для текущего
bool Base::move_to(Base* new_parent) {
	// --- Проверка возможности работы метода ---

	// Если уже является родительским
	if (parent == new_parent) return true;

	// Переопределение головного объекта для корневого объекта недопустимо.
	// Недопустимо создать второй корневой объект.
	if (!parent || !new_parent) return false;

	// Недопустимо при переопределении, чтобы у нового головного
	// появились два подчиненных объекта с одинаковым наименованием.
	if (new_parent -> get_child_by_name(name))
		return false;

	// Новый головной объект не должен принадлежать к объектам из ветки текущего.
	Base* current = new_parent;

	while (current) {
		if (current == this) return false;

		current = current -> parent;
	}
	// ------------------------------------------

	// Ссылки на подчинённые старого и нового родительских
	vector <Base*> & old_siblings = parent -> children;
	vector <Base*> & new_siblings = new_parent -> children;

	// Поиск текущего в old_siblings и его удаление на векторе этой ссылки
	auto it = find(old_siblings.begin(), old_siblings.end(), this);
	old_siblings.erase(it);

	// Изменение свойства parent и добавление текущего в new_siblings
	parent = new_parent;
	new_siblings.push_back(this);

	return true;
}

// Метод удаления подчинённого объекта по имени
void Base::delete_child(string name) {
	// Получение подчинённого по имени
	Base* child = get_child_by_name(name);

	// Если подчинённый найдён
	if (child) {
		// Поиск подчинённого в children и его удаление на этом векторе
		auto it = find(children.begin(), children.end(), child);
		children.erase(it);

		// Главное удаление подчинённого - вызов деструктора подчинённого
		delete child;
	}
}
// --------------------------- </Exercise3> ---------------------------
