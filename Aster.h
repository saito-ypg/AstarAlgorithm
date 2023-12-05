#pragma once
#include<vector>
#include<map>
using std::vector;
const int mapX = 6, mapY =6;

class Aster
{
public:
	struct POS {
		int x_; int y_;
		POS() :x_(-1), y_(-1) {} 
		POS(int x, int y):x_(x),y_(y){} 
		bool operator==(const POS &a) { return(this->x_ == a.x_ && this->y_ == a.y_);}
	};
	struct Cell {//いちます毎の情報
		POS cellpos;
		//int cost;//そのセルを通るときのコスト
		int cCost;//実コスト、今までの移動
		int hCost;//推測コスト、ひゅーり
		int eCost;//トータル、実＋ひゅーり
		Cell* parent;
		Cell():/*cost(-1),*/cCost(-1),hCost(-1),eCost(-1),parent(nullptr){}
		Cell(POS pos) :Cell() { cellpos = pos; }
		bool operator==(const Cell& a) { return(this->cellpos == a.cellpos); }
	};
private:
	vector < vector < int >> map;//通れるところとかコストとか
	//vector < vector < Cell >> CellMap;//情報入れておくもの
	int heuristic(POS now);//現在地からの最短経路
	void Search();//肝要。再帰？
	std::vector<Cell> openCells;
	std::vector<Cell>closeCells;
public:
	POS target_;//探索目的地点
	POS start_;//探索開始地点

	vector<POS> Route;//探索終了したらこれに入れてって後でreverse
	Aster();
	~Aster();
	void BeginSearch();
	void Show();//探索終了したら
};

