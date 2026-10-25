#include "include/view.h"

int initWin() {
	paintWindow(30, 4, 60, 22);
	gotoxy(50, 6);
	printf("* 传一考试系统 *");
	gotoxy(60, 7);
	char date[20] = {0};
	getNowDate(date);
	printf("日期：%s",date);
	paintButton(50, 9, 20, 3, "1-登  录");
	paintButton(50, 12, 20, 3, "2-注  册");
	paintButton(50, 15, 20, 3, "3-退  出");
	gotoxy(50, 19);
	printf("请选择：");
	char choose = 0;
	while (1) {
		choose = getch();
		if (choose == '1' || choose == '2' || choose == '3') {
			putch(choose);
			break;
		}
	}
	if (choose == '1')
		return LOGINWIN;
	else if (choose == '2')
		return REGWIN;
	else {
		gotoxy(48, 21);
		printf("---成功退出考试系统！---");
		gotoxy(51, 22);
		system("pause");
		gotoxy(0, 25);
		return -1;
	}
}

int loginWin() {
	char username[7] = "";
	char password[7] = "";

	paintWindow(30, 6, 60, 18);
	gotoxy(50, 8);
	printf("* 传一考试系统登录界面 *");
	gotoxy(60, 9);
	char date[20] = {0};
	getNowDate(date);
	printf("日期：%s",date);
	gotoxy(47, 11);
	printf("用户名：");
	paintWindow(55, 10, 20, 3);
	gotoxy(47, 14);
	printf("密  码：");
	paintWindow(55, 13, 20, 3);
	gotoxy(47, 18);
	printf("提示：按回车登录验证，ESC返回");

	gotoxy(57, 11);
	int len_u = 6;
	int mode_u = 1;
	int res_u = inputCtrl(username, len_u, mode_u);
	if (res_u==1) return INITWIN;

	gotoxy(57, 14);
	int len_p = 6;
	int mode_p = 0;
	int res_p = inputCtrl(password, len_p, mode_p);
	if (res_p==1) return INITWIN;
	
	if(res_u==-1||res_p==-1){
		gotoxy(49, 20);
		printf("---账号或密码不能为空----");
		gotoxy(53, 21);
		system("pause");
		return LOGINWIN;
	}
	
	int i = 0;
	for (i = 0; i < userNum; i++) {
		if (strcmp(user[i].name, username) == 0 && strcmp(user[i].passwd, password) == 0) {
			loginIndex = i;
			gotoxy(53, 20);
			printf("---登录成功！---");
			gotoxy(51, 21);
			system("pause");
			return user[i].role == 1 ? ADMWIN : STUWIN;
		}
	}
	gotoxy(50, 20);
	printf("---账号或密码不正确----");
	gotoxy(53, 21);
	system("pause");
	return LOGINWIN;
}

int regWin() {
	paintWindow(30, 4, 60, 22);
	gotoxy(50, 6);
	printf("* 传一考试系统注册界面 *");
	gotoxy(60, 7);
	char date[20] = {0};
	getNowDate(date);
	printf("日期：%s",date);

	gotoxy(47, 9);
	printf("用 户 名");
	paintWindow(55, 8, 20, 3);
	gotoxy(47, 12);
	printf("密    码");
	paintWindow(55, 11, 20, 3);
	gotoxy(47, 15);
	printf("确认密码");
	paintWindow(55, 14, 20, 3);
	gotoxy(47, 18);
	printf("角    色");
	paintWindow(55, 17, 20, 3);
	gotoxy(51, 20);
	printf("角色：1-管理员 2-考生");
	gotoxy(47, 21);
	printf("提示：按回车登录验证，ESC返回");
	
	int len_u = 6;
	int mode_u = 1;
	while(1){
		memset(&user[userNum].name,0,len_u);
		gotoxy(57, 9);
		int res = inputCtrl(user[userNum].name, len_u, mode_u);
		if (res == 1) return INITWIN;
		if (res == 0) break;
		gotoxy(49, 23);
		printf("用户名不能为空,请重新输入");
		gotoxy(53, 24);
		system("pause");
		gotoxy(49, 23);
		printf("                               ");
		gotoxy(53, 24);
		printf("                    ");
	}

	int len_p = 6;
	int mode_p = 0;
	while (1) {
		memset(&user[userNum].passwd,0,len_p);
		gotoxy(57, 12);
		int res =  inputCtrl(user[userNum].passwd, len_p, mode_p);
		if (res == 1) return INITWIN;
		
		if (res == -1){
			gotoxy(49, 23);
			printf("密码不能为空,请重新输入");
			gotoxy(53, 24);
			system("pause");
			gotoxy(57, 12);
			printf("          ");
			gotoxy(49, 23);
			printf("                               ");
			gotoxy(53, 24);
			printf("                    ");
			continue;
		}
		
		char password[10] = "";
		gotoxy(57, 15);
		if (inputCtrl(password, len_p, mode_p)==1) return INITWIN;
		if (strcmp(user[userNum].passwd, password) == 0) break;
		gotoxy(46, 23);
		printf("两次输入的密码不一致,请重新输入");
		gotoxy(52, 24);
		system("pause");
		gotoxy(57, 12);
		printf("          ");
		gotoxy(57, 15);
		printf("          ");
		gotoxy(46, 23);
		printf("                               ");
		gotoxy(52, 24);
		printf("                    ");
	}

	char role = 0;
	while (1) {
		gotoxy(57, 18);
		role = getch();
		if (role == 27) return INITWIN;
		if (role == '1' || role == '2') {
			putch(role);
			break;
		}
		if (role == '\r'){
			gotoxy(49, 23);
			printf("角色类型不能为空,请重新输入");
			gotoxy(53, 24);
			system("pause");
			gotoxy(49, 23);
			printf("                               ");
			gotoxy(53, 24);
			printf("                    ");
		}
	}

	user[userNum].role = role - '0';
	user[userNum].id = 1001 + userNum;
	user[userNum].state = 1;
	
	//新注册的用户写入文件
	appendDataToFile(&user[userNum], sizeof(USER_T), "data/user.dat");
	
	userNum++;
	gotoxy(53, 23);
	printf("---注册成功！---");
	gotoxy(51, 24);
	system("pause");
	return LOGINWIN;
}

int admWin() {
	paintWindow(30, 2, 60, 26);
	gotoxy(50, 4);
	printf("* 传一考试系统管理员界面 *");
	gotoxy(45, 6);
	printf("欢迎%s管理员", user[loginIndex].name);
	gotoxy(65, 6);
	char date[20] = {0};
	getNowDate(date);
	printf("日期：%s",date);

	paintButton(50, 8, 20, 3, "1-修改密码");
	paintButton(50, 11, 20, 3, "2-用户查询");
	paintButton(50, 14, 20, 3, "3-成绩查询");
	paintButton(50, 17, 20, 3, "4-考题管理");
	paintButton(50, 20, 20, 3, "5-考卷管理");

	gotoxy(50, 24);
	printf("请选择：");
	char choose = 0;
	while (1) {
		choose = getch();
		if (choose == 27)
			return INITWIN;
		if (choose == '1' || choose == '2' || choose == '3' || choose == '4' || choose == '5') {
			putch(choose);
			break;
		}
	}
	switch (choose - '0') {
		case 1: return UPDATEPWDWIN; break;
		case 2: return SEARCHUSERSWIN; break;
		case 3: return ADMSHOWSCOREWIN; break;
		case 4: return MANAGEQUESTIONWIN; break;
		case 5: return MANAGEEXAMPAPERWIN; break;
	}
}

int stuWin() {
	paintWindow(35, 5, 50, 20);
	gotoxy(50, 7);
	printf("* 传一考试系统考生主界面 *");
	gotoxy(45, 9);
	printf("欢迎%s考生", user[loginIndex].name);
	gotoxy(65, 9);
	char date[20] = {0};
	getNowDate(date);
	printf("日期：%s",date);

	paintButton(50, 11, 20, 3, "1-修改密码");
	paintButton(50, 14, 20, 3, "2-考    试");
	paintButton(50, 17, 20, 3, "3-成绩查询");

	gotoxy(50, 21);
	printf("请选择：");
	char choose = 0;
	while (1) {
		choose = getch();
		if (choose == 27)
			return INITWIN;
		if (choose == '1' || choose == '2' || choose == '3') {
			putch(choose);
			break;
		}
	}
	switch (choose - '0') {
		case 1: return UPDATEPWDWIN; break;
		case 2: return SHOWEXAMWIN; break;
		case 3: return STUSHOWSCOREWIN; break;
	}
}

