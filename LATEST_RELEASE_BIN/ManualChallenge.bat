@echo off

echo Using manual word set.
set WORD_LIST=EARED MAZED JEELS ROUES BOBOS LESES
echo Word list: %WORD_LIST%

for %%f in (*.dll) do (
    echo.
    echo Starting: %%~nf
    PlayWordle.exe %%~nf.dll 6 %WORD_LIST% > %%~nf.out
    echo Complete: %%~nf.out
    LastLine.exe %%~nf.out
)
