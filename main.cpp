#include<iostream>
#include<graphics.h>
#include<conio.h>
#include"aStar.h"
using namespace std;

int main()
{
	aStar a;
	initgraph(400, 400);
	a.init();
	node* s = new node(3, 3);
	node* e = new node(15, 15);
	a.Search(s, e);
	getchar();
	closegraph();

}