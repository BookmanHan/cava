#pragma once
#include "stdafx.h"

class cls_compiler_syntex
{
private:
	cls_compiler_word cw;
	cls_compiler_syntex_action_table action_table;
	map<string,int> ter_info;
	vector<pair<int,int>> product_info;
	string& src;

	set<string> import_files;
	bool do_check_over;
	int len_import;

public:
	cls_compiler_symbol_table_manager cstm;
	vector<cls_compiler_command> des;
	string str_get;
	bool check_success;
	string import;

private:
	void do_func_dec();
	void statement_copy(cls_compiler_command& cmd,cls_compiler_syntex_item& item1,cls_compiler_syntex_item& item2,cls_compiler_syntex_item& item_re);
	void do_continue_break();
	void do_assign_computing(vector<cls_compiler_syntex_item> now,int num,cls_compiler_syntex_item &re);
	void do_bool_computing(vector<cls_compiler_syntex_item> now,int num,cls_compiler_syntex_item &re);
	void do_computing(vector<cls_compiler_syntex_item> now,int num,cls_compiler_syntex_item &re);
public:
	void load_action_table(string str);
	cls_compiler_syntex(string& a_src,string str_oper,string str_product,string str_ac_tb,vector<int> a_lines,int a_pre);

	void load_ter_info(string str_filename);
	void load_product_info(string str_filename);
	static bool check_key_word(string str);
	int num_error;
	void error(string str,int num = 10);

	//检测函数与结构体的信息！
	bool do_run_check(vector<cls_compiler_syntex_item>& now,int next_status,cls_compiler_syntex_item& re);
	int get_command_type(int type,int pointer_level,int a_const);
	bool do_run_real(vector<cls_compiler_syntex_item>& now,int next_status,cls_compiler_syntex_item& re,vector<cls_compiler_syntex_item>& stack);
	vector<int> lines;
	bool do_run(int do_what =0);
};