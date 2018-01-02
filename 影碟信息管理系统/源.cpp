#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
int main()
{
	char choice;
	for (;;)
	{
		system("cls");
		Menu1();
		choice = getchar_s();
		while (choice > '6' || choice < '1')
		{
			printf("请输入正确的选择（1-6）:");
			choice = getchar_s();
		}
		if (choice == '1')
		{
			Users_Login();
			UI();
		}
		else if (choice == '2')
		{
			if(Users_Regis()) UI();
		}
		else if (choice == '3')
			Find_Film();
		else if (choice == '4')
		{
			Film_Infor();
			printf("按任意键退出浏览"); 
			getchar();
		}
		else if (choice == '5')
		{
			Admin_Login();
			AdminI();
		}
		else if (choice == '6')
		{
			printf("按任意键退出系统");
			getchar();
			exit(1); 
		}
	}
	return 0;
}