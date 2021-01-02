#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include<algorithm>
using namespace std;

struct node
{
	int x;
	int y;
	int G, H, F;
	node* prio;
	node(int x, int y)
	{
		this->x = x;
		this->y = y;
		this->G = 0;
		this->F = 0;
		this->H = 0;
		this->prio = NULL;
	}
	node(int x, int y,node* prio)
	{
		this->x = x;
		this->y = y;
		this->G = 0;
		this->F = 0;
		this->H = 0;
		this->prio = prio;
	}

};
class aStar
{
public:
	vector<node*>OpenList;
	vector<node*>CloseList;
	node* end, *start;
	static const int WeightW = 10;
	static const int WeightWH = 14;
	static const int size = 20;
	void Search(node* startPos, node* endPos);
	void next(node* current);
	void InsertPoit(int x, int y,node* father,int g);
	void countGHF(node* sNode, node* eNode, int g);
	static bool compare(node* n1, node* n2);
	void init();
	void draw(int x,int y);
	void print(node* current);

};