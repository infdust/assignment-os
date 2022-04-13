default:
	-mkdir output
	${CC} -g lab0.c -o output/lab0 -Wall -Wextra
check:
	output/lab0 --input=./src.txt --output=dst.txt
check1:
	output/lab0 --catch --segfault --segfault
check2:
	output/lab0 --dump-core
check3:
	output/lab0 --dump-core --segfault --segfault
clean:
	rm -rf output
dist:
	tar -czvf output/lib0-789.tar.gz makefile lab0.c