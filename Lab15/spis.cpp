/*Основной файл spis.cpp*/
#include <iostream>
#include "modSp.h"
#include <locale.h>
//main_beg________________________________________________________________
//основная программа
int main()
{
    using namespace std;
    bool res;
    list* first, * end;
    telem ch;
    int i;			//ответ в диалоге
    setlocale(LC_ALL, "Russian");
    init_spis(&first, &end);
    //создание исходного списка
    cout << "\n Проверить, упорядочены ли элементы списка по алфавиту \n";
    cout << " Введите элементы списка (символы) сплошной строкой;"
        << " в конце - точка:" << endl;
    cin >> ch;
    while (ch != '.')
    {
        add_spis(ch, &first, &end);
        cin >> ch;
    }
    //вывод исходного списка
    if (first && first->link) //список имеет хотя бы два элемента и есть что сравнивать
    {
        cout << " Исходный список:" << endl;
        view_spis(first);
        //обработка списка
        res = obrabotka(first);
        cout << "\nРезультат получен: ";
        if (res)
        {
            cout << "Элементы списка упорядочены по алфавиту\n";
        }
        else
        {
            cout << "Элементы списка НЕ упорядочены по алфавиту\n";
        }
        cout << " Результирующий список:" << endl;
        view_spis(first);
        //освобождение памяти
        udal_spis(&first, &end);
    }
    else cout << "Список не создан или в нем меньше 3-х элементов";
    cout << "\n Повторить-1, Выход-2";
    cin >> i;
    if (i == 1) main();
    return 0;
}
