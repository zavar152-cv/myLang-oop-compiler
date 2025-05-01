
    [section constantsM]

vtable_A:
    dq Object.Object
    dq A.A

vtable_MegaBaseClass:
    dq Object.Object
    dq MegaBaseClass.MegaBaseClass

vtable_BaseClass:
    dq Object.Object
    dq MegaBaseClass.MegaBaseClass
    dq BaseClass.parentMethod2
    dq BaseClass.BaseClass

vtable_MyClass:
    dq Object.Object
    dq MegaBaseClass.MegaBaseClass
    dq MyClass.parentMethod2
    dq BaseClass.BaseClass
    dq MyClass.doSomething
    dq MyClass.parentMethod
    dq MyClass.testMethod
    dq MyClass.myMethod
    dq MyClass.MyClass

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

vtable_Object:
    dq Object.Object

