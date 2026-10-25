#ifndef _TOOL_H_
#define _TOOL_H_

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>

/*
函数名：gotoxy
函数功能：将光标移动到指定的 (x, y) 坐标位置
函数参数：int x 光标的水平位置（列）
		  int y 光标的垂直位置（行）
函数返回值：无返回值
*/
void gotoxy(int x, int y);

/*
函数名：inputCtrl
函数功能：循环输入英文或数字，可限制输入长度和设置是明文还是密文显示
函数参数：text-存输入数据的数组
		  len--最大输入个数
		  mode-明文/密文显示 1-明文 0-密文
函数返回值：返回一个整数值
			0：表示输入满足求
			1：表示用户按下了ESC键，希望返回开始界面
*/
int inputCtrl(char* text, int len, int mode);

/*
函数名:paintwindow
函数功能:实现窗口的绘制。
函数参数：startX--起始X坐标
		  startY--起始Y坐标
		  wide-宽,height-高
函数返回值:无
*/
void paintWindow(int startX, int startY, int wide, int height);

/*
函数名:paintButton
函数功能:实现按钮的绘制
函数参数:startX-起始X坐标
		 starty--起始Y坐标
		 wide-宽
		 height-高
		 text-文本
函数返回值:无
*/
void paintButton(int startX, int startY, int wide, int height, char text[10]);

/*
函数名:paintTable
函数功能:绘制表格函数
函数参数:startX-起始X坐标
		 starty--起始Y坐标
		 gridWidth-单元格的宽度
		 row-表格行
		 col-表格列
返回值:无
*/
void paintTable(int startX, int startY, int gridWidth, int row, int col);

/*
函数名:getNowDate
函数功能:获取当前日期(将当前日期保存到字符串中)
函数参数:date--当前日期 
返回值:无
*/
void getNowDate(char* date);

/*
函数名:getNowDateAndTime
函数功能:获取当前日期和时间(将当前日期和时间保存到字符串中)
函数参数:dt--当前日期和时间 
返回值:无
*/
void getNowDateAndTime(char* dt);
#endif
