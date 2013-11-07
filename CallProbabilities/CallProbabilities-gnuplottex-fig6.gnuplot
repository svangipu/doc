set terminal latex
set output 'CallProbabilities-gnuplottex-fig6.tex'
set terminal epslatex color
set xrange [0:52.0]
set yrange [0.0290:0.0310]
unset key
set xlabel "maturity"
set ylabel "zero rate"
plot 'yts_m_flat.txt' with line, 'yts_nontl_flat.txt' with line
