#pragma once
#include<vector>
using std::vector;
const int mapX = 6, mapY = 6;
class Aster
{
public:
	struct POS { int x; int y; POS() { x = 0, y = 0; } };
	//enum TILE { PT = 0,NPT };//PT -> Pass Through
	class Cell {//�����܂����̏��
		POS cellpos;
		int cost;//���̃Z����ʂ�Ƃ��̃R�X�g
		int certainCost;//Certain,���R�X�g
		int heuristicCost;//heuristic,�֐�


	};
private:
	POS target_;//�T���ړI
	POS start_;//�T���J�n
	vector < vector < int >> map;
	int heuristic(POS now);//���ݒn����̍ŒZ�o�H
	

public:
	Aster();
	~Aster();
	void Search();//�̗v�B�ċA�H
	void Show();//�T���I��������
};

