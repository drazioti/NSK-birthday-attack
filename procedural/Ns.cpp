// Ns.cpp
#include "Ns.h"

/**
 * constructor of Ns obj
 */
Ns::Ns(){}

/**
 * destructor of Ns obj
 */
Ns::~Ns(){
    // free primes array
    delete[] this->primes;
}

/**
 * init vallues of p,q,n,s according to lenp & call init function to set u
 */
void Ns::choose_pk_sk(int lenp,mpz_class &p,mpz_class &q,unsigned int &n,mpz_class *&u,mpz_class &s){
    //calculate
    //check the length of p and set the vallues
    if(lenp==600){
        n = 84;
        p=mpz_class("2074757784440496479256203931845580575506223116121218449997828664845326405706454073199853524473551897144098943305650394591197575537705887653943437417056981843530590901700771609797439",10);
        q=mpz_class("1037378892220248239628101965922790287753111558060609224998914332422663202853227036599926762236775948572049471652825197295598787768852943826971718708528490921765295450850385804898719",10);
    }else if(lenp==1024){
        n = 130;//n = 130;
        p=mpz_class("356016873783498533947581036092641272306360368050925808571238846207127055154301347886337239040241779594156481218243271432984000696808011616039210639390840176709567072017753811949256718002480410000475130359737947125690893606890239817035840801874264111611236566297668497801840516568157731657056332626732525479259",10);
        q=mpz_class("178008436891749266973790518046320636153180184025462904285619423103563527577150673943168619520120889797078240609121635716492000348404005808019605319695420088354783536008876905974628359001240205000237565179868973562845446803445119908517920400937132055805618283148834248900920258284078865828528166313366262739629",10);
    }else if(lenp==2048){
        n = 232;
        p=mpz_class("49602036983371092259147540363584647204071653867172430513214426393945899721358727738639843690176877714453506962352346127699675984824298521566661548583161306302109776282592070527665917209557680638514225792771513660101454532957236581944526547561559549110008028374143260964378198717998418190150986828475191457976974248469899690659796179217094422955203899925977675132323008288807247334985222480184208553922524595153266221641790574520331591186042123578501071416938635911581975938357315995683256002600487269950091337172447883358779407250169914463238033964605233448547936216145839488555331364566643703592667232766768858537619",10);
        q=mpz_class("24801018491685546129573770181792323602035826933586215256607213196972949860679363869319921845088438857226753481176173063849837992412149260783330774291580653151054888141296035263832958604778840319257112896385756830050727266478618290972263273780779774555004014187071630482189099358999209095075493414237595728988487124234949845329898089608547211477601949962988837566161504144403623667492611240092104276961262297576633110820895287260165795593021061789250535708469317955790987969178657997841628001300243634975045668586223941679389703625084957231619016982302616724273968108072919744277665682283321851796333616383384429268809",10);
    }
    
    // Set up the secret key
    s=mpz_class("5649012341",10);     
    
    // //print setted vallues
    // cout<< "n " << n <<endl;
    // cout<< "p " << p <<endl;
    // cout<< "q " << q <<endl;
    // cout<< "s " << s <<endl;

    //allocate space for primes
    this->primes = new (nothrow) mpz_class [n+1];
    //throw error msg if you can not allocate memory for primes array
    if (this->primes == nullptr) {
        cerr << "Could not allocate primes array" << endl;
    }else{
        // set up the primes field
        set_primes_mpz(n+1);
        //delete[(unsigned int)(n+1)] this->primes;
        
        // // print primes array
        // for(unsigned long i=0;i<n;i++){
        //     cout << " " << primes[i]<< ",";
        // }
        // cout<<endl;
    }

    // allocate space for u list
    u = new (nothrow) mpz_class [n+1];
    //throw error msg if you can not allocate memory for u array
    if (u == nullptr) {
        cerr << "Could not allocate u array" << endl;
    }else{
        // init u array
        init(s,p,u,n+1);

        // // print u array
        // for(unsigned long i=0;i<n+1;i++){
        //     cout << u[i]<< endl;
        // }
        // cout<<endl;
    }
}

/**
 * sets the prime array with the first n primes
 */
void Ns::set_primes_mpz(int n){
    //declare
    // create a counter vallue for the primes found
    int counter=0;
    
    //calculate
    // start a for loop from 0 until you find n primes 
    for(unsigned long i=0;counter<n;i++){
        //set the next number to the array vallue 
        this->primes[counter]=i;
        //check if it's a prime number
        if(mpz_probab_prime_p(this->primes[counter].get_mpz_t(),25)==2){
            // mpz_init_set_ui(primes[counter],i);
            counter++;
        }
    }
}

/**
 * init the u list by caluclating the prod
 */
void Ns::init(mpz_class s,mpz_class p,mpz_class *&u,unsigned int n){
    //declare field
    mpz_class exponent, p_minus_1=p-1;
    //set p_minus_1 as p-1 so that you dont have to do cast on each loop

    //construct/calculate public key (list of n+1 ints)
    for (int i = 0; i < n; i++) {//init the u list
        mpz_invert(exponent.get_mpz_t(), s.get_mpz_t(), p_minus_1.get_mpz_t());//set exponent as s^(-1) MOD p-1
        mpz_powm(u[i].get_mpz_t(),primes[i].get_mpz_t(),exponent.get_mpz_t(),p.get_mpz_t());//set ui as primes[i]^exponent MOD p
    }
}

