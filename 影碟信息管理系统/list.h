#ifndef FILM_H
#include<stdio.h>
#define MAXN 105
typedef struct film    /*影碟信息*/
{
	char name[MAXN];    //影碟名称
	char national[MAXN];//国家
	int  type;           //类型
	int  account;        //数量
	char dir[MAXN];     //导演
	int  year;       //上映年份
}FILM;

typedef struct user
{
	char account[MAXN];
	char password[MAXN];
	
}USER;

;

/*登录界面：显示用户登录，影碟修改，退出系统*/
void menu1();

/*用户界面：显示查找，借阅，归还，退出*/
void menu2();

/*会员登录操作：输入用户名，密码*/
void user_login();

/*用户*/
void main_user();

/*注册用户信息*/
void user_register();

/*找回密码*/
void find_password(char*,int);

/*添加影碟信息*/
void Addfilm();

/*输出所有影碟信息*/
void show();

/*操作：根据图书名称查询有关电影*/
void find();

/*展现用户信息（密码，借阅图书）*/
void show_user();

/*借书*/
void rent();

/*还书*/
void back();

/*修改影碟信息*/
void alter();

/*删除影碟,采用链表*/
void del();

/*自定义getchar()函数*/
char getchar_s();

#endif // !LIST_H

#pragma once
