#pragma once
#include "stdafx.h"

class cls_compiler_symbol_table_item
{
public:
	int type;
	int n_const;
	int c_type;
	int pointer_level;
	string context;
	int memory_ptr;
	int seg;
	vector<cls_compiler_symbol_table_item> struct_info;
	vector<cls_compiler_symbol_table_item> param;
	int mem_total;

	bool get_struct_item(string str,cls_compiler_symbol_table_item& item);
	cls_compiler_symbol_table_item();

};