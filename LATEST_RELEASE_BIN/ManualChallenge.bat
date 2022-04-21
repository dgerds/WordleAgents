@echo off
echo.
echo -----------------------------------------------------
echo.
echo Using manual word set.
set NUM_WORDS=5
set WORD_LIST=EARED MAZED JEELS ROUES BOBOS
echo.
echo Word list: %WORD_LIST%

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
