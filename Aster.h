#pragma once
#include<vector>
using std::vector;
const int mapX = 6, mapY =6;
class Aster
{
public:
	struct POS { int x_; int y_; POS() :x_(-1), y_(-1) {} POS(int x, int y):x_(x),y_(y){} };
	struct Cell {//�����܂����̏��
		POS cellpos;
		int cost;//���̃Z����ʂ�Ƃ��̃R�X�g
		int certainCost;//���R�X�g
		int estimationCost;//����֐��A���{�Ђ�[��
		Cell():cost(-1),certainCost(-1),estimationCost(-1) {}
		Cell(int x, int y) :Cell() { cellpos = POS(x, y);}
	};
private:

	vector < vector < int >> map;
	vector < vector < Cell >> CellMap;
	int heuristic(POS now);//���ݒn����̍ŒZ�o�H
	

public:
	POS target_;//�T���ړI�n�_
	POS start_;//�T���J�n�n�_
	Aster();
	~Aster();
	void Search();//�̗v�B�ċA�H
	void Show();//�T���I��������
};

