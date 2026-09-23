#include "../headers/App.h"

// Конструктор класса App
App::App(Base* parent): Base(parent) {}

// Построение иерархии объектов внутри приложения
void App::build_tree() {
	// --- Начальное построение ---
	string parent_name;
	Base *parent = this,   // Обход объекта начинается с самого app
		*child = nullptr;  // Последний созданный листовой узел

	// Настроение имени для текущего объекта
	cin >> parent_name;
	set_name(parent_name);

	// Читаем пары (родитель, потомок),
	// пока не встретим пару с одинаковыми именами
	while (true) {
		string child_name;
		cin >> parent_name >> child_name;

		if (parent_name == child_name) break;

		// Если только что созданный узел совпал с именем родителя,
		// спускаемся на уровень ниже
		if (child && parent_name == child -> get_name())
			parent = child;

		// Создаём нового потомка,
		// если его ещё нет и имя родителя совпадает
		if (!parent -> get_child_by_name(child_name)
			&& parent_name == parent -> get_name())
			child = new Class1(parent, child_name);
	}
	// ---

	// Вывод начального дерева
	execute();
	cout << endl;

	// --- Изменение имён объектов ---

	// Вычисление количества уровней дерева
	int depth = 1;
	for (Base* p = child; p && p != this; p = p -> get_parent())
		++depth;

	// Читаем запросы на переименование: level index new_name
	// Остановить, если level = 0
	while (true) {
		int level = 0, index = 0;
		string name;  // Новое имя

		cin >> level;
		if (level == 0) break;
		cin >> index >> name;

		if (level > depth) continue;  // Слишком глубокий доступ

		// Level 1 - это сам app
		if (level == 1) {
			if (index == 1) set_name(name);
			continue;
		}

		// Если имеется только 1 уровень, читать следующий запрос
		if (!child) continue;

		// От листового узла поднимаемся вверх до узла на уровне "level"
		Base* current = child;
		int step = depth - level + 1;
		while (step) {
			current = current -> get_parent();
			--step;
		}

		// Берём потомка по индексу (нумерация с 1)
		current = current -> get_child_by_index(index - 1);

		if (current) current -> set_name(name);
	}
	// ---
}

// Запуск приложения
int App::execute() {
	cout << get_name();  // Вывод имени корневого узла
	display();           // Отображение всего поддерева
	return(0);
}

// Деструктор класса App
App::~App() {}
