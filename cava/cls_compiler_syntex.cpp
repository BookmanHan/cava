#include "StdAfx.h"
#include "cls_compiler_syntex.h"

void cls_compiler_syntex::do_func_dec()
{
	for(int cnt=0;cnt<des.size();cnt++)
	{
		if (des[cnt].oper == command_tag)
		{
			if (des[cnt+1].oper == command_return)
			{	
				des[cnt].name = "";
				des[cnt].oper = command_nop;
				des[cnt+1].oper = command_nop;
			}
		}
	}
}

void cls_compiler_syntex::statement_copy(cls_compiler_command& cmd,cls_compiler_syntex_item& item1,cls_compiler_syntex_item& item2,cls_compiler_syntex_item& item_re)
{
	cmd.ptr1 = item1.p_1;
	cmd.seg1 = item1.seg;
	if (item1.p_3 != 0)
	{
		if (item1.p_4 == 1)
			cmd.ct1 = ctype_pointer;
		else if (item1.p_4 == 2)
			cmd.ct1 = ctype_pointer_random;
	}
	else
	{
		cmd.ct1 = item1.p_2;
	}

	cmd.ptr2 = item2.p_1;
	cmd.seg2 = item2.seg;
	if (item2.p_3 != 0)
	{
		if (item2.p_4 == 1)
			cmd.ct2 = ctype_pointer;
		else if (item2.p_4 == 2)
			cmd.ct2 = ctype_pointer_random;
	}
	else
	{
		cmd.ct2 = item2.p_2;
	}

	cmd.re = item_re.p_1;
	cmd.seg_re = item_re.seg;
	if (item_re.p_3 != 0)
	{
		if (item_re.p_4 <= 1)
			cmd.ct_re = ctype_pointer;
		else if (item_re.p_4 == 2)
			cmd.ct_re = ctype_pointer_random;
	}
	else
	{
		cmd.ct_re = item_re.p_2;
	}
}

void cls_compiler_syntex::do_continue_break()
{
	vector<int> breaks;
	vector<int> conts;

	for(int cnt=0;cnt<des.size();cnt++)
	{
		if (des[cnt].oper == command_switch)
		{
			des[cnt].oper = command_abs_jump;
			breaks.push_back(-1);
			conts.push_back(-1);
		}
		else if (des[cnt].oper == command_for || des[cnt].oper == command_while)
		{
			des[cnt].oper = command_jump;
			breaks.push_back(-1);
			conts.push_back(-1);
		}
		else if (des[cnt].oper == command_break)
		{
			breaks.push_back(cnt);
		}
		else if (des[cnt].oper == command_continue)
		{
			conts.push_back(cnt);
		}
		else if (des[cnt].oper == command_switch_re)
		{
			des[cnt].oper = command_nop;

			while(breaks.size() != 0)
			{
				if (breaks.back() == -1)
				{
					breaks.pop_back();
					break;
				}

				des[breaks.back()].re = cnt+1;
				des[breaks.back()].oper = command_abs_jump;
				breaks.pop_back();
			}

			while(conts.size() != 0)
			{
				if (conts.back() == -1)
				{
					conts.pop_back();
					break;
				}

				des[conts.back()].re = cnt;
				des[conts.back()].oper = command_abs_jump;
				conts.pop_back();
			}
		}
		else if (des[cnt].oper == command_for_re || des[cnt].oper == command_while_re)
		{
			des[cnt].oper = command_abs_jump;

			while(breaks.size() != 0)
			{
				if (breaks.back() == -1)
				{
					breaks.pop_back();
					break;
				}

				des[breaks.back()].re = cnt+1;
				des[breaks.back()].oper = command_abs_jump;
				breaks.pop_back();
			}

			while(conts.size() != 0)
			{
				if (conts.back() == -1)
				{
					conts.pop_back();
					break;
				}

				des[conts.back()].re = cnt;
				des[conts.back()].oper = command_abs_jump;
				conts.pop_back();
			}
		}
	}
}
void cls_compiler_syntex::do_assign_computing(vector<cls_compiler_syntex_item> now,int num,cls_compiler_syntex_item &re)
{
	int cmd_type = type_none;

	if (num >= 1051 && num <= 1062)
	{
		;
	}
	else
	{
		return;
	}

	if (!fn_type_trans(now[1].p_2,now[3].p_2,now[1].p_3,now[3].p_3))
	{
		error("类型不符");
	}

	if (now[3].p_3 != 0)
	{
		error("指针不能做被加数！");
	}

	if (now[1].p_3 != now[3].p_3)
	{
		if ((now[3].p_2 == ctype_int && now[3].p_3 == 0))
		{

		}
		else
		{
			error("指针层数不符合 或者 只允许指针与int类型的运算！");
		}
	}

	if (now[1].p_4 >= 1 && now[3].p_4 == 0)
	{
		if (now[3].p_2 == ctype_int && now[3].p_3 == 0)
		{
			;
		}
		else
		{
			error("智能性质不符合");
		}
	}

	if (now[1].p_4 == 1)
	{
		error("smart不能改变，请使用random！");
	}

	cls_compiler_command cmd;
	switch(num)
	{
	case 1051:
		cmd.oper = command_add;
		break;
	case 1052:
		cmd.oper = command_minus;
		break;
	case 1053:
		cmd.oper = command_mutiply;
		break;
	case 1054:
		cmd.oper = command_divide;
		break;
	case 1055:
		cmd.oper = command_mod;
		break;
	case 1056:
		cmd.oper = command_and;
		break;
	case 1057:
		cmd.oper = command_or;
		break;
	case 1058:
		cmd.oper = command_left;
		break;
	case 1059:
		cmd.oper = command_right;
		break;
	case 1060:
		cmd.oper = command_roleft;
		break;
	case 1061:
		cmd.oper = command_roright;
		break;
	case 1062:
		cmd.oper = command_xor;
		break;
	}

	if (now[1].b_left == true)
	{
		cls_compiler_command cmd1;
		cmd1.oper = command_get;
		cmd1.ptr1 = now[1].p_1;
		cmd1.seg1  = now[1].seg;
		cmd1.ct1 = get_command_type(now[1].p_2,now[1].p_3+1,now[1].p_4);
		cmd1.re = cstm.get_tmp_pos(now[1].p_2,now[1].p_3,now[1].p_4);
		cmd1.ct_re = get_command_type(now[1].p_2,now[1].p_3,now[1].p_4);
		cmd1.seg_re = now[1].seg;

		des.push_back(cmd1);
		statement_copy(cmd,now[1],now[3],now[1]);
		if (cmd.re == -1)
		{
			error("类型未声明！");
		}

		cmd.ct_re = get_command_type(now[1].p_2,now[1].p_3,now[1].p_4);
		des.push_back(cmd);

		cmd.oper = command_pointer_set;
		cmd.ptr1 = cmd1.re;
		cmd.ct1 = cmd1.ct_re;
		cmd.seg1 = cmd1.seg1;
		cmd.re  = now[1].p_1;
		now[1].p_3++;
		cmd.ct_re = get_command_type(now[1].p_2,now[1].p_3,now[1].p_4);
		now[1].p_3--;
		cmd.seg_re = now[1].seg;

		des.push_back(cmd);
	}
	else
	{
		statement_copy(cmd,now[1],now[3],now[1]);
		if (cmd.re == -1)
		{
			error("类型未声明！");
		}

		cmd.ct_re = get_command_type(now[1].p_2,now[1].p_3,now[1].p_4);
		des.push_back(cmd);
	}

	re.copy_from(now[1]);
}

