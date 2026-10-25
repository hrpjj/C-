#include <stdio.h>
#include "include/tool.h"

void gotoxy(int x, int y) {
	HANDLE hOut;
	COORD pos = { x, y };
	// 光标的起始位（第1列，第3行） 0是第1列 2是第3行
	// STD_OUTPUT_HANDLE：标准输出的句柄 
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
	// printf("定位光标位置搜索（%d,%d）\n"),pos.X,pos.Y);
}

int inputCtrl(char* text, int len, int mode) {
	int i = strlen(text);//该功能的加入导致了众多bug，故应该养成输入前使用memset的习惯 
	int flag = i==0?1:0;
	while (1) {
		text[i] = getch();
		if (text[i] == '\b' && i > 0) {
			//删除时区分中英文字符 
			if((unsigned char)text[i-1] > 127){
				i-=2;
				printf("\b\b  \b\b");
			}
			else{
				i--;
				printf("\b \b");
			}
			continue;
		}
		if (text[i] == '\r') {
			text[i] = '\0';
			if(i) return 0;
			return -1;
		}
		if (text[i] == 27) {
			if(flag) text[0] = '\0';
			else text[i] = '\0';
			return 1;
		}
		 // 处理方向键的输入
		if(text[i] == -32) return getch();
		 
		 // 处理中文字符的输入(用 (unsigned char) 类型转换，确保取值范围为 0~255，使中文字符被正确识别)
        if (i < len &&(unsigned char)text[i] > 127) {
        	char* chinese = (char*)malloc(3 * sizeof(char));
			memcpy(chinese, &text[i], sizeof(char));
    		chinese[1] = getch();
    		chinese[2] = '\0';
    		printf("%s", chinese);
    		memcpy(&text[i], chinese, 3 * sizeof(char));
    		i+=2;
    		free(chinese);
        }
		
		if (i < len && (text[i] >= '0' && text[i] <= '9' ||
			text[i] >= 'a' && text[i] <= 'z' ||
			text[i] >= 'A' && text[i] <= 'Z')) {
			if (!mode && ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z')))
				continue;
			putch(text[i]);
			i++;
			if (!mode) {
				Sleep(50);
				printf("\b");
				putch('*');
			}
		}
	}
}

//╔ ═ ╗║╚  ═  ╝
void paintWindow(int startX, int startY, int wide, int height) {
	int i = 0;
	gotoxy(startX, startY);
	printf("╔");
	for (i = 0; i < wide - 2; i++)
		printf("═");
	printf("╗");

	for (i = 0; i < height - 2; i++) {
		gotoxy(startX, startY + i + 1);
		printf("║");
		gotoxy(startX + wide - 1, startY + i + 1);
		printf("║");
	}

	gotoxy(startX, startY + height - 1);
	printf("╚");
	for (i = 0; i < wide - 2; i++)
		printf("═");
	printf("╝");
}

void paintButton(int startX, int startY, int wide, int height, char text[10]) {
	paintWindow(startX, startY, wide, height);
	int offset_x = (wide - strlen(text)) / 2 + 1;
	int offset_y = height / 2;
	gotoxy(startX + offset_x, startY + offset_y);
	printf("%s", text);
}

//'┌','┬','┐','├','┼','┤','└','┴','┘','─','│'
void paintTable(int startX, int startY, int gridWidth, int row, int col) {
	int i = 0, j = 0, k = 0;
	gotoxy(startX, startY);

	printf("┌ ");
	for (i = 0; i < col; i++) {
		for (j = 0; j < gridWidth; j++)
			printf("─ ");
		if (i != col - 1)
			printf("┬ ");
	}
	printf("┐");


	for (i = 0; i < row; i++) {
		for (j = 0; j < col + 1; j++) {
			gotoxy(startX + j * (gridWidth + 1) * 2, startY + 2 * i + 1);
			printf("│ ");
		}
	}

	for (i = 1; i < row; i++) {
		gotoxy(startX, startY + 2 * i);
		printf("├ ");
		for (j = 0; j < col; j++) {
			for (k = 0; k < gridWidth; k++)
				printf("─ ");
			if (j != col - 1)
				printf("┼ ");
		}
		printf("┤");
	}

	gotoxy(startX, startY + 2 * row);
	printf("└ ");
	for (i = 0; i < col; i++) {
		for (j = 0; j < gridWidth; j++)
			printf("─ ");
		if (i != col - 1)
			printf("┴ ");
	}
	printf("┘");
}

void getNowDate(char* date){
	//日期从1900年开始计算，月份为0-11 
	time_t now = time(NULL);
	struct tm* nowTime = localtime(&now);
	sprintf(date,"%04d-%02d-%02d",
		nowTime->tm_year+1900,nowTime->tm_mon+1,nowTime->tm_mday);
}

void getNowDateAndTime(char* dt){
	//日期从1900年开始计算，月份为0-11 
	time_t now = time(NULL);
	struct tm* nowTime = localtime(&now);
	sprintf(dt,"%04d-%02d-%02d %02d:%02d:%02d",
		nowTime->tm_year+1900,nowTime->tm_mon+1,nowTime->tm_mday,
		nowTime->tm_hour,nowTime->tm_min,nowTime->tm_sec);
}
