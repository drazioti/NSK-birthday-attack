# Naccache Stern Knapsack birthday attack

We provide an improved and parallel implementation of a previous attack ([1]) to Naccache-Stern knapsack (NSK) cryptosystem.

[1] M. Anastasiadis, N. Chatzis and K. A. Draziotis, Birthday type attacks to the Naccache-Stern Knapsack cryptosystem, 
Information Proc.Letters (Elsevier) Vol. 138, October 2018, Pages 39-43. 

For bugs refer to the original [repo](https://github.com/vamartid/NSK-birthday-attack). 

## Authors

* **Vasileios Martidis**

## License

This project is licensed under the GPLv3 License - see the [LICENSE.md](LICENSE.md) file for details.

## Getting Started

First you need to install the following programs.

* [GMP](https://gmplib.org/) - Arithmetic without limitations
* [args](https://github.com/Taywee/args) - Argument parsing library
* [OpenSSL](https://www.openssl.org/) - Used for the md5-hashes

and for the parallel version (optional)
* [Openmp](https://www.openmp.org/) - API specification for parallel programming

You will need to have installed the libraries in Built With section, have the latest g++ version to build the project.

To build the single core version,
```
cd procedural
make all2
```
To build the parallel version of this attack
```
cd parallel
make all2par
```
This make argument, builds the project and we get multy.out which is the excecutable.

### Running the attack

You can view how to use the arguments of the excecutable like this. 
```
./multy.out --help
```

After reading the help output. We can run for example an attack to a message with hamming 7 and p of 2048-bits and b=n/2-3  like this.
```
./multy.out -p 3 --ham 7 --sb 3
```

For instance 
```
./multy.out -p 1 --ham 7 --sb 0
---------Generating keys...
number bits of prime p: 600
message   : 19342886918842423195996160
Hamming weight of msg: 7
Bound of the attack : 42
---------Starting ...
Round : 1
h1 4
h2 3
time : 4.568272s
Round : 2
h1 4
h2 3
time : 4.586754s
Round : 3
h1 4
h2 3
msg = 19342886918842423195996160
time : 4.605926s
Overall time : 13.760952s
```

## Acknowledgments

* [First version of this attack written in Sagemath](https://github.com/drazioti/python_scripts/tree/master/paper_ns)