void cls_compiler_syntex::do_bool_computing(vector<cls_compiler_syntex_item> now,int num,cls_compiler_syntex_item &re)
{
	if (num >= 1075 && num <= 1082)
	{

	}
	else
	{
		return;
	}


	if (!fn_type_trans(now[1].p_2,now[3].p_2,now[1].p_3,now[3].p_3))
	{
		error("类型不符");
	}

	cls_compiler_command cmd;
	switch(num)
	{
	case 1075:
		cmd.oper = command_larger;
		break;
	case 1076:
		cmd.oper = command_smaller;
		break;
	case 1077:
		cmd.oper = command_smaller_equ;
		break;
	case 1078:
		cmd.oper = command_larger_eql;
		break;
	case 1079:
		cmd.oper = command_equ;
		break;
	case 1080:
		cmd.oper = command_non_equ;
		break;
	}

	statement_copy(cmd,now[1],now[3],now[1]);
	cmd.re = cstm.get_tmp_pos(now[1].p_2,now[1].p_3,now[1].p_4);
	cmd.seg_re = seg_stack;
	cmd.ct_re = ctype_int;

	des.push_back(cmd);

	if (cmd.re == -1)
	{
		error("类型未声明");
	}

	re.copy_from(now[1]);
	re.p_1 = cmd.re;
	re.p_2 = ctype_int;
	re.p_3 = 0;
	re.p_4 = 0;
	re.seg = seg_stack;
}

void cls_compiler_syntex::do_computing(vector<cls_compiler_syntex_item> now,int num,cls_compiler_syntex_item &re)
{
	if (num >= 1063 && num <= 1074)
	{
		;
	}
	else
	{
		return;
	}


	if (!fn_type_trans(now[1].p_2,now[3].p_2,now[1].p_3,now[3].p_3))
	{
		error("类型不符");
	}

	cls_compiler_command cmd;
	switch(num)
	{
	case 1063:
		cmd.oper = command_add;
		break;
	case 1064:
		cmd.oper = command_minus;
		break;
	case 1065:
		cmd.oper = command_mutiply;
		break;
	case 1066:
		cmd.oper = command_divide;
		break;
	case 1067:
		cmd.oper = command_mod;
		break;
	case 1068:
		cmd.oper = command_and;
		break;
	case 1069:
		cmd.oper = command_or;
		break;
	case 1070:
		cmd.oper = command_left;
		break;
	case 1071:
		cmd.oper = command_right;
		break;
	case 1072:
		cmd.oper = command_roleft;
		break;
	case 1073:
		cmd.oper = command_roright;
		break;
	case 1074:
		cmd.oper = command_xor;
		break;
	}

	statement_copy(cmd,now[1],now[3],now[1]);
	cmd.re = cstm.get_tmp_pos(now[1].p_2,now[1].p_3,now[1].p_4);
	des.push_back(cmd);

	if (cmd.re == -1)
	{
		error("类型未声明");
	}

	re.copy_from(now[1]);
	re.p_1 = cmd.re;
}

void cls_compiler_syntex::load_action_table(string str)
{
	ifstream fin;
	fin.open(str.c_str());

	while(!fin.eof())
	{
		int p,q,m;
		fin>>p>>q>>m;
		action_table.set_move(p,q,m);
	}

	fin.close();
}

cls_compiler_syntex::cls_compiler_syntex(string& a_src,string str_oper,string str_product,string str_ac_tb,vector<int> a_lines,int a_pre):cw(a_src,str_oper),src(a_src),action_table(500,400,165,138)
{
	srand(time(NULL));
	load_ter_info(str_oper);
	load_product_info(str_product);
	load_action_table(str_ac_tb);
	lines = a_lines; // 防止析构，特别这么做！

	do_check_over = false;

	num_error = 0;
	src =a_src;

	len_import = a_pre;
	//bool b_2 = true;
	//while(!do_check_over)
	//{
	//	do_check_over = true;
	//	b_2 = do_run(1);
	//	cw.src.insert(cw.pos-cw.str_pre_get.length(),import);
	//	len_import += import.length();
	//	import.clear();
	//	str_get = "";
	//	cw.reset();
	//}

	bool b_1 = do_run();
	do_continue_break();
	cw.reset();
	do_func_dec();
	check_success = b_1;
}

void cls_compiler_syntex::load_ter_info(string str_filename)
{
	ifstream fin;
	fin.open(str_filename.c_str());

	while(!fin.eof())
	{
		string str;
		string str_2;
		int n;
		getline(fin,str);
		getline(fin,str_2);
		stringstream ss(str_2);
		ss>>n;

		if (str.size() != 0)
			ter_info[str] = n;
	}

	fin.close();
}

void cls_compiler_syntex::load_product_info(string str_filename)
{
	ifstream fin;
	fin.open(str_filename.c_str());

	while(!fin.eof())
	{
		string str;
		int n_l;
		int n_r_num;
		fin>>str>>n_l>>n_r_num;
		product_info.push_back(make_pair(n_l,n_r_num));
	}

	fin.close();
}

bool cls_compiler_syntex::check_key_word(string str)
{
	const static string key_word[] = {"default","switch","case","null","random","smart","void","break","continue","new","struct","class","return","include","end","char","const","do","else","for","if","import","int","double","short","sizeof","struct","unsigned_char","unsigned_int","unsigned_short","while"};

	for(int cnt=0;cnt<sizeof(key_word)/sizeof(string);cnt++)
	{
		if (str == key_word[cnt])
			return true;
	}

	return false;
}

void cls_compiler_syntex::error(string str,int num)
{
	int cnt = 0;
	int n = cw.pos;
	if (n < 0)
	{
		cnt = 1;
	}
	else
	{
		for(cnt=0;cnt<lines.size()-1;cnt++)
		{
			if (n < lines[cnt+1])
			{
				break;
			}
		}
	}

	check_success = false;
	num_error++;
	cout<<"第 "<<num_error<<" 个错误："<<endl;
	cout<<"\t"<<"主要失效原因："<<str<<endl;
	cout<<"\t"<<"主要失效符号："<<cw.str_pre_get<<endl;
	cout<<"\t"<<"主要失效行号："<<(cnt+2)<<endl;
	cw.display(20);
	cout<<endl;
	system("pause");
	exit(0);
}

//检测函数与结构体的信息！

bool cls_compiler_syntex::do_run_check(vector<cls_compiler_syntex_item>& now,int next_status,cls_compiler_syntex_item& re)
{

	switch(next_status)
	{
	case 1002:
		{
			if (import_files.find(now[3].str) != import_files.end())
			{
				break;
			}

			do_check_over = false;
			ifstream fin(now[3].str.substr(1,now[3].str.length()-2).c_str());
			if (!fin.is_open())
			{
				error("无法打开import文件！");
			}

			import_files.insert(now[3].str);
			while(!fin.eof())
			{
				string str_get_try;
				getline(fin,str_get_try);

				import += str_get_try;
			}

			fin.close();
		}	
		return false;
		break;
	case 1003:
		return false;
		break;
	}

	return true;
}

int cls_compiler_syntex::get_command_type(int type,int pointer_level,int a_const)
{
	if (pointer_level == 0)
		return type;
	else if (a_const <= 1)
		return ctype_pointer;
	else 
		return ctype_pointer_random;
}

