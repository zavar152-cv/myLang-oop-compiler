    [section codeM]

  JMP main
test:

.BB0:
  ENTER 2
.BB1:

  ;OT at 56:9
  LDI32 R0, 9
  ;var l
  ST d R0, [BP, -8]

  ;OT at 57:9
  LDI32 R0, 8
  ;var l
  LD d R1, [BP, -8]
  LDI32 R2, 7
  MUL d R1, R2
  ADD d R0, R1
  ;var b
  ST d R0, [BP, -16]

  ;OT at 58:5
  ;var l
  LD d R0, [BP, -8]
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 2
  RET

main:

.BB0:
  ENTER 7
.BB1:

  ;OT at 2:9

  ;OT at 4:10
  LDI32 R0, 0x69
  ;var c
  ST b R0, [BP, -16]

  ;OT at 9:12
  LDI32 R0, main_const0
  ;var s
  ST q R0, [BP, -24]

  ;OT at 0:1
  LDI32 AR, main_const1
  LDC64 R0, AR
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var DEC
  PUSH R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV RT, ALR
  ADD q ALR, R0
  LEAVE 0
  ;var DEC
  POP R0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  ;var matrix
  ST q RT, [BP, -32]

  ;OT at 15:15
  ;var matrix
  LD q R1, [BP, -32]
  LDI32 R2, 0
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LDI32 AR, main_const2
  LDC64 R0, AR
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var DEC
  PUSH R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV RT, ALR
  ADD q ALR, R0
  LEAVE 0
  ;var DEC
  POP R0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  ST q RT, R1

  ;OT at 16:15
  ;var matrix
  LD q R1, [BP, -32]
  LDI32 R2, 1
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LDI32 AR, main_const2
  LDC64 R0, AR
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var DEC
  PUSH R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV RT, ALR
  ADD q ALR, R0
  LEAVE 0
  ;var DEC
  POP R0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  ST q RT, R1

  ;OT at 17:15
  ;var matrix
  LD q R1, [BP, -32]
  LDI32 R2, 2
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LDI32 AR, main_const2
  LDC64 R0, AR
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var DEC
  PUSH R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV RT, ALR
  ADD q ALR, R0
  LEAVE 0
  ;var DEC
  POP R0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  ST q RT, R1

  ;OT at 18:15
  ;var matrix
  LD q R1, [BP, -32]
  LDI32 R2, 3
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LDI32 AR, main_const2
  LDC64 R0, AR
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var DEC
  PUSH R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV RT, ALR
  ADD q ALR, R0
  LEAVE 0
  ;var DEC
  POP R0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  ST q RT, R1

  ;OT at 20:18
  ;var matrix
  LD q R1, [BP, -32]
  LDI32 R2, 0
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LD q R1, R1
  LDI32 R2, 0
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LDI32 R2, 0
  ST q R2, R1

  ;OT at 21:18
  ;var matrix
  LD q R1, [BP, -32]
  LDI32 R2, 0
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LD q R1, R1
  LDI32 R2, 1
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LDI32 R2, 10
  ST q R2, R1

  ;OT at 23:18
  ;var matrix
  LD q R1, [BP, -32]
  LDI32 R2, 1
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LD q R1, R1
  LDI32 R2, 0
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LDI32 R2, 20
  ST q R2, R1

  ;OT at 24:18
  ;var matrix
  LD q R1, [BP, -32]
  LDI32 R2, 1
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LD q R1, R1
  LDI32 R2, 1
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LDI32 R2, 21
  ST q R2, R1

  ;OT at 26:18
  ;var matrix
  LD q R1, [BP, -32]
  LDI32 R2, 2
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LD q R1, R1
  LDI32 R2, 0
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LDI32 R2, 40
  ST q R2, R1

  ;OT at 27:18
  ;var matrix
  LD q R1, [BP, -32]
  LDI32 R2, 2
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LD q R1, R1
  LDI32 R2, 1
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LDI32 R2, 50
  ST q R2, R1

  ;OT at 29:18
  ;var matrix
  LD q R1, [BP, -32]
  LDI32 R2, 3
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LD q R1, R1
  LDI32 R2, 0
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LDI32 R2, 60
  ST q R2, R1

  ;OT at 30:18
  ;var matrix
  LD q R1, [BP, -32]
  LDI32 R2, 3
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LD q R1, R1
  LDI32 R2, 1
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LDI32 R2, 701
  ST q R2, R1

  ;OT at 32:9
  LDI32 AR, main_const3
  LDC64 R0, AR
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var DEC
  PUSH R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV RT, ALR
  ADD q ALR, R0
  LEAVE 0
  ;var DEC
  POP R0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  ;var buffer
  ST d RT, [BP, -40]

  ;OT at 34:9
  ;var buffer
  LD d R0, [BP, -40]
  ;var b
  ST d R0, [BP, -48]

  ;OT at 35:5
  ;var b
  LD d R0, [BP, -48]
  ;var buffer
  LD d R1, [BP, -40]
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var buffer
  PUSH R1
  ;var b
  PUSH R0
  CALL printlnNumber
  ;var b
  POP R0
  ;var buffer
  POP R1
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0

  ;OT at 36:5
  ;var matrix
  LD q R0, [BP, -32]
  LDI32 R1, 0
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  LDI32 R1, 0
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  ;var buffer
  LD d R1, [BP, -40]
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var buffer
  PUSH R1
  ;var indexr
  PUSH R0
  CALL printlnNumber
  ;var indexr
  POP R0
  ;var buffer
  POP R1
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0

  ;OT at 37:5
  ;var matrix
  LD q R0, [BP, -32]
  LDI32 R1, 0
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  LDI32 R1, 1
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  ;var buffer
  LD d R1, [BP, -40]
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var buffer
  PUSH R1
  ;var indexr
  PUSH R0
  CALL printlnNumber
  ;var indexr
  POP R0
  ;var buffer
  POP R1
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0

  ;OT at 38:5
  ;var matrix
  LD q R0, [BP, -32]
  LDI32 R1, 1
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  LDI32 R1, 0
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  ;var buffer
  LD d R1, [BP, -40]
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var buffer
  PUSH R1
  ;var indexr
  PUSH R0
  CALL printlnNumber
  ;var indexr
  POP R0
  ;var buffer
  POP R1
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0

  ;OT at 39:5
  ;var matrix
  LD q R0, [BP, -32]
  LDI32 R1, 1
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  LDI32 R1, 1
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  ;var buffer
  LD d R1, [BP, -40]
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var buffer
  PUSH R1
  ;var indexr
  PUSH R0
  CALL printlnNumber
  ;var indexr
  POP R0
  ;var buffer
  POP R1
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0

  ;OT at 40:5
  ;var matrix
  LD q R0, [BP, -32]
  LDI32 R1, 2
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  LDI32 R1, 0
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  ;var buffer
  LD d R1, [BP, -40]
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var buffer
  PUSH R1
  ;var indexr
  PUSH R0
  CALL printlnNumber
  ;var indexr
  POP R0
  ;var buffer
  POP R1
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0

  ;OT at 41:5
  ;var matrix
  LD q R0, [BP, -32]
  LDI32 R1, 2
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  LDI32 R1, 1
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  ;var buffer
  LD d R1, [BP, -40]
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var buffer
  PUSH R1
  ;var indexr
  PUSH R0
  CALL printlnNumber
  ;var indexr
  POP R0
  ;var buffer
  POP R1
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0

  ;OT at 42:5
  ;var matrix
  LD q R0, [BP, -32]
  LDI32 R1, 3
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  LDI32 R1, 0
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  ;var buffer
  LD d R1, [BP, -40]
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var buffer
  PUSH R1
  ;var indexr
  PUSH R0
  CALL printlnNumber
  ;var indexr
  POP R0
  ;var buffer
  POP R1
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0

  ;OT at 43:5
  ;var matrix
  LD q R0, [BP, -32]
  LDI32 R1, 3
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  LDI32 R1, 1
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  ;var buffer
  LD d R1, [BP, -40]
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var buffer
  PUSH R1
  ;var indexr
  PUSH R0
  CALL printlnNumber
  ;var indexr
  POP R0
  ;var buffer
  POP R1
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0

  ;OT at 44:5
  ;var matrix
  LD q R0, [BP, -32]
  LDI32 R1, 3
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  LDI32 R1, 1
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  ;var buffer
  LD d R1, [BP, -40]
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var buffer
  PUSH R1
  ;var indexr
  PUSH R0
  CALL printlnNumber
  ;var indexr
  POP R0
  ;var buffer
  POP R1
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0

  ;OT at 45:5
  ;var matrix
  LD q R0, [BP, -32]
  LDI32 R1, 3
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  LDI32 R1, 1
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  ;var buffer
  LD d R1, [BP, -40]
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var buffer
  PUSH R1
  ;var indexr
  PUSH R0
  CALL printlnNumber
  ;var indexr
  POP R0
  ;var buffer
  POP R1
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0

  ;OT at 46:5
  ;var matrix
  LD q R0, [BP, -32]
  LDI32 R1, 3
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  LDI32 R1, 1
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  ;var buffer
  LD d R1, [BP, -40]
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var buffer
  PUSH R1
  ;var indexr
  PUSH R0
  CALL printlnNumber
  ;var indexr
  POP R0
  ;var buffer
  POP R1
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0

  ;OT at 47:5
  ;var matrix
  LD q R0, [BP, -32]
  LDI32 R1, 3
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  LDI32 R1, 1
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  ;var buffer
  LD d R1, [BP, -40]
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var buffer
  PUSH R1
  ;var indexr
  PUSH R0
  CALL printlnNumber
  ;var indexr
  POP R0
  ;var buffer
  POP R1
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0

  ;OT at 49:9
  ;var matrix
  LD q R0, [BP, -32]
  LDI32 R1, 0
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  LDI32 R1, 0
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  ;var v
  ST d R0, [BP, -56]

  ;OT at 50:5
  ;var v
  LD d R0, [BP, -56]
  ;var buffer
  LD d R1, [BP, -40]
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var buffer
  PUSH R1
  ;var v
  PUSH R0
  CALL printlnNumber
  ;var v
  POP R0
  ;var buffer
  POP R1
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0

  ;OT at 52:5
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 7
  HLT

