#pragma once
#include "stdafx.h"

class cls_compiler
{
private:
	string src;
	cls_compiler_pre_processor cpp;
	cls_compiler_syntex cs;

public:
	cls_compiler(string str_src);
	bool save_mid_code_to_file(string str_filename);
};
