#ifndef _DATA_H
#define _DATA_H

#include <stdio.h>

//用户结构体 
typedef struct {
	int id;//用户ID 
	char name[7];//用户名 
	char passwd[7];//密码 
	int role;//角色：1-管理员 2-考生 
	int state;//状态：1-可用 0-被删除 
}USER_T;//28字节 

extern USER_T user[100];
extern int userNum;//当前用户数 
extern int loginIndex;//当前登录用户下标 

/*
函数名:initUsers
函数功能:打开文件，若文件不存在，则自动创建，
		 并写入初始化数据实现对文件的初始化
函数参数:无
返回值:无
*/
extern void initUsers();//初始化用户

/*
函数名:appendDataToFile
函数功能:追加数据到文件末
函数参数:data--写入文件的数据的地址
		 len--写入文件的数据长度
		 filepath--写入文件的路径 
返回值:无
*/
extern void appendDataToFile(void* data, int len, char* filepath);//将数据添加到文件末 

/*
函数名:updateDataToFile
函数功能:局部更新数据到文件 
函数参数:data--写入文件的数据的地址
		 len--写入文件的数据长度
		 filepath--写入文件的路径 
		 offset--文件指针的偏移量 
返回值:无
*/
extern void updateDataToFile(void* data, int len, char* filepath, int offset);

//考题结构体
typedef struct {
    int id;//考题编号
    char subject[100];//题目类型 
    char title[100];//题目
    int score;//分值
    char option[10][100];//选项
    int optionNum;//选项个数
    char answer[2];//答案
    char analysis[100];
}QUESTION_T;

extern QUESTION_T question[100];
extern int questionNum;//题目数 
extern int changeQuestionIndex;//修改题目的下标

/*
函数名:initQuestions
函数功能:打开文件，若文件不存在，则自动创建，
		 并写入初始化数据实现对文件的初始化
函数参数:无
返回值:无
*/
extern void initQuestions();//初始化题目 


//考试记录结构体
typedef struct {
	int id;//考生ID
	char name[8];//名字
	char time[20];//考试时间
	int score;//分数
}EXAMRECORD_T;

extern EXAMRECORD_T examrecord[100];
extern int examrecordNum;//考试记录数 

/*
函数名:initExamRecords
函数功能:打开文件，若文件不存在，则自动创建
函数参数:无
返回值:无
*/
extern void initExamRecords();

//考卷结构体
typedef struct {
	int id;//考卷ID
	char title[20];//考卷名称 
	char date[20];//考卷发布日期 
	int score;//试卷总分
	int num;//试卷总题数
	int questionId[20];//试卷题目id
}EXAMPAPER_T;

extern EXAMPAPER_T exampaper[100];
extern int exampaperNum;//考卷数 
extern int ExamPaperIndex;//当前考卷下标 
/*
函数名:initExamPapers
函数功能:打开文件，若文件不存在，则自动创建
函数参数:无
返回值:无
*/
extern void initExamPapers();

#endif
