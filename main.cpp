#include "headers/App.h"

int main()
{
	// program here
	App app(nullptr);       // Объявление объекта приложение
	app.build_tree();       // Конструирование системы
	return(app.execute());  // Запуск системы
}
