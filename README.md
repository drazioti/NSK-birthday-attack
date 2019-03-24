# Naccache Stern Knapsack birthday attack

We provide an improved and parallel implementation of a previous attack to Naccache-Stern knapsack (NSK) cryptosystem.

Reference
-----------
M. Anastasiadis, N. Chatzis and K. A. Draziotis, Birthday type attacks to the Naccache-Stern Knapsack cryptosystem, 
Information Proc.Letters (Elsevier) Vol. 138, October 2018, Pages 39-43, 

## Getting Started

You will need to have installed the libraries in Built With section, have the latest g++ version to build the project.

To build the single core version,
```
make all2
```
To build the parallel version of this attack
```
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

## Running the tests

Explain how to run the automated tests for this system

## Built With

* [Openmp](https://www.openmp.org/) - API specification for parallel programming
* [GMP](https://gmplib.org/) - Arithmetic without limitations
* [OpenSSL](https://www.openssl.org/) - Used for the md5-hashes
* [args](https://github.com/Taywee/args) - Argument parsing library

## Authors

* **Vasileios Martidis**

## License

This project is licensed under the GPLv3 License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* [First version of this attack](https://github.com/drazioti/python_scripts/tree/master/paper_ns)

