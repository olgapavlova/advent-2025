cat out.txt | sort | uniq | awk '{s += $1} END {print s}'
