reset
set terminal png size 800,800
width = 0.8
# Titre du graphique
set title title_option

# Style de l'histogramme
set style fill solid border -1
set boxwidth 2 absolute
set style data boxes
set xlabel 'ID du trajet'
set ylabel 'Longueur du trajet (en km)'
set xrange [0:*]
set yrange [*:*]
set offsets 0.75, -0.25, 0, 0

# Utiliser des espaces comme séparateurs de colonnes
set datafile separator " "

# Spécifier les colonnes à utiliser
colonne_trajets = 2
colonne_nombre = 1


# Afficher l'histogramme
set xtics rotate by -45
set output 'res.png'

plot "res.csv" using colonne_nombre:xticlabels(colonne_trajets) with histogram title "Longueur du trajet" linecolor rgb "#eca1c9"
exit