/**
 * encrypt message m by using public key and set c
 */
void Ns::encrypt(mpz_class& c,mpz_class m,mpz_class p,mpz_class *u){
    //declare field
    mpz_class to_be_multiplied, prod=1;
    //declare and set starting value of the prod
    
    //calculate field
    
    //calculate the number of bits
    size_t size_of_message = mpz_sizeinbase(m.get_mpz_t(),2);
    // cout << size_of_message << endl; // print the size of the message
    
    //prod calculation
    for(int i=(size_of_message-1);i>-1;i--){
        mpz_pow_ui(to_be_multiplied.get_mpz_t(),u[i].get_mpz_t(),mpz_tstbit (m.get_mpz_t(), i));//calculate the u[i]^bit[i]
        prod = prod * to_be_multiplied;//multiply the last prod with the new calculation
    }
    //set the c
    c = prod % p;   //do the modulo prod MOD p
}

/**
 * decrypt cyphertext c by using public and secret key and set m 
 */
void Ns::decrypt(mpz_class &m,mpz_class c,unsigned int n,mpz_class p,mpz_class s){

    //declaration field
    mpz_class cs,
            gcd_res,
            gcd_minus_1,
            two_powered,
            dividend,
            divisor,
            to_be_summed,
            sum=0;
    //set sum as 0 before starting to add

    //calculate field
    mpz_powm(cs.get_mpz_t(),c.get_mpz_t(),s.get_mpz_t(),p.get_mpz_t()); //calculate c^s MOD p
    //sum calculation
    for (int i = 0; i < n+1; i++) {
        mpz_gcd(gcd_res.get_mpz_t(),cs.get_mpz_t(),primes[i].get_mpz_t());  //gcd(cs,prime[i])
        gcd_minus_1 = gcd_res-1;    //gcd -1
        mpz_ui_pow_ui(two_powered.get_mpz_t(),2,i); //2^i
        mpz_mul(dividend.get_mpz_t(),gcd_minus_1.get_mpz_t(),two_powered.get_mpz_t());  //multiply the gcd*2^i and set div
        divisor = primes[i]-1;              // primes-1
        to_be_summed = dividend / divisor;  // div/prime-1 
        sum = sum + to_be_summed;           //sum the last sum with the new calculation
    }
    
    //set the m
    m = sum;
}

/**
 * calculate the hamming weight of the mpz number
 */
int Ns::popcount(mpz_class number, int n){
    // declare field
    int hamming = 0;
    // calculation field
    // for each bit check the value
    for(int i=0;i<n+1;i++){
        //test bit on i possition
        if(mpz_tstbit (number.get_mpz_t(), i)){
            hamming++;
        }
    }
    return hamming;
}

