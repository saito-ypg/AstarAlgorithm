#include<iostream>
#include<cmath>
#include<algorithm>
#include "Aster.h"
//https://stone-program.com/python/algorithm/a-star-introduction/
//https://qiita.com/2dgames_jp/items/f29e915357c1decbc4b7
const int nonPath = 0;//0�͒ʂ�Ȃ��ꏊ�I
int Aster::heuristic(POS now)
{
	int x = target_.x_ - now.x_;
	int y = target_.y_ - now.y_;
	return pow(x,2) + pow(y,2);
}

Aster::Aster()
{
	
	map = {
		   {1,1,1,1,1,1},
		   {1,1,0,1,0,1},
		   {1,1,1,0,1,1},
		   {1,1,1,1,1,1},
		   {1,1,1,1,1,1},
		   {1,1,1,1,1,1},
	};//�e�v�f�̓R�X�g
	//openCells.reserve(10);
	//closeCells.reserve(10);

	

}

Aster::~Aster()
{
}

void Aster::BeginSearch()
{
	//CellMap.at(start_.y_).at(start_.x_).certainCost = 0;
	Cell startcell=Cell(start_);
	startcell.cCost = 0;
	openCells.push_back(startcell);
	openCells.front().cCost = 0;
	search();
}

void Aster::search()
{	

	while (true)
	{
		int min = INT_MAX;
		int index = -1;
		for (auto i = 0; i < openCells.size(); i++)
		{
			if (min > openCells.at(i).eCost)
			{
				min = openCells.at(i).eCost;
				index = i;
			}
		}
		Cell now;
		now=openCells.at(index);
		closeCells.push_back(openCells.at(index));
		openCells.erase(openCells.begin() + index);

		if (now.cellpos == target_)
		{
			std::cout << "�T�����I�����܂���" << std::endl;
			getRoute(now);
			std::reverse(Route.begin(),Route.end());
			return;
		}
		//�㉺���E����
		{//��
			POS next = { now.cellpos.x_,now.cellpos.y_ - 1 };
			checkNext(next, now);
		}
		{//��
			POS next = {now.cellpos.x_, now.cellpos.y_ + 1 };
			checkNext(next, now);
		} 
		{//�E
			POS next = {now.cellpos.x_+1, now.cellpos.y_ };
			checkNext(next, now);
		}
		{//��
			POS next = {now.cellpos.x_-1 , now.cellpos.y_ };
			checkNext(next, now);
		}
		if (openCells.empty()) {
			std::cout << "�S�[���ւ̌o�H�����݂��܂���" << std::endl;
			return;
		}
	}



//���݃m�[�h���S�[���m�[�h��������I��
	//�S�[���m�[�h��������Ȃ�������I��
}
void Aster::checkNext(POS next, Cell &nowCell)
{
	if (next.x_ >= mapX || next.x_ < 0 || next.y_ >= mapY || next.y_ < 0)//�͈͊O�Ȃ猩�Ȃ�
	{
		return;
	}
	if (map.at(next.y_).at(next.x_) == nonPath) //�ʂ�Ȃ��}�X�Ȃ猩�Ȃ�
	{
		return;
	}

	Cell nextcell(next);
	for(auto &i:closeCells)
	{
		if (i.cellpos == nextcell.cellpos)//close�ɂ���cell�Ȃ疳��
			return;
	}
	
	
	
	for (int i = 0; i < openCells.size(); i++)
	{
		auto& itrcell = openCells.at(i);
		if (itrcell.cellpos == nextcell.cellpos)//�ړI��cell�����ł�open�ɑ��݂���Ȃ�
		{
			if (itrcell.cCost > nowCell.cCost)//���R�X�g��r���āA���Ȃ���ΐe��now�ɂ��Ď��R�X�g�X�V�����������Ă邩
			{
				itrcell.parent = &nowCell;
			}
			return;
		}
	}


	{//cell�ǉ�����
		nextcell.parent = &nowCell;
		nextcell.cCost = nowCell.cCost + map[next.y_][next.x_];//���R�X�g�ǉ�
		nextcell.hCost = heuristic(next);//�����R�X�g
		nextcell.eCost = nextcell.cCost + nextcell.hCost;
		openCells.push_back(nextcell);
	}
	
}
void Aster::getRoute(Cell cell)
{
	Route.push_back(cell.cellpos);
	if(cell.parent!=nullptr)
		getRoute(*cell.parent);
}
void Aster::Show()
{
	for (auto i : Route)
	{
		std::cout << i.toString ()<< std::endl;
	}
}

