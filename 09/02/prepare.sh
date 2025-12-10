IN=${1:-input}
sort -t, -k1,1n $IN.txt > x-direct.txt
sort -t, -k2,2n $IN.txt > y-direct.txt
sort -t, -k1,1nr $IN.txt > x-reverse.txt
sort -t, -k2,2nr $IN.txt > y-reverse.txt
