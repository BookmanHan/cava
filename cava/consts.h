#pragma once
static const int ct_null = -1;
//�����ֵ������ת������fn_type_trans�йأ���
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
//��ptr1ָ���ֵ��re��ַָ��ĵ�ַ�
const  int command_tag = 2;
//��ǩ��������name��
const  int command_get = 3;
//��ptr1ָ��ĵ�ַ��ȡ�����ݸ�re
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
//��ptr1��ptr2��ֵ��XX����ŵ�re����ȥ���߼�������ȷΪ1������Ϊ0
const  int command_real_set = 22;
//��p_1�е�ֵ��re����Ҫ������ָ���ʼ����
const  int command_reverse = 23;
//��ptr1�ֵ�ֵȡ����Ȼ���re
const  int command_not = 24;
//��ptr1�ֵ�ֵȡ����Ȼ���re
const  int command_jump = 25;
//ͨ���ж�ptr1��ֵ���������ȷ��(>1)������ptr2�ĵ�ַ����������re�ĵ�ַ��
const  int command_abs_jump = 26;
//������ת��re�ĵ�ַ��
const  int command_inc = 27;
//��re�е�ֵ++��
const  int command_dec = 28;
//��re�е�ֵ--��
const  int command_push = 30;
//��re��ֵpush��
const  int command_pop = 31;
//��re��ֵpop
const  int command_call = 32;
//���ú���name���ѷ���ֵ�ŵ�re�У�
const  int command_pre_call = 33;
//�޸�esp��ֵ���޸�����re�С�
const  int command_after_call = 34;
//�޸�esp��ֵ���޸�����re�С�ptr2Ϊ�Է���Ž����ַ(����esp����)��ptr1Ϊ�Լ���Ž���ĵ�ַ��
const  int command_return = 35;
//���غ���ֵ��
const  int command_get_return = 36;
//û��ʵ����;�����Բ����ǡ�
const  int command_set_stack_pointer = 37;
//û��ʵ����;�����Բ����ǡ�
const  int command_neg = 38;
//��Ԫ�ر�Ϊ��ֵ��
const  int command_new = 39;
//ptr1Ϊָ�������ptr2Ϊ������Ŀ��ע��ct2Ϊ�������ͣ�reΪ��ŷ��ؽ���ĵ�ַ��
const  int command_delete = 40;
//ptr1Ϊָ�������reΪ�ͷŵ�ַ�Ĵ�ŵĵ�ַ����������Ϊ����ָ��������������Ϊ1��ɾ����
//���delete����һ��ָ�����͵��ڴ棬���ڰ�ָ�������ڴ�������󣬰�ָ���λ���ϵļ���-1.
//���ָ�����ջ�ռ䣬�򻺳�������䣬Ȼ��ֱ���ҵ�Ϊֹ��
const  int command_new_add_ref = 41;
//ptr1Ϊָ�������reΪ���Ӽ����Ĵ�ŵĵ�ַ����������Ϊ����ָ����������ָ�����ջ�ռ䣬��ô��������Ѱ�Ҷѿռ䡣
const  int command_break = 42;
const  int command_continue = 43;
const  int command_get_pointer = 44;
//��ptr1�ĵ�ַ��Ϊ���Ե�ַ���ŵ�re�С�stack�ϵ�Ҫ����esp��
const  int command_for = 45;
const  int command_while = 46; 
const  int command_for_re = 47; 
const  int command_while_re = 48;
//�����ĸ���ֻ��Ϊ��break��continue��û��ʵ�ʵ�����ͼ�ֵ��ǰ������ͬ��jump�������ͬ��abs_jump;
const  int command_delete_random = 49;
//ptr1Ϊָ�������reΪ�ͷŵ�ַ�Ĵ�ŵĵ�ַ����������Ϊ����ָ��������������Ϊ1��ɾ����
//���delete����һ��ָ�����͵��ڴ棬���ڰ�ָ�������ڴ�������󣬰�ָ���λ���ϵļ���-1.
//���ָ�����ջ�ռ䣬�򻺳�������䣬Ȼ��ֱ���ҵ�Ϊֹ��
const  int command_new_add_ref_random = 50;
//����random����ָ��ļ�������smartָ��ԭ��һ����
const  int command_switch_re = 51;
const  int command_switch = 52; // ʵ����Ϊcommand_abs_jump
//û��ʵ�����壬ֻ��Ϊ��break��continue��
const  int command_pointer_set = 53;
//��ptr1ָ���ֵ����reָ���ֵ��Ϊ��ַ�ĵ�Ԫ��