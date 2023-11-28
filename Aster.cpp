#include<iostream>
#include<cmath>
#include "Aster.h"
#include<deque>
//https://stone-program.com/python/algorithm/a-star-introduction/
//https://qiita.com/2dgames_jp/items/f29e915357c1decbc4b7
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
	

	/*CellMap.resize(mapY);
	for (int i = 0; i < mapY; i++)
	{
		CellMap.at(i).resize(mapX, Cell());
	}*/
	/*for (int i = 0; i < mapY; i++)
	{
		for(int j=0;j<mapX;j++)
		{
			CellMap.at(i).at(j).cellpos = POS{ j,i };
		}
	}*/

}

Aster::~Aster()
{
}

void Aster::BeginSearch()
{
	//CellMap.at(start_.y_).at(start_.x_).certainCost = 0;
	openCells.emplace(start_,Cell());
	Search(start_);
}

void Aster::Search(POS pos_)
{

	//上下左右見る
	{//上
		POS next = { pos_.y_ - 1, pos_.x_};
		if (next .y_>= 0 && map.at(next.y_).at(next.x_) != nonPath);
		{
			Cell &NextCell = CellMap.at(next.y_).at(next.x_);
			int h = heuristic(next);
			NextCell.estimationCost = h;
			NextCell.certainCost = CellMap.at(pos_.y_).at(pos_.x_).certainCost + 1;

		}
	}






//現在ノードがゴールノードだったら終了
	//ゴールノードが見つからなかったら終了
}
void Aster::Show()
{
}
