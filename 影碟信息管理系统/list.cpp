#include<stdio.h>
#include<string.h>
#include<Windows.h>
#include<time.h>
#include "list.h"
#define KEY 1999  
/*是否循环*/
static bool judge();

void menu1()
{
	printf("********影碟管理系统********\n");
	printf("       1.会员登录\n");
	printf("       2.会员注册\n");
	printf("       3.影碟查找\n");
	printf("       4.影碟信息修改\n");
	printf("       5.影碟信息浏览\n");
	printf("       6.影碟信息录入\n");
	printf("       7.退出系统\n");
	printf("***************************\n");
	printf("请选择（1-7）：");
}
void menu2()
{
	printf("*********会员界面**********\n");
	printf("      1.查询账户信息\n");
	printf("      2.借阅\n");
	printf("      3.归还\n");
	printf("      4.退出会员界面\n");
	printf("****************************\n");
	printf("请选择（1-4）：");
}
void user_login()
{
	int flag=1;
	int count = 0;
	FILE *fp;
	int num, i;
	fp = fopen("user_date.txt", "r");
	USER user[MAXN];
	for (num = 0; !feof(fp); num++)
		fscanf(fp, "%s%s", user[num].account, user[num].password);
	fclose(fp);
	USER olduser;
	while (flag)
	{
		printf("账户：");
		gets_s(olduser.account);
		for (i = 0; i < num; i++)
			if (!strcmp(olduser.account, user[i].account))
			{
				flag = 0; break;
			}
		if (i == num) {
			printf("该账户不存在！是否注册新用户（Y/N）：");
			if (judge())
			{
				user_register(); return;
			}
		}
	}
	printf("密码：");
	for (;;) {
		gets_s(olduser.password);
		if (!strcmp(olduser.password, user[i].password))
		{
			printf("正在登陆...");
			Sleep(600); 
			return;
		}
		else
		{
			count++;
			if (count >= 3) 
			{ 
				printf("是否找回密码（Y/N)：");
				if (judge())
				{find_password(olduser.account, i); return;}
			}
			else 
			{
				printf("账户或密码错误！\n");
				printf("请重新输入密码：");
			}
		}
	}	
	
}
void main_user()
{
	char choice;
	int flag = 1;
	while (flag) {
		system("cls");
		menu2();
		choice= getchar_s();
		while (choice > '5' || choice < '1')
		{
			printf("请输入正确的选择:");
			choice = getchar_s();
		}
		switch (choice)
		{
		case'1':show_user(); break;
		case'2':rent(); break;
		case'3':back(); break;
		case'4':flag = 0; break;
		}
	}
}
void user_register()
{
	USER user[MAXN];
	FILE *fp;
	int flag=1;
	fp = fopen("user_date.txt", "r+");
	USER new_user;
	int num;
	for (num = 0;!feof(fp); num++)
		fscanf(fp, "%s%s", user[num].account, user[num].password);
	printf("输入新的用户名：");
	while(flag) {
		scanf("%s", new_user.account);
		for (int i = 0; i < num; i++)
		{
			if (!strcmp(new_user.account, user[i].account))
			{
				printf("该用户名已经存在！请重新输入！"); break;
			}
			else flag = 0;
		}
	}
	printf("输入新的密码：");
	scanf("%s", new_user.password);
	getchar();
	printf("确认注册（Y/N）：");
	if (judge())
	{
		fprintf(fp, "%s %s\n", new_user.account, new_user.password);
		fclose(fp);
		printf("注册成功！"); printf("正在跳转..."); Sleep(700);
	}
	else printf("注册失败！");
}
void find_password(char* olduser,int i)
{
	int code;
	FILE* fp;
	char new_password1[MAXN];
	char new_password2[MAXN];
	int num;
	fp = fopen("user_date.txt", "r+");
	USER user[MAXN];
	for (num = 0; !feof(fp); num++)
		fscanf(fp, "%s%s", user[num].account, user[num].password);
	printf("请输入验证码：");
	scanf("%d", &code);
	while (code != KEY) { scanf("%d", &code); printf("验证码错误！"); }
	printf("请输入新的密码：");
	scanf("%s", new_password1);
	printf("再输入一次新密码：");
	scanf("%s", new_password2);
	if (strcmp(new_password1,new_password2))printf("两次密码不同，请重新输入：");
	else strcpy(user[i].password , new_password1);
	rewind(fp);
	for (int j = 0; j < num; j++)
		fprintf(fp, "%s %s\n", user[j].account, user[j].password);
	fclose(fp);
	printf("修改密码成功！正在跳转...");
	Sleep(500);
	return;
}
void Addfilm()
{
	FILM newfilm;
	FILE *fp;
	for (;;)
	{
		printf("请输入影碟名称：");
		scanf("%s", newfilm.name);
		printf("请输入国家：");
		scanf("%s", newfilm.national);
		printf("请输入类型:1-爱情 2-动作：");
		scanf("%d", &newfilm.type);
		printf("请输入数量：");
		scanf("%d", &newfilm.account);
		printf("请输入导演：");
		scanf("%s", newfilm.dir);
		printf("请输入上映时间：");
		scanf("%d", &newfilm.year);
		getchar();
		printf("是否保存该影碟信息（Y/N）：");
		if (judge())
		{
			fp = fopen("film_date.txt", "a");
			fprintf(fp, "%s %s %d %d %s %d\n", newfilm.name, newfilm.national, newfilm.type, newfilm.account, newfilm.dir, newfilm.year);
			fclose(fp);
			printf("保存成功!\n");
		}
		else printf("未保存！\n");
		printf("是否继续输入?（Y/N）：");
		if (judge())continue;
		else return;
	}
}
void show()
{
	FILE *fp;
	int num=0;
	FILM filmlist[MAXN];
	fp = fopen("film_date.txt", "r");
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%d%d%s%d", filmlist[num].name, filmlist[num].national, &filmlist[num].type, &filmlist[num].account, filmlist[num].dir, &filmlist[num].year);
		num++;
	}
	fclose(fp);
	if (num == 0)printf("当前库存为零");
	else {
		printf("*****************图书信息*****************\n");
		printf("影碟名     国家  类型  数量  导演  上映时间\n");
		num--;
		while (num--)
			printf("%-10s%5s%5d%5d%10s%5d\n", filmlist[num].name, filmlist[num].national, filmlist[num].type, filmlist[num].account, filmlist[num].dir, filmlist[num].year);
	}
	printf("按任意键退出浏览");
	getchar();
}
void find()
{
	char choice;
	FILM find_film;
	FILE *fp;
	FILM filmlist[MAXN];
	int num = 0,flag=1;
	fp = fopen("film_date.txt", "r+");
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%d%d%s%d", filmlist[num].name, filmlist[num].national, &filmlist[num].type, &filmlist[num].account, filmlist[num].dir, &filmlist[num].year);
		num++;
	}
	fclose(fp);
	for (;;)
	{
		printf("请选择查询条件(1-名称 2-导演)：\n");
		choice = getchar_s();
		printf("请输入查询信息：");
		switch (choice)
		{
		case'1':gets_s(find_film.name); flag = 0; break;
		case'2':gets_s(find_film.dir); flag = 0; break;
		default:
			printf("请输入（1-2）：");
			getchar_s();
		}
		int flag = 0;
		switch (choice)
		{

		case '1':
			printf("*****************图书信息*****************\n");
			printf("影碟名     国家  类型  数量  导演  上映时间\n");
			for (int i = 0; i < num; i++)
			{

				if (strcmp(find_film.name, filmlist[i].name) == 0)
				{
					printf("%-10s%5s%5d%5d%10s%5d\n", filmlist[i].name, filmlist[i].national, filmlist[i].type, filmlist[i].account, filmlist[i].dir, filmlist[i].year);
					flag = 1;
				}
			}
			if (flag == 0)printf("没有符合条件的电影！"); break;
		case '2':
			printf("*****************图书信息*****************\n");
			printf("影碟名     国家  类型  数量  导演  上映时间\n");
			for (int i = 0; i < num; i++)
			{
				if (strcmp(find_film.dir, filmlist[i].dir) == 0)
				{
					printf("%-10s%5s%5d%5d%10s%5d\n", filmlist[i].name, filmlist[i].national, filmlist[i].type, filmlist[i].account, filmlist[i].dir, filmlist[i].year);
					flag = 1;
				}
			}
			if (flag == 0)printf("没有符合条件的电影！"); break;
		default:
			break;
		}
		printf("\n是否继续查询（Y/N）：");
		if (judge())continue;
		else { printf("按任意键退出查找"); getchar(); return; }
	}
}
void show_user()
{
	char user[MAXN];
	FILE *fp;
	fp = fopen("user.txt", "r");


}
void rent() 
{
	FILM filmlist[MAXN];
	int num = 0;
	int select;
	FILE *fp = fopen("film_date.txt", "a+");
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%d%d%s%d", filmlist[num].name, filmlist[num].national, &filmlist[num].type, &filmlist[num].account, filmlist[num].dir, &filmlist[num].year);
		num++;
	}
	fclose(fp);
	printf("当前可借的影碟：\n");
	int count = 1;
	printf("编号   影碟名    库存\n");
	for (int i = 0; i<num - 1; i++)
	{
		if(filmlist[i].account==0)
			printf("%-6d%-11s%-5d不可借\n",i+1, filmlist[i].name, filmlist[i].account);
		else printf("%-6d%-11s%-5d可借\n", i + 1, filmlist[i].name, filmlist[i].account);
	}
	puts("借阅规则：每天5元");
	printf("输入您想借阅的电影编号:\n");
	for (;;) {
		scanf("%d", &select);
		getchar();
		if ( select>num-1  ||  select< 1)
			printf("请输入正确的编号:");
		else {
			while (filmlist[select-1].account == 0)
			{
				printf("该影碟不可借！\n请重新输入：");
				scanf("%d", &select);
				getchar();
			}
			printf("确认借阅（Y/N)");
			if (judge()) {
				filmlist[(select) - 1].account--;
				fp = fopen("film_date.txt","w");
				for (int i = 0; i<num - 1; i++)
					fprintf(fp,"%s %s %d %d %s %d\n",filmlist[i].name, filmlist[i].national, filmlist[i].type, filmlist[i].account, filmlist[i].dir, filmlist[i].year);
				fclose(fp);
				printf("借阅成功!");
				printf("继续借阅（Y/N）：");
				if (judge())continue;
				else { printf("按任意键退出借阅！"); getchar(); return; }
			}
			else { printf("借阅失败！"); return; }
		}
	}
}
void back()
{
	int y1, m1, d1, y, m, d;
	time_t t;
	struct tm * lt;
	time(&t);			//获取Unix时间戳
	lt = localtime(&t); //转为时间结构
	y1 = y = lt->tm_year + 1900;
	m1 = m = lt->tm_mon + 1;
	d1 = d = lt->tm_mday;
	int time;
	scanf("%d", &time);
	switch (time)
	{
	case 1:d = d1 + 7; break;
	case 2:d = d1 + 14; break;
	case 3:m = m1 + 1;	break;
	}
	if (d>30)
	{
		d -= 30;
		m++;
	}
	if (m>12)
	{
		m = 1;
		y++;
	}
	printf("归还日期为：%d年%d月%d日\n", y, m, d);
}
void alter()
{
	FILE *fp;
	int num = 0;
	FILM filmlist[MAXN];
	fp = fopen("film_date.txt", "r+");
	while (!feof(fp))
	{
		num++;
		fscanf(fp, "%s%s%d%d%s%d", filmlist[num].name, filmlist[num].national, &filmlist[num].type, &filmlist[num].account, filmlist[num].dir, &filmlist[num].year);
	}
	num--;
	printf("*******************图书信息***********************\n");
	printf("编号  影碟名     国家  类型  库存  导演  上映时间\n");
	for (int i = 1; i <= num; i++)
		printf("%-5d%-10s%5s%5d%5d%10s%5d\n", i, filmlist[i].name, filmlist[i].national, filmlist[i].type, filmlist[i].account, filmlist[i].dir, filmlist[i].year);
	int choice1, choice2;
	printf("请选择影碟编号(1-%d)及修改类型(1-库存 2-上映时间)：\n", num);
	int flag = 1;
	for (;;)
	{
		do {
			flag = 1;
			scanf("%d%d", &choice1, &choice2);
			switch (choice2)
			{
			case 1:printf("原数据：%s %d\n", filmlist[choice1].name, filmlist[choice1].account);
				printf("请输入新的库存："); scanf("%d", &filmlist[choice1].account); break;
			case 2:printf("原数据：%s %d\n", filmlist[choice1].name, filmlist[choice1].year);
				printf("请输入新的上映时间："); scanf("%d", &filmlist[choice1].year); break;
			default:printf("请重新输入："); flag = 0; break;
			}
		} while (flag == 0);
		if (judge())continue;
		else break;
	}
	rewind(fp);
	for (int j = 1; j <= num; j++)
		fprintf(fp, "%s %s %d %d %s %d\n", filmlist[j].name, filmlist[j].national, filmlist[j].type, filmlist[j].account, filmlist[j].dir, filmlist[j].year);
	fclose(fp);
	printf("修改成功！"); printf("正在跳转..."); Sleep(700);
	getchar();
}
char getchar_s()
{
	char ret_val;
	ret_val = getchar();
	while (getchar() != '\n')
		continue;
	return ret_val;
}
bool judge()
{
	char choice;
	choice = getchar_s();
	if (choice == 'y' || choice == 'Y')return true;
	else return false;
}