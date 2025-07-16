    [section codeM]

main:

    LDI32 R0, 1
    ADD q R0, R0
    LDI32 R0, obj2
    LDI32 R2, obj
    LDF q R1, R2, 24
    ;MCALL R0, 16
    LDI32 IID, 3
    ICALL R0, 8

    LDI32 AR, classInfo_BaseClass
    MOV THIS, ALR
    NEW AR, 4

    LDI32 R4, 25
    STF q R4, THIS, 24
    LDF q R5, THIS, 24

    HLT

func:
    LDI32 R1, 2
    ADD q R1, R1
    RET

func2:
    LDI32 R1, 2
    ADD q R1, R1
    RET

func3:
    LDI32 R1, 2
    ADD q R1, R1
    RET

func4:
    LDI32 R1, 2
    ADD q R1, R1
    RET

func5:
    LDI32 R1, 2
    ADD q R1, R1
    RET

    [section dataM]
obj:
    dq classInfo_BaseClass ;0
    dq 0x1 ;8
    dq 0x2 ;16
    dq 0x3 ;24
    dq 0x4 ;32
obj2:
    dq classInfo_BaseClass ;0

; TODO checkcast

    [section constantsM]

classInfo_Object:
    .typeId: dq 0x00
    .superPtr: dq 0x0
    .vtablePtr: dq vtable_Object
    .interfaceCount: 
        dq 0x0
    .interfaceIds: 
        dq 0x0
    .interfaceImpl:
        dq 0x0

classInfo_BaseClass:
    .typeId: dq 0x01
    .superPtr: dq classInfo_Object
    .vtablePtr: dq vtable_BaseClass
    .interfaceCount: 
        dq 0x2
    .interfaceIds: 
        dq 0x2
        dq 0x3
    .interfaceImpl:
        dq itable_Interface_BaseClass
        dq itable_Interface2_BaseClass

itable_Interface_BaseClass:
    dq func3
    dq func4

itable_Interface2_BaseClass:
    dq func2
    dq func5

vtable_BaseClass:
    dq func
    dq func2
    dq func3

vtable_Object:
    dq 0x0