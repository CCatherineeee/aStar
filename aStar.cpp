#include"aStar.h"
#include<graphics.h>
#include<conio.h>
#include<Windows.h>
#include<iostream>
using namespace std;

int map[101][101] =
{
	{0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0}
};

const int WIDTH_BLOCK_NUM = 20;
const int HEIGHT_BLOCK_NUM = 20;
const int WINDOWS_WIDTH = 400;
const int WINDOWS_HEIGHT = 400;


int width = WINDOWS_WIDTH / WIDTH_BLOCK_NUM;
int height = WINDOWS_HEIGHT / HEIGHT_BLOCK_NUM;
void aStar::Search(node* startPos, node* endPos)
{
	if (startPos->x<0||startPos->y<0||startPos->y>=size||startPos->x>=size||endPos->x>=size||endPos->y>=size)
		return;
	node* current;
	this->start = startPos;
	this->end = endPos;
	OpenList.push_back(startPos);
	while (OpenList.size() > 0)
	{
		current = OpenList[0];
		if (current->x == endPos->x && current->y == endPos->y)
		{
			//printMap();
			print(current);
			setfillcolor(RED);
			fillrectangle(3 * height, 3 * width, 3 * height + height, 3 * width + width);
			setfillcolor(RED);
			fillrectangle(15 * height, 15 * width, 15 * height + height, 15 * width + width);
			OpenList.clear();
			CloseList.clear();
			break;
		}
		next(current);
		CloseList.push_back(current);
		OpenList.erase(OpenList.begin());
		sort(OpenList.begin(), OpenList.end(), compare);
	}
	
}
void aStar::InsertPoit(int x, int y,node* father,int g)
{
	//cout << "**" << endl;
	//超出范围
	if (x < 0 || y < 0 ||y >= size ||x >= size )
		return;
	//为障碍
	if (map[x][y] == 1)
		return;
	int flag = 0;
	for (int i = 0; i < CloseList.size(); i++)
	{
		if (CloseList[i]->x == x && CloseList[i]->y == y)
		{
			flag = 1;
			break;
		}
	}
	if (flag)
		return;
	flag = -1;
	for (int i = 0; i < OpenList.size(); i++)
	{
		if (OpenList[i]->x == x && OpenList[i]->y == y)
		{
			flag = i;
			break;
		}
	}
	if (flag != -1)
	{
		node* point = OpenList[flag];
		if (point->G > father->G + g)
		{
			point->prio = father;
			point->G = father->G + g;
			point->F = point->G + point->H;
		}
	}
	else
	{
		node* point = new node(x, y, father);
		countGHF(point, end, g);
		OpenList.push_back(point);
		draw(x, y);
		Sleep(200);
	}

}
bool aStar::compare(node* n1, node* n2)
{
	return n1->F < n2->F;
}
void aStar::countGHF(node* sNode, node* eNode, int g)
{
	int h = abs(sNode->x - eNode->x) * WeightW + abs(sNode->y - eNode->y) * WeightW;
	int currentg = sNode->prio->G + g;
	int f = currentg + h;
	sNode->F = f;
	sNode->H = h;
	sNode->G = currentg;
}
void aStar::next(node* current)
{

	InsertPoit(current->x - 1, current->y, current, WeightW);//左
	InsertPoit(current->x + 1, current->y, current, WeightW);//右
	InsertPoit(current->x, current->y + 1, current, WeightW);//上
	InsertPoit(current->x, current->y - 1, current, WeightW);//下
	InsertPoit(current->x - 1, current->y + 1, current, WeightWH);//左上
	InsertPoit(current->x - 1, current->y - 1, current, WeightWH);//左下
	InsertPoit(current->x + 1, current->y - 1, current, WeightWH);//右下
	InsertPoit(current->x + 1, current->y + 1, current, WeightWH);//右上
}
//初始化地图
void aStar::init()
{
	setbkcolor(WHITE);
	setlinecolor(BLACK);
	settextcolor(BLACK);
	cleardevice();
	for (int i = 0; i < WINDOWS_WIDTH; i += width)
	{
		line(i, 0, i, WINDOWS_HEIGHT);
	}
	for (int i = 0; i < WINDOWS_HEIGHT; i += height)
	{
		line(0, i, WINDOWS_WIDTH, i);
	}
	//cleardevice();
	setfillcolor(GREEN);
	for(int i=0;i<size;i++)
		for (int j = 0; j < size; j++)
		{
			if (map[i][j] == 1)
				//fillrectangle(i * width, j * height, i * width+width, j * height+height);
				fillrectangle(j * height, i * width, j * height + height, i * width + width);

		}
	setfillcolor(RED);
	fillrectangle(3 * height, 3 * width, 3 * height + height, 3 * width + width);
	setfillcolor(RED);
	fillrectangle(15 * height, 15 * width, 15 * height + height, 15 * width + width);
	
}
void aStar::draw(int x,int y)
{
	setfillcolor(YELLOW);
	fillrectangle(y * height, x * width, y * height + height, x * width + width);
}
void aStar::print(node* current)
{
	if (current->prio != NULL)
		print(current->prio);
	setfillcolor(BLUE);
	fillrectangle(current->y * height, current->x * width, current->y * height + height, current->x * width + width);
	Sleep(200);
}