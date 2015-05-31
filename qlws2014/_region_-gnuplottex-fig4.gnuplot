set terminal latex
set output '_region_-gnuplottex-fig4.tex'
set terminal epslatex color
       set xrange [*:*]
       set yrange [*:*]
       set xlabel "strike"
       set ylabel "put call parity violation"
       set grid
       set logscale y
       set format y "%1.0e"
       set key below
       plot 'out5.txt' u 1:(abs($4)) w l title 'Hagan (Numeric, NonParallelShifts)', 'out6.txt' u 1:(abs($4)) w l title 'Linear TSR'
 
