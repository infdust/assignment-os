default:
	-mkdir output
	${CC} -g lab2_add.c -o output/lab2_add -Wall -Wextra -pthread
check1:default
	output/lab2_add --threads=8 --iterations=10 --yield
	output/lab2_add --threads=8 --iterations=20 --yield
	output/lab2_add --threads=8 --iterations=40 --yield
	output/lab2_add --threads=8 --iterations=80 --yield
	output/lab2_add --threads=8 --iterations=100 --yield
	output/lab2_add --threads=8 --iterations=1000 --yield
	output/lab2_add --threads=8 --iterations=10000 --yield
	output/lab2_add --threads=8 --iterations=100000 --yield
	output/lab2_add --threads=16 --iterations=10 --yield
	output/lab2_add --threads=16 --iterations=20 --yield
	output/lab2_add --threads=16 --iterations=40 --yield
	output/lab2_add --threads=16 --iterations=80 --yield
	output/lab2_add --threads=16 --iterations=100 --yield
	output/lab2_add --threads=16 --iterations=1000 --yield
	output/lab2_add --threads=16 --iterations=10000 --yield
	output/lab2_add --threads=16 --iterations=100000 --yield
	output/lab2_add --threads=32 --iterations=10 --yield
	output/lab2_add --threads=32 --iterations=20 --yield
	output/lab2_add --threads=32 --iterations=40 --yield
	output/lab2_add --threads=32 --iterations=80 --yield
	output/lab2_add --threads=32 --iterations=100 --yield
	output/lab2_add --threads=32 --iterations=1000 --yield
	output/lab2_add --threads=32 --iterations=10000 --yield
	output/lab2_add --threads=32 --iterations=100000 --yield
	output/lab2_add --threads=48 --iterations=10 --yield
	output/lab2_add --threads=48 --iterations=20 --yield
	output/lab2_add --threads=48 --iterations=40 --yield
	output/lab2_add --threads=48 --iterations=80 --yield
	output/lab2_add --threads=48 --iterations=100 --yield
	output/lab2_add --threads=48 --iterations=1000 --yield
	output/lab2_add --threads=48 --iterations=10000 --yield
	output/lab2_add --threads=48 --iterations=100000 --yield
check2:default
	output/lab2_add --threads=8 --iterations=100 --yield
	output/lab2_add --threads=8 --iterations=1000 --yield
	output/lab2_add --threads=8 --iterations=10000 --yield
	output/lab2_add --threads=8 --iterations=100000 --yield
	output/lab2_add --threads=32 --iterations=100 --yield
	output/lab2_add --threads=32 --iterations=1000 --yield
	output/lab2_add --threads=32 --iterations=10000 --yield
	output/lab2_add --threads=32 --iterations=100000 --yield
	output/lab2_add --threads=8 --iterations=100
	output/lab2_add --threads=8 --iterations=1000
	output/lab2_add --threads=8 --iterations=10000
	output/lab2_add --threads=8 --iterations=100000
	output/lab2_add --threads=32 --iterations=100
	output/lab2_add --threads=32 --iterations=1000
	output/lab2_add --threads=32 --iterations=10000
	output/lab2_add --threads=32 --iterations=100000
check3:default
	output/lab2_add --threads=1 --iterations=100 --yield
	output/lab2_add --threads=1 --iterations=1000 --yield
	output/lab2_add --threads=1 --iterations=10000 --yield
	output/lab2_add --threads=1 --iterations=100000 --yield
	output/lab2_add --threads=1 --iterations=1000000 --yield
	output/lab2_add --threads=1 --iterations=10000000 --yield
	output/lab2_add --threads=1 --iterations=100
	output/lab2_add --threads=1 --iterations=1000
	output/lab2_add --threads=1 --iterations=10000
	output/lab2_add --threads=1 --iterations=100000
	output/lab2_add --threads=1 --iterations=1000000
	output/lab2_add --threads=1 --iterations=10000000
check4:default
	output/lab2_add --threads=8 --iterations=10000 --yield
	output/lab2_add --threads=16 --iterations=10000 --yield
	output/lab2_add --threads=32 --iterations=10000 --yield
	output/lab2_add --threads=48 --iterations=10000 --yield
	output/lab2_add --threads=8 --iterations=10000 --yield --sync=m
	output/lab2_add --threads=16 --iterations=10000 --yield --sync=m
	output/lab2_add --threads=32 --iterations=10000 --yield --sync=m
	output/lab2_add --threads=48 --iterations=10000 --yield --sync=m
	output/lab2_add --threads=8 --iterations=10000 --yield --sync=s
	output/lab2_add --threads=16 --iterations=10000 --yield --sync=s
	output/lab2_add --threads=32 --iterations=10000 --yield --sync=s
	output/lab2_add --threads=48 --iterations=10000 --yield --sync=s
	output/lab2_add --threads=8 --iterations=10000 --yield --sync=c
	output/lab2_add --threads=16 --iterations=10000 --yield --sync=c
	output/lab2_add --threads=32 --iterations=10000 --yield --sync=c
	output/lab2_add --threads=48 --iterations=10000 --yield --sync=c
check5:default
	output/lab2_add --threads=8 --iterations=100000
	output/lab2_add --threads=16 --iterations=100000
	output/lab2_add --threads=32 --iterations=100000
	output/lab2_add --threads=48 --iterations=100000
	output/lab2_add --threads=8 --iterations=100000 --sync=m
	output/lab2_add --threads=16 --iterations=100000 --sync=m
	output/lab2_add --threads=32 --iterations=100000 --sync=m
	output/lab2_add --threads=48 --iterations=100000 --sync=m
	output/lab2_add --threads=8 --iterations=100000 --sync=s
	output/lab2_add --threads=16 --iterations=100000 --sync=s
	output/lab2_add --threads=32 --iterations=100000 --sync=s
	output/lab2_add --threads=48 --iterations=100000 --sync=s
	output/lab2_add --threads=8 --iterations=100000 --sync=c
	output/lab2_add --threads=16 --iterations=100000 --sync=c
	output/lab2_add --threads=32 --iterations=100000 --sync=c
	output/lab2_add --threads=48 --iterations=100000 --sync=c
clean:
	rm -rf output
dist:
	tar -czvf output/lab2.tar.gz makefile lab2_add.c
gdb:
	gdb output/lab2_add