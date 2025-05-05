    [section codeM]

  LDI32 AR, classInfo_MyClass
  MOV THIS, ALR
  NEW AR, 4
  JMP MyClass_main
A_doSomething5:

.BB0:
  ENTER 0
.BB1:

  ;OT at 86:9
  LDI32 R0, 5
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

A_doSomething:

.BB0:
  ENTER 0
.BB1:

  ;OT at 82:9
  LDI32 R0, 1
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

A_A:

.BB0:
  ENTER 0
.BB1:
  LEAVE 0
  RET

MegaBaseClass_MegaBaseClass:

.BB0:
  ENTER 0
.BB1:
  LEAVE 0
  RET

BaseClass_parentMethod2:

.BB0:
  ENTER 0
.BB1:

  ;OT at 63:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

BaseClass_BaseClass:

.BB0:
  ENTER 0
.BB1:
  LEAVE 0
  RET

MyClass_doSomething5:

.BB0:
  ENTER 0
.BB1:

  ;OT at 53:9
  LDI32 R0, 8
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

MyClass_doSomething:

.BB0:
  ENTER 0
.BB1:

  ;OT at 49:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

MyClass_parentMethod2:

.BB0:
  ENTER 0
.BB1:

  ;OT at 45:9
  LDI32 R0, 1
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

MyClass_parentMethod:

.BB0:
  ENTER 0
.BB1:

  ;OT at 41:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

MyClass_testMethod:

.BB0:
  ENTER 0
.BB1:

  ;OT at 37:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

MyClass_myMethod:

.BB0:
  ENTER 2
.BB1:

  ;OT at 17:13
  LDI32 R0, 9
  ;var a
  ST d R0, [BP, -8]

  ;OT at 18:17
  LDI32 R0, 1
  LDI32 R1, 2
  PUSH THIS
  LDI32 AR, classInfo_MyClass
  MOV THIS, ALR
  NEW AR, 4
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
  PUSH R1
  ;var DEC
  PUSH R0
  CALL MyClass_MyClass
  ;var DEC
  POP R0
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
  MOV R2, THIS
  POP THIS
  ;var instance
  ST q R2, [BP, -16]

  ;OT at 19:17
  LDI32 R0, 7
  ;var myField
  FA AR, THIS, 0
  ST d R0, AR

  ;OT at 20:18
  LDI32 R0, 1
  ;var myField2
  FA AR, THIS, 8
  ST d R0, AR

  ;OT at 21:17
  ;var myField2
  FA AR, THIS, 8
  LD d R0, AR
  ;var myField
  FA AR, THIS, 0
  ST d R0, AR

  ;OT at 22:27
  LDI32 R1, 5
  LDI32 R2, 5
  PUSH THIS
  LDI32 AR, classInfo_MyClass
  MOV THIS, ALR
  NEW AR, 4
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
  ;var DEC
  PUSH R1
  CALL MyClass_MyClass
  ;var DEC
  POP R1
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
  ;var instance
  LD q R0, [BP, -16]
  FA R0, R0, 16
  ST q R3, R0

  ;OT at 23:35
  LDI32 R1, 78
  ;var instance
  LD q R0, [BP, -16]
  LDF q R0, R0, 16
  FA R0, R0, 0
  ST q R1, R0

  ;OT at 33:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 2
  RET

main:
MyClass_main:

.BB0:
  ENTER 0
.BB1:

  ;OT at 12:9
  LDI32 R0, 1
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
  PUSH R0
  CALL MyClass_myMethod
  ;var DEC
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

  ;OT at 13:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  HLT

MyClass_MyClass:

.BB0:
  ENTER 0
.BB1:

  ;OT at 8:17
  ;var a
  LD d R0, [BP, 16]
  ;var b
  LD d R1, [BP, 24]
  ADD d R0, R1
  ;var myField
  FA AR, THIS, 0
  ST d R0, AR
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO_printlnLong:

.BB0:
  ENTER 0
