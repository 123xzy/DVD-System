#ifndef FILM_H
#include<stdio.h>
#define MAXN 105
/*影碟信息*/
typedef struct film    
{
	char name[MAXN];    //影碟名称
	char national[MAXN];//国家
	int  type;           //类型
	int  quantity;        //数量
	char dir[MAXN];     //导演
	int  year;       //上映年份
}FILM;

/*用户信息*/
typedef struct user
{
	char account[MAXN];
	char password[MAXN];
	
}USER;

/*借阅信息*/
typedef struct userfilm
{
	char account[MAXN];
	char name[MAXN];
	int year;
	int month;
	int day;
	struct userfilm* next;
}Userfilm;

/*登录界面*/
void Menu1();

/*用户界面：查找，借阅，归还*/
void Menu2();

/*管理员界面：影碟修改，录入*/
void Menu3();

/*用户登录操作：输入用户名，密码*/
void Users_Login();

/*管理员登录操作*/
void Admin_Login();

/*用户界面*/
void UI();

/*管理员界面*/
void AdminI();

/*注册用户信息*/
void Users_Regis();

/*找回密码*/
void PassW_Retri(int);

/*添加影碟信息*/
void Addfilm();

/*输出所有影碟信息*/
void Film_Infor();

/*操作：根据影碟名称查询有关电影*/
void Find_Film();

/*展现用户信息（密码，借阅影碟）*/
void User_Infor();

/*借阅影碟*/
void Rent_Film();

/*归还影碟*/
void Return_Film();

/*修改影碟信息*/
void Alter_Film();

/*自定义getchar()函数*/
char getchar_s();

#endif // !LIST_H

#pragma once
