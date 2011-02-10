#include "StdAfx.h"
#include "cls_compiler.h"

cls_compiler::cls_compiler(string str_src):cpp(str_src,src),cs(src,str_dir + "in.txt.opers",str_dir +"in.txt.product",str_dir +"in.txt.action",cpp.lines,cpp.this_pre_line)
{
	if (cs.check_success == true)
	{
		cout<<"成功编译！"<<endl;

		cout<<"结果："<<endl;
		for(int cnt=0;cnt<cs.des.size();cnt++)
		{
			cout<<cnt<<":\t";
			if (cs.des[cnt].oper == command_tag)
			{
				cout<<cs.des[cnt].name<<":"<<endl;
			}
			else if (cs.des[cnt].oper == command_call)
			{
				cout<<cs.des[cnt].oper<<"\t";
				cout<<cs.des[cnt].name<<"\t";
				cout<<cs.des[cnt].seg_re<<":"<<cs.des[cnt].re<<","<<cs.des[cnt].ct_re;
				cout<<endl;
			}
			else
			{
				cout<<cs.des[cnt].oper<<"\t";
				cout<<cs.des[cnt].seg1<<":"<<cs.des[cnt].ptr1<<","<<cs.des[cnt].ct1;
				cout<<"\t";
				cout<<cs.des[cnt].seg2<<":"<<cs.des[cnt].ptr2<<","<<cs.des[cnt].ct2;
				cout<<"\t";
				cout<<cs.des[cnt].seg_re<<":"<<cs.des[cnt].re<<","<<cs.des[cnt].ct_re;
				cout<<endl;
			}
		}
	}
	else
	{
		cout<<"编译失败！"<<endl;
	}
}

bool cls_compiler::save_mid_code_to_file(string str_filename)
{
	map<string,int> map_tag_ins;
	for(int cnt=0;cnt<cs.des.size();cnt++)
	{
		if (cs.des[cnt].oper == command_tag)
		{
			map_tag_ins.insert(make_pair(cs.des[cnt].name,cnt));
		}
	}

	fstream fout(str_filename.c_str(),ios::binary | ios::out);

	fout<<cs.cstm.struct_table.table_items.size()<<endl;
	for(int cnt=0;cnt<cs.cstm.struct_table.table_items.size();cnt++)
	{
		fout<<cs.cstm.struct_table.table_items[cnt].c_type<<endl;
		fout<<cs.cstm.get_mem_port(cs.cstm.struct_table.table_items[cnt])<<endl;
	}

	for(int cnt=0;cnt<cs.des.size();cnt++)
	{
		if (cs.des[cnt].oper == command_call)
		{
			fout<<cs.des[cnt].oper<<endl;
			fout<<cs.des[cnt].ptr1<<endl;
			fout<<cs.des[cnt].ct1<<endl;
			fout<<cs.des[cnt].seg1<<endl;
			fout<<cs.des[cnt].ptr1<<endl;
			fout<<cs.des[cnt].ct1<<endl;
			fout<<cs.des[cnt].seg1<<endl;
			fout<<map_tag_ins[cs.des[cnt].name]<<endl;
			fout<<cs.des[cnt].ct_re<<endl;
			fout<<cs.des[cnt].seg_re<<endl;
		}
		else
		{
			fout<<cs.des[cnt].oper<<endl;
			fout<<cs.des[cnt].ptr1<<endl;
			fout<<cs.des[cnt].ct1<<endl;
			fout<<cs.des[cnt].seg1<<endl;
			fout<<cs.des[cnt].ptr1<<endl;
			fout<<cs.des[cnt].ct1<<endl;
			fout<<cs.des[cnt].seg1<<endl;
			fout<<cs.des[cnt].re<<endl;
			fout<<cs.des[cnt].ct_re<<endl;
			fout<<cs.des[cnt].seg_re<<endl;
		}
	}

	fout.close();

	return true;
}