#include<iostream>
#include<cmath>
#include<algorithm>
#include "Aster.h"
//https://stone-program.com/python/algorithm/a-star-introduction/
//https://qiita.com/2dgames_jp/items/f29e915357c1decbc4b7
const int nonPath = 0;//0は通れない場所！
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
	Cell* startcell=new Cell(start_);
	startcell->cCost = 0;
	openCells.push_back(startcell);
	search();
}

void Aster::search()
{	

	while (true)
	{
		int min = INT_MAX;
		auto index = openCells.end();//目的
		for (auto i = openCells.begin(); i != openCells.end(); i++)
		{
			if (min > i->eCost)
			{
				min = i->eCost;
				index = i;
			}
		}
		closeCells.push_back(openCells.at(index));
		openCells.erase(openCells.begin() + index);
		Cell now = closeCells.back();
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
void Aster::checkNext(POS next,Cell nowCell)
{
	if(next.x_>=mapX||next.x_<0||next.y_>=mapY||next.y_<0)//範囲外なら見ない
	{
		return;
	}
		Cell nextcell(next);
	if (map.at(next.y_).at(next.x_) != nonPath //通れないマスではない
		&& (std::find(closeCells.begin(), closeCells.end(), nextcell) == closeCells.end()))//かつcloselistに入っていない
	{
		auto itr = std::find(openCells.begin(), openCells.end(), nextcell);
		if (itr == openCells.end())//openlistに入ってなかったら
		{//cell追加する
			nextcell.parent = &nowCell;
			nextcell.cCost = nowCell.cCost + map[next.y_][next.x_];//実コスト追加
			nextcell.hCost = heuristic(next);//推測コスト
			nextcell.eCost = nextcell.cCost + nextcell.hCost;
			openCells.push_back(nextcell);
		}
		else//入ってたら
		{
			int comp = nowCell.cCost + map[next.y_][next.x_];
			if (itr->cCost > comp)//実コスト比較して、少なければ親をnowにして実コスト更新←条件あってるか
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

//Aster::Cell Aster::Cell::operator=(const Cell& a)
//{
//	Cell retval;
//	retval.cellpos = a.cellpos;
//	retval.cCost = a.cCost;
//	retval.hCost = a.hCost;
//	retval.eCost = a.eCost;
//	retval.parent = a.parent;
//	return retval;
//}
