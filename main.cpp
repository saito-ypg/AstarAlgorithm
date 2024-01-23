#include <iostream>
#include"Aster.h"



int main(){
	Aster a;
	a.target_ = { 3,1 };
	a.start_ = { 2,0 };
	a.BeginSearch();
	a.Show();
}