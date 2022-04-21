@echo off
echo.
echo Starting: %1
PlayWordle.exe %1.dll %NUM_WORDS% %WORD_LIST%
echo.
echo Complete: %1
echo. > agent-complete.tmp