#pragma once
#include<vector>
using std::vector;
const int mapX = 6, mapY = 6;
class Aster
{
public:
	struct POS { int x; int y; POS() { x = 0, y = 0; } };
	//enum TILE { PT = 0,NPT };//PT -> Pass Through
	class Cell {//いちます毎の情報
		POS cellpos;
		int cost;//そのセルを通るときのコスト
		int certainCost;//Certain,実コスト
		int heuristicCost;//heuristic,関数


	};
private:
	POS target_;//探索目的
	POS start_;//探索開始
	vector < vector < int >> map;
	int heuristic(POS now);//現在地からの最短経路
	

public:
	Aster();
	~Aster();
	void Search();//肝要。再帰？
	void Show();//探索終了したら
};

