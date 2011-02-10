#include "StdAfx.h"
#include "cls_yacc_info.h"

cls_yacc_info::cls_yacc_info()
{
	max_non_id = 0;
	max_ter_id = 0;
}

int cls_yacc_info::get_str_num_ter(string str)
{
	if (map_ter_name_id.find(str) != map_ter_name_id.end())
	{
		return map_ter_name_id[str];
	}
	else
	{
		map_ter_name_id.insert(make_pair(str,max_ter_id));
		return max_ter_id++;
	}
}

int cls_yacc_info::get_str_num(string str)
{
	if (map_non_name_id.find(str) != map_non_name_id.end())
	{
		return map_non_name_id[str];
	}
	else
	{
		map_non_name_id.insert(make_pair(str,t_const_spilt +max_non_id));
		return t_const_spilt + max_non_id++;
	}
}