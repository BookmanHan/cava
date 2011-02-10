#include "StdAfx.h"
#include "cls_yacc_kernal.h"

void cls_yacc_kernal::get_move_vct(int n_cur,ofstream& fout,cls_yacc_info& info,vector<int>& rank,set<int>& join)
{
	bool b_reduce = false;
	int order = 0;
	map<int,int> v_rank;

	for(int cnt=0;cnt<items.size();cnt++)
	{
		if (items[cnt].right.size() == items[cnt].pos)
		{
			set<int>::iterator itor = info.follow[items[cnt].left].begin();
			while(itor != info.follow[items[cnt].left].end())
			{
				if (*itor == -1)
				{
					itor++;
					continue;
				}
				if (items[cnt].oper != -1)
					v_rank[*itor] = rank[items[cnt].oper];

				fout<<n_cur<<endl<<*itor<<endl<<(1000 + items[cnt].order)<<endl;
				itor++;
			}
		}
	}

	int cnt = 0;
	for(cnt = 0;cnt < moves.size();cnt++)
	{
		if (moves[cnt].item <= cls_yacc_product_item::const_spilt)
		{
			map<int,int>::iterator map_itor = v_rank.find(moves[cnt].item);

			if (map_itor != v_rank.end() && map_itor->second > rank[moves[cnt].item])
			{
				continue;
			}
			else if (map_itor != v_rank.end() && map_itor->second == rank[moves[cnt].item])
			{
				if (join.find(moves[cnt].item) != join.end())
				{
					fout<<moves[cnt].pre<<endl<<moves[cnt].item<<endl<<moves[cnt].cur<<endl;
				}
				else
				{
					continue;
				}
			}
			else
			{
				fout<<moves[cnt].pre<<endl<<moves[cnt].item<<endl<<moves[cnt].cur<<endl;
			}
		}
		else
		{
			fout<<moves[cnt].pre<<endl<<moves[cnt].item<<endl<<moves[cnt].cur<<endl;
		}
	}
}

 cls_yacc_kernal::cls_yacc_kernal()
{

}

bool  cls_yacc_kernal::operator == (const cls_yacc_kernal& that) const
{
	if (that.items.size() != this->items.size())
		return false;

	for(int cnt_i=0;cnt_i<this->items.size();cnt_i++)
	{
		bool b_get = false;
		for(int cnt_j=0;cnt_j<that.items.size();cnt_j++)
		{
			if (this->items[cnt_i] == that.items[cnt_j])
			{
				b_get = true;
				break;
			}
		}

		if (b_get == false)
			return false;
	}

	return true;
}

void  cls_yacc_kernal::move_next_step(vector<cls_yacc_kernal>& kernals,vector<cls_yacc_product>& src,int n_cur,int &n_total)
{
	bool *b_used = new bool[items.size()];
	for(int cnt=0;cnt<items.size();cnt++)
	{
		*(b_used + cnt) = false;
	}

	for(int cnt=0;cnt<items.size();cnt++)
	{
		if (items[cnt].right.size() == items[cnt].pos)
			continue;
		if (*(b_used+cnt) == true)
			continue;

		b_used[cnt] = true;
		cls_yacc_kernal new_kernal;
		cls_yacc_kernal_item new_item = items[cnt];
		new_item.pos++;
		new_kernal.items.push_back(new_item);

		cls_yacc_product_item item = items[cnt].right[items[cnt].pos];
		for(int pos=cnt+1;pos<items.size();pos++)
		{
			if (items[pos].right.size() == items[pos].pos)
				continue;

			if (items[pos].right[items[pos].pos] == item)
			{
				*(b_used + pos) = true;
				cls_yacc_kernal_item n_item = items[pos];
				n_item.pos++;
				new_kernal.items.push_back(n_item);
			}
		}

		new_kernal.set_closure(src);
		bool b_found = false;
		int cnt_c=0;
		for(;cnt_c<n_total;cnt_c++)
		{
			if (kernals[cnt_c] == new_kernal)
			{
				b_found = true;
				break;
			}
		}

		if (b_found == false)
		{
			cls_yacc_move move;
			move.pre = n_cur;
			move.cur = n_total;
			move.item = item.item;
			moves.push_back(move);
			kernals[n_total] = new_kernal;
			n_total++;
		}
		else
		{
			cls_yacc_move move;
			move.pre = n_cur;
			move.cur = cnt_c;
			move.item = item.item;
			moves.push_back(move);
		}
	}

	delete b_used;
}

void  cls_yacc_kernal::set_closure(const vector<cls_yacc_product>& src)
{
	int pos_last = 0;
	bool b_change = true;
	while(b_change)
	{
		b_change = false;
		int pos_last_r = items.size();

		for(int cnt_i=pos_last;cnt_i<pos_last_r;cnt_i++)
		{
			if (items[cnt_i].pos == items[cnt_i].right.size())
				continue;

			cls_yacc_product_item cur_item = items[cnt_i].right[items[cnt_i].pos];
			if (cur_item)
			{
				for(int cnt_j=0;cnt_j<src.size();cnt_j++)
				{
					if (src[cnt_j].left.item == cur_item.item)
					{
						cls_yacc_kernal_item k_item = src[cnt_j];
						k_item.pos = 0;

						if (find(items.begin(),items.end(),k_item) == items.end())
						{
							items.push_back(k_item);
							b_change = true;
						}
					}
				}
			}
		}

		pos_last = pos_last_r;
	}
}