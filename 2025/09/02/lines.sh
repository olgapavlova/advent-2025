awk -F',' '{ count[$1]++ } END { print "WRONG COLS:"; for (x in count) if (count[x] != 2) { print "\t", x, count[x] } }' input.txt
awk -F',' '{ count[$2]++ } END { print "WRONG ROWS:"; for (x in count) if (count[x] != 2) { print "\t", x, count[x] } }' input.txt
