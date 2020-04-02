// LineFriends.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <map>
#include <set>
#include <list>
#include <vector>
using namespace std;

struct Line
{
	int _left  = 0;
	int _right = 0;
	bool isValid()
	{
		if (_left < -1000000 || _left > 1000000 || _right <= _left || _right < -1000000 || _right > 1000000)
			return false;

		return true;
	}
};

struct Question
{
	int _a = 0;
	int _b = 0;

	bool isValid(int line_num)
	{
		if (_a < 0 || _a == _b || _a >= line_num || _b < 0 || _b >= line_num)
			return false;
		return true;
	}
	void Solve(vector<Line> const& lines);
	int SolveSub(set<int>& prev_a, vector<Line>const& lines, list<int> friend_list, int relation_count);

	bool isFriend(vector<Line>const& lines, int a, int b)
	{
		if (a == b)
		{
			return false;
		}

		if ((lines[a]._left <= lines[b]._left && lines[a]._right >= lines[b]._left)
			|| (lines[a]._left <= lines[b]._right && lines[a]._right >= lines[b]._right))
		{
			return true;
		}
		return false;
	}

};


int _tmain(int argc, _TCHAR* argv[])
{
	int line_num = 0;
	int question_num = 0;
	vector<Line> lines;
	vector<Question> questions;

	cin >> line_num;
	
	if (line_num < 2 || line_num > 300)
	{
		cout << "wrong input line num:" << line_num;
		return 1;
	}
	
	//multimap<int, int> left_order_map;
	//multimap<int, int> right_order_map;

	lines.resize(line_num);
	for (int i = 0; i < line_num; i++)
	{
		cin >> lines[i]._left;
		cin >> lines[i]._right;
		if (lines[i].isValid() == false)
		{
			return 1;
		}
		//left_order_map.insert(make_pair(lines[i]._left, i));
		//right_order_map.insert(make_pair(lines[i]._right, i));
	}
	
	cin >> question_num;
	
	if (question_num < 1 || question_num > 300)
	{
		cout << "wrong input question_num:" << question_num;
		return 1;
	}
	questions.resize(question_num);
	for (int i = 0; i < question_num; i++)
	{
		cin >> questions[i]._a;
		cin >> questions[i]._b;

		// 0 base Index로 바꾸어줌 
		questions[i]._a--;
		questions[i]._b--;

		if (questions[i].isValid(line_num) == false)
		{
			cout << "wrong input question:" << questions[i]._a;
			return 1;
		}
	}

	for (int i = 0; i < question_num; i++)
	{
		questions[i].Solve(lines);
	}
			
	return 0;
}

void Question::Solve(vector<Line> const& lines)
{
	int relation_count = 1;
	if (isFriend(lines, _a, _b) == true)
	{
		cout << relation_count << endl;
		return;
	}
	list<int> friends_list;
	int i = 0;
	for(int i=0; i< lines.size(); i++)
	{
		int a = _a;
		if (true == isFriend(lines, a, i))
		{
			if (i == _b)
			{
				cout << relation_count << endl;
				return;
			}
			else if (i == _a)
			{
				continue;
			}
			else
			{
				friends_list.push_back(i);
			}
		}
	}
	if (friends_list.size() != 0)
	{
		bool is_fail = true;
		for (int a : friends_list)
		{
			set<int> prev_a;
			prev_a.insert(a);
			prev_a.insert(_a);
			if (SolveSub(prev_a, lines, friends_list, relation_count) == 0)
			{
				is_fail = false;
				return;
			}
		}
		if (is_fail == true)
		{
			cout << -1 << endl;
			return;
		}
	}
	else
	{
		cout << -1 << endl;
		return;
	}
}
int Question::SolveSub(set<int>& prev_a, vector<Line>const& lines, list<int> friend_list, int relation_count)
{
	relation_count++;
	list<int> new_friends_list;
	for (auto a : friend_list)
	{
		for (int i = 0; i < lines.size(); i++)
		{
			if(prev_a.find(i) != prev_a.end())
				continue;

			if (true == isFriend(lines, a, i))
			{
				if (i == _b)
				{
					cout << relation_count << endl;
					return 0;
				}
				else
				{
					new_friends_list.push_back(i);
				}
			}
		}
		if (new_friends_list.size() == 0)
		{
			return 1;
		}
	}

	for (int a : new_friends_list)
	{
		prev_a.insert(a);
		if (SolveSub(prev_a, lines, new_friends_list, relation_count) == 0)
			return 0;
	}

	relation_count++;
	
	return 1;
}