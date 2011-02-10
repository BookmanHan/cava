#include "StdAfx.h"
#include "cls_compiler_symbol_table_manager.h"

int cls_compiler_symbol_table_manager::get_tmp_pos(int c_type,int pointer_level,int a_const,int type)
{
	cls_compiler_symbol_table_item item;
	item.type = type_var;
	item.c_type =c_type;
	item.n_const = a_const;
	item.pointer_level =pointer_level;

	return get_tmp_pos(get_mem_port(item));
}

cls_compiler_symbol_table_manager::cls_compiler_symbol_table_manager()
{
	n_static_num = 0;
	n_cur_num = 4;
}

int cls_compiler_symbol_table_manager::get_mem_port(cls_compiler_symbol_table_item item)
{
	if (item.pointer_level != 0)
	{
		if (item.n_const <= 1)
			return 4;
		else 
			return 8;
	}

	if (item.type == type_var)
	{
		switch(item.c_type)
		{
		case ctype_void:
			return 0;
			break;
		case ctype_double:
			return 8;
			break;
		case ctype_int:
			return 4;
			break;
		case ctype_short:
			return 2;
			break;
		case ctype_char:
			return 1;
			break;
		case ctype_unsigned_int:
			return 4;
			break;
		case ctype_unsigned_short:
			return 2;
			break;
		case ctype_unsigned_char:
			return 1;
			break;
		case ctype_pointer:
			return 4;
			break;
		case ctype_pointer_random:
			return 8;
			break;
		default:
			for(int cnt=0;cnt<struct_table.table_items.size();cnt++)
			{
				if (struct_table.table_items[cnt].c_type == item.c_type)
				{
					int re = 0;
					cls_compiler_symbol_table_item i = (struct_table.table_items[cnt]);
					for(int cnt=0;cnt<i.struct_info.size();cnt++)
					{
						re += get_mem_port(i.struct_info[cnt]);
					}

					return re;
				}
			}
			break;
		}
	}
	else if (item.type == type_struct)
	{
		int n_re = 0;
		for(int cnt=0;cnt<item.struct_info.size();cnt++)
		{
			int port = get_mem_port(item.struct_info[cnt]);
			n_re = n_re/port*port + port;
		}

		return n_re;
	}
	else if (item.type == type_char)
	{
		return 1;
	}
	else if (item.type == type_const)
	{
		return 8;
	}
	else if (item.type == type_string)
	{
		return item.context.size() + 1;
	}
	else 
	{
		return 0;
	}
}


int cls_compiler_symbol_table_manager::get_tmp_pos(int width)
{
	if (width == 0)
	{
		return -1;
	}

	int re =n_cur_num;
	if (n_cur_num%width != 0)
		n_cur_num = (1 + n_cur_num/width)*width + width;
	else 
		n_cur_num += width;

	return re;
}

bool cls_compiler_symbol_table_manager::add_func(cls_compiler_symbol_table_item& item)
{
	if (fun_table.get_name_info(item.context,0) == false)
		return fun_table.add_name_info(item);
	else
		return false;
}

bool cls_compiler_symbol_table_manager::get_func(string str,cls_compiler_symbol_table_item **item)
{
	if (fun_table.get_name_info(str,0) == false)
	{
		return false;
	}
	else
	{
		*item = &fun_table.get_name_info(str);
		return true;
	}
}

cls_compiler_symbol_table_item& cls_compiler_symbol_table_manager::get_struct(string str)
{
	return struct_table.get_name_info(str);
}

cls_compiler_symbol_table_item cls_compiler_symbol_table_manager::get_struct(int c_type)
{
	for(int cnt=0;cnt<struct_table.table_items.size();cnt++)
	{
		if (struct_table.table_items[cnt].c_type == c_type)
		{
			return struct_table.table_items[cnt];
		}
	}
}

bool cls_compiler_symbol_table_manager::add_struct(cls_compiler_symbol_table_item &item)
{
	return struct_table.add_name_info(item);
}

bool cls_compiler_symbol_table_manager::check_cur_by_mem(int mem)
{
	return true;
}

bool cls_compiler_symbol_table_manager::check_name_info(string str)
{
	cls_compiler_symbol_table_item item;
	return get_name_info(str,item);
}

