#include "StdAfx.h"
#include "cls_yacc_product_item.h"

cls_yacc_product_item::operator int()
{
	return item;
}

bool cls_yacc_product_item::operator == (const cls_yacc_product_item that) const
{
	if (this->item == that.item)
		return true;
	else
		return false;
}

cls_yacc_product_item::cls_yacc_product_item()
{

}

cls_yacc_product_item::cls_yacc_product_item(int a_item)
{
	item = a_item;
	if (item < const_spilt)
		b_is_non = false;
	else
		b_is_non = true;
}

bool cls_yacc_product_item::operator==(const cls_yacc_product_item& that)
{
	return item == that.item;
}

cls_yacc_product_item::operator bool()
{
	return b_is_non; 
}