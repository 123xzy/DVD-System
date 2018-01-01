#include<stdio.h>
#include<string.h>
#include<Windows.h>
#include<time.h>
#include "list.h"
#define KEY 1999  

/*是否循环*/
static bool judge();

/*计算相隔几天*/
static int Total_Days(int year, int month, int days);

FILM filmlist[MAXN];  //所有影碟信息
FILE *fp;
USER user[MAXN];      //所有用户信息
USER User;            //当前用户信息
Userfilm user_film[MAXN];//用户借阅信息

void Menu1()
{
	printf("********影碟管理系统********\n");
	printf("       1.会员登录\n");
	printf("       2.会员注册\n");
	printf("       3.影碟查找\n");
	printf("       4.影碟信息浏览\n");
	printf("       5.管理员登录\n");
	printf("       6.退出系统\n");
	printf("***************************\n");
	printf("请选择（1-6）：");
}
void Menu2()
{
	printf("*********会员界面**********\n");
	printf("      1.查询账户信息\n");
	printf("      2.借阅影碟\n");
	printf("      3.归还影碟\n");
	printf("      4.退出会员界面\n");
	printf("****************************\n");
	printf("请选择（1-4）：");
}
void Menu3()
{
	printf("*********管理员界面**********\n");
	printf("      1.影碟信息修改\n");
	printf("      2.影碟信息录入\n");
	printf("      3.退出管理员界面\n");
	printf("****************************\n");
	printf("请选择（1-3）：");
}
void Users_Login()
{
	int num;
	fp = fopen("user_date.txt", "r");
	for (num = 1; !feof(fp); num++)
		fscanf(fp, "%s%s", user[num].account, user[num].password);

	int flag=1;
	int count = 0;
	int i;

	//输入账户
	while (flag)
	{
		
		printf("账户：");
		gets_s(User.account);
		for (i = 1; i <= num; i++)
			if (!strcmp(User.account, user[i].account))
			{
				flag = 0; break;
			}
		
		//用户不存在时，选择注册
		if (i == ++num)
		{
			printf("该账户不存在！是否注册新用户（Y/N）：");
			if (judge())
			{
				Users_Regis(); return;
			}
		}
	}
	//输入密码
	for (;;) {
		printf("密码：");
		gets_s(User.password);
		if (!strcmp(User.password, user[i].password))
		{
			printf("正在登陆...");
			Sleep(600); 
			return;
		}
		
		//连续三次输错密码时，选择找回密码
		else
		{
			count++;
			if (count >= 3) 
			{ 
				printf("是否找回密码（Y/N)：");
				if (judge())
				{PassW_Retri(i); return;}
			}
			else 
			{
				printf("账户或密码错误！\n");
				printf("请重新输入密码：");
			}
		}
	}	
	
}
void Admin_Login()
{
	int code;
	printf("输入KEY：");
	scanf("%d", &code);
	getchar();
	while (code != KEY) { scanf("%d", &code); printf("验证码错误！"); }
	printf("登录成功！正在跳转...");
	Sleep(500);
	return;
}
void UI()
{
	char choice;
	for(;;){
		system("cls");
		Menu2();
		choice= getchar_s();
		while (choice > '5' || choice < '1')
		{
			printf("请输入正确的选择:");
			choice = getchar_s();
		}
		switch (choice)
		{
		case'1':User_Infor(); break;
		case'2':Rent_Film(); break;
		case'3':Return_Film(); break;
		case'4':return;
		}
	}
}
void AdminI()
{
	char choice;
	for (;;) {
		system("cls");
		Menu3();
		choice = getchar_s();
		while (choice > '3' || choice < '1')
		{
			printf("请输入正确的选择:");
			choice = getchar_s();
		}
		switch (choice)
		{
		case'1':Alter_Film(); break;
		case'2':Addfilm(); break;
		case'3':printf("按任意键退出管理员系统");getchar(); return;
		}
	}
}
void Users_Regis()
{
	int flag=1,num;
	fp = fopen("user_date.txt", "r+");
	for (num = 1; !feof(fp); num++)
		fscanf(fp, "%s%s", user[num].account, user[num].password);
	printf("输入新的用户名：");
	while(flag) {
		scanf("%s", User.account);
		for (int i = 1; i <= num; i++)
		{
			if (!strcmp(User.account, user[i].account))
			{
				printf("该用户名已经存在！请重新输入！"); break;
			}
			else flag = 0;
		}
	}
	printf("输入新的密码：");
	scanf("%s", User.password);
	getchar();
	printf("确认注册（Y/N）：");
	if (judge())
	{
		fprintf(fp, "%s %s\n", User.account,User.password);
		fclose(fp);
		printf("注册成功！"); printf("正在跳转..."); Sleep(700);
	}
	else printf("注册失败！"); fclose(fp);
}
void PassW_Retri(int i)
{
	int code;
	char new_password1[MAXN];
	char new_password2[MAXN];
	int  num;
	fp = fopen("user_date.txt", "r+");
	for (num = 1; !feof(fp); num++)
		fscanf(fp, "%s%s", user[num].account, user[num].password);
	
	//验证两次的密码
	printf("请输入新的密码：");
	fgets(new_password1, MAXN, stdin);
	printf("再输入一次新密码：");
	fgets(new_password2, MAXN, stdin);
	while (strcmp(new_password1, new_password2)) 
	{ 
		printf("两次密码不同！\n");
		printf("请输入新的密码：");
		fgets(new_password1, MAXN, stdin);
		printf("再输入一次新密码：");
		fgets(new_password2, MAXN, stdin);
	}

	strcpy(user[i].password , new_password1);
	rewind(fp);
	for (int j = 1; j <=num; j++)
		fprintf(fp, "%s %s\n", user[j].account, user[j].password);
	fclose(fp);
	printf("修改密码成功！正在跳转...");
	Sleep(500);
	return;
}
void Addfilm()
{
	FILM newfilm;
	int  num;
	fp = fopen("film_date.txt", "a+");
	for (;;)
	{
		printf("请输入影碟名称：");
		scanf("%s", newfilm.name);
		printf("请输入国家：");
		scanf("%s", newfilm.national);
		printf("请输入类型:1-爱情 2-动作：");
		scanf("%d", &newfilm.type);
		printf("请输入数量：");
		scanf("%d", &newfilm.quantity);
		printf("请输入导演：");
		scanf("%s", newfilm.dir);
		printf("请输入上映时间：");
		scanf("%d", &newfilm.year);
		getchar();
		printf("是否保存该影碟信息（Y/N）：");
		if (judge())
		{
			fprintf(fp, "%s %s %d %d %s %d\n", newfilm.name, newfilm.national, newfilm.type, newfilm.quantity, newfilm.dir, newfilm.year);
			printf("保存成功!\n");fclose(fp);
		}
		else printf("未保存！\n");
		printf("是否继续输入?（Y/N）：");
		if (judge())continue;
		else  return; 
	}
}
void Film_Infor()
{
	int num=0;
	fp = fopen("film_date.txt", "r");
	while (!feof(fp))
	{
		num++;
		fscanf(fp, "%s%s%d%d%s%d\n", filmlist[num].name, filmlist[num].national, &filmlist[num].type, &filmlist[num].quantity, filmlist[num].dir, &filmlist[num].year);
	}
	if (num == 0)printf("当前库存为零");
	else {
		printf("*******************图书信息*******************\n");
		printf("编号  影碟名  国家  类型  数量  导演  上映时间\n");
		for(int i=1;i<=num;i++)
			printf("%-5d%-10s%5s%5d%5d%10s%5d\n",i, filmlist[i].name, filmlist[i].national, filmlist[i].type, filmlist[i].quantity, filmlist[i].dir, filmlist[i].year);
	}
	fclose(fp);
}
void Find_Film()
{
	char choice;
	FILM find_film;
	int flag=1,num;
	fp = fopen("film_date.txt", "r");
	for (num = 1; !feof(fp); num++)
		fscanf(fp, "%s%s%d%d%s%d\n", filmlist[num].name, filmlist[num].national, &filmlist[num].type, &filmlist[num].quantity, filmlist[num].dir, &filmlist[num].year);
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
					printf("%-10s%5s%5d%5d%10s%5d\n", filmlist[i].name, filmlist[i].national, filmlist[i].type, filmlist[i].quantity, filmlist[i].dir, filmlist[i].year);
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
					printf("%-10s%5s%5d%5d%10s%5d\n", filmlist[i].name, filmlist[i].national, filmlist[i].type, filmlist[i].quantity, filmlist[i].dir, filmlist[i].year);
					flag = 1;
				}
			}
			if (flag == 0)printf("没有符合条件的电影！"); break;
		default:
			break;
		}
		printf("\n是否继续查询（Y/N）：");
		if (judge())continue;
		else 
		{ 
			fclose(fp); 
			printf("按任意键退出查找"); getchar();return;
		}
	}
}
void User_Infor()
{
	FILE*fp = fopen("rent_back.txt", "rb");
	struct userfilm*head=NULL,*current,*prev;
	int num = 0;
	//将文件中已有信息形成链表
	while(!feof(fp))//读到文件结尾
	{
		current = (userfilm*)malloc(sizeof(userfilm));
		if(fread(current, sizeof(userfilm), 1, fp)==0)break;
		if(head ==NULL)head=current;  
		else prev->next=current;   
		current->next = NULL;                    //表明这是链表最后一项
		prev = current;                           //current完成使命，即成为上一项
	}
	//打印链表信息
	current = head;
	while (current!= NULL){
		//输出当前用户的借阅信息 
		if(!strcmp(current->account,User.account))
			printf("%d %s %s %d年%d月%d日\n",++num, current->account, current->name, current->year, current->month, current->day);
		current = current->next;
	} 
	if (num == 0)printf("你未借阅任何书籍！");
	fclose(fp);
	printf("按任意键退出");
	getchar();
	return;
}
void Rent_Film() 
{
	//获取当前时间
	time_t t;
	struct tm * lt;
	time(&t);
	lt = localtime(&t);
	int y = lt->tm_year + 1900;
	int m = lt->tm_mon + 1;
	int d = lt->tm_mday;

	//展示电影名单
	Film_Infor();
	
	//暂存借阅电影
	userfilm User_film; 
	
	struct userfilm*current;
	
	//打开电影文件
	int num=0;
	fp = fopen("film_date.txt", "r+");
	while (!feof(fp))
	{
		num++;
		fscanf(fp, "%s%s%d%d%s%d\n", filmlist[num].name, filmlist[num].national, &filmlist[num].type, &filmlist[num].quantity, filmlist[num].dir, &filmlist[num].year);
	}

	//打开借阅文件
	FILE* rent_back = fopen("rent_back.txt", "a+");
	
	printf("每天三元\n");
	for(;;)
	{
		
		printf("输入您想借阅的电影编号：");
		int seqnum;//借阅电影序号
		current= (userfilm*)malloc(sizeof(userfilm));
		strcpy(current->account, User.account);
		scanf("%d", &seqnum);
		getchar();
		strcpy(current->name, filmlist[seqnum].name);
		filmlist[seqnum].quantity--;
		current->year = y;
		current->month= m;
		current->day= d;
		fwrite(current, sizeof(userfilm), 1, rent_back);//将结构体信息写入文件
		printf("借阅成功!");
		printf("是否继续借阅（Y/N）：");
		if (judge())continue;
		else break;
	}
	fclose(rent_back);
	rewind(fp);
	for (int j = 1; j <= num; j++)
		fprintf(fp, "%s %s %d %d %s %d\n", filmlist[j].name, filmlist[j].national, filmlist[j].type, filmlist[j].quantity, filmlist[j].dir, filmlist[j].year);
	fclose(fp);
	return;
} 
void Return_Film()
{
	int num = 0;

	//将当前用户和其他用户分成两条链表
	struct userfilm*head1 = NULL,*prev1;
	struct userfilm*head2 = NULL, *prev2;
	struct userfilm* current;
	for (;;)
	{
		//打开电影文件
		fp = fopen("film_date.txt", "r+");
		while (!feof(fp))
		{
			num++;
			fscanf(fp, "%s%s%d%d%s%d\n", filmlist[num].name, filmlist[num].national, &filmlist[num].type, &filmlist[num].quantity, filmlist[num].dir, &filmlist[num].year);
		}

		//将文件中所有用户的信息形成链表
		FILE*fp2 = fopen("rent_back.txt", "rb+");
		while (!feof(fp2))                      //读到文件结尾,这里有坑，feod会多读一项
		{
			current = (userfilm*)malloc(sizeof(userfilm));
			if (fread(current, sizeof(userfilm), 1, fp2) == 0)break;
			if (!strcmp(current->account, User.account))
			{
				if (head1 == NULL)head1 = current;
				else prev1->next = current;
				current->next = NULL;                    //表明这是链表最后一项
				prev1 = current;                          //current完成使命，即成为上一项
			}
			else
			{
				if (head2 == NULL)head2 = current;
				else prev2->next = current;
				current->next = NULL;
				prev2 = current;
			}
		}
		fclose(fp2);

		int choice;

		//输出当前用户的借阅信息
		current = head1; num = 0;
		do {
			if (!strcmp(current->account, User.account))
				printf("%d %s %s %d年%d月%d日\n", ++num, current->account, current->name, current->year, current->month, current->day);
			current = current->next;
		} while (current != NULL);

		//选择归还

		printf("选择归还(1-%d):", num);
		scanf("%d", &choice);
		while (choice<1 && choice>num)
		{
			printf("错误！重新选择:");
			scanf("%d", &choice);
		}
		int j = 1; current = head1;
		while (current != NULL)
		{
			if (choice == 1) { head1 = current->next; break; }//选择归还第一个，直接改变表头
			else {
				if ((choice - 1) == j) {
					current->next = current->next->next; break;
				}
				else  current = current->next;
			}
			j++;
		}
		
		fp2 = fopen("rent_back.txt", "w");//间接达到清空文件的目的
		//将当前用户信息存档
		current = head1;
		while (current != NULL)
		{
			fwrite(current, sizeof(userfilm), 1, fp2);
			current = current->next;
		}
		//将其他用户信息存档
		current = head2;
		while (current != NULL)
		{
			fwrite(current, sizeof(userfilm), 1, fp2);
			current = current->next;
		}
		fclose(fp2);
		fclose(fp);
		
		//是否继续
		printf("归还成功！是否继续归还（Y/N）:");
		if (judge())continue;
		else break;
	}
	printf("正在跳转...");
	Sleep(300);
	return;
}
void Alter_Film()
{
	int num=0;
	fp = fopen("film_date.txt", "r+");
	while (!feof(fp))
	{
		num++;
		fscanf(fp, "%s%s%d%d%s%d\n", filmlist[num].name, filmlist[num].national, &filmlist[num].type, &filmlist[num].quantity, filmlist[num].dir, &filmlist[num].year);
	}
	printf("*******************图书信息***********************\n");
	printf("编号  影碟名     国家  类型  库存  导演  上映时间\n");
	for (int i = 1; i <= num; i++)
		printf("%-5d%-10s%5s%5d%5d%10s%5d\n", i, filmlist[i].name, filmlist[i].national, filmlist[i].type, filmlist[i].quantity, filmlist[i].dir, filmlist[i].year);
	int choice1, choice2;
	
	int flag = 1;
	for (;;)
	{
		printf("请选择需修改的影碟编号(1-%d)及修改类型(1-库存 2-上映时间)：\n", num);
		do {
			flag = 1;
			scanf("%d%d", &choice1, &choice2);
			switch (choice2)
			{
			case 1:printf("原数据：%s %d\n", filmlist[choice1].name, filmlist[choice1].quantity);
				printf("请输入新的库存：");
				scanf("%d", &filmlist[choice1].quantity); getchar(); break;
			case 2:printf("原数据：%s %d\n", filmlist[choice1].name, filmlist[choice1].year);
				printf("请输入新的上映时间："); 
				scanf("%d", &filmlist[choice1].year); getchar(); break;
			default:printf("请重新输入："); flag = 0; break;
			}
		} while (flag == 0);
		printf("是否继续修改（Y/N）：");
		if (judge())continue;
		else break;
	}
	rewind(fp);
	for (int j = 1; j <= num; j++)
		fprintf(fp, "%s %s %d %d %s %d\n", filmlist[j].name, filmlist[j].national, filmlist[j].type, filmlist[j].quantity, filmlist[j].dir, filmlist[j].year);
	fclose(fp);
	printf("修改成功！正在跳转...");
	Sleep(700);
	return;
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
int Total_Days(int year, int month, int days)
{
	//获取当前时间
	time_t t;
	struct tm * lt;
	time(&t);
	lt = localtime(&t);
	int y = lt->tm_year + 1900;
	int m = lt->tm_mon + 1;
	int d = lt->tm_mday;
}