int updatePwdWin() {
	paintWindow(30, 5, 60, 20);
	gotoxy(49, 7);
	printf("* 传一考试系统修改密码界面 *");
	gotoxy(45, 9);
	printf("欢迎%s%s", user[loginIndex].name, user[loginIndex].role == 1 ? "管理员" : "考生");
	gotoxy(65, 9);
	char date[20] = {0};
	getNowDate(date);
	printf("日期：%s",date);
	gotoxy(45, 12);
	printf("旧  密  码：");
	paintWindow(57, 11, 20, 3);
	gotoxy(45, 15);
	printf("新  密  码：");
	paintWindow(57, 14, 20, 3);
	gotoxy(45, 18);
	printf("确认新密码：");
	paintWindow(57, 17, 20, 3);
	gotoxy(45, 20);
	printf("提示：按回车确认修改密码，ESC返回");

	char password[6] = "";//用户输入的旧密码 
	char password_new[6] = "";//用户输入的新密码
	char password_new_confirm[6] = "";//用户确认的新密码
	int len_p = 6;
	int mode_p = 0;
	int res = 0;
	while (1) {
		memset(password,0,sizeof(password));
		gotoxy(59, 12);
		res = inputCtrl(password, len_p, mode_p);
		if (res == 1) return user[loginIndex].role == 1 ? ADMWIN : STUWIN;
		if(res == -1){
			gotoxy(51, 22);
			printf("---输入不能为空---");
			gotoxy(52, 23);
			system("pause");
			return UPDATEPWDWIN;
		}
		if (strcmp(user[loginIndex].passwd, password) == 0) break;
		gotoxy(42, 22);
		printf("输入的旧密码和原旧密码不一致,请重新输入");
		gotoxy(52, 23);
		system("pause");
		gotoxy(59, 12);
		return UPDATEPWDWIN;
	}
	while (1) {
		memset(password_new,0,sizeof(password_new));
		gotoxy(59, 15);
		res = inputCtrl(password_new, len_p, mode_p);
		if (res==1) return user[loginIndex].role == 1 ? ADMWIN : STUWIN;
		if(res==-1){
			gotoxy(51, 22);
			printf("---输入不能为空---");
			gotoxy(52, 23);
			system("pause");
			gotoxy(51, 22);
			printf("                  ");
			gotoxy(52, 23);
			printf("                  ");
			continue;
		}
		if (strcmp(password, password_new) == 0) {
			gotoxy(44, 22);
			printf("输入的新密码和原密码一致,请重新输入");
			gotoxy(52, 23);
			system("pause");
			gotoxy(59, 15);
			printf("          ");
			gotoxy(44, 22);
			printf("                                       ");
			gotoxy(52, 23);
			printf("                  ");
			continue;
		}

		memset(password_new_confirm,0,sizeof(password_new_confirm));
		gotoxy(59, 18);
		int res = inputCtrl(password_new_confirm, len_p, mode_p);
		if (res==1) return user[loginIndex].role == 1 ? ADMWIN : STUWIN;
		if(res==-1){
			gotoxy(51, 22);
			printf("---输入不能为空---");
			gotoxy(52, 23);
			system("pause");
			gotoxy(59, 15);
			printf("          ");
			gotoxy(51, 22);
			printf("                  ");
			gotoxy(52, 23);
			printf("                  ");
			continue;
		}
		if (strcmp(password_new, password_new_confirm) == 0) break;
		gotoxy(46, 22);
		printf("两次输入的密码不一致,请重新输入");
		gotoxy(52, 23);
		system("pause");
		gotoxy(59, 15);
		printf("          ");
		gotoxy(59, 18);
		printf("          ");
		gotoxy(46, 22);
		printf("                                       ");
		gotoxy(52, 23);
		printf("                  ");
	}
	strcpy(user[loginIndex].passwd, password_new);
	
	//用户密码修改成功后更新到文件中
	updateDataToFile(&user[loginIndex], sizeof(USER_T), "data/user.dat", sizeof(USER_T)*loginIndex); 
		
	gotoxy(51, 22);
	printf("---密码修改成功！---");
	gotoxy(52, 23);
	system("pause");
	return LOGINWIN;
}

int searchUsersWin() {
	paintWindow(35, 5, 50, 20);
	gotoxy(50, 7);
	printf("* 传一考试系统考生查询界面 *");
	gotoxy(45, 9);
	printf("欢迎%s管理员", user[loginIndex].name);
	gotoxy(65, 9);
	char date[20] = {0};
	getNowDate(date);
	printf("日期：%s",date);

	paintButton(50, 11, 20, 3, "1-全部查询");
	paintButton(50, 14, 20, 3, "2-条件查询");
	paintButton(50, 17, 20, 3, "3-返    回");
	
	gotoxy(50, 21);
	printf("请选择：");
	char choose = 0;
	while (1) {
		choose = getch();
		if (choose == 27)
			return ADMWIN;
		if (choose == '1' || choose == '2' || choose == '3') {
			putch(choose);
			break;
		}
	}
	switch (choose - '0') {
		case 1: return SHOWALLUSERSWIN; break;
		case 2: return SHOWSOMEUSERSWIN; break;
		case 3: return ADMWIN; break;
	}
}
 
int showAllUsersWin() {
	int page = (userNum - 1) / 3 + 1;//总页数 
	static int nowPage = 1;//当前页 
	int i = 0, j = 0;
	paintWindow(30, 5, 60, 20);
	gotoxy(44, 7);
	printf("* 传一考试系统考生全部查询界面 *");
	gotoxy(41, 9);
	printf("欢迎%s管理员", user[loginIndex].name);
	gotoxy(65, 9);
	char date[20] = {0};
	getNowDate(date);
	printf("日期：%s",date);

	gotoxy(42, 13);
	printf("ID");
	gotoxy(53, 13);
	printf("姓名");
	gotoxy(65, 13);
	printf("密码");
	gotoxy(77, 13);
	printf("状态");

	//当前用户的起始索引 
	int nowUserIndex = (nowPage - 1) * 3;

	//注意到当userNum=3,nowUserIndex=0时,若改为=，则row=3，造成bug 
	int row = userNum - nowUserIndex >= 3 ? 3 : userNum % 3;

	paintTable(36, 12, 5, row + 1, 4);
	gotoxy(38, 22);
	printf("<- -> 左右键翻页 %d/%d", nowPage, page);
	for (i = 0; i < row; i++) {
		gotoxy(41, 15 + 2 * i);
		printf("%d", user[nowUserIndex + i].id);
		gotoxy(52, 15 + 2 * i);
		printf("%s", user[nowUserIndex + i].name);
		int passwdlen = strlen(user[nowUserIndex + i].passwd);
		gotoxy(67 - passwdlen / 2, 15 + 2 * i);
		for (j = 0; j < passwdlen; j++)
			printf("*");
		gotoxy(76 + user[nowUserIndex + i].state, 15 + 2 * i);
		printf("%s", user[nowUserIndex + i].state ? "可用" : "不可用");
	}
	gotoxy(59, 22);
	char choose[2] = {0};
	int res = inputCtrl(choose, 2, 1);
	if (res == 1){
		nowPage = 1;
		return SEARCHUSERSWIN;
	}
	else if (res == 75) {
		if (nowPage > 1) nowPage--;
		else {
			gotoxy(60, 22);
			printf("已经是第一页");
			gotoxy(60, 23);
			system("pause");
		}
	}
	else if (res == 77) {
		if (nowPage < page) nowPage++;
		else {
			gotoxy(60, 22);
			printf("已经是最后一页");
			gotoxy(60, 23);
			system("pause");
		}
	}
	return SHOWALLUSERSWIN;
}

