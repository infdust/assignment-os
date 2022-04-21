set terminal png
set datafile separator ","

set title "List-1: Throughout vs Threads"
set xlabel "Threads"
set logscale x 10
set xrange [0.5:64]
set ylabel "Throughout (Operations/s)"
set logscale y 10
set output 'lab2_list-1.png'
plot \
     "< grep 'list-none-m,' lab2_list-1.csv" using ($2):($5)/($6)*1000000000 \
	title 'mutex' with linespoints lc rgb 'red', \
     "< grep 'list-none-s,' lab2_list-1.csv" using ($2):($5)/($6)*1000000000 \
	title 'spin-lock' with linespoints lc rgb 'green'


set title "List-2: Time per lock vs Threads"
set xlabel "Threads"
set logscale x 10
set xrange [0.5:64]
set ylabel "Time per lock (ns)"
set logscale y 10
set output 'lab2_list-2.png'
plot \
     "< grep 'list-none-m,' lab2_list-2.csv" using ($2):($8)/($5) \
	title 'mutex' with linespoints lc rgb 'red',


set title "List-3: Threads and Iterations that run without failure"
set xlabel "Threads"
set logscale x 2
set xrange [0.5:64]
set ylabel "Iterations per thread"
set logscale y 10
set output 'lab2_list-3.png'
plot \
     "< grep list-id-none lab2_list-3.csv" using ($2):($3) \
	title 'w/o yields' with points lc rgb 'green'


set title "List-4: Throughout vs Threads(mutex)"
set xlabel "Threads"
set logscale x 2
set xrange [0.5:64]
set ylabel "Throughout (Operations/s)"
set logscale y 10
set output 'lab2_list-4.png'
plot \
     "< grep list-none-m lab2_list-4.csv | grep ',1000,1,'" using ($2):($5)/($6)*1000000000 \
	title '1 list' with linespoints lc rgb 'green',\
     "< grep list-none-m lab2_list-4.csv | grep ',1000,4,'" using ($2):($5)/($6)*1000000000 \
	title '4 list' with linespoints lc rgb 'red',\
     "< grep list-none-m lab2_list-4.csv | grep ',1000,8,'" using ($2):($5)/($6)*1000000000 \
	title '8 list' with linespoints lc rgb 'blue',\
     "< grep list-none-m lab2_list-4.csv | grep ',1000,16,'" using ($2):($5)/($6)*1000000000 \
	title '16 list' with linespoints lc rgb 'orange'


set title "List-4: Throughout vs Threads(spin-lock)"
set xlabel "Threads"
set logscale x 2
set xrange [0.5:64]
set ylabel "Throughout (Operations/s)"
set logscale y 10
set output 'lab2_list-5.png'
plot \
     "< grep list-none-s lab2_list-5.csv | grep ',1000,1,'" using ($2):($5)/($6)*1000000000 \
	title '1 list' with linespoints lc rgb 'green',\
     "< grep list-none-s lab2_list-5.csv | grep ',1000,4,'" using ($2):($5)/($6)*1000000000 \
	title '4 list' with linespoints lc rgb 'red',\
     "< grep list-none-s lab2_list-5.csv | grep ',1000,8,'" using ($2):($5)/($6)*1000000000 \
	title '8 list' with linespoints lc rgb 'blue',\
     "< grep list-none-s lab2_list-5.csv | grep ',1000,16,'" using ($2):($5)/($6)*1000000000 \
	title '16 list' with linespoints lc rgb 'orange'