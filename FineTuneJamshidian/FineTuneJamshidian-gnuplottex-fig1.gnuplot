set terminal latex
set output 'FineTuneJamshidian-gnuplottex-fig1.tex'
set terminal epslatex color
set xrange [0:10.0]
set yrange [0:1.5]
unset key
set xlabel "spread s"
set ylabel "delta"
plot 'spreadex.txt' with line