int showSomeUsersWin() {
	static int i_userid = 0;
	static USER_T queryUser = { 0 };//保存查询到的用户 
	int page = (userNum - 1) / 3 + 1;//总页数 
	static int nowPage = 1;//当前页 
	int i = 0, j = 0;
	paintWindow(30, 4, 60, 22);
	gotoxy(44, 6);
	printf("* 传一考试系统考生条件查询界面 *");
	gotoxy(41, 8);
	printf("欢迎%s管理员", user[loginIndex].name);
	gotoxy(65, 8);
	char date[20] = {0};
	getNowDate(date);
	printf("日期：%s",date);

	gotoxy(41, 11);
	printf("查询考生ID");
	paintWindow(52, 10, 20, 3);

	gotoxy(42, 14);
	printf("ID");
	gotoxy(53, 14);
	printf("姓名");
	gotoxy(65, 14);
	printf("密码");
	gotoxy(77, 14);
	printf("状态");

	if (i_userid == 0) {
		//当前用户的起始索引 
		int nowUserIndex = (nowPage - 1) * 3;

		//注意到当userNum=3,nowUserIndex=0时,若改为>，则row=0，造成bug 
		int row = userNum - nowUserIndex >= 3 ? 3 : userNum % 3;

		paintTable(36, 13, 5, row + 1, 4);
		gotoxy(38, 23);
		printf("<- -> 左右键翻页 %d/%d", nowPage, page);
		for (i = 0; i < row; i++) {
			gotoxy(41, 16 + 2 * i);
			printf("%d", user[nowUserIndex + i].id);
			gotoxy(52, 16 + 2 * i);
			printf("%s", user[nowUserIndex + i].name);
			int passwdlen = strlen(user[nowUserIndex + i].passwd);
			gotoxy(67 - passwdlen / 2, 16 + 2 * i);
			for (j = 0; j < passwdlen; j++)
				printf("*");
			gotoxy(76 + user[nowUserIndex + i].state, 16 + 2 * i);
			printf("%s", user[nowUserIndex + i].state ? "可用" : "不可用");
		}
	}
	else{
		paintTable(36, 13, 5, 2, 4);
		gotoxy(38, 23);
		printf("<- -> 左右键翻页 1/1");
		gotoxy(41, 16);
		printf("%d", queryUser.id);
		gotoxy(52, 16);
		printf("%s", queryUser.name);
		int passwdlen = strlen(queryUser.passwd);
		gotoxy(67 - passwdlen / 2, 16);
		for (j = 0; j < passwdlen; j++)
			printf("*");
		gotoxy(76 + queryUser.state, 16);
		printf("%s", queryUser.state ? "可用" : "不可用");
	}
	gotoxy(54, 11);
	char c_userid[5] = { 0 };
	int res = inputCtrl(c_userid, 4, 1);
	if (res == -1) {
		i_userid = 0;
		nowPage = 1;
		return SHOWSOMEUSERSWIN;
	}
	if (res == 0) {
		i_userid = atoi(c_userid);
		for (i = 0; i < userNum; i++) {
			if (user[i].id == i_userid) {
				queryUser = user[i];
				return SHOWSOMEUSERSWIN;
			}
		}
		i_userid = 0;
		nowPage = 1;
		gotoxy(60, 23);
		printf("该考生不存在");
		gotoxy(60, 24);
		system("pause");
	}
	if (res == 1){
		i_userid = 0;
		nowPage = 1;
		return SEARCHUSERSWIN;
	}
	else if (res == 75) { 
		if (nowPage > 1) nowPage--;
		else {
			gotoxy(60, 23);
			printf("已经是第一页");
			gotoxy(60, 24);
			system("pause");
		}
	}
	else if (res == 77) {
		if (nowPage < page) nowPage++;
		else {
			gotoxy(60, 23);
			printf("已经是最后一页");
			gotoxy(60, 24);
			system("pause");
		}
	}
	return SHOWSOMEUSERSWIN;
}

int showExamWin(){
	paintWindow(30, 3, 60, 24);
	gotoxy(44, 5);
	printf("* 传一考试系统考生考试界面 *");
	gotoxy(41, 7);
	printf("欢迎%s考生", user[loginIndex].name);
	gotoxy(65, 7);
	char date[20] = {0};
	getNowDate(date);
	printf("日期：%s",date);
	
	static int questionIndex = 0;
	static int score = 0; 
	int i = 0;
	
	gotoxy(41, 9);
	printf("考试类型：%s",question[questionIndex].subject);
	gotoxy(41, 11);
	printf("第%d题 分数：%d",questionIndex+1,question[questionIndex].score);
	if(strlen(question[questionIndex].title)>=40){
		gotoxy(41, 13);
		printf("题目：");
		for(i=0;i<40;i++)
			printf("%c",question[questionIndex].title[i]);
		gotoxy(47, 14);
		for(i=40;i<strlen(question[questionIndex].title);i++)
			printf("%c",question[questionIndex].title[i]);
	}
	else{
		gotoxy(41, 13);
		printf("题目：%s",question[questionIndex].title);
	}
	for(i=0;i<question[questionIndex].optionNum;i++){
		gotoxy(41, 16+i);
		printf("%s", question[questionIndex].option[i]);
	}
	gotoxy(41, 21);
	printf("请输入答案：");
	paintWindow(54, 20, 20, 3);
	
	char input_answer[2] = {0};
	gotoxy(56,21);
	int res = inputCtrl(input_answer, 1, 1);
	if(res == 1){
		questionIndex = 0;
		score = 0; 
		return STUWIN;
	}
	if(res == -1){
		gotoxy(41,23);
		printf("输入不能为空");
		gotoxy(41,24);
		system("pause"); 
		gotoxy(41,23);
		printf("        ");
		gotoxy(41,24);
		printf("                  ");
		return SHOWEXAMWIN;
	}
	if(strcmp(input_answer,"A")!=0&&strcmp(input_answer,"B")!=0&&
		strcmp(input_answer,"C")!=0&&strcmp(input_answer,"D")!=0){
		gotoxy(41,23);
		printf("输入的选项不存在");
		gotoxy(41,24);
		system("pause"); 
		gotoxy(41,23);
		printf("        ");
		gotoxy(41,24);
		printf("                  ");
		return SHOWEXAMWIN;
	}
	if(strcmp(input_answer,question[questionIndex].answer)==0)
		score += question[questionIndex].score;
	questionIndex++;
	if(questionIndex >= questionNum){
		gotoxy(41,23);
		printf("考试结束，正在保存数据。。。");
		Sleep(1000);
		gotoxy(41,24);
		printf("考试得分：%d",score);
		
		examrecord[examrecordNum].id = user[loginIndex].id;
		strcpy(examrecord[examrecordNum].name, user[loginIndex].name);
		char dt[20] = {0};
		getNowDateAndTime(dt);
		strcpy(examrecord[examrecordNum].time, dt);
		examrecord[examrecordNum].score = score;
		//保存考试成绩(存入文件中) 
		appendDataToFile(&examrecord[examrecordNum], sizeof(EXAMRECORD_T), "data/examrecord.dat");
		examrecordNum++;
		
		questionIndex = 0;
		score = 0; 
		gotoxy(65,24);
		getch();
		return STUWIN;
	}
	gotoxy(41,24);
	printf("即将进入下一题");
	Sleep(500);
	return SHOWEXAMWIN;
}

