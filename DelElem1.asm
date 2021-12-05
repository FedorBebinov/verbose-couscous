section .data
extern buf
extern size_obj
	eps dq 1.e-6

section .bss

section .text
bits 64
global delElem1
delElem1:
push rbp
mov rbp,rsp
	mov rdx,eps
	movsd xmm1,[rdx] ;eps
	mov rdx,buf
	movsd xmm0,[rdx+8] ;tAver
	mov eax,[rdx+4]
	mov r8,rax ;k_obj
;add rdx,16
;mov rax,r8
;movsd xmm0,xmm2
;jmp .return
	mov eax,[qword size_obj]
	mov r9,rax ;size_obj
	add rdx,16 ;tmp
	mov r10,rdx ;tmp1
	xor rcx,rcx
.loop:
	cmp rcx,r8
	jge .return
	add r10,r9 ;tmp1
	movsd xmm2,[rdx+8] ;aver
	addsd xmm2,xmm1
	comisd xmm0,xmm2
	jbe .label
	mov [rdx],dword -1
.label:
	inc rcx
	mov rdx,r10
	jmp .loop
.return:
	pop rbp
	ret