@echo off
IF "%~1" == "" GOTO usage
echo.
echo -----------------------------------------------------
echo.
echo Picking words...
set NUM_WORDS=%1
PickWords.exe %NUM_WORDS% > temp-file.tmp
set /p WORD_LIST= < temp-file.tmp
echo.
echo Word list: %WORD_LIST%
del temp-file.tmp
if exist agent-complete.tmp del agent-complete.tmp

for %%f in (*.dll) do (
    echo.
    echo -----------------------------------------------------
    echo.
    echo Next player: %%~nf
    start "%%~nf" RunAgent.bat %%~nf
    echo.
    echo Waiting for agent to complete game...
    call WaitForFile.bat agent-complete.tmp
    del agent-complete.tmp
)
echo.
echo -----------------------------------------------------
GOTO end

:usage
echo.
echo ERROR: Missing command line parameter
echo.
echo Usage: RunChallenge.bat "num games"

:end