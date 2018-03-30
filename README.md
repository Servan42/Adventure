# Adventure

## Description

This software is a personnal project. It is a RPG fight system simulator in the Unix terminal.
Currently this software is still in developement. 

## Requirements 

I run this software with Ubuntu (Unix kernel), in the terminal. It contains system calls like `system("clear")`. You need to modifiy these calls if you want to run it on a different operating system.
The software also displays colors in the terminal with lines like this one `printf("\033[7m \033[0m");`. If your terminal does not support this type of encoding, you should remove them in the source code of the file display_fight.c .