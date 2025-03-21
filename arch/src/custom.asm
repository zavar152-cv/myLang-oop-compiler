    [section codeM]

  JMP main
test:

.BB0:
  ENTER 2
.BB1:

  ;OT at 93:9
  LDI32 R0, 9
  ;var l
  ST d R0, [BP, -8]

  ;OT at 94:9
  LDI32 R0, 8
  ;var l
  LD d R1, [BP, -8]
  LDI32 R2, 7
  MUL d R1, R2
  ADD d R0, R1
  ;var b
  ST d R0, [BP, -16]

  ;OT at 95:5
  ;var l
  LD d R0, [BP, -8]
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 2
  RET

main:

.BB0:
  ENTER 15
.BB1:

  ;OT at 2:9

  ;OT at 4:10
  LDI32 R0, 0x69
  ;var c
  ST b R0, [BP, -88]

  ;OT at 9:12
  LDI32 R0, main_const2
  ;var s
  ST q R0, [BP, -96]

  ;OT at 0:1
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
  MOV R1, RT
  ;var matrix
  ST q R1, [BP, -104]

  ;OT at 15:15
  ;var matrix
  LD q R1, [BP, -104]
  LDI32 R2, 0
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LDI32 AR, main_const4
  LDC64 R2, AR
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
  PUSH R2
  ENTER 0
  LD q R0, [BP, 8]
  MOV RT, ALR
  ADD q ALR, R0
  LEAVE 0
  ;var DEC
  POP R2
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R3, RT
  ST q R3, R1

  ;OT at 16:15
  ;var matrix
  LD q R1, [BP, -104]
  LDI32 R2, 1
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LDI32 AR, main_const4
  LDC64 R2, AR
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
  PUSH R2
  ENTER 0
  LD q R0, [BP, 8]
  MOV RT, ALR
  ADD q ALR, R0
  LEAVE 0
  ;var DEC
  POP R2
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R3, RT
  ST q R3, R1

  ;OT at 17:15
  ;var matrix
  LD q R1, [BP, -104]
  LDI32 R2, 2
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LDI32 AR, main_const4
  LDC64 R2, AR
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
  PUSH R2
  ENTER 0
  LD q R0, [BP, 8]
  MOV RT, ALR
  ADD q ALR, R0
  LEAVE 0
  ;var DEC
  POP R2
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R3, RT
  ST q R3, R1

  ;OT at 18:15
  ;var matrix
  LD q R1, [BP, -104]
  LDI32 R2, 3
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LDI32 AR, main_const4
  LDC64 R2, AR
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
  PUSH R2
  ENTER 0
  LD q R0, [BP, 8]
  MOV RT, ALR
  ADD q ALR, R0
  LEAVE 0
  ;var DEC
  POP R2
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R3, RT
  ST q R3, R1

  ;OT at 20:18
  ;var matrix
  LD q R1, [BP, -104]
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
  LD q R1, [BP, -104]
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
  LD q R1, [BP, -104]
  LDI32 R2, 1
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LD q R1, R1
  LDI32 R2, 0
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LDI32 R2, -20
  ST q R2, R1

  ;OT at 24:18
  ;var matrix
  LD q R1, [BP, -104]
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
  LD q R1, [BP, -104]
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
  LD q R1, [BP, -104]
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
  LD q R1, [BP, -104]
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
  LD q R1, [BP, -104]
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
  LDI32 AR, main_const5
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
  MOV R1, RT
  ;var buffer
  ST d R1, [BP, -112]

  ;OT at 34:10
  ;var buffer
  LD d R0, [BP, -112]
  LDI32 R1, 97
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
  PUSH R1
  ;var buffer
  PUSH R0
  ENTER 0
  LD d R0, [BP, 8]
  LD d R1, [BP, 16]
  CMP d R0, R1
  EQ RT
  LEAVE 0
  ;var buffer
  POP R0
  ;var DEC
  POP R1
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R2, RT
  ;var f
  ST q R2, [BP, -120]
  JMP .BB2

.BB2:

  ;OT at 36:11
  ;var f
  LD q R0, [BP, -120]
  LDI32 R1, 0
  CMP q R0, R1
  EQ R0
  JNZ .BB4
  JZ .BB3

