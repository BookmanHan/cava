// yacc.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	cls_yacc yacc(str_dir + "in.txt",str_dir + "rank.txt",str_dir + "join.txt");
	cout<<"已完成！"<<endl;

	return 0;
}

