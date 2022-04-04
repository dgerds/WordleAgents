@echo off

echo Picking words...
PickWords.exe 5 > temp-file.tmp
set /p WORD_LIST= < temp-file.tmp
echo Word list: %WORD_LIST%
del temp-file.tmp

for %%f in (*.dll) do (
    echo.
    echo Starting: %%~nf
    PlayWordle.exe %%~nf.dll 5 %WORD_LIST% > %%~nf.out
    echo Complete: %%~nf.out
    LastLine.exe %%~nf.out
)
