reset
set terminal png size 800,800
width = 0.4
# Titre du graphique
set title "Histogramme du nombre de trajets par conducteur"

# Style de l'histogramme
set style fill solid border -1
set xrange [*:*]
set yrange [0:*]
set offsets 0,0,0.5-width/2.,0.5

# Utiliser des espaces comme séparateurs de colonnes
set datafile separator " "

# Spécifier les colonnes à utiliser
colonne_nom = 3
colonne_prenom = 2
colonne_trajets = 1


# Afficher l'histogramme
set output 'res.png'

plot "res.csv" using (0.5*column(colonne_trajets)):0:(0.5*column(colonne_trajets)):(width/2.):yticlabels(stringcolumn(colonne_prenom)." ".stringcolumn(colonne_nom)) with boxxy notitle linecolor rgb "#eca1c9"
exit