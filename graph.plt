# graphique.gp
set terminal png size 1600,800
set output 'res.png'

set title 'Option -s'
set datafile separator ";"
set xlabel 'ID des Trajets'
set ylabel 'Distances en km'

set xtics 2 nomirror rotate by -90

plot 'res.csv' using 4:xtic(1) with filledcurves x1 notitle lc "#b70b98", \
     'res.csv' using 3:xtic(1) with filledcurves x1 notitle lc "#e845ca", \
     'res.csv' using 2:xtic(1) with filledcurves x1 notitle lc "#e0a4d5"