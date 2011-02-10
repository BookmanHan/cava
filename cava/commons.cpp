#include "stdafx.h"

string fn_get_random_name(string pre,int num)
{
	string str = "rn_"+pre;
	for(int cnt=0;cnt<num;cnt++)
	{
		char n = rand()%10 + '0';
		str += n;
	}

	return str;
}

string& trim(string &str)
{

	int i,j,start,end;

	//left_trim
	for (i=0; (str[i]!=0 && str[i]<=32);)
	{
		i++;
	}

	start=i;

	//right_trim
	for(i=0,j=0; str[i]!=0; i++)
	{
		j = ((str[i]<=32)? j+1 : 0);
	}

	end=i-j;

	str = str.substr(start,end-start);

	return str;
}

bool fn_type_trans(int c_src,int c_des,int p_sec,int p_des)
{
	if (p_sec != 0 && p_des == 0 && c_des == ctype_int)
	{
		return true;
	}

	if (p_sec != p_des)
	{
		return false;
	}

	if (c_src == c_des)
	{
		return true;
	}

	if (p_sec == 0)
	{
		if (c_src == ctype_pointer && c_des == ctype_pointer_random)
		{
			return true;
		}
		else if  (c_des == ctype_pointer && c_src == ctype_pointer_random)
		{
			return true;
		}
		else if (c_src <= ctype_double && c_des <= ctype_double)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (p_sec != 0 && p_des == 0 && c_des == ctype_int)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
