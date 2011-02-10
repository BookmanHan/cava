#pragma once
#include "stdafx.h"

class cls_compiler_symbol_table_manager
{
public:
	int n_static_num;
	int n_cur_num;
	vector<cls_compiler_symbol_table> tables;
	cls_compiler_symbol_table const_table;
	cls_compiler_symbol_table fun_table;
	cls_compiler_symbol_table struct_table;

public:
	int get_tmp_pos(int c_type,int pointer_level,int a_const,int type = type_var);
	cls_compiler_symbol_table_manager();
	int get_mem_port(cls_compiler_symbol_table_item item);
	int get_tmp_pos(int width);
	bool add_func(cls_compiler_symbol_table_item& item);
	bool get_func(string str,cls_compiler_symbol_table_item **item);
	cls_compiler_symbol_table_item& get_struct(string str);
	cls_compiler_symbol_table_item get_struct(int c_type);
	bool add_struct(cls_compiler_symbol_table_item &item);
	bool check_cur_by_mem(int mem);
	bool check_name_info(string str);
	bool get_name_info(string str,cls_compiler_symbol_table_item& item_get);
	cls_compiler_symbol_table_item get_name_info(string str);
	bool add_name_info(cls_compiler_symbol_table_item& item_set,bool auto_alloc = true);
	bool enter_block();
	bool de_ref_cur(vector<cls_compiler_command>&des);
	bool leave_block(vector<cls_compiler_command>&des,bool check_deref = true);
};