int admShowScoreWin(){
	static int i_ExamRecordid = 0;
	static EXAMRECORD_T queryeExamRecord[100] = { 0 };//保存查询到的考试记录
	static int queryeNum = 0;//查询到的考试记录的总数 
	static int nowPage = 1;//当前页 
	int i = 0, row = 0, page = 0; 
	paintWindow(23, 4, 74, 22);
	gotoxy(44, 6);
	printf("* 传一考试系统考生成绩查询界面 *");
	gotoxy(41, 8);
	printf("欢迎%s管理员", user[loginIndex].name);
	gotoxy(65, 8);
	char date[20] = {0};
	getNowDate(date);
	printf("日期：%s",date);

	gotoxy(35, 11);
	printf("查询考生ID");
	paintWindow(52, 10, 20, 3);

	gotoxy(36, 14);
	printf("考生ID");
	gotoxy(57, 14);
	printf("考试时间");
	gotoxy(79, 14);
	printf("考试成绩");
	
	//当前考试记录的起始索引 
	int nowExamRecordIndex = (nowPage - 1) * 3;
	gotoxy(35, 23);
	if (i_ExamRecordid == 0){
		page = (examrecordNum - 1) / 3 + 1;//总页数 
		printf("上一页<-  ->下一页 第%d页  共%d页", nowPage, page);
		row = examrecordNum - nowExamRecordIndex >= 3 ? 3 : examrecordNum % 3;
		paintTable(27, 13, 10, row + 1, 3);
		
		int j = 0;
        for (i = 0; i < examrecordNum - 1; i++) {
            int flag = 0;  // 优化标志
            for (j = 0; j < examrecordNum - i - 1; j++) {
                if (strcmp(examrecord[j].time, examrecord[j + 1].time) < 0) {
                    EXAMRECORD_T temp = examrecord[j];
                    examrecord[j] = examrecord[j + 1];
                    examrecord[j + 1] = temp;
                    flag = 1;
                }
            }
            if (flag == 0) break;
        }
		
		for (i = 0; i < row; i++) {
			gotoxy(37, 16 + 2 * i);
			printf("%d", examrecord[nowExamRecordIndex + i].id);
			gotoxy(52, 16 + 2 * i);
			printf("%s", examrecord[nowExamRecordIndex + i].time);
			gotoxy(82, 16 + 2 * i);
			printf("%d", examrecord[nowExamRecordIndex + i].score);
		}
	}
	else{
		page = (queryeNum - 1) / 3 + 1;//总页数 
		printf("上一页<-  ->下一页 第%d页  共%d页", nowPage, page);
		row = queryeNum - nowExamRecordIndex >= 3 ? 3 : queryeNum % 3;
		paintTable(27, 13, 10, row + 1, 3);
		
		for (i = 0; i < row; i++) {
			gotoxy(37, 16 + 2 * i);
			printf("%d", queryeExamRecord[nowExamRecordIndex + i].id);
			gotoxy(52, 16 + 2 * i);
			printf("%s", queryeExamRecord[nowExamRecordIndex + i].time);
			gotoxy(82, 16 + 2 * i);
			printf("%d", queryeExamRecord[nowExamRecordIndex + i].score);
		}
	}
	
	gotoxy(54, 11);
	char c_ExamRecordid[5] = { 0 };
	int res = inputCtrl(c_ExamRecordid, 4, 1);
	if (res == -1) {
		nowPage = 1;
		i_ExamRecordid = 0;
		return ADMSHOWSCOREWIN;
	}
	if (res == 0) {
		queryeNum = 0;
		i_ExamRecordid = atoi(c_ExamRecordid);
		for (i = 0; i < examrecordNum; i++)
			if (examrecord[i].id == i_ExamRecordid)
				queryeExamRecord[queryeNum++] = examrecord[i];
		if(queryeNum!=0){
			nowPage = 1;
			
        	for (i = 0; i < queryeNum - 1; i++) {
            	int j = 0, flag = 0;  // 优化标志
            	for (j = 0; j < queryeNum - i - 1; j++) {
                	if (strcmp(queryeExamRecord[j].time, queryeExamRecord[j + 1].time) < 0) {
                    	EXAMRECORD_T temp = queryeExamRecord[j];
                    	queryeExamRecord[j] = queryeExamRecord[j + 1];
                    	queryeExamRecord[j + 1] = temp;
                    	flag = 1;
                	}
            	}
            	if (flag == 0) break;
        	}
			return ADMSHOWSCOREWIN;
		} 
		nowPage = 1;
		i_ExamRecordid = 0;
		gotoxy(70, 23);
		printf("该考生不存在");
		gotoxy(70, 24);
		system("pause");
	}
	if (res == 1){
		nowPage = 1;
		i_ExamRecordid = 0;
		return ADMWIN;
	}
	else if (res == 75) { 
		if (nowPage > 1) nowPage--;
		else {
			gotoxy(70, 23);
			printf("已经是第一页");
			gotoxy(70, 24);
			system("pause");
		}
	}
	else if (res == 77) {
		if (nowPage < page) nowPage++;
		else {
			gotoxy(70, 23);
			printf("已经是最后一页");
			gotoxy(70, 24);
			system("pause");
		}
	}
	return ADMSHOWSCOREWIN;
}

int stuShowScoreWin(){
	static EXAMRECORD_T queryeExamRecord[100] = { 0 };//保存当前考生的考试记录
	static int queryeNum = 0;//当前考生的考试记录数 
	static int nowPage = 1;//当前页 
	int i = 0, row = 0, page = 0;
	paintWindow(30, 5, 60, 20);
	gotoxy(46, 7);
	printf("* 传一考试系统成绩查询界面 *");
	gotoxy(43, 9);
	printf("欢迎%s考生", user[loginIndex].name);
	gotoxy(65, 9);
	char date[20] = {0};
	getNowDate(date);
	printf("日期：%s",date);

	gotoxy(46, 12);
	printf("考试时间");
	gotoxy(68, 12);
	printf("考试成绩");
	
	//当前考试记录的起始索引 
	int nowExamRecordIndex = (nowPage - 1) * 3;
	
	//进入时统计当前考生的考试记录
	if (queryeNum == 0) {
        for (i = 0; i < examrecordNum; i++)
            if (examrecord[i].id == user[loginIndex].id)
                queryeExamRecord[queryeNum++] = examrecord[i];
        int j = 0;
        for (i = 0; i < queryeNum - 1; i++) {
            int flag = 0;  // 优化标志
            for (j = 0; j < queryeNum - i - 1; j++) {
                if (strcmp(queryeExamRecord[j].time, queryeExamRecord[j + 1].time) < 0) {
                    EXAMRECORD_T temp = queryeExamRecord[j];
                    queryeExamRecord[j] = queryeExamRecord[j + 1];
                    queryeExamRecord[j + 1] = temp;
                    flag = 1;
                }
            }
            if (flag == 0) break;
        }
    }
	page = (queryeNum - 1) / 3 + 1;//总页数
	gotoxy(40, 21);
	printf("<- -> 左右键翻页 %d/%d   按任意键返回", nowPage, page);
	row = queryeNum - nowExamRecordIndex >= 3 ? 3 : queryeNum % 3;
	paintTable(38, 11, 10, row + 1, 2);
	for (i = 0; i < row; i++) {
		gotoxy(41, 14 + 2 * i);
		printf("%s", queryeExamRecord[nowExamRecordIndex + i].time);
		gotoxy(71, 14 + 2 * i);
		printf("%d", queryeExamRecord[nowExamRecordIndex + i].score);
	}
	gotoxy(76, 21);
	char res = getch();
	if(res == -32){
		res = getch();
		if (res == 75) {
			if (nowPage > 1) nowPage--;
			else {
				gotoxy(63, 21);
				printf("已经是第一页");
				gotoxy(63, 22);
				system("pause");
			}
			return STUSHOWSCOREWIN;
		}
		else if (res == 77) {
			if (nowPage < page) nowPage++;
			else {
				gotoxy(63, 21);
				printf("已经是最后一页");
				gotoxy(63, 22);
				system("pause");
			}
			return STUSHOWSCOREWIN;
		}
	}
	nowPage = 1;
	queryeNum = 0;
	return STUWIN;
}

