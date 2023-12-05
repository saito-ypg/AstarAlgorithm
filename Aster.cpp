#include<iostream>
#include<cmath>
#include "Aster.h"
#include<cmath>
#include<algorithm>
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
	Search();
}

void Aster::Search()
{	
	int min = INT_MAX;
	int index = -1;
	for (auto i=0;i<openCells.size();i++)
	{
		if (min > openCells.at(i).cCost)
		{
			min = openCells.at(i).cCost;
			index = i;
		}
	}
	closeCells.push_back(openCells.at(index));
	openCells.erase(openCells.begin() + index);
	Cell& now = closeCells.back();

	//上下左右見る
	{//上
		POS next = { now.cellpos.y_-1,now.cellpos.x_};
		Cell nextcell(next);
		if (next.y_ >= 0 && map.at(next.y_).at(next.x_) != nonPath //範囲外もしくは通れないマスではない
			&& (std::find(closeCells.begin(),closeCells.end(),nextcell)==closeCells.end()))//かつcloselistに入っていない
		{
			auto itr = std::find(openCells.begin(), openCells.end(), nextcell);
			if (itr == openCells.end())//openlistに入ってなかったら
			{//cell追加する
				nextcell.parent = &now;
				nextcell.cCost = now.cCost + map[next.y_][next.x_];//実コスト追加
				nextcell.hCost = heuristic(next);//推測コスト
				nextcell.eCost = nextcell.cCost + nextcell.hCost;
			}
			else//入ってたら
			{
				int comp =now.cCost + map[next.y_][next.x_];
				if (itr->cCost > comp)//実コスト比較して、少なければ親をnowにして実コスト更新←条件あってるか
					itr->parent = &now;
				itr->cCost = comp;
			}
		}
	}






//現在ノードがゴールノードだったら終了
	//ゴールノードが見つからなかったら終了
}
void Aster::Show()
{
}
