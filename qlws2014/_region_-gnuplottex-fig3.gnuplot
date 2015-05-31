set terminal latex
set output '_region_-gnuplottex-fig3.tex'
set terminal epslatex color
        set xrange [*:*]
        set yrange [*:*]
        set xlabel "strike"
        set ylabel "implied lognormal volatility"
        set grid
        plot 'out3.txt' u 1:2 w p title 'Input', 'out4.txt' u 1:2 w l title 'SVI'
 
