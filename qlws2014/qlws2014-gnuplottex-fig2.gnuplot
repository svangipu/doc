set terminal latex
set output 'qlws2014-gnuplottex-fig2.tex'
set terminal epslatex color
        set xrange [*:*]
        set yrange [*:*]
        set xlabel "strike"
        set ylabel "implied lognormal volatility"
        set grid
        plot 'out2.txt' u 1:2 w l title 'SABR', '' u 1:10 w l title 'ZABR 1.0', '' u 1:14 w l title 'ZABR 0.5', '' u 1:18 w l title 'ZABR 1.5'
 
