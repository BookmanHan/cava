#pragma  once
#include "stdafx.h"

class cls_yacc_kernal_item : public cls_yacc_product
{
public:
	int pos;
public:
	cls_yacc_kernal_item();
	cls_yacc_kernal_item(cls_yacc_product p);
	bool operator == (const cls_yacc_kernal_item that) const;
};