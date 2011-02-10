#pragma once
#include "stdafx.h"

class cls_yacc_product
{
public:
	string str_exp;
	cls_yacc_product_item left;
	vector<cls_yacc_product_item> right;
	cls_yacc_info* info;
	int oper;
	int order;

private:
	void analyze_exp();

public:
	cls_yacc_product();
	cls_yacc_product(string a_exp,cls_yacc_info* a_info,int a_pos);
};