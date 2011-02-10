#pragma once
#include "stdafx.h"

class cls_compiler_command
{
public:
	string name;
	int oper;
	int ptr1;
	int ptr2;
	int seg1;
	int seg2;
	int ct1;
	int ct2;
	int re;
	int seg_re;
	int ct_re;

public:
	cls_compiler_command();
};