int ManageQuestionWin() {
    paintWindow(25, 4, 70, 22);
    gotoxy(46, 6);
    printf("* 传一考试系统考题管理界面 *");
    gotoxy(43, 8);
    printf("欢迎%s管理员", user[loginIndex].name);
    gotoxy(65, 8);
    char date[20] = { 0 };
    getNowDate(date);
    printf("日期：%s", date);

    gotoxy(40, 10);
    printf("查询考题");
    paintWindow(50, 9, 20, 3);
    paintWindow(73, 9, 7, 3);
    gotoxy(75, 10);
    printf("新增");

    static int questionflag = 0;
    static QUESTION_T queryQuestion = { 0 };
    int page = (questionNum - 1) / 3 + 1;
    static int nowPage = 1;
    int i = 0, j = 0;
    int position[8][2] = {{52, 10}, {79, 10}, {80, 15}, {86, 15},
                          {80, 17}, {86, 17}, {80, 19}, {86, 19}};
    static int nowPos = 0;
    static int pos = 8;
    gotoxy(37, 13);
    printf("序号");
    gotoxy(49, 13);
    printf("题目名称");
    gotoxy(64, 13);
    printf("出题人");
    gotoxy(79, 13);
    printf("操作");

    if (questionflag == 0) {
        int nowQuestionIndex = (nowPage - 1) * 3;
        int row = questionNum - nowQuestionIndex >= 3 ? 3 : questionNum % 3;
        pos = row * 2 + 2;
        paintTable(31, 12, 6, row + 1, 4);
        gotoxy(38, 22);
        printf("<- -> 左右键翻页 %d/%d", nowPage, page);
        gotoxy(37, 23);
        printf("↑↓上下键切换选项 %d/%d", nowPos + 1, pos);
        for (i = 0; i < row; i++) {
            gotoxy(38, 15 + 2 * i);
            printf("%d", question[nowQuestionIndex + i].id);
            
            //处理中文字符题目(一个中文字符占两个字节) 
            gotoxy(47, 15 + 2 * i);
            printf("题目：");
            char title[7] = { 0 };
            strncpy(title, question[nowQuestionIndex + i].title, 6);
            title[6] = '\0';
            printf("%s", title);
            
            gotoxy(64, 15 + 2 * i);
            printf("%s", user[loginIndex].name);
            paintWindow(74, 14 + 2 * i, 7, 3);
            gotoxy(76, 15 + 2 * i);
            printf("修改");
            paintWindow(80, 14 + 2 * i, 7, 3);
            gotoxy(82, 15 + 2 * i);
            printf("删除");
        }
    } else {
        paintTable(31, 12, 6, 2, 4);
        page = 1;
        pos = 4;
        gotoxy(38, 22);
        printf("<- -> 左右键翻页 %d/%d", nowPage, page);
        gotoxy(37, 23);
        printf("↑↓上下键切换选项 %d/%d", nowPos + 1, pos);
        gotoxy(38, 15);
        printf("%d", queryQuestion.id);
        gotoxy(47, 15);
        printf("题目：");
        char title[7] = { 0 };
        strncpy(title, queryQuestion.title, 6);
        title[6] = '\0';
        printf("%s", title);
        gotoxy(64, 15);
        printf("%s", user[loginIndex].name);
        paintWindow(74, 14, 7, 3);
        gotoxy(76, 15);
        printf("修改");
        paintWindow(80, 14, 7, 3);
        gotoxy(82, 15);
        printf("删除");
    }

    gotoxy(position[nowPos][0], position[nowPos][1]);

    char c_questiontitle[7] = { 0 };
    int res = inputCtrl(c_questiontitle, 6, 1);
    if (res == -1) {
    	changeQuestionIndex = (nowPos - 2) / 2 + (nowPage - 1) * 3;
    	
        if (nowPos == 0) {
            questionflag = 0;
            nowPage = 1;
            return MANAGEQUESTIONWIN;
        } 
		else if (nowPos == 1)
            return INCREASEQUESTIONWIN;
		else if (nowPos == 2 || nowPos == 4 || nowPos == 6)
            return CHANGEQUESTIONWIN;
        memset(&question[changeQuestionIndex],0,sizeof(QUESTION_T));
        questionNum--;
        for (i = changeQuestionIndex; i < questionNum; i++) {
            question[i] = question[i+1];
            question[i].id--;
        }
		memset(&question[questionNum],0,sizeof(QUESTION_T));
        FILE* fp = fopen("data/question.dat", "wb+");
        fwrite(question, sizeof(QUESTION_T), questionNum, fp);
        fclose(fp);

        questionflag = 0;
        nowPage = 1;
        nowPos = 0;
        return MANAGEQUESTIONWIN;
    } else if (res == 0) {
        char* title = (char*)malloc(6 * sizeof(char));
        for (i = 0; i < questionNum; i++) {
            memcpy(title, &question[i].title, 6 * sizeof(char));
            if (strcmp(title, c_questiontitle) == 0) {
                queryQuestion = question[i];
                free(title);
                questionflag = 1;
                nowPage = 1;
                nowPos = 0;
                return MANAGEQUESTIONWIN;
            }
        }
        free(title);
        questionflag = 0;
        nowPage = 1;
        gotoxy(65, 22);
        printf("该题不存在");
        gotoxy(65, 23);
        system("pause");
    } else if (res == 1) {
        questionflag = 0;
        nowPage = 1;
        nowPos = 0;
        return ADMWIN;
    } else if (res == 75) {
        if (nowPage > 1) {
            nowPage--;
            nowPos = 0;
        } else {
            gotoxy(65, 22);
            printf("已经是第一页");
            gotoxy(65, 23);
            system("pause");
        }
    } else if (res == 77) {
        if (nowPage < page) {
            nowPage++;
            nowPos = 0;
        } else {
            gotoxy(65, 22);
            printf("已经是最后一页");
            gotoxy(65, 23);
            system("pause");
        }
    } else if (res == 72) {
        if (nowPos > 0) {
            nowPos--;
        } else {
            gotoxy(65, 22);
            printf("已经是第一个选项");
            gotoxy(65, 23);
            system("pause");
        }
    } else if (res == 80) {
        if (nowPos < pos - 1) {
            nowPos++;
        } else {
            gotoxy(65, 22);
            printf("已经是最后一个选项");
            gotoxy(65, 23);
            system("pause");
        }
    }
    return MANAGEQUESTIONWIN;
}

