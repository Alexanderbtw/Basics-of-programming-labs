/*Файл modSp.cpp
Исходный файл
Реализация набора функций для обработки списка*/
#include<iostream>
#include"modSp.h"
using namespace std;
//obrabotka_beg___________________________________________________________
//Обработка списка
bool obrabotka(list* first)
{
    while (first->link)
    {
        if (tolower(first->data) > tolower(first->link->data))
            return false;
        first = first->link;
    }
    return true;
}
//obrabotka_end___________________________________________________________

//view_spis_beg___________________________________________________________
//Просмотр содержимого списка
void view_spis(list* tec)
{
    while (tec)
    {
        cout << tec->data << " ";
        tec = tec->link;
    }
    return;
}
//view_spis_end___________________________________________________________

//add_spis_beg____________________________________________________________
//Добавление нового элемента в конец списка
void add_spis(telem ch, list** first, list** end)
{
    list* nov = new list;	//выделяем память под элемент списка
    nov->data = ch;		//заполняем информационную часть
    nov->link = 0;			//в ссылочную - NULL
    if (*first)			//если список не пуст
        (*end)->link = nov;
    else *first = nov;		//если список пока пуст
    *end = nov;			//новый элемент встал в конец списка
    return;
}
//add_spis_end____________________________________________________________

//init_spis_beg___________________________________________________________
//Инициализация списка
void init_spis(list** first, list** end)
{
    *first = *end = 0;	//исходный список пуст
    return;
}
//init_spis_end___________________________________________________________

//udal_spis_beg___________________________________________________________
//Освобождение динамической памяти
void udal_spis(list** first, list** end)
{
    list* tec;
    while (*first)				//начинаем с первого элемента
    {
        tec = *first;			//запоминаем его адрес
        *first = (*first)->link;	/*удаляем из списка и переходим
                         к следующему элементу*/
        delete tec;			//освобождаем память
    }
    *end = 0;					/*когда удален весь список
                           адрес последнего равен NULL*/
    return;
}
//udal_spis_end___________________________________________________________
