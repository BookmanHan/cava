#include "StdAfx.h"
#include "cls_compiler_syntex_action_table.h"

int cls_compiler_syntex_action_table::get_next(int row,int sym)
{
	if (sym>=spilt)
	{
		sym -= spilt;
		sym += ter;
	}

	return context[row][sym];
}

cls_compiler_syntex_action_table::cls_compiler_syntex_action_table(int rows,int n_split,int a_ter,int non):context(rows)
{
	spilt = n_split;
	ter = a_ter;
	context.resize(rows);
	for(int cnt=0;cnt<rows;cnt++)
	{
		context[cnt].resize(spilt+non+2,-1);
	}
}

void cls_compiler_syntex_action_table::set_move(int row,int sym,int next)
{
	if (sym>=spilt)
	{
		sym -= spilt;
		sym += ter;
	}

	context[row][sym] = next;
}

void cls_compiler_syntex_action_table::set_reduce(int row,int next)
{
	fill(context[row].begin(),context[row].begin()+ter,next);
}