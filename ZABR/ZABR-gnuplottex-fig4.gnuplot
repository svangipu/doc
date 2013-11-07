set terminal latex
set output 'ZABR-gnuplottex-fig4.tex'
set terminal epslatex color
        set style line 1 linecolor rgb "blue"
        set style line 2 linecolor rgb "red"
        set style line 3 linecolor rgb "green"
        set xrange [0:0.10]
set yrange [0:0.045]
set xlabel "strike k"
set ylabel "local vol \theta(k)"
        set grid
        plot 'smiles.dat' using 1:14 with lines ls 1 title "Equivalent local vol"
