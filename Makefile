all:
	gcc -pthread thread_create_example.c -o thread_create_example.exe
	gcc exec_example.c -o exec_exemple.exe
	gcc fork_example.c -o fork_exemple.exe

clean:
	rm *.exe