printlnNumber:

.BB0:
  ENTER 0
.BB1:

  ;OT at 63:5
  ;var num
  LD d R0, [BP, 16]
  ;var bufferRef
  LD d R1, [BP, 24]
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var bufferRef
  PUSH R1
  ;var num
  PUSH R0
  CALL printNumber
  ;var num
  POP R0
  ;var bufferRef
  POP R1
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0

  ;OT at 64:5
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  CALL println
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0

  ;OT at 65:5
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

printNumber:

.BB0:
  ENTER 3
.BB1:

  ;OT at 0:1
  ;var bufferRef
  LD d R0, [BP, 24]
  ;var buffer
  ST q R0, [BP, -16]

  ;OT at 36:9
  ;var num
  LD d R0, [BP, 16]
  ;var temp
  ST d R0, [BP, -24]
  JMP .BB2

.BB2:

  ;OT at 37:14
  ;var temp
  LD d R0, [BP, -24]
  LDI32 R1, 0
  CMP d R0, R1
  LE R0
  JZ .BB4
  JNZ .BB3

.BB3:

  ;OT at 42:14
  ;var temp
  LD d R0, [BP, -24]
  LDI32 R1, 0
  CMP d R0, R1
  EQ R0
  JZ .BB6
  JNZ .BB7

