set terminal latex
set output 'qlws2014-gnuplottex-fig5.tex'
set terminal epslatex color
       set xrange [-5:5]
       set yrange [-5:5]
       set cbrange [0:0.5]
       set xlabel "x"
       set ylabel "y"
       set zlabel "z"
       set isosample 100,100
       unset key
       set view 35,24
       splot (sin(pi*(x+0.5))*cos(pi*(y+1))+2)*(x**2+y**2)/50.0 with pm3d, (sin(pi*(x+0.5))*cos(pi*(y+1))+2)*(x**2+y**2)/50.0 with lines
 
