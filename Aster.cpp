#include<iostream>
#include<cmath>
#include "Aster.h"
#include<cmath>
#include<algorithm>
//https://stone-program.com/python/algorithm/a-star-introduction/
//https://qiita.com/2dgames_jp/items/f29e915357c1decbc4b7
const int nonPath = 0;//0�͒ʂ�Ȃ��ꏊ�I
int Aster::heuristic(POS now)
{
	//return abs(now.x_ - target_.x_) + abs(now.y_ - target_.y_);
	return now.x_ * now.x_ + now.y_ * now.y_;
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
	

	

}

Aster::~Aster()
{
}

void Aster::BeginSearch()
{
	//CellMap.at(start_.y_).at(start_.x_).certainCost = 0;
	Cell startcell(start_);
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
		Cell* now = &openCells.at(index);
		auto push = openCells.begin() + index;
		std::move(push,push,std::back_inserter(closeCells));
		//openCells.erase(openCells.begin() + index);//�����Ŏ���ł�H
		
		if (now->cellpos == target_)
		{
			std::cout << "�T�����I�����܂���" << std::endl;
			getRoute(now);
			std::reverse(Route.begin(),Route.end());
			return;
		}
		//�㉺���E����
		{//��
			POS next = { now.cellpos.x_,now.cellpos.y_ - 1 };
			checkNext(next, now);//�֐�����^�C�~���O�Őe������������Ă�
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
void Aster::checkNext(POS next,Cell nowCell)
{
	if(next.x_>=mapX||next.x_<0||next.y_>=mapY||next.y_<0)//�͈͊O�Ȃ猩�Ȃ�
	{
		return;
	}
		Cell nextcell(next);
	if (map.at(next.y_).at(next.x_) != nonPath //�ʂ�Ȃ��}�X�ł͂Ȃ�
		&& (std::find(closeCells.begin(), closeCells.end(), nextcell) == closeCells.end()))//����closelist�ɓ����Ă��Ȃ�
	{
		auto itr = std::find(openCells.begin(), openCells.end(), nextcell);
		if (itr == openCells.end())//openlist�ɓ����ĂȂ�������
		{//cell�ǉ�����
			nextcell.parent = &nowCell;
			nextcell.cCost = nowCell.cCost + map[next.y_][next.x_];//���R�X�g�ǉ�
			nextcell.hCost = heuristic(next);//�����R�X�g
			nextcell.eCost = nextcell.cCost + nextcell.hCost;
			openCells.push_back(nextcell);
		}
		else//�����Ă���
		{
			int comp = nowCell.cCost + map[next.y_][next.x_];
			if (itr->cCost > comp)//���R�X�g��r���āA���Ȃ���ΐe��now�ɂ��Ď��R�X�g�X�V�����������Ă邩
			{
				itr->parent = &nowCell;
				itr->cCost = comp;
			}
		}
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
