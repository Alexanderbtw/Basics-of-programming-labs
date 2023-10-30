#pragma once
/*Файл modSp.h
Заголовочный файл
Содержит определения новых типов и объявления функций*/
//Определения типов
typedef char telem;	//определение типа информационного поля
struct list			//определение типа элемента списка
{
	telem data;		//информационное поле
	list* link;		//поле адреса
};
//Объявления (прототипы) функций
void init_spis(list**, list**);			//инициализация списка
void add_spis(telem, list**, list**);	//добавление элемента
bool obrabotka(list*);					//обработка списка
void view_spis(list*);					//просмотр списка
void udal_spis(list**, list**);			//освобождение памяти