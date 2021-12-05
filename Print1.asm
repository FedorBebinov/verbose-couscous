; // hello.c
; #include <stdio.h>
; int main()
; {
;   char msg[] = "Hello world\n";
;   printf("%s\n",msg);
;   return 0;  
;fprintf(output_file, "element %i: type %i dimension %i average %.2lf \n", i + 1, type, dim, aver);
; }
	
; Declare needed C  functions
        extern	fprintf		; the C function, to be called

        section .data		; Data section, initialized variables
aver:	dq 2.5
fmt:    db "element %i: type %i dimension %i average %.2lf ", 10, 0          

        section .text           ; Code section.
bits 64
        global print1		; the standard gcc entry point
print1:				; the program label for the entry point
        push    rbp		; set up stack frame, must be alligned
mov rbp,rsp
	
	mov	rsi,fmt
	mov	rdx,1
	mov	rcx,2
	mov	r8,3
	movsd xmm0,[aver]

	;lea	rcx,msg
	;mov	rdx,msg
	mov	rax,1		; or can be  xor  rax,rax
        call    fprintf		; Call C function

	mov	rax,0		; normal, no error, return value
	pop	rbp		; restore stack
	ret			; return
