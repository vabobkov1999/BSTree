
#ifdef WIN32
#include <windows.h>
#endif
#include <iostream>
#include <string>
#include <limits> // ввод значений происходит через int
#include <fstream>
#include "tree.h"
using namespace std;
using namespace BSTree;

void menu();
template <typename T>
void correct_input(T &choose);

int main(int argc, char* argv[])
{
#ifdef WIN32
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
#endif
	Tree<int> tree;
	if (argc > 1) {
		int i = 0;
		while (argc - 1 != i) {
			i++;
			tree.insert(atoi(argv[i]));
		}
	}
	bool exit = false;
	while (!exit)
	{
		menu();
		 int choose;
		  correct_input(choose);
		   switch (choose)
		{
    
		case 1:
			tree.print();
			break;
      
		case 2:
		{
    
			if (tree.empty()) {
				cout << "Дерево пустое" << endl;
				break;
			}
			bool is_correct = false;
			while (!is_correct) {
				is_correct = true;
				cout << "a. Прямой обход" << endl;
				cout << "b. Поперечный обход" << endl;
				cout << "c. Обратный обход " << endl;
				char temp = 0;
				cin >> temp;
				is_correct = tree.print((traversal_order)temp);
			}
		}
		break;
    
		case 3:
		{
			int node_value;
			cout << "Введите значение для нового узла: ";
			correct_input(node_value);
			if (!tree.insert(node_value)) {
				cout << "Такой узел уже существует" << endl;
			}
			break;
		}
		break;
    
		case 4:
		{
			cout << "Введие значение для нового узла: ";
			int new_node;
			correct_input(new_node);
			if (tree.remove(new_node)) {
				cout << "Узел был успешно удален из этого дерева" << endl;
				break;
			}
			cout << "Узел не был найден в дереве" << endl;
		}
		break;
    
		case 5:
		{
			cout << "Введите путь к файлу: ";
			string way;
			cin >> way;
			if (tree.save(way)) {
				cout << "Дерево было успешно сохранено" << endl;
				break;
			}
			cout << "Извините, что-то пошло не так" << endl;
		}
			break;
      
		case 6:
		{
			cout << "Введите путь к файлу: ";
			string way;
			cin >> way;
			if (tree.load(way)) {
				cout << "Дерево было успешно загружено" << endl;
				break;
			}
			cout << "Файл с заданным путем не существует" << endl;
		}
			break;
      
		case 7:
		{
			cout << "Введите значение для поиска: ";
			int val;
			correct_input(val);
			if (tree.exists(val)) {
				cout << "Узел найден" << endl;
				break;
			}
			cout << "Узел НЕ найден" << endl;
		}
			break;
      
		case 8:
		{
			bool is_correct = false;
			while (!is_correct)
			{
				cout << "Вы хотите покинуть программы ? (y,N)" << endl;
				string answer;
				cin >> answer;
				if (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes" || answer == "YES")
				{
					cout << "До свидания, всего хорошего!" << endl;
					is_correct = true;
					exit = true;
					break;
				}
				if (answer == "N" || answer == "n" || answer == "no" || answer == "No" || answer == "NO")
				{
					is_correct = true;
					break;
				}
				cout << "Попробуйте еще раз!" << endl;
			}
			break;
		}
		default:
			cout << "Неправильный ввод данных!" << endl;
			break;
		}
	}
	return 0;
}

void menu()
{
	cout << endl;
	cout << "Выберите одну из операций:" << endl;
	cout << "1. Вывести дерево на экран" << endl;
	cout << "2. Вывести список узлов дерева" << endl;
	cout << "3. Добавить узел в дерево" << endl;
	cout << "4. Удалить узел из дерева" << endl;
	cout << "5. Сохранить дерево в файл" << endl;
	cout << "6. Загрузить дерево из файла" << endl;
	cout << "7. Проверить наличие узла" << endl;
	cout << "8. Завершить работу программы" << endl;
}

template <typename T>
void correct_input(T &choose) {
	bool good = true;
	do {
		cin >> choose;
		if (!(good = cin.good())) {
			cout << "Неправильный ввод данных. Попробуйте еще раз" << endl;
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (!good);
}
