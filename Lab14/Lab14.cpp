#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
#define FNAME_I "D:\\bd15.dat\0"	//��� ����� � �������� �����
#define FNAME_R "D:\\bd25.dat\0"	//��� ����� � ������������ ������
int proverka_file(const char*, const char*);	//�������� ������� �����
void dobavka(const char* fname);
void zag1();
void zag2();
void prosmotrbd1(const char* fname);
void prosmotrbd2(const char* fname);
void poisk_phonenumber(const char* fname1, const char* fname2);
void sort_date(const char* fname);
void sort_cost(const char* fname);
const char PR_R[] = "rb";	//������� �������� ��������� ����� �� ������
const char PR_S[] = "r+b";	//������� �������� ����� �� ������ � ������
const char PR_W[] = "wb";	//������� �������� ����� �� ������
const char PR_A[] = "ab";	//������� �������� ����� �� ����������
typedef struct {
	int city_code;		// ��� ������
	char phone_number[17];	// ����� �������� +d(ddd)ddd-dd-dd
	char date[11];		// YYYY.MM.DD
	int duration;		// � �������
	int cost;			// � ���.
}call;

int main()
{
	int var;
	char otv;
	char fname_i[20] = FNAME_I;
	char fname_r[20] = FNAME_R;
	setlocale(LC_ALL, "Russian");

	for (; ;)
	{//����� ���� ��������
		printf("\n    ��� ��������:\n");
		printf("  1 - �������� ���� ������\n");
		printf("  2 - ���������� ����� �������\n");
		printf("  3 - ���������� �� ���� ������\n");
		printf("  4 - ���������� �� ���� �� ������\n");
		printf("  5 - ����� �� ������ ��������\n");
		printf("  6 - �������� ���� ������\n");
		printf("  7 - �������� ���� ������ ������ ���������� ����������\n");
		printf("  8 - ���������� ������\n");
		printf("  ������� ��� �������� ->");
		scanf("%i", &var);
		switch (var)
		{
		default:break;
		case 1: if (proverka_file(fname_i, PR_R))
		{
			printf(" ���� ���� ������ ���������� ������� � ������ ", fname_i);
			printf(" ��� ������ ������.\n");
			printf(" ������ ���� � ����� ������? [Y/N] ");
			while ((otv = getchar()) == '\n');
			if (otv == 'Y' || otv == 'y' || otv == '�' || otv == '�')
			{
				printf(" ������� ��� ������������ �����: ");
				scanf("%s", fname_i);
			}
			else break;
		}
			  if (!proverka_file(fname_i, PR_W))
			  {
				  printf("\n ������ �������� ����� ��� ������\n");
				  break;
			  }
			  printf(" ������� ���� ", fname_i, '\n');
			  getchar();
			  dobavka(fname_i);
			  printf("\n �������� ����� ���������.\n");
			  if (proverka_file(fname_i, PR_R))
				  printf(" ���� ������ ������ � ������\n");
			  else printf("\n ���� �� �������\n");
			  break;
		case 2: if (proverka_file(fname_i, PR_R))
		{
			printf(" ���� ���� ������ ���������� ������� � ������ ", fname_i);
			printf(" ��� ������ ������.\n");
			printf(" ����� ��������� ����� ������ � ����? [Y/N] ");
			while ((otv = getchar()) == '\n');
			if (otv == 'N' || otv == 'n' || otv == '�' || otv == '�')
			{
				printf(" ������� ��� ����� ������ ����: ");
				scanf("%s", fname_i);
				if (!proverka_file(fname_i, PR_R))
				{
					printf(" ����� ���� ������ �� �����������\n");
					break;
				}
			}
		}
			  printf(" ��������� ������ � ���� ", fname_i, '\n');
			  dobavka(fname_i);
			  printf("\n ��������� ����� ��������� \n");
			  break;
		case 3: if (!proverka_file(fname_i, PR_S))
		{
			printf("\n ������ �������� ����� ��� ������ � ������\n");
			break;
		}
			  sort_date(fname_i);
			  printf("\n ���������� �� ���� ������ ���������\n");
			  break;
		case 4: if (!proverka_file(fname_i, PR_S))
		{
			printf("\n ������ �������� ����� ��� ������ � ������\n");
			break;
		}
			  sort_cost(fname_i);
			  printf("\n ���������� �� ��������� �� ������ ���������\n");
			  break;
		case 5: if (!proverka_file(fname_i, PR_R))
		{
			printf("\n ������ �������� ����� ��� ������\n");
			break;
		}
			  if (!proverka_file(fname_r, PR_W))
			  {
				  printf("\n ������ �������� ����� ��� ������\n");
				  break;
			  }
			  poisk_phonenumber(fname_i, fname_r);
			  printf("\n ����� �� ����������� ������ ��������\n");
			  break;
		case 6: if (!proverka_file(fname_i, PR_R))
		{
			printf("\n ������ �������� ����� ��� ������\n");
			break;
		}
			  prosmotrbd1(fname_i);
			  break;
		case 7: if (!proverka_file(fname_r, PR_R))
		{
			printf("\n ������ �������� ����� ��� ������\n");
			break;
		}
			  prosmotrbd2(fname_r);
			  break;
		case 8: return 0;
		}
	}
}

