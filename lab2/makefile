default:
	-mkdir output
	${CC} -g lab2_add.c -o output/lab2_add -Wall -Wextra -pthread
	${CC} -g lab2_list.c SortedList.c -o output/lab2_list -Wall -Wextra -pthread
graphs:
	gnuplot lab2_add.gp
	gnuplot lab2_list.gp
checka:checka1 checka2 checka3 checka4 checka5
checkl:checkl1
checka1:default
	output/lab2_add --threads=1 --iterations=10
	output/lab2_add --threads=1 --iterations=20
	output/lab2_add --threads=1 --iterations=40
	output/lab2_add --threads=1 --iterations=80
	output/lab2_add --threads=1 --iterations=100
	output/lab2_add --threads=1 --iterations=1000
	output/lab2_add --threads=1 --iterations=10000
	output/lab2_add --threads=1 --iterations=100000
	output/lab2_add --threads=2 --iterations=10
	output/lab2_add --threads=2 --iterations=20
	output/lab2_add --threads=2 --iterations=40
	output/lab2_add --threads=2 --iterations=80
	output/lab2_add --threads=2 --iterations=100
	output/lab2_add --threads=2 --iterations=1000
	output/lab2_add --threads=2 --iterations=10000
	output/lab2_add --threads=2 --iterations=100000
	output/lab2_add --threads=4 --iterations=10
	output/lab2_add --threads=4 --iterations=20
	output/lab2_add --threads=4 --iterations=40
	output/lab2_add --threads=4 --iterations=80
	output/lab2_add --threads=4 --iterations=100
	output/lab2_add --threads=4 --iterations=1000
	output/lab2_add --threads=4 --iterations=10000
	output/lab2_add --threads=4 --iterations=100000
	output/lab2_add --threads=8 --iterations=10
	output/lab2_add --threads=8 --iterations=20
	output/lab2_add --threads=8 --iterations=40
	output/lab2_add --threads=8 --iterations=80
	output/lab2_add --threads=8 --iterations=100
	output/lab2_add --threads=8 --iterations=1000
	output/lab2_add --threads=8 --iterations=10000
	output/lab2_add --threads=8 --iterations=100000
	output/lab2_add --threads=16 --iterations=10
	output/lab2_add --threads=16 --iterations=20
	output/lab2_add --threads=16 --iterations=40
	output/lab2_add --threads=16 --iterations=80
	output/lab2_add --threads=16 --iterations=100
	output/lab2_add --threads=16 --iterations=1000
	output/lab2_add --threads=16 --iterations=10000
	output/lab2_add --threads=16 --iterations=100000
	output/lab2_add --threads=32 --iterations=10
	output/lab2_add --threads=32 --iterations=20
	output/lab2_add --threads=32 --iterations=40
	output/lab2_add --threads=32 --iterations=80
	output/lab2_add --threads=32 --iterations=100
	output/lab2_add --threads=32 --iterations=1000
	output/lab2_add --threads=32 --iterations=10000
	output/lab2_add --threads=32 --iterations=100000
	output/lab2_add --threads=48 --iterations=10
	output/lab2_add --threads=48 --iterations=20
	output/lab2_add --threads=48 --iterations=40
	output/lab2_add --threads=48 --iterations=80
	output/lab2_add --threads=48 --iterations=100
	output/lab2_add --threads=48 --iterations=1000
	output/lab2_add --threads=48 --iterations=10000
	output/lab2_add --threads=48 --iterations=100000
	output/lab2_add --threads=1 --iterations=10 --yield
	output/lab2_add --threads=1 --iterations=20 --yield
	output/lab2_add --threads=1 --iterations=40 --yield
	output/lab2_add --threads=1 --iterations=80 --yield
	output/lab2_add --threads=1 --iterations=100 --yield
	output/lab2_add --threads=1 --iterations=1000 --yield
	output/lab2_add --threads=1 --iterations=10000 --yield
	output/lab2_add --threads=1 --iterations=100000 --yield
	output/lab2_add --threads=2 --iterations=10 --yield
	output/lab2_add --threads=2 --iterations=20 --yield
	output/lab2_add --threads=2 --iterations=40 --yield
	output/lab2_add --threads=2 --iterations=80 --yield
	output/lab2_add --threads=2 --iterations=100 --yield
	output/lab2_add --threads=2 --iterations=1000 --yield
	output/lab2_add --threads=2 --iterations=10000 --yield
	output/lab2_add --threads=2 --iterations=100000 --yield
	output/lab2_add --threads=4 --iterations=10 --yield
	output/lab2_add --threads=4 --iterations=20 --yield
	output/lab2_add --threads=4 --iterations=40 --yield
	output/lab2_add --threads=4 --iterations=80 --yield
	output/lab2_add --threads=4 --iterations=100 --yield
	output/lab2_add --threads=4 --iterations=1000 --yield
	output/lab2_add --threads=4 --iterations=10000 --yield
	output/lab2_add --threads=4 --iterations=100000 --yield
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
checka2:default
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
checka3:default
	output/lab2_add --threads=1 --iterations=100
	output/lab2_add --threads=1 --iterations=1000
	output/lab2_add --threads=1 --iterations=10000
	output/lab2_add --threads=1 --iterations=100000
	output/lab2_add --threads=1 --iterations=1000000
	output/lab2_add --threads=1 --iterations=10000000
