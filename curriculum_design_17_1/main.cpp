//  Copyright (C) 2017  JEVEM624
//This program is free software: you can redistribute it and or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<windows.h>
struct student//����student�ṹ�����
{
	long id;
	char name[20];
	int age;
	char gender[4];
	int year;
	int month;
	int day;
	char address[100];
	char phone[20];
	char email[50];
	struct student *next;
};
typedef struct student Student, *Linklist;
int load(Linklist A);
int save(Linklist A);
int input(Linklist A);
int output(Linklist A);
int age(Linklist p, int y, int m, int d);
int edit(Linklist A);
int seach_id(Linklist A);
int seach_name(Linklist A);
int main()
{
	Linklist A = (Linklist)malloc(sizeof(Student));//����ṹ����Ϊͷ
	A->next = NULL;
	load(A);//�����ļ�
	int menu_select, sec_menu_select = 0;
	int day, month, year;//��ȡϵͳʱ����������
	struct tm *ptr;
	time_t it;
	it = time(NULL);
	ptr = localtime(&it);
	day = ptr->tm_mday;
	month = ptr->tm_mon + 1;
	year = ptr->tm_year + 1900;

	while (1)
	{
		system("mode con cols=85 lines=30  ");
		system("cls");
		printf("��ӭʹ��ѧ����Ϣ����ϵͳ\n\n");
		printf("**********�˵�**********\n");
		printf("*   1.ѧ����Ϣ¼��     *\n");
		printf("*   2.ѧ����Ϣ�޸�     *\n");
		printf("*   3.ѧ����Ϣ���     *\n");
		printf("*   4.ѧ����Ϣ��ѯ     *\n");
		printf("*   5.�˳�             *\n");
		printf("************************\n");
		printf("��ѡ��");
		scanf("%d", &menu_select);
		switch (menu_select)
		{
		case 1://����¼��ģ��
			system("cls");
			input(A);
			save(A);
			break;
		case 2://�����޸�ģ��
			system("cls");
			edit(A);
			save(A);
			break;
		case 3://�������ģ��
			system("cls");
			output(A);
			break;
		case 4://�����ѯģ��
		{
			while (1)
			{
				system("cls");
				printf("��ӭʹ��ѧ����Ϣ����ϵͳ\n\n");
				printf("**********�˵�**********\n");
				printf("*   1.��ѧ�Ų�ѯ     *\n");
				printf("*   2.��������ѯ     *\n");
				printf("*   0.�˳�           *\n");
				printf("��ѡ��");
				scanf("%d", &sec_menu_select);
				switch (sec_menu_select)
				{
				case 0:
					system("cls");
					break;
				case 1:
					seach_id(A);
					break;
				case 2:
					seach_name(A);
					break;
				default:
					printf("��������ȷѡ��");
					getchar();
					getchar();

				};
				break;
			}
		}
		break;
		case 5://�˳�����
			system("cls");
			return 0;
			break;
		default:
			printf("��������ȷѡ��");
			getchar();
			getchar();
			break;
		}
	}
	return 0;
}
int load(Linklist A)//���س���ǰĿ¼�������ļ�
{
	FILE *fp;
	long id;
	if (fp = fopen("data.txt", "r"), fp == NULL) //���ļ����������½�һ��
	{
		FILE *fp = fopen("data.txt", "w");
		return 0;
	}
	while (fscanf(fp, "%ld", &id) != EOF)//���ɹ�����һ������
	{
		//Ϊ��ǰ�����������s
		Linklist s;
		s = (Linklist)malloc(sizeof(Student));

		s->id = id;
		fscanf(fp, "%s %d %s %d %d %d %s %s %s", &s->name, &s->age, &s->gender, &s->year, &s->month, &s->day, &s->address, &s->phone, &s->email);
		s->next = A->next;
		A->next = s;
	}
	return 0;
}
int save(Linklist A)
{
	FILE *fp;
	Linklist p = A->next; //pָ����Ԫ���

	fp = fopen("data.txt", "w");

	while (p) //�������ݵ��ļ�
	{
		fprintf(fp, "%ld %s %d %s %d %d %d %s %s %s", p->id, p->name, p->age, p->gender, p->year, p->month, p->day, p->address, p->phone, p->email);
		fprintf(fp, "\n");
		p = p->next;
	}
	printf("\n");

	fclose(fp);
	return 0;
}
int input(Linklist A)
{
	int day, month, year, t = 0;

	struct tm *ptr;
	time_t it;
	it = time(NULL);
	ptr = localtime(&it);
	day = ptr->tm_mday;
	month = ptr->tm_mon + 1;
	year = ptr->tm_year + 1900;
	char ch = 'y';
	while (ch == 'y')
	{
		system("cls");
		Linklist s, panduan;//�����½ڵ�
		s = (Linklist)malloc(sizeof(Student));

		while (1)//����¼��
		{
			printf("������ѧ��:");
			scanf("%ld", &s->id);
			t = 0;
			panduan = (Linklist)malloc(sizeof(Student));
			panduan = A->next;
			while (panduan)//�ж�ѧ���Ƿ��ظ�
			{

				if (s->id == panduan->id)
				{
					t = t + 1;
					panduan = panduan->next;
				}
				else
					panduan = panduan->next;
			}
			if (t != 0)
			{
				printf("ѧ���ظ�������������\n");
				continue;
			}
			else
				break;
		}
		printf("����������:");
		scanf("%s", &s->name);
		printf("�������Ա�:");
		scanf("%s", &s->gender);
		while (1)//�ж������Ƿ���ȷ
		{
			printf("���������������:");
			scanf("%d%d%d", &s->year, &s->month, &s->day);
			if ((s->year > year) || (s->year == year&&s->month > month) || (s->year == year, s->month == month, s->day > day))
			{
				printf("��������ȷ����\n");
				continue;
			}
			else
				age(s, s->year, s->month, s->day);
			break;
		}
		printf("��ַ:");
		scanf("%s", &s->address);
		printf("�绰:");
		scanf("%s", &s->phone);
		printf("E-mail:");
		scanf("%s", &s->email);
		s->next = NULL;
		s->next = A->next;
		A->next = s;
		printf("�Ƿ�������(y/n):\n");
		scanf(" %c", &ch);
		system("cls");
	}

	return 0;
}
int output(Linklist A)
{
	system("mode con cols=130 lines=50  ");
	Linklist p;
	int i = 0;
	p = A->next; //pָ����Ԫ���
	printf("ѧ��      ����     ����     �Ա�          ��������            ��ַ                      �绰               E-mail\n");
	while (p) //��p�ǿգ����p�е�����
	{

		printf("%-10ld%-10s%-10d%-10s%d��%d��%d��   %-30s%-15s%-15s\n", p->id, p->name, p->age, p->gender, p->year, p->month, p->day, p->address, p->phone, p->email);
		p = p->next;
	}
	printf("\n\n��������������˵�");
	getchar();
	getchar();
	system("cls");
	return 0;
}
int seach_id(Linklist A)
{
	int id, t = 0;
	printf("������ѧ��");
	scanf("%ld", &id);
	Linklist p;
	p = (Linklist)malloc(sizeof(student));
	p = A->next;
	while (p)//������ѧ�Ž�������������������������
	{
		if (p->id == id)
		{
			system("mode con cols=130 lines=50  ");
			printf("ѧ��      ����     ����     �Ա�          ��������            ��ַ                      �绰               E-mail\n");
			printf("%-10ld%-10s%-10d%-10s%d��%d��%d��   %-30s%-15s%-15s\n", p->id, p->name, p->age, p->gender, p->year, p->month, p->day, p->address, p->phone, p->email);
			t = t + 1;
			getchar();
			getchar();
			break;
		}
		else
		{
			p = p->next;
		}
	}
	if (t == 0)
	{
		printf("δ�鵽ѧ��Ϊ%d��ѧ��", id);
		getchar();
		getchar();
	}
	return 0;
}
int seach_name(Linklist A)
{
	char name[20];
	int t = 0;
	printf("����������");
	scanf("%s", &name);
	Linklist p;
	p = (Linklist)malloc(sizeof(student));
	p = A->next;
	while (p)//���������ֽ�������������������������
	{
		if (strcmp(p->name, name) == 0)
		{
			system("mode con cols=130 lines=50  ");
			printf("ѧ��      ����     ����     �Ա�          ��������            ��ַ                      �绰               E-mail\n");
			printf("%-10ld%-10s%-10d%-10s%d��%d��%d��   %-30s%-15s%-15s\n", p->id, p->name, p->age, p->gender, p->year, p->month, p->day, p->address, p->phone, p->email);
			getchar();
			getchar();
			t = t + 1;
			break;
		}
		else
		{
			p = p->next;
		}
	}
	if (t == 0)
	{
		printf("δ�鵽����Ϊ%s��ѧ��", name);
		getchar();
		getchar();
	}
	return 0;
}
int age(Linklist p, int y, int m, int d)
{
	int day, month, year;//��ȡϵͳʱ��
	struct tm *ptr;
	time_t it;
	it = time(NULL);
	ptr = localtime(&it);
	day = ptr->tm_mday;
	month = ptr->tm_mon + 1;
	year = ptr->tm_year + 1900;

	if (y != year)//��������м���
	{
		p->age = year - y;
	}
	else
	{
		if (m > month)
		{
			p->age = year - y;
		}
		else if (m < month)
		{
			p->age = year - y + 1;
		}
		else if (m = month)
		{
			if (d > day)
			{
				p->age = year - y;
			}
			else if (d <= day)
			{
				p->age = year - y + 1;
			}
		}
	}
	return 0;
}
int edit(Linklist A)
{
	int day, month, year, t = 0;//��ȡϵͳʱ��������
	struct tm *ptr;
	time_t it;
	it = time(NULL);
	ptr = localtime(&it);
	day = ptr->tm_mday;
	month = ptr->tm_mon + 1;
	year = ptr->tm_year + 1900;
	long i;
	printf("������Ҫ�޸ĵ�ѧ��ѧ�ţ�");
	scanf("%ld", &i);
	Linklist p;
	p = A->next;
	while (p) //�鵽ѧ��
	{

		if (p->id == i)//�ж������id�Ƿ��������е�ѧ��id��ͬ
		{
			t = t + 1;
			int i;
			char ch = 'y';


			while (ch == 'y')//���Խ��ж���޸�
			{
				system("cls");
				system("mode con cols=130 lines=50  ");
				printf("ѧ��      ����     ����     �Ա�          ��������            ��ַ                      �绰               E-mail\n");
				printf("%-10ld%-10s%-10d%-10s%d��%d��%d��   %-30s%-15s%-15s\n", p->id, p->name, p->age, p->gender, p->year, p->month, p->day, p->address, p->phone, p->email);
				printf("��ѡ���޸�����1.ѧ��  2.����  3.�Ա�  4.��������  5.��ַ  6.�绰  7.E-mail  8.�˳�:\n");//�����û�����ѡ���޸�����

				scanf("%d", &i);
				switch (i)
				{
				case 1:
					Linklist panduan;
					int t, temp_id;
					while (1)
					{
						printf("�޸�ѧ��Ϊ:");
						scanf("%ld", &temp_id);
						t = 0;
						panduan = (Linklist)malloc(sizeof(Student));
						panduan = A->next;
						while (panduan)//�ж��޸ĺ��ѧ����ϵͳ���Ƿ����
						{

							if (temp_id == panduan->id)
							{
								t = t + 1;
								panduan = panduan->next;
							}
							else
								panduan = panduan->next;
						}
						if (t != 0)
						{
							printf("ѧ���ظ�������������\n");
							continue;
						}
						else
						{
							p->id = temp_id;
							break;
						}

					}
					break;
				case 2:
					printf("�޸�����Ϊ");
					scanf("%s", &p->name);
					break;
				case 4:
					while (1)//�ж������Ƿ���ȷ
					{
						printf("�޸ĳ���������Ϊ:");
						scanf("%d%d%d", &p->year, &p->month, &p->day);
						if ((p->year > year) || (p->year == year&&p->month > month) || (p->year == year, p->month == month, p->day > day))
						{
							printf("��������ȷ����\n");
							continue;
						}
						else
						{
							age(p, p->year, p->month, p->day);
							break;
						}
					}
					break;
				case 3:
					printf("�޸��Ա�Ϊ��");
					scanf("%s", &p->gender);
					break;
				case 5:
					printf("�޸ĵ�ַΪ��");
					scanf("%s", &p->address);
					break;
				case 6:
					printf("�޸ĵ绰Ϊ��");
					scanf("%s", &p->phone);
					break;
				case 7:
					printf("�޸�EmailΪ");
					scanf("%s", &p->email);
					break;
				case 0:
					return 0;
				}
				if (i != 8)
				{
					printf("�Ƿ�����޸�(y/n):");
					scanf(" %c", &ch);
				}
				else
					ch = 'n';
			}
			p = p->next;//ָ���̽��
		}
		else
			p = p->next;//ָ���̽��
	}
	if (t == 0)
	{
		printf("δ�ҵ�ѧ��Ϊ%ld��ѧ��", i);
		getchar();
		getchar();
	}
	return 0;
}