set terminal latex
set output 'ZABR-gnuplottex-fig3.tex'
set terminal epslatex color
        set style line 1 linecolor rgb "blue"
        set style line 2 linecolor rgb "red"
        set style line 3 linecolor rgb "green"
        set style line 4 linecolor rgb "black"
        set style line 5 linecolor rgb "orange"
        set xrange [0:0.20]
set yrange [0:1]
set xlabel "strike"
set ylabel "implied lognormal vol"
        set grid
        set ytics 0,0.1,1
        plot 'smiles.dat' using 1:($10>0?$10:1/0) with lines ls 1 title "sme gamma=1.0",'smiles.dat' using 1:($20>0?$20:1/0) with lines ls 2 title "sme gamma=0.0",'smiles.dat' using 1:($21>0?$21:1/0) with lines ls 3 title "sme gamma=0.5",'smiles.dat' using 1:($22>0?$22:1/0) with lines ls 4 title "sme gamma=1.5",'smiles.dat' using 1:($23>0?$23:1/0) with lines ls 5 title "sme gamma=1.7"
