/*���� modSp.cpp
�������� ����
���������� ������ ������� ��� ��������� ������*/
#include<iostream>
#include"modSp.h"
using namespace std;
//obrabotka_beg___________________________________________________________
//��������� ������
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
//�������� ����������� ������
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
//���������� ������ �������� � ����� ������
void add_spis(telem ch, list** first, list** end)
{
    list* nov = new list;	//�������� ������ ��� ������� ������
    nov->data = ch;		//��������� �������������� �����
    nov->link = 0;			//� ��������� - NULL
    if (*first)			//���� ������ �� ����
        (*end)->link = nov;
    else *first = nov;		//���� ������ ���� ����
    *end = nov;			//����� ������� ����� � ����� ������
    return;
}
//add_spis_end____________________________________________________________

//init_spis_beg___________________________________________________________
//������������� ������
void init_spis(list** first, list** end)
{
    *first = *end = 0;	//�������� ������ ����
    return;
}
//init_spis_end___________________________________________________________

//udal_spis_beg___________________________________________________________
//������������ ������������ ������
void udal_spis(list** first, list** end)
{
    list* tec;
    while (*first)				//�������� � ������� ��������
    {
        tec = *first;			//���������� ��� �����
        *first = (*first)->link;	/*������� �� ������ � ���������
                         � ���������� ��������*/
        delete tec;			//����������� ������
    }
    *end = 0;					/*����� ������ ���� ������
                           ����� ���������� ����� NULL*/
    return;
}
//udal_spis_end___________________________________________________________
