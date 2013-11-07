set terminal latex
set output '_region_-gnuplottex-fig2.tex'
set terminal epslatex color
set xrange [0:1000]
set yrange [*:*]
unset key
set xlabel "z (bp)"
set ylabel "da / dz (z) (bp / bp)"
        set grid
        set xtics 0,100
        #set ytics 0,0.1
plot 'spreads2c.dat' using 1:2 with line, 'spreads2b.dat' using 1:2 with line, 'spreads2a.dat' using 1:2 with line
