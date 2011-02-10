#include "StdAfx.h"
#include "cls_yacc_kernal_item.h"

cls_yacc_kernal_item::cls_yacc_kernal_item()
{
	pos = 0;
}

cls_yacc_kernal_item::cls_yacc_kernal_item(cls_yacc_product p):cls_yacc_product(p)
{
	pos = 0;
}

bool cls_yacc_kernal_item::operator == (const cls_yacc_kernal_item that) const
{
	if (this->str_exp == that.str_exp && this->pos == that.pos)
	{
		return true;
	}
	else
	{
		return false;
	}
}
