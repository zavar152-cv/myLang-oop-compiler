    [section codeM]

  LDI32 AR, classInfo_Main
  MOV THIS, ALR
  NEW AR, 0
  JMP Main_main
main:
Main_main:

.BB0:
  ENTER 3
.BB1:

  ;OT at 54:17
  PUSH THIS
  LDI32 AR, classInfo_BuiltIn
  MOV THIS, ALR
  NEW AR, 0
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  CALL BuiltIn_BuiltIn
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R0, THIS
  POP THIS
  ;var bi
  ST q R0, [BP, -8]

  ;OT at 55:12
  PUSH THIS
  LDI32 AR, classInfo_IO
  MOV THIS, ALR
  NEW AR, 3
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  CALL IO_IO
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R0, THIS
  POP THIS
  ;var io
  ST q R0, [BP, -16]

  ;OT at 0:1
  LDI32 R1, 16
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var DEC
  PUSH R1
  ;var bi
  LD q R0, [BP, -8]
  MOV THIS, R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV RT, ALR
  ADD q ALR, R0
  LEAVE 0
  ;var DEC
  POP R1
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R2, RT
  ;var shapes
  ST q R2, [BP, -24]

  ;OT at 58:19
  ;var shapes
  LD q R1, [BP, -24]
  LDI32 R2, 0
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LDI32 R2, 3
  LDI32 R3, 4
  PUSH THIS
  LDI32 AR, classInfo_Rectangle
  MOV THIS, ALR
  NEW AR, 2
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var DEC
  PUSH R3
  ;var DEC
  PUSH R2
  CALL Rectangle_Rectangle
  ;var DEC
  POP R2
  ;var DEC
  POP R3
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R4, THIS
  POP THIS
  ST q R4, R1

  ;OT at 59:19
  ;var shapes
  LD q R1, [BP, -24]
  LDI32 R2, 1
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LDI32 R2, 10
  PUSH THIS
  LDI32 AR, classInfo_Circle
  MOV THIS, ALR
  NEW AR, 1
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var DEC
  PUSH R2
  CALL Circle_Circle
  ;var DEC
  POP R2
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R3, THIS
  POP THIS
  ST q R3, R1

  ;OT at 61:12
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var shapes
  LD q R1, [BP, -24]
  LDI32 R2, 0
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LD q R1, R1
  MOV THIS, R1
  MCALL R1, 8
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R2, RT
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var method
  PUSH R2
  ;var io
  LD q R0, [BP, -16]
  MOV THIS, R0
  MCALL R0, 72
  ;var method
  POP R2
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R3, RT

  ;OT at 62:12
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var shapes
  LD q R1, [BP, -24]
  LDI32 R2, 0
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LD q R1, R1
  MOV THIS, R1
  MCALL R1, 16
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R2, RT
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var method
  PUSH R2
  ;var io
  LD q R0, [BP, -16]
  MOV THIS, R0
  MCALL R0, 24
  ;var method
  POP R2
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R3, RT

  ;OT at 64:12
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var shapes
  LD q R1, [BP, -24]
  LDI32 R2, 1
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LD q R1, R1
  MOV THIS, R1
  MCALL R1, 8
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R2, RT
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var method
  PUSH R2
  ;var io
  LD q R0, [BP, -16]
  MOV THIS, R0
  MCALL R0, 72
  ;var method
  POP R2
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R3, RT

  ;OT at 65:12
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var shapes
  LD q R1, [BP, -24]
  LDI32 R2, 1
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LD q R1, R1
  MOV THIS, R1
  MCALL R1, 16
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R2, RT
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var method
  PUSH R2
  ;var io
  LD q R0, [BP, -16]
  MOV THIS, R0
  MCALL R0, 24
  ;var method
  POP R2
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R3, RT

  ;OT at 67:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 3
  HLT

Main_Main:

.BB0:
  ENTER 0
.BB1:
  LEAVE 0
  RET

Circle_area:

.BB0:
  ENTER 0
.BB1:

  ;OT at 42:33
  ;var radius
  FA AR, THIS, 0
  LD d R0, AR
  ;var radius
  FA AR, THIS, 0
  LD d R1, AR
  MUL d R0, R1
  LDI32 R1, 314
  MUL d R0, R1
  LDI32 R1, 100
  DIV d R0, R1
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

Circle_Circle:

.BB0:
  ENTER 0