.BB4:

  ;OT at 38:9
  LDI32 R0, 0x2D
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var SYMB
  PUSH R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV OUT, R0
  LEAVE 0
  ;var SYMB
  POP R0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0

  ;OT at 39:14
  ;var temp
  LD d R0, [BP, -24]
  NEG d R0
  ;var temp
  ST d R0, [BP, -24]
  JMP .BB3

.BB5:

  ;OT at 59:5
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB14

.BB6:

  ;OT at 43:9
  LDI32 R0, 0x30
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var SYMB
  PUSH R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV OUT, R0
  LEAVE 0
  ;var SYMB
  POP R0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  JMP .BB5

.BB7:

  ;OT at 45:13
  LDI32 R0, 0
  ;var index
  ST d R0, [BP, -8]
  JMP .BB8

.BB8:

  ;OT at 47:21
  ;var temp
  LD d R0, [BP, -24]
  LDI32 R1, 0
  CMP d R0, R1
  GR R0
  JZ .BB10
  JNZ .BB9

.BB9:

  ;OT at 53:15
  ;var index
  LD d R0, [BP, -8]
  LDI32 R1, 1
  SUB d R0, R1
  ;var index
  ST d R0, [BP, -8]
  JMP .BB11

.BB10:

  ;OT at 48:27
  ;var buffer
  LD q R1, [BP, -16]
  ;var index
  LD d R2, [BP, -8]
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  ;var temp
  LD d R2, [BP, -24]
  LDI32 R3, 10
  MOD d R2, R3
  LDI32 R3, 48
  OR q R2, R3
  ST q R2, R1

  ;OT at 49:19
  ;var index
  LD d R0, [BP, -8]
  LDI32 R1, 1
  ADD d R0, R1
  ;var index
  ST d R0, [BP, -8]

  ;OT at 50:18
  ;var temp
  LD d R0, [BP, -24]
  LDI32 R1, 10
  DIV d R0, R1
  ;var temp
  ST d R0, [BP, -24]
  JMP .BB8

