@echo off
set WAIT_FOR_FILE=%1

:CheckForFile
if exist %WAIT_FOR_FILE% goto :FoundFile
timeout /t 1 >nul
goto CheckForFile

:FoundFile