.BB1:

  ;OT at 37:9
  LDI32 R0, Circle_Circle_const0
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var STR
  PUSH R0
  CALL Shape_Shape
  ;var STR
  POP R0
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R1, RT

  ;OT at 38:16
  ;var radiusArg
  LD d R0, [BP, 16]
  ;var radius
  FA AR, THIS, 0
  ST d R0, AR
  JMP .BB2

.BB2:
  LEAVE 0
  RET

Rectangle_area:

.BB0:
  ENTER 0
.BB1:

  ;OT at 28:15
  ;var width
  FA AR, THIS, 0
  LD d R0, AR
  ;var height
  FA AR, THIS, 8
  LD d R1, AR
  MUL d R0, R1
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

Rectangle_Rectangle:

.BB0:
  ENTER 0
.BB1:

  ;OT at 22:9
  LDI32 R0, Rectangle_Rectangle_const0
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var STR
  PUSH R0
  CALL Shape_Shape
  ;var STR
  POP R0
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R1, RT

  ;OT at 23:15
  ;var widthArg
  LD d R0, [BP, 16]
  ;var width
  FA AR, THIS, 0
  ST d R0, AR

  ;OT at 24:16
  ;var heightArg
  LD d R0, [BP, 24]
  ;var height
  FA AR, THIS, 8
  ST d R0, AR
  JMP .BB2

.BB2:
  LEAVE 0
  RET

Shape_getName:

.BB0:
  ENTER 0
.BB1:

  ;OT at 13:9
  ;var name
  FA AR, THIS, 0
  LD q R0, AR
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

Shape_area:

.BB0:
  ENTER 0
.BB1:

  ;OT at 9:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

Shape_Shape:

.BB0:
  ENTER 0
.BB1:

  ;OT at 5:14
  ;var nameArg
  LD q R0, [BP, 16]
  ;var name
  FA AR, THIS, 0
  ST q R0, AR
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO_printlnLong:

.BB0:
  ENTER 0
.BB1:

  ;OT at 149:9
  ;var num
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
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var num
  PUSH R0
  CALL IO_printLong
  ;var num
  POP R0
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R1, RT

  ;OT at 150:9
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  CALL IO_println
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R0, RT

  ;OT at 151:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO_printLong:

.BB0:
  ENTER 3
.BB1:

  ;OT at 0:1
  ;var longBuffer
  FA AR, THIS, 16
  LD d R0, AR
  ;var buffer
  ST q R0, [BP, -16]

  ;OT at 121:14
  ;var num
  LD q R0, [BP, 16]
  ;var temp
  ST q R0, [BP, -24]
  JMP .BB2

.BB2:

  ;OT at 123:18
  ;var temp
  LD q R0, [BP, -24]
  LDI32 R2, 0
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var DEC
  PUSH R2
  ;var bi
  FA AR, THIS, 0
  LD q R1, AR
  MOV THIS, R1
  ENTER 0
  LD d R0, [BP, 8]
  CDQ RT, R0
  LEAVE 0
  ;var DEC
  POP R2
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R3, RT
  CMP q R0, R3
  LE R0
  JNZ .BB4
  JZ .BB3

.BB3:

  ;OT at 128:18
  ;var temp
  LD q R0, [BP, -24]
  LDI32 R2, 0
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var DEC
  PUSH R2
  ;var bi
  FA AR, THIS, 0
  LD q R1, AR
  MOV THIS, R1
  ENTER 0
  LD d R0, [BP, 8]
  CDQ RT, R0
  LEAVE 0
  ;var DEC
  POP R2
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R3, RT
  CMP q R0, R3
  EQ R0
  JNZ .BB6
  JZ .BB7

.BB4:

  ;OT at 124:16
  LDI32 R1, 0x2D
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var SYMB
  PUSH R1
  ;var bi
  FA AR, THIS, 0
  LD q R0, AR
  MOV THIS, R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV OUT, R0
  LDI32 RT, 0
  LEAVE 0
  ;var SYMB
  POP R1
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R2, RT

  ;OT at 125:18
  ;var temp
  LD q R0, [BP, -24]
  NEG q R0
  ;var temp
  ST q R0, [BP, -24]
  JMP .BB3

.BB5:

  ;OT at 145:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB14

.BB6:

  ;OT at 129:16
  LDI32 R1, 0x30
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var SYMB
  PUSH R1
  ;var bi
  FA AR, THIS, 0
  LD q R0, AR
  MOV THIS, R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV OUT, R0
  LDI32 RT, 0
  LEAVE 0
  ;var SYMB
  POP R1
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R2, RT
  JMP .BB5