.BB11:

  ;OT at 54:22
  ;var index
  LD d R0, [BP, -8]
  LDI32 R1, -1
  CMP d R0, R1
  NEQ R0
  JZ .BB13
  JNZ .BB12

.BB12:
  JMP .BB5

.BB13:

  ;OT at 55:13
  ;var buffer
  LD q R0, [BP, -16]
  ;var index
  LD d R1, [BP, -8]
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LD q R0, R0
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var read
  PUSH R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV OUT, R0
  LEAVE 0
  ;var read
  POP R0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0

  ;OT at 56:19
  ;var index
  LD d R0, [BP, -8]
  LDI32 R1, 1
  SUB d R0, R1
  ;var index
  ST d R0, [BP, -8]
  JMP .BB11

.BB14:
  LEAVE 3
  RET

printlnString:

.BB0:
  ENTER 0
.BB1:

  ;OT at 28:5
  ;var s
  LD q R0, [BP, 16]
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var s
  PUSH R0
  CALL printString
  ;var s
  POP R0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0

  ;OT at 29:5
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  CALL println
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0

  ;OT at 30:5
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

printString:

.BB0:
  ENTER 2
.BB1:

  ;OT at 18:9
  LDI32 R0, 0
  ;var i
  ST d R0, [BP, -8]

  ;OT at 19:9
  ;var s
  LD q R0, [BP, 16]
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var s
  PUSH R0
  CALL strlength
  ;var s
  POP R0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  ;var l
  ST d RT, [BP, -16]
  JMP .BB2

.BB2:

  ;OT at 20:14
  ;var i
  LD d R0, [BP, -8]
  ;var l
  LD d R1, [BP, -16]
  CMP d R0, R1
  NEQ R0
  JZ .BB4
  JNZ .BB3

.BB3:

  ;OT at 24:5
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB5

.BB4:

  ;OT at 21:9
  ;var s
  LD q R0, [BP, 16]
  ;var i
  LD d R1, [BP, -8]
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LDC64 R0, R0
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var read
  PUSH R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV OUT, R0
  LEAVE 0
  ;var read
  POP R0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0

  ;OT at 22:11
  ;var i
  LD d R0, [BP, -8]
  LDI32 R1, 1
  ADD d R0, R1
  ;var i
  ST d R0, [BP, -8]
  JMP .BB2

.BB5:
  LEAVE 2
  RET

println:

.BB0:
  ENTER 0
.BB1:

  ;OT at 13:5
  LDI32 R0, 0x0A
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var SYMB
  PUSH R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV OUT, R0
  LEAVE 0
  ;var SYMB
  POP R0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0

  ;OT at 14:5
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

strlength:

.BB0:
  ENTER 1
.BB1:

  ;OT at 2:9
  LDI32 R0, 0
  ;var len
  ST d R0, [BP, -8]
  JMP .BB2

.BB2:

  ;OT at 3:17
  LDI32 R0, 1
  LDI32 R1, 1
  CMP q R0, R1
  EQ R0
  JZ .BB4
  JNZ .BB3

.BB3:

  ;OT at 9:5
  ;var len
  LD d R0, [BP, -8]
  MOV RT, R0
  JMP .BB8

.BB4:
  JMP .BB5

.BB5:

  ;OT at 4:22
  ;var str
  LD q R0, [BP, 16]
  ;var len
  LD d R1, [BP, -8]
  LDI32 BR2, 8
  MUL q R1, BR2
  ADD q R0, R1
  LDC64 R0, R0
  LDI32 R1, 0x00
  CMP b R0, R1
  EQ R0
  JZ .BB7
  JNZ .BB6

.BB6:

  ;OT at 7:13
  ;var len
  LD d R0, [BP, -8]
  LDI32 R1, 1
  ADD d R0, R1
  ;var len
  ST d R0, [BP, -8]
  JMP .BB2

.BB7:

  ;OT at 5:13
  JMP .BB3

.BB8:
  LEAVE 1
  RET


    [section constantsM]


main_const0:
  dq 0x48
  dq 0x65
  dq 0x6C
  dq 0x6C
  dq 0x6F
  dq 0x00
main_const1:
  dq 32

main_const2:
  dq 16

main_const3:
  dq 80