void Ns::gen(unsigned int n,double bound1,int flag,mpz_class p,mpz_class *u,int *&I1,int *&I2,mpz_class *&U1,mpz_class *&U2,int &s1,int &s2,bool randomness_off){
    int a1=0,
        b1=n,
        bound=floor(bound1);
    //s1 size of U1 and I1
    //s2 is size of U2 and I2
    
    //remember
    //check floor of bound1 later
    if(bound>=b1-a1){
        cout << "bound must be smaller than "<< b1-a1<<endl;
        return;
    }else if(flag!=0&&flag!=2){
        cout << "flag should be 0 or 2 "<<endl;
        return;
    }else if(flag==0){
        //bound   is the size of the U1 list when flag is 1
        //n-bound is the size of the U2 list when flag is 1
        
        //I need to ask for the random function why is there n and not n+1

        //create an array of n+1 and give it to the I1
        I1=new int[n+1];
        for(int i =0;i<n+1;i++){
            I1[i]=i;
        }
        
        if(!randomness_off){
            // //shuffle the array we created
            random_shuffle(&I1[0], &I1[n+1],random_function_test);
        }else{
            //check the size of the message
            // //set certain shuffle for testing purpose   
            if (n= 84){
                int cer[]={16, 4, 19, 30, 44, 32, 9, 41, 24, 31, 54, 25, 23, 84, 35, 52, 27, 11,
                46, 21, 80, 17, 47, 82, 81, 61, 66, 65, 53, 10, 64, 48, 67, 26, 76, 2,
                60, 39, 12, 68, 7, 28,57, 63, 79, 58, 69, 18, 33, 42, 59, 1, 62, 22, 70, 0, 13, 15, 50, 55,
                73, 37, 34, 74, 6, 20, 14, 51, 8, 43, 5, 3, 29, 40, 77, 56, 72, 71, 36,
                75, 49, 83, 45, 78, 38};
                for(int i =0;i<n+1;i++){
                    I1[i]=cer[i];
                }
            }else if (n=130){
                int cer[] ={107, 7, 109, 119, 10, 18, 62, 64, 38, 34, 58, 80, 88, 1, 59, 90, 56, 91,
                25, 11, 57, 126, 111, 36, 46, 47, 5, 86, 4, 2, 9, 114, 43, 124, 122, 35, 52, 31, 20, 28,
                26, 104, 3, 121, 117, 118, 42, 71, 100, 70, 30, 98, 24, 72, 75, 102, 69, 68, 113, 13, 61,
                6, 73, 89, 82, 15, 39, 97, 63, 123, 101, 74, 105, 54, 66, 87, 116, 84, 112, 21, 45, 55,
                96, 93, 125, 22, 127, 44, 95, 23, 83, 65, 92, 94, 33, 103, 115, 128, 14, 48, 27, 29, 0,
                12, 37, 19, 120, 40, 76, 129, 41, 108, 53, 81, 51, 99, 17, 32, 78, 106, 77, 16, 60, 50,
                130, 67, 8, 110, 85, 79, 49};
                for(int i =0;i<n+1;i++){
                    I1[i]=cer[i];
                }
            }else if (n=232){
                int cer[] ={133, 130, 55, 86, 97, 3, 219, 139, 200, 45, 87, 40, 27, 18, 71, 121,
                81, 224, 72, 164, 54, 76, 126, 12, 122, 159, 174, 0, 172, 88, 21, 41,
                51, 63, 113, 94, 49, 24, 100, 161, 56, 146, 173, 182, 209, 99, 33,
                135, 39, 20, 38, 153, 74, 231, 186, 127, 70, 118, 166, 202, 171,
                221, 142, 178, 60, 42, 203, 183, 92, 206, 181, 212, 34, 215, 218,
                30, 95, 25, 84, 10, 228, 105, 196, 137, 217, 7, 192, 220, 131, 222,
                140, 68, 85, 36, 29, 214, 169, 193, 14, 110, 83, 9, 230, 112, 129,
                168, 8, 19, 154, 210, 144, 80, 31, 103, 211, 107, 58, 150, 4, 136,
                152, 52, 216, 115, 227, 123, 194, 16, 145, 5, 59, 175, 185, 44, 179,
                207, 46, 106, 98, 205, 96, 156, 89, 93, 191, 79, 180, 1, 225, 104,
                90, 82, 229, 170, 61, 187, 66, 167, 149, 138, 195, 67, 11, 15, 141,
                109, 232, 91, 47, 64, 184, 50, 157, 188, 148, 114, 75, 6, 155, 226,
                176, 116, 223, 190, 101, 28, 120, 119, 65, 22, 23, 53, 213, 77, 198,
                2, 125, 102, 143, 26, 199, 35, 177, 204, 43, 17, 165, 57, 124, 197,
                208, 108, 78, 134, 160, 37, 151, 73, 13, 163, 201, 117, 189, 111,
                62, 132, 48, 32, 162, 147, 69, 158, 128};
                for(int i =0;i<n+1;i++){
                    I1[i]=cer[i];
                }
            }
        }
        

        // cout <<"copied"<<endl;
        // //print the array
        // for(int i =0;i<n+1;i++){
        //     cout << I1[i]<<", ";
        // }cout<< endl;
        
        //set the size vars
        s1 = bound;
        if(bound1==n/2){//if the bound is n/2
            //give the seccond array n - n/2
            s2 = (n+1)-bound;
            // cout<< "here -1" <<endl;
        }else{//else if the bound is smaller
            //do the following
            // s2 = bound;
            // cout<< "bound is "<<bound <<endl;
            //because there is a part of the I1 array we do not need
            //I need to free the cells from the memmory
            //so I reallocate 2 arrays copy I1 and I2 there and delete the old one
            
            int newSize=2*bound; //set a size for the new array and allocate the memmory
            int *newI1=new int[newSize];
            std::copy(I1,I1+(newSize), newI1); //copy the wanted content
            // //print the newI1
            // cout << "newI1"<<" ";
            // for(int i =0;i<newSize;i++){
            //     cout << newI1[i]<<" ";
            // }cout <<endl;
            delete[] I1; //delete the old array
            I1=newI1; //set the new created array as the I1
            // check if there is a n and do accordingly 
            bool has_n=false;
            int i = 0;
            do{
                if(I1[i]==n){
                    has_n=true;
                }
                i++;
            }while(!has_n && i<newSize);
            if(!has_n){// if a n is not found set a random cell n
                // cout<< "No n found"<<endl;
                int pos =random_function_test (newSize);
                // pos = newSize-1;
                // cout<< "pos "<<pos<<endl;
                newI1[pos] = n;
                // cout<< "Set n"<<endl;
            }//if a n is found do nothing
            //give the seccond array n - n/2
            s2 = newSize-bound;
        }

        //set the I2 begin at array at the bound1
        I2=&I1[bound];
        /*
         //print the I1
         cout << "I1["<<s1<<"]"<<" ";
         for(int i =0;i<s1;i++){
             cout << I1[i]<<" ";
         }cout <<endl;
         //print the I2
         cout << "I2["<<s2<<"]"<<" ";
         for(int i =0;i<s2;i++){
             cout << I2[i]<<" ";
         }cout <<endl;
         */
    }else if(flag==2){
        //bound or bound+1  is the size of the U1 list when flag is 2
        //bound is the size of the U2 list when flag is 2
        
        //need to be done

        //python code
        // hash = hashlib.md5(os.urandom(2*n)).digest()
        // random.seed(hash)
        // L = random.sample(range(a1,b1+1), 2*bound)
        // I1 = L[0:bound]
        // I2 = L[bound:2*bound]
        // if n not in list(set.union(set(I1),set(I2))):
        //     I1 = I1 + [n]

    }

    //init & calculate U1
    // allocate space for u list
    U1 = new (nothrow) mpz_class [s1];
    //throw error msg if you can not allocate memory for u array
    if (U1 == nullptr) {
        cerr << "Could not allocate U1 array" << endl;
    }else{
        for (int i = 0; i < s1; i++) {//init the u list
            U1[i] = u[I1[i]] % p;//set U1[] vallue at cell I1[i] with u MOD p
        }
    }
    
    // //print U1
    // for(unsigned long i=0;i<s1;i++){
    //     cout<<i<<" "<< U1[i]<<endl;
    // }cout<<endl;

    //init & calculate U2
    U2 = new (nothrow) mpz_class [s2];
    //throw error msg if you can not allocate memory for u array
    if (U2 == nullptr) {
        cerr << "Could not allocate U2 array" << endl;
    }else{
        for (int i = 0; i < s2; i++) {//init the u list
            U2[i] = u[I2[i]] % p;//set U2[] vallue at cell I1[i] with u MOD p
        }
    }

    // //print U2
    // for(unsigned long i=0;i<s2;i++){
    //     cout<<i<<" "<< U2[i]<<endl;
    // }cout<<endl;
}

