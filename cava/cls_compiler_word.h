#pragma once
#include "stdafx.h"

class cls_compiler_word
{
private:
	//这里和具体语言有关，请修改！
	vector<string> opers;
	int status;

public:
	string& src;
	int pos;
	string str_pre_get;
	int lines ;

public:
	void reset();
	void display(int num);
	
private:
	void load_opers_from_file(string str_filename);
	int check_opers();

public:
	cls_compiler_word(string &a_src,string str_filename);
	operator bool();
	bool check_end();
	string get_next(int &type);
	string get_next(int &n,int m);

};