int IncreaseQuestionWin() {
	paintWindow(25, 0, 70, 30);
	gotoxy(48, 1);
	printf("* 传一考试系统新增界面 *");
	gotoxy(43, 2);
	printf("欢迎%s管理员", user[loginIndex].name);
	gotoxy(65, 2);
	char date[20] = { 0 };
	getNowDate(date);
	printf("日期：%s", date);

	gotoxy(40, 4);
	printf("题目");
	paintWindow(46, 3, 35, 3);

	gotoxy(40, 7);
	printf("选项A");
	paintWindow(46, 6, 35, 3);

	gotoxy(40, 10);
	printf("选项B");
	paintWindow(46, 9, 35, 3);

	gotoxy(40, 13);
	printf("选项C");
	paintWindow(46, 12, 35, 3);

	gotoxy(40, 16);
	printf("选项D");
	paintWindow(46, 15, 35, 3);

	gotoxy(40, 19);
	printf("答案");
	paintWindow(46, 18, 35, 3);

	gotoxy(40, 22);
	printf("分数");
	paintWindow(46, 21, 20, 3);
	gotoxy(67, 22);
	printf("分");

	gotoxy(40, 25);
	printf("解析");
	paintWindow(46, 24, 35, 4);

	gotoxy(45, 28);
	printf("按回车键保存，按ESC键返回上一级");

	while (1) {
		memset(&question[questionNum].title,0,sizeof(question[questionNum].title));
		gotoxy(48, 4);
		int res = inputCtrl(question[questionNum].title, 50, 1);
		if (res == 1) return MANAGEQUESTIONWIN;
		if (res == 0) break;
		gotoxy(70, 22);
		printf("输入不能为空,请重新输入");
		gotoxy(72, 23);
		system("pause");
		gotoxy(70, 22);
		printf("                               ");
		gotoxy(72, 23);
		printf("                    ");
	}

	int i = 0;
	char optionText[41] = {0};
	char options[4][4] = {{"A）"},{"B）"},{"C）"},{"D）"}}; 
	for (i = 0; i < 4; i++) {
		memset(optionText,0,sizeof(optionText));
		while (1) {
			strcpy(question[questionNum].option[i], options[i]); 
			gotoxy(48, 7 + 3 * i);
			int res = inputCtrl(optionText, 40, 1);
			strcpy(strstr(question[questionNum].option[i], "）") + 2,optionText);
			if (res == 1) return MANAGEQUESTIONWIN;
			if (res == 0) break;
			gotoxy(70, 22);
			printf("输入不能为空,请重新输入");
			gotoxy(72, 23);
			system("pause");
			gotoxy(70, 22);
			printf("                               ");
			gotoxy(72, 23);
			printf("                    ");
		}
	}

	char choose[2] = { 0 };
	while (1) {
		memset(choose,0,sizeof(choose));
		gotoxy(48, 19);
		int res = inputCtrl(choose, 1, 1);
		if (res == 1) return MANAGEQUESTIONWIN;
		if (res == 0) {
			if ((choose[0] == 'A' || choose[0] == 'B' || choose[0] == 'C' || choose[0] == 'D')) break;
			else {
				gotoxy(70, 22);
				printf("选项输入错误,请重新输入");
				gotoxy(72, 23);
				system("pause");
				gotoxy(70, 22);
				printf("                               ");
				gotoxy(72, 23);
				printf("                    ");
				gotoxy(49, 20);
				printf("\b \b");
				choose[0] = '\0';
				continue;
			}
		}
		gotoxy(70, 22);
		printf("输入不能为空,请重新输入");
		gotoxy(72, 23);
		system("pause");
		gotoxy(70, 22);
		printf("                               ");
		gotoxy(72, 23);
		printf("                    ");
	}
	question[questionNum].answer[0] = choose[0];

	char c_Questionid[3] = { 0 };
	while (1) {
		memset(c_Questionid,0,sizeof(c_Questionid));
		gotoxy(48, 22);
		int res = inputCtrl(c_Questionid, 2, 1);
		if (res == 1) return MANAGEQUESTIONWIN;
		if (res == 0) break;
		gotoxy(70, 22);
		printf("输入不能为空,请重新输入");
		gotoxy(72, 23);
		system("pause");
		gotoxy(70, 22);
		printf("                               ");
		gotoxy(72, 23);
		printf("                    ");
	}
	question[questionNum].score = atoi(c_Questionid);

	while (1) {
		memset(&question[questionNum].analysis,0,sizeof(question[questionNum].analysis));
		gotoxy(48, 25);
		int res = inputCtrl(question[questionNum].analysis, 99, 1);
		if (res == 1) return MANAGEQUESTIONWIN;
		if (res == 0) break;
		gotoxy(70, 22);
		printf("输入不能为空,请重新输入");
		gotoxy(72, 23);
		system("pause");
		gotoxy(70, 22);
		printf("                               ");
		gotoxy(72, 23);
		printf("                    ");
	}

	//新添加的题目写入文件
	question[questionNum].id = questionNum + 1;
	strcpy(question[questionNum].subject, "C语言考试");
	question[questionNum].optionNum = 4;
	appendDataToFile(&question[questionNum], sizeof(QUESTION_T), "data/question.dat");
	
	questionNum++;

	gotoxy(77, 22);
	printf("新增成功");
	gotoxy(72, 23);
	system("pause");
	gotoxy(70, 22);
	printf("                               ");
	gotoxy(72, 23);
	printf("                    ");
	return MANAGEQUESTIONWIN;
}

int ChangeQuestionWin() {
	paintWindow(25, 0, 70, 30);
	gotoxy(48, 1);
	printf("* 传一考试系统修改界面 *");
	gotoxy(43, 2);
	printf("欢迎%s管理员", user[loginIndex].name);
	gotoxy(65, 2);
	char date[20] = { 0 };
	getNowDate(date);
	printf("日期：%s", date);

	gotoxy(40, 5);
	printf("题目");
	paintWindow(46, 4, 40, 3);

	gotoxy(40, 8);
	printf("选项A");
	paintWindow(46, 7, 40, 3);

	gotoxy(40, 11);
	printf("选项B");
	paintWindow(46, 10, 40, 3);

	gotoxy(40, 14);
	printf("选项C");
	paintWindow(46, 13, 40, 3);

	gotoxy(40, 17);
	printf("选项D");
	paintWindow(46, 16, 40, 3);

	gotoxy(40, 20);
	printf("答案");
	paintWindow(46, 19, 20, 3);

	gotoxy(40, 23);
	printf("解析");
	paintWindow(46, 22, 40, 4);

	gotoxy(45, 27);
	printf("按回车键保存修改，按ESC键返回上一级");

	gotoxy(48, 5);
	printf("%s", question[changeQuestionIndex].title);

	int i = 0;
	for (i = 0; i < question[changeQuestionIndex].optionNum; i++) {
		gotoxy(48, 8 + 3 * i);
		printf("%s", strstr(question[changeQuestionIndex].option[i], "）") + 2);
	}
	gotoxy(48, 20);
	printf("%c", question[changeQuestionIndex].answer[0]);

	gotoxy(48, 23);
	printf("%s", question[changeQuestionIndex].analysis);

	while (1) {
		char title[50] = {0};
		strcpy(title,question[changeQuestionIndex].title);
		gotoxy(48 + strlen(title), 5);
		int res = inputCtrl(title, 50, 1);
		if (res == 1) return MANAGEQUESTIONWIN;
		if (res == 0) {
			strcpy(question[changeQuestionIndex].title,title);
			//新修改的题目更新并写入文件
			updateDataToFile(&question[changeQuestionIndex], sizeof(QUESTION_T), "data/question.dat", changeQuestionIndex * sizeof(QUESTION_T));
			gotoxy(75, 20);
			printf("修改成功！");
			gotoxy(71, 21);
			system("pause");
			gotoxy(75, 20);
			printf("          ");
			gotoxy(71, 21);
			printf("                    ");
			break;
		}
		gotoxy(70, 20);
		printf("输入不能为空,请重新输入");
		gotoxy(72, 21);
		system("pause");
		gotoxy(70, 20);
		printf("                               ");
		gotoxy(72, 21);
		printf("                    ");
	}

	for (i = 0; i < 4; i++) {
		while (1) {
			char option[40] = {0};
			strcpy(option,question[changeQuestionIndex].option[i]);
			gotoxy(45 + strlen(option), 8 + 3 * i);
			int res = inputCtrl(option, 40, 1);
			if (res == 1) return MANAGEQUESTIONWIN;
			if (res == 0) {
				strcpy(question[changeQuestionIndex].option[i],option);
				//新修改的题目更新并写入文件
				updateDataToFile(&question[changeQuestionIndex], sizeof(QUESTION_T), "data/question.dat", changeQuestionIndex * sizeof(QUESTION_T));
				gotoxy(75, 20);
				printf("修改成功！");
				gotoxy(71, 21);
				system("pause");
				gotoxy(75, 20);
				printf("          ");
				gotoxy(71, 21);
				printf("                    ");
				break;
			}
			gotoxy(70, 20);
			printf("输入不能为空,请重新输入");
			gotoxy(72, 21);
			system("pause");
			gotoxy(70, 20);
			printf("                               ");
			gotoxy(72, 21);
			printf("                    ");
		}
	}

	while (1) {
		char choose[2] = { 0 };
		strcpy(choose, question[changeQuestionIndex].answer);
		gotoxy(48 + strlen(choose), 20);
		int res = inputCtrl(choose, 1, 1);
		if (res == 1) return MANAGEQUESTIONWIN;
		if (res == 0) {
			if ((choose[0] == 'A' || choose[0] == 'B' || choose[0] == 'C' || choose[0] == 'D')) {
				strcpy(question[changeQuestionIndex].answer, choose);
				//新修改的题目更新并写入文件
				updateDataToFile(&question[changeQuestionIndex], sizeof(QUESTION_T), "data/question.dat", changeQuestionIndex * sizeof(QUESTION_T));
				gotoxy(75, 20);
				printf("修改成功！");
				gotoxy(71, 21);
				system("pause");
				gotoxy(75, 20);
				printf("          ");
				gotoxy(71, 21);
				printf("                    ");
				break;
			}
			else {
				gotoxy(70, 20);
				printf("选项输入错误,请重新输入");
				gotoxy(72, 21);
				system("pause");
				gotoxy(70, 20);
				printf("                               ");
				gotoxy(72, 21);
				printf("                    ");
				gotoxy(49, 20);
				printf("\b \b");
				choose[0] = '\0';
				continue;
			}
		}
		gotoxy(70, 20);
		printf("输入不能为空,请重新输入");
		gotoxy(72, 21);
		system("pause");
		gotoxy(70, 20);
		printf("                               ");
		gotoxy(72, 21);
		printf("                    ");
	}

	while (1) {
		char analysis[100] = {0};
		strcpy(analysis, question[changeQuestionIndex].analysis);
		gotoxy(48 + strlen(analysis), 23);
		int res = inputCtrl(analysis, 99, 1);
		if (res == 1) return MANAGEQUESTIONWIN;
		if (res == 0) {
			strcpy(question[changeQuestionIndex].analysis, analysis);
			//新修改的题目更新并写入文件
			updateDataToFile(&question[changeQuestionIndex], sizeof(QUESTION_T), "data/question.dat", changeQuestionIndex * sizeof(QUESTION_T));
			gotoxy(75, 20);
			printf("修改成功！");
			gotoxy(71, 21);
			system("pause");
			gotoxy(75, 20);
			printf("          ");
			gotoxy(71, 21);
			printf("                    ");
			break;
		}
		gotoxy(70, 20);
		printf("输入不能为空,请重新输入");
		gotoxy(72, 21);
		system("pause");
		gotoxy(70, 20);
		printf("                               ");
		gotoxy(72, 21);
		printf("                    ");
	}
	return MANAGEQUESTIONWIN;
}