bool Ns::attack(unsigned int n,double bound1,mpz_class p,mpz_class c,int hamming,mpz_class s,int flag,int* I1,int* I2,mpz_class* U1,mpz_class* U2,int s1,int s2){
    int a1=0,
        b1=n,
        bound=floor(bound1);
    // check the bound value if it is not right skip the attack
    if (bound>=b1-a1){
        cerr<<"Bound must be < b1-a1, please try again."<<endl;
        flag=3;
    }
    // check the flag value
    if (flag==0||flag==2){
        //declare vars
        int lim;
            // a1=0,//not needed variable
            // b1=n,//not needed variable
        unsigned long long number_of;
        mpz_class m; //create a variable for the message to check result later
        // declare M1,M2,M3 lists of number and md5
        std::vector <std::pair <std::string,std::vector<short>>> M1,M2;
        //set lim according to hamming weight
        int h1,h2;
        if(hamming%2==0){
            h1=hamming/2;
            h2=h1;
        }else{
            h1=(hamming+1)/2;
            h2=h1-1;
        }
        cout<< "h1 "<<h1<<endl;
        cout<< "h2 "<<h2<<endl;
        // set m as the message 
        this->decrypt(m,c,n,p,s);
        // construction of the first set {prod(ui^ei)}
        func2(M1,U1,s1,h1,p,mpz_class(1));
        func2(M2,U2,s2,h2,p,c);
        // declare intersection list of number and md5
        std::vector <std::pair <std::string,std::vector<short>>> inters = intersection(M1, M2);
        // delete duplicates
        inters.erase( unique( inters.begin(), inters.end(),eq_first<std::string,std::vector<short>>() ), inters.end() );
        // set capacity to size 
        inters.shrink_to_fit();
        
        mpz_class tmp_msg;
        if(!inters.empty()){
            // cout<<"----INSIDE----"<<endl;
            if(inters.size()==1){//if size is 1 then it's the solution
                //reconstruct message for the solution
                std::string sol=inters.at(0).first;
                std::vector <std::pair <std::string,std::vector<short>>>::iterator it1 = find_if(M1.begin(), M1.end(),cmp_first_with<std::string,std::vector<short>>(sol));;
                std::vector <std::pair <std::string,std::vector<short>>>::iterator it2 = find_if(M2.begin(), M2.end(),cmp_first_with<std::string,std::vector<short>>(sol));;
                //print info of pairs
                // std::cout<<"M1 pair : " <<it1->first <<" ";
                // for(int i=0;i<it1->second.size();++i){
                //     std::cout<<it1->second[i]<<",";
                // }
                // std::cout<<std::endl;
                // std::cout<<"M2 pair : " << it2->first <<" ";
                // for(int i=0;i<it2->second.size();++i){
                //     std::cout<<it2->second[i]<<",";
                // }
                // std::cout<<std::endl;
                // std::string r1=std::string(s1-mpz_sizeinbase(it1->second.get_mpz_t(),2),'0')+it1->second.get_str(2);
                // std::string r2=std::string(s2-mpz_sizeinbase(it2->second.get_mpz_t(),2),'0')+it2->second.get_str(2);
                //create var for the message
                mpz_class msg;
                construct_msg_mpz(msg,I1,it1->second,s1,I2,it2->second,s2);
                
                
                if(msg==m){//compare m with our message
                    // // print msg
                    std::cout <<"msg = "<<msg<<std::endl;
                    // cout << "before1"<<endl;
                    // cout<<"M1 capacity = "<<M1.size()<<" "<<"M1 capacity = "<<M1.capacity()<<endl;
                    // cout<<"M2 capacity = "<<M2.size()<<" "<<"M2 capacity = "<<M2.capacity()<<endl;
                    // cout<<"M3 capacity = "<<M3.size()<<" "<<"M3 capacity = "<<M3.capacity()<<endl;
                    M1.clear();
                    M2.clear();
                    // M3.clear();
                    // M1.shrink_to_fit(); // Capacity of v is now 0
                    // M2.shrink_to_fit(); // Capacity of v is now 0
                    // M3.shrink_to_fit(); // Capacity of v is now 0
                    std::vector <std::pair <std::string,std::vector<short>>> (M1).swap(M1);
                    std::vector <std::pair <std::string,std::vector<short>>> (M2).swap(M2);
                    // std::vector <std::pair <std::string,std::vector<short>>> (M3).swap(M3);
                    // cout << "after"<<endl;
                    // cout<<"M1 capacity = "<<M1.size()<<" "<<"M1 capacity = "<<M1.capacity()<<endl;
                    // cout<<"M2 capacity = "<<M2.size()<<" "<<"M2 capacity = "<<M2.capacity()<<endl;
                    // cout<<"M3 capacity = "<<M3.size()<<" "<<"M3 capacity = "<<M3.capacity()<<endl;
                    // delete M1;
                    // delete M2;
                    // delete M3;
                    // std::vector <std::pair <std::string,mpz_class>> ().swap(M1);
                    // std::vector <std::pair <std::string,mpz_class>> ().swap(M2);
                    // std::vector <std::pair <std::string,mpz_class>> ().swap(M3);
                    
                    // cout<<"inters capacity = "<<inters.size()<<" "<<"inters capacity = "<<inters.capacity()<<endl;
                    // std::vector <std::pair <std::string,mpz_class>> ().swap(inters);
                    // cout<<"inters capacity = "<<inters.size()<<" "<<"inters capacity = "<<inters.capacity()<<endl;
                    
                    inters.clear();
                    std::vector <std::pair <std::string,std::vector<short>>> (inters).swap(inters);
                    
                    return true;
                }
                // //check it it is the same message with the decrypted;
            }else{
                for(int i=0;i<inters.size();i++){
                    //reconstruct message for each possible solution
                    std::string sol=inters.at(i).first;
                    std::vector <std::pair <std::string,std::vector<short>>>::iterator it1 = find_if(M1.begin(), M1.end(),cmp_first_with<std::string,std::vector<short>>(sol));;
                    std::vector <std::pair <std::string,std::vector<short>>>::iterator it2 = find_if(M2.begin(), M2.end(),cmp_first_with<std::string,std::vector<short>>(sol));;
                    //print info of pairs
                    // std::cout<<"M1 pair : " <<it1->first <<" ";
                    // mpz_out_str(stdout,10,it1->second.get_mpz_t());//print
                    // std::cout<<std::endl;
                    // std::cout<<"M2 pair : " << it2->first <<" ";
                    // mpz_out_str(stdout,10,it2->second.get_mpz_t());//print
                    // std::cout<<std::endl;
                    // std::string r1=std::string(s1-mpz_sizeinbase(it1->second.get_mpz_t(),2),'0')+it1->second.get_str(2);
                    //s1 lenght of I1 and of max num of cmb e.g. (cmb(len,ham)  len is s1)
                    //so s1-mpz_size_in_base2 
                    //are the remaining length if we remove from s1 the number of diggits of the mpz num in base2
                    //which is a number starting from 1 always so if it's smaller than the s1 it removes the zeros from start
                    //so this part are only the non visible zeros
                    //lastly we append the number in base of 2
                    // std::string r2=std::string(s2-mpz_sizeinbase(it2->second.get_mpz_t(),2),'0')+it2->second.get_str(2);
                    //create var for the message
                    mpz_class msg;
                    construct_msg_mpz(msg,I1,it1->second,s1,I2,it2->second,s2);
                    if(tmp_msg!=msg){//compare msg with last message found
                        if(msg==m){//compare m with our message
                            // // print msg
                            std::cout <<"msg = "<<msg<<std::endl;
                            // cout << "before2"<<endl;
                            // cout<<"M1 capacity = "<<M1.size()<<" "<<"M1 capacity = "<<M1.capacity()<<endl;
                            // cout<<"M2 capacity = "<<M2.size()<<" "<<"M2 capacity = "<<M2.capacity()<<endl;
                            // cout<<"M3 capacity = "<<M3.size()<<" "<<"M3 capacity = "<<M3.capacity()<<endl;
                            M1.clear();
                            M2.clear();
                            // M3.clear();
                            // M1.shrink_to_fit(); // Capacity of v is now 0
                            // M2.shrink_to_fit(); // Capacity of v is now 0
                            // M3.shrink_to_fit(); // Capacity of v is now 0
                            std::vector <std::pair <std::string,std::vector<short>>> (M1).swap(M1);
                            std::vector <std::pair <std::string,std::vector<short>>> (M2).swap(M2);
                            // std::vector <std::pair <std::string,std::vector<short>>> (M3).swap(M3);
                            
                            // cout << "after"<<endl;
                            // cout<<"M1 capacity = "<<M1.size()<<" "<<"M1 capacity = "<<M1.capacity()<<endl;
                            // cout<<"M2 capacity = "<<M2.size()<<" "<<"M2 capacity = "<<M2.capacity()<<endl;
                            // cout<<"M3 capacity = "<<M3.size()<<" "<<"M3 capacity = "<<M3.capacity()<<endl;
                            // delete M1;
                            // delete M2;
                            // delete M3;
                            // std::vector <std::pair <std::string,mpz_class>> ().swap(M1);
                            // std::vector <std::pair <std::string,mpz_class>> ().swap(M2);
                            // std::vector <std::pair <std::string,mpz_class>> ().swap(M3);
                            
                            // cout<<"inters capacity = "<<inters.size()<<" "<<"inters capacity = "<<inters.capacity()<<endl;
                            // std::vector <std::pair <std::string,mpz_class>> ().swap(inters);
                            // cout<<"inters capacity = "<<inters.size()<<" "<<"inters capacity = "<<inters.capacity()<<endl;
                            
                            inters.clear();
                            std::vector <std::pair <std::string,std::vector<short>>> (inters).swap(inters);
                            return true;
                        }
                        tmp_msg = msg;//set mpz
                    }
                    // //check it it is the same message with the decrypted;
                }
            }
        }
        inters.clear();
        std::vector <std::pair <std::string,std::vector<short>>> (inters).swap(inters);
        // cout << "before3"<<endl;
        // cout<<"M1 capacity = "<<M1.size()<<" "<<"M1 capacity = "<<M1.capacity()<<endl;
        // cout<<"M2 capacity = "<<M2.size()<<" "<<"M2 capacity = "<<M2.capacity()<<endl;
        // cout<<"M3 capacity = "<<M3.size()<<" "<<"M3 capacity = "<<M3.capacity()<<endl;
        M1.clear();
        M2.clear();
        // M3.clear();
        // M1.shrink_to_fit(); // Capacity of v is now 0
        // M2.shrink_to_fit(); // Capacity of v is now 0
        // M3.shrink_to_fit(); // Capacity of v is now 0
        std::vector <std::pair <std::string,std::vector<short>>> (M1).swap(M1);
        std::vector <std::pair <std::string,std::vector<short>>> (M2).swap(M2);
        // std::vector <std::pair <std::string,std::vector<short>>> (M3).swap(M3);

        // cout << "after"<<endl;
        // cout<<"M1 capacity = "<<M1.size()<<" "<<"M1 capacity = "<<M1.capacity()<<endl;
        // cout<<"M2 capacity = "<<M2.size()<<" "<<"M2 capacity = "<<M2.capacity()<<endl;
        // cout<<"M3 capacity = "<<M3.size()<<" "<<"M3 capacity = "<<M3.capacity()<<endl;
        
        // std::vector <std::pair <std::string,mpz_class>> ().swap(M1);
        // std::vector <std::pair <std::string,mpz_class>> ().swap(M2);
        // std::vector <std::pair <std::string,mpz_class>> ().swap(M3);
    }
    
    return false;
}

