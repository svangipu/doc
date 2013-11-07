set terminal latex
set output '_region_-gnuplottex-fig3.tex'
set terminal epslatex color
set xrange [0:1000]
set yrange [*:*]
unset key
set xlabel "z (bp)"
set ylabel "da / dy (z) (bp / bp)"
        set grid
        set xtics 0,100
        #set ytics -10,-0.1
plot 'spreads3c.dat' using 1:2 with line, 'spreads3b.dat' using 1:2 with line, 'spreads3a.dat' using 1:2 with line
