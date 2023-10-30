#include<iostream>
#include<math.h>
#include<locale.h>
using namespace std;
typedef int telem;	//объявление типа элемента массива
typedef telem* tmas;	//объявление типа "указатель на telem"
telem mult(tmas a, int n, int size);
int find_neg_idx(tmas a, int size);
void inputmas(tmas a, int size);
void outputmas(tmas a, int size);
//main_beg______________________________________________________________
int main()
{
    int n;				//размер массива
    setlocale(LC_ALL, "Russian");
    cout << "\n Найти номер элемента массива, для которого сумма" << endl;
    cout << " разностей со значениями соседних элементов максимальна";
    //Ввод исходных данных
    cout << "\n Введите значение n: ";
    cin >> n;
    int size = n * 2;
    tmas a = new telem[size];	/*создание переменной-указателя на telem,
                                 выделение динамической памяти под массив
                                 адрес начала области заносится в a*/
    telem prod;
    inputmas(a, size);
    cout << " Исходный массив:\n";
    outputmas(a, size);

    prod = mult(a, n, size);
    if (prod == -1)
        cout << " В массиве нет отрицательных элементов ";
    else
        cout << " Искомое произведение элементов массива с нечётными номерами: " << prod << endl;
    delete[] a;			//освобождение динамической памяти
    return 0;
}
//main_end______________________________________________________________
//find_first_neg_start__________________________________________________
int find_neg_idx(tmas a, int size)
{
    int first_neg = -1;
    for (int i = 0; i < size; i++)
    {
        if (a[i] < 0)
        {
            first_neg = i;
            break;
        }
    }
    return first_neg;
}
//find_first_neg_end____________________________________________________
//mult_beg______________________________________________________________
telem mult(tmas a, int n, int size)
{
    // поиск первого отрицательного числа
    int first_neg = find_neg_idx(a, size);
    if (first_neg == -1)
        return -1;

    telem left = 0, right = 0;

    if (first_neg > n)
    {
        left = n;
        right = first_neg;
    }
    else
    {
        right = n;
        left = first_neg;
    }

    if (left % 2 == 0)
    {
        left += 1;
    }
    else
    {
        left += 2;
    }

    telem prod = right - left > 1 ? a[left] : 0;			//если между элементами есть хоть один элемент с нечетным идексом, задаём его значение, иначе - 0

    // поиск произведения
    for (int i = left + 2; i < right; i += 2)
    {
        prod *= a[i];
    }

    return abs(prod);
}
//mult_end______________________________________________________________
//inputmas_beg__________________________________________________________
void inputmas(tmas a, int size)
{
    cout << " В массиве обязательно должно пристуствовать хотя бы одно отрицательное число!" << endl;
    cout << " Введите одной строкой элементы массива из ";
    cout << size << " чисел и нажмите <Enter>" << endl << " ";
    
    for (int i = 0; i < size; i++)
        cin >> *(a + i);
}
//inputmas_end__________________________________________________________
//outputmas_beg_______________________________________________________
void outputmas(tmas a, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << *(a + i) << ' ';
    }
    cout << endl;
}
//outputmas_end_______________________________________________________

