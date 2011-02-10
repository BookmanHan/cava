// cava.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

/*
缺点：
1、短路表达式。
2、*的优先级问题与结合性问题！
*/
int _tmain(int argc, _TCHAR* argv[])
{
	string str_compile_file = str_dir + "do.txt";
	cls_compiler compiler_core(string("\"") + str_compile_file + "\"");
	compiler_core.save_mid_code_to_file(str_dir + "mid_code.out");

	system("pause");

	return 0;
}

