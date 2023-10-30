#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
#define FNAME_I "D:\\bd15.dat\0"	//имя файла с исходной базой
#define FNAME_R "D:\\bd25.dat\0"	//имя файла с результатами поиска
int proverka_file(const char*, const char*);	//проверка наличия файла
void dobavka(const char* fname);
void zag1();
void zag2();
void prosmotrbd1(const char* fname);
void prosmotrbd2(const char* fname);
void poisk_phonenumber(const char* fname1, const char* fname2);
void sort_date(const char* fname);
void sort_cost(const char* fname);
const char PR_R[] = "rb";	//признак открытия бинарного файла на чтение
const char PR_S[] = "r+b";	//признак открытия файла на чтение и запись
const char PR_W[] = "wb";	//признак открытия файла на запись
const char PR_A[] = "ab";	//признак открытия файла на добавление
typedef struct {
	int city_code;		// Код города
	char phone_number[17];	// Номер телефона +d(ddd)ddd-dd-dd
	char date[11];		// YYYY.MM.DD
	int duration;		// В минутах
	int cost;			// В руб.
}call;

int main()
{
	int var;
	char otv;
	char fname_i[20] = FNAME_I;
	char fname_r[20] = FNAME_R;
	setlocale(LC_ALL, "Russian");

	for (; ;)
	{//Выбор вида действия
		printf("\n    Вид действия:\n");
		printf("  1 - создание базы данных\n");
		printf("  2 - добавление новых записей\n");
		printf("  3 - сортировка по дате звонка\n");
		printf("  4 - сортировка по цене за минуту\n");
		printf("  5 - поиск по номеру телефона\n");
		printf("  6 - просмотр базы данных\n");
		printf("  7 - просмотр базы данных поиска телефонных разговоров\n");
		printf("  8 - завершение задачи\n");
		printf("  Введите вид действия ->");
		scanf("%i", &var);
		switch (var)
		{
		default:break;
		case 1: if (proverka_file(fname_i, PR_R))
		{
			printf(" Файл базы данных телефонных звонков с именем ", fname_i);
			printf(" был создан раньше.\n");
			printf(" Создаём файл с новым именем? [Y/N] ");
			while ((otv = getchar()) == '\n');
			if (otv == 'Y' || otv == 'y' || otv == 'Н' || otv == 'н')
			{
				printf(" Задайте имя создаваемого файла: ");
				scanf("%s", fname_i);
			}
			else break;
		}
			  if (!proverka_file(fname_i, PR_W))
			  {
				  printf("\n Ошибка открытия файла для записи\n");
				  break;
			  }
			  printf(" Создаем базу ", fname_i, '\n');
			  getchar();
			  dobavka(fname_i);
			  printf("\n Создание файла закончено.\n");
			  if (proverka_file(fname_i, PR_R))
				  printf(" База данных готова к работе\n");
			  else printf("\n база не создана\n");
			  break;
		case 2: if (proverka_file(fname_i, PR_R))
		{
			printf(" Файл базы данных телефонных звонков с именем ", fname_i);
			printf(" был создан раньше.\n");
			printf(" Будем добавлять новые записи в него? [Y/N] ");
			while ((otv = getchar()) == '\n');
			if (otv == 'N' || otv == 'n' || otv == 'Т' || otv == 'т')
			{
				printf(" Задайте имя файла другой базы: ");
				scanf("%s", fname_i);
				if (!proverka_file(fname_i, PR_R))
				{
					printf(" Такая база данных не создавалась\n");
					break;
				}
			}
		}
			  printf(" Добавляем записи в файл ", fname_i, '\n');
			  dobavka(fname_i);
			  printf("\n Изменение файла закончено \n");
			  break;
		case 3: if (!proverka_file(fname_i, PR_S))
		{
			printf("\n Ошибка открытия файла для чтения и записи\n");
			break;
		}
			  sort_date(fname_i);
			  printf("\n Сортировка по дате звонка закончена\n");
			  break;
		case 4: if (!proverka_file(fname_i, PR_S))
		{
			printf("\n Ошибка открытия файла для чтения и записи\n");
			break;
		}
			  sort_cost(fname_i);
			  printf("\n Сортировка по стоимости за минуту закончена\n");
			  break;
		case 5: if (!proverka_file(fname_i, PR_R))
		{
			printf("\n Ошибка открытия файла для чтения\n");
			break;
		}
			  if (!proverka_file(fname_r, PR_W))
			  {
				  printf("\n Ошибка открытия файла для записи\n");
				  break;
			  }
			  poisk_phonenumber(fname_i, fname_r);
			  printf("\n Поиск по телефонному номеру закончен\n");
			  break;
		case 6: if (!proverka_file(fname_i, PR_R))
		{
			printf("\n Ошибка открытия файла для чтения\n");
			break;
		}
			  prosmotrbd1(fname_i);
			  break;
		case 7: if (!proverka_file(fname_r, PR_R))
		{
			printf("\n Ошибка открытия файла для чтения\n");
			break;
		}
			  prosmotrbd2(fname_r);
			  break;
		case 8: return 0;
		}
	}
}

