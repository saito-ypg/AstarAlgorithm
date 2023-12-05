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
	struct Cell {//�����܂����̏��
		POS cellpos;
		//int cost;//���̃Z����ʂ�Ƃ��̃R�X�g
		int certainCost;//���R�X�g
		int estimationCost;//����֐��A���{�Ђ�[��
		Cell* parent;
		Cell():/*cost(-1),*/certainCost(-1),estimationCost(-1),parent(nullptr){}
		Cell(POS pos) :Cell() { cellpos = pos; }
		bool operator==(const Cell& a) { return(this->cellpos == a.cellpos); }
	};
private:
	vector < vector < int >> map;//�ʂ��Ƃ���Ƃ��R�X�g�Ƃ�
	//vector < vector < Cell >> CellMap;//������Ă�������
	int heuristic(POS now);//���ݒn����̍ŒZ�o�H
	void Search();//�̗v�B�ċA�H
	std::vector<Cell> openCells;
	std::vector<Cell>closeCells;
public:
	POS target_;//�T���ړI�n�_
	POS start_;//�T���J�n�n�_

	vector<POS> Route;//�T���I�������炱��ɓ���Ă��Č��reverse
	Aster();
	~Aster();
	void BeginSearch();
	void Show();//�T���I��������
};

