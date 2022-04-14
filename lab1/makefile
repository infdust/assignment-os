default:
	-mkdir output
	${CC} -g lab1.c -o output/lab1 -Wall -Wextra
check:default
	output/lab1\
	 --verbose\
	 --append --wronly dst.txt\
	 --pipe\
	 --pipe\
	 --rdonly src.txt\
	 --command 5 2 2 tr A-Y b-z\
	 --command 3 0 0 tr A-Z a-z\
	 --command 1 4 4 tr a-z A-Z\
	 --close 2\
	 --close 4\
	 --wait\

clean:
	rm -rf output
dist:
	tar -czvf output/lib1.tar.gz makefile lab0.c
test:default
gdb:
	gdb output/lab1