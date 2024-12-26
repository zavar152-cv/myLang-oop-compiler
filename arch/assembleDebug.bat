@echo off
setlocal EnableDelayedExpansion	
set Portable.RemoteTasks.Manager.Login=u314935
set Portable.RemoteTasks.Manager.Password=f8c8299c-e2ae-4a32-b4bc-8115eef62291
set defFile=myArch.target.pdsl
set archName=myArch
set asmListing=src/custom.asm
set stdoutRegStName=OUT_S
set stdinRegStName=IN_S
echo %Portable.RemoteTasks.Manager.Login%
echo %Portable.RemoteTasks.Manager.Password%
echo !archName!

Portable.RemoteTasks.Manager.exe -w -id -s AssembleDebug asmListing !asmListing! definitionFile !defFile! archName !archName! sourcesDir src stdoutRegStName !stdoutRegStName! stdinRegStName !stdinRegStName! > tmp.txt
		
		for /F %%i in (tmp.txt) do set id=%%i
		echo TaskID: !id!

		echo. 
		echo RESULTS:
		Portable.RemoteTasks.Manager.exe -g !id!
		Portable.RemoteTasks.Manager.exe -g !id! -r out.ptptb > binary.ptptb
		echo. 