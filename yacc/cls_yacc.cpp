#include "StdAfx.h"
#include "cls_yacc.h"

void cls_yacc::load_join_from_file(string str_filename)
{
	ifstream fin(str_filename.c_str());

	while(!fin.eof())
	{
		string str_get;
		getline(fin,str_get);
		join_right.insert(info.map_ter_name_id[str_get]);
	}

	fin.close();
}

bool cls_yacc::check_product_empty(int n)
{
	for(int cnt=0;cnt<src.size();cnt++)
	{
		if (src[cnt].left.item == n && src[cnt].right.size() == 0)
			return  true;
	}

	return false;
}

bool cls_yacc::get_first_set_r()
{
	map<int,set<int>> pre = info.first;
	map<string,int>::iterator itor = info.map_non_name_id.begin();

	while(itor != info.map_non_name_id.end())
	{
		for(int cnt=0;cnt<src.size();cnt++)
		{
			if (src[cnt].left.item == itor->second)
			{
				int cnt_k=0;
				for(cnt_k=0;cnt_k<src[cnt].right.size();cnt_k++)
				{
					if (src[cnt].right[cnt_k].item >= cls_yacc_product_item::const_spilt)
					{
						int cur = src[cnt].right[cnt_k];

						set<int>::iterator itor_set = info.first[cur].begin();
						while(itor_set != info.first[cur].end())
						{
							info.first[itor->second].insert(*itor_set);
							itor_set++;
						}

						if (!check_product_empty(src[cnt].right[cnt_k]))
						{
							break; 
						}
					}
					else
					{
						info.first[itor->second].insert(src[cnt].right[cnt_k]);
						break;
					}
				}

				if (cnt_k == src[cnt].right.size())
				{
					info.first[itor->second].insert(-1);
				}
			}
		}

		itor++;
	}

	return pre != info.first;
}

void cls_yacc::get_first_set()
{
	while(get_first_set_r())
		;
}

bool cls_yacc::get_follow_set_r()
{	
	map<int,set<int>> pre = info.follow;

	for(int cnt=0;cnt<src.size();cnt++)
	{
		if (src[cnt].right.size() <= 1)
			continue;

		for(int k=0;k<src[cnt].right.size()-1;k++)
		{
			if (src[cnt].right[k])
			{
				int t = k;
				do 
				{
					t++;
					if (src[cnt].right[t])
					{
						set<int>::iterator itor_set = info.first[src[cnt].right[t]].begin();
						while(itor_set != info.first[src[cnt].right[t]].end())
						{
							info.follow[src[cnt].right[k]].insert(*itor_set);
							itor_set++;
						}
					}
					else
					{
						info.follow[src[cnt].right[k]].insert(src[cnt].right[t]);
					}

				} while (t<src[cnt].right.size()-1 && src[cnt].right[t] && check_product_empty(src[cnt].right[t]));

				if (t == src[cnt].right.size()-1)
				{
					set<int>::iterator itor = info.follow[src[cnt].left].begin();
					while(itor != info.follow[src[cnt].left].end())
					{
						info.follow[src[cnt].right[k]].insert(*itor);
						itor++;
					}
				}
			}
		}
	}

	for(int cnt=0;cnt<src.size();cnt++)
	{
		if (src[cnt].right.size() == 0)
			continue;

		if (src[cnt].right.back())
		{
			set<int>::iterator itor = info.follow[src[cnt].left].begin();
			while(itor != info.follow[src[cnt].left].end())
			{
				info.follow[src[cnt].right.back()].insert(*itor);
				itor++;
			}
		}
	}

	return pre != info.follow;
}

void cls_yacc::get_follow_set()
{
	info.follow[src[0].left].insert(info.map_ter_name_id["?"]);
	while(get_follow_set_r())
		;
}

void cls_yacc::display_info(string str_info)
{
	ofstream fout;
	fout.open((str_info + ".opers").c_str());

	map<string,int>::iterator itor = info.map_ter_name_id.begin();
	while(itor != info.map_ter_name_id.end())
	{
		fout<<itor->first<<endl<<itor->second<<endl;
		itor++;
	}

	fout.close();

	fout.open((str_info + ".product").c_str());

	for(int cnt=0;cnt<src.size();cnt++)
	{
		fout<<src[cnt].str_exp<<endl<<src[cnt].left.item<<endl<<src[cnt].right.size()<<endl;
	}

	fout.close();
}

cls_yacc::cls_yacc(string str_product,string str_rank,string str_join):kernals(2000),rank(200)
{
	cls_yacc_kernal yk;
	load_product_from_file(str_product);
	load_rank_from_file(str_rank);
	load_join_from_file(str_join);
	get_first_set();
	get_follow_set();
	display_info(str_product);
	analyze_slr();

	str_product += ".action";
	save_to_file(str_product);
}

void cls_yacc::load_rank_from_file(string str_filename)
{
	ifstream fin;
	fin.open(str_filename.c_str());

	int cnt_total = 1000;
	while(!fin.eof())
	{
		string str_read;
		getline(fin,str_read);

		if (str_read == "@")
		{
			cnt_total--;
		}
		else
		{
			rank[info.map_ter_name_id[str_read]] = cnt_total;
		}
	}

	fin.close();
}

void cls_yacc::load_product_from_file(string str_filename)
{
	ifstream fin;
	fin.open(str_filename.c_str());

	int n_total = 0;
	while(!fin.eof())
	{
		string str_read;
		string str_read_next;
		getline(fin,str_read);
		src.push_back(cls_yacc_product(str_read,&info,n_total++));
	}

	fin.close();
}

void cls_yacc::analyze_slr()
{
	cls_yacc_kernal_item org_item(src[0]);
	cls_yacc_kernal k;

	int n_last = 0;
	n_total = 1;
	kernals[0].items.push_back(org_item);
	kernals[0].set_closure(src);
	for(int cnt=0;cnt<n_total;cnt++)
	{
		cout<<cnt<<endl;
		kernals[cnt].move_next_step(kernals,src,cnt,n_total);
	}
}

void cls_yacc::save_to_file(string str_filename)
{
	ofstream fout;
	fout.open(str_filename.c_str());

	for(int cnt=0;cnt<n_total;cnt++)
	{
		kernals[cnt].get_move_vct(cnt,fout,info,rank,join_right);
	}

	fout.close();
}