.BB7:

  ;OT at 131:17
  LDI32 R0, 0
  ;var index
  ST d R0, [BP, -8]
  JMP .BB8

.BB8:

  ;OT at 133:25
  ;var temp
  LD q R0, [BP, -24]
  LDI32 R2, 0
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var DEC
  PUSH R2
  ;var bi
  FA AR, THIS, 0
  LD q R1, AR
  MOV THIS, R1
  ENTER 0
  LD d R0, [BP, 8]
  CDQ RT, R0
  LEAVE 0
  ;var DEC
  POP R2
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R3, RT
  CMP q R0, R3
  GR R0
  JNZ .BB10
  JZ .BB9

.BB9:

  ;OT at 139:19
  ;var index
  LD d R0, [BP, -8]
  LDI32 R1, 1
  SUB d R0, R1
  ;var index
  ST d R0, [BP, -8]
  JMP .BB11

.BB10:

  ;OT at 134:31
  ;var buffer
  LD q R1, [BP, -16]
  ;var index
  LD d R2, [BP, -8]
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  ;var temp
  LD q R3, [BP, -24]
  LDI32 R5, 10
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var DEC
  PUSH R5
  ;var bi
  FA AR, THIS, 0
  LD q R4, AR
  MOV THIS, R4
  ENTER 0
  LD d R0, [BP, 8]
  CDQ RT, R0
  LEAVE 0
  ;var DEC
  POP R5
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R6, RT
  MOD q R3, R6
  LDI32 R7, 48
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var HEX
  PUSH R7
  ;var bi
  FA AR, THIS, 0
  LD q R6, AR
  MOV THIS, R6
  ENTER 0
  LD d R0, [BP, 8]
  CDQ RT, R0
  LEAVE 0
  ;var HEX
  POP R7
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV N0, RT
  OR q R3, N0
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var %
  PUSH R3
  ;var bi
  FA AR, THIS, 0
  LD q R2, AR
  MOV THIS, R2
  ENTER 0
  LD q R0, [BP, 8]
  MOVT d RT, R0
  LEAVE 0
  ;var %
  POP R3
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV N0, RT
  ST q N0, R1

  ;OT at 135:23
  ;var index
  LD d R0, [BP, -8]
  LDI32 R1, 1
  ADD d R0, R1
  ;var index
  ST d R0, [BP, -8]

  ;OT at 136:22
  ;var temp
  LD q R0, [BP, -24]
  LDI32 R2, 10
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var DEC
  PUSH R2
  ;var bi
  FA AR, THIS, 0
  LD q R1, AR
  MOV THIS, R1
  ENTER 0
  LD d R0, [BP, 8]
  CDQ RT, R0
  LEAVE 0
  ;var DEC
  POP R2
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R3, RT
  DIV q R0, R3
  ;var temp
  ST q R0, [BP, -24]
  JMP .BB8

.BB11:

  ;OT at 140:26
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

  ;OT at 141:20
  ;var buffer
  LD q R1, [BP, -16]
  ;var index
  LD d R2, [BP, -8]
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LD q R1, R1
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var read
  PUSH R1
  ;var bi
  FA AR, THIS, 0
  LD q R0, AR
  MOV THIS, R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV OUT, R0
  LDI32 RT, 0
  LEAVE 0
  ;var read
  POP R1
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R2, RT

  ;OT at 142:23
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

IO_printlnInt:

.BB0:
  ENTER 0
.BB1:

  ;OT at 113:9
  ;var num
  LD d R0, [BP, 16]
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var num
  PUSH R0
  CALL IO_printInt
  ;var num
  POP R0
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R1, RT

  ;OT at 114:9
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  CALL IO_println
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R0, RT

  ;OT at 115:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO_printInt:

.BB0:
  ENTER 3
.BB1:

  ;OT at 0:1
  ;var intBuffer
  FA AR, THIS, 8
  LD d R0, AR
  ;var buffer
  ST q R0, [BP, -16]

  ;OT at 86:13
  ;var num
  LD d R0, [BP, 16]
  ;var temp
  ST d R0, [BP, -24]
  JMP .BB2

.BB2:

  ;OT at 87:18
  ;var temp
  LD d R0, [BP, -24]
  LDI32 R1, 0
  CMP d R0, R1
  LE R0
  JNZ .BB4
  JZ .BB3

