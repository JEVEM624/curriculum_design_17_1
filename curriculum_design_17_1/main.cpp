//  Copyright (C) 2017  JEVEM624
//This program is free software: you can redistribute it and or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<windows.h>
struct student//定义student结构体变量
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
	Linklist A = (Linklist)malloc(sizeof(Student));//申请结构体作为头
	A->next = NULL;
	load(A);//加载文件
	int menu_select, sec_menu_select = 0;
	int day, month, year;//获取系统时间存入变量中
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
		printf("欢迎使用学生信息管理系统\n\n");
		printf("**********菜单**********\n");
		printf("*   1.学生信息录入     *\n");
		printf("*   2.学生信息修改     *\n");
		printf("*   3.学生信息浏览     *\n");
		printf("*   4.学生信息查询     *\n");
		printf("*   5.退出             *\n");
		printf("************************\n");
		printf("请选择：");
		scanf("%d", &menu_select);
		switch (menu_select)
		{
		case 1://进入录入模块
			system("cls");
			input(A);
			save(A);
			break;
		case 2://进入修改模块
			system("cls");
			edit(A);
			save(A);
			break;
		case 3://进入浏览模块
			system("cls");
			output(A);
			break;
		case 4://进入查询模块
		{
			while (1)
			{
				system("cls");
				printf("欢迎使用学生信息管理系统\n\n");
				printf("**********菜单**********\n");
				printf("*   1.按学号查询     *\n");
				printf("*   2.按姓名查询     *\n");
				printf("*   0.退出           *\n");
				printf("请选择：");
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
					printf("请输入正确选项");
					getchar();
					getchar();

				};
				break;
			}
		}
		break;
		case 5://退出程序
			system("cls");
			return 0;
			break;
		default:
			printf("请输入正确选项");
			getchar();
			getchar();
			break;
		}
	}
	return 0;
}
int load(Linklist A)//加载程序当前目录下数据文件
{
	FILE *fp;
	long id;
	if (fp = fopen("data.txt", "r"), fp == NULL) //若文件不存在则新建一个
	{
		FILE *fp = fopen("data.txt", "w");
		return 0;
	}
	while (fscanf(fp, "%ld", &id) != EOF)//当成功读入一个整数
	{
		//为当前整数建立结点s
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
	Linklist p = A->next; //p指向首元结点

	fp = fopen("data.txt", "w");

	while (p) //储存数据到文件
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
		Linklist s, panduan;//申请新节点
		s = (Linklist)malloc(sizeof(Student));

		while (1)//进行录入
		{
			printf("请输入学号:");
			scanf("%ld", &s->id);
			t = 0;
			panduan = (Linklist)malloc(sizeof(Student));
			panduan = A->next;
			while (panduan)//判断学号是否重复
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
				printf("学号重复，请重新输入\n");
				continue;
			}
			else
				break;
		}
		printf("请输入姓名:");
		scanf("%s", &s->name);
		printf("请输入性别:");
		scanf("%s", &s->gender);
		while (1)//判断日期是否正确
		{
			printf("请输入出生年月日:");
			scanf("%d%d%d", &s->year, &s->month, &s->day);
			if ((s->year > year) || (s->year == year&&s->month > month) || (s->year == year, s->month == month, s->day > day))
			{
				printf("请输入正确日期\n");
				continue;
			}
			else
				age(s, s->year, s->month, s->day);
			break;
		}
		printf("地址:");
		scanf("%s", &s->address);
		printf("电话:");
		scanf("%s", &s->phone);
		printf("E-mail:");
		scanf("%s", &s->email);
		s->next = NULL;
		s->next = A->next;
		A->next = s;
		printf("是否继续添加(y/n):\n");
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
	p = A->next; //p指向首元结点
	printf("学号      姓名     年龄     性别          出生年月            地址                      电话               E-mail\n");
	while (p) //当p非空，输出p中的数据
	{

		printf("%-10ld%-10s%-10d%-10s%d年%d月%d日   %-30s%-15s%-15s\n", p->id, p->name, p->age, p->gender, p->year, p->month, p->day, p->address, p->phone, p->email);
		p = p->next;
	}
	printf("\n\n按任意键返回主菜单");
	getchar();
	getchar();
	system("cls");
	return 0;
}
int seach_id(Linklist A)
{
	int id, t = 0;
	printf("请输入学号");
	scanf("%ld", &id);
	Linklist p;
	p = (Linklist)malloc(sizeof(student));
	p = A->next;
	while (p)//对输入学号进行搜索，如果存在则输出数据
	{
		if (p->id == id)
		{
			system("mode con cols=130 lines=50  ");
			printf("学号      姓名     年龄     性别          出生年月            地址                      电话               E-mail\n");
			printf("%-10ld%-10s%-10d%-10s%d年%d月%d日   %-30s%-15s%-15s\n", p->id, p->name, p->age, p->gender, p->year, p->month, p->day, p->address, p->phone, p->email);
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
		printf("未查到学号为%d的学生", id);
		getchar();
		getchar();
	}
	return 0;
}
int seach_name(Linklist A)
{
	char name[20];
	int t = 0;
	printf("请输入姓名");
	scanf("%s", &name);
	Linklist p;
	p = (Linklist)malloc(sizeof(student));
	p = A->next;
	while (p)//对输入名字进行搜索，如果处在则输出数据
	{
		if (strcmp(p->name, name) == 0)
		{
			system("mode con cols=130 lines=50  ");
			printf("学号      姓名     年龄     性别          出生年月            地址                      电话               E-mail\n");
			printf("%-10ld%-10s%-10d%-10s%d年%d月%d日   %-30s%-15s%-15s\n", p->id, p->name, p->age, p->gender, p->year, p->month, p->day, p->address, p->phone, p->email);
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
		printf("未查到姓名为%s的学生", name);
		getchar();
		getchar();
	}
	return 0;
}
int age(Linklist p, int y, int m, int d)
{
	int day, month, year;//获取系统时间
	struct tm *ptr;
	time_t it;
	it = time(NULL);
	ptr = localtime(&it);
	day = ptr->tm_mday;
	month = ptr->tm_mon + 1;
	year = ptr->tm_year + 1900;

	if (y != year)//对年龄进行计算
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
	int day, month, year, t = 0;//获取系统时间存入变量
	struct tm *ptr;
	time_t it;
	it = time(NULL);
	ptr = localtime(&it);
	day = ptr->tm_mday;
	month = ptr->tm_mon + 1;
	year = ptr->tm_year + 1900;
	long i;
	printf("请输入要修改的学生学号：");
	scanf("%ld", &i);
	Linklist p;
	p = A->next;
	while (p) //查到学生
	{

		if (p->id == i)//判断输入的id是否与数据中的学生id相同
		{
			t = t + 1;
			int i;
			char ch = 'y';


			while (ch == 'y')//可以进行多次修改
			{
				system("cls");
				system("mode con cols=130 lines=50  ");
				printf("学号      姓名     年龄     性别          出生年月            地址                      电话               E-mail\n");
				printf("%-10ld%-10s%-10d%-10s%d年%d月%d日   %-30s%-15s%-15s\n", p->id, p->name, p->age, p->gender, p->year, p->month, p->day, p->address, p->phone, p->email);
				printf("请选择修改内容1.学号  2.姓名  3.性别  4.出生年月  5.地址  6.电话  7.E-mail  8.退出:\n");//根据用户输入选择修改内容

				scanf("%d", &i);
				switch (i)
				{
				case 1:
					Linklist panduan;
					int t, temp_id;
					while (1)
					{
						printf("修改学号为:");
						scanf("%ld", &temp_id);
						t = 0;
						panduan = (Linklist)malloc(sizeof(Student));
						panduan = A->next;
						while (panduan)//判断修改后的学号在系统中是否存在
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
							printf("学号重复，请重新输入\n");
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
					printf("修改姓名为");
					scanf("%s", &p->name);
					break;
				case 4:
					while (1)//判断日期是否正确
					{
						printf("修改出生年月日为:");
						scanf("%d%d%d", &p->year, &p->month, &p->day);
						if ((p->year > year) || (p->year == year&&p->month > month) || (p->year == year, p->month == month, p->day > day))
						{
							printf("请输入正确日期\n");
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
					printf("修改性别为：");
					scanf("%s", &p->gender);
					break;
				case 5:
					printf("修改地址为：");
					scanf("%s", &p->address);
					break;
				case 6:
					printf("修改电话为：");
					scanf("%s", &p->phone);
					break;
				case 7:
					printf("修改Email为");
					scanf("%s", &p->email);
					break;
				case 0:
					return 0;
				}
				if (i != 8)
				{
					printf("是否继续修改(y/n):");
					scanf(" %c", &ch);
				}
				else
					ch = 'n';
			}
			p = p->next;//指向后继结点
		}
		else
			p = p->next;//指向后继结点
	}
	if (t == 0)
	{
		printf("未找到学号为%ld的学生", i);
		getchar();
		getchar();
	}
	return 0;
}