.BB3:

  ;OT at 40:9
  ;var buffer
  LD d R0, [BP, -112]
  ;var b
  ST d R0, [BP, -48]

  ;OT at 41:5
  ;var b
  LD d R0, [BP, -48]
  ;var buffer
  LD d R1, [BP, -112]
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
  CALL printlnInt
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
  MOV R2, RT

  ;OT at 42:5
  ;var matrix
  LD q R0, [BP, -104]
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
  LD d R1, [BP, -112]
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
  CALL printlnInt
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
  MOV R2, RT

  ;OT at 43:5
  ;var matrix
  LD q R0, [BP, -104]
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
  LD d R1, [BP, -112]
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
  CALL printlnInt
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
  MOV R2, RT

  ;OT at 44:5
  ;var matrix
  LD q R0, [BP, -104]
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
  LD d R1, [BP, -112]
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
  CALL printlnInt
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
  MOV R2, RT

  ;OT at 45:5
  ;var matrix
  LD q R0, [BP, -104]
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
  LD d R1, [BP, -112]
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
  CALL printlnInt
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
  MOV R2, RT

  ;OT at 46:5
  ;var matrix
  LD q R0, [BP, -104]
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
  LD d R1, [BP, -112]
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
  CALL printlnInt
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
  MOV R2, RT

  ;OT at 47:5
  ;var matrix
  LD q R0, [BP, -104]
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
  LD d R1, [BP, -112]
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
  CALL printlnInt
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
  MOV R2, RT

  ;OT at 48:5
  ;var matrix
  LD q R0, [BP, -104]
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
  LD d R1, [BP, -112]
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
  CALL printlnInt
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
  MOV R2, RT

  ;OT at 49:5
  ;var matrix
  LD q R0, [BP, -104]
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
  LD d R1, [BP, -112]
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
  CALL printlnInt
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
  MOV R2, RT

  ;OT at 50:5
  ;var matrix
  LD q R0, [BP, -104]
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
  LD d R1, [BP, -112]
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
  CALL printlnInt
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
  MOV R2, RT

  ;OT at 51:5
  ;var matrix
  LD q R0, [BP, -104]
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
  LD d R1, [BP, -112]
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
  CALL printlnInt
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
  MOV R2, RT

  ;OT at 52:5
  ;var matrix
  LD q R0, [BP, -104]
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
  LD d R1, [BP, -112]
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
  CALL printlnInt
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
  MOV R2, RT

  ;OT at 53:5
  ;var matrix
  LD q R0, [BP, -104]
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
  LD d R1, [BP, -112]
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
  CALL printlnInt
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
  MOV R2, RT

  ;OT at 55:9
  ;var matrix
  LD q R0, [BP, -104]
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

  ;OT at 56:5
  ;var v
  LD d R0, [BP, -56]
  ;var buffer
  LD d R1, [BP, -112]
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
  CALL printlnInt
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
  MOV R2, RT

  ;OT at 58:9
  LDI32 R0, -2
  ;var y
  ST d R0, [BP, -64]

  ;OT at 60:10
  ;var y
  LD d R0, [BP, -64]
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var y
  PUSH R0
  ENTER 0
  LD q R0, [BP, 8]
  MOVT b RT, R0
  LEAVE 0
  ;var y
  POP R0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R1, RT
  ;var u
  ST b R1, [BP, -72]
  JMP .BB5

.BB4:

  ;OT at 37:9
  LDI32 R0, 0x6D
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
  LDI32 RT, 0
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
  MOV R1, RT
  JMP .BB3

.BB5:

  ;OT at 62:11
  ;var u
  LD b R0, [BP, -72]
  LDI32 R1, 254
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
  PUSH R1
  ENTER 0
  LD q R0, [BP, 8]
  MOVT b RT, R0
  LEAVE 0
  ;var DEC
  POP R1
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R2, RT
  CMP b R0, R2
  EQ R0
  JNZ .BB7
  JZ .BB6

.BB6:

  ;OT at 66:9
  LDI32 R0, -1
  ;var k
  ST d R0, [BP, -32]

  ;OT at 68:10
  ;var k
  LD d R0, [BP, -32]
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var k
  PUSH R0
  ENTER 0
  LD q R0, [BP, 8]
  MOVT d RT, R0
  LEAVE 0
  ;var k
  POP R0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R1, RT
  ;var k1
  ST d R1, [BP, -40]
  JMP .BB8

.BB7:

  ;OT at 63:9
  LDI32 R0, 0x72
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
  LDI32 RT, 0
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
  MOV R1, RT
  JMP .BB6

.BB8:

  ;OT at 70:12
  ;var k1
  LD d R0, [BP, -40]
  LDI32 R1, 4294967295
  CMP d R0, R1
  EQ R0
  JNZ .BB10
  JZ .BB9

