default:
	-mkdir output
	${CC} -g lab1.c -o output/lab1 -Wall -Wextra
check:default
	output/lab1\
	 --verbose\
	 --profile\
	 --append --wronly dst.txt\
	 --pipe\
	 --pipe\
	 --rdonly src.txt\
	 --command 5 2 2 tr A-M n-z\
	 --command 3 0 0 cat - src.txt\
	 --command 1 4 4 sort -\
	 --close 2\
	 --close 4\
	 --wait\

clean:
	rm -rf output
dist:
	tar -czvf output/lib1.tar.gz makefile lab1.c
gdb:
	gdb output/lab1