bool cls_compiler_syntex::do_run_real(vector<cls_compiler_syntex_item>& now,int next_status,cls_compiler_syntex_item& re,vector<cls_compiler_syntex_item>& stack)
{
	do_computing(now,next_status,re);
	do_assign_computing(now,next_status,re);
	do_bool_computing(now,next_status,re);

	switch(next_status)
	{
	case 1000:
		return true;
		break;
	case 1001:
		;
		break;
	case 1002:
		{
		}
		break;
	case 1003:
		;
		break;
	case 1004:
		;
		break;
	case 1005:
		;
		break;
	case 1006:
		;
		break;
	case 1007:
		{
			cstm.enter_block();
		}
		break;
	case 1008:
		{
			cls_compiler_symbol_table_item item;
			item.context = now[2].str;
			item.type = type_struct;
			item.struct_info = now[4].tb_items;
			item.c_type = c_type_cur ++;

			cstm.add_struct(item);
			re.str = now[2].str;
		}
		break;
	case 1009:
		{
			cls_compiler_symbol_table_item item;
			item.type = type_var;
			item.c_type = now[1].p_1;
			item.pointer_level = now[1].p_2;
			item.n_const = now[1].p_3;
			item.context = now[2].str;
			item.memory_ptr = 0;
			re.p_1 = 0;
			re.p_2 = cstm.get_mem_port(item);
			re.tb_items.push_back(item);
		}
		break;
	case 1010:
		{
			cls_compiler_symbol_table_item item;
			item.type = type_var;
			item.c_type = now[2].p_1;
			item.pointer_level = now[2].p_2;
			item.n_const = now[2].p_3;
			item.context = now[3].str;
			item.memory_ptr = now[1].p_1 + now[1].p_2;
			re.p_1 = item.memory_ptr;
			re.p_2 = cstm.get_mem_port(item);

			re.tb_items = now[1].tb_items;
			re.tb_items.push_back(item);
		}
		break;
	case 1011:
		{
			//re.type = type_none;
			re.p_1= now[1].p_1;
			re.p_2 = now[2].p_1;
			re.p_3 = false;
		}
		break;
	case 1012:
		{
			re.p_1 = cstm.get_struct(now[2].str).c_type;	
			re.p_2 = now[3].p_1;
			re.p_3 = false;
		}
		break;
	case 1013:
		re.p_1 = ctype_short;
		break;
	case 1014:
		re.p_1 = ctype_char;
		break;
	case 1015:
		re.p_1 = ctype_int;
		break;
	case 1016:
		re.p_1 = ctype_unsigned_short;
		break;
	case 1017:
		re.p_1 = ctype_unsigned_char;
		break;
	case 1018:
		re.p_1 = ctype_unsigned_int;
		break;
	case 1019:
		re.p_1 = ctype_double;
		break;
	case 1020:
		re.copy_from(now[2]);
		re.p_3 = 1;
		break;
	case 1021:
		re.p_1 = 0;
		break;
	case 1022:
		re.p_1 = now[2].p_1 + 1;
		break;
	case 1023:
		{
			for(int cnt=0;cnt<now[2].items.size();cnt++)
			{
				cls_compiler_symbol_table_item item;
				if (cstm.tables.back().get_name_info(now[2].items[cnt].items[0].str,0) == true)
				{
					error("变量已经定义！");
				}

				item.context = now[2].items[cnt].items[0].str;
				item.type = type_var;
				item.c_type = now[1].p_1;
				item.pointer_level = now[1].p_2;
				item.n_const = now[1].p_3;
				cstm.add_name_info(item);
				item.seg = cstm.get_name_info(item.context).seg;
				item.memory_ptr = cstm.get_name_info(item.context).memory_ptr;

				if (cstm.tables.size() == 1 && item.n_const == 0 && item.pointer_level > 0)
				{
					error("全局智能定义智能指针！");
				}

				if( now[2].items[cnt].items[0].seg == seg_none)
				{
					if (item.n_const >= 1)
					{
						cls_compiler_command cmd;
						cmd.oper = command_real_set;
						cmd.ptr1 = 0;
						cmd.ct1 = ctype_int;
						cmd.seg1 = seg_none;
						cmd.re = item.memory_ptr;
						cmd.ct_re = get_command_type(item.c_type,item.pointer_level,item.n_const);
						cmd.seg_re = item.seg;
						des.push_back(cmd);
					}
				}
				else
				{
					if (now[1].p_2 != now[2].items[cnt].items[0].p_3)
						error("指针层数不符合");
					if ((now[1].p_3 >0 && now[2].items[cnt].items[0].p_4 == 0) || (now[1].p_3 == 0 && now[2].items[cnt].items[0].p_4 > 0))
						error("智能类型不同");

					if (now[1].p_1 != now[2].items[cnt].items[0].p_2)
					{
						if (!fn_type_trans(now[1].p_2,now[2].items[cnt].items[0].p_2,now[1].p_3,now[2].items[cnt].items[0].p_3))
						{
							error("类型不兼容");
						}
					}


					if (now[1].p_2 > 0 && now[1].p_3 == 1)
					{
						cls_compiler_command cmd;
						cmd.oper = command_new_add_ref;
						//re中存放了解引用的值！ptr1存放了指针层数！

						cmd.ptr1 = now[1].p_3;
						cmd.re = now[2].items[cnt].items[0].p_1;
						cmd.seg_re = now[2].items[cnt].items[0].seg;
						cmd.ct_re = ctype_pointer;

						des.push_back(cmd);
					}
					else if (now[1].p_2 > 0 && now[1].p_3 == 2)
					{
						cls_compiler_command cmd;
						cmd.oper = command_new_add_ref_random;
						//re中存放了解引用的值！ptr1存放了指针层数！

						cmd.ptr1 = now[1].p_3;
						cmd.re = now[2].items[cnt].items[0].p_1;
						cmd.seg_re = now[2].items[cnt].items[0].seg;
						cmd.ct_re = ctype_pointer_random;

						des.push_back(cmd);
					}

					cls_compiler_command cmd;
					cmd.oper = command_set;

					statement_copy(cmd,now[2].items[cnt].items[0],now[2].items[cnt].items[0],now[2].items[cnt].items[0]);
					cmd.re = cstm.get_name_info(item.context).memory_ptr;
					cmd.seg_re = item.seg;
					cmd.ct_re = get_command_type(item.c_type,item.pointer_level,item.n_const);

					des.push_back(cmd);
				}
			}
		}
		break;
	case 1024:
		re.items.push_back(now[1]);
		break;
	case 1025:
		re.copy_from(now[3]);
		re.items.push_back(now[1]);
		break;
	case 1026:
		{
			cls_compiler_syntex_item sitem(0,0,now[1].str);
			sitem.str = now[1].str;
			sitem.p_2 = 0;
			sitem.seg = seg_none;
			re.items.push_back(sitem);
		}

		break;
	case 1027:
		{
			cls_compiler_syntex_item sitem(0,0,now[1].str);
			sitem.str = now[1].str;
			sitem.seg = now[3].seg;
			sitem.p_1 = now[3].p_1;
			sitem.p_2 = now[3].p_2;
			sitem.p_3 = now[3].p_3;
			sitem.p_4 = now[3].p_4;
			re.items.push_back(sitem);
		}

		break;
	case 1028:
		{

		}
		break;
	case 1029:
		{
			cls_compiler_symbol_table_item* item;
			if (cstm.get_func(now[1].str_re,&item) == true)
				item->param = now[3].tb_items;
			else
				error("函数没定义！");
		}
		break;
	case 1030:
		{
			cls_compiler_command cmd;
			cmd.oper = command_tag;
			cmd.name = now[2].str;
			des.push_back(cmd);
			cstm.enter_block();

			cls_compiler_symbol_table_item item;
			item.c_type = now[1].p_1;
			item.pointer_level = now[1].p_2;
			item.n_const = now[1].p_3;
			item.context = now[2].str;
			cstm.add_func(item);

			re.str_re = now[2].str;
		}
		break;
	case 1031:
		{
			if (stack.back().str != ";")
				cstm.leave_block(des,true);
			else
				cstm.leave_block(des,false);

			cls_compiler_command cmd;
			cmd.oper = command_return;
			cmd.seg_re = seg_none;
			cmd.ct_re = type_none;
			cmd.re = 0;
			des.push_back(cmd);
		}
		break;
	case 1032:
		{
			cls_compiler_symbol_table_item item;
			item.seg = seg_stack;
			item.type = type_var;
			item.c_type = now[1].p_1;
			item.pointer_level = now[1].p_2;
			item.n_const = now[1].p_3;
			item.context = now[2].str;
			item.memory_ptr = -cstm.get_mem_port(item);

			re.p_1 = item.memory_ptr;
			cstm.add_name_info(item,false);
			re.tb_items.push_back(item);
		}
		break;
	case 1033:
		{
			cls_compiler_symbol_table_item item;
			item.type = type_var;
			item.seg = seg_stack;
			item.c_type = now[1].p_1;
			item.pointer_level = now[1].p_2;
			item.n_const = now[1].p_3;
			item.context = now[2].str;
			item.memory_ptr = now[4].p_1;
			cstm.add_name_info(item,false);
			re.copy_from(now[4]);
			re.p_1 = -cstm.get_mem_port(item) + now[4].p_1;
			re.tb_items.push_back(item);
		}
		break;
	case 1034:
		{
			re.copy_from(now[2]);
		}
		break;
	case 1035:
		re.copy_from(now[1]);
		break;
	case 1036:
		cstm.enter_block();
		break;
	case 1037:
		cstm.leave_block(des);
		break;
	case 1038:
		re.copy_from(now[1]);
		break;
	case 1039:
		re.p_1 = 0;
		re.p_2 = 0;
		re.p_3 = 0;
		break;
	case 1040:
		{
			if ( now[1].p_1!=  0)
			{
				int level = now[1].p_1;
				int mem_level = level;
				level -- ;
			
				if (now[2].p_3 < level)
					error("指针层数错误");

				int pos = now[2].p_1;
				int sag = now[2].seg;
				int ct = now[2].p_2;
				for(int cnt=0;cnt<level;cnt++)
				{
					cls_compiler_command cmd;
					cmd.oper = command_get;
					cmd.ptr1 = pos;
					cmd.ct1 = get_command_type(now[2].p_2,now[2].p_3,now[2].p_4);
					cmd.seg1 = sag;
					cmd.re = cstm.get_tmp_pos(now[2].p_2,level - cnt - 1,now[2].p_4);

					cmd.ct_re = get_command_type(now[2].p_2,now[2].p_3 - cnt - 1,now[2].p_4);

					if (cstm.tables.size() == 1)
						cmd.seg_re = seg_const;
					else
						cmd.seg_re = seg_stack;

					if (cmd.re == -1)
					{
						error("类型未声明！");
					}

					pos = cmd.re;
					des.push_back(cmd);
				}

				re.seg = now[2].seg;
				re.p_1 = pos;
				re.p_2 = now[2].p_2;
				re.p_3 = now[2].p_3 - mem_level;
				re.p_4 = now[2].p_4;
				re.real_pointer_level = now[2].p_3;

				re.b_left = true;
			}
			else
			{
				re.copy_from(now[2]);
				re.p_3--;
			}
		}
		break;
	case 1041:
		{
			if (now[1].b_left == false)
			{
				re.copy_from(now[1]);
				re.p_3 --;

				cls_compiler_command cmd;
				cmd.oper = command_add;
				cmd.ptr1 = now[1].p_1;
				cmd.seg1 = now[1].seg;
				cmd.ct1 = get_command_type(now[1].p_2,now[1].p_3,now[1].p_4);
				cmd.ptr2 = now[3].p_1;
				cmd.seg2 = now[3].seg;
				cmd.ct2 =get_command_type(now[3].p_2,now[3].p_3,now[1].p_4);
				cmd.re  = cstm.get_tmp_pos(4);

				if (cmd.re == -1)
				{
					error("类型未声明！");
				}

				cmd.seg_re = cmd.seg1;
				cmd.ct_re = cmd.ct1;
				des.push_back(cmd);

				re.p_1 = cmd.re;
				re.b_left = true;
			}
			else
			{
				if (now[1].p_3 == 0)
					error("数据指针层数错误");

				cls_compiler_command cmd;

				cmd.oper = command_add;
				cmd.ptr1 = now[1].p_1;
				cmd.seg1 = now[1].seg;
				cmd.ct1 = get_command_type(now[1].p_2,now[1].p_3,now[1].p_4);
				cmd.ptr2 = now[3].p_1;
				cmd.seg2 = now[3].seg;
				cmd.ct2 =get_command_type(now[3].p_2,now[3].p_3,now[1].p_4);
				cmd.re  = cstm.get_tmp_pos(4);

				if (cmd.re == -1)
				{
					error("类型未声明！");
				}

				cmd.seg_re = cmd.seg1;
				cmd.ct_re = cmd.ct1;

				if (cmd.re == -1)
				{
					error("类型未声明！");
				}

				re.copy_from(now[1]);
				re.p_1 = cmd.re;
				re.p_3--;
				re.p_4 = false;

				if (now[1].real_pointer_level == 0)
				{
					re.real_pointer_level = now[1].p_3;
				}
				else
				{
					re.real_pointer_level = now[1].real_pointer_level;
				}

				cmd.ct_re = get_command_type(now[1].p_2,re.p_3,now[1].p_4);

				des.push_back(cmd);

				re.b_left = true;
			}
		}
		break;
	case 1042:
		;
		break;
	case 1043:
		{
			cls_compiler_symbol_table_item item;
			if (false == cstm.get_name_info(now[1].str,item))
			{
				error("变量未声明");
			}

			re.p_1 = item.memory_ptr;
			re.seg = item.seg;
			re.p_2 = item.c_type;
			re.p_3 = item.pointer_level;
			re.p_4 = item.n_const;
		}
		break;
	case 1044:
		{
			cls_compiler_symbol_table_item item;
			item.type = type_string;
			item.context = now[1].str;

			if (!cstm.check_name_info(now[1].str))
			{
				cstm.add_name_info(item);
			}

			cstm.add_name_info(item);
			re.p_1 = cstm.get_name_info(now[1].str).memory_ptr;
			re.seg = cstm.get_name_info(now[1].str).seg;
			re.p_2 = ctype_char;
			re.p_3 = 1;
			re.p_4 = false;

		}
		break;
	case 1045:
		{
			cls_compiler_symbol_table_item item;
			item.type = type_const;
			item.context = now[1].str;

			if (!cstm.check_name_info(now[1].str))
			{
				cstm.add_name_info(item);
			}

			re.p_1 = cstm.get_name_info(now[1].str).memory_ptr;
			re.seg = cstm.get_name_info(now[1].str).seg;
			re.p_2 = ctype_int;
			re.p_3 = 0;
			re.p_4 = false;
		}

		break;

	case 1046:
		{
			cls_compiler_symbol_table_item item;
			item.type = type_char;
			item.context = now[1].str;

			if (!cstm.check_name_info(now[1].str))
			{
				cstm.add_name_info(item);
			}

			cstm.add_name_info(item);
			re.p_1 = cstm.get_name_info(now[1].str).memory_ptr;
			re.seg = cstm.get_name_info(now[1].str).seg;
			re.p_2 = ctype_char;
			re.p_3 = 0;
			re.p_4 = false;
		}
		break;

	case 1047:
		{
			cls_compiler_symbol_table_item item;
			item.type = type_const;
			item.context = now[2].str;
			item.type = type_var;
			item.c_type = now[2].p_2;
			item.pointer_level = now[2].p_3;
			item.n_const = now[2].p_4;

			cls_compiler_command cmd;
			cmd.oper = command_neg;
			cmd.ptr1 = now[2].p_1;
			cmd.seg1 = now[2].seg;
			cmd.ct1 = get_command_type(now[2].p_2,now[2].p_3,now[2].p_4);
			cmd.re = cstm.get_tmp_pos(cstm.get_mem_port(item));

			if (cmd.re == -1)
			{
				error("类型未声明！");
			}

			cmd.seg_re = cmd.seg1;
			cmd.ct_re = cmd.ct1;
			des.push_back(cmd);

			re.seg = cstm.get_name_info(now[1].str).seg;
			re.p_1 = cmd.re;
			re.seg = cmd.seg_re;
			re.p_2 = now[2].p_2;
			re.p_3 = now[2].p_3;
			re.p_4 = now[2].p_4;
		}
		break;

	case 1048:
		{
			re.copy_from(now[1]);
			if (now[1].b_left == true)
			{
				cls_compiler_command cmd1;
				cmd1.oper = command_get;
				cmd1.ptr1 = now[1].p_1;
				cmd1.seg1  = now[1].seg;
				cmd1.ct1 = get_command_type(now[1].p_2,now[1].p_3+1,now[1].p_4);
				cmd1.re = cstm.get_tmp_pos(now[1].p_2,now[1].p_3,now[1].p_4);
				cmd1.ct_re = get_command_type(now[1].p_2,now[1].p_3,now[1].p_4);
				cmd1.seg_re = now[1].seg;

				des.push_back(cmd1);
				
				re.p_1 = cmd1.re;
				re.seg = cmd1.seg_re;
			}
		}
		break;
	case 1049:
		{
			cls_compiler_command cmd1;
			cmd1.oper = command_new_add_ref;
			cmd1.ptr1 = now[2].p_3;
			cmd1.re = now[2].p_1;
			cmd1.ct_re = ctype_pointer;
			cmd1.seg_re = seg_none;

			des.push_back(cmd1);

			cls_compiler_command cmd;
			cmd.oper = command_get_pointer;
			statement_copy(cmd,now[2],now[2],now[2]);
			cmd.re = cstm.get_tmp_pos(4);
			cmd.ct_re = get_command_type(now[2].p_2,now[2].p_3,now[2].p_4);
			cmd.seg_re = seg_stack;

			if (cmd.re == -1)
			{
				error("类型未声明！");
			}

			des.push_back(cmd);

			re.p_1 = cmd.re;
			re.seg = cmd.seg_re;
			re.p_2 = now[2].p_2;
			re.p_3 = now[2].p_3 + 1;
			re.p_4 = now[2].p_4;
		}
		break;
	case 1050:
		{
			if (!fn_type_trans(now[1].p_2,now[3].p_2,now[1].p_3,now[3].p_3))
			{
				error("类型不符");
			}

			if (now[1].p_3 != 0 && now[1].p_4 > 0 && now[3].p_4 == 0)
			{
				error("智能指针不能赋给非智能指针！");
			}

			if (now[1].p_4 == 1 && now[1].p_3 > 0)
			{
				cls_compiler_command cmd;
				cmd.oper = command_delete;
				cmd.ptr1 = - now[1].p_3 + now[1].real_pointer_level + 1;
				cmd.re = now[1].p_1;
				cmd.seg_re = now[1].seg;
				cmd.ct_re = ctype_pointer;
				des.push_back(cmd);
			}
			else if (now[1].p_4 == 2 && now[1].p_3 > 0)
			{
				cls_compiler_command cmd;
				cmd.oper = command_delete_random;
				cmd.ptr1 = - now[1].p_3 + now[1].real_pointer_level + 1;
				cmd.re = now[1].p_1;
				cmd.seg_re = now[1].seg;
				cmd.ct_re = ctype_pointer_random;
				des.push_back(cmd);
			}

			if (now[3].p_4 == 1 && now[3].p_3 > 0)
			{
				cls_compiler_command cmd;
				cmd.oper = command_new_add_ref;
				cmd.ptr1 = - now[1].p_3 + now[1].real_pointer_level + 1;
				cmd.re = now[3].p_1;
				cmd.seg_re = now[3].seg;
				cmd.ct_re = ctype_pointer;
				des.push_back(cmd);
			}
			else if (now[3].p_4 == 2 && now[3].p_3 > 0)
			{
				cls_compiler_command cmd;
				cmd.oper = command_new_add_ref_random;
				cmd.ptr1 = - now[1].p_3 + now[1].real_pointer_level + 1;
				cmd.re = now[3].p_1;
				cmd.seg_re = now[3].seg;
				cmd.ct_re = ctype_pointer_random;
				des.push_back(cmd);
			}

			cls_compiler_command cmd;

			if (now[1].b_left == true)
			{
				cmd.oper = command_pointer_set;
				now[1].p_3++;
				statement_copy(cmd,now[3],now[3],now[1]);
				now[1].p_3--;

				des.push_back(cmd);
			}
			else
			{
				cmd.oper = command_set;
				statement_copy(cmd,now[3],now[3],now[1]);

				des.push_back(cmd);
			}

			re.copy_from(now[1]);
		}
		break;
	case 1083:
		{
			cls_compiler_symbol_table_item i;
			i.type = type_var;
			i.c_type = now[2].p_2;
			i.n_const = now[2].p_4;
			i.pointer_level = now[2].p_3;

			cls_compiler_command cmd;
			cmd.oper = command_reverse;
			statement_copy(cmd,now[2],now[2],now[2]); 
			cmd.re = cstm.get_tmp_pos(now[2].p_2,now[2].p_3,now[2].p_4);

			if (cmd.re == -1)
			{
				error("类型未声明！");
			}

			des.push_back(cmd);

			re.copy_from(now[1]);
			re.p_1 = cmd.re;
		}
		break;
	case 1084:
		{
			cls_compiler_command cmd;
			cmd.oper = command_not;
			statement_copy(cmd,now[2],now[2],now[2]);
			cmd.re = cstm.get_tmp_pos(now[2].p_2,now[2].p_3,now[2].p_4);

			if (cmd.re == -1)
			{
				error("类型未声明！");
			}

			des.push_back(cmd);
			re.copy_from(now[1]);
			re.p_1 = cmd.re;
		}
		break;
	case 1085:
		{
			des[now[5].p_1].re = now[7].p_2 - 1;
			des.pop_back();
		}
		break;
	case 1086:
		{
			des[now[5].p_1].re = now[8].p_2;
			des[now[8].p_1].re = now[10].p_2;

		}
		break;
	case 1087:
		{
			des[now[6].p_1].re = now[8].p_2;
			des[now[8].p_1].re = now[3].p_1;

		}
		break;
	case 1088:
		{
			des[now[9].p_1].ptr2 = now[12].p_2;
			des[now[9].p_1].re = now[14].p_2;
			des[now[12].p_1].re = now[6].p_2;
			des[now[14].p_1].re = now[9].p_2;

		}
		break;
	case 1089:
		{
			cls_compiler_command cmd;
			cmd.oper = command_jump;
			cmd.ptr1 = now[7].p_1;
			cmd.ct1 = get_command_type(now[7].p_2,now[7].p_3,now[7].p_4);
			cmd.seg1 = now[7].seg;
			cmd.ptr2 = now[2].p_1;
			cmd.re = des.size() + 1;
			des.push_back(cmd);
		}
		break;
	case 1090:
		{
			cls_compiler_command cmd;
			re.p_1 = des.size();
			cmd.oper = command_jump;
			cmd.ptr1 = (stack.rbegin() + 1)->p_1;
			cmd.ct1 =  (stack.rbegin() + 1)->p_2;
			cmd.seg1 = (stack.rbegin() + 1)->seg;
			cmd.ptr2 = des.size() + 1;
			cmd.re = -1;
			des.push_back(cmd);
		}
		break;
	case 1091:
		{
			cls_compiler_command cmd;
			cmd.oper = command_abs_jump;
			cmd.re = -1;
			des.push_back(cmd);
			re.p_1 = des.size() - 1;
			re.p_2 = des.size();
		}
		break;
	case 1092:
		{
			re.p_2 = des.size();
		}
		break;
	case 1093:
		{
			re.p_1 = des.size();
		}
		break;

	case 1094:
		{
			cls_compiler_command cmd;
			cmd.oper = command_while;
			cmd.ptr1 = (stack.rbegin() + 1)->p_1;
			cmd.ct1 =  (stack.rbegin() + 1)->p_2;
			cmd.seg1 = (stack.rbegin() + 1)->seg;
			cmd.ptr2 = des.size()+1;
			cmd.re = -1;
			des.push_back(cmd);
			re.p_1 = des.size() - 1;
			re.p_2 = des.size();
		}
		break;
	case 1095:
		{
			cls_compiler_command cmd;
			cmd.oper = command_while_re;
			cmd.re = -1;
			des.push_back(cmd);
			re.p_1 = des.size() - 1;
			re.p_2 = des.size();
		}
		break;
	case 1096:
		{
			;
		}
		break;
	case 1097:
		{
			re.p_2 = des.size();
		}
		break;
	case 1098:
		{
			cls_compiler_command cmd;
			cmd.oper = command_for;
			cmd.ptr1 = (stack.rbegin() + 1)->p_1;
			cmd.ct1 =  (stack.rbegin() + 1)->p_2;
			cmd.seg1 = (stack.rbegin() + 1)->seg;
			cmd.re = -1;
			des.push_back(cmd);
			re.p_1 = des.size() - 1;
			re.p_2 = des.size();
		}
		break;
	case 1099:
		{
			cls_compiler_command cmd;
			cmd.oper = command_abs_jump;
			cmd.re = -1;
			des.push_back(cmd);
			re.p_1 = des.size() - 1;
			re.p_2 = des.size();
		}
		break;
	case 1100:
		{
			cls_compiler_command cmd;
			cmd.oper = command_for_re;
			cmd.re = -1;
			des.push_back(cmd);
			re.p_1 = des.size()-1;
			re.p_2 = des.size();
		}
		break;
	case 1101:
		{
			re.p_1 = des.size();
		}
		break;
	case 1102:
		{
		}
		break;
	case 1103:
		{
		}
		break;
	case 1104:
		{
			cstm.enter_block();
		}
		break;
	case 1105:
		{
			cstm.leave_block(des);
		}
		break;
	case 1106:
		{
			if (now[1].p_4 == 1)
				error("smart不能改变，请使用random！");

			cls_compiler_command cmd;
			cmd.oper = command_inc;
			statement_copy(cmd,now[1],now[1],now[1]);

			cmd.re = cstm.get_tmp_pos(now[1].p_2,now[1].p_3,now[1].p_4);

			if (cmd.re == -1)
			{
				error("类型未声明！");
			}

			des.push_back(cmd);

			re.copy_from(now[1]);
			re.p_1 = cmd.re;
		}
		break;
	case 1107:
		{
			if (now[2].p_4 == 1)
				error("smart不能改变，请使用random！");

			cls_compiler_command cmd;
			cmd.oper = command_inc;
			statement_copy(cmd,now[2],now[2],now[2]);

			des.push_back(cmd);

			re.copy_from(now[1]);
		}
		break;
	case 1108:
		{
			if (now[1].p_4 == 1)
				error("smart不能改变，请使用random！");

			cls_compiler_command cmd;
			cmd.oper = command_dec;
			statement_copy(cmd,now[1],now[1],now[1]);

			cmd.re = cstm.get_tmp_pos(now[1].p_2,now[1].p_3,now[1].p_4);

			if (cmd.re == -1)
			{
				error("类型未声明！");
			}

			des.push_back(cmd);

			re.copy_from(now[1]);
			re.p_1 = cmd.re;
		}
		break;
	case 1109:
		{
			if (now[2].p_4 == 1)
				error("smart不能改变，请使用random！");

			cls_compiler_command cmd;
			cmd.oper = command_dec;
			statement_copy(cmd,now[2],now[2],now[2]);

			des.push_back(cmd);

			re.copy_from(now[1]);
		}
		break;
	case 1110:
		{
			cls_compiler_symbol_table_item item,ins;
			item.type = type_var;
			item.c_type = now[2].p_2;
			item.pointer_level = now[2].p_3;

			int n = cstm.get_mem_port(item);
			string str;
			stringstream ss(str);
			ss<<n;

			ins.context = str;
			ins.type = type_const;
			ins.pointer_level = 0;
			ins.n_const = true;

			if (!cstm.check_name_info(str))
			{
				cstm.add_name_info(ins);
			}

			re.p_1 = cstm.get_name_info(str).memory_ptr;
			re.seg = cstm.get_name_info(str).seg;
			re.p_2 = ctype_int;
			re.p_3 = 0;
			re.p_4 = true;
		}
		break;
	case 1111:
		{
			if (now[1].p_2 < 100)
				error("类型不正确");
			else if (now[1].p_3 != 1)
				error("只有指针才能使用->符号。");

			cls_compiler_symbol_table_item item;
			if (false == cstm.get_struct(now[1].p_2).get_struct_item(now[3].str,item))
			{
				error("结构体成员错误！");
			}
			else
			{
				re.copy_from(now[1]);
				re.p_1 = now[1].p_1 + item.memory_ptr;
				re.seg = now[1].seg;
				re.p_2 = item.c_type;
				re.p_3 = item.pointer_level;
				re.p_4 = item.n_const;
			}
		}
		break;
	case 1112:
		{
			cls_compiler_symbol_table_item item;
			if (false == cstm.get_struct(now[1].p_2).get_struct_item(now[3].str,item))
			{
				error("结构体成员错误！");
			}
			else
			{
				re.p_1 = now[1].p_1 + item.memory_ptr;
				re.seg = now[1].seg;
				re.p_2 = item.c_type;
				re.p_3 = item.pointer_level;
				re.p_4 = item.n_const;
			}
		}
		break;
	case 1113:
		{
			cstm.de_ref_cur(des);
			cls_compiler_command cmd;
			cmd.oper = command_return;
			cmd.re = now[2].p_1;
			statement_copy(cmd,now[2],now[2],now[2]);
			des.push_back(cmd);
		}
		break;
	case 1114:
		{
			//类型转换。
		}
		break;
	case 1115:
		{
			re.copy_from(now[2]);
		}
		break;
	case 1116:
		{
			cls_compiler_command cmd,cmd1,cmd2;

			cls_compiler_symbol_table_item *citem;
			if (!cstm.get_func(now[1].str,&citem) == true)
				error("函数不存在");

			cls_compiler_symbol_table_item& item = *citem;
			if (item.param.size() != 0)
				error("函数参数个数不对！");

			re.str = now[1].str;
			cmd.oper = command_pre_call;
			cmd.re = cstm.n_cur_num;
			cmd.seg_re = seg_none;
			cmd.ct_re = ctype_int;

			des.push_back(cmd);

			item.type = type_var;
			item.type = type_var;
			cmd1.oper = command_call;
			cmd1.name = item.context;

			cmd2.oper = command_after_call;
			cmd2.ptr1 = now[1].p_1;
			cmd2.ct1 = get_command_type(item.c_type,item.pointer_level,item.n_const);
			cmd2.seg1 = seg_stack;
			cmd2.seg_re = seg_stack;
			cmd2.re = cstm.n_cur_num;
			cmd2.seg_re = seg_none;
			cmd2.ct_re = ctype_int;

			des.push_back(cmd1);
			des.push_back(cmd2);

			re.p_1 = cmd2.ptr1;
			re.seg = seg_stack;
			re.p_2 = item.c_type;
			re.p_3 = item.pointer_level;
			re.p_4 = item.n_const;
		}
		break;
	case 1117:
		{
			cls_compiler_command cmd,cmd1,cmd2;
			cls_compiler_symbol_table_item *citem;
			if (!cstm.get_func(now[1].str,&citem) == true)
				error("函数不存在");

			cls_compiler_symbol_table_item &item = *citem;

			int total = item.param.size();

			if(total != now[2].p_1 + 1)
			{
				error("函数参数个数不对！");
			}

			for(int cnt=0;cnt<total;cnt++)
			{
				if (now[2].tb_items[cnt].pointer_level != item.param[cnt].pointer_level)
				{
					error("函数的参数类型不对！");
				}
				else if (now[2].tb_items[cnt].n_const >= 1 && item.param[cnt].n_const  == 0)
				{
					error("smart、random都不能被非智能赋值！");
				}
				else if (!fn_type_trans(now[2].tb_items[cnt].c_type,item.param[cnt].c_type,now[2].tb_items[cnt].pointer_level,item.param[cnt].pointer_level))
				{
					error("类型不匹配！");
				}
			}

			re.str = now[1].str;
			cmd.oper = command_pre_call;
			cmd.re = cstm.n_cur_num;
			cmd.seg_re = seg_none;
			cmd.ct_re = ctype_int;

			des.push_back(cmd);

			for(int cnt=total-1;cnt>=0;cnt--)
			{
				cls_compiler_command cmd;
				cmd.oper = command_push;
				cmd.re =  - cstm.n_cur_num + now[2].tb_items[cnt].memory_ptr;
				cmd.seg_re = now[2].tb_items[cnt].seg;
				cmd.ct_re = get_command_type(now[2].tb_items[cnt].c_type,now[2].tb_items[cnt].pointer_level,now[2].tb_items[cnt].n_const);
				des.push_back(cmd);
			}

			item.type = type_var;
			cmd1.oper = command_call;
			cmd1.name = item.context;

			cmd2.oper = command_after_call;
			cmd2.ptr1 = now[1].p_1;
			cmd2.ct1 =  get_command_type(item.c_type,item.pointer_level,item.n_const);
			cmd2.seg1 = seg_stack;
			cmd2.seg_re = seg_stack;
			cmd2.re = cstm.n_cur_num;
			cmd2.seg_re = seg_none;
			cmd2.ct_re = ctype_int;

			des.push_back(cmd1);
			des.push_back(cmd2);

			re.p_1 = cmd2.ptr1;
			re.seg = seg_stack;
			re.p_2 = item.c_type;
			re.p_3 = item.pointer_level;
			re.p_4 = item.n_const;
		}
		break;
	case 1118:
		{
			if (now[1].p_3 >0 && now[1].p_4 == 1)
			{
				cls_compiler_command cmd_1;
				cmd_1.oper = command_new_add_ref;
				cmd_1.ptr1 = 1;
				cmd_1.re = now[1].p_1;
				cmd_1.ct_re = ctype_pointer;
				cmd_1.seg_re = seg_none;
				des.push_back(cmd_1);
			}
			else if (now[1].p_3 >0 && now[1].p_4 == 2)
			{
				cls_compiler_command cmd_1;
				cmd_1.oper = command_new_add_ref_random;
				cmd_1.ptr1 = 1;
				cmd_1.re = now[1].p_1;
				cmd_1.ct_re = ctype_pointer_random;
				cmd_1.seg_re = seg_none;
				des.push_back(cmd_1);
			}

			//cls_compiler_command cmd;
			//cmd.oper = command_push;
			//cmd.re = now[1].p_1;
			//cmd.seg_re = now[1].seg;
			//cmd.ct_re = get_command_type(now[1].p_2,now[1].p_3);
			//des.push_back(cmd);

			cls_compiler_symbol_table_item item;
			item.c_type = now[1].p_2;
			item.pointer_level = now[1].p_3;
			item.n_const = now[1].p_4;
			item.memory_ptr = now[1].p_1;

			re.p_1 = 0;
			re.tb_items.push_back(item);
		}
		break;
	case 1119:
		{
			if (now[3].p_3 >0 && now[3].p_4 == 1)
			{
				cls_compiler_command cmd_1;
				cmd_1.oper = command_new_add_ref;
				cmd_1.ptr1 = 1;
				cmd_1.re = now[3].p_1;
				cmd_1.ct_re = ctype_pointer;
				cmd_1.seg_re = seg_none;
				des.push_back(cmd_1);
			}
			else if (now[3].p_3 >0 && now[3].p_4 == 1)
			{
				cls_compiler_command cmd_1;
				cmd_1.oper = command_new_add_ref_random;
				cmd_1.ptr1 = 1;
				cmd_1.re = now[3].p_1;
				cmd_1.ct_re = ctype_pointer;
				cmd_1.seg_re = seg_none;
				des.push_back(cmd_1);
			}

			//cls_compiler_command cmd;
			//cmd.oper = command_push;
			//cmd.re = now[3].p_1;
			//cmd.seg_re = now[3].seg;
			//cmd.ct_re = get_command_type(now[1].p_2,now[1].p_3);
			//des.push_back(cmd);

			cls_compiler_symbol_table_item item;
			item.c_type = now[3].p_2;
			item.pointer_level = now[3].p_3;
			item.n_const = now[3].p_4;
			item.memory_ptr = now[3].p_1;

			re.tb_items.push_back(item);
			for(int cnt=0;cnt<now[1].tb_items.size();cnt++)
			{
				re.tb_items.push_back(now[1].tb_items[cnt]);
			}

			re.p_1 = now[1].p_1 + 1;
		}
		break;
	case 1120:
		{
			cls_compiler_command cmd;
			cmd.oper = command_new;
			//ptr1用于保存指针的层数！以便解引用时可以垃圾回收；
			cmd.ptr1 = now[2].p_3+1;
			cmd.seg1 = seg_none;
			cmd.ct1 = ctype_pointer;
			cmd.ptr2 = now[4].p_1;
			cmd.seg2 = now[4].seg;
			cmd.ct2 = now[2].p_1;
			if (cstm.tables.size() == 1)
				cmd.seg_re = seg_const;
			else 
				cmd.seg_re = seg_stack;

			cmd.re = cstm.get_tmp_pos(now[2].p_1,now[2].p_2+1,now[2].p_3);
			
			//cls_compiler_symbol_table_item item;
			//item.memory_ptr = cmd.re;
			//item.n_const = 1;
			//item.type = type_var;
			//item.c_type = ctype_pointer;
			//item.context = fn_get_random_name("new_const",10);
			//cstm.add_name_info(item);
	
			if (cmd.re == -1)
			{
				error("类型未声明！");
			}

			cmd.ct_re = get_command_type(now[2].p_1,now[2].p_2+1,now[2].p_3);
			des.push_back(cmd);

			re.p_1 = cmd.re;
			re.seg = cmd.seg_re;
			re.p_2 = now[2].p_1;
			re.p_3 = now[2].p_2 + 1;
			re.p_4 = 1;
		}
		break;
	case 1124:
		{
			cls_compiler_symbol_table_item *item;
			if (cstm.get_func(now[1].str_re,&item) == true)
				item->param = now[3].tb_items;
			else
				error("函数没定义！");
		}
		break;
	case 1126:
		{
			re.p_1 = ctype_void;
		}
		break;
	case 1127:
		{
			cls_compiler_symbol_table_item item;
			item.type = type_var;
			item.context = now[1].str;
			item.c_type = ctype_double;

			if (!cstm.check_name_info(now[1].str))
			{
				cstm.add_name_info(item);
			}

			cstm.add_name_info(item);
			re.p_1 = cstm.get_name_info(now[1].str).memory_ptr;
			re.seg = cstm.get_name_info(now[1].str).seg;
			re.p_2 = ctype_double;
			re.p_3 = 0;
			re.p_4 = false;
		}
	case 1121:
		{
			cls_compiler_command cmd;
			cmd.oper = command_break;
			des.push_back(cmd);
		}
		break;
	case 1122:
		{
			cls_compiler_command cmd;
			cmd.oper = command_continue;
			des.push_back(cmd);
		}
		break;
	case 1129:
		{
			re.str = now[1].str;
			cls_compiler_symbol_table_item *citem;
			if (!cstm.get_func(now[1].str,&citem) == true)
				error("函数不存在");

			cls_compiler_symbol_table_item &item = *citem;

			if (cstm.get_mem_port(item) != 0)
			{
				re.p_1 = cstm.get_tmp_pos(cstm.get_mem_port(item));

				if (re.p_1 == -1)
				{
					error("类型未声明！");
				}

			}				
			else
			{
				re.p_1 = 0;
			}
		}
		break;
	case 1132:
		{
			des[now[5].p_1].re = now[8].p_2 - 1;
			des.pop_back();
		}
		break;
	case 1133:
		{
			des[now[5].p_1].re = now[9].p_2;
			des[now[9].p_1].re = now[12].p_2;

		}
		break;
	case 1134:
		{
			des[now[6].p_1].re = now[9].p_2;
			des[now[9].p_1].re = now[3].p_1;

		}
		break;
	case 1135:
		{
			des[now[9].p_1].ptr2 = now[12].p_2;
			des[now[9].p_1].re = now[15].p_2;
			des[now[12].p_1].re = now[6].p_2;
			des[now[15].p_1].re = now[9].p_2;

		}
		break;
	case 1136:
		{
			cls_compiler_command cmd;
			cmd.oper = command_jump;
			cmd.ptr1 = now[7].p_1;
			cmd.ct1 = get_command_type(now[7].p_2,now[7].p_3,now[7].p_4);
			cmd.seg1 = now[7].seg;
			cmd.ptr2 = now[2].p_1;
			cmd.re = des.size() + 1;
			des.push_back(cmd);
		}
		break;
	case 1137:
		{
			re.p_1 = now[2].p_1;
			re.p_2 = now[2].p_2;
			re.p_3 = 2;
		}
		break;
	case 1138:
		{
			cls_compiler_command cmd,cmd1,cmd2;
			int ptr = des.size();
			cmd.oper = command_abs_jump;
			cmd.re = -1;
			des.push_back(cmd);

			des[now[5].p_1].re = des.size();

			cmd2.oper = command_equ;
			cmd2.ptr1 = now[3].p_1;
			cmd2.ct1 = get_command_type(now[3].p_2,now[3].p_3,now[3].p_4);
			cmd2.seg1 = now[3].seg;

			int n_record = -1;
			for(int cnt=0;cnt<now[7].cases.size();cnt++)
			{
				if (!fn_type_trans(now[3].p_2,now[7].cases[cnt].p_2,now[3].p_3,now[7].p_4))
				{
					error("类型不符合，也可能是指针层数不符合！");
				}

				if (now[7].cases[cnt].p_2 == -1)
				{
					if (-1 != n_record)
					{
						error("存在多个default，这时不允许的！");
					}

					n_record = cnt;

					continue;
				}

				cmd2.ptr2 = now[7].cases[cnt].p_1;
				cmd2.ct2 = get_command_type(now[7].cases[cnt].p_2,now[7].cases[cnt].p_3,now[7].cases[cnt].p_4);
				cmd2.seg2 = now[7].cases[cnt].seg;
				cmd2.re = cstm.get_tmp_pos(4);
				cmd2.seg_re = seg_stack;
				cmd2.ct_re = ctype_int;

				des.push_back(cmd2);

				cls_compiler_command cmd;
				cmd.oper = command_jump;
				cmd.ptr1 = cmd2.re;
				cmd.ct1 = ctype_int;
				cmd.seg1 = seg_stack;
				cmd.ptr2  = now[7].ptrs[cnt];
				cmd.re = des.size() + 1;
				des.push_back(cmd);
			}

			if (n_record != -1)
			{
				cls_compiler_command cmd;
				cmd.oper = command_abs_jump;
				cmd.re = now[7].ptrs[n_record];
				des.push_back(cmd);
			}

			des[ptr].re = des.size();

			cmd1.oper = command_switch_re;
			des.push_back(cmd1);
		}
		break;
	case 1139:
		{
			re.cases.push_back(now[2]);
			re.ptrs.push_back(now[3].p_1);
			//case_recode的p_1表示这个case 开始的地址！。
		}
		break;
	case 1140:
		{
			re.cases = now[1].cases;
			re.cases.push_back(now[3]);
			re.ptrs = now[1].ptrs;
			re.ptrs.push_back(now[4].p_1);
		}
		break; 
	case 1141:
		{
			re.p_1 = des.size();
		}
		break;
	case 1142:
		{
			cls_compiler_command cmd;
			cmd.oper = command_switch;
			cmd.re = -1;

			des.push_back(cmd);
			re.p_1 = des.size()-1;
		}
		break;
	case 1143:
		{
			//cls_compiler_command cmd;
			//cmd.oper = command_abs_jump;
			//cmd.re = -1;

			//des.push_back(cmd);
			re.p_1 = des.size() - 1;
			re.p_2 = 0;
		}
		break;
	case 1144:
		{
			now[2].p_2 = -1;
			re.cases.push_back(now[2]);
			re.ptrs.push_back(now[3].p_1);
		}
		break;
	case 1145:
		{
			now[3].p_2 = -1;
			re.cases = now[1].cases;
			re.cases.push_back(now[3]);
			re.ptrs = now[1].ptrs;
			re.ptrs.push_back(now[4].p_1);
		}
		break;
	case 1146:
		{
			//留给短路表达式！
		}
		break;
	case 1147:
		{
			re.p_1 = 1;
		}
		break;
	case 1148:
		{
			re.p_1  = now[2].p_1 + 1;
		}
		break;
	case 1149:
		re.copy_from(now[2]);
		break;
	case 1150:
		{
			cls_compiler_symbol_table_item item;
			if (false == cstm.get_name_info(now[1].str,item))
			{
				error("变量未声明");
			}

			re.p_1 = item.memory_ptr;
			re.seg = item.seg;
			re.p_2 = item.c_type;
			re.p_3 = item.pointer_level;
			re.p_4 = item.n_const;
			re.b_left = false;
		}
		break;
	default:
		break;
	}

	return true;
}

