#pragma once
#include<vector>
using std::vector;
const int mapX = 6, mapY =6;
class Aster
{
public:
	struct POS { int x_; int y_; POS() :x_(-1), y_(-1) {} POS(int x, int y):x_(x),y_(y){} };
	struct Cell {//いちます毎の情報
		POS cellpos;
		int cost;//そのセルを通るときのコスト
		int certainCost;//実コスト
		int estimationCost;//推定関数、実＋ひゅーり
		Cell():cost(-1),certainCost(-1),estimationCost(-1) {}
		Cell(int x, int y) :Cell() { cellpos = POS(x, y);}
	};
private:

	vector < vector < int >> map;
	vector < vector < Cell >> CellMap;
	int heuristic(POS now);//現在地からの最短経路
	

public:
	POS target_;//探索目的地点
	POS start_;//探索開始地点
	Aster();
	~Aster();
	void Search();//肝要。再帰？
	void Show();//探索終了したら
};

