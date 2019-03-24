// Ns.h

#ifndef Ns_H
#define Ns_H

#include <iostream> //cout
#include <algorithm>// std::random_shuffle
// for parallel
// #include<parallel/algorithm>
// for parallel end
#include <math.h>   //floor
#include <gmpxx.h>//gmp c++ interface
//# include <omp.h>//openmp
using std::cout;
using std::cerr;
using std::endl;
using std::fixed;
using std::rand;
using std::srand;
using std::random_shuffle;
using std::nothrow;
// for parallel
// using __gnu_parallel::find_if;
// for parallel end
#include "Utilities.h"
#include "Combinations.h"

class Ns{
    public:
        // Constructor-Destructor
        Ns(); //constructor of Ns obj
        ~Ns(); //destructor of Ns obj deletes primes array
        // Other public functions
        void choose_pk_sk(int,mpz_class&,mpz_class&,unsigned int&,mpz_class*&,mpz_class&); //init vars
        void encrypt(mpz_class&,mpz_class,mpz_class,mpz_class*); //encrypt message
        void decrypt(mpz_class&,mpz_class,unsigned int,mpz_class,mpz_class); //decrypt message
        int popcount(mpz_class,int);// calculate the hamming weight of the mpz number
        void gen(unsigned int,double,int,mpz_class,mpz_class*,int*&,int*&,mpz_class*&,mpz_class*&,int&,int&,bool);
        bool attack(unsigned int,double,mpz_class,mpz_class,int,mpz_class,int,int*,int*,mpz_class*,mpz_class*,int,int);
    
    private: 
        // Private fields 
        mpz_class *primes; //primes ptr for the array
        // Private functions
        void set_primes_mpz(int); //init primes
        void init(mpz_class,mpz_class,mpz_class*&,unsigned int); //init u
        void func2(std::vector <std::pair <std::string,std::vector<short>>>&,mpz_class*&,int,int,mpz_class,mpz_class); //init M lists
        std::string prod_of_f2_when_c_bigger_1(std::vector<short> cmb,mpz_class *&L,mpz_class& p,mpz_class& c);
        std::string prod_of_f2_when_c_not_bigger_1(std::vector<short> cmb,mpz_class *&L,mpz_class& p,mpz_class& c);
        void custom_mulinv(mpz_class &res,mpz_class num,mpz_class p);
        void modd_mpz_class_ui(mpz_class &res,mpz_class base,long int exp,mpz_class mod);
        void construct_msg_mpz(mpz_class &,int*&,std::vector<short>,int&,int*&,std::vector<short>,int&);
};
#endif
