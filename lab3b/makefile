default:clean
	-mkdir output
	${CC} -g lab3b.c -o output/lab3b -Wall -Wextra
check:default
	-output/lab3b ./test/P3B-test_1.csv
	-output/lab3b ./test/P3B-test_2.csv
	-output/lab3b ./test/P3B-test_3.csv
	-output/lab3b ./test/P3B-test_4.csv
	-output/lab3b ./test/P3B-test_5.csv
	-output/lab3b ./test/P3B-test_6.csv
	-output/lab3b ./test/P3B-test_7.csv
	-output/lab3b ./test/P3B-test_8.csv
	-output/lab3b ./test/P3B-test_9.csv
	-output/lab3b ./test/P3B-test_10.csv
	-output/lab3b ./test/P3B-test_11.csv
	-output/lab3b ./test/P3B-test_12.csv
	-output/lab3b ./test/P3B-test_13.csv
	-output/lab3b ./test/P3B-test_14.csv
	-output/lab3b ./test/P3B-test_15.csv
	-output/lab3b ./test/P3B-test_16.csv
	-output/lab3b ./test/P3B-test_17.csv
	-output/lab3b ./test/P3B-test_18.csv
	-output/lab3b ./test/P3B-test_19.csv
	-output/lab3b ./test/P3B-test_20.csv
	-output/lab3b ./test/P3B-test_21.csv
	-output/lab3b ./test/P3B-test_22.csv
clean:
	rm -rf output
dist:
	tar -czvf output/lab3b.tar.gz makefile lab3b.c
gdb:
	gdb output/lab3b