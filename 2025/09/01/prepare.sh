IN=${1:-input}
sort -t, -k1,1n $IN.txt > xup.txt
sort -t, -k2,2n $IN.txt > yup.txt
sort -t, -k1,1nr $IN.txt > xdown.txt
sort -t, -k2,2nr $IN.txt > ydown.txt
echo $IN
