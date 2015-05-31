set terminal latex
set output '_region_-gnuplottex-fig6.tex'
set terminal epslatex color
       set xrange [0.0:10.0]
       set yrange [*:*]
       set xlabel "x"
       set ylabel "error"
       unset key
       set logscale y
       set format y "%1.0e"
       plot 'out7.txt' u 1:(abs($2-$3)) w l
 
