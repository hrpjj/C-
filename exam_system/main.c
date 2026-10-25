#include "include/view.h"

int main(int argc, char* argv[]) {
	initUsers();
	initQuestions();
	initExamRecords();
	initExamPapers();
	
	int (*fp[])() = {initWin,loginWin,regWin,admWin,stuWin,updatePwdWin,searchUsersWin,
					showAllUsersWin,showSomeUsersWin,showExamWin,admShowScoreWin,stuShowScoreWin,
					ManageQuestionWin,IncreaseQuestionWin,ChangeQuestionWin,
					ManageExamPaperWin,CreateExamPaperWin,ExamPaperPreviewWin,ExamPaperListWin};
	
	int winCode = INITWIN;
	
	while (1) {
		system("cls"); 
		winCode = fp[winCode]();
		if(winCode==-1) exit(0);
	}
	return 0;
}

