#include "StdAfx.h"
#include "cls_compiler_symbol_table.h"

cls_compiler_symbol_table_item& cls_compiler_symbol_table::get_name_info(string str)
{
	for(int cnt=0;cnt<table_items.size();cnt++)
	{
		if (table_items[cnt].context == str)
		{
			return table_items[cnt];
		}
	}

	cls_compiler_symbol_table_item i;
	return i;
}

bool cls_compiler_symbol_table::get_name_info(string str,int num)
{
	for(int cnt=0;cnt<table_items.size();cnt++)
	{
		if (table_items[cnt].context == str)
		{
			return true;
		}
	}

	return false;
}

bool cls_compiler_symbol_table::add_name_info(cls_compiler_symbol_table_item& item_set)
{
	if (get_name_info(item_set.context,0))
	{
		get_name_info(item_set.context) = item_set;
		return false;
	}
	else
	{
		table_items.push_back(item_set);
	}
}

cls_compiler_symbol_table_item& cls_compiler_symbol_table::get_cur()
{
	return table_items.back();
}