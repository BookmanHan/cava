#pragma once
class cls_compiler_syntex_item
{
public:
	int status;
	string str;
	int type;
public:
	string str_re;

	vector<cls_compiler_syntex_item> items;
	vector<cls_compiler_symbol_table_item> tb_items;
	vector<string> names;
	vector<int> ptrs;
	vector<cls_compiler_syntex_item> cases;

	int p_1;
	int seg;
	int p_2;
	int p_3;
	int p_4;

	int real_pointer_level;

public:
	bool copy_from(const cls_compiler_syntex_item& that);
	cls_compiler_syntex_item(int a_s,int a_t,string a_str);
};