std::string Ns::prod_of_f2_when_c_bigger_1(std::vector<short> cmb,mpz_class *&L,mpz_class& p,mpz_class& c){
    //num_to_be_md5 is the number with the result of the prod
    mpz_class num_to_be_md5;
    mpz_class prod,             // prod calculated
            to_be_multiplied,   // var that is being multiplied with prod on each loop of the if
            c_x_prod;           // var that takes prod*c vallue
            // nwh;                // number with certain hamming weight be added to the pair
    // calc the number
    //set starting value of the prod
    prod=1;
    c_x_prod=1;
    //prod calculation
    to_be_multiplied=1;
    for(int k=0;k<cmb.size();k++){
        mpz_invert(to_be_multiplied.get_mpz_t(),L[cmb[k]].get_mpz_t(),p.get_mpz_t());//res=num^-1MOD mod
        // custom_mulinv(to_be_multiplied,to_be_multiplied,p);
        //multiply the last prod with the new calculation
        prod *= to_be_multiplied;
    }//prod is done
    c_x_prod = prod*c;//to_be_mod=c*prod 
    mpz_mod(num_to_be_md5.get_mpz_t(),c_x_prod.get_mpz_t(),p.get_mpz_t());//to_be_mod MOD p
    // create the digest and keep the 12 first from hex repr
    // md5f12=to_md5_f6_str(num_to_be_md5);    //part 2 ready
    // std::pair<std::string,std::vector<short>> pair_to_be_added=std::make_pair(md5f12,cmb); //create pair
    return to_md5_f6_str(num_to_be_md5);
}