.BB9:

  ;OT at 0:1
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  CALL longBufferSize
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R0, RT
  LDI32 R1, 8
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
  PUSH R1
  ENTER 0
  LD d R0, [BP, 8]
  CDQ RT, R0
  LEAVE 0
  ;var DEC
  POP R1
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R2, RT
  MUL q R0, R2
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var call
  PUSH R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV RT, ALR
  ADD q ALR, R0
  LEAVE 0
  ;var call
  POP R0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R2, RT
  ;var longBuffer
  ST q R2, [BP, -8]

  ;OT at 80:10
  LDI32 AR, main_const1
  LDC64 R0, AR
  ;var p
  ST q R0, [BP, -16]

  ;OT at 82:10
  ;var p
  LD q R0, [BP, -16]
  LDI32 R1, 3
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
  PUSH R1
  ENTER 0
  LD d R0, [BP, 8]
  CDQ RT, R0
  LEAVE 0
  ;var DEC
  POP R1
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R2, RT
  SUB q R0, R2
  ;var res
  ST q R0, [BP, -24]
  JMP .BB11

.BB10:

  ;OT at 71:9
  LDI32 R0, 0x71
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
  LDI32 RT, 0
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
  MOV R1, RT
  JMP .BB9

.BB11:

  ;OT at 84:13
  ;var res
  LD q R0, [BP, -24]
  LDI32 AR, main_const0
  LDC64 R1, AR
  CMP q R0, R1
  EQ R0
  JNZ .BB13
  JZ .BB12

.BB12:

  ;OT at 89:5
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB14

.BB13:

  ;OT at 85:9
  ;var res
  LD q R0, [BP, -24]
  ;var longBuffer
  LD q R1, [BP, -8]
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var longBuffer
  PUSH R1
  ;var res
  PUSH R0
  CALL printLong
  ;var res
  POP R0
  ;var longBuffer
  POP R1
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R2, RT

  ;OT at 86:9
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
  MOV R0, RT
  JMP .BB12

.BB14:
  LEAVE 15
  HLT

printlnLong:

.BB0:
  ENTER 0
.BB1:

  ;OT at 138:5
  ;var num
  LD q R0, [BP, 16]
  ;var bufferRef
  LD q R1, [BP, 24]
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
  CALL printLong
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
  MOV R2, RT

  ;OT at 139:5
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
  MOV R0, RT

  ;OT at 140:5
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

printLong:

.BB0:
  ENTER 3
.BB1:

  ;OT at 0:1
  ;var bufferRef
  LD q R0, [BP, 24]
  ;var buffer
  ST q R0, [BP, -16]

  ;OT at 110:10
  ;var num
  LD q R0, [BP, 16]
  ;var temp
  ST q R0, [BP, -24]
  JMP .BB2

.BB2:

  ;OT at 112:14
  ;var temp
  LD q R0, [BP, -24]
  LDI32 R1, 0
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
  PUSH R1
  ENTER 0
  LD d R0, [BP, 8]
  CDQ RT, R0
  LEAVE 0
  ;var DEC
  POP R1
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R2, RT
  CMP q R0, R2
  LE R0
  JNZ .BB4
  JZ .BB3

.BB3:

  ;OT at 117:14
  ;var temp
  LD q R0, [BP, -24]
  LDI32 R1, 0
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
  PUSH R1
  ENTER 0
  LD d R0, [BP, 8]
  CDQ RT, R0
  LEAVE 0
  ;var DEC
  POP R1
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R2, RT
  CMP q R0, R2
  EQ R0
  JNZ .BB6
  JZ .BB7

.BB4:

  ;OT at 113:9
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
  LDI32 RT, 0
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
  MOV R1, RT

  ;OT at 114:14
  ;var temp
  LD q R0, [BP, -24]
  NEG q R0
  ;var temp
  ST q R0, [BP, -24]
  JMP .BB3

.BB5:

  ;OT at 134:5
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB14

.BB6:

  ;OT at 118:9
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
  LDI32 RT, 0
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
  MOV R1, RT
  JMP .BB5

.BB7:

  ;OT at 120:13
  LDI32 R0, 0
  ;var index
  ST d R0, [BP, -8]
  JMP .BB8

.BB8:

  ;OT at 122:21
  ;var temp
  LD q R0, [BP, -24]
  LDI32 R1, 0
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
  PUSH R1
  ENTER 0
  LD d R0, [BP, 8]
  CDQ RT, R0
  LEAVE 0
  ;var DEC
  POP R1
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R2, RT
  CMP q R0, R2
  GR R0
  JNZ .BB10
  JZ .BB9