.BB1:

  ;OT at 145:9
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
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var bufferRef
  PUSH R1
  ;var num
  PUSH R0
  CALL IO_printLong
  ;var num
  POP R0
  ;var bufferRef
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
  MOV R2, RT

  ;OT at 146:9
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

  ;OT at 147:9
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
  ;var bufferRef
  LD q R0, [BP, 24]
  ;var buffer
  ST q R0, [BP, -16]

  ;OT at 117:14
  ;var num
  LD q R0, [BP, 16]
  ;var temp
  ST q R0, [BP, -24]
  JMP .BB2

.BB2:

  ;OT at 119:18
  ;var temp
  LD q R0, [BP, -24]
  LDI32 R2, 0
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
  MOV R3, RT
  CMP q R0, R3
  LE R0
  JNZ .BB4
  JZ .BB3

.BB3:

  ;OT at 124:18
  ;var temp
  LD q R0, [BP, -24]
  LDI32 R2, 0
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
  MOV R3, RT
  CMP q R0, R3
  EQ R0
  JNZ .BB6
  JZ .BB7

.BB4:

  ;OT at 120:16
  LDI32 R1, 0x2D
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
  ;var SYMB
  PUSH R1
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
  MOV R2, RT

  ;OT at 121:18
  ;var temp
  LD q R0, [BP, -24]
  NEG q R0
  ;var temp
  ST q R0, [BP, -24]
  JMP .BB3

.BB5:

  ;OT at 141:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB14

.BB6:

  ;OT at 125:16
  LDI32 R1, 0x30
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
  ;var SYMB
  PUSH R1
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
  MOV R2, RT
  JMP .BB5

.BB7:

  ;OT at 127:17
  LDI32 R0, 0
  ;var index
  ST d R0, [BP, -8]
  JMP .BB8

.BB8:

  ;OT at 129:25
  ;var temp
  LD q R0, [BP, -24]
  LDI32 R2, 0
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
  MOV R3, RT
  CMP q R0, R3
  GR R0
  JNZ .BB10
  JZ .BB9

.BB9:

  ;OT at 135:19
  ;var index
  LD d R0, [BP, -8]
  LDI32 R1, 1
  SUB d R0, R1
  ;var index
  ST d R0, [BP, -8]
  JMP .BB11

.BB10:

  ;OT at 130:31
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
  MOV R6, RT
  MOD q R3, R6
  LDI32 R7, 48
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
  ;var HEX
  PUSH R7
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
  MOV N0, RT
  OR q R3, N0
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
  ;var %
  PUSH R3
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
  MOV N0, RT
  ST q N0, R1

  ;OT at 131:23
  ;var index
  LD d R0, [BP, -8]
  LDI32 R1, 1
  ADD d R0, R1
  ;var index
  ST d R0, [BP, -8]

  ;OT at 132:22
  ;var temp
  LD q R0, [BP, -24]
  LDI32 R2, 10
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
  MOV R3, RT
  DIV q R0, R3
  ;var temp
  ST q R0, [BP, -24]
  JMP .BB8

.BB11:

  ;OT at 136:26
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

  ;OT at 137:20
  ;var buffer
  LD q R1, [BP, -16]
  ;var index
  LD d R2, [BP, -8]
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LD q R1, R1
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
  ;var read
  PUSH R1
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
  MOV R2, RT

  ;OT at 138:23
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

  ;OT at 109:9
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
  PUSH N0
  PUSH N1
  PUSH N2
  PUSH N3
  PUSH N4
  PUSH N5
  PUSH N6
  PUSH N7
  ;var bufferRef
  PUSH R1
  ;var num
  PUSH R0
  CALL IO_printInt
  ;var num
  POP R0
  ;var bufferRef
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
  MOV R2, RT

  ;OT at 110:9
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

  ;OT at 111:9
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
  ;var bufferRef
  LD d R0, [BP, 24]
  ;var buffer
  ST q R0, [BP, -16]

  ;OT at 82:13
  ;var num
  LD d R0, [BP, 16]
  ;var temp
  ST d R0, [BP, -24]
  JMP .BB2

