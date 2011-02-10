#pragma once
#include "stdafx.h"

class cls_compiler_symbol_table
{
public:
	vector<cls_compiler_symbol_table_item> table_items;
	cls_compiler_symbol_table_item& get_name_info(string str);
	bool get_name_info(string str,int num);
	bool add_name_info(cls_compiler_symbol_table_item& item_set);
	cls_compiler_symbol_table_item& get_cur();
};
