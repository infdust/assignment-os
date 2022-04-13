default:
	-mkdir output
	${CC} -g lab1.c -o output/lab1 -Wall -Wextra
check:default
	output/lab1 --verbose --verbose --wronly dst.txt --rdonly src.txt --command 1 0 0 tr a-z A-Z
clean:
	rm -rf output
dist:
	tar -czvf output/lib1.tar.gz makefile lab0.c
test:default
gdb:
	gdb output/lab1