.BB2:

  ;OT at 83:18
  ;var temp
  LD d R0, [BP, -24]
  LDI32 R1, 0
  CMP d R0, R1
  LE R0
  JNZ .BB4
  JZ .BB3

.BB3:

  ;OT at 88:18
  ;var temp
  LD d R0, [BP, -24]
  LDI32 R1, 0
  CMP d R0, R1
  EQ R0
  JNZ .BB6
  JZ .BB7

.BB4:

  ;OT at 84:16
  LDI32 R1, 0x2D
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
  ;var SYMB
  PUSH R1
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
  MOV R2, RT

  ;OT at 85:18
  ;var temp
  LD d R0, [BP, -24]
  NEG d R0
  ;var temp
  ST d R0, [BP, -24]
  JMP .BB3

.BB5:

  ;OT at 105:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB14

.BB6:

  ;OT at 89:16
  LDI32 R1, 0x30
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
  ;var SYMB
  PUSH R1
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
  MOV R2, RT
  JMP .BB5

.BB7:

  ;OT at 91:17
  LDI32 R0, 0
  ;var index
  ST d R0, [BP, -8]
  JMP .BB8

.BB8:

  ;OT at 93:25
  ;var temp
  LD d R0, [BP, -24]
  LDI32 R1, 0
  CMP d R0, R1
  GR R0
  JNZ .BB10
  JZ .BB9

.BB9:

  ;OT at 99:19
  ;var index
  LD d R0, [BP, -8]
  LDI32 R1, 1
  SUB d R0, R1
  ;var index
  ST d R0, [BP, -8]
  JMP .BB11

.BB10:

  ;OT at 94:31
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

  ;OT at 95:23
  ;var index
  LD d R0, [BP, -8]
  LDI32 R1, 1
  ADD d R0, R1
  ;var index
  ST d R0, [BP, -8]

  ;OT at 96:22
  ;var temp
  LD d R0, [BP, -24]
  LDI32 R1, 10
  DIV d R0, R1
  ;var temp
  ST d R0, [BP, -24]
  JMP .BB8

.BB11:

  ;OT at 100:26
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

  ;OT at 101:20
  ;var buffer
  LD q R1, [BP, -16]
  ;var index
  LD d R2, [BP, -8]
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LD q R1, R1
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
  ;var read
  PUSH R1
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
  MOV R2, RT

  ;OT at 102:23
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

  ;OT at 75:9
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

  ;OT at 71:9
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

  ;OT at 67:9
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

  ;OT at 63:9
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

  ;OT at 57:9
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

  ;OT at 58:9
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

  ;OT at 59:9
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

  ;OT at 47:13
  LDI32 R0, 0
  ;var i
  ST d R0, [BP, -8]

  ;OT at 48:13
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

  ;OT at 49:18
  ;var i
  LD d R0, [BP, -8]
  ;var l
  LD d R1, [BP, -16]
  CMP d R0, R1
  NEQ R0
  JNZ .BB4
  JZ .BB3

.BB3:

  ;OT at 53:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB5

.BB4:

  ;OT at 50:16
  ;var s
  LD q R1, [BP, 16]
  ;var i
  LD d R2, [BP, -8]
  LDI32 BR2, 8
  MUL q R2, BR2
  ADD q R1, R2
  LDC64 R1, R1
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
  ;var read
  PUSH R1
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
  MOV R2, RT

  ;OT at 51:15
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

  ;OT at 41:9
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

  ;OT at 42:9
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

  ;OT at 43:9
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

  ;OT at 36:12
  ;var toOut
  LD b R1, [BP, 16]
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
  PUSH R1
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
  MOV R2, RT

  ;OT at 37:9
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

  ;OT at 30:9
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

  ;OT at 31:9
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

  ;OT at 32:9
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

  ;OT at 25:12
  ;var toOut
  LD b R1, [BP, 16]
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
  PUSH R1
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
  MOV R2, RT

  ;OT at 26:9
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

  ;OT at 20:12
  LDI32 R1, 0x0A
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
  ;var SYMB
  PUSH R1
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
  MOV R2, RT

  ;OT at 21:9
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

  ;OT at 9:13
  LDI32 R0, 0
  ;var len
  ST d R0, [BP, -8]
  JMP .BB2

