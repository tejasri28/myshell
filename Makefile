fileName=main
CWD=$(PWD)

all:
	gcc -Wall -g Utility.c Prompt.c Parser.c MyShell1.c ExecuteCommands.c -L/usr/include -lreadline -o MyShell.out
	gcc ls.c -o bin/ls.out
	gcc ps1.c -o bin/ps.out
	gcc wc.c -o bin/wc.out
	gcc cat.c -o bin/cat.out
	gcc mkdir.c -o bin/mkdir.out
	
clean : 
	rm -f *.out
