@echo off
setlocal EnableDelayedExpansion

rem ============================================================
rem dump-folder.bat
rem Author: Entirely vibecoded by ChatGPT
rem Purpose: Naive and simple way to share entire code repositories with ChatGPT
rem
rem Usage:
rem   Navigate to the repository in command line 
rem   dump-folder.bat
rem   Entire content of the repository is now in the clipboard. Paste it with CTRL+V
rem    
rem   Add this to your PATH. Start typing "dump" and press tab for autocomplete.
rem   dump-folder.bat -p to show output on console only
rem ============================================================

if "%~1"=="" (
    set "TARGET=%CD%"
) else (
    set "TARGET=%~1"
)

rem Clipboard is the default
set "MODE=clipboard"

if /I "%~2"=="--console" set "MODE=console"
if /I "%~2"=="-p" set "MODE=console"

if not exist "%TARGET%\" (
    echo ERROR: Directory does not exist:
    echo %TARGET%
    exit /b 1
)

rem Directory from which the script was run
set "BASE=%CD%"

set "TEMPFILE=%TEMP%\dump-folder-%RANDOM%-%RANDOM%.txt"

(
    echo ============================================================
    echo DIRECTORY TREE
    echo ============================================================
    tree "%TARGET%" /f /a

    echo(
    echo(
    echo ============================================================
    echo FILE CONTENTS
    echo ============================================================
    echo(

    for /r "%TARGET%" %%F in (*) do (

        rem ----------------------------------------------------
        rem Skip common generated/dependency directories
        rem ----------------------------------------------------
        echo %%F | findstr /I /L ^
            "\.git\ \node_modules\ \bin\ \obj\ \build\ \dist\ \target\ \vendor\" ^
            >nul

        if errorlevel 1 (

            rem ------------------------------------------------
            rem Calculate path relative to where the script
            rem was run.
            rem ------------------------------------------------
            set "FILE=%%F"
            set "RELATIVE=!FILE:%BASE%\=!"

            echo ============================================================
            echo START OF FILE: !RELATIVE!
            echo ============================================================

            rem ------------------------------------------------
            rem Read file and determine whether it is binary.
            rem Remove trailing CR/LF so END OF FILE starts
            rem immediately on the next line.
            rem ------------------------------------------------
            powershell -NoProfile -Command ^
                "$p='%%F';" ^
                "try {" ^
                "  $b=[IO.File]::ReadAllBytes($p);" ^
                "" ^
                "  if($b.Length -eq 0) { exit 0 }" ^
                "" ^
                "  if($b.Length -ge 3 -and $b[0] -eq 239 -and $b[1] -eq 187 -and $b[2] -eq 191) {" ^
                "      $text=[Text.Encoding]::UTF8.GetString($b,3,$b.Length-3)" ^
                "  } elseif($b.Length -ge 2 -and $b[0] -eq 255 -and $b[1] -eq 254) {" ^
                "      $text=[Text.Encoding]::Unicode.GetString($b,2,$b.Length-2)" ^
                "  } elseif($b.Length -ge 2 -and $b[0] -eq 254 -and $b[1] -eq 255) {" ^
                "      $text=[Text.Encoding]::BigEndianUnicode.GetString($b,2,$b.Length-2)" ^
                "  } else {" ^
                "      $n=[Math]::Min($b.Length,8192);" ^
                "      $binary=0;" ^
                "      for($i=0;$i -lt $n;$i++) {" ^
                "          $x=$b[$i];" ^
                "          if($x -eq 0 -or ($x -lt 7) -or ($x -gt 14 -and $x -lt 32)) {" ^
                "              $binary++" ^
                "          }" ^
                "      }" ^
                "" ^
                "      if(($binary/$n) -gt 0.01) {" ^
                "          [Console]::Write('[binary file skipped]');" ^
                "          exit 0" ^
                "      }" ^
                "" ^
                "      $text=[Text.Encoding]::UTF8.GetString($b)" ^
                "  }" ^
                "" ^
                "  $text=$text.TrimEnd([char]13,[char]10);" ^
                "  [Console]::Write($text);" ^
                "} catch {" ^
                "  [Console]::Write('[binary/unreadable file skipped]');" ^
                "}"

            rem ------------------------------------------------
            rem End marker immediately follows the file content.
            rem ------------------------------------------------
            echo(
            echo ============================================================
            echo END OF FILE: !RELATIVE!
            echo ============================================================

            rem ------------------------------------------------
            rem Space between files.
            rem ------------------------------------------------
            echo(
            echo(
            echo(
        )
    )
) > "%TEMPFILE%"

rem ============================================================
rem Output
rem ============================================================

if /I "%MODE%"=="clipboard" (
    clip < "%TEMPFILE%"
    echo Output copied to clipboard.
) else (
    type "%TEMPFILE%"
)

del "%TEMPFILE%" 2>nul

endlocal