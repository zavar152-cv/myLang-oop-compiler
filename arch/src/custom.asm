	[section dataM]

varA: 
	dd 0x2
varB: 
	dd 0x2

	[section codeM]

main:
	;LDI32 SP, 0xFFFFFFFF

	;LDI32 R6, 0x7FFFFFFF
	;LDI32 R5, 0x00000001

	LDI32 AR, varA
	LD d R6, AR
	LDI32 AR, varB
	LD d R5, AR

	;cbq R6, R6
	;cbq R5, R5

	MOD d R6, R5

	CALL func

	LDI32 R7, 0xFF
	;NOT b R7
	;JZ here
	LDI32 R1, 0xFA
	JGREQ R7, R1, here

	LDI32 R0, 0x10
	LDI32 R1, 0x80
	ADD b R0, R1
	LDI32 AR, 0x7
	ST b R0, AR
	LD b R3, AR

	ST b R3, [SP, -8]
	LD b R4, [SP, -8]

func:
	LDI32 R0, 0x9
	RET

here:
	PUSH R1
	PUSH R7
	POP R5
	POP R5

	HLT