.BB2:

  ;OT at 10:21
  LDI32 R0, 1
  LDI32 R1, 1
  CMP q R0, R1
  EQ R0
  JNZ .BB4
  JZ .BB3

.BB3:

  ;OT at 16:9
  ;var len
  LD d R0, [BP, -8]
  MOV RT, R0
  JMP .BB8

.BB4:
  JMP .BB5

.BB5:

  ;OT at 11:26
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

  ;OT at 14:17
  ;var len
  LD d R0, [BP, -8]
  LDI32 R1, 1
  ADD d R0, R1
  ;var len
  ST d R0, [BP, -8]
  JMP .BB2

.BB7:

  ;OT at 12:17
  JMP .BB3

.BB8:
  LEAVE 1
  RET

IO_IO:

.BB0:
  ENTER 0
.BB1:

  ;OT at 5:12
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

vtable_A:
    dq Object_Object
    dq A_doSomething5
    dq A_doSomething
    dq A_A

itable_Interface1_A:
    dq A_doSomething5
    dq A_doSomething


classInfo_A:
    .typeId: dq 0x06
    .superPtr: dq classInfo_Object
    .vtablePtr: dq vtable_A
    .interfaceCount:
        dq 0x01
    .interfaceIds:
        dq 0x08
    .interfaceImpl:
        dq itable_Interface1_A

vtable_MegaBaseClass:
    dq Object_Object
    dq MegaBaseClass_MegaBaseClass

classInfo_MegaBaseClass:
    .typeId: dq 0x05
    .superPtr: dq classInfo_Object
    .vtablePtr: dq vtable_MegaBaseClass
    .interfaceCount:
        dq 0x00
    .interfaceIds:
        dq 0x0
    .interfaceImpl:
        dq 0x0

vtable_BaseClass:
    dq Object_Object
    dq MegaBaseClass_MegaBaseClass
    dq BaseClass_parentMethod2
    dq BaseClass_BaseClass

classInfo_BaseClass:
    .typeId: dq 0x04
    .superPtr: dq classInfo_MegaBaseClass
    .vtablePtr: dq vtable_BaseClass
    .interfaceCount:
        dq 0x00
    .interfaceIds:
        dq 0x0
    .interfaceImpl:
        dq 0x0

vtable_MyClass:
    dq Object_Object
    dq MegaBaseClass_MegaBaseClass
    dq MyClass_parentMethod2
    dq BaseClass_BaseClass
    dq MyClass_doSomething5
    dq MyClass_doSomething
    dq MyClass_parentMethod
    dq MyClass_testMethod
    dq MyClass_myMethod
    dq MyClass_main
    dq MyClass_MyClass

itable_Interface1_MyClass:
    dq MyClass_doSomething5
    dq MyClass_doSomething

itable_Interface2_MyClass:


classInfo_MyClass:
    .typeId: dq 0x03
    .superPtr: dq classInfo_BaseClass
    .vtablePtr: dq vtable_MyClass
    .interfaceCount:
        dq 0x02
    .interfaceIds:
        dq 0x08
        dq 0x09
    .interfaceImpl:
        dq itable_Interface1_MyClass
        dq itable_Interface2_MyClass

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


IO_ulongBufferSize_const0:
  dq 19

IO_longBufferSize_const0:
  dq 19

IO_uintBufferSize_const0:
  dq 10

IO_intBufferSize_const0:
  dq 10