.BB9:

  ;OT at 128:15
  ;var index
  LD d R0, [BP, -8]
  LDI32 R1, 1
  SUB d R0, R1
  ;var index
  ST d R0, [BP, -8]
  JMP .BB11

.BB10:

  ;OT at 123:27
  ;var buffer
  LD q R1, [BP, -16]
  ;var index
  LD d R2, [BP, -8]
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  ;var temp
  LD q R2, [BP, -24]
  LDI32 R3, 10
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
  PUSH R3
  ENTER 0
  LD d R0, [BP, 8]
  CDQ RT, R0
  LEAVE 0
  ;var DEC
  POP R3
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R4, RT
  MOD q R2, R4
  LDI32 R4, 48
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var HEX
  PUSH R4
  ENTER 0
  LD d R0, [BP, 8]
  CDQ RT, R0
  LEAVE 0
  ;var HEX
  POP R4
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R5, RT
  OR q R2, R5
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var %
  PUSH R2
  ENTER 0
  LD q R0, [BP, 8]
  MOVT d RT, R0
  LEAVE 0
  ;var %
  POP R2
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R5, RT
  ST q R5, R1

  ;OT at 124:19
  ;var index
  LD d R0, [BP, -8]
  LDI32 R1, 1
  ADD d R0, R1
  ;var index
  ST d R0, [BP, -8]

  ;OT at 125:18
  ;var temp
  LD q R0, [BP, -24]
  LDI32 R1, 10
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
  PUSH R1
  ENTER 0
  LD d R0, [BP, 8]
  CDQ RT, R0
  LEAVE 0
  ;var DEC
  POP R1
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R2, RT
  DIV q R0, R2
  ;var temp
  ST q R0, [BP, -24]
  JMP .BB8

.BB11:

  ;OT at 129:22
  ;var index
  LD d R0, [BP, -8]
  LDI32 R1, -1
  CMP d R0, R1
  NEQ R0
  JNZ .BB13
  JZ .BB12

.BB12:
  JMP .BB5

.BB13:

  ;OT at 130:13
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
  LDI32 RT, 0
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
  MOV R1, RT

  ;OT at 131:19
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

printlnInt:

.BB0:
  ENTER 0
.BB1:

  ;OT at 102:5
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
  CALL printInt
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
  MOV R2, RT

  ;OT at 103:5
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
  MOV R0, RT

  ;OT at 104:5
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

printInt:

.BB0:
  ENTER 3
.BB1:

  ;OT at 0:1
  ;var bufferRef
  LD d R0, [BP, 24]
  ;var buffer
  ST q R0, [BP, -16]

  ;OT at 75:9
  ;var num
  LD d R0, [BP, 16]
  ;var temp
  ST d R0, [BP, -24]
  JMP .BB2

.BB2:

  ;OT at 76:14
  ;var temp
  LD d R0, [BP, -24]
  LDI32 R1, 0
  CMP d R0, R1
  LE R0
  JNZ .BB4
  JZ .BB3

.BB3:

  ;OT at 81:14
  ;var temp
  LD d R0, [BP, -24]
  LDI32 R1, 0
  CMP d R0, R1
  EQ R0
  JNZ .BB6
  JZ .BB7

.BB4:

  ;OT at 77:9
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
  LDI32 RT, 0
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
  MOV R1, RT

  ;OT at 78:14
  ;var temp
  LD d R0, [BP, -24]
  NEG d R0
  ;var temp
  ST d R0, [BP, -24]
  JMP .BB3

.BB5:

  ;OT at 98:5
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB14

.BB6:

  ;OT at 82:9
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
  LDI32 RT, 0
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
  MOV R1, RT
  JMP .BB5

.BB7:

  ;OT at 84:13
  LDI32 R0, 0
  ;var index
  ST d R0, [BP, -8]
  JMP .BB8

.BB8:

  ;OT at 86:21
  ;var temp
  LD d R0, [BP, -24]
  LDI32 R1, 0
  CMP d R0, R1
  GR R0
  JNZ .BB10
  JZ .BB9

.BB9:

  ;OT at 92:15
  ;var index
  LD d R0, [BP, -8]
  LDI32 R1, 1
  SUB d R0, R1
  ;var index
  ST d R0, [BP, -8]
  JMP .BB11

