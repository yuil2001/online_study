// LineFriends.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

struct Line
{
	int _left  = 0;
	int _right = 0;

};
int _tmain(int argc, _TCHAR* argv[])
{
	int line_num = 0;
	int question_num = 0;
	Line* lines = nullptr;
	cin >> line_num;
	
	if (line_num < 2 || line_num > 300)
	{
		cout << "wrong input line num:" << line_num;
		return 1;
	}
	
	lines = new Line[line_num];
	for (int i = 0; i < line_num; i++)
	{
		cin >> lines[i]._left;
		cin >> lines[i]._right;
	}

	cin >> question_num;
	

	
	if (lines != nullptr)
	{
		delete[] lines;
	}
	
	
	return 0;
}