checka4:default
	output/lab2_add --threads=1 --iterations=10000 --yield
	output/lab2_add --threads=2 --iterations=10000 --yield
	output/lab2_add --threads=4 --iterations=10000 --yield
	output/lab2_add --threads=8 --iterations=10000 --yield
	output/lab2_add --threads=16 --iterations=10000 --yield
	output/lab2_add --threads=32 --iterations=10000 --yield
	output/lab2_add --threads=48 --iterations=10000 --yield
	output/lab2_add --threads=1 --iterations=10000 --yield --sync=m
	output/lab2_add --threads=2 --iterations=10000 --yield --sync=m
	output/lab2_add --threads=4 --iterations=10000 --yield --sync=m
	output/lab2_add --threads=8 --iterations=10000 --yield --sync=m
	output/lab2_add --threads=16 --iterations=10000 --yield --sync=m
	output/lab2_add --threads=32 --iterations=10000 --yield --sync=m
	output/lab2_add --threads=48 --iterations=10000 --yield --sync=m
	output/lab2_add --threads=1 --iterations=10000 --yield --sync=s
	output/lab2_add --threads=2 --iterations=10000 --yield --sync=s
	output/lab2_add --threads=4 --iterations=10000 --yield --sync=s
	output/lab2_add --threads=8 --iterations=10000 --yield --sync=s
	output/lab2_add --threads=16 --iterations=10000 --yield --sync=s
	output/lab2_add --threads=32 --iterations=10000 --yield --sync=s
	output/lab2_add --threads=48 --iterations=10000 --yield --sync=s
	output/lab2_add --threads=1 --iterations=10000 --yield --sync=c
	output/lab2_add --threads=2 --iterations=10000 --yield --sync=c
	output/lab2_add --threads=4 --iterations=10000 --yield --sync=c
	output/lab2_add --threads=8 --iterations=10000 --yield --sync=c
	output/lab2_add --threads=16 --iterations=10000 --yield --sync=c
	output/lab2_add --threads=32 --iterations=10000 --yield --sync=c
	output/lab2_add --threads=48 --iterations=10000 --yield --sync=c