//���������� ����� ��������� � ���� ������
void dobavka(const char* fname)
{
	char otv;
	call curr_call;
	FILE* baza;
	baza = fopen(fname, PR_A);
	rewind(baza);
	do
	{
		printf("\n ��� ������? ");
		scanf("%i", &curr_call.city_code);

		printf(" ����� ��������? (� �������  +d(ddd)ddd-dd-dd) ");
		scanf("%s", &curr_call.phone_number);

		printf(" ���� ������? (� ������� YYYY.MM.DD) ");
		scanf("%s", &curr_call.date);

		printf(" �����������������? (�����) ");
		scanf("%i", &curr_call.duration);

		printf(" ��������� ������? (� ������) ");
		scanf("%i", &curr_call.cost);

		fwrite(&curr_call, sizeof(curr_call), 1, baza);

		printf("\n ����������?[Y/N]");
		while ((otv = getchar()) == '\n');
	} while (otv == 'Y' || otv == 'y' || otv == '�' || otv == '�');
	fclose(baza);
	return;
}

//����� ��������� ��� ��������� ��������� �����
void zag1()
{
	int i;

	printf("\n");
	for (i = 1; i <= 80; i++)
		printf("-");
	printf("\n");
	printf("|%10s|%20s|%11s|%17s|%16s|\n", "��� ������", "����� ��������  ",
		"���� ������", "�����������������", "��������� ������");
	for (i = 1; i <= 80; i++)
		printf("-");
	return;
}

//����� ��������� ��� ��������� ����� ������ ������
void zag2()
{
	int i;

	printf("\n");
	for (i = 1; i <= 80; i++)
		printf("-");
	printf("\n");
	printf("|%20s|%10s|%11s|%17s|%16s|\n", "����� ��������  ",  "��� ������",
		"���� ������", "�����������������", "��������� ������");
	for (i = 1; i <= 80; i++)
		printf("-");
	return;
}

//�������� ���� ������ �������
void prosmotrbd1(const char* fname)
{
	int i;
	call curr_call;
	FILE* baza;
	baza = fopen(fname, PR_R);
	printf("\n     ���� ������ ���������� ����������");
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


//�������� ���� ������ ������ ������� �� ������ ��������
void prosmotrbd2(const char* fname)
{
	int i;
	call curr_call;
	FILE* baza;
	baza = fopen(fname, PR_R);	//��������� ���� �� ������
	printf("\n  ���� ������ ������ ������� �� ������ ��������");
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

//����� ����� �� �������� ������ ����������
void poisk_phonenumber(const char* fname1, const char* fname2)
{
	char number[17];
	call curr_call;
	FILE* in,						//�������� ����
		* out;						//���� ����������� ������
	in = fopen(fname1, PR_R);		//��������� ���� �� ������
	out = fopen(fname2, PR_W);		//��������� ���� �� ������
	printf("\n ����� �������� ��� ������? ");
	scanf("%s", &number);
	while (fread(&curr_call, sizeof(curr_call), 1, in) > 0)
		if (strncmp(curr_call.phone_number, number, 17) == 0)
			fwrite(&curr_call, sizeof(curr_call), 1, out);
	fclose(out);
	fclose(in);
	return;
}

//���������� �� ���� ������
void sort_date(const char* fname)
{
	int i;
	int fl;
	call ppp, curr;
	FILE* baza;
	baza = fopen(fname, PR_S);	//��������� ���� �� ������ � ������
	do {
		rewind(baza);
		fl = 0;
		for (i = 0; fread(&curr, sizeof(curr), 1, baza) > 0; i += sizeof(curr),
			fseek(baza, i, SEEK_SET))	//������� i �� ������ �����
		{
			if (fread(&ppp, sizeof(curr), 1, baza) > 0)
			{
				if (strncmp(curr.date, ppp.date, 11) > 0)
				{
					fseek(baza, i, SEEK_SET);	//������� i �� ������ �����
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

//���������� �� �������� ��������� ������
void sort_cost(const char* fname)
{
	int i;
	int fl;
	call ppp, curr;
	FILE* baza;
	baza = fopen(fname, PR_S);	//��������� ���� �� ������ � ������
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
					fseek(baza, i, SEEK_SET);	//������� i �� ������ �����
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

//�������� ������� ����������� �����
int proverka_file(const char* fname, const char* pr)
{//��������� ����
	if (!(fopen(fname, pr)))		//���� �� ����������
		return(0);
	return(1);
}