int ManageExamPaperWin() {
	paintWindow(30, 6, 60, 18);
	gotoxy(50, 8);
	printf("* 传一考试系统考卷管理界面 *");
	gotoxy(45, 10);
	printf("欢迎%s管理员", user[loginIndex].name);
	gotoxy(65, 10);
	char date[20] = {0};
	getNowDate(date);
	printf("日期：%s",date);

	paintButton(50, 12, 20, 3, "1-创建考卷");
	paintButton(50, 15, 20, 3, "2-考卷列表");

	gotoxy(50, 20);
	printf("请选择：");
	char choose = 0;
	while (1) {
		choose = getch();
		if (choose == 27)
			return ADMWIN;
		if (choose == '1' || choose == '2') {
			putch(choose);
			break;
		}
	}
	switch (choose - '0') {
		case 1: return CREATEEXAMPAPERWIN; break;
		case 2: return EXAMPAPERLISTWIN; break;
	}
}

int CreateExamPaperWin(){
	paintWindow(25, 3, 70, 24);
    gotoxy(46, 5);
    printf("* 传一考试系统创建考卷界面 *");
    gotoxy(43, 7);
    printf("欢迎%s管理员", user[loginIndex].name);
    gotoxy(65, 7);
    char date[20] = { 0 };
    getNowDate(date);
    printf("日期：%s", date);
	
	gotoxy(37, 10);
	printf("试卷名称：");
	paintWindow(47, 9, 20, 3);
	paintButton(70, 9, 7, 3,"预览");
	
	gotoxy(37, 14);
	printf("试卷总分：");
	paintWindow(47, 13, 20, 3);
	
	gotoxy(37, 18);
	printf("试卷总题数：");
	paintWindow(49, 17, 18, 3);
	gotoxy(70,18);
	printf("当前最大总题数为：%d",questionNum);
	
	paintButton(37, 20, 15, 3,"自动生成考卷");
	
	gotoxy(37, 24);
	printf("按回车保存考卷，按ESC键返回");
	
	while (1) {
		memset(&exampaper[exampaperNum].title,0,sizeof(20));
		gotoxy(49,10);
		int res = inputCtrl(exampaper[exampaperNum].title, 20, 1);
		if (res == 1) return MANAGEEXAMPAPERWIN;
		if (res == 0) break;
		gotoxy(65, 21);
		printf("试卷名称不能为空,请重新输入");
		gotoxy(68, 22);
		system("pause");
		gotoxy(65, 21);
		printf("                               ");
		gotoxy(68, 22);
		printf("                    ");
	}
	
	while (1) {
		char score[4] = {0};
		gotoxy(49, 14);
		int res = inputCtrl(score, 3, 1);
		if (res == 1) return MANAGEEXAMPAPERWIN;
		if (res == 0) {
			if((score[0]>='1'&&score[0]<='9')||(score[0]>='1'&&score[0]<='9'&&score[1]>='0'&&score[1]<='9')
			||(score[0]>='1'&&score[0]<='9'&&score[1]>='0'&&score[1]<='9'&&score[2]>='0'&&score[2]<='9')){
				exampaper[exampaperNum].score = atoi(score);
				break;
			}
			gotoxy(63, 21);
			printf("只允许输入正整数,请重新输入");
			gotoxy(68, 22);
			system("pause");
			gotoxy(63, 21);
			printf("                               ");
			gotoxy(68, 22);
			printf("                    ");
			gotoxy(49, 14);
			printf("    ");
			continue;
		}
		gotoxy(65, 21);
		printf("输入不能为空,请重新输入");
		gotoxy(68, 22);
		system("pause");
		gotoxy(65, 21);
		printf("                               ");
		gotoxy(68, 22);
		printf("                    ");
	}
	
	while (1) {
		char num[3] = {0};
		gotoxy(51, 18);
		int res = inputCtrl(num, 2, 1);
		if (res == 1) return MANAGEEXAMPAPERWIN;
		if (res == 0) {
			if((num[0]>='1'&&num[0]<='9')||(num[0]>='1'&&num[0]<='9'&&num[1]>='0'&&num[1]<='9')){
				exampaper[exampaperNum].num = atoi(num);
				break;
			}
			gotoxy(63, 21);
			printf("只允许输入正整数,请重新输入");
			gotoxy(68, 22);
			system("pause");
			gotoxy(63, 21);
			printf("                               ");
			gotoxy(68, 22);
			printf("                    ");
			gotoxy(51, 18);
			printf("    ");
			continue;
		}
		gotoxy(65, 21);
		printf("输入不能为空,请重新输入");
		gotoxy(68, 22);
		system("pause");
		gotoxy(65, 21);
		printf("                               ");
		gotoxy(68, 22);
		printf("                    ");
	}
	
	char choose[1] = {0};
	gotoxy(51, 21);
	int res = inputCtrl(choose, 0, 1);
	if (res == 1) return MANAGEEXAMPAPERWIN;
	srand((unsigned int)time(NULL));
	int i = 0;
	int questionIdFlag[100] = {0};//试卷题目id是否存在的标记 
	for(i=0;i<exampaper[exampaperNum].num;i++){
		int flagIndex = rand()%questionNum;
		if(questionIdFlag[flagIndex] == 0){
			exampaper[exampaperNum].questionId[i] = flagIndex;
			questionIdFlag[flagIndex] = 1;
		}
		else i--;
	}
	
	exampaper[exampaperNum].id = exampaperNum + 1;
	strcpy(exampaper[exampaperNum].date, date);
	appendDataToFile(&exampaper[exampaperNum], sizeof(EXAMPAPER_T), "data/examrpaper.dat");
	exampaperNum++;
	
	gotoxy(76, 10);
	choose[1] = 0;
	res = inputCtrl(choose, 0, 1);
	
	if (res == 1) return MANAGEEXAMPAPERWIN;
	return EXAMPAPERPREVIEWWIN;
}

