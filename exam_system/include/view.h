#ifndef _VIEW_H_
#define _VIEW_H_

#include "tool.h"
#include "data.h"

#define INITWIN 0
#define LOGINWIN 1
#define REGWIN 2
#define ADMWIN 3
#define STUWIN 4
#define UPDATEPWDWIN 5
#define SEARCHUSERSWIN 6
#define SHOWALLUSERSWIN 7
#define SHOWSOMEUSERSWIN 8
#define SHOWEXAMWIN 9
#define ADMSHOWSCOREWIN 10
#define STUSHOWSCOREWIN 11
#define MANAGEQUESTIONWIN 12
#define INCREASEQUESTIONWIN 13
#define CHANGEQUESTIONWIN 14
#define MANAGEEXAMPAPERWIN 15 
#define CREATEEXAMPAPERWIN 16
#define EXAMPAPERPREVIEWWIN 17
#define EXAMPAPERLISTWIN 18

//开始界面
int initWin();
//登录界面
int loginWin();
//注册界面
int regWin();
//管理员主界面
int admWin();
//考生主界面
int stuWin();
//修改密码界面
int updatePwdWin();
//管理员：考生查询界面
int searchUsersWin();
//管理员：考生全部查询界面 
int showAllUsersWin();
//管理员：考生条件查询界面 
int showSomeUsersWin();
//考生：考试界面
int showExamWin(); 
//管理员：考生成绩查询界面
int admShowScoreWin();
//考生：成绩查询界面
int stuShowScoreWin();
//管理员：考题管理界面
int ManageQuestionWin();
//管理员：考题新增界面
int IncreaseQuestionWin();
//管理员：考题修改界面
int ChangeQuestionWin();
//管理员：考卷管理界面
int ManageExamPaperWin();
//管理员：创建考卷界面
int CreateExamPaperWin();
//管理员：考卷预览界面
int ExamPaperPreviewWin();
//管理员：考卷列表界面
int ExamPaperListWin();

#endif
