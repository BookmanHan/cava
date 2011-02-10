#include "StdAfx.h"
#include "cls_compiler_syntex_item.h"

bool cls_compiler_syntex_item::copy_from(const cls_compiler_syntex_item& that)
{
	items = that.items;
	tb_items = that.tb_items;
	names = that.names;
	ptrs = that.ptrs;
	p_1 =that.p_1;
	p_2 =that.p_2;
	p_3 =that.p_3;
	p_4 =that.p_4;
	seg = that.seg;
	b_left = that.b_left;

	real_pointer_level= that.real_pointer_level;

	return true;
}

cls_compiler_syntex_item::cls_compiler_syntex_item(int a_s,int a_t,string a_str)
{
	str = a_str;
	status = a_s;
	type = a_t;
	p_1 = p_2 = p_3 = p_4 = 0;
	seg = seg_none;
	real_pointer_level = 0;
	b_left= false;
}