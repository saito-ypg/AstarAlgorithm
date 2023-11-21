#include<iostream>
#include<cmath>
#include "Aster.h"
#include<deque>

const int nonPath = 0;//0は通れない場所！
int Aster::heuristic(POS now)
{
	return abs(now.x_ - target_.x_) + abs(now.y_ - target_.y_);
}

Aster::Aster()
{
	
	map = {
		   {1,1,1,1,1,1},
		   {1,1,1,1,1,1},
		   {1,1,1,1,1,1},
		   {1,1,1,1,1,1},
		   {1,1,1,1,1,1},
		   {1,1,1,1,1,1},
	};//各要素はコスト
	

	CellMap.resize(mapY);
	for (int i = 0; i < mapY; i++)
	{
		CellMap.at(i).resize(mapX, Cell());
	}
	for (int i = 0; i < mapY; i++)
	{
		for(int j=0;j<mapX;j++)
		{
			CellMap.at(i).at(j).cellpos = POS{ j,i };
		}
	}

}

Aster::~Aster()
{
}

void Aster::Search(POS pos_)
{	
	std::deque<POS>poslist;//
	//上下左右見る
	{//上
		int next = pos_.y_-1;
		if (next >= 0 && map.at(next).at(pos_.x_) != nonPath);
		{
			
		}
}

void Aster::Show()
{
}
