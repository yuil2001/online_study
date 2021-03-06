// rollercoaster.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <stdio.h>
#include <map>
#include <iostream>
#include <cstring>
#include <vector>



const int max_value = 1000;

int r;
int c;

int max_sum;
std::string max_sum_path;

struct node
{
	short happy_value =0;
	bool is_aready_sum = false;
	bool up = false;
	bool right = false;
	bool left = false;
	bool down = false;

	short prev_r = 0;
	short prev_c = 0;
};

std::vector<node> node_array;

int search(std::string& cur_path);
void clear_history(short c_r, short c_c);


#define TEST

int main()
{

#ifdef TEST
	r = 4;
	c = 4;
#else
	//scanf_s("%d %d", &r, &c);
	std::cin >> r;
	std::cin >> c;
#endif

	if (r < 2 || c < 2)
	{
		std::cout << "you must input bigger than 2" << std::endl;
		return 0;
	}

	if (r > 1000 || c > 1000)
	{
		std::cout << "you must input value smaller then  1000" << std::endl;
		return 0;
	}
	
#ifdef TEST
	std::cout << r <<" " << c << std::endl;
#endif

	node_array.reserve(r*c);
	for (int i = 0; i < r*c; i++)
	{
		node node_default;
		node_array.push_back(node_default);
	}
#ifdef TEST
	
	node_array[0].happy_value = 5;
	node_array[1].happy_value = 1;
	node_array[2].happy_value = 3;
	node_array[3].happy_value = 3;

	
	node_array[4].happy_value = 4;
	node_array[5].happy_value = 0;
	node_array[6].happy_value = 1;
	node_array[7].happy_value = 1;

	node_array[8].happy_value = 2;
	
	node_array[9].happy_value = 1;
	
	node_array[10].happy_value = 2;
	node_array[11].happy_value = 0;

	node_array[12].happy_value = 2;
	node_array[13].happy_value = 2;
	node_array[14].happy_value = 1;
	node_array[15].happy_value = 2;
	
#else
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			std::cin >> node_array[i*r + j].happy_value;
		}
	}
#endif

#ifdef TEST
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			if (j == c - 1)
			{
				std::cout << node_array[i*r + j].happy_value << std::endl;
			}
			else
			{
				std::cout << node_array[i*r + j].happy_value << " ";
			}
		}
	}
#endif 
		
	std::string path_string;
	path_string.reserve(r*c);
	
	search(path_string);

	std::cout << max_sum_path.c_str() << std::endl;
		
	 
    return 0;
}
 
int search_sub(short& c_r, short& c_c, short& prev_r, short& prev_c)
{
	if (c_r >= r || c_c >= c || c_r < 0 || c_c < 0 || node_array[c_r*r + c_c].is_aready_sum == true || node_array[c_r*r + c_c].happy_value == 0)
	{
		// 유효하지 않으면 에러코드를 반환
		c_r = prev_r;
		c_c = prev_c;
		prev_c = node_array[c_r*r + c_c].prev_c;
		prev_r = node_array[c_r*r + c_c].prev_r;
		return 1;
	}

	node_array[c_r*r + c_c].prev_c = prev_c;
	node_array[c_r*r + c_c].prev_r = prev_r;
	
	return 0;
}

int search(std::string& cur_path)
{

	int ret = 0;
	short c_r = 0;
	short c_c = 0;
	short prev_r = 0; 
	short prev_c = 0;
	short cur_sum = 0;
	/*
	node_array[0].prev_c = -1;
	node_array[0].prev_r = -1;
	*/


	while (1)
	{
		if (c_r == r - 1 && c_c == c - 1)
		{
			if (cur_sum + node_array[c_r*r + c_c].happy_value > max_sum)
			{
				max_sum = cur_sum + node_array[c_r*r + c_c].happy_value;
				max_sum_path = cur_path;
			}
			node_array[c_r*r + c_c].is_aready_sum = false;

			if (cur_path.empty() == false)
				cur_path.pop_back();

			c_c = node_array[c_r*r + c_c].prev_c;
			c_r = node_array[c_r*r + c_c].prev_r;

			prev_c = node_array[c_r*r + c_c].prev_c;
			prev_r = node_array[c_r*r + c_c].prev_r;
		
		}
		else if (node_array[c_r*r + c_c].right == false && c_c < c)
		{
			node_array[c_r*r + c_c].right = true;
			cur_sum += node_array[c_r*r + c_c].happy_value;
			cur_path += "R";
			node_array[c_r*r + c_c].is_aready_sum = true;
			prev_c = c_c;
			prev_r = c_r;
			c_c += 1;
			ret = search_sub(c_r, c_c, prev_r, prev_c);
			if (ret == 1)
			{
				if (cur_path.empty() == false)
					cur_path.pop_back();
			}
		}
		else if (node_array[c_r*r + c_c].left == false && c_c >= 0)
		{
			node_array[c_r*r + c_c].left = true;
			cur_sum += node_array[c_r*r + c_c].happy_value;
			cur_path += "L";
			node_array[c_r*r + c_c].is_aready_sum = true;
			prev_c = c_c;
			prev_r = c_r;
			c_c -= 1;
			ret = search_sub(c_r, c_c, prev_r, prev_c);
			if (ret == 1)
			{
				if (cur_path.empty() == false)
					cur_path.pop_back();
			}
		}
		else if (node_array[c_r*r + c_c].down == false && c_r < r)
		{
			node_array[c_r*r + c_c].down = true;
			cur_sum += node_array[c_r*r + c_c].happy_value;
			cur_path += "D";
			node_array[c_r*r + c_c].is_aready_sum = true;
			prev_c = c_c;
			prev_r = c_r;
			c_r += 1;
			ret = search_sub(c_r, c_c, prev_r, prev_c);
			if (ret == 1)
			{
				if (cur_path.empty() == false)
					cur_path.pop_back();
			}
		}
		else if (node_array[c_r*r + c_c].up == false && c_r >= 0)
		{
			node_array[c_r*r + c_c].up = true;
			cur_sum += node_array[c_r*r + c_c].happy_value;
			cur_path += "U";
			node_array[c_r*r + c_c].is_aready_sum = true;
			prev_c = c_c;
			prev_r = c_r;
			c_r -= 1;
			ret = search_sub(c_r, c_c, prev_r, prev_c);
			if (ret == 1)
			{
				if (cur_path.empty() == false)
					cur_path.pop_back();
			}
		}
		else
		{
			//4방량 탐색이 끝났다.

			// 0, 0으로 돌아왔으면 종료
			if (c_c == 0 && c_r == 0)
			{
				return 0;
			}

			cur_sum -= node_array[c_r*r + c_c].happy_value;

			clear_history(c_r, c_c);

			c_c = node_array[c_r*r + c_c].prev_c;
			c_r = node_array[c_r*r + c_c].prev_r;

			prev_c = node_array[c_r*r + c_c].prev_c;
			prev_r = node_array[c_r*r + c_c].prev_r;
			
		}
	}
	
}

void clear_history(short c_r, short c_c)
{
	return;
	if (c_r >= r || c_c >= c || c_r < 0 || c_c < 0)
		return;

	node_array[c_r*r + c_c].is_aready_sum = false;
	node_array[c_r*r + c_c].left = false;
	node_array[c_r*r + c_c].right = false;
	node_array[c_r*r + c_c].up = false;
	node_array[c_r*r + c_c].down = false;
}