set terminal latex
set output 'MF-gnuplottex-fig1.tex'
set terminal epslatex color
set xrange [0:15]
set yrange [-3:3]
set zrange [0:1.01]
unset key
set xlabel "t"
set ylabel "y"
set zlabel "N(t,y)" 0,1
set view 61,152,,
splot 'numeraire.txt' with pm3d, 'numeraire.txt' with lines
