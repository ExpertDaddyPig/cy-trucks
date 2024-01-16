reset
set terminal png size 800,800
width = 0.4
# Titre du graphique

# Style de l'histogramme
set style fill solid border -1
set ylabel 'Conducteurs'
set xrange [*:*]
set yrange [0:*]
set offsets 0,0,0.5-width/2.,0.5

# Utiliser des espaces comme séparateurs de colonnes
set datafile separator ";"

# Afficher l'histogramme
set output 'res.png'

plot "data_d1.dat" using 2:yticlabels(1) with lp
exit