set terminal latex
set output '_region_-gnuplottex-fig1.tex'
set terminal epslatex color
set xrange [0:1000]
set yrange [*:*]
unset key
set xlabel "z (bp)"
set ylabel "a(z) (bp)"
        set grid
        set xtics 0,100
        #set ytics 0,100
plot 'spreads1c.dat' using 1:2 with line, 'spreads1b.dat' using 1:2 with line, 'spreads1a.dat' using 1:2 with line, 'spreads1c.dat' using 1:1 with line