//Добавление новых элементов в базу данных
void dobavka(const char* fname)
{
	char otv;
	call curr_call;
	FILE* baza;
	baza = fopen(fname, PR_A);
	rewind(baza);
	do
	{
		printf("\n Код города? ");
		scanf("%i", &curr_call.city_code);

		printf(" Номер телефона? (в формате  +d(ddd)ddd-dd-dd) ");
		scanf("%s", &curr_call.phone_number);

		printf(" Дата звонка? (в формате YYYY.MM.DD) ");
		scanf("%s", &curr_call.date);

		printf(" Продолжительность? (минут) ");
		scanf("%i", &curr_call.duration);

		printf(" Стоимость минуты? (в рублях) ");
		scanf("%i", &curr_call.cost);

		fwrite(&curr_call, sizeof(curr_call), 1, baza);

		printf("\n Продолжать?[Y/N]");
		while ((otv = getchar()) == '\n');
	} while (otv == 'Y' || otv == 'y' || otv == 'Н' || otv == 'н');
	fclose(baza);
	return;
}

//Вывод заголовка при просмотре исходного файла
void zag1()
{
	int i;

	printf("\n");
	for (i = 1; i <= 80; i++)
		printf("-");
	printf("\n");
	printf("|%10s|%20s|%11s|%17s|%16s|\n", "Код города", "Номер телефона  ",
		"Дата звонка", "Продолжительность", "Стоимость минуты");
	for (i = 1; i <= 80; i++)
		printf("-");
	return;
}

//Вывод заголовка при просмотре файла поиска звонка
void zag2()
{
	int i;

	printf("\n");
	for (i = 1; i <= 80; i++)
		printf("-");
	printf("\n");
	printf("|%20s|%10s|%11s|%17s|%16s|\n", "Номер телефона  ",  "Код города",
		"Дата звонка", "Продолжительность", "Стоимость минуты");
	for (i = 1; i <= 80; i++)
		printf("-");
	return;
}

//Просмотр базы данных звонков
void prosmotrbd1(const char* fname)
{
	int i;
	call curr_call;
	FILE* baza;
	baza = fopen(fname, PR_R);
	printf("\n     База данных телефонных разговоров");
	zag1();
	while (fread(&curr_call, sizeof(curr_call), 1, baza) > 0)
	{
		printf("\n|%10i|%20s|%11s|%17i|%16i|", curr_call.city_code, curr_call.phone_number,
			curr_call.date, curr_call.duration, curr_call.cost);
	}
	printf("\n");
	for (i = 1; i <= 80; i++)
		printf("-");
	fclose(baza);
	return;
}


//Просмотр базы данных поиска звонков по номеру телефона
void prosmotrbd2(const char* fname)
{
	int i;
	call curr_call;
	FILE* baza;
	baza = fopen(fname, PR_R);	//открываем файл на чтение
	printf("\n  База данных поиска звонков по номеру телефона");
	zag2();
	while (fread(&curr_call, sizeof(curr_call), 1, baza) > 0)
	{
		printf("\n|%20s|%10i|%11s|%17i|%16i|", curr_call.phone_number, curr_call.city_code,
			curr_call.date, curr_call.duration, curr_call.cost);
	}
	printf("\n");
	for (i = 1; i <= 80; i++)
		printf("-");
	fclose(baza);
	return;
}

//Поиск туров по названию страны пребывания
void poisk_phonenumber(const char* fname1, const char* fname2)
{
	char number[17];
	call curr_call;
	FILE* in,						//исходный файл
		* out;						//файл результатов поиска
	in = fopen(fname1, PR_R);		//открываем файл на чтение
	out = fopen(fname2, PR_W);		//открываем файл на запись
	printf("\n Номер телефона для поиска? ");
	scanf("%s", &number);
	while (fread(&curr_call, sizeof(curr_call), 1, in) > 0)
		if (strncmp(curr_call.phone_number, number, 17) == 0)
			fwrite(&curr_call, sizeof(curr_call), 1, out);
	fclose(out);
	fclose(in);
	return;
}

//Сортировка по дате звонка
void sort_date(const char* fname)
{
	int i;
	int fl;
	call ppp, curr;
	FILE* baza;
	baza = fopen(fname, PR_S);	//открываем файл на чтение и запись
	do {
		rewind(baza);
		fl = 0;
		for (i = 0; fread(&curr, sizeof(curr), 1, baza) > 0; i += sizeof(curr),
			fseek(baza, i, SEEK_SET))	//позиция i от НАЧАЛА файла
		{
			if (fread(&ppp, sizeof(curr), 1, baza) > 0)
			{
				if (strncmp(curr.date, ppp.date, 11) > 0)
				{
					fseek(baza, i, SEEK_SET);	//позиция i от НАЧАЛА файла
					fwrite(&ppp, sizeof(curr), 1, baza);
					fwrite(&curr, sizeof(curr), 1, baza);
					fl = 1;
				}
			}
		}
	} while (fl);
	fclose(baza);
	return;
}

//Сортировка по убыванию стоимости звонка
void sort_cost(const char* fname)
{
	int i;
	int fl;
	call ppp, curr;
	FILE* baza;
	baza = fopen(fname, PR_S);	//открываем файл на чтение и запись
	do {
		rewind(baza);
		fl = 0;
		for (i = 0; fread(&curr, sizeof(curr), 1, baza) > 0; i += sizeof(curr),
			fseek(baza, i, SEEK_SET))
		{
			if (fread(&ppp, sizeof(curr), 1, baza) > 0)
			{
				if (curr.cost > ppp.cost)
				{
					fseek(baza, i, SEEK_SET);	//позиция i от НАЧАЛА файла
					fwrite(&ppp, sizeof(curr), 1, baza);
					fwrite(&curr, sizeof(curr), 1, baza);
					fl = 1;
				}
			}
		}
	} while (fl);
	fclose(baza);
	return;
}

//проверка наличия физического файла
int proverka_file(const char* fname, const char* pr)
{//Открываем файл
	if (!(fopen(fname, pr)))		//файл не существует
		return(0);
	return(1);
}
