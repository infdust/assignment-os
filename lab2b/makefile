default:
	-mkdir output
	${CC} -g -pg lab2_list.c SortedList.c -o output/lab2_list -Wall -Wextra -pthread
profile:default
	output/lab2_list --threads=48 --iterations=1000 --sync=m
	gprof output/lab2_list
	output/lab2_list --threads=48 --iterations=1000 --sync=s
	gprof output/lab2_list
	output/lab2_list --threads=48 --iterations=1000 --sync=m --lists=16
	gprof output/lab2_list
	output/lab2_list --threads=48 --iterations=1000 --sync=s --lists=16
	gprof output/lab2_list
check3:default
	output/lab2_list --threads=1 --iterations=10 --sync=m --yield=id --lists=4
	output/lab2_list --threads=1 --iterations=10 --sync=s --yield=id --lists=4
	output/lab2_list --threads=1 --iterations=20 --sync=m --yield=id --lists=4
	output/lab2_list --threads=1 --iterations=20 --sync=s --yield=id --lists=4
	output/lab2_list --threads=1 --iterations=40 --sync=m --yield=id --lists=4
	output/lab2_list --threads=1 --iterations=40 --sync=s --yield=id --lists=4
	output/lab2_list --threads=1 --iterations=80 --sync=m --yield=id --lists=4
	output/lab2_list --threads=1 --iterations=80 --sync=s --yield=id --lists=4
	output/lab2_list --threads=4 --iterations=10 --sync=m --yield=id --lists=4
	output/lab2_list --threads=4 --iterations=10 --sync=s --yield=id --lists=4
	output/lab2_list --threads=4 --iterations=20 --sync=m --yield=id --lists=4
	output/lab2_list --threads=4 --iterations=20 --sync=s --yield=id --lists=4
	output/lab2_list --threads=4 --iterations=40 --sync=m --yield=id --lists=4
	output/lab2_list --threads=4 --iterations=40 --sync=s --yield=id --lists=4
	output/lab2_list --threads=4 --iterations=80 --sync=m --yield=id --lists=4
	output/lab2_list --threads=4 --iterations=80 --sync=s --yield=id --lists=4
	output/lab2_list --threads=8 --iterations=10 --sync=m --yield=id --lists=4
	output/lab2_list --threads=8 --iterations=10 --sync=s --yield=id --lists=4
	output/lab2_list --threads=8 --iterations=20 --sync=m --yield=id --lists=4
	output/lab2_list --threads=8 --iterations=20 --sync=s --yield=id --lists=4
	output/lab2_list --threads=8 --iterations=40 --sync=m --yield=id --lists=4
	output/lab2_list --threads=8 --iterations=40 --sync=s --yield=id --lists=4
	output/lab2_list --threads=8 --iterations=80 --sync=m --yield=id --lists=4
	output/lab2_list --threads=8 --iterations=80 --sync=s --yield=id --lists=4
	output/lab2_list --threads=12 --iterations=10 --sync=m --yield=id --lists=4
	output/lab2_list --threads=12 --iterations=10 --sync=s --yield=id --lists=4
	output/lab2_list --threads=12 --iterations=20 --sync=m --yield=id --lists=4
	output/lab2_list --threads=12 --iterations=20 --sync=s --yield=id --lists=4
	output/lab2_list --threads=12 --iterations=40 --sync=m --yield=id --lists=4
	output/lab2_list --threads=12 --iterations=40 --sync=s --yield=id --lists=4
	output/lab2_list --threads=12 --iterations=80 --sync=m --yield=id --lists=4
	output/lab2_list --threads=12 --iterations=80 --sync=s --yield=id --lists=4
	output/lab2_list --threads=16 --iterations=10 --sync=m --yield=id --lists=4
	output/lab2_list --threads=16 --iterations=10 --sync=s --yield=id --lists=4
	output/lab2_list --threads=16 --iterations=20 --sync=m --yield=id --lists=4
	output/lab2_list --threads=16 --iterations=20 --sync=s --yield=id --lists=4
	output/lab2_list --threads=16 --iterations=40 --sync=m --yield=id --lists=4
	output/lab2_list --threads=16 --iterations=40 --sync=s --yield=id --lists=4
	output/lab2_list --threads=16 --iterations=80 --sync=m --yield=id --lists=4
	output/lab2_list --threads=16 --iterations=80 --sync=s --yield=id --lists=4
	output/lab2_list --threads=24 --iterations=10 --sync=m --yield=id --lists=4
	output/lab2_list --threads=24 --iterations=10 --sync=s --yield=id --lists=4
	output/lab2_list --threads=24 --iterations=20 --sync=m --yield=id --lists=4
	output/lab2_list --threads=24 --iterations=20 --sync=s --yield=id --lists=4
	output/lab2_list --threads=24 --iterations=40 --sync=m --yield=id --lists=4
	output/lab2_list --threads=24 --iterations=40 --sync=s --yield=id --lists=4
	output/lab2_list --threads=24 --iterations=80 --sync=m --yield=id --lists=4
	output/lab2_list --threads=24 --iterations=80 --sync=s --yield=id --lists=4
check4:default
	output/lab2_list --threads=1 --iterations=1000 --sync=m --lists=4
	output/lab2_list --threads=4 --iterations=1000 --sync=m --lists=4
	output/lab2_list --threads=8 --iterations=1000 --sync=m --lists=4
	output/lab2_list --threads=16 --iterations=1000 --sync=m --lists=4
	output/lab2_list --threads=32 --iterations=1000 --sync=m --lists=4
	output/lab2_list --threads=48 --iterations=1000 --sync=m --lists=4
check5:default
	output/lab2_list --threads=1 --iterations=1000 --sync=s --lists=4
	output/lab2_list --threads=4 --iterations=1000 --sync=s --lists=4
	output/lab2_list --threads=8 --iterations=1000 --sync=s --lists=4
	output/lab2_list --threads=16 --iterations=1000 --sync=s --lists=4
	output/lab2_list --threads=32 --iterations=1000 --sync=s --lists=4
	output/lab2_list --threads=48 --iterations=1000 --sync=s --lists=4
clean:
	rm -rf output
dist:
	tar -czvf output/lab2.tar.gz makefile lab2_list.c SortedList.h SortedList.c
gdb:
	gdb output/lab2_list