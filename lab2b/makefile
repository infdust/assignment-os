default:
	-mkdir output
	${CC} -g -pg lab2_list.c SortedList.c -o output/lab2_list -Wall -Wextra -pthread
graphs:
	gnuplot lab2_list.gp
profile:default
	output/lab2_list --threads=48 --iterations=1000 --sync=m
	gprof output/lab2_list
	output/lab2_list --threads=48 --iterations=1000 --sync=s
	gprof output/lab2_list
	output/lab2_list --threads=48 --iterations=1000 --sync=m --lists=16
	gprof output/lab2_list
	output/lab2_list --threads=48 --iterations=1000 --sync=s --lists=16
	gprof output/lab2_list
check1:default
	output/lab2_list --threads=1 --iterations=1000 --sync=m
	output/lab2_list --threads=2 --iterations=1000 --sync=m
	output/lab2_list --threads=4 --iterations=1000 --sync=m
	output/lab2_list --threads=8 --iterations=1000 --sync=m
	output/lab2_list --threads=16 --iterations=1000 --sync=m
	output/lab2_list --threads=32 --iterations=1000 --sync=m
	output/lab2_list --threads=48 --iterations=1000 --sync=m
	output/lab2_list --threads=1 --iterations=1000 --sync=s
	output/lab2_list --threads=2 --iterations=1000 --sync=s
	output/lab2_list --threads=4 --iterations=1000 --sync=s
	output/lab2_list --threads=8 --iterations=1000 --sync=s
	output/lab2_list --threads=16 --iterations=1000 --sync=s
	output/lab2_list --threads=32 --iterations=1000 --sync=s
	output/lab2_list --threads=48 --iterations=1000 --sync=s
check2:default
	output/lab2_list --threads=1 --iterations=1000 --sync=m
	output/lab2_list --threads=2 --iterations=1000 --sync=m
	output/lab2_list --threads=4 --iterations=1000 --sync=m
	output/lab2_list --threads=8 --iterations=1000 --sync=m
	output/lab2_list --threads=16 --iterations=1000 --sync=m
	output/lab2_list --threads=32 --iterations=1000 --sync=m
	output/lab2_list --threads=48 --iterations=1000 --sync=m
