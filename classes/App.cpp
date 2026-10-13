#include "App.h"

// Конструктор класса App
App::App(Base* parent): Base(parent) {}

// Метод создания дерева иерархии
void App::build_tree() {
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

		// Завершить программу или пропустить комбинацию,
		// если родитель не найден или дубликация имён его потомков 
		Base* parent = find_by_path(parent_name);

		if (!parent) {
			cout << "Object tree" << endl;
			display_tree();

			cout << endl << "The head object " << parent_name << " is not found";
			exit(1);
		}

		if (parent -> get_child_by_name(child_name)) {
			cout << parent_name << "     Dubbing the names of subordinate objects" << endl;
			continue;
		}

		// Создание потомка с номером класса
		switch (class_num) {
			case 2: new Class2(parent, child_name); break;
			case 3: new Class3(parent, child_name); break;
			case 4: new Class4(parent, child_name); break;
			case 5: new Class5(parent, child_name); break;
			case 6: new Class6(parent, child_name); break;
		}
	}
}

// Метод запуска системы
int App::execute() {
	// Вывод дерева
	cout << "Object tree" << endl;
	display_tree();
	cout << endl;

	// --- Обработка команд ---

	// Настройка текущего объекта
	Base* current = this;

	// Читаем комбинацию (команда, путь),
	// пока не встретим "END"
	while (true) {
		string command;
		cin >> command;

		if (command == "END") break;

		string path;
		cin >> path;

		// Поиск объекта по пути
		Base* found = current -> find_by_path(path);

		// Обработка команды SET
		if (command == "SET") {
			// Если объект найдён
			if (found) {
				// Найдённый станет текущим
				current = found;

				cout << "Object is set: " << current -> get_name();
			}
			else
				cout << "The object was not found at the specified coordinate: " << path;
		}

		// Обработка команды FIND
		if (command == "FIND") {
			cout << path << "     ";

			// Если объект найдён
			if (found)
				cout << "Object name: " << found -> get_name();
			else
				cout << "Object is not found";
		}

		// Обработка команды DELETE
		if (command == "DELETE") {
			// Если объект найдён
			if (found) {
				// Получение имени найдённого
				string found_name = found -> get_name();

				// Проверка, является ли найдённый объект подчинённым текущего
				if (found == current -> get_child_by_name(found_name)) {
					// Создание абсолютного пути
					string path = "/" + found_name;

					Base* root_child = found;

					while (root_child -> get_parent() -> get_parent()) {
						root_child = root_child -> get_parent();

						path = "/" + root_child -> get_name() + path;
					}

					// Удаление найдённого
					current -> delete_child(found_name);

					cout << "The object " << path << " has been deleted";
				}
			}
		}

		// Обработка команды MOVE
		if (command == "MOVE") {
			// Если объект не найдён
			if (!found)
				cout << path << "     Head object is not found";

			// Недопустимо при переопределении, чтобы у нового головного
			// появились два подчиненных объекта с одинаковым наименованием.
			else if (found -> get_child_by_name(current -> get_name()))
				cout << path << "     Dubbing the names of subordinate objects";

			// Если переопределение успешно
			else if (current -> move_to(found))
				cout << "New head object: " << found -> get_name();

			else
				cout << path << "     Redefining the head object failed";
		}

		cout << endl;
	}
	// ------------------------

	// Вывод дерева после изменений
	cout << "Current object hierarchy tree" << endl;
	display_tree();

	return(0);
}

// Деструктор класса App
App::~App() {}
