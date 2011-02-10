#include "stdafx.h"

//begin from here...

int _tmain(int argc, _TCHAR* argv[])
{
	string str_compile_file = str_dir + "do.txt";
	cls_compiler compiler_core(string("\"") + str_compile_file + "\"");
	compiler_core.save_mid_code_to_file(str_dir + "mid_code.out");

	system("pause");

	return 0;
}

