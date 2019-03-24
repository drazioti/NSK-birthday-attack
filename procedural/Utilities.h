
// Utilities.h
#ifndef Utilities_H
#define Utilities_H

#include <iostream>
#include <gmpxx.h> //GMP
#include <openssl/md5.h>
#include <vector>
#include<algorithm>
// for parallel
// #include<parallel/algorithm>
// for parallel end
using std::cout;
using std::endl;
using std::fixed;
using std::rand;
using std::string;
// for parallel
// using __gnu_parallel::sort;
// using __gnu_parallel::set_intersection;
// for parallel end
/**
 * compare only first element of a pair
 */
template <class T1, class T2 >
struct cmp_first {
    bool operator()(const std::pair<T1,T2>&p1, const std::pair<T1,T2>&p2) {
        return (p1.first<p2.first);
        // return (p1.second<p2.second);
    }
};
/**
 * compare only first element of a pair with given str
 */
template <class T1, class T2 >
struct cmp_first_with {
  cmp_first_with(T1 value):value_(value){}
  bool operator()(const std::pair<T1,T2>&p)const {
      return (value_==p.first);
    }
  private:
    T1 value_;
};

template <class T1, class T2 >
struct eq_first {
    bool operator()(const std::pair<T1,T2>&p1, const std::pair<T1,T2>&p2) {
        return (p1.first==p2.first);
    }
};

/**
 * intersect the vectors according to cmp_first
 */
template<typename K, typename V>
std::vector<std::pair<K,V>> intersection(std::vector<std::pair<K,V>>& v1,std::vector<std::pair<K,V>>& v2){
    std::vector<std::pair<K,V>> v3;
    sort(v1.begin(), v1.end(),cmp_first<K, V>());
    sort(v2.begin(), v2.end(),cmp_first<K, V>());
    set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v3),cmp_first<K, V>());
    return v3;
}
/**
 * take time and print
 */
double time_passed(time_t);
/**
 * convert a char to a number
 */
int char_to_num(char);
/**
 * convert mpz_class to unsinged long long int
 */
unsigned long long mpz_2_ull(mpz_class);
/**
 * return a random int smaller than int
 */
int random_function_test (int);
/**
 * number to first 6 of md5
 */
string to_md5_f6_str(mpz_class);

string msg_Gen(unsigned int,unsigned int);
#endif