std::string Ns::prod_of_f2_when_c_not_bigger_1(std::vector<short> cmb,mpz_class *&L,mpz_class& p,mpz_class& c){
    //num_to_be_md5 is the number with the result of the prod
    mpz_class num_to_be_md5;
    mpz_class prod,             // prod calculated
            to_be_multiplied,   // var that is being multiplied with prod on each loop of the if
            c_x_prod;           // var that takes prod*c vallue
            // nwh;                // number with certain hamming weight be added to the pair
    // calc the number
    //set starting value of the prod
    prod=1;
    c_x_prod=1;
    to_be_multiplied=1;
    for(int k=0;k<cmb.size();k++){
        mpz_powm_ui(to_be_multiplied.get_mpz_t(),L[cmb[k]].get_mpz_t(),1,p.get_mpz_t());//res=base^exp MOD mod
        // modd_mpz_class_ui(to_be_multiplied,L[cmb[k]],1,p);
        //multiply the last prod with the new calculation
        prod *= to_be_multiplied;
    }//prod is done
    c_x_prod = prod*c;//to_be_mod=c*prod 
    // cout << c_x_prod <<endl;
    mpz_mod(num_to_be_md5.get_mpz_t(),c_x_prod.get_mpz_t(),p.get_mpz_t());//to_be_mod MOD p
    // create the digest and keep the 12 first from hex repr
    // md5f12=to_md5_f6_str(num_to_be_md5);    //part 2 ready
    // std::pair<std::string,std::vector<short>> pair_to_be_added=std::make_pair(md5f12,cmb); //create pair
    return to_md5_f6_str(num_to_be_md5);
}

