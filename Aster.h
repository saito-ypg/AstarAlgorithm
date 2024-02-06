#pragma once
#include<vector>
#include<list>
#include<string>
#include<map>
using std::vector;
using std::string;
const int mapX = 6, mapY =6;

class Aster
{
public:
	struct POS {
		int x_; int y_;
		POS() :x_(-1), y_(-1) {} 
		POS(int x, int y):x_(x),y_(y){} 
		bool operator==(const POS&  a) const{ return(this->x_ == a.x_ && this->y_ == a.y_);}
		string toString() {
			return string("{" +std::to_string( x_ )+ "," +std::to_string( y_ )+ "}");
		}
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

	//	Cell operator=(const Cell& a);
	};
private:
	vector < vector < int >> map;//通れるところとかコストとか
	//vector < vector < Cell >> CellMap;//情報入れておくもの
	int heuristic(POS now);//現在地からの最短経路
	void search();//肝要。再帰？
	void checkNext(POS next,Cell*const nowCell );
	std::list<Cell> openCells;
	std::list<Cell>closeCells;//いらない疑惑
	void getRoute(Cell cell);
public:
	POS target_;//探索目的地点
	POS start_;//探索開始地点

	vector<POS> Route;//探索終了したらこれに入れてって後でreverse
	Aster();
	~Aster();
	void BeginSearch();
	void Show();//探索終了したら
};

