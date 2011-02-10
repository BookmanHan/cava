#pragma once
//
//extern static const int ct_null;
////这里的值和类型转换函数fn_type_trans有关！；
//extern static const int type_struct ;
//extern static const int type_var ;
//extern static const int type_string ;
//extern static const int type_char ;
//extern static const int type_const;
//extern static const int type_oper;
//extern static const int type_none ;
//extern static const int type_const_double ;
//
//extern static const int ctype_char ;
//extern static const int ctype_short ;
//extern static const int ctype_int ;
//extern static const int ctype_unsigned_char ;
//extern static const int ctype_unsigned_short ;
//extern static const int ctype_unsigned_int ;
//extern static const int ctype_double ;
//extern static const int ctype_pointer ;
//extern static const int ctype_pointer_random ;
//extern static const int ctype_void ;
//
//extern static const int seg_none ;
//extern static const int seg_const ;
//extern static const int seg_stack ;
//extern static const int seg_heap ;
//
//extern static const int command_nop ;
//extern static const int command_set ;
////把ptr1的值给re；
//extern static const int command_tag ;
////标签，名字在name中
//extern static const int command_get ;
////从ptr1指向的地址处取出内容给re
//extern static const int command_add ;
//extern static const int command_minus ;
//extern static const int command_mutiply ;
//extern static const int command_divide ;
//extern static const int command_mod ;
//extern static const int command_or ;
//extern static const int command_and ;
//extern static const int command_xor ;
//extern static const int command_left ;
//extern static const int command_right ;
//extern static const int command_roleft ;
//extern static const int command_roright ;
//extern static const int command_larger ;
//extern static const int command_larger_eql ;
//extern static const int command_smaller ;
//extern static const int command_smaller_equ ;
//extern static const int command_equ ;
//extern static const int command_non_equ ;
////把ptr1与ptr2的值相XX结果放到re里面去。逻辑运算正确为1，错误为0
//extern static const int command_real_set ;
////把p_1中的值给re，主要是用于指针初始化！
//extern static const int command_reverse ;
////把ptr1种的值取反，然后给re
//extern static const int command_not ;
////把ptr1种的值取反，然后给re
//extern static const int command_jump ;
////通过判断ptr1的值，如果是正确的(>1)则跳到ptr2的地址，否则跳到re的地址。
//extern static const int command_abs_jump ;
////绝对跳转到re的地址。
//extern static const int command_inc ;
////把re中的值++；
//extern static const int command_dec ;
////把re中的值--；
//extern static const int command_push ;
////把re的值push。
//extern static const int command_pop ;
////把re的值pop
//extern static const int command_call ;
////调用函数name，把返回值放到re中，
//extern static const int command_pre_call ;
////修改esp的值，修改量在re中。
//extern static const int command_after_call ;
////修改esp的值，修改量在re中。ptr2为对方存放结果地址(就是esp处！)，ptr1为自己存放结果的地址！
//extern static const int command_return ;
////返回函数值。
//extern static const int command_get_return ;
////没有实际用途，可以不考虑。
//extern static const int command_set_stack_pointer ;
////没有实际用途，可以不考虑。
//extern static const int command_neg ;
////给元素变为负值。
//extern static const int command_new ;
////ptr1为指针层数！ptr2为申请数目，注意ct2为神奇类型，re为存放返回结果的地址。
//extern static const int command_delete ;
////ptr1为指针层数，re为释放地址的存放的地址！！！功能为减少指针计数，如果计数为1则删除！
////如果delete的是一个指针类型的内存，得在把指针类型内存的析构后，把指向的位置上的计数-1.
////如果指向的是栈空间，则缓冲计数不变，然后直到找到为止！
//extern static const int command_new_add_ref ;
////ptr1为指针层数，re为增加计数的存放的地址！！！功能为增加指针计数。如果指向的是栈空间，那么继续向下寻找堆空间。
//extern static const int command_break ;
//extern static const int command_continue ;
//extern static const int command_get_pointer ;
////把ptr1的地址变为绝对地址！放到re中。stack上的要加上esp！
//extern static const int command_for ;
//extern static const int command_while ; 
//extern static const int command_for_re ; 
//extern static const int command_while_re ;
////以上四个，只是为了break和continue，没有实际的意义和价值！前两个等同于jump，后面等同于abs_jump;
//extern static const int command_delete_random ;
////ptr1为指针层数，re为释放地址的存放的地址！！！功能为减少指针计数，如果计数为1则删除！
////如果delete的是一个指针类型的内存，得在把指针类型内存的析构后，把指向的位置上的计数-1.
////如果指向的是栈空间，则缓冲计数不变，然后直到找到为止！
//extern static const int command_new_add_ref_random ;
////增加random类型指针的计数！和smart指针原理一样。
//extern static const int command_switch_re ;
//extern static const int command_switch ; // 实际上为command_abs_jump
////没有实际意义，只是为了break和continue。

