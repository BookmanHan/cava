#include "StdAfx.h"
#include "cls_compiler_pre_processor.h"

cls_compiler_pre_processor::cls_compiler_pre_processor(string &a_file,string& a_src):str_file(a_file),src(a_src)
{
	import_file.push_back(str_file);
	import_file_not_find.push_back(str_file);

	get_import_things();
	get_src();
}

bool cls_compiler_pre_processor::get_one_import(string str_filename)
{
	ifstream fin(str_filename.substr(1,str_filename.length() - 2).c_str());
	if (!fin.is_open())
	{
		return false;
	}

	string str,str_key,str_things;

	while(!fin.eof())
	{
		getline(fin,str);
		stringstream ss(str);
		ss>>str_key;

		if (str_key == "import")
		{
			ss>>str_things;

			if (find(import_file.begin(),import_file.end(),(str_things)) == import_file.end())
			{
				import_file.push_back(str_things);
			}
			if (find(import_file_not_find.begin(),import_file_not_find.end(),(str_things)) == import_file_not_find.end())
			{
				import_file_not_find.push_back(str_things);
			}
		}
		else if (str_key == "load_lib")
		{
			ss>>str_things;
			lib_file.push_back(str_things);
		}
		else
		{
			break;
		}
	}

	fin.close();

	return true;
}

void cls_compiler_pre_processor::get_import_things()
{
	while(import_file_not_find.size() != 0)
	{
		vector<string> now = import_file_not_find;
		import_file_not_find.clear();

		vector<string>::iterator itor = now.begin();
		while(itor != now.end())
		{
			get_one_import(*itor);
			itor++;
		}
	}
}

int cls_compiler_pre_processor::error(string str)
{
	cout<<str<<endl;

	return 0;
}

void cls_compiler_pre_processor::get_src()
{
	string str;
	vector<string>::reverse_iterator itor = import_file.rbegin();
	while(itor != import_file.rend())
	{
		ifstream fin(itor->substr(1,itor->length()-2).c_str());

		if (!fin.is_open())
		{
			error((*itor) + "：这个import文件无法打开！");
		}

		bool reduce_it = true;
		int total_pre_line = 0;

		if (*itor != str_file)
		{
			while(!fin.eof())
			{
				string str,str_key;
				getline(fin,str);

				if (reduce_it == true)
				{
					stringstream ss(str);
					ss>>str_key;

					if (str_key == "import")
					{
					}
					else if (str_key == "load_lib")
					{
					}
					else
					{
						reduce_it = false;
						src += str;
					}
				}
				else
				{
					src += str;
				}
			}
		}
		else
		{
			while(!fin.eof())
			{
				string str,str_key;
				getline(fin,str);

				if (reduce_it == true)
				{
					stringstream ss(str);
					ss>>str_key;

					if (str_key == "import")
					{
						total_pre_line++;
						lines.push_back(0);
					}
					else if (str_key == "load_lib")
					{
						total_pre_line++;
						lines.push_back(0);
					}
					else
					{
						reduce_it = false;
						src += str;
						lines.push_back(src.size());
					}
				}
				else
				{
					src += str;
					lines.push_back(src.size());
				}
			}
		}

		this_pre_line = total_pre_line;
		import_len = src.size();
		itor ++;
	}
}