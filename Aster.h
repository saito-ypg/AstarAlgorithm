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
	struct Cell {//�����܂����̏��
		POS cellpos;
		//int cost;//���̃Z����ʂ�Ƃ��̃R�X�g
		int cCost;//���R�X�g�A���܂ł̈ړ�
		int hCost;//�����R�X�g�A�Ђ�[��
		int eCost;//�g�[�^���A���{�Ђ�[��
		Cell* parent;
		Cell():/*cost(-1),*/cCost(-1),hCost(-1),eCost(-1),parent(nullptr){}
		Cell(POS pos) :Cell() { cellpos = pos; }

	//	Cell operator=(const Cell& a);
	};
private:
	vector < vector < int >> map;//�ʂ��Ƃ���Ƃ��R�X�g�Ƃ�
	//vector < vector < Cell >> CellMap;//������Ă�������
	int heuristic(POS now);//���ݒn����̍ŒZ�o�H
	void search();//�̗v�B�ċA�H
	void checkNext(POS next,Cell*const nowCell );
	std::list<Cell> openCells;
	std::list<Cell>closeCells;//����Ȃ��^�f
	void getRoute(Cell cell);
public:
	POS target_;//�T���ړI�n�_
	POS start_;//�T���J�n�n�_

	vector<POS> Route;//�T���I�������炱��ɓ���Ă��Č��reverse
	Aster();
	~Aster();
	void BeginSearch();
	void Show();//�T���I��������
};

