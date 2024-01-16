#!/bin/bash

if [ $# -lt 1 ]; then
    echo "Il n'y a pas assez d'arguments.";
    exit 1;
fi

if [ $1 == "-h" ]; then
    echo "                                ╓─────────────────╖";
    echo "╔════════════════╦══════════════╣LISTE DES OPTIONS╠════════════════════════════════╗";
    echo "║                ║              ╙─────────────────╜                                ║";
    echo "║  -f <fichier>  ║ Renseigne le fichier d'entrée contenant les données à traiter.  ║";
    echo "║                ║                                                                 ║";
    echo "║  -d1           ║ Renvoie un histogramme horizontal listant les 10 conducteurs    ║";
    echo "║                ║    avec le plus de trajets différents.                          ║";
    echo "║  -d2           ║ Renvoie un histogramme horizontal listant les 10 conducteurs    ║";
    echo "║                ║    avec la plus longue distance totale parcourue.               ║";
    echo "║  -l            ║ Renvoie un histogramme vertical listant les 10 trajets les plus ║";
    echo "║                ║    longs.                                                       ║";
    echo "║  -t            ║ Renvoie un histogramme regroupé listant les 10 villes les plus  ║";
    echo "║                ║    traversées.                                                  ║";
    echo "║  -s            ║ Renvoie un graphique répertoriant les distances minimales,      ║";
    echo "║                ║    moyennes et maximales des étapes de chaque trajet.           ║";
    echo "╚════════════════╩═════════════════════════════════════════════════════════════════╝";
    exit 0;
fi

file="NULL";
dist1=0;
dist2=0;
long=0;
city=0;
stat=0;

for ((i=1; i<=$#; i++)); do
    if [ "${!i}" == "-f" ]; then
        i=$((i+1));
        file=${!i};
    fi
    if [ "${!i}" == "-d1" ]; then
        dist1=1;
    fi
    if [ "${!i}" == "-d2" ]; then
        dist2=1;
    fi
    if [ "${!i}" == "-l" ]; then
        long=1;
    fi
    if [ "${!i}" == "-t" ]; then
        city=1;
    fi
    if [ "${!i}" == "-s" ]; then
        stat=1;
    fi
done

if [ "$file" == "NULL" ]; then
    echo "Aucun fichier n'a été entré, veuillez entre le chemin d'un fichier valable.";
    exit 2;
fi

if [[ "$file" != "NULL" ]] && [[ $(($dist1 + $dist2 + $long + $city + $stat)) == 0 ]]; then 
    echo "Aucune option n'a été entrée ou les options entrées ne sont pas valides. Renseignez vous sur les options en executant la commande avec l'option -h.";
    exit 3;
fi

if [ $(($dist1 + $dist2 + $long + $stat)) -gt 1 ]; then
    echo "Vous avez selectionné trop d'options. Veuillez selectionner une option à la fois.";
    exit 4;
fi

if [ $dist1 == 1 ]; then
    LC_ALL=C sort -dk6 -t";" $file | cut --fields=1,6 -d ';' | LC_ALL=C mawk -F"," '!_[$1]++' | tr ';' ' ' | cut --fields=2,3 -d " " | uniq -c | LC_ALL=C mawk '{print $1 " " $2 " " $3}' | sort -nr | head -10  > res.csv;
    gnuplot -e "title_option='Option -d1'; xlabel_option='Nombre de trajets'" horiz_histo.plt;
    exit 0;
fi

if [ $dist2 == 1 ]; then
    LC_ALL=C sort -k6 -t";" -d $file | cut --fields=5,6 -d ';' | tr ';' ',' | tr ' ' '_' | LC_ALL=C mawk -F"," '{sum[$2]+=$1} END {for (name in sum) printf "%.3f %s\n", sum[name], name}' | tr '_' ' ' | tr ',' ' ' | sort -nr | head -10 > res.csv;
    gnuplot -e "title_option='Option -d2'; xlabel_option='Distance (en km)'" horiz_histo.plt;
    exit 0;
fi

if [ $long == 1 ]; then
    LC_ALL=C sort -k6 -t";" -d data.csv | cut --fields=1,5 -d ';' | LC_ALL=C mawk -F";" '{sum[$1]+=$2} END {for (name in sum) print sum[name] " " name}' | sort -n | tail -10 | sort -k2 -t" " -n > res.csv;
    gnuplot -e "title_option='Option -l'" verti_histo.plt;
    exit 0;
fi

if [ $city == 1 ]; then
    cut --fields=2,3,4 -d ";" $file | tail -n +2 > trips_data.csv;
    linecount=($(wc -l trips_data.csv));
    LC_ALL=C ./tri -t -lc $linecount;
    gnuplot histo_regroup.plt;
    exit 0;
fi

if [ $stat == 1 ]; then
    cut --fields=1,5 -d ";" $file | tail -n +2 > trips_distance.csv;
    linecount=($(wc -l trips_distance.csv));
    LC_ALL=C ./tri -s -lc $linecount;
    gnuplot graph.plt;
    exit 0;
fi