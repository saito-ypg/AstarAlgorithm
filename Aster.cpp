#include<iostream>
#include<iomanip>
#include<cmath>
#include<algorithm>
#include "Aster.h"
//https://stone-program.com/python/algorithm/a-star-introduction/
//https://qiita.com/2dgames_jp/items/f29e915357c1decbc4b7
namespace {
	const int nonPath = 0;//0は通れない場所！
}
int Aster::heuristic(POS now)
{
	int x = target_.x_ - now.x_;
	int y = target_.y_ - now.y_;
	return pow(x,2) + pow(y,2);
}

Aster::Aster()
{
	map = {
		   {1,1,40,1,1,1},
		   {1,1,0,1,0,1},
		   {1,1,1,0,1,3},
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
	if (map.at(start_.y_).at(start_.x_)==nonPath||
		start_.y_<0||start_.y_>=mapY||
		start_.x_<0||start_.x_>=mapX)
	{
		std::cout << "スタート位置が不正です！" << std::endl;
		return;
	}
	//CellMap.at(start_.y_).at(start_.x_).certainCost = 0;
	Cell startcell=Cell(start_);
	startcell.cCost = 0;
	startcell.hCost = heuristic(start_);
	startcell.eCost = startcell.cCost + startcell.hCost;
	openCells.push_back(startcell);
	openCells.front().cCost = 0;
	search();
}

void Aster::search()
{	

	while (true)
	{
		int min = INT_MAX;
		auto minitr = openCells.end();
		for (auto it = openCells.begin(); it != openCells.end(); ++it)
		{
			if (min > it->eCost)
			{
				min = it->eCost;
				minitr = it; // イテレーターを更新
			}
		}
		Cell* now = &(*minitr); // イテレーターを通じてセルにアクセス
		closeCells.splice(closeCells.end(), openCells, minitr); // openCells から closeCells に移動
		if (now->cellpos == target_)
		{
			std::cout << "探索が終了しました" << std::endl;
			getRoute(*now);
			std::reverse(Route.begin(),Route.end());
			Show();
			return;
		}
		//上下左右見る
		{//上
			POS next = { now->cellpos.x_,now->cellpos.y_ - 1 };
			checkNext(next, now);
		}
		{//下
			POS next = {now->cellpos.x_, now->cellpos.y_ + 1 };
			checkNext(next, now);
		} 
		{//右
			POS next = {now->cellpos.x_+1, now->cellpos.y_ };
			checkNext(next, now);
		}
		{//左
			POS next = {now->cellpos.x_-1 , now->cellpos.y_ };
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
void Aster::checkNext(POS next, Cell *const nowCell)
{
	if (next.x_ >= mapX || next.x_ < 0 || next.y_ >= mapY || next.y_ < 0)//範囲外なら見ない
	{
		return;
	}
	if (map.at(next.y_).at(next.x_) == nonPath) //通れないマスなら見ない
	{
		return;
	}

	
	for(auto &i:closeCells)
	{
		if (i.cellpos ==next)//closeにあるcellなら無視
			return;
	}
	
	
	
	for (auto& it:openCells)
	{
		if (it.cellpos == next)//目的のcellがすでにopenに存在するなら
		{
			if (it.cCost > nowCell->cCost)//実コスト比較して、少なければ親をnowにして実コスト更新←条件あってるか
			{
				it.parent = nowCell;
			}
			return;
		}
	}


	{//cell追加する
		Cell nextcell(next);
		nextcell.parent = nullptr;
		nextcell.parent = nowCell; // 最初に親を設定
		nextcell.cCost = nowCell->cCost + map[next.y_][next.x_]; // 実コスト追加
		nextcell.hCost = heuristic(next); // 推測コスト
		nextcell.eCost = nextcell.cCost + nextcell.hCost;
		openCells.push_back(nextcell);
		int i = 0;
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
	using std::cout;
	using std::endl;
	for (int x = 0; x < (mapX+1) * 2; x++)
	{
		cout << "*";
	}
	cout << endl;
	for (int y=0;y<mapY;y++)
	{
		cout << "*";
		for (int x=0;x<mapX;x++)
		{
			
			int& cell = map.at(y).at(x);
			if (cell == nonPath)
			{
				cout << std::setw(2) << "■";
			}
			else if (POS(x, y) == start_)
			{
				cout << std::setw(2) << "S";
			}
			else if (POS(x, y) == target_)
			{
				cout << std::setw(2) << "G";
			}
			
			else
			{
				cout << std::setw(2) << cell;
			}
		}
		cout << "*";
		cout<<endl;
	}
	for (int x = 0; x <( mapX+1) * 2; x++)
	{
		cout << "*";
	}
	cout << endl;
	cout << "↓" << endl;
	
	for (auto i : Route)
	{
		map.at(i.y_).at(i.x_) = INT_MAX;
	}

	for (int x = 0; x < (mapX + 1) * 2; x++)
	{
		cout << "*";
	}
	cout << endl;
	for (int y = 0; y < mapY; y++)
	{
		cout << "*";
		for (int x = 0; x < mapX; x++)
		{

			int& cell = map.at(y).at(x);
			if (cell == nonPath)
			{
				cout << std::setw(2) << "■";
			}
			else if (POS(x, y) == start_)
			{
				cout << std::setw(2) << "S";
			}
			else if (POS(x, y) == target_)
			{
				cout << std::setw(2) << "G";
			}

			else if (cell == INT_MAX)
			{
				cout << std::setw(2) << "◇";
			}
			else cout << std::setw(2)<<" ";
		}
		cout << "*";
		cout << endl;
	}
	for (int x = 0; x < (mapX + 1) * 2; x++)
	{
		cout << "*";
	}
	cout << endl;

}

