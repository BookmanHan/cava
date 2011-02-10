#include "StdAfx.h"
#include "cls_yacc_product.h"

cls_yacc_product::cls_yacc_product()
{
	oper = -1;
}

cls_yacc_product::cls_yacc_product(string a_exp,cls_yacc_info* a_info,int a_pos):info(a_info)
{
	oper = -1;
	order = a_pos;
	str_exp = a_exp;
	analyze_exp();
}

void cls_yacc_product::analyze_exp()
{
	int status = 0;
	bool b_do_left = false;
	string str_get;

	for(int cnt=0;cnt<str_exp.size();cnt++)
	{
		switch(str_exp[cnt])
		{
		case '$':
			if (status != 2)
			{
				status = 2;
			}
			else
			{
				right.push_back(cls_yacc_product_item(info->get_str_num_ter(str_get)));
				str_get.clear();

				oper = *right.rbegin();

				status = 0;
			}

			break;

		case '#':
			if (status != 1)
			{
				status = 1;
			}
			else
			{
				if (b_do_left == false)
				{
					left = cls_yacc_product_item(info->get_str_num(str_get));
					str_get.clear();
				}
				else
				{
					right.push_back(cls_yacc_product_item(info->get_str_num(str_get)));
					str_get.clear();
				}

				status  = 0;
			}
			break;

		case '@':
			b_do_left = true;
			break;

		default:
			str_get += str_exp[cnt];
			break;
		}
	}
}