/**
 * This function set up the M sets with pairs 
 * of which each one has two vallues
 * a mpz_class number with certain hamming weight and
 * a string with the 12 first from hex repr from the md5 digest of
 * the prod calculation according to the mpz_number on base of 2
 */
void Ns::func2(std::vector <std::pair <std::string,std::vector<short>>> &RE,mpz_class *&L,int len,int ham,mpz_class p,mpz_class c){
    // cout<<"n="<<len<<" h= "<<ham<<endl;
    Combinations* c_obj=new Combinations(len,ham);//obj which calc next comp
    // mpf_t to_be_multiplied_f;
    //calc nwh
    mpz_class number_of_cmb;//declare
    unsigned long long number_of_cmb_ull;//var which will take vallue from number of cmb
    c_obj->get_size(number_of_cmb);//set size of max compinations
    number_of_cmb_ull=mpz_2_ull(number_of_cmb);//set ull from mpz

    // std::cout << "MPZclass max compinations : "<<number_of_cmb<<std::endl;
    // std::cout << "ULLnumber of diferent compinations : "<< number_of_cmb_ull<<endl;//print that number
    
    //check if this way is better
    // RE.reserve(number_of_cmb_ull);
    // if(number_of_cmb_ull>1)
    if(c>1){
        for(unsigned long long i=0;i<number_of_cmb_ull;i++){
            //init/declare vars
            // std::string md5f12;         // md5 string to be added to the pair
            std::vector<short> cmb;
            cmb = c_obj->next_combination();//set the cmb which is the next combination
            // calc digest
            RE.push_back(std::make_pair(prod_of_f2_when_c_bigger_1(cmb,L,p,c),cmb)); //add pair
        }
    }else{
        for(unsigned long long i=0;i<number_of_cmb_ull;i++){
            //init/declare vars
            // std::string md5f12;         // md5 string to be added to the pair
            std::vector<short> cmb;
            cmb = c_obj->next_combination();//set the cmb which is the next combination
            // calc digest
            RE.push_back(std::make_pair(prod_of_f2_when_c_not_bigger_1(cmb,L,p,c),cmb)); //add pair
        }
    }
    // std::cout << "Finished genaration of M set : "<< number_of_cmb_ull<<endl;//print that number
    //clear combinations obj
    delete c_obj;
    // for(int i=0;i<RE.size();i++){
    //     cout <<RE[i].first<<" , "<< " , [";
    //     for(size_t jj = 0; jj < ham; jj++)
    //     {
    //         cout <<RE[i].second[jj]<<"," ;
    //     }cout<<"]"<<endl;
        
    // }
}


// void reduce(std::vector <std::pair <std::string,std::vector<short>>> *vp,
//             int begin,
//             int end
//             ){
//     if(end - begin == 1) return;
//     int pivot = (begin+end)/2;
//     #pragma omp task
//     reduce(v, begin, pivot);
//     #pragma omp task
//     reduce(v, pivot, end);
//     #pragma omp taskwait
//     v1[begin].insert(v1[begin].end(), v1[pivot].begin(), v1[pivot].end());
//     v2[begin].insert(v2[begin].end(), v2[pivot].begin(), v2[pivot].end());
// }

/**
 *  Set res vallue to the  
 *  res = base ^ exp MOD p
 *  if exp is negative handle it like Modular Inverse
 *  else handle it like mod
 */
void Ns::modd_mpz_class_ui(mpz_class &res,mpz_class base,long int exp,mpz_class mod){
    if(exp>=0){
        mpz_powm_ui(res.get_mpz_t(),base.get_mpz_t(),exp,mod.get_mpz_t());//res=base^exp MOD mod
    }else{
        //init
        mpz_class gcd;//great 
        //calc
        mpz_gcd(gcd.get_mpz_t(),base.get_mpz_t(),mod.get_mpz_t());
        // check if they are co-primes
        if(gcd>1){//gcd(base,mod)>1
            cerr<< "base and mod are not primes to each other"<<endl;
        }
        if(exp==-1){
            mpz_invert(res.get_mpz_t(),base.get_mpz_t(),mod.get_mpz_t());//res=base^-1MOD mod
        }else{
            //init
            mpz_class newbase;
            //calc
            mpz_pow_ui(newbase.get_mpz_t(),base.get_mpz_t(),-exp);//newbase= base^|exp|
            mpz_invert(res.get_mpz_t(),newbase.get_mpz_t(),mod.get_mpz_t());//res=newbase^-1MOD mod
        }
    }
}

