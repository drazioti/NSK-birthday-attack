We can use the bash script as follows

```
$./script.sh a b c d

where a : the number of iterations,
      b : 1 or 2 or 3, the parameter -p,
      c : Hamming, the parameter --ham,
      d : the parameter --sb 
      e.g.
$./script.sh 2 1 6 0
---------Generating keys...
number bits of prime p: 600
msg    : 20589517865311653402247200
Hamming weight of msg: 6
Bound of the attack : 42
---------Starting ...
Round : 1
msg = 20589517865311653402247200
0:00.85 ./attack_parallel_rasp.out -p 1 --ham 6 --sb 0
---------Generating keys...
number bits of prime p: 600
msg    : 19361702579774358666346496
Hamming weight of msg: 6
Bound of the attack : 42
---------Starting ...
Round : 1
Round : 2
msg = 19361702579774358666346496
0:01.34 ./attack_parallel_rasp.out -p 1 --ham 6 --sb 0

```
