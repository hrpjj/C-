#ifndef _FILE_H_
#define _FILE_H_

#include "data.h"

/*
函数名:file open
函数功能:打开文件，若文件不存在，则自动创建，
		 并写入初始化数据实现对文件的初始化
函数参数:fileName--文件名
		 data--写入的初始化数据首地址
		 size--写入文件的数据大小
返回值:返回文件指针fp
*/
FILE* file_open(char *fileName, void *data,int size);

/*
函数名:file_read
函数功能:读文件的数据，写入结构体数组中
函数参数:fp--文件指针
		 data--读取文件数据写入内存的首地址
		 size--每次读取一块数据的大小
返回值:返回结构体数据的个数
*/
int file_read(FILE *fp,void *data,int size);

/*
函数名:file add
函数功能:文件以追加方式写入新数据
函数参数:fileName--文件名
		 data--写入的新数据的首地址
		 size--数据的大小
返回值:无
*/
void file_add(char *fileName, void *data,int size); 

/*
函数名:file_update
函数功能:文件数据局部修改
函数参数:fileName-文件名
		 position-偏移位置
		 data--写入数据的地址
		 size-写入数据的大小
返回值:无
*/
void file_update(char *fileName,int position, void *data, int size);

#endif
