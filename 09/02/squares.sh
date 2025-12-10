awk -F',' '{ print ($3-$1 + 1)*($4-$2 + 1)}' squares.txt | sort -n
