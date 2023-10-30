#include<iostream>
#include<locale.h>
using namespace std;
typedef int telem;		//определение типа элементов массива
typedef telem* tstr;		//определение типа "указатель на telem"
typedef tstr* tmatr;		//тип "указатель на указатель на telem"
void input_matr(tmatr a, int size);
void output_matr(tmatr a, int size);
float aver(tmatr a, int size);
//main_beg______________________________________________________________
int main()
{
    int size;		//число столбцов матрицы
    tmatr a;		//переменная-указатель на указатель на telem	
    float average;  //среднее арифметическое
    setlocale(LC_ALL, "Russian");
    cout << " Найти среднее арифметическое значений отрицательных элементов области [4+5+6+7+8]\n";
    cout << " Введите размер половины квадратной матрицы: ";
    cin >> size;
    size *= 2;
    a = new tstr[size];		/*выделение динамической памяти под массив
                       указателей на строки массива*/
    for (int i = 0; i < size; i++)	//выделение памяти под каждую строку
        *(a + i) = new telem[size];	/*каждому элементу массива указателей
                                     на строки присваивается адрес начала
                                     области памяти, выделяемой под строку*/
    input_matr(a, size);
    cout << " Исходная матрица:\n";
    output_matr(a, size);
    average = aver(a, size);
    if (average == 0)
        cout << " В заданных областях матрицы нет отрицательных элементов";
    else
        cout << " Среднне арифметическое отрицательных элементов в заданной области: " << average;
    cout << endl << " Для завершения нажмите <Enter>";
    //Освобождение динамической памяти
    for (int i = 0; i < size; i++)
        delete* (a + i);
    delete[]a;
    return 0;
}
//main_end______________________________________________________________
//input_matr_beg________________________________________________________
void input_matr(tmatr a, int size)
{
    cout << " Введите построчно через пробел элементы";
    cout << " массива размера " << size << "x" << size;
    cout << "\n После ввода строки нажимайте <Enter>" << endl;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            cin >> *(*(a + i) + j);
}
//input_matr_end________________________________________________________
//aver_beg______________________________________________________________
float aver(tmatr a, int size)
{
    telem sum = 0; // сумма элементов
    int count = 0; // кол-во элементов
    // подсчёт верхней половины матрицы (области 8)
    for (int i = 0; i < size / 2; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (a[i][j] < 0)
            {
                sum += a[i][j];
                count++;
            }
        }
    }
    // подсчёт нижней половины матрицы (областей 4, 5, 6, 7)
    for (int i = size / 2; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (a[i][j] < 0)
            {
                sum += a[i][j];
                count++;
            }
        }
    }

    return count == 0 ? 0 : float(sum) / count;

}
//aver_end______________________________________________________________
//output_matr_beg_______________________________________________________
void output_matr(tmatr a, int size)
{
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            cout.width(3);	//ширина поля выводимого параметра
            cout << *(*(a + i) + j) << ' ';
        }
        cout << '\n';
    }
}
//output_matr_end______________________________________________________
