#pragma once
#include<vector>
#include<map>
using std::vector;
const int mapX = 6, mapY =6;

class Aster
{
public:
	struct POS { int x_; int y_; POS() :x_(-1), y_(-1) {} POS(int x, int y):x_(x),y_(y){} };
	struct Cell {//いちます毎の情報
		POS cellpos;
		//int cost;//そのセルを通るときのコスト
		int certainCost;//実コスト
		int estimationCost;//推定関数、実＋ひゅーり
		Cell():/*cost(-1),*/certainCost(-1),estimationCost(-1) {}
		Cell(int x, int y) :Cell() { cellpos = POS(x, y);}
	/*	auto operator <=>(const Cell&)const {
			
			return
		}*/
	};
private:

	vector < vector < int >> map;//通れるところとかコストとか
	vector < vector < Cell >> CellMap;//情報入れておくもの
	int heuristic(POS now);//現在地からの最短経路
	void Search(POS pos_);//肝要。再帰？

public:
	POS target_;//探索目的地点
	POS start_;//探索開始地点
	Aster();
	~Aster();
	void BeginSearch();
	void Show();//探索終了したら
};

