    [section codeM]

A.doSomething5:

.BB0:
  ENTER 0
.BB1:

  ;OT at 77:9
  LDI32 R0, 5
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

A.doSomething:

.BB0:
  ENTER 0
.BB1:

  ;OT at 73:9
  LDI32 R0, 1
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

A.A:

.BB0:
  ENTER 0
.BB1:
  LEAVE 0
  RET

MegaBaseClass.MegaBaseClass:

.BB0:
  ENTER 0
.BB1:
  LEAVE 0
  RET

BaseClass.parentMethod2:

.BB0:
  ENTER 0
.BB1:

  ;OT at 54:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

BaseClass.BaseClass:

.BB0:
  ENTER 0
.BB1:
  LEAVE 0
  RET

MyClass.doSomething5:

.BB0:
  ENTER 0
.BB1:

  ;OT at 44:9
  LDI32 R0, 8
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

MyClass.doSomething:

.BB0:
  ENTER 0
.BB1:

  ;OT at 40:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

MyClass.parentMethod2:

.BB0:
  ENTER 0
.BB1:

  ;OT at 36:9
  LDI32 R0, 1
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

MyClass.parentMethod:

.BB0:
  ENTER 0
.BB1:

  ;OT at 32:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

MyClass.testMethod:

.BB0:
  ENTER 0
.BB1:

  ;OT at 28:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

MyClass.myMethod:

.BB0:
  ENTER 2
.BB1:

  ;OT at 12:13
  LDI32 R0, 9
  ;var a
  ST d R0, [BP, -8]

  ;OT at 13:17
  ;var instance
  ST q , [BP, -16]

  ;OT at 17:9
  MOV BR1, SP
  PUSH R0
  PUSH R1
  PUSH R2
  PUSH R3
  PUSH R4
  PUSH R5
  PUSH R6
  PUSH R7
  CALL testMethod
  POP R7
  POP R6
  POP R5
  POP R4
  POP R3
  POP R2
  POP R1
  POP R0
  MOV R0, RT

  ;OT at 19:27
  LDI32 R0, 5
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
  CALL method
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

  ;OT at 21:9
  LDI32 AR, MyClass.myMethod_const0
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
  CALL parentMethod
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

  ;OT at 22:9
  LDI32 AR, MyClass.myMethod_const0
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
  CALL parentMethod2
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

  ;OT at 24:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 2
  RET

MyClass.MyClass:

.BB0:
  ENTER 0
.BB1:

  ;OT at 8:17
  ;var a
  LD d R0, [BP, 16]
  ;var b
  LD d R1, [BP, 24]
  ADD d R0, R1
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO.printlnLong:

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

  ;OT at 147:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO.printLong:

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
  CALL method
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

  ;OT at 124:18
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
  CALL method
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

  ;OT at 120:16
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
  CALL method
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
  CALL method
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

  ;OT at 127:17
  LDI32 R0, 0
  ;var index
  ST d R0, [BP, -8]
  JMP .BB8

.BB8:

  ;OT at 129:25
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
  CALL method
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
  CALL method
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
  CALL method
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
  CALL method
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
  CALL method
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
  CALL method
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

IO.printlnInt:

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

  ;OT at 111:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO.printInt:

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
  CALL method
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
  CALL method
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
  CALL method
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

IO.ulongBufferSize:

.BB0:
  ENTER 0
.BB1:

  ;OT at 75:9
  LDI32 AR, IO.ulongBufferSize_const0
  LDC64 R0, AR
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO.longBufferSize:

.BB0:
  ENTER 0
.BB1:

  ;OT at 71:9
  LDI32 AR, IO.longBufferSize_const0
  LDC64 R0, AR
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO.uintBufferSize:

.BB0:
  ENTER 0
.BB1:

  ;OT at 67:9
  LDI32 AR, IO.uintBufferSize_const0
  LDC64 R0, AR
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO.intBufferSize:

.BB0:
  ENTER 0
.BB1:

  ;OT at 63:9
  LDI32 AR, IO.intBufferSize_const0
  LDC64 R0, AR
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO.printlnString:

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

  ;OT at 59:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO.printString:

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
  CALL method
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

