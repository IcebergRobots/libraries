@echo OFF
color 09

echo ICEBERG ROBOTS
echo --------------
echo Time: %TIME%
echo copying new libraries to Computer %COMPUTERNAME%...
echo from %cd% to %HOMEPATH%\Documents\Arduino\libraries
echo --------------
ROBOCOPY %cd%\ %HOMEPATH%\Documents\Arduino\libraries\ /S >nul
echo Time: %TIME%
echo finished with exitcode %ERRORLEVEL%
echo And just for fun a random Number: %RANDOM%
echo --------------
ECHO Open libraries Folder? (y/n)
SET /p wahl=
if '%wahl%' == 'y' goto yes
Goto End
:yes
echo All right, here is the folder. Bye!
explorer %HOMEPATH%\Documents\Arduino\libraries
TIMEOUT /T 3
:End

