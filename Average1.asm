;extern int size_obj;
;extern char buf[];
;void average() {
;	int k_obj = *((int*)(buf + 4));
;	char* tmp = buf + 16;
;	char* tmp1 = tmp;
;	double sum = 0.;
;	int len = 0;
;	for (int i = 0; i < k_obj; ++i) {
;		tmp1 += size_obj;
;		int type = *((int*)tmp);
;		int dim = *((int*)(tmp + 4));
;		int dim2 = dim * dim;
;		double* aver = (double*)(tmp + 8);
;		tmp += 16;
;		double sum_obj = 0.;
;		for (int j = 0; j < dim2; ++j) {
;			sum_obj += *((double*)tmp);
;			tmp += 8;
;		}
;		*aver = sum_obj / dim2;
;		len += dim2;
;		sum += sum_obj;
;		tmp = tmp1;
;	}
;	*((double*)(buf + 8)) = sum / len; //total average
;}
section .data
extern buf
extern size_obj
	len dd 0

section .bss
	avr_ resq 1

section .text
bits 64
global average1
average1:
push rbp
mov rbp,rsp
	xorps xmm0,xmm0 ;sum=0.
	mov rdx,buf
	mov eax,[rdx+4]
	mov r8,rax ;k_obj
	mov eax,[qword size_obj]
	mov r9,rax ;size_obj
	add rdx,16 ;tmp
	mov r10,rdx ;tmp1
	xor rcx,rcx ;cycle
.loop0:
	cmp rcx,r8
	jge .return0
	push rcx
	add r10,r9 ;tmp1
	mov eax,[rdx+4] ;dim
	imul eax,eax
	mov r11,rax ;dim2
	add rdx,8
	mov rcx,avr_
	mov [rcx],rdx ;adress aver
	add rdx,8
	xorps xmm1,xmm1 ;sum_obj=0.
	xor rcx,rcx ;cycle
.loop1:
	cmp rcx,r11
	jge .return1
	movsd xmm2,[rdx] ;cell
	addsd xmm1,xmm2
	add rdx,8
	inc rcx
	jmp .loop1
.return1:
	movsd xmm3,xmm1
	cvtsi2sd xmm2,r11
	divsd xmm3,xmm2
	mov rcx,avr_
	mov rax,[rcx]
	movsd [rax],xmm3
	mov eax,[len]
	;mov rcx,len
	;mov eax,[rcx]
	add rax,r11
	mov [len],eax
	;mov [rcx],eax
	addsd xmm0,xmm1
	pop rcx
	inc rcx
	mov rdx,r10
	jmp .loop0
.return0:
	mov rcx,len
	mov eax,[rcx]
	cvtsi2sd xmm2,rax
	divsd xmm0,xmm2
	mov rdx,buf
	movsd [rdx+8],xmm0
	pop rbp
	ret
