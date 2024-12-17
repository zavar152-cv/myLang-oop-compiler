	[section constantsM]
constA:
	dq 0x7
constStr:
	dq 0x8
	dq 0x9
	dq 0x10

	[section dataM]

varA: 
	dd 0x2
varB: 
	dd 0x2
emptyPlace:

	[section codeM]

main:
	ENTER 1
	;LDI32 SP, 0xFFFFFFFF

	;LDI32 R6, 0x7FFFFFFF
	;LDI32 R5, 0x00000001

	LDI32 BR1, constStr
	LDI32 BR2, emptyPlace
	MEMCPYC BR2, BR1, 3

	LD q R0, [BR2, 0]
	LD q R0, [BR2, 8]
	LD q R0, [BR2, 16]
	LDI32 AR, constA
	LDC64 R0, AR
	LDI32 R1, 0x7
	NEQ R0, R1

	LDI32 AR, varA
	LD d R6, AR
	LDI32 AR, varB
	LD d R5, AR

	;cbq R6, R6
	;cbq R5, R5

	ADD d R6, R5

	PUSH R6
	CALL func
	POP R6

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
	ENTER 2
	LDI32 R0, 0x9
	ST b R0, [BP, +8]
	LDI32 R1, 0x7
	LDI32 R2, 0x1
	PUSH R1
	PUSH R2
	POP R3
	POP R3
	LD b R4, [BP, +8]
	LDI32 R6, 0x0
	LEAVE 2
	RET

here:
	PUSH R1
	PUSH R7
	POP R5
	POP R5

	LEAVE 1
	HLT