bool cls_compiler_syntex::do_run(int do_what)
{
	vector<cls_compiler_syntex_item> stack;
	stack.push_back(cls_compiler_syntex_item(0,type_oper,"?"));

	if (do_what == 0)
		src += "?";

	int type;
	bool b_get_next = true;
	int cur_status = 0;
	int next_status = 0;
	int pre_status = -1;
	string str_pre;
	int n_pre;

	while(cw == true || b_get_next == false)
	{
		if (b_get_next)
		{
			while((str_get = cw.get_next(type))=="");
		}
		else
		{
			b_get_next = true;
		}

		if (stack.size() >= 10000)
		{
			error("程序过大！请分开编译后链接。或者程序出现不可修复的问题！");
		}

		pre_status = cur_status;
		cur_status = stack.back().status;

		int ter_id = 0;
		switch(type)
		{
		case type_const:
			ter_id = ter_info["const_num"];
			break;
		case type_const_double:
			ter_id = ter_info["const_double"];
			break;
		case type_oper:
			ter_id = ter_info[str_get];
			break;
		case type_var:
			if (check_key_word(str_get))
			{
				ter_id = ter_info[str_get];
			}
			else
			{
				ter_id = ter_info["var"];
			}
			break;
		case type_string:
			ter_id = ter_info["string"];
			break;
		case type_char:
			ter_id = ter_info["char"];
			break;
		case -1:
			error(str_get,pre_status);
			return false;
			break;

		}

		if (cur_status >= 1000)
		{
			next_status = cur_status;
		}
		else
		{
			next_status = action_table.get_next(cur_status,ter_id);
		}

		if (next_status == -1)
		{
			error(str_get,pre_status);
			return false;
		}

		if (next_status < 1000)
		{
			stack.push_back(cls_compiler_syntex_item(next_status,type,str_get));
		}
		else
		{
			//cout<<next_status<<endl;

			vector<cls_compiler_syntex_item> now;
			for(int cnt_k=0;cnt_k<product_info[next_status-1000].second;cnt_k++)
			{
				now.push_back(stack.back());
				stack.pop_back();
			}

			cls_compiler_syntex_item nedd(0,0,"");
			now.push_back(nedd);
			reverse(now.begin(),now.end());

			int tmp_status = stack.back().status;
			int real_status = action_table.get_next(tmp_status,product_info[next_status-1000].first);
			cls_compiler_syntex_item re(real_status,product_info[next_status-1000].first,"$non_it$");

			if (do_what == 0)
			{
				do_run_real(now,next_status,re,stack);
			}
			else if (do_what == 1)
			{
				if (true == do_run_check(now,next_status,re))
					return true;
			}
			else if (do_what == 4)
			{
				cout<<next_status<<endl;
			}

			if (real_status == -1)
			{
				error(str_get,pre_status);
				return false;
			}

			stack.push_back(re);

			b_get_next = false;
		}
	}

	return true;
}