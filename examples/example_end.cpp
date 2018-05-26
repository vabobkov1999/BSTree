#include <iostream>
#include <string>
#include "bstree.hpp"
using namespace BSTree;
using namespace std;

auto menu(Tree&) -> void;

auto change_color(int c) -> void;

int main(int argc, char* argv[]) {
    Tree tree;
    int n = 0;

    for (unsigned int i = 1; i < argc; ++i) ++n;

    int* MassTree_curr = new int[n];

    for (unsigned i = 0; i < n; ++i) MassTree_curr[i] = atoi(argv[i + 1]);

    int* MassTree = new int[n];

    for (unsigned i = 0; i < n; ++i)
        for (unsigned j = i + 1; j < n; ++j) {
            if (MassTree_curr[i] == MassTree_curr[j]) MassTree_curr[j] = 0;
        }
    int k = 0;
    bool flag = true;
    for (unsigned i = 0; i < n; ++i) {
        if ((MassTree_curr[i] == 0) && (flag == true)) {
            string str = argv[i + 1];
            if (str == "0") {
                MassTree[k] = MassTree_curr[i];
                ++k;
                flag = false;
                continue;
            }
        }
        if (MassTree_curr[i] != 0) {
            MassTree[k] = MassTree_curr[i];
            ++k;
        }
    }

    for (unsigned i = 0; i < k; ++i) tree.insert(MassTree[i]);
    delete[] MassTree_curr;
    menu(tree);
    delete[] MassTree;
}

auto menu(Tree & tree) -> void {
    while (1) {
        change_color(CYAN);
        cout << "Выберите одну из операций: " << endl;
        cout << "1. Вывести дерево на экран" << endl;
        cout << "2. Вывести список узлов дерева" << endl;
        cout << "3. Добавить узел в дерево" << endl;
        cout << "4. Удалить узел из дерева" << endl;
        cout << "5. Сохранить дерево в файл" << endl;
        cout << "6. Загрузить дерево из файла" << endl;
        cout << "7. Проверить наличие узла" << endl;
        cout << "8. Завершить работу программы" << endl;
        change_color(GREEN);
        int choise = 0;
        cin >> choise;
        if (tree.empty()&&(choise != 8)&&(choise != 3)) {
            cout << "Дерево пустое!" << endl;
            cout << tree.empty() << endl;
        }
        else
            switch (choise) {
            case 1:
                tree.print_tree();
                break;
            case 2: {
                change_color(GREEN);
                cout << "Ввести списков узлов дерева:" << endl;
                cout << "а. Прямой обход"<< endl;
                cout << "b. Поперечный обход" << endl;
                cout << "c. Обратный обход" << endl;
                char value;
                cin >> value;
                if (value == 'a')
                    tree.print(traversal_order::pre);
                else if (value == 'b')
                    tree.print(traversal_order::in);
                else if (value == 'c')
                    tree.print(traversal_order::post);
                else {
                    change_color(RED);
                    cout << "Введено некорректное значение!";
                }
                cout << endl;
            }
            break;
            case 3: {
                change_color(GREEN);
                cout << "Введите значение добавляемого элемента: ";
                int value;
                cin >> value;
                bool flag = tree.add_element(value);
                if (flag) {
                    cout << "Элемент успешно добавлен в дерево!" << endl;
                }
                if (!flag) {
                    change_color(RED);
                    cout << "Элемент со значением " << value << " уже есть в дереве!" << endl;
                }
            }
            break;
            case 4: {
                change_color(GREEN);
                cout << "Введите значение удаляемого элемента: ";
                int value;
                cin >> value;
                bool flag = tree.remove(value);
                if (flag) {
                    cout << "Элемент успешно удален из дерева!" << endl;
                }
                if (!flag) {
                    change_color(RED);
                    cout << "Элемент со значением " << value << " не найден в дереве!" << endl;
                }
            }
            break;
            case 5: {
                change_color(GREEN);
                cout << "Введите путь к файлу: ";
                string way;
                cin >> way;
                bool rez = tree.save(way);
                if (rez)
                    cout << "Дерево было успешно сохранено" << endl;
            }
            break;
            case 6: {
                change_color(GREEN);
                cout << "Введите путь к файлу: ";
                string way;
                cin >> way;
                bool rez = tree.load(way);
                if (rez)
                    cout << "Дерево было успешно загружено" << endl;
                else {
                    change_color(RED);
                    cout << "Файл с заданным путем не существует" << endl;
                }
            }
            break;
            case 7: {
                change_color(GREEN);
                cout << "Введите значение для поиска: ";
                int val;
                cin >> val;
                bool rez = tree.exists(val);
                if(rez)
                    cout << "Узел найден" << endl;
                else {
                    change_color(RED);
                    cout << "Узел не найден" << endl;
                }
            }
            break;
            case 8: {
                change_color(RED);
                cout << "Вы уверены, что хотите выйти?(yes|no)" << endl;
                change_color(GREEN);
                string prog_exit;
                cin >> prog_exit;
                if ((prog_exit == "yes") || (prog_exit == "YES") ||
                        (prog_exit == "Yes") || (prog_exit == "y")) {
                    cout << "До свидания !" << endl;
                    return;
                }
            }
            break;
            }
    }
}