checka5:default
	output/lab2_add --threads=1 --iterations=100000
	output/lab2_add --threads=2 --iterations=100000
	output/lab2_add --threads=4 --iterations=100000
	output/lab2_add --threads=8 --iterations=100000
	output/lab2_add --threads=16 --iterations=100000
	output/lab2_add --threads=32 --iterations=100000
	output/lab2_add --threads=48 --iterations=100000
	output/lab2_add --threads=1 --iterations=100000 --sync=m
	output/lab2_add --threads=2 --iterations=100000 --sync=m
	output/lab2_add --threads=4 --iterations=100000 --sync=m
	output/lab2_add --threads=8 --iterations=100000 --sync=m
	output/lab2_add --threads=16 --iterations=100000 --sync=m
	output/lab2_add --threads=32 --iterations=100000 --sync=m
	output/lab2_add --threads=48 --iterations=100000 --sync=m
	output/lab2_add --threads=1 --iterations=100000 --sync=s
	output/lab2_add --threads=2 --iterations=100000 --sync=s
	output/lab2_add --threads=4 --iterations=100000 --sync=s
	output/lab2_add --threads=8 --iterations=100000 --sync=s
	output/lab2_add --threads=16 --iterations=100000 --sync=s
	output/lab2_add --threads=32 --iterations=100000 --sync=s
	output/lab2_add --threads=48 --iterations=100000 --sync=s
	output/lab2_add --threads=1 --iterations=100000 --sync=c
	output/lab2_add --threads=2 --iterations=100000 --sync=c
	output/lab2_add --threads=4 --iterations=100000 --sync=c
	output/lab2_add --threads=8 --iterations=100000 --sync=c
	output/lab2_add --threads=16 --iterations=100000 --sync=c
	output/lab2_add --threads=32 --iterations=100000 --sync=c
	output/lab2_add --threads=48 --iterations=100000 --sync=c
checkl1:default
	output/lab2_list --threads=1 --iterations=10
	output/lab2_list --threads=1 --iterations=100
	output/lab2_list --threads=1 --iterations=1000
	output/lab2_list --threads=1 --iterations=10000
	output/lab2_list --threads=1 --iterations=20000
