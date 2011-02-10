#include "StdAfx.h"
#include "cls_compiler_symbol_table_item.h"

bool cls_compiler_symbol_table_item::get_struct_item(string str,cls_compiler_symbol_table_item& item)
{
	for(int cnt=0;cnt<struct_info.size();cnt++)
	{
		if (struct_info[cnt].context == str)
		{
			item = struct_info[cnt];
			return true;
		}
	}

	return false;
}

cls_compiler_symbol_table_item::cls_compiler_symbol_table_item()
{
	mem_total = 0;
	n_const = false;
	c_type = 0;
	type = type_var;
	pointer_level = 0;
	context = "";
	memory_ptr = 0;
	seg = seg_none;
}