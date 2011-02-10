#pragma once

class cls_compiler_pre_processor
{
public:
	string str_file;
	int import_len;
	int this_pre_line;

	vector<string> import_file_not_find;
	vector<string> import_file;
	vector<string> lib_file;
	string &src;

	vector<int> lines;

public:
	cls_compiler_pre_processor(string &a_file,string& a_src);
	bool get_one_import(string str_filename);
	void get_import_things();
	int error(string str);
	void get_src();
};