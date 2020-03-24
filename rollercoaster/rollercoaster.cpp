// rollercoaster.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <stdio.h>
#include <map>
#include <iostream>
#include <cstring>


const int max_value = 1000;

int r;
int c;

int max_sum;
std::string max_sum_path;

struct node
{
	short happy_value;
	bool is_aready_sum;
	bool upper;
	bool right;
	bool left;
	bool down;

	short prev_r;
	short prev_c;
};
node* node_array;
//bool* bool_array;

void search(short c_r, short c_c, short prev_r, short prev_c, int cur_sum, std::string& cur_path);

//#define TEST

int main()
{
#ifdef TEST
	r = 3;
	c = 3;
#else
	//scanf_s("%d %d", &r, &c);
	std::cin >> r;
	std::cin >> c;
#endif

	if (r < 2 || c < 2)
	{
		printf("you must input bigger than 2\n");
		return 0;
	}

	if (r > 1000 || c > 1000)
	{
		printf("you must input value smaller then  1000\n");
		return 0;
	}
	
#ifdef TEST
	printf("r=%d, c=%d\n", r, c);
#endif

	node_array= new node[r*c];
	memset(node_array, 0, sizeof(node)*r*c);
#ifdef TEST
	node_array[0].happy_value = 5;
	node_array[1].happy_value = 1;
	node_array[2].happy_value = 3;

	node_array[3].happy_value = 2;
	node_array[4].happy_value = 4;
	node_array[5].happy_value = 8;

	node_array[6].happy_value = 1;
	node_array[7].happy_value = 1;
	node_array[8].happy_value = 2;
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
				printf("%d\n", node_array[i*r + j].happy_value);
			}
			else
			{
				printf("%d ", node_array[i*r + j].happy_value);
			}
		}
	}
#endif 

	
	std::string path_string;
	path_string.reserve(r*c);
	
	search(0, 0, 0, 0, 0, path_string);

	printf("%s\n", max_sum_path.c_str());

	
	 
    return 0;
}
 
void search(short c_r, short c_c, short prev_r, short prev_c, int cur_sum, std::string& cur_path)
{

	// 최종 위치에 도착
	if (c_r == r-1 && c_c == c-1)
	{
		if (cur_sum + node_array[c_r*r + c_c].happy_value > max_sum)
		{
			max_sum = cur_sum + node_array[c_r*r + c_c].happy_value;
			max_sum_path = cur_path;
		}
		node_array[c_r*r + c_c].is_aready_sum = false;
		
		search(prev_r, prev_c, node_array[prev_r*r + prev_c].prev_r, node_array[prev_r*r + prev_c].prev_c, cur_sum, cur_path);
	}
	else //이외
	{

		if (node_array[c_r*r + c_c].is_aready_sum == true || node_array[c_r*r + c_c].happy_value == 0 || c_r >= r || c_c >= c || c_r < 0 || c_c < 0)
		{
			//이전에 기록된 경로는 삭제
			if( cur_path.empty() == false)
				cur_path.pop_back();
			return;
		}

		while(1)
		{
			if (node_array[c_r*r + c_c].right == false && c_c < c  )
			{
				node_array[c_r*r + c_c].right = true;
				cur_sum += node_array[c_r*r + c_c].happy_value;
				cur_path += "R";
				node_array[c_r*r + c_c].is_aready_sum = true;
				search(c_r, c_c + 1, c_r, c_c, cur_sum, cur_path);
			}
			else if (node_array[c_r*r + c_c].left == false && c_c >= 0 )
			{
				node_array[c_r*r + c_c].left = true;
				cur_sum += node_array[c_r*r + c_c].happy_value;
				cur_path += "L";
				node_array[c_r*r + c_c].is_aready_sum = true;
				search(c_r, c_c - 1, c_r, c_c, cur_sum, cur_path);

			}
			else if (node_array[c_r*r + c_c].down == false && c_r < r)
			{
				node_array[c_r*r + c_c].down = true;
				cur_sum += node_array[c_r*r + c_c].happy_value;
				cur_path += "D";
				node_array[c_r*r + c_c].is_aready_sum = true;
				search(c_r + 1, c_c, c_r, c_c, cur_sum, cur_path);
			}
			else if (node_array[c_r*r + c_c].upper == false && c_r >= 0)
			{
				node_array[c_r*r + c_c].upper = true;
				cur_sum += node_array[c_r*r + c_c].happy_value;
				cur_path += "D";
				node_array[c_r*r + c_c].is_aready_sum = true;
				search(c_r - 1, c_c, c_r, c_c, cur_sum, cur_path);
			}
			else
			{
				if (prev_r == 0 && prev_c == 0)
				{
					return;
				}
				//4방량 탐색이 끝났다.
				return;
			}
		}
		
	}
}
