@echo off
echo.
echo -----------------------------------------------------
echo.
echo Using manual word set.
set NUM_WORDS=5
set WORD_LIST=EARED MAZED JEELS ROUES BOBOS
echo.
echo Word list: %WORD_LIST%

for %%f in (*.dll) do (
    echo.
    echo -----------------------------------------------------
    echo.
    echo Next player: %%~nf
    timeout 5
    start "%%~nf" RunAgent.bat %%~nf
)
echo.
echo -----------------------------------------------------
