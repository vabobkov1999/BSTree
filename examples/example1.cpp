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
    if (tree.empty()&&(choise != 8))
      cout << "Дерево пустое!" << endl;
    else
      switch (choise) {
        case 1:
          tree.print();
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
        } break;
      }
  }
}