.BB3:

  ;OT at 92:18
  ;var temp
  LD d R0, [BP, -24]
  LDI32 R1, 0
  CMP d R0, R1
  EQ R0
  JNZ .BB6
  JZ .BB7

.BB4:

  ;OT at 88:16
  LDI32 R1, 0x2D
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var SYMB
  PUSH R1
  ;var bi
  FA AR, THIS, 0
  LD q R0, AR
  MOV THIS, R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV OUT, R0
  LDI32 RT, 0
  LEAVE 0
  ;var SYMB
  POP R1
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R2, RT

  ;OT at 89:18
  ;var temp
  LD d R0, [BP, -24]
  NEG d R0
  ;var temp
  ST d R0, [BP, -24]
  JMP .BB3

.BB5:

  ;OT at 109:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB14

.BB6:

  ;OT at 93:16
  LDI32 R1, 0x30
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var SYMB
  PUSH R1
  ;var bi
  FA AR, THIS, 0
  LD q R0, AR
  MOV THIS, R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV OUT, R0
  LDI32 RT, 0
  LEAVE 0
  ;var SYMB
  POP R1
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R2, RT
  JMP .BB5

.BB7:

  ;OT at 95:17
  LDI32 R0, 0
  ;var index
  ST d R0, [BP, -8]
  JMP .BB8

.BB8:

  ;OT at 97:25
  ;var temp
  LD d R0, [BP, -24]
  LDI32 R1, 0
  CMP d R0, R1
  GR R0
  JNZ .BB10
  JZ .BB9

.BB9:

  ;OT at 103:19
  ;var index
  LD d R0, [BP, -8]
  LDI32 R1, 1
  SUB d R0, R1
  ;var index
  ST d R0, [BP, -8]
  JMP .BB11

.BB10:

  ;OT at 98:31
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

  ;OT at 99:23
  ;var index
  LD d R0, [BP, -8]
  LDI32 R1, 1
  ADD d R0, R1
  ;var index
  ST d R0, [BP, -8]

  ;OT at 100:22
  ;var temp
  LD d R0, [BP, -24]
  LDI32 R1, 10
  DIV d R0, R1
  ;var temp
  ST d R0, [BP, -24]
  JMP .BB8

.BB11:

  ;OT at 104:26
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

  ;OT at 105:20
  ;var buffer
  LD q R1, [BP, -16]
  ;var index
  LD d R2, [BP, -8]
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LD q R1, R1
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var read
  PUSH R1
  ;var bi
  FA AR, THIS, 0
  LD q R0, AR
  MOV THIS, R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV OUT, R0
  LDI32 RT, 0
  LEAVE 0
  ;var read
  POP R1
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R2, RT

  ;OT at 106:23
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

IO_ulongBufferSize:

.BB0:
  ENTER 0
.BB1:

  ;OT at 79:9
  LDI32 AR, IO_ulongBufferSize_const0
  LDC64 R0, AR
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO_longBufferSize:

.BB0:
  ENTER 0
.BB1:

  ;OT at 75:9
  LDI32 AR, IO_longBufferSize_const0
  LDC64 R0, AR
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO_uintBufferSize:

.BB0:
  ENTER 0
.BB1:

  ;OT at 71:9
  LDI32 AR, IO_uintBufferSize_const0
  LDC64 R0, AR
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO_intBufferSize:

.BB0:
  ENTER 0
.BB1:

  ;OT at 67:9
  LDI32 AR, IO_intBufferSize_const0
  LDC64 R0, AR
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO_printlnString:

.BB0:
  ENTER 0
.BB1:

  ;OT at 61:9
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
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var s
  PUSH R0
  CALL IO_printString
  ;var s
  POP R0
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R1, RT

  ;OT at 62:9
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  CALL IO_println
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R0, RT

  ;OT at 63:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO_printString:

.BB0:
  ENTER 2
.BB1:

  ;OT at 51:13
  LDI32 R0, 0
  ;var i
  ST d R0, [BP, -8]

  ;OT at 52:13
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
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var s
  PUSH R0
  CALL IO_strlength
  ;var s
  POP R0
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
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

  ;OT at 53:18
  ;var i
  LD d R0, [BP, -8]
  ;var l
  LD d R1, [BP, -16]
  CMP d R0, R1
  NEQ R0
  JNZ .BB4
  JZ .BB3

.BB3:

  ;OT at 57:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB5

