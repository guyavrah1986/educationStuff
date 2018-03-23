:: Disable the need to prefix echo using the @ symbol (i.e.- no need to write @echo "something to echo", simply wirte: echo "something to echo")
@echo off

set projectName=compilationProcess
echo "building project %projectName%"

set currDir=%cd%
echo "current directory is:%currDird%"

:: remove old build folder and all its content
rmdir /S build

:: create a new one
mkdir build

:: navigate to the build fodler so that the build output will go there
cd build

:: invoke the cmake command to buld the project
cmake -G "Visual Studio 15 2017 Win64" ..

:: stop the batch and ask for us to enter any key before terminating, this (built in) command
:: will prompt the user to:
:: "Press any key to continue. . . "
pause

:: enable back the @in echo
echo on