#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set key right bottom
set xlabel "N de ejemplares"
set ylabel "Tiempo(mcs)"

set output "grafica_matrices.eps"
plot 'datos-mat.txt' using 1:2 t "Tiempos reales" w points, 'datos-mat.txt' using 1:3 t "Tiempos estimados" w l

set output "grafica_fibonacci.eps"
plot 'datos-fib.txt' using 1:2 t "Tiempos reales" w points, 'datos-fib.txt' using 1:3 t "Tiempos estimados" w l

_end_
