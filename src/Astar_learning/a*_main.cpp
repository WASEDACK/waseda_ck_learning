#include <iostream>
#include "a*.h"
using namespace std;
 
int main()
{
	//初始化地图，用二维矩阵代表地图，1表示障碍物，0表示可通
/*	vector<vector<int>> map={
		{1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,1,1,0,1,0,0,0,0,1},
		{1,0,0,1,1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,1,1,1},
		{1,1,1,0,0,0,0,0,1,1,0,1},
		{1,1,0,1,0,0,0,0,0,0,0,1},
		{1,0,1,0,0,0,0,1,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1}
	};
 */
    vector<vector<int>> map={
        {1,1,1,1,1},
        {1,0,0,0,1},
        {1,0,0,0,1},
        {1,1,1,1,1}
        
    };
    vector<vector<vector<double>>> real_map=
    {
        {{},{},{},{},{}},
        {{},{0,0},{0,3},{0,6},{}},
        {{},{0,1},{1,1},{1,2},{}},
        {{},{},{},{},{}}
        
    };
	Astar astar;
	astar.InitAstar(map,real_map);
 
	//设置起始和结束点
	Point start(1,1);
	//Point end(6,10);
    Point end(2,3);
	//A*算法找寻路径
	//list<Point *> path=astar.GetPath(start,end,false);
    list<Point *> path=astar.GetPath(start,end,true);
	//打印
	for(auto &p:path)
		cout<<'('<<p->x<<','<<p->y<<')'<<endl;
 
	system("pause");
	return 0;
}
