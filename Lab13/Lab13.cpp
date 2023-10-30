#include<string.h>
#include<iostream>
#include<locale.h>

using namespace std;

char**& remove_unnecessary(char*);
void output(char**&);

int main()
{
    char input[] = "   Ded nadelal bed i pobed   ";
    setlocale(LC_ALL, "Russian");

    cout << "Исходная строка:" << endl;
    cout << input << endl;

    char** res_str = remove_unnecessary(input);

    cout << "Результат работы:" << endl;
    output(res_str);

    delete[] *res_str;
    return 0;
}

char**& remove_unnecessary(char *str)
{
    char* p;
    char* next_token = NULL;
    int size = strlen(str) / 2;
    char** result{ new char* [size] };
    for (int i = 0; i < size; i++)
    {
        result[i] = nullptr;
    }

    char last_char = NULL;
    int i = 0;

    p = strtok_s(str, ",. ", &next_token);
    while (p)
    {
        if (tolower(*p) >= last_char)
        {
            result[i++] = p;
            last_char = tolower(*p);
        }
        p = strtok_s(NULL, ",. ", &next_token);
    }

    return result;
}

void output(char**& str)
{
    while (*str)
    {
        cout << *str++ << endl;
    }
}
