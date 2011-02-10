#pragma once
#include "stdafx.h"

class cls_yacc_product_item
{
public:
	const static int const_spilt = t_const_spilt;
	bool b_is_non;
	int item;

public:
	operator int();
	bool operator == (const cls_yacc_product_item that) const;
	cls_yacc_product_item();
	cls_yacc_product_item(int a_item);
	bool operator==(const cls_yacc_product_item& that);
	operator bool();
};
