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
dist_min_max_moy=0;

for ((i=1; i<=$#; i++)); do
    if [ "${!i}" == "-f" ]; then
        file=$(($i+1));
        i=$((i+1))
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
done

if [ "$file" == "NULL" ]; then
    echo "Aucun fichier n'a été entré, veuillez entre le chemin d'un fichier valable.";
    exit 2;
fi

if [ $dist1 == 1 ]; then
    sort -k6 -t";" -d data.csv | cut --fields=1,6 -d ';' | mawk -F"," '!_[$1]++' | tr ';' ' ' | cut --fields=2,3 -d " " | uniq -c | mawk '{print $1 " " $2 " " $3}' | sort -n | tail -10  > res.csv;
    gnuplot horiz_histo.plt;
    exit 0;
fi

if [ $dist2 == 1 ]; then
    sort -k6 -t";" -d data.csv | cut --fields=5,6 -d ';' | mawk -F"," '!_[$1]++' | tr ';' ',' | tr ' ' ',' > res.csv;
    mawk '{sum[$3]+=$1} END {for (name in sum) print name, sum[name]}' res.csv > test.csv;
    exit 0;
fi