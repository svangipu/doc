set terminal latex
set output 'fxtarf-gnuplottex-fig17.tex'
set terminal epslatex color
set xrange [0.60:1.75]
set yrange [*:*]
unset key
set grid
        set xtics 0.1
set xlabel "FX spot"
set ylabel "NPV"
        plot 'tarf17.dat' u 1:($2/100000000) w l, '' u 1:($5==0?1/0:$5/100000000) w p pt 6 ps 1, '' u 1:($1>=$3&&$1<=$4?0.0:1/0) w l lt 1 lw 3 lc 0
