#include<iostream>
#include<cmath>
#include "Aster.h"
#include<deque>

const int nonPath = 0;//0�͒ʂ�Ȃ��ꏊ�I
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
	};//�e�v�f�̓R�X�g
	

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
	//�㉺���E����
	{//��
		int next = pos_.y_-1;
		if (next >= 0 && map.at(next).at(pos_.x_) != nonPath);
		{
			
		}
}

void Aster::Show()
{
}