checkl2:default
	output/lab2_list --threads=4 --iterations=1
	output/lab2_list --threads=4 --iterations=10
	output/lab2_list --threads=4 --iterations=100
	output/lab2_list --threads=4 --iterations=1000
	output/lab2_list --threads=8 --iterations=1
	output/lab2_list --threads=8 --iterations=10
	output/lab2_list --threads=8 --iterations=100
	output/lab2_list --threads=8 --iterations=1000
	output/lab2_list --threads=16 --iterations=1
	output/lab2_list --threads=16 --iterations=10
	output/lab2_list --threads=16 --iterations=100
	output/lab2_list --threads=16 --iterations=1000
	output/lab2_list --threads=24 --iterations=1
	output/lab2_list --threads=24 --iterations=10
	output/lab2_list --threads=24 --iterations=100
	output/lab2_list --threads=24 --iterations=1000
	-output/lab2_list --threads=4 --iterations=1 --yield=i
	-output/lab2_list --threads=4 --iterations=2 --yield=i
	-output/lab2_list --threads=4 --iterations=4 --yield=i
	-output/lab2_list --threads=4 --iterations=8 --yield=i
	-output/lab2_list --threads=4 --iterations=16 --yield=i
	-output/lab2_list --threads=4 --iterations=32 --yield=i
	-output/lab2_list --threads=8 --iterations=1 --yield=i
	-output/lab2_list --threads=8 --iterations=2 --yield=i
	-output/lab2_list --threads=8 --iterations=4 --yield=i
	-output/lab2_list --threads=8 --iterations=8 --yield=i
	-output/lab2_list --threads=8 --iterations=16 --yield=i
	-output/lab2_list --threads=8 --iterations=32 --yield=i
	-output/lab2_list --threads=16 --iterations=1 --yield=i
	-output/lab2_list --threads=16 --iterations=2 --yield=i
	-output/lab2_list --threads=16 --iterations=4 --yield=i
	-output/lab2_list --threads=16 --iterations=8 --yield=i
	-output/lab2_list --threads=16 --iterations=16 --yield=i
	-output/lab2_list --threads=16 --iterations=32 --yield=i
	-output/lab2_list --threads=24 --iterations=1 --yield=i
	-output/lab2_list --threads=24 --iterations=2 --yield=i
	-output/lab2_list --threads=24 --iterations=4 --yield=i
	-output/lab2_list --threads=24 --iterations=8 --yield=i
	-output/lab2_list --threads=24 --iterations=16 --yield=i
	-output/lab2_list --threads=24 --iterations=32 --yield=i
	-output/lab2_list --threads=4 --iterations=1 --yield=d
	-output/lab2_list --threads=4 --iterations=2 --yield=d
	-output/lab2_list --threads=4 --iterations=4 --yield=d
	-output/lab2_list --threads=4 --iterations=8 --yield=d
	-output/lab2_list --threads=4 --iterations=16 --yield=d
	-output/lab2_list --threads=4 --iterations=32 --yield=d
	-output/lab2_list --threads=8 --iterations=1 --yield=d
	-output/lab2_list --threads=8 --iterations=2 --yield=d
	-output/lab2_list --threads=8 --iterations=4 --yield=d
	-output/lab2_list --threads=8 --iterations=8 --yield=d
	-output/lab2_list --threads=8 --iterations=16 --yield=d
	-output/lab2_list --threads=8 --iterations=32 --yield=d
	-output/lab2_list --threads=16 --iterations=1 --yield=d
	-output/lab2_list --threads=16 --iterations=2 --yield=d
	-output/lab2_list --threads=16 --iterations=4 --yield=d
	-output/lab2_list --threads=16 --iterations=8 --yield=d
	-output/lab2_list --threads=16 --iterations=16 --yield=d
	-output/lab2_list --threads=16 --iterations=32 --yield=d
	-output/lab2_list --threads=24 --iterations=1 --yield=d
	-output/lab2_list --threads=24 --iterations=2 --yield=d
	-output/lab2_list --threads=24 --iterations=4 --yield=d
	-output/lab2_list --threads=24 --iterations=8 --yield=d
	-output/lab2_list --threads=24 --iterations=16 --yield=d
	-output/lab2_list --threads=24 --iterations=32 --yield=d
	-output/lab2_list --threads=4 --iterations=1 --yield=il
	-output/lab2_list --threads=4 --iterations=2 --yield=il
	-output/lab2_list --threads=4 --iterations=4 --yield=il
	-output/lab2_list --threads=4 --iterations=8 --yield=il
	-output/lab2_list --threads=4 --iterations=16 --yield=il
	-output/lab2_list --threads=4 --iterations=32 --yield=il
	-output/lab2_list --threads=8 --iterations=1 --yield=il
	-output/lab2_list --threads=8 --iterations=2 --yield=il
	-output/lab2_list --threads=8 --iterations=4 --yield=il
	-output/lab2_list --threads=8 --iterations=8 --yield=il
	-output/lab2_list --threads=8 --iterations=16 --yield=il
	-output/lab2_list --threads=8 --iterations=32 --yield=il
	-output/lab2_list --threads=16 --iterations=1 --yield=il
	-output/lab2_list --threads=16 --iterations=2 --yield=il
	-output/lab2_list --threads=16 --iterations=4 --yield=il
	-output/lab2_list --threads=16 --iterations=8 --yield=il
	-output/lab2_list --threads=16 --iterations=16 --yield=il
	-output/lab2_list --threads=16 --iterations=32 --yield=il
	-output/lab2_list --threads=24 --iterations=1 --yield=il
	-output/lab2_list --threads=24 --iterations=2 --yield=il
	-output/lab2_list --threads=24 --iterations=4 --yield=il
	-output/lab2_list --threads=24 --iterations=8 --yield=il
	-output/lab2_list --threads=24 --iterations=16 --yield=il
	-output/lab2_list --threads=24 --iterations=32 --yield=il
	-output/lab2_list --threads=4 --iterations=1 --yield=dl
	-output/lab2_list --threads=4 --iterations=2 --yield=dl
	-output/lab2_list --threads=4 --iterations=4 --yield=dl
	-output/lab2_list --threads=4 --iterations=8 --yield=dl
	-output/lab2_list --threads=4 --iterations=16 --yield=dl
	-output/lab2_list --threads=4 --iterations=32 --yield=dl
	-output/lab2_list --threads=8 --iterations=1 --yield=dl
	-output/lab2_list --threads=8 --iterations=2 --yield=dl
	-output/lab2_list --threads=8 --iterations=4 --yield=dl
	-output/lab2_list --threads=8 --iterations=8 --yield=dl
	-output/lab2_list --threads=8 --iterations=16 --yield=dl
	-output/lab2_list --threads=8 --iterations=32 --yield=dl
	-output/lab2_list --threads=16 --iterations=1 --yield=dl
	-output/lab2_list --threads=16 --iterations=2 --yield=dl
	-output/lab2_list --threads=16 --iterations=4 --yield=dl
	-output/lab2_list --threads=16 --iterations=8 --yield=dl
	-output/lab2_list --threads=16 --iterations=16 --yield=dl
	-output/lab2_list --threads=16 --iterations=32 --yield=dl
	-output/lab2_list --threads=24 --iterations=1 --yield=dl
	-output/lab2_list --threads=24 --iterations=2 --yield=dl
	-output/lab2_list --threads=24 --iterations=4 --yield=dl
	-output/lab2_list --threads=24 --iterations=8 --yield=dl
	-output/lab2_list --threads=24 --iterations=16 --yield=dl
	-output/lab2_list --threads=24 --iterations=32 --yield=dl
