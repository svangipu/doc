set terminal latex
set output 'MF-gnuplottex-fig7.tex'
set terminal epslatex color
set xrange [0:52.0]
set yrange [0.02999:0.03001]
unset key
set xlabel "maturity"
set ylabel "zero rate"
plot 'yts_m_flat.txt' with line, 'yts_ntl_flat.txt' with line
