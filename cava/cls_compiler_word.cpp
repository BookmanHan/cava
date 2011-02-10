#include "StdAfx.h"
#include "cls_compiler_word.h"

cls_compiler_word::cls_compiler_word(string &a_src,string str_filename):src(a_src)
{
	load_opers_from_file(str_filename);

	pos = 0;
	status = 0;
	lines = 0;
}

cls_compiler_word::operator bool()
{
	return pos < src.size();
}

bool cls_compiler_word::check_end()
{
	return pos >= src.size();
}
string cls_compiler_word::get_next(int &type)
{
	string str;
	while(true)
	{
		str = get_next(type,0);
		str_pre_get = str;

		if (trim(str) != "")
			break;
	}

	return trim(str);
}

string cls_compiler_word::get_next(int &n,int m)
{
	if (*this == false)
		return "#";

	int n_begin = pos;

	int n_cnt = 0;
	while(true)
	{
		switch(status)
		{
		case 0:

			n_cnt = check_opers();

			if(n_cnt>=0)
			{
				n = type_oper;
				pos += opers[n_cnt].size();
				return opers[n_cnt];
			}
			else if (isdigit(src[pos]))
			{
				status = 1;
			}
			else if (isalpha(src[pos]))
			{
				status = 4;
			}
			else if (src[pos] == '\'')
			{
				pos++;
				status = 3;
			}
			else if (src[pos] == '\"')
			{
				pos++;
				status = 2;
			}
			else
			{
				pos++;
				return "";
			}
			break;

		case 1://const
			if (src[pos] == 'H' || src[pos] == 'D' || src[pos] == 'B' || src[pos] == 'O')
			{
				n = type_const;
				return src.substr(n_begin,pos-n_begin+1);
			}
			else if (src[pos] == '.')
			{
				pos++;
				status = 6;
			}
			else if (isdigit(src[pos]))
			{
				pos++;
			}	
			else if (check_opers()>=0)
			{
				n = type_const;
				status = 0;
				return src.substr(n_begin,pos-n_begin);
			}
			else
			{
				status = 0;
				n = type_const;
				return  src.substr(n_begin,pos-n_begin);
			}
			break;

		case 2://string
			if (src[pos] == '\\')
			{
				char ch = src[pos + 1];
				src.erase(pos,1);
				switch(ch)
				{
				case '\\':
					src[pos] = '\\';
					break;
				case '\"':
					src[pos] = '\"';
					break;
				case '\'':
					src[pos] = '\'';
					break;
				case 'n':
					src[pos] = '\n';
					break;
				case 'r':
					src[pos] = '\r';
					break;
				case 't':
					src[pos] = '\n';
					break;
				case '0':
					src[pos] = 0;
					break;
				}
				pos++;
			}
			else if (src[pos] == '\"')
			{
				pos++;
				status = 0;
				n = type_string;
				return src.substr(n_begin,pos-n_begin);
			}
			else 
			{
				pos++;
			}
			break;
		case 3://char
			if (src[pos] == '\\')
			{
				char ch = src[pos + 1];
				src.erase(pos,1);
				switch(ch)
				{
				case '\\':
					src[pos] = '\\';
					break;
				case '\"':
					src[pos] = '\"';
					break;
				case '\'':
					src[pos] = '\'';
					break;
				case 'n':
					src[pos] = '\n';
					break;
				case 'r':
					src[pos] = '\r';
					break;
				case 't':
					src[pos] = '\n';
					break;
				case '0':
					src[pos] = 0;
					break;
				}
				pos++;
			}
			else if (src[pos] == '\'')
			{
				pos++;
				status = 0;
				n = type_char;
				return src.substr(n_begin,pos-n_begin);
			}
			else 
			{
				pos++;
			}
			break;
		case 4://id
			if (isalpha(src[pos]) || isdigit(src[pos]) || src[pos] == '_')
			{
				pos++;
			}
			else
			{
				status = 0;
				n = type_var;
				return src.substr(n_begin,pos - n_begin);
			}

			break;
		case 6:
			if (isdigit(src[pos]))
			{
				pos++;
			}	
			else if (check_opers()>=0)
			{
				n = type_const_double;
				status = 0;
				return src.substr(n_begin,pos-n_begin);
			}
			else
			{
				status = 0;
				n = type_const_double;
				return  src.substr(n_begin,pos-n_begin);
			}
			break;
		}
	}

	n = -1;
	return "";
}

void cls_compiler_word::reset()
{
	pos = 0;
	status = 0;
}

void cls_compiler_word::display(int num)
{
	cout<<"Ö÷ÒªÊ§Ð§·ûºÅ£º"<<pos<<":"<<src[pos]<<endl;
	int num_begin = pos - num;
	if (num_begin <0)
		num_begin = 0;

	int num_end = pos + num;
	if (num_end>=src.size())
	{
		num_end =src.size() - 1;
	}

	for(int cnt=num_begin;cnt<num_end;cnt++)
	{
		if (cnt == num-1)
		{
			cout<<"¡¾";
		}
		else if (cnt == num + 1)
		{
			cout<<"¡¿";
		}

		cout<<src[cnt];
	}
}

void cls_compiler_word::load_opers_from_file(string str_filename)
{
	ifstream fin;
	fin.open(str_filename.c_str());

	while(!fin.eof())
	{
		string str_read;
		getline(fin,str_read);
		if (str_read.size() == 0)
		{
			getline(fin,str_read);
			continue;
		}
		if (str_read.size() <= 3 && !isalpha(str_read[0]))
			opers.push_back(str_read);

		getline(fin,str_read);
	}

	fin.close();
}

int cls_compiler_word::check_opers()
{
	int re = -1;

	for(int cnt=0;cnt<opers.size();cnt++)
	{
		if (pos + opers[cnt].size() -1 > src.size())
			continue;


		if (src.substr(pos,opers[cnt].size()) == opers[cnt] )
		{
			if (re == -1 || opers[re].size() < opers[cnt].size())
				re = cnt;
		}
	}

	return re;
}
