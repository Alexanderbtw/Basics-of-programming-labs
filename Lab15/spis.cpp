/*�������� ���� spis.cpp*/
#include <iostream>
#include "modSp.h"
#include <locale.h>
//main_beg________________________________________________________________
//�������� ���������
int main()
{
    using namespace std;
    bool res;
    list* first, * end;
    telem ch;
    int i;			//����� � �������
    setlocale(LC_ALL, "Russian");
    init_spis(&first, &end);
    //�������� ��������� ������
    cout << "\n ���������, ����������� �� �������� ������ �� �������� \n";
    cout << " ������� �������� ������ (�������) �������� �������;"
        << " � ����� - �����:" << endl;
    cin >> ch;
    while (ch != '.')
    {
        add_spis(ch, &first, &end);
        cin >> ch;
    }
    //����� ��������� ������
    if (first && first->link) //������ ����� ���� �� ��� �������� � ���� ��� ����������
    {
        cout << " �������� ������:" << endl;
        view_spis(first);
        //��������� ������
        res = obrabotka(first);
        cout << "\n��������� �������: ";
        if (res)
        {
            cout << "�������� ������ ����������� �� ��������\n";
        }
        else
        {
            cout << "�������� ������ �� ����������� �� ��������\n";
        }
        cout << " �������������� ������:" << endl;
        view_spis(first);
        //������������ ������
        udal_spis(&first, &end);
    }
    else cout << "������ �� ������ ��� � ��� ������ 3-� ���������";
    cout << "\n ���������-1, �����-2";
    cin >> i;
    if (i == 1) main();
    return 0;
}
