Compiled in Debian system (Debian 3.16.51-2 (2017-12-03) x86_64 GNU/Linux) with g++ 9.4.2-10.

```
$ /usr/bin/time -f "%E %C" ./attack_parallel_deb.out -p 1 --ham 7
---------Generating keys...
number bits of prime p: 600
msg    : 19531716996520891069267968
Hamming weight of msg: 7
Bound of the attack : 42
---------Starting ...
Round : 1
Round : 2
Round : 3
Round : 4
Round : 5
Round : 6
Round : 7
msg = 19531716996520891069267968
0:13.89 ./attack_parallel_deb.out -p 1 --ham 7
```
If you want to run say 10 times the program
```
$n=0; while [[ $n -lt 10 ]]; do /usr/bin/time -f "%E %C" ./attack_parallel_deb.out -p 1 --ham 7; n=$((n+1)); done
```
The algorithm uses so many cores as there are free in our system.
