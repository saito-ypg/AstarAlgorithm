#include <iostream>
#include"Aster.h"



int main(){
	Aster a;
	a.target_ = { 3,3 };
	a.start_ = { 3,1 };
	a.BeginSearch();
	a.Show();
}