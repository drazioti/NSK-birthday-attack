#include <iostream>
//#include "Utilities.h"
#include "Ns.h"

// for parallel
// # include <omp.h>//openmp
// for parallel end
#include <gmpxx.h>//gmp c++ interface
#include <args.hxx>// argument lib args by Taywee

using std::srand;
using std::cout;
using std::endl;
using std::boolalpha;
using std::fixed;

int main(int argc, char **argv){
    // init / set field
    srand(rand() ^ time(NULL));                         // initilize the seed
    //set nested parallelism
    // omp_set_dynamic(0);
    // omp_set_nested(1);
    
    unsigned int n;                                     // decalre var n
    mpz_class p,q,*u,m,c,s,m2;                          // declare vars p,q,n,u,s
    Ns *ns=new Ns();                                    // declare ns object
    int lenp;                                           // declare p bit-length
    
    //declare Argument Parser
    args::ArgumentParser parser("This is an implementation of a propability attack\n to Naccache-Stern Knapsack cryptosystem.", "Make sure to place arguments right.");
    //declare Argument groups
    args::Group key_group(parser, "Key:", args::Group::Validators::All);
    args::Group msg_group(parser, "Message:", args::Group::Validators::Xor);
    args::Group bound_group(parser, "Bound:", args::Group::Validators::DontCare);
    args::Group testing_group(parser, "For testing purposes:", args::Group::Validators::DontCare);
    args::Group help_group(parser, "Help:", args::Group::Validators::DontCare);
    //declare Argument vars & flags
    args::ValueFlag<int> p_bits(key_group,"integer 1,2 or 3", "Size(bits) of the p\n\
 1 is for  600-bit p,\n\
 2 is for 1024-bit p,\n\
 3 is for 2048-bit p",{'p',"p_len"});
    args::ValueFlag<int> h_num(msg_group,"integer", "Hamming weight of the random generated message m.\n\
This vallue must belong to (0,n/2) where n is\n\
  42 if p's bits are  600\n\
  70 if p's bits are 1024\n\
 116 if p's bits are 2048 accordingly",{"ham","hamming"});
    args::ValueFlag<std::string> string_num_m(msg_group, "specific message", "Give specific message you sellected", {'m',"msg"});
    args::ValueFlag<std::string> string_num_m2(msg_group, "specific message", "Give specific message you sellected", {'b',"msg_bin"});
    args::Flag fixed_msg(msg_group, "Fix example", "Run a fixed input message from the main", {'f',"fixed"});
    args::ValueFlag<int> b_num(bound_group,"integer", "Number(#) to be subtracted from bound\n\
so that (n/2-#) > 0\n\
  42 if p's bits are  600\n\
  70 if p's bits are 1024\n\
 116 if p's bits are 2048 accordingly",{"sb","substruct"});
    args::Flag no_randomness(testing_group, "Randomness", "Disable randomness testing purposes", {'r',"randomness"});
    args::HelpFlag help(help_group, "help", "Display help menu", {'h', "help"});
    // Manage arguments
    try
    {
        parser.ParseCLI(argc, argv);
    }
    catch (const args::Completion& e)
    {
        std::cout << e.what();
        return 0;
    }
    catch (const args::Help&)
    {
        std::cout << parser;
        return 0;
    }
    catch (const args::ParseError& e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }
    catch (args::ValidationError e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }
    
    //print start
    cout<<"---------Start---------"<<endl;

    // Init bits of the p 
    if (p_bits) { 
        std::cout << "P number bits : ";
        switch(args::get(p_bits)) {
            case 1 : lenp=600;
                    break;
            case 2 : lenp=1024;
                    break;
            case 3 : lenp=2048;
                    break;
            default :
                    std::cout << "\nNot valid input, please check the help panel with -h , --help argument"<<std::endl;
                    return 1;
        }
        std::cout<<lenp<< std::endl;
    }
    
    // randomness check
    if (no_randomness) {
        std::cout << "Randomised OFF on I1,I2 of the attack" << std::endl; 
    }

    ns->choose_pk_sk(lenp,p,q,n,u,s);                    // set p,q,n,u,s

    // set message vallue
    if (fixed_msg){//this is for testing purpose
        std::cout << "Fixed input" << std::endl; 
        //testing for 8 hamming
        if(lenp==600){//600
            m=mpz_class("1000100000000000000000100000000000000000110000000000000000000000000000101000000000010",2);
        }else if(lenp==1024){//1024
            m=mpz_class("1000000000000000001000000000000000000000010000000000000000000001000000100000010000010000000000010000000000000000000000000000000000",2);
        }else if(lenp==2048){// 2048
            m=mpz_class("1001000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000001000000000000000000000000000001001000000000010000000000000000000000000000000000000000000000000000000100000",2);
            // m=mpz_class("29014238117495173910888882",10);                    // set m message vallue hamming 9
        }
    }else if(h_num){// generated msg with h hamming weight
        if(n/2-args::get(h_num)<0||args::get(h_num)<=0){
            //n/2 is the biggest because if we inverse each bit from 0 to 1 and from 1 to 0
            // we have a message with > n/2 hamming of zeros.
            std::cout << "\nNot valid input, please check the help panel with -h , --help argument"<<std::endl;
            return 1;
        }
        m=mpz_class(msg_Gen(n+1,args::get(h_num)),2);                       // generate a random message n+1 bit
    }else if(string_num_m){
        m=mpz_class(args::get(string_num_m),10);                       // set given message
    }else if(string_num_m2){
        m=mpz_class(args::get(string_num_m2),2);                       // set given message 
    }else{
        std::cout << "No message given" << std::endl;
    }
    
    // encrypt / decrypt field
    ns->encrypt(c,m,p,u);                               // encrypt and set c
    ns->decrypt(m2,c,n,p,s);                            // decrypt and set m

    // print field
    // cout<< "n " << n <<endl;
    // cout<< "p " << p <<endl;
    // cout<< "q " << q <<endl;
    cout<< "msg    : " << m <<endl;
    // cout<< "m bits : " << m.get_str(2) <<endl;
    // cout<< "c      : "<< c <<endl;
    // cout<< "m2     : " << m2 <<endl;

    // attack related field

    // init / set field
    int hamming = ns->popcount(m,n);                    // the hamming weight of the message m
    double bound = n/2;                              // the auxiliary variable bound. Here we choose bound = n/2
    
    //print hamming weight
    std::cout << "Hamming weight of msg: "<<hamming<<std::endl;
    // check if the new bound is valid
    if (b_num) { // b_num is being substracted from bound
        if( bound-args::get(b_num)<=0){
            std::cout << "\nNot valid input, please check the help panel with -h , --help argument"<<std::endl;
            return 1;
        }
        bound = bound - args::get(b_num);
    }
    
    int flag = 0;                                       // bound n/2 goes with flag=0

    // print field 2
    // cout<<"Hamming : "<<hamming<<endl;
    cout << "Bound of the attack : "<<bound<<endl;
    cout<<"---------NS attack---------"<<endl;
    //init vars of the main program rounds number result and total time
    unsigned int round=0;                                   // var to count attack rounds
    bool res =false;                                        // var for the result of each attack loop
    double clock_total=0;                                   // var for the total attack time
    // keep attacking till the result of the attack is True (success)
    while(!res){
        // init vars
        int s1,s2,*I1,*I2;                                              // lists
        mpz_class *U1,*U2;                                              // declare vars I1,I2,U1,U2
        // start
        round++;                                                        // increment round
        cout <<"Round : "<< round <<endl;                               // print round num
        ns->gen(n,bound,flag,p,u,I1,I2,U1,U2,s1,s2,no_randomness);      // set I1,I2 & generate U1,U2
        // set starting time var
        time_t start_time = clock();                                    // start time of the attack
        res = ns->attack(n,bound,p,c,hamming,s,flag,I1,I2,U1,U2,s1,s2); // perform the NS attack and print it's result
        double round_time=time_passed(start_time);                      // time after this round of attack
        cout << "Round's attack time : "   << fixed << round_time <<"s" << endl;   // print total time
        clock_total=clock_total+round_time;                             // increase total time with the round time
        
        //clear field
        // free I1 array and I2 psevdo-array 
        delete[] I1;
        // I do not need to free I2 because the pointer 
        // is looking to the I1[bound] vallue which is already
        // free by excecuting free(I1)
        delete[] U1;
        delete[] U2;
    }
    cout << "Total time : "   << fixed << clock_total <<"s" << endl;          // print total time
    cout << "Average time : " << fixed << clock_total/round <<"s" << endl;    // print average time per round
    
    // free Ns obj
    delete ns;
    // free u array
    delete[] u;
    // end the program successfuly
    return 0;
}
