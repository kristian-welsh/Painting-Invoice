	.file	"program.c"
	.stabs	"c:/users/kristian welsh/dropbox/university/year 0/foundation programming/coursework/assignment 1/program/program.c",100,0,2,Ltext0
	.text
Ltext0:
	.stabs	"gcc2_compiled.",60,0,0,0
	.stabs	"int:t(0,1)=r(0,1);-2147483648;2147483647;",128,0,0,0
	.stabs	"char:t(0,2)=r(0,2);0;127;",128,0,0,0
	.stabs	"long int:t(0,3)=r(0,3);-2147483648;2147483647;",128,0,0,0
	.stabs	"unsigned int:t(0,4)=r(0,4);0;-1;",128,0,0,0
	.stabs	"long unsigned int:t(0,5)=r(0,5);0;-1;",128,0,0,0
	.stabs	"long long int:t(0,6)=r(0,6);0;-1;",128,0,0,0
	.stabs	"long long unsigned int:t(0,7)=r(0,7);0;-1;",128,0,0,0
	.stabs	"short int:t(0,8)=r(0,8);-32768;32767;",128,0,0,0
	.stabs	"short unsigned int:t(0,9)=r(0,9);0;65535;",128,0,0,0
	.stabs	"signed char:t(0,10)=r(0,10);-128;127;",128,0,0,0
	.stabs	"unsigned char:t(0,11)=r(0,11);0;255;",128,0,0,0
	.stabs	"float:t(0,12)=r(0,1);4;0;",128,0,0,0
	.stabs	"double:t(0,13)=r(0,1);8;0;",128,0,0,0
	.stabs	"long double:t(0,14)=r(0,1);12;0;",128,0,0,0
	.stabs	"void:t(0,15)=(0,15)",128,0,0,0
	.stabs	"C:/Program Files (x86)/quincy/mingw/include/stdio.h",130,0,0,0
	.stabs	"c:/program files (x86)/quincy/mingw/bin/../lib/gcc/mingw32/4.2.1-sjlj/include/stddef.h",130,0,0,0
	.stabs	"size_t:t(2,1)=(0,4)",128,0,0,0
	.stabs	"wchar_t:t(2,2)=(0,9)",128,0,0,0
	.stabs	"wint_t:t(2,3)=(0,9)",128,0,0,0
	.stabn	162,0,0,0
	.stabs	"c:/program files (x86)/quincy/mingw/bin/../lib/gcc/mingw32/4.2.1-sjlj/include/stdarg.h",130,0,0,0
	.stabs	"__gnuc_va_list:t(3,1)=(3,2)=*(0,2)",128,0,0,0
	.stabn	162,0,0,0
	.stabs	"_iobuf:T(1,1)=s32_ptr:(3,2),0,32;_cnt:(0,1),32,32;_base:(3,2),64,32;_flag:(0,1),96,32;_file:(0,1),128,32;_charbuf:(0,1),160,32;_bufsiz:(0,1),192,32;_tmpfname:(3,2),224,32;;",128,0,0,0
	.stabs	"FILE:t(1,2)=(1,1)",128,0,0,0
	.stabs	"fpos_t:t(1,3)=(0,6)",128,0,0,0
	.stabn	162,0,0,0
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "Client Name: o %s\12\0"
LC1:
	.ascii "Room Width: %d\12\0"
	.text
	.stabs	"main:F(0,1)",36,0,0,_main
.globl _main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	.stabn	68,0,21,LM0-LFBB1
LM0:
LFBB1:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ecx
	subl	$68, %esp
	.stabn	68,0,21,LM1-LFBB1
LM1:
	call	___main
	.stabn	68,0,25,LM2-LFBB1
LM2:
	leal	-48(%ebp), %eax
	movl	%eax, (%esp)
	call	_askName
	.stabn	68,0,26,LM3-LFBB1
LM3:
	call	_askWidth
	movl	%eax, -16(%ebp)
	.stabn	68,0,27,LM4-LFBB1
