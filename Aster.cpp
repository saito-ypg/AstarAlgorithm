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
	

	

}

Aster::~Aster()
{
}

void Aster::BeginSearch()
{
	//CellMap.at(start_.y_).at(start_.x_).certainCost = 0;
	Cell startcell(start_);
	openCells.push_back(startcell);
	openCells.front().certainCost = 0;
	Search();
}

void Aster::Search()
{	
	int min = INT_MAX;
	int index = -1;
	for (auto i=0;i<openCells.size();i++)
	{
		if (min > openCells.at(i).certainCost)
		{
			min = openCells.at(i).certainCost;
			index = i;
		}
	}
	closeCells.push_back(openCells.at(index));
	openCells.erase(openCells.begin() + index);
	Cell& now = closeCells.back();

	//�㉺���E����
	{//��
		POS next = { now.cellpos.y_-1,now.cellpos.x_};
		Cell nextcell(next);
		if (next.y_ >= 0 && map.at(next.y_).at(next.x_) != nonPath //�͈͊O�������͒ʂ�Ȃ��}�X����Ȃ�
			&& (std::find(closeCells.begin(),closeCells.end(),nextcell)==closeCells.end()))//����closelist�ɓ����Ă��Ȃ�
		{
		

		}
	}






//���݃m�[�h���S�[���m�[�h��������I��
	//�S�[���m�[�h��������Ȃ�������I��
}
void Aster::Show()
{
}
