#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "grafico.eps"
set key right bottom
set xlabel "Tiempo"
set ylabel "Tamaño ejemplar"
plot 'Datos.txt' using 1:2 t "Tiempos reales" w l, 'Datos.txt' using 1:3 t "Tiempos estimados" w l
_end_
