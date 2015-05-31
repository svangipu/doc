set terminal latex
set output 'pix-gnuplottex-fig1.tex'
set terminal epslatex color
set xrange [0:0.10]
set yrange [-50:50]
set xlabel "strike"
set ylabel "density"
plot 'out.txt' u 1:5 w l, '' u 1:9 w l
