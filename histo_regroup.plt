reset
set terminal png size 800,800
# Titre du graphique
set title "Option -t"

# Style de l'histogramme
set style data histogram
set style histogram clustered gap 2
set style fill solid border -1
set boxwidth 2.5 absolute
set xlabel "Villes"
set xrange [0:*]
set yrange [*:*]
set offsets 1, 0, 0, 0


# Utiliser des espaces comme séparateurs de colonnes
set datafile separator ";"

# Spécifier les colonnes à utiliser
colonne_premier = 3
colonne_passage = 2
colonne_ville = 1


# Afficher l'histogramme
set xtics rotate by -90
set output 'res.png'

plot "res.csv" using colonne_passage:xticlabels(1) lc rgb "#eca1c9" title "Nombre de passage", '' using colonne_premier:xticlabels(1) lc rgb "#ee91dd" title "Nombre de fois où la ville est celle de départ"
exit