.BB4:

  ;OT at 54:16
  ;var s
  LD q R1, [BP, 16]
  ;var i
  LD d R2, [BP, -8]
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LDC64 R1, R1
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var read
  PUSH R1
  ;var bi
  FA AR, THIS, 0
  LD q R0, AR
  MOV THIS, R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV OUT, R0
  LDI32 RT, 0
  LEAVE 0
  ;var read
  POP R1
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R2, RT

  ;OT at 55:15
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

IO_printlnChar:

.BB0:
  ENTER 0
.BB1:

  ;OT at 45:9
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
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var toOut
  PUSH R0
  CALL IO_printChar
  ;var toOut
  POP R0
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R1, RT

  ;OT at 46:9
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  CALL IO_println
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R0, RT

  ;OT at 47:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO_printChar:

.BB0:
  ENTER 0
.BB1:

  ;OT at 40:12
  ;var toOut
  LD b R1, [BP, 16]
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var toOut
  PUSH R1
  ;var bi
  FA AR, THIS, 0
  LD q R0, AR
  MOV THIS, R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV OUT, R0
  LDI32 RT, 0
  LEAVE 0
  ;var toOut
  POP R1
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R2, RT

  ;OT at 41:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO_printlnByte:

.BB0:
  ENTER 0
.BB1:

  ;OT at 34:9
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
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var toOut
  PUSH R0
  CALL IO_printByte
  ;var toOut
  POP R0
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R1, RT

  ;OT at 35:9
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  CALL IO_println
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R0, RT

  ;OT at 36:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO_printByte:

.BB0:
  ENTER 0
.BB1:

  ;OT at 29:12
  ;var toOut
  LD b R1, [BP, 16]
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var toOut
  PUSH R1
  ;var bi
  FA AR, THIS, 0
  LD q R0, AR
  MOV THIS, R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV OUT, R0
  LDI32 RT, 0
  LEAVE 0
  ;var toOut
  POP R1
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R2, RT

  ;OT at 30:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO_println:

.BB0:
  ENTER 0
.BB1:

  ;OT at 24:12
  LDI32 R1, 0x0A
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var SYMB
  PUSH R1
  ;var bi
  FA AR, THIS, 0
  LD q R0, AR
  MOV THIS, R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV OUT, R0
  LDI32 RT, 0
  LEAVE 0
  ;var SYMB
  POP R1
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R2, RT

  ;OT at 25:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO_strlength:

.BB0:
  ENTER 1
.BB1:

  ;OT at 13:13
  LDI32 R0, 0
  ;var len
  ST d R0, [BP, -8]
  JMP .BB2

.BB2:

  ;OT at 14:21
  LDI32 R0, 1
  LDI32 R1, 1
  CMP q R0, R1
  EQ R0
  JNZ .BB4
  JZ .BB3

.BB3:

  ;OT at 20:9
  ;var len
  LD d R0, [BP, -8]
  MOV RT, R0
  JMP .BB8

.BB4:
  JMP .BB5

.BB5:

  ;OT at 15:26
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

  ;OT at 18:17
  ;var len
  LD d R0, [BP, -8]
  LDI32 R1, 1
  ADD d R0, R1
  ;var len
  ST d R0, [BP, -8]
  JMP .BB2

.BB7:

  ;OT at 16:17
  JMP .BB3

.BB8:
  LEAVE 1
  RET

IO_IO:

.BB0:
  ENTER 0
.BB1:

  ;OT at 7:12
  PUSH THIS
  LDI32 AR, classInfo_BuiltIn
  MOV THIS, ALR
  NEW AR, 0
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  CALL BuiltIn_BuiltIn
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R0, THIS
  POP THIS
  ;var bi
  FA AR, THIS, 0
  ST q R0, AR

  ;OT at 8:19
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  CALL IO_intBufferSize
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R1, RT
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var intBufferSize
  PUSH R1
  ;var bi
  FA AR, THIS, 0
  LD q R0, AR
  MOV THIS, R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV RT, ALR
  ADD q ALR, R0
  LEAVE 0
  ;var intBufferSize
  POP R1
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R2, RT
  ;var intBuffer
  FA AR, THIS, 8
  ST d R2, AR

  ;OT at 9:20
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  CALL IO_longBufferSize
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R1, RT
  MOV BR1, SP
  PUSH THIS
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var longBufferSize
  PUSH R1
  ;var bi
  FA AR, THIS, 0
  LD q R0, AR
  MOV THIS, R0
  ENTER 0
  LD q R0, [BP, 8]
  MOV RT, ALR
  ADD q ALR, R0
  LEAVE 0
  ;var longBufferSize
  POP R1
  POP N7
  POP N6
  POP N5
  POP N4
  POP N3
  POP N2
  POP N1
  POP N0
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  POP THIS
  MOV R2, RT
  ;var longBuffer
  FA AR, THIS, 16
  ST d R2, AR
  JMP .BB2