static const int ct_null = -1;
//这里的值和类型转换函数fn_type_trans有关！；
static const int type_struct = 1;
static const int type_var = 2;
static const int type_string = 3;
static const int type_char = 4;
static const int type_const = 5;
static const int type_oper = 6;
static const int type_none = 7;
static const int type_const_double = 8;

static const int ctype_char = 1;
static const int ctype_short = 2;
static const int ctype_int = 3;
static const int ctype_unsigned_char = 4;
static const int ctype_unsigned_short = 5;
static const int ctype_unsigned_int = 6;
static const int ctype_double = 7;
static const int ctype_pointer = 8;
static const int ctype_pointer_random = 9;
static const int ctype_void = 10;

static const int seg_none = 0;
static const int seg_const = 1;
static const int seg_stack = 2;
static const int seg_heap = 3;



const  int command_nop = 0;
const  int command_set = 1;
//把ptr1的值给re；
const  int command_tag = 2;
//标签，名字在name中
const  int command_get = 3;
//从ptr1指向的地址处取出内容给re
const  int command_add = 4;
const  int command_minus = 5;
const  int command_mutiply = 6;
const  int command_divide = 7;
const  int command_mod = 8;
const  int command_or = 9;
const  int command_and = 10;
const  int command_xor = 11;
const  int command_left = 12;
const  int command_right = 13;
const  int command_roleft = 14;
const  int command_roright = 15;
const  int command_larger = 16;
const  int command_larger_eql = 17;
const  int command_smaller = 18;
const  int command_smaller_equ = 19;
const  int command_equ = 20;
const  int command_non_equ = 21;
//把ptr1与ptr2的值相XX结果放到re里面去。逻辑运算正确为1，错误为0
const  int command_real_set = 22;
//把p_1中的值给re，主要是用于指针初始化！
const  int command_reverse = 23;
//把ptr1种的值取反，然后给re
const  int command_not = 24;
//把ptr1种的值取反，然后给re
const  int command_jump = 25;
//通过判断ptr1的值，如果是正确的(>1)则跳到ptr2的地址，否则跳到re的地址。
const  int command_abs_jump = 26;
//绝对跳转到re的地址。
const  int command_inc = 27;
//把re中的值++；
const  int command_dec = 28;
//把re中的值--；
const  int command_push = 30;
//把re的值push。
const  int command_pop = 31;
//把re的值pop
const  int command_call = 32;
//调用函数name，把返回值放到re中，
const  int command_pre_call = 33;
//修改esp的值，修改量在re中。
const  int command_after_call = 34;
//修改esp的值，修改量在re中。ptr2为对方存放结果地址(就是esp处！)，ptr1为自己存放结果的地址！
const  int command_return = 35;
//返回函数值。
const  int command_get_return = 36;
//没有实际用途，可以不考虑。
const  int command_set_stack_pointer = 37;
//没有实际用途，可以不考虑。
const  int command_neg = 38;
//给元素变为负值。
const  int command_new = 39;
//ptr1为指针层数！ptr2为申请数目，注意ct2为神奇类型，re为存放返回结果的地址。
const  int command_delete = 40;
//ptr1为指针层数，re为释放地址的存放的地址！！！功能为减少指针计数，如果计数为1则删除！
//如果delete的是一个指针类型的内存，得在把指针类型内存的析构后，把指向的位置上的计数-1.
//如果指向的是栈空间，则缓冲计数不变，然后直到找到为止！
const  int command_new_add_ref = 41;
//ptr1为指针层数，re为增加计数的存放的地址！！！功能为增加指针计数。如果指向的是栈空间，那么继续向下寻找堆空间。
const  int command_break = 42;
const  int command_continue = 43;
const  int command_get_pointer = 44;
//把ptr1的地址变为绝对地址！放到re中。stack上的要加上esp！
const  int command_for = 45;
const  int command_while = 46; 
const  int command_for_re = 47; 
const  int command_while_re = 48;
//以上四个，只是为了break和continue，没有实际的意义和价值！前两个等同于jump，后面等同于abs_jump;
const  int command_delete_random = 49;
//ptr1为指针层数，re为释放地址的存放的地址！！！功能为减少指针计数，如果计数为1则删除！
//如果delete的是一个指针类型的内存，得在把指针类型内存的析构后，把指向的位置上的计数-1.
//如果指向的是栈空间，则缓冲计数不变，然后直到找到为止！
const  int command_new_add_ref_random = 50;
//增加random类型指针的计数！和smart指针原理一样。
const  int command_switch_re = 51;
const  int command_switch = 52; // 实际上为command_abs_jump
//没有实际意义，只是为了break和continue。