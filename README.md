# Naccache Stern Knapsack birthday attack

We provide an improved and parallel implementation of a previous attack to Naccache-Stern knapsack (NSK) cryptosystem.

Reference
-----------
M. Anastasiadis, N. Chatzis and K. A. Draziotis, Birthday type attacks to the Naccache-Stern Knapsack cryptosystem, 
Information Proc.Letters (Elsevier) Vol. 138, October 2018, Pages 39-43. 

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
---------Start---------
P number bits : 600
msg    : 19947313142309510170280192
Hamming weight of msg: 7
Bound of the attack : 42
---------NS attack---------
Round : 1
h1 4
h2 3
Round's attack time : 4.563700s
Round : 2
h1 4
h2 3
Round's attack time : 4.575533s
Round : 3
h1 4
h2 3
msg = 19947313142309510170280192
Round's attack time : 4.587568s
Total time : 13.726801s
Average time : 4.575600s
```

## Running the tests

Explain how to run the automated tests for this system

## Authors

* **Vasileios Martidis**

## License

This project is licensed under the GPLv3 License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* [First version of this attack written in Sagemath](https://github.com/drazioti/python_scripts/tree/master/paper_ns)
