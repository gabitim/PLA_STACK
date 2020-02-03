include /masm32/include64/masm64rt.inc
include Source.inc

ELEM struct
	OP BYTE 0
	NR QWORD 0
	NEXT QWORD NULL

ELEM ENDS

.data
	elem ELEM {}
	head QWORD NULL
	numberAux QWORD NULL
	operandAux BYTE NULL
.code

Stack_Push PROC
	USING rbx, rdi, r12, r13
	SaveRegs

	mov rdi, rcx
	mov r12, rdx
	mov r13, r8


	mov rbx, malloc(sizeof ELEM)
	mov [rbx].ELEM.OP, r12b
	mov [rbx].ELEM.NR, r13
	mov [rbx].ELEM.NEXT, NULL

	.if rdi == 0
		mov [rbx].ELEM.NEXT, NULL
	.else
		mov [rbx].ELEM.NEXT, rdi
	.endif
	mov rdi, rbx
	mov head, rdi
	RestoreRegs

	ret
Stack_Push ENDP

Stack_Show PROC
	USING rbx
	SaveRegs
	mov rbx, rcx
	.if rbx == NULL
		printf("Vid\n")
	.else
		.repeat
			.if [rbx].ELEM.OP == '0'
				printf("%d\n", qword ptr [rbx].ELEM.NR)
			.else
				printf("%c\n", byte ptr [rbx].ELEM.OP)		
			.endif
			mov rbx, [rbx].ELEM.NEXT
		.until rbx == NULL
	.endif
	RestoreRegs
	ret	
Stack_Show ENDP

Stack_Pop PROC
	USING rbx, r12
	SaveRegs
	mov rbx, rcx
	mov r12, qword ptr [rbx].ELEM.NEXT
	free(rbx)
	mov rbx, r12
	mov head, rbx
	RestoreRegs
	ret
Stack_Pop ENDP

main proc
	
	printf("Nr: ")
	scanf("%d", addr numberAux)
	printf("Character: ")
	scanf("\n%c", addr operandAux)
	
	mov rcx, head
	movzx rdx, operandAux
	mov r8, numberAux
	call Stack_Push

	printf("Nr: ")
	scanf("%d", addr numberAux)
	printf("Character: ")
	scanf("\n%c", addr operandAux)
	
	mov rcx, head
	movzx rdx, operandAux
	mov r8, numberAux
	call Stack_Push

	mov rcx, head
	call Stack_Show


	
	ret
main endp


end