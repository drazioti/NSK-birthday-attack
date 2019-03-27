n=0; 
while [[ $n -lt $1 ]]; 
   do /usr/bin/time -f "%E %C" ./attack_parallel_rasp.out -p $2 --ham $3 --sb $4; 
   n=$((n+1)); 
done