.BB2:
  LEAVE 0
  RET

BuiltIn_BuiltIn:

.BB0:
  ENTER 0
.BB1:
  LEAVE 0
  RET

Object_Object:

.BB0:
  ENTER 0
.BB1:
  LEAVE 0
  RET


    [section constantsM]

vtable_Main:
    dq Object_Object
    dq Main_main
    dq Main_Main

classInfo_Main:
    .typeId: dq 0x06
    .superPtr: dq classInfo_Object
    .vtablePtr: dq vtable_Main
    .interfaceCount:
        dq 0x00
    .interfaceIds:
        dq 0x0
    .interfaceImpl:
        dq 0x0

vtable_Circle:
    dq Object_Object
    dq Shape_getName
    dq Circle_area
    dq Shape_Shape
    dq Circle_Circle

classInfo_Circle:
    .typeId: dq 0x05
    .superPtr: dq classInfo_Shape
    .vtablePtr: dq vtable_Circle
    .interfaceCount:
        dq 0x00
    .interfaceIds:
        dq 0x0
    .interfaceImpl:
        dq 0x0

vtable_Rectangle:
    dq Object_Object
    dq Shape_getName
    dq Rectangle_area
    dq Shape_Shape
    dq Rectangle_Rectangle

classInfo_Rectangle:
    .typeId: dq 0x04
    .superPtr: dq classInfo_Shape
    .vtablePtr: dq vtable_Rectangle
    .interfaceCount:
        dq 0x00
    .interfaceIds:
        dq 0x0
    .interfaceImpl:
        dq 0x0

vtable_Shape:
    dq Object_Object
    dq Shape_getName
    dq Shape_area
    dq Shape_Shape

classInfo_Shape:
    .typeId: dq 0x03
    .superPtr: dq classInfo_Object
    .vtablePtr: dq vtable_Shape
    .interfaceCount:
        dq 0x00
    .interfaceIds:
        dq 0x0
    .interfaceImpl:
        dq 0x0

vtable_IO:
    dq Object_Object
    dq IO_printlnLong
    dq IO_printLong
    dq IO_printlnInt
    dq IO_printInt
    dq IO_ulongBufferSize
    dq IO_longBufferSize
    dq IO_uintBufferSize
    dq IO_intBufferSize
    dq IO_printlnString
    dq IO_printString
    dq IO_printlnChar
    dq IO_printChar
    dq IO_printlnByte
    dq IO_printByte
    dq IO_println
    dq IO_strlength
    dq IO_IO

classInfo_IO:
    .typeId: dq 0x02
    .superPtr: dq classInfo_Object
    .vtablePtr: dq vtable_IO
    .interfaceCount:
        dq 0x00
    .interfaceIds:
        dq 0x0
    .interfaceImpl:
        dq 0x0

vtable_BuiltIn:
    dq Object_Object
    dq BuiltIn_BuiltIn

classInfo_BuiltIn:
    .typeId: dq 0x01
    .superPtr: dq classInfo_Object
    .vtablePtr: dq vtable_BuiltIn
    .interfaceCount:
        dq 0x00
    .interfaceIds:
        dq 0x0
    .interfaceImpl:
        dq 0x0

vtable_Object:
    dq Object_Object

classInfo_Object:
    .typeId: dq 0x00
    .superPtr: dq classInfo_Object
    .vtablePtr: dq vtable_Object
    .interfaceCount:
        dq 0x00
    .interfaceIds:
        dq 0x0
    .interfaceImpl:
        dq 0x0


Circle_Circle_const0:
  dq 0x43
  dq 0x69
  dq 0x72
  dq 0x63
  dq 0x6C
  dq 0x65
  dq 0x00
Rectangle_Rectangle_const0:
  dq 0x52
  dq 0x65
  dq 0x63
  dq 0x74
  dq 0x61
  dq 0x6E
  dq 0x67
  dq 0x6C
  dq 0x65
  dq 0x00
IO_ulongBufferSize_const0:
  dq 152

IO_longBufferSize_const0:
  dq 152

IO_uintBufferSize_const0:
  dq 80

IO_intBufferSize_const0:
  dq 80
