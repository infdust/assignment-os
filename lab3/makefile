default:
	-mkdir output
	${CC} -g lab3a.c -o output/lab3a -Wall -Wextra
check:default
	output/lab3a
clean:
	rm -rf output
dist:
	tar -czvf output/lab3a.tar.gz makefile lab3a.c
gdb:
	gdb output/lab3a