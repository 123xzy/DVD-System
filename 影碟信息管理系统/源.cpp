#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
#define TSIZE 45
int main()
{
	char choice1;
	for (;;)
	{
		system("cls");
		menu1();
		choice1 = getchar_s();
		while (choice1 > '7' || choice1 < '1')
		{
			printf("请输入正确的选择（1-6）:");
			choice1 = getchar_s();
		}
		if (choice1 == '1')
		{
			user_login();
			main_user();
		}
		else if (choice1 == '2')
		{user_register(); main_user();}
		else if (choice1 == '3')
			find();
		else if (choice1 == '4')
			alter();
		else if (choice1 == '5')
			show();
		else if (choice1 == '6')
			Addfilm();
		else if (choice1 == '7')
		{
			printf("确定退出系统（按任意键退出）");
			getchar();
			exit(1); 
		}
	}
	return 0;
}