bool cls_compiler_symbol_table_manager::get_name_info(string str,cls_compiler_symbol_table_item& item_get)
{
	vector<cls_compiler_symbol_table>::reverse_iterator itor = tables.rbegin();
	while(itor != tables.rend())
	{
		cls_compiler_symbol_table_item &item = itor->get_name_info(str);
		if (itor->get_name_info(str,0))
		{
			item_get = item;
			return true;
		}

		itor++;
	}

	if (const_table.get_name_info(str,0) == true)
	{
		item_get = const_table.get_name_info(str);
		return true;
	}

	return false;
}

cls_compiler_symbol_table_item cls_compiler_symbol_table_manager::get_name_info(string str)
{
	cls_compiler_symbol_table_item item;
	get_name_info(str,item);

	return item;
}
bool cls_compiler_symbol_table_manager::add_name_info(cls_compiler_symbol_table_item& item_set,bool auto_alloc)
{
	int port = get_mem_port(item_set);
	if (port == 0)
	{
		return false;
	}

	if (item_set.type == type_const || item_set.type == type_string || item_set.type == type_char)
	{
		if (auto_alloc)
		{	
			item_set.memory_ptr = n_static_num;
			item_set.seg = seg_const;
			
			if (n_static_num%port !=0)
				n_static_num = (1+n_static_num/port)*port + port;
			else
				n_static_num += port;
		}

		const_table.add_name_info(item_set);
		return true;
	}
	else if (tables.size() == 1)
	{
		if (auto_alloc)
		{	
			item_set.memory_ptr = n_static_num;
			item_set.seg = seg_const;

			if (n_static_num%port !=0)
				n_static_num = (1+n_static_num/port)*port + port;
			else
				n_static_num += port;
		}

		tables.back().add_name_info(item_set);
		return true;
	}
	else if (auto_alloc)
	{
		item_set.memory_ptr = n_cur_num;
		item_set.seg = seg_stack;

		if (n_cur_num%port !=0)
			n_cur_num = (1+n_cur_num/port)*port + port;
		else
			n_cur_num += port;
	}

	tables.back().add_name_info(item_set);

	return true;
}

bool cls_compiler_symbol_table_manager::enter_block()
{
	cls_compiler_symbol_table t;
	tables.push_back(t);
	return true;
}

bool cls_compiler_symbol_table_manager::de_ref_cur(vector<cls_compiler_command>&des)
{
	for(int cnt = 0;cnt<tables.back().table_items.size();cnt++)
	{
		if (tables.back().table_items[cnt].n_const == 1)
		{
			cls_compiler_command cmd;
			//存放指针的层数！
			cmd.oper = command_delete;
			cmd.re = tables.back().table_items[cnt].pointer_level;
			cmd.seg_re = seg_none;
			cmd.ct_re = ctype_pointer;

			des.push_back(cmd);
		}
		else
		{
			cls_compiler_command cmd;
			//存放指针的层数！
			cmd.oper = command_delete_random;
			cmd.re = tables.back().table_items[cnt].pointer_level;
			cmd.seg_re = seg_none;
			cmd.ct_re = ctype_pointer_random;

			des.push_back(cmd);

		}
	}

	return true;
}

bool cls_compiler_symbol_table_manager::leave_block(vector<cls_compiler_command>&des,bool check_deref)
{
	if (check_deref == true)
	{
		for(int cnt = 0;cnt<tables.back().table_items.size();cnt++)
		{
			if (tables.back().table_items[cnt].n_const == 1)
			{
				cls_compiler_command cmd;
				//存放指针的层数！
				cmd.oper = command_delete;
				cmd.ptr1 = 1;
				cmd.re = tables.back().table_items[cnt].memory_ptr;
				cmd.seg_re = tables.back().table_items[cnt].seg;
				cmd.ct_re = ctype_pointer;

				des.push_back(cmd);
			}
			else if (tables.back().table_items[cnt].n_const == 2)
			{
				cls_compiler_command cmd;
				//存放指针的层数！
				cmd.oper = command_delete_random;
				cmd.ptr1 = 1;
				cmd.re = tables.back().table_items[cnt].memory_ptr;
				cmd.seg_re = tables.back().table_items[cnt].seg;
				cmd.ct_re = ctype_pointer_random;

				des.push_back(cmd);
			}
		}
	}

	tables.pop_back();
	if(tables.size() == 1)
	{
		fun_table.get_cur().mem_total = n_cur_num;
		n_cur_num = 4;
	}

	if (tables.size() == 0)
		DebugBreak();

	return true;
}