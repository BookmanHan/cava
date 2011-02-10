#pragma once
#include "stdafx.h"

class cls_yacc_kernal
{
public:
	vector<cls_yacc_kernal_item> items;
	vector<cls_yacc_move> moves;

public:
	void get_move_vct(int n_cur,ofstream& fout,cls_yacc_info& info,vector<int>& rank,set<int>& join);
	cls_yacc_kernal();
	bool operator == (const cls_yacc_kernal& that) const;
	void move_next_step(vector<cls_yacc_kernal>& kernals,vector<cls_yacc_product>& src,int n_cur,int &n_total);
	void set_closure(const vector<cls_yacc_product>& src);
};