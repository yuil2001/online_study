// Helicopter.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

struct Point
{
	long long _x = 0;
	long long _y = 0;
};

int main()
{
	int l = 0;
	int n = 0;
	int m = 0;

	cin >> l;
	cin >> n;
	cin >> m;

	vector<Point> upper_bound;
	vector<Point> down_bound;
	if (n < 2 || n> 300 || n%2!=0)
	{
		cout << "input error n=" << n << endl;
		return 1;
	}

	if (m < 2 || m> 300 || m%2 != 0)
	{
		cout << "input error m=" << m << endl;
		return 1;
	}
	upper_bound.resize(n);
	for (int i = 0; i < n; i++)
	{
		cin >> upper_bound[i]._x;
		cin >> upper_bound[i]._y;
	}
	
	down_bound.resize(m);
	for (int i = 0; i < m; i++)
	{
		cin >> down_bound[i]._x;
		cin >> down_bound[i]._y;
	}
	double path_length = 0.0;
	
	int max_division_length = 0;
	multimap<long long, int> division_path_lengths;
	long long length = 0;
	int i = 0;
	for (i = 0; i < m-1; i++)
	{
		if (i % 2 == 0)
		{
			length = abs(down_bound[i + 1]._x - down_bound[i]._x);
			length += abs(down_bound[i + 1]._y - down_bound[i]._y);
		}
		else
		{
			length += abs(down_bound[i + 1]._x - down_bound[i]._x);
			length += abs(down_bound[i + 1]._y - down_bound[i]._y);
			division_path_lengths.insert(make_pair(length, i));
			length = 0;
		}
	}
	division_path_lengths.insert(make_pair(length, i));

	for (auto a : division_path_lengths)
	{
		path_length += a.first;
	}
	
	auto it = division_path_lengths.end();
	it--;
		
	path_length -= it->first;

	double len = sqrt(pow(down_bound[it->second]._x - down_bound[it->second - 2]._x, 2) + pow(down_bound[it->second]._y - down_bound[it->second - 2]._y, 2));
	path_length += len;

	cout << path_length << endl;

    return 0;
}