.BB10:

  ;OT at 87:27
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

  ;OT at 88:19
  ;var index
  LD d R0, [BP, -8]
  LDI32 R1, 1
  ADD d R0, R1
  ;var index
  ST d R0, [BP, -8]

  ;OT at 89:18
  ;var temp
  LD d R0, [BP, -24]
  LDI32 R1, 10
  DIV d R0, R1
  ;var temp
  ST d R0, [BP, -24]
  JMP .BB8

.BB11:

  ;OT at 93:22
  ;var index
  LD d R0, [BP, -8]
  LDI32 R1, -1
  CMP d R0, R1
  NEQ R0
  JNZ .BB13
  JZ .BB12

.BB12:
  JMP .BB5

.BB13:

  ;OT at 94:13
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
  LDI32 RT, 0
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
  MOV R1, RT

  ;OT at 95:19
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

ulongBufferSize:

.BB0:
  ENTER 0
.BB1:

  ;OT at 68:5
  LDI32 AR, ulongBufferSize_const0
  LDC64 R0, AR
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

longBufferSize:

.BB0:
  ENTER 0
.BB1:

  ;OT at 64:5
  LDI32 AR, longBufferSize_const0
  LDC64 R0, AR
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

uintBufferSize:

.BB0:
  ENTER 0
.BB1:

  ;OT at 60:5
  LDI32 AR, uintBufferSize_const0
  LDC64 R0, AR
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

intBufferSize:

.BB0:
  ENTER 0
.BB1:

  ;OT at 56:5
  LDI32 AR, intBufferSize_const0
  LDC64 R0, AR
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

printlnString:

.BB0:
  ENTER 0
.BB1:

  ;OT at 50:5
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
  MOV R1, RT

  ;OT at 51:5
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
  MOV R0, RT

  ;OT at 52:5
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

  ;OT at 40:9
  LDI32 R0, 0
  ;var i
  ST d R0, [BP, -8]

  ;OT at 41:9
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
  MOV R1, RT
  ;var l
  ST d R1, [BP, -16]
  JMP .BB2

.BB2:

  ;OT at 42:14
  ;var i
  LD d R0, [BP, -8]
  ;var l
  LD d R1, [BP, -16]
  CMP d R0, R1
  NEQ R0
  JNZ .BB4
  JZ .BB3

.BB3:

  ;OT at 46:5
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB5

.BB4:

  ;OT at 43:9
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
  LDI32 RT, 0
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
  MOV R1, RT

  ;OT at 44:11
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

printlnChar:

.BB0:
  ENTER 0
.BB1:

  ;OT at 34:5
  ;var toOut
  LD b R0, [BP, 16]
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var toOut
  PUSH R0
  CALL printChar
  ;var toOut
  POP R0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R1, RT

  ;OT at 35:5
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
  MOV R0, RT

  ;OT at 36:5
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

printChar:

.BB0:
  ENTER 0
.BB1:

  ;OT at 29:5
  ;var toOut
  LD b R0, [BP, 16]
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var toOut
  PUSH R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV OUT, R0
  LDI32 RT, 0
  LEAVE 0
  ;var toOut
  POP R0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R1, RT

  ;OT at 30:5
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

printlnByte:

.BB0:
  ENTER 0
.BB1:

  ;OT at 23:5
  ;var toOut
  LD b R0, [BP, 16]
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var toOut
  PUSH R0
  CALL printByte
  ;var toOut
  POP R0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R1, RT

  ;OT at 24:5
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
  MOV R0, RT

  ;OT at 25:5
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

printByte:

.BB0:
  ENTER 0
.BB1:

  ;OT at 18:5
  ;var toOut
  LD b R0, [BP, 16]
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  ;var toOut
  PUSH R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV OUT, R0
  LDI32 RT, 0
  LEAVE 0
  ;var toOut
  POP R0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R1, RT

  ;OT at 19:5
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
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
  LDI32 RT, 0
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
  MOV R1, RT

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
  JNZ .BB4
  JZ .BB3

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
  JNZ .BB7
  JZ .BB6

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
  dq 9223372036854775804

main_const1:
  dq 9223372036854775807

main_const2:
  dq 0x48
  dq 0x65
  dq 0x6C
  dq 0x6C
  dq 0x6F
  dq 0x00
main_const3:
  dq 32

main_const4:
  dq 16

main_const5:
  dq 80

ulongBufferSize_const0:
  dq 19

longBufferSize_const0:
  dq 19

uintBufferSize_const0:
  dq 10

intBufferSize_const0:
  dq 10