check3:default
	-output/lab2_list --threads=1 --iterations=1 --yield=id --lists=4
	-output/lab2_list --threads=1 --iterations=2 --yield=id --lists=4
	-output/lab2_list --threads=1 --iterations=4 --yield=id --lists=4
	-output/lab2_list --threads=1 --iterations=8 --yield=id --lists=4
	-output/lab2_list --threads=1 --iterations=16 --yield=id --lists=4
	-output/lab2_list --threads=4 --iterations=1 --yield=id --lists=4
	-output/lab2_list --threads=4 --iterations=2 --yield=id --lists=4
	-output/lab2_list --threads=4 --iterations=4 --yield=id --lists=4
	-output/lab2_list --threads=4 --iterations=8 --yield=id --lists=4
	-output/lab2_list --threads=4 --iterations=16 --yield=id --lists=4
	-output/lab2_list --threads=8 --iterations=1 --yield=id --lists=4
	-output/lab2_list --threads=8 --iterations=2 --yield=id --lists=4
	-output/lab2_list --threads=8 --iterations=4 --yield=id --lists=4
	-output/lab2_list --threads=8 --iterations=8 --yield=id --lists=4
	-output/lab2_list --threads=8 --iterations=16 --yield=id --lists=4
	-output/lab2_list --threads=12 --iterations=1 --yield=id --lists=4
	-output/lab2_list --threads=12 --iterations=2 --yield=id --lists=4
	-output/lab2_list --threads=12 --iterations=4 --yield=id --lists=4
	-output/lab2_list --threads=12 --iterations=8 --yield=id --lists=4
	-output/lab2_list --threads=12 --iterations=16 --yield=id --lists=4
	-output/lab2_list --threads=16 --iterations=1 --yield=id --lists=4
	-output/lab2_list --threads=16 --iterations=2 --yield=id --lists=4
	-output/lab2_list --threads=16 --iterations=4 --yield=id --lists=4
	-output/lab2_list --threads=16 --iterations=8 --yield=id --lists=4
	-output/lab2_list --threads=16 --iterations=16 --yield=id --lists=4
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
	output/lab2_list --threads=1 --iterations=1000 --sync=m --lists=1
	output/lab2_list --threads=4 --iterations=1000 --sync=m --lists=1
	output/lab2_list --threads=8 --iterations=1000 --sync=m --lists=1
	output/lab2_list --threads=16 --iterations=1000 --sync=m --lists=1
	output/lab2_list --threads=32 --iterations=1000 --sync=m --lists=1
	output/lab2_list --threads=48 --iterations=1000 --sync=m --lists=1
	output/lab2_list --threads=1 --iterations=1000 --sync=m --lists=4
	output/lab2_list --threads=4 --iterations=1000 --sync=m --lists=4
	output/lab2_list --threads=8 --iterations=1000 --sync=m --lists=4
	output/lab2_list --threads=16 --iterations=1000 --sync=m --lists=4
	output/lab2_list --threads=32 --iterations=1000 --sync=m --lists=4
	output/lab2_list --threads=48 --iterations=1000 --sync=m --lists=4
	output/lab2_list --threads=1 --iterations=1000 --sync=m --lists=8
	output/lab2_list --threads=4 --iterations=1000 --sync=m --lists=8
	output/lab2_list --threads=8 --iterations=1000 --sync=m --lists=8
	output/lab2_list --threads=16 --iterations=1000 --sync=m --lists=8
	output/lab2_list --threads=32 --iterations=1000 --sync=m --lists=8
	output/lab2_list --threads=48 --iterations=1000 --sync=m --lists=8
	output/lab2_list --threads=1 --iterations=1000 --sync=m --lists=16
	output/lab2_list --threads=4 --iterations=1000 --sync=m --lists=16
	output/lab2_list --threads=8 --iterations=1000 --sync=m --lists=16
	output/lab2_list --threads=16 --iterations=1000 --sync=m --lists=16
	output/lab2_list --threads=32 --iterations=1000 --sync=m --lists=16
	output/lab2_list --threads=48 --iterations=1000 --sync=m --lists=16
check5:default
	output/lab2_list --threads=1 --iterations=1000 --sync=s --lists=1
	output/lab2_list --threads=4 --iterations=1000 --sync=s --lists=1
	output/lab2_list --threads=8 --iterations=1000 --sync=s --lists=1
	output/lab2_list --threads=16 --iterations=1000 --sync=s --lists=1
	output/lab2_list --threads=32 --iterations=1000 --sync=s --lists=1
	output/lab2_list --threads=48 --iterations=1000 --sync=s --lists=1
	output/lab2_list --threads=1 --iterations=1000 --sync=s --lists=4
	output/lab2_list --threads=4 --iterations=1000 --sync=s --lists=4
	output/lab2_list --threads=8 --iterations=1000 --sync=s --lists=4
	output/lab2_list --threads=16 --iterations=1000 --sync=s --lists=4
	output/lab2_list --threads=32 --iterations=1000 --sync=s --lists=4
	output/lab2_list --threads=48 --iterations=1000 --sync=s --lists=4
	output/lab2_list --threads=1 --iterations=1000 --sync=s --lists=8
	output/lab2_list --threads=4 --iterations=1000 --sync=s --lists=8
	output/lab2_list --threads=8 --iterations=1000 --sync=s --lists=8
	output/lab2_list --threads=16 --iterations=1000 --sync=s --lists=8
	output/lab2_list --threads=32 --iterations=1000 --sync=s --lists=8
	output/lab2_list --threads=48 --iterations=1000 --sync=s --lists=8
	output/lab2_list --threads=1 --iterations=1000 --sync=s --lists=16
	output/lab2_list --threads=4 --iterations=1000 --sync=s --lists=16
	output/lab2_list --threads=8 --iterations=1000 --sync=s --lists=16
	output/lab2_list --threads=16 --iterations=1000 --sync=s --lists=16
	output/lab2_list --threads=32 --iterations=1000 --sync=s --lists=16
	output/lab2_list --threads=48 --iterations=1000 --sync=s --lists=16
clean:
	rm -rf output
dist:
	tar -czvf output/lab2.tar.gz makefile lab2_list.c SortedList.h SortedList.c
gdb:
	gdb output/lab2_list