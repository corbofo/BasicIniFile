# BasicIniFile

Basic ini file responds to my need to have a small function to read ini file values instead of big library on no a windows environment.

## Use

You've got a sample in the file
run.c

To compile on a linux
./buildRun.sh

Then to run
./run.exe

## Tests

In order to have functions matching original, I used TDD with own basic unit tests system.
You don't need test to only run functions.
Tests purpose are only to bug fixes and matching original functions.

### MSYS2 and MinGW 64-bit

Have MSYS2 and MinGW 64-bit installed :

https://www.msys2.org/wiki/MSYS2-installation/

Properly install MinGW 64 environment on MSYS2 in a MSYS2 MSYS terminal (my command lines to do that where):

pacman -Su
pacman -Sy
pacman -Su
pacman -S --needed base-devel mingw-w64-x86_64-toolchain

### Run tests

After install launch in a MSYS2 MinGW 64-bit terminal on windows :

./buildTest.sh

Then

./test.exe

## Limitations

The functions don't use dynamic allocation but fixed sized buffers with a MAX_LENGTH of 256. It should be enough for common usage.
The BIFGetPrivateProfileString returnedString and size is on the function user resposability and isn't subject to previous limitation.

This limitations are at the moment resposable of failling some tests.

So key names and section names in the ini file can't have length > MAX_LENGTH - 1.

