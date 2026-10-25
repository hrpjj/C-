#include "include/file.h"

FILE * file_open(char *fileName, void *data,int size){
	FILE* fp = fopen(fileName,"rb+");
	if(fp == NULL){
		fp = fopen(fileName,"wb+");
		fwrite(data,size,2,fp);
	}
	return fp;
}

int file_read(FILE *fp,void *data,int size){
	int num = 0;
	rewind(fp);
	while(fread((USER_T *)data+num,size,1,fp)){
		num++;
	}
	return num;
}

void file_add(char *fileName, void *data,int size){
	FILE* fp = fopen(fileName,"ab+");
	fwrite(data,size,1,fp);
}

void file_update(char *fileName,int position, void *data, int size){
	
}
