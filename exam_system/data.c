#include "include/data.h"

USER_T user[100] = {0};

int userNum = 0;//当前用户数 
int loginIndex = 0;//当前登录用户下标 

//初始化用户
//判断user.dat文件是否存在
//若已存在，则直接读取文件中的初始数据，并保存到user数组中 
//若不存在，则新建user.dat文件，并将初始的两个用户信息保存到文件中 
void initUsers(){
	USER_T initUser[2] = { {1001,"admins","123456",1,1},
					 	   {1002,"examer","123456",2,1} };
	FILE* fp = fopen("data/user.dat","rb+");
	if(fp == NULL){
		fp = fopen("data/user.dat","wb+");
		fwrite(initUser, sizeof(USER_T), 2, fp);
	}
	//从文件中读取用户信息并保存到user数组中 
	rewind(fp);
	while(fread(&user[userNum], sizeof(USER_T), 1, fp)){
		userNum++;
	}
	fclose(fp);
} 

void appendDataToFile(void* data, int len, char* filepath){
	FILE* fp = fopen(filepath,"ab+");
	fwrite(data, len, 1, fp);
	fclose(fp);
} 

void updateDataToFile(void* data, int len, char* filepath, int offset){
	FILE* fp = fopen(filepath,"rb+");
	fseek(fp, offset, SEEK_SET);
	fwrite(data, len, 1, fp);
	fclose(fp);
} 

QUESTION_T question[100] = {0};
int questionNum = 0; //题目数 
int changeQuestionIndex = 0;//修改题目的下标

//初始化题目 
//判断question.dat文件是否存在
//若已存在，则直接读取文件中的初始数据，并保存到question数组中 
//若不存在，则新建question.dat文件，并将初始的五个题目信息保存到文件中 
void initQuestions(){
	QUESTION_T initQuestion[5] = {
        {1,"C语言考试","以下对C语言的描述中，正确的是（）",20,
            {"A）Ｃ语言源程序中可以有重名的函数","B）一个C项目可以有一个或多个.c文件构成","C）最小的C语言源程序中没有任何内容","D）一行只能写一条语句"},4,'B'},
        {2,"C语言考试","Ｃ语言程序的模块化是通过以下哪个选项实现的（）",20,
            {"A）变量","B）语句","C）函数","D）程序行"},4,'C'},
        {3,"C语言考试","以下选项中叙述正确的是（）",20,
            {"A）函数体必须由 { 开始","B）C 程序必须由 main 语句开始","C）C 程序中的注释可以嵌套","D）C 程序中的注释必须在一行完成"},4,'A'},
        {4,"C语言考试","在16位系统中，C语言中，错误的int类型的常数的是（）",20,
            {"A）32768","B）0","C）037","D）0xAF"},4,'A'},
        {5,"C语言考试","Ｃ语言中整数-8在内存中存储形式是（）",20,
            {"A）1111 1111 1111 1000","B）1000 0000 0000 1000","C）0000 0000 0000 1000","D）1111 1111 1111 0111"},4,'A'}
    };
	FILE* fp = fopen("data/question.dat","rb+");
	if(fp == NULL){
		fp = fopen("data/question.dat","wb+");
		fwrite(initQuestion, sizeof(QUESTION_T), 5, fp);
	}
	//从文件中读取用户信息并保存到question数组中 
	rewind(fp);
	while(fread(&question[questionNum], sizeof(QUESTION_T), 1, fp)){
		questionNum++;
	}
	fclose(fp);
}

EXAMRECORD_T examrecord[100] = {0};
int examrecordNum = 0;//考试记录数 

//初始化考试记录
//判断examrecord.dat文件是否存在
//若已存在，则直接读取文件中的数据，并保存到examrecord数组中 
//若不存在，则新建examrecord.dat文件，并将初始的两个考试记录保存到文件中 
void initExamRecords(){
	EXAMRECORD_T initExamRecord[2] = {{1002,"examer","2025-02-14 07:20:00",100},
										{1002,"examer","2025-02-14 10:08:00",100}}; 
	FILE* fp = fopen("data/examrecord.dat","rb+");
	if(fp == NULL) {
		fp = fopen("data/examrecord.dat","wb+");
		fwrite(initExamRecord, sizeof(EXAMRECORD_T), 2, fp);
	}
	//从文件中读取用户信息并保存到examrecord数组中 
	rewind(fp);
	while(fread(&examrecord[examrecordNum], sizeof(EXAMRECORD_T), 1, fp)){
		examrecordNum++;
	}
	fclose(fp);
} 

EXAMPAPER_T exampaper[100] = {0};
int exampaperNum = 0;//考卷数 
int ExamPaperIndex = -1;//当前预览或者删除时的考卷下标 

//初始化考卷
//判断examrpaper.dat文件是否存在
//若已存在，则直接读取文件中的数据，并保存到examrpaper数组中 
//若不存在，则新建examrpaper.dat文件
void initExamPapers(){
	FILE* fp = fopen("data/examrpaper.dat","rb+");
	if(fp == NULL) fp = fopen("data/examrpaper.dat","wb+");
	
	//从文件中读取考卷信息并保存到examrpaper数组中 
	rewind(fp);
	while(fread(&exampaper[exampaperNum], sizeof(EXAMPAPER_T), 1, fp)){
		exampaperNum++;
	}
	fclose(fp);
} 

