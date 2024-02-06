#include<iostream>
#include<cmath>
#include<algorithm>
#include "Aster.h"
//https://stone-program.com/python/algorithm/a-star-introduction/
//https://qiita.com/2dgames_jp/items/f29e915357c1decbc4b7
const int nonPath = 0;//0は通れない場所！
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
	};//各要素はコスト
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
			std::cout << "探索が終了しました" << std::endl;
			getRoute(now);
			std::reverse(Route.begin(),Route.end());
			return;
		}
		//上下左右見る
		{//上
			POS next = { now.cellpos.x_,now.cellpos.y_ - 1 };
			checkNext(next, now);
		}
		{//下
			POS next = {now.cellpos.x_, now.cellpos.y_ + 1 };
			checkNext(next, now);
		} 
		{//右
			POS next = {now.cellpos.x_+1, now.cellpos.y_ };
			checkNext(next, now);
		}
		{//左
			POS next = {now.cellpos.x_-1 , now.cellpos.y_ };
			checkNext(next, now);
		}
		if (openCells.empty()) {
			std::cout << "ゴールへの経路が存在しません" << std::endl;
			return;
		}
	}



//現在ノードがゴールノードだったら終了
	//ゴールノードが見つからなかったら終了
}
void Aster::checkNext(POS next, Cell &nowCell)
{
	if (next.x_ >= mapX || next.x_ < 0 || next.y_ >= mapY || next.y_ < 0)//範囲外なら見ない
	{
		return;
	}
	if (map.at(next.y_).at(next.x_) == nonPath) //通れないマスなら見ない
	{
		return;
	}

	Cell nextcell(next);
	for(auto &i:closeCells)
	{
		if (i.cellpos == nextcell.cellpos)//closeにあるcellなら無視
			return;
	}
	
	
	
	for (int i = 0; i < openCells.size(); i++)
	{
		auto& itrcell = openCells.at(i);
		if (itrcell.cellpos == nextcell.cellpos)//目的のcellがすでにopenに存在するなら
		{
			if (itrcell.cCost > nowCell.cCost)//実コスト比較して、少なければ親をnowにして実コスト更新←条件あってるか
			{
				itrcell.parent = &nowCell;
			}
			return;
		}
	}


	{//cell追加する
		nextcell.parent = &nowCell;
		nextcell.cCost = nowCell.cCost + map[next.y_][next.x_];//実コスト追加
		nextcell.hCost = heuristic(next);//推測コスト
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