LM4:
	leal	-48(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	_printf
	.stabn	68,0,28,LM5-LFBB1
LM5:
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	_printf
	.stabn	68,0,29,LM6-LFBB1
LM6:
	movl	$0, %eax
	.stabn	68,0,30,LM7-LFBB1
LM7:
	addl	$68, %esp
	popl	%ecx
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.stabs	"name:(0,16)=ar(0,17)=r(0,17);0;-1;;0;31;(0,2)",128,0,0,-48
	.stabs	"width:(0,1)",128,0,0,-16
	.stabs	"height:(0,1)",128,0,0,-12
	.stabs	"length:(0,1)",128,0,0,-8
	.stabn	192,0,0,LFBB1-LFBB1
	.stabn	224,0,0,Lscope1-LFBB1
Lscope1:
	.section .rdata,"dr"
LC2:
	.ascii "Please enter client name: \0"
	.text
	.stabs	"askName:F(0,15)",36,0,0,_askName
	.stabs	"namePtr:p(3,2)",160,0,0,8
.globl _askName
	.def	_askName;	.scl	2;	.type	32;	.endef
_askName:
	.stabn	68,0,37,LM8-LFBB2
LM8:
LFBB2:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	.stabn	68,0,38,LM9-LFBB2
LM9:
	movl	$LC2, (%esp)
	call	_printf
	.stabn	68,0,39,LM10-LFBB2
LM10:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_gets
	.stabn	68,0,40,LM11-LFBB2
LM11:
	leave
	ret
Lscope2:
	.section .rdata,"dr"
LC3:
	.ascii "Please enter room width: \0"
LC4:
	.ascii "%d\0"
	.text
	.stabs	"askWidth:F(0,1)",36,0,0,_askWidth
.globl _askWidth
	.def	_askWidth;	.scl	2;	.type	32;	.endef
_askWidth:
	.stabn	68,0,43,LM12-LFBB3
LM12:
LFBB3:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	.stabn	68,0,45,LM13-LFBB3
LM13:
	movl	$LC3, (%esp)
	call	_printf
	.stabn	68,0,46,LM14-LFBB3
LM14:
	leal	-4(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC4, (%esp)
	call	_scanf
	.stabn	68,0,47,LM15-LFBB3
LM15:
	movl	-4(%ebp), %eax
	.stabn	68,0,48,LM16-LFBB3
LM16:
	leave
	ret
	.stabs	"width:(0,1)",128,0,0,-4
	.stabn	192,0,0,LFBB3-LFBB3
	.stabn	224,0,0,Lscope3-LFBB3
Lscope3:
	.stabs	"askHeight:F(0,1)",36,0,0,_askHeight
.globl _askHeight
	.def	_askHeight;	.scl	2;	.type	32;	.endef
_askHeight:
	.stabn	68,0,51,LM17-LFBB4
LM17:
LFBB4:
	pushl	%ebp
	movl	%esp, %ebp
	.stabn	68,0,53,LM18-LFBB4
LM18:
	popl	%ebp
	ret
Lscope4:
	.stabs	"askLength:F(0,1)",36,0,0,_askLength
.globl _askLength
	.def	_askLength;	.scl	2;	.type	32;	.endef
_askLength:
	.stabn	68,0,56,LM19-LFBB5
LM19:
LFBB5:
	pushl	%ebp
	movl	%esp, %ebp
	.stabn	68,0,58,LM20-LFBB5
LM20:
	popl	%ebp
	ret
Lscope5:
	.stabs	"askPaintType:F(0,2)",36,0,0,_askPaintType
.globl _askPaintType
	.def	_askPaintType;	.scl	2;	.type	32;	.endef
_askPaintType:
	.stabn	68,0,61,LM21-LFBB6
LM21:
LFBB6:
	pushl	%ebp
	movl	%esp, %ebp
	.stabn	68,0,63,LM22-LFBB6
LM22:
	popl	%ebp
	ret
Lscope6:
	.stabs	"askUndercoatNeeded:F(0,1)",36,0,0,_askUndercoatNeeded
.globl _askUndercoatNeeded
	.def	_askUndercoatNeeded;	.scl	2;	.type	32;	.endef
_askUndercoatNeeded:
	.stabn	68,0,66,LM23-LFBB7
LM23:
LFBB7:
	pushl	%ebp
	movl	%esp, %ebp
	.stabn	68,0,68,LM24-LFBB7
LM24:
	popl	%ebp
	ret
Lscope7:
	.stabs	"askLabour:F(0,1)",36,0,0,_askLabour
.globl _askLabour
	.def	_askLabour;	.scl	2;	.type	32;	.endef
_askLabour:
	.stabn	68,0,71,LM25-LFBB8
LM25:
LFBB8:
	pushl	%ebp
	movl	%esp, %ebp
	.stabn	68,0,73,LM26-LFBB8
LM26:
	popl	%ebp
	ret
Lscope8:
	.stabs	"calculateInvoice:F(0,15)",36,0,0,_calculateInvoice
	.stabs	"width:p(0,1)",160,0,0,8
	.stabs	"height:p(0,1)",160,0,0,12
	.stabs	"length:p(0,1)",160,0,0,16
	.stabs	"paintType:p(0,1)",160,0,0,20
	.stabs	"undercoatNeeded:p(0,1)",160,0,0,24
	.stabs	"labour:p(0,1)",160,0,0,28
.globl _calculateInvoice
	.def	_calculateInvoice;	.scl	2;	.type	32;	.endef
_calculateInvoice:
	.stabn	68,0,77,LM27-LFBB9
LM27:
LFBB9:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	20(%ebp), %eax
	movb	%al, -4(%ebp)
	.stabn	68,0,79,LM28-LFBB9
LM28:
	leave
	ret
	.stabs	"paintType:(0,2)",128,0,0,-4
Lscope9:
	.stabs	"",100,0,0,Letext0
Letext0:
	.def	_scanf;	.scl	2;	.type	32;	.endef
	.def	_gets;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
