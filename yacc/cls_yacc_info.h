#pragma once

class cls_yacc_info
{
public:
	map<string,int> map_non_name_id;
	map<string,int> map_ter_name_id;
	map<int,set<int>> follow;
	map<int,set<int>> first;

private:
	int max_non_id;
	int max_ter_id;

public:
	cls_yacc_info();
	int get_str_num_ter(string str);
	int get_str_num(string str);
};