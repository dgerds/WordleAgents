@echo off

set WORD_LIST=SMALL TREND LIONS FREED PILOT

for %%f in (*.dll) do (
    echo.
    echo Starting: %%~nf
    PlayWordle.exe %%~nf.dll 5 %WORD_LIST% > %%~nf.out
    echo Complete: %%~nf.out
)
