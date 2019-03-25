


##INSTALL on raspberry pi3
Install gmpxxx
```
sudo apt install libgmp-dev
```

Install openssl
```
$git clone git://git.openssl.org/openssl.git
$cd openssl
$./config
$make
$make test
$sudo make install
```
Install args

```
$git clone https://github.com/Taywee/args.git
$cd args
$sudo make install
```
Then,
```
$git clone https://github.com/drazioti/NSK-birthday-attack.git
$cd /NSK-birthday-attack/procedural
$make all2
```

```
$./multy.out -p 1 --ham 7 --sb 0
---------Generating keys...
number bits of prime p: 600
message   : 19349906031045596210659328
Hamming weight of msg: 7
Bound of the attack : 42
---------Starting ...
Round : 1
h1 4
h2 3
time : 9.272646s
Round : 2
h1 4
h2 3
time : 9.324088s
Round : 3
h1 4
h2 3
msg = 19349906031045596210659328
time : 9.316042s
Overall time : 27.912776s
```