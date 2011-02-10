#pragma once

class cls_compiler_syntex_action_table
{
private:
	int spilt;
	int ter;
	vector<vector<int>> context;

public:
	int get_next(int row,int sym);
	cls_compiler_syntex_action_table(int rows,int n_split,int a_ter,int non);
	void set_move(int row,int sym,int next);
	void set_reduce(int row,int next);
};