/**
 *  Set res vallue to the Modular Inverse of number
 *  res = num ^ -1 MOD p
 */
void Ns::custom_mulinv(mpz_class &res,mpz_class num,mpz_class p){
    if (num==0){
        res=1;//res=num^0 MOD mod= 0 always
    }else{
        mpz_invert(res.get_mpz_t(),num.get_mpz_t(),p.get_mpz_t());//res=num^-1MOD mod
    }
}

/**
 * Set mpz_class msg as the message calculated from the prod
 *
 */
void Ns::construct_msg_mpz(mpz_class &msg,int*&I1,std::vector<short> r1,int &s1,int*&I2,std::vector<short> r2,int &s2){
    std::vector<int> r1int;
    std::vector<int> r2int;
    mpz_class sum1=0,sum2=0;
    //I dont have the length of I1 and I2 so I use the r1,r2 length
    //I can set this operation to be done by 2 threads
    short count=0;
    for (int i = 0; i < s1; i++){//prduct 1
        mpz_class tmp=0,prod=1;
        //init vars
        mpz_ui_pow_ui(tmp.get_mpz_t(),2,I1[i]);
        //calculate the product of 2 vectors i th cell
        if(r1[count]==i){
            prod = tmp*1;
            count++;
        }else{
            prod = 0;
        }
        //add the last product of the two vectors
        sum1 = sum1+prod;
    }
    count=0;
    for (int i = 0; i < s2; i++){//prduct 2
        mpz_class tmp=0,prod=1;
        //init vars
        mpz_ui_pow_ui(tmp.get_mpz_t(),2,I2[i]);
        //calculate the product of 2 vectors i th cell
        if(r2[count]==i){
            prod = tmp*1;
            count++;
        }else{
            prod = 0;
        }
        //add the last product of the two vectors
        sum2 = sum2+prod;
    }
    msg= sum1+sum2;
}








// comments

// stuf about M1 to print after set-up

// // print M1
// cout<< " FOR "<<endl;
// cout<< " M1 size "<<M1.size()<<endl;

// cout<< "M1[0]="<<M1[0].first<<" , "<<M1[0].second<< endl;


// cout<< "M1["<<M1.size()-1<<"]="<<M1[M1.size()-1].first<<" , "<<M1[M1.size()-1].second<< endl;

// cout<<"M1="<<M1.size()<<endl;
// for(const auto& a_pair :M1){
//     cout <<a_pair.first<<" , "<<a_pair.second<< endl;
// }

// stuf about M3,M2 to print after set-up

// // print M3
// cout<< "printing new M3 from h1==1"<<endl;

// cout<< " case 1 "<<endl;
// cout<<"M2 size "<<M2.size()<<endl;

// cout<< "M2[0]="<<M2[0].first<<" , "<< M2[0].second << endl;

// cout<< "M2["<<M2.size()-1<<"]="<<M2[M2.size()-1].first<<" , "<< M2[M2.size()-1].second << endl;

// for(const auto& a_pair :M2){
//     cout <<a_pair.first<<" , "<< a_pair.second << endl;
// }

// cout<<"M3 size "<<M3.size()<<endl;

// cout<< "M3[0]="<<M3[0].first<<" , " << M3[0].second << endl;

// cout<< "M3["<<M3.size()-1<<"]="<<M3[M3.size()-1].first<<" , "<< M3[M3.size()-1].second << endl;

// for(const auto& a_pair :M3){
//     cout <<a_pair.first<<" , " << a_pair.second << endl;
// }


// stuf about M2 to print after set-up

// cout<< " case 2 "<<endl;
// cout<<"M2 size "<<M2.size()<<endl;
// cout<< "M2[0]="<<M2[0].first<<" , " << M2[0].second << endl;

// cout<< "M2["<<M2.size()-1<<"]="<<M2[M2.size()-1].first<<" , " << M2[M2.size()-1].second << endl;

// for(const auto& a_pair :M2){
//     cout <<a_pair.first<<" , " << a_pair.second << endl;
// }

// stuf about M2,M3 to print after set-up

// cout<< " case 3 "<<endl;

// cout<< "printing new M3 from h1>1&&h2==h1"<<endl;

// cout<<"M2 size "<<M2.size()<<endl;

// for(const auto& a_pair :M2){
//     cout <<a_pair.first<<" , " << a_pair.second << endl;
// }

// cout<< "M2[0]="<<M2[0].first<<" , " << M2[0].second << endl;

// cout<< "M2["<<M2.size()-1<<"]="<<M2[M2.size()-1].first<<" , "<< M2[M2.size()-1].second << endl;

// cout<<"M3 size "<<M3.size()<<endl;

// cout<< "M3[0]="<<M3[0].first<<" , " << M3[0].second << endl;

// cout<< "M3["<<M3.size()-1<<"]="<<M3[M3.size()-1].first<<" , " << M3[M3.size()-1].second << endl;

// for(const auto& a_pair :M3){
//     cout <<a_pair.first<<" , "<< a_pair.second << endl;
// }