IO.printlnChar:

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

  ;OT at 43:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO.printChar:

.BB0:
  ENTER 0
.BB1:

  ;OT at 36:12
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
  CALL method
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

  ;OT at 37:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO.printlnByte:

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

  ;OT at 32:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO.printByte:

.BB0:
  ENTER 0
.BB1:

  ;OT at 25:12
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
  CALL method
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

  ;OT at 26:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO.println:

.BB0:
  ENTER 0
.BB1:

  ;OT at 20:12
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
  CALL method
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

  ;OT at 21:9
  LDI32 R0, 0
  MOV RT, R0
  JMP .BB2

.BB2:
  LEAVE 0
  RET

IO.strlength:

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

IO.IO:

.BB0:
  ENTER 0
.BB1:

  ;OT at 5:12
  JMP .BB2

.BB2:
  LEAVE 0
  RET

BuiltIn.BuiltIn:

.BB0:
  ENTER 0
.BB1:
  LEAVE 0
  RET


    [section constantsM]

vtable_A:
    dq Object.Object
    dq A.doSomething5
    dq A.doSomething
    dq A.A

itable_Interface1_A:
    dq A.doSomething5
    dq A.doSomething


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
    dq Object.Object
    dq MegaBaseClass.MegaBaseClass

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
    dq Object.Object
    dq MegaBaseClass.MegaBaseClass
    dq BaseClass.parentMethod2
    dq BaseClass.BaseClass

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
    dq Object.Object
    dq MegaBaseClass.MegaBaseClass
    dq MyClass.parentMethod2
    dq BaseClass.BaseClass
    dq MyClass.doSomething5
    dq MyClass.doSomething
    dq MyClass.parentMethod
    dq MyClass.testMethod
    dq MyClass.myMethod
    dq MyClass.MyClass

itable_Interface1_MyClass:
    dq MyClass.doSomething5
    dq MyClass.doSomething

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
    dq Object.Object
    dq IO.printlnLong
    dq IO.printLong
    dq IO.printlnInt
    dq IO.printInt
    dq IO.ulongBufferSize
    dq IO.longBufferSize
    dq IO.uintBufferSize
    dq IO.intBufferSize
    dq IO.printlnString
    dq IO.printString
    dq IO.printlnChar
    dq IO.printChar
    dq IO.printlnByte
    dq IO.printByte
    dq IO.println
    dq IO.strlength
    dq IO.IO

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
    dq Object.Object
    dq BuiltIn.__lastSP
    dq BuiltIn.__lastALR
    dq BuiltIn.__writeChar
    dq BuiltIn.__write
    dq BuiltIn.__readChar
    dq BuiltIn.__read
    dq BuiltIn.__cmpRef
    dq BuiltIn.__allocRef
    dq BuiltIn.__toUlongFromLong
    dq BuiltIn.__toUlongFromUint
    dq BuiltIn.__toUlongFromInt
    dq BuiltIn.__toUlongFromByte
    dq BuiltIn.__toLongFromUlong
    dq BuiltIn.__toLongFromUint
    dq BuiltIn.__toLongFromInt
    dq BuiltIn.__toLongFromByte
    dq BuiltIn.__toUintFromUlong
    dq BuiltIn.__toUintFromLong
    dq BuiltIn.__toUintFromInt
    dq BuiltIn.__toUintFromByte
    dq BuiltIn.__toIntFromUlong
    dq BuiltIn.__toIntFromLong
    dq BuiltIn.__toIntFromUint
    dq BuiltIn.__toIntFromByte
    dq BuiltIn.__toByteFromUlong
    dq BuiltIn.__toByteFromLong
    dq BuiltIn.__toByteFromUint
    dq BuiltIn.__toByteFromInt
    dq BuiltIn.BuiltIn

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
    dq Object.Object

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


MyClass.myMethod_const0:
  dq 5

IO.ulongBufferSize_const0:
  dq 19

IO.longBufferSize_const0:
  dq 19

IO.uintBufferSize_const0:
  dq 10

IO.intBufferSize_const0:
  dq 10
