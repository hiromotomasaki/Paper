/**
 * main.cpp
 *
 * Copyright (c) 2016 HIROMOTO,Masaki
 *
 */
#include "main.hpp"

using namespace hiro;

// set_presolve したときの間違った方法
void print_invalid(lprec *problem, double *x){
	int i;
	get_variables ( problem, x ) ;
	for( i =0 ; i<= 2; i++ )
		std::cout << x[i] << "\n";
}
// 正しい方法
void print_valid(lprec *problem){
	int Nc, Nr, i;
	double value;
	Nc = get_Norig_columns(problem);
	Nr = get_Norig_rows(problem);
	// std::cout << "Nc" << Nc << "\n";
	// std::cout << "Nr" << Nr << "\n";
	for(i = 1; i <= Nc; i++) {
		value = get_var_primalresult(problem, Nr + i);
		std::cout << value << "\n";
	}
}
int main( ) {
	// int i ;
	double x[3];    // 変数
	double c[4] = { -9999., -1., -1., -1.}; // 目的関数
	double b[3] = { 7., 13., 30. };  // 制約条件
	double A[3][4]; // 制約条件
	lprec *problem;
	problem=make_lp( 0,3 );
	set_obj_fn ( problem, c ); // 目的関数
// 制約条件の設定(右辺)
	A[0][1] = 0 ; A[0][2] = 3 ; A[0][3] = 2 ;
	A[1][1] = 0 ; A[1][2] = 5 ; A[1][3] = 6 ;
// x1==30 : 自明な制約
	A[2][1] = 1 ; A[2][2] = 0 ; A[2][3] = 0 ;
// 制約条件の設定(右辺)
	for(int i=0;i<2;++i)
		add_constraint( problem, A[i], LE, b[i] );
	add_constraint( problem, A[2], EQ, b[2] );
// メッセージレベルの設定（0〜6; default is 4）
	set_verbose(problem, 0);
// 求解
	set_presolve( problem, PRESOLVE_ROWS | PRESOLVE_COLS | PRESOLVE_LINDEP,
				  get_presolveloops(problem));
	solve( problem );
// 目的関数値の取得
	std::cout << "Obj : " << get_objective(problem) << "\n";
// 最適解の取得
	std::cout << "--- print_invalid ---" << "\n";
	print_invalid( problem, x );  // invalid!
	std::cout << "--- print_valid ---" << "\n";
	print_valid( problem );  // valid!

	return EXIT_SUCCESS;
}
