set terminal latex
set output 'ZABR-gnuplottex-fig1.tex'
set terminal epslatex color
        set style line 1 linecolor rgb "blue"
        set style line 2 linecolor rgb "red"
        set style line 3 linecolor rgb "green"
        set xrange [0:0.20]
set yrange [0:0.70]
set xlabel "strike"
set ylabel "implied ln vol"
        set grid
        plot 'smiles.dat' using 1:2 with lines ls 1 title "Classic Hagan",'smiles.dat' using 1:6 with lines ls 2 title "sme lognormal", 'smiles.dat' using 1:($10>0?$10:1/0) with lines ls 3 title "sme normal"