int ExamPaperPreviewWin() {
	int queryNum = ExamPaperIndex;//queryNum为当前考卷下标
	if (ExamPaperIndex == -1)
		queryNum = exampaperNum - 1;
	paintWindow(25, 4, 70, 22);
	gotoxy(48, 6);
	printf("* 传一考试系统%s *", exampaper[queryNum].title);
	gotoxy(43, 8);
	printf("欢迎%s管理员", user[loginIndex].name);
	gotoxy(65, 8);
	char date[20] = { 0 };
	getNowDate(date);
	printf("日期：%s", date);

	static int queryeIndex = 0;//当前题数下标 

	gotoxy(35, 10);
	printf("考试类型：%s", exampaper[queryNum].title);

	gotoxy(35, 12);
	int questionId = exampaper[queryNum].questionId[queryeIndex];
	printf("第%d题 分数：%d", queryeIndex + 1, question[questionId].score);

	gotoxy(35, 14);
	printf("题目：%s", question[questionId].title);

	int i = 0;
	for (i = 0; i < question[questionId].optionNum; i++) {
		gotoxy(35, 16 + i);
		printf("%s", question[questionId].option[i]);
	}

	gotoxy(35, 23);
	printf("按ESC键返回考卷管理界面");
	gotoxy(55, 21);
	printf("第%d题", queryeIndex + 1);
	if (queryeIndex == 0) {
		gotoxy(75, 23);
		printf("按->跳转到下一题");
	}
	else if (queryeIndex == exampaper[queryNum].num - 1) {
		gotoxy(75, 23);
		printf("按<-跳转到上一题");
	}
	else {
		gotoxy(60, 23);
		printf("按<-跳转到上一题 按->跳转到下一题");
	}

	char choose[3] = { 0 };
	int res = inputCtrl(choose, 2, 1);
	if (res == -1 || res == 1) {
		queryeIndex = 0;
		if (queryNum == ExamPaperIndex){
			ExamPaperIndex = -1;
			return EXAMPAPERLISTWIN;
		}
		else return MANAGEEXAMPAPERWIN; 
	}
	else if (res == 75) {
		if (queryeIndex > 0) queryeIndex--;
		else {
			gotoxy(75, 23);
			printf("                ");
			gotoxy(70, 23);
			printf("已经是第一题");
			gotoxy(70, 24);
			system("pause");
		}
	}
	else if (res == 77) {
		if (queryeIndex < exampaper[queryNum].num - 1) queryeIndex++;
		else {
			gotoxy(75, 23);
			printf("                ");
			gotoxy(70, 23);
			printf("已经是最后一题");
			gotoxy(70, 24);
			system("pause");
		}
	}
	queryNum = queryNum;
	return EXAMPAPERPREVIEWWIN;
}

int ExamPaperListWin() {
    paintWindow(20, 4, 80, 22);
    gotoxy(46, 6);
    printf("* 传一考试系统考卷列表界面 *");
    gotoxy(43, 8);
    printf("欢迎%s管理员", user[loginIndex].name);
    gotoxy(65, 8);
    char date[20] = { 0 };
    getNowDate(date);
    printf("日期：%s", date);

    gotoxy(40, 10);
    printf("查询试卷名称");
    paintWindow(53, 9, 20, 3);

    static int exampaperflag = 0;
    static EXAMPAPER_T queryExamPaper = { 0 };
    int page = (exampaperNum - 1) / 3 + 1;
    static int nowPage = 1;
    int i = 0, j = 0;
    int position[7][2] = { {55, 10}, {88, 15}, {94, 15},
                          {88, 17}, {94, 17}, {88, 19}, {94, 19} };
    static int nowPos = 0;
    static int pos = 7;
    gotoxy(31, 13);
    printf("序号");
    gotoxy(43, 13);
    printf("试卷名称");
    gotoxy(57, 13);
    printf("发布时间");
    gotoxy(72, 13);
    printf("出卷人");
    gotoxy(87, 13);
    printf("操作");

    if (exampaperflag == 0) {
        int nowExamPaperIndex = (nowPage - 1) * 3;
        int row = exampaperNum - nowExamPaperIndex >= 3 ? 3 : exampaperNum % 3;
        pos = row * 2 + 1;
        paintTable(25, 12, 6, row + 1, 5);
        gotoxy(38, 22);
        printf("<- -> 左右键翻页 %d/%d", nowPage, page);
        gotoxy(37, 23);
        printf("↑↓上下键切换选项 %d/%d", nowPos + 1, pos);
        for (i = 0; i < row; i++) {
            gotoxy(32, 15 + 2 * i);
            printf("%d", exampaper[nowExamPaperIndex + i].id);
            
            int len = strlen(exampaper[nowExamPaperIndex + i].title);
            gotoxy(47-len/2, 15 + 2 * i);
            printf("%s", exampaper[nowExamPaperIndex + i].title);
            
            gotoxy(56, 15 + 2 * i);
            printf("%s", exampaper[nowExamPaperIndex + i].date);
            
            gotoxy(72, 15 + 2 * i);
            printf("%s", user[loginIndex].name);
            paintWindow(82, 14 + 2 * i, 7, 3);
            gotoxy(84, 15 + 2 * i);
            printf("预览");
            paintWindow(88, 14 + 2 * i, 7, 3);
            gotoxy(90, 15 + 2 * i);
            printf("删除");
        }
    }
    else {
        paintTable(25, 12, 6, 2, 5);
        page = 1;
        pos = 3;
        gotoxy(38, 22);
        printf("<- -> 左右键翻页 %d/%d", nowPage, page);
        gotoxy(37, 23);
        printf("↑↓上下键切换选项 %d/%d", nowPos + 1, pos);
        gotoxy(32, 15);
        printf("%d", queryExamPaper.id);
        
        int len = strlen(queryExamPaper.title);
        gotoxy(47-len/2, 15 + 2 * i);
        printf("%s", queryExamPaper.title);
        
        gotoxy(56, 15 + 2 * i);
        printf("%s", queryExamPaper.date);
        
        gotoxy(72, 15);
        printf("%s", user[loginIndex].name);
        paintWindow(82, 14, 7, 3);
        gotoxy(84, 15);
        printf("预览");
        paintWindow(88, 14, 7, 3);
        gotoxy(90, 15);
        printf("删除");
    }

    gotoxy(position[nowPos][0], position[nowPos][1]);

    char c_exampapertitle[11] = { 0 };
    int res = inputCtrl(c_exampapertitle, 10, 1);
    if (res == -1) {
        ExamPaperIndex = (nowPos - 1) / 2 + (nowPage - 1) * 3;

        if (nowPos == 0) {
            exampaperflag = 0;
            nowPage = 1;
            return EXAMPAPERLISTWIN;
        }
        else if (nowPos == 1 || nowPos == 3 || nowPos == 5)
        	return EXAMPAPERPREVIEWWIN;
        memset(&exampaper[ExamPaperIndex], 0, sizeof(EXAMPAPER_T));
        exampaperNum--;
        for (i = ExamPaperIndex; i < exampaperNum; i++) {
            exampaper[i] = exampaper[i + 1];
            exampaper[i].id--;
        }
		memset(&exampaper[exampaperNum], 0, sizeof(EXAMPAPER_T));
        FILE* fp = fopen("data/examrpaper.dat", "wb+");
        fwrite(exampaper, sizeof(EXAMPAPER_T), exampaperNum, fp);
        fclose(fp);

        exampaperflag = 0;
        nowPage = 1;
        nowPos = 0;
        ExamPaperIndex = -1;
        return EXAMPAPERLISTWIN;
    }
    else if (res == 0) {
        char* title = (char*)malloc(10 * sizeof(char));
        for (i = 0; i < exampaperNum; i++) {
            memcpy(title, &exampaper[i].title, 10 * sizeof(char));
            if (strcmp(title, c_exampapertitle) == 0) {
                queryExamPaper = exampaper[i];
                free(title);
                exampaperflag = 1;
                nowPage = 1;
                nowPos = 0;
                return EXAMPAPERLISTWIN;
            }
        }
        free(title);
        exampaperflag = 0;
        nowPage = 1;
        gotoxy(65, 22);
        printf("该试卷不存在");
        gotoxy(65, 23);
        system("pause");
    }
    else if (res == 1) {
        exampaperflag = 0;
        nowPage = 1;
        nowPos = 0;
        return MANAGEEXAMPAPERWIN;
    }
    else if (res == 75) {
        if (nowPage > 1) {
            nowPage--;
            nowPos = 0;
        }
        else {
            gotoxy(65, 22);
            printf("已经是第一页");
            gotoxy(65, 23);
            system("pause");
        }
    }
    else if (res == 77) {
        if (nowPage < page) {
            nowPage++;
            nowPos = 0;
        }
        else {
            gotoxy(65, 22);
            printf("已经是最后一页");
            gotoxy(65, 23);
            system("pause");
        }
    }
    else if (res == 72) {
        if (nowPos > 0) {
            nowPos--;
        }
        else {
            gotoxy(65, 22);
            printf("已经是第一个选项");
            gotoxy(65, 23);
            system("pause");
        }
    }
    else if (res == 80) {
        if (nowPos < pos - 1) {
            nowPos++;
        }
        else {
            gotoxy(65, 22);
            printf("已经是最后一个选项");
            gotoxy(65, 23);
            system("pause");
        }
    }
    return EXAMPAPERLISTWIN;
}
