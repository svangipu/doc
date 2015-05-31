set terminal latex
set output 'qlws2014-gnuplottex-fig1.tex'
set terminal epslatex color
  set xrange [0:0.15]
  set yrange [-40:40]
  set xlabel "strike"
  set ylabel "density"
        set grid
  plot 'out.txt' u 1:5 w l title 'Hagan (2002)', '' u 1:9 w l title 'Doust'
 