checkl3:default
	output/lab2_list --threads=24 --iterations=32 --yield=i --sync=m
	output/lab2_list --threads=24 --iterations=32 --yield=i --sync=s
	-output/lab2_list --threads=24 --iterations=32 --yield=i
	output/lab2_list --threads=24 --iterations=32 --yield=d --sync=m
	output/lab2_list --threads=24 --iterations=32 --yield=d --sync=s
	-output/lab2_list --threads=24 --iterations=32 --yield=d
	output/lab2_list --threads=24 --iterations=32 --yield=il --sync=m
	output/lab2_list --threads=24 --iterations=32 --yield=il --sync=s
	-output/lab2_list --threads=24 --iterations=32 --yield=il
	output/lab2_list --threads=24 --iterations=32 --yield=dl --sync=m
	output/lab2_list --threads=24 --iterations=32 --yield=dl --sync=s
	-output/lab2_list --threads=24 --iterations=32 --yield=dl
checkl4:default
	output/lab2_list --threads=1 --iterations=1000 --sync=m
	output/lab2_list --threads=1 --iterations=1000 --sync=s
	output/lab2_list --threads=2 --iterations=1000 --sync=m
	output/lab2_list --threads=2 --iterations=1000 --sync=s
	output/lab2_list --threads=4 --iterations=1000 --sync=m
	output/lab2_list --threads=4 --iterations=1000 --sync=s
	output/lab2_list --threads=8 --iterations=1000 --sync=m
	output/lab2_list --threads=8 --iterations=1000 --sync=s
	output/lab2_list --threads=16 --iterations=1000 --sync=m
	output/lab2_list --threads=16 --iterations=1000 --sync=s
	output/lab2_list --threads=24 --iterations=1000 --sync=m
	output/lab2_list --threads=24 --iterations=1000 --sync=s
	output/lab2_list --threads=32 --iterations=1000 --sync=m
	output/lab2_list --threads=32 --iterations=1000 --sync=s
	output/lab2_list --threads=48 --iterations=1000 --sync=m
	output/lab2_list --threads=48 --iterations=1000 --sync=s
clean:
	rm -rf output
dist:
	tar -czvf output/lab2.tar.gz makefile lab2_add.c lab2_list.c SortedList.h SortedList.c
gdba:
	gdb output/lab2_add
gdbl:
	gdb output/lab2_list