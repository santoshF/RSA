/*
 * =====================================================================================
 *
 *       Filename:  RSA.cpp
 *
 *    Description:  To implement RSA algorithm. 
 *
 *        Version:  1.0
 *        Created:  Tuesday 02 April 2013 02:02:55  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Santosh Fernandes (), s.is.santosh@gmail.com
 *   Organization:  ISSC
 *
 * =====================================================================================
 */

#include <primesieve/soe/PrimeSieve.h>
#include <primesieve/soe/primesieve_error.h>
#include <iostream>
#include <exception>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <cstdio>
using namespace std;

class stop_primesieve : public exception {};

vector<long int> primes;
vector<long int> primes1;

void callback ( unsigned  int prime ){
 
//Check condition if more than 1000 quit generating 
 if(primes.size() == 1000) throw stop_primesieve();
 
 //Store Random 1000 primes
 primes.push_back(prime);
 
}

void callback1 (unsigned  int prime ){

 primes1.push_back(prime);
}

unsigned long int euclid(unsigned long int a,unsigned long int b){
unsigned long int  gcd ,q,r,m,n,u=1,v=0,y = 1, x = 0;
 gcd= b;
while(a != 0 ){
  q = gcd/a;
  r = gcd % a   ;
  m = x - u * q;
  n = y - v * q;
  gcd = a;
  a = r;
  x = u;
  y = v;	
  u = m;
  v = n;		
}
return gcd;
}


unsigned long int extended_euclid(unsigned long int a,unsigned long int b,unsigned long int  x ,unsigned long int y){
 x = 0,y=1;
long int u = 1 , v = 0 , m ,n,q,r,gcd;
gcd = b;
while (a != 0){
 q = gcd /a ;
 r = gcd % a;
 m = x - u * q;
 n = y - v * q;
 gcd = a;
 a = r;
 x = u;
 y = v;
 u = m;
 v = n;

}

return (x%b);

}

long int  square_and_multiply(long int modulus,long int base,long int power)
{
    long int b=1,temp;
    temp=base;
    if(power==0&&base==0)
    {
      printf("\nIndeterminant value\n");
      exit(1);
    }
    if(power==0)
    {
      return b;
      exit(1);
    }
    if(power&1)
    b=base;
    power=power>>1;
      while(power)
      {
      temp=(temp*temp)%modulus;
      if(power&1)
      b=(temp*b)%modulus;
      power=power>>1;
      }
      return b;

} 

unsigned long exp_calc(unsigned long c,unsigned long n,unsigned d){
unsigned long i , g,f;
if(d % 2 == 0) g = 1;
else g = c;

for(i = 1 ; i <= d/2 ;i++ ){
 f = c * c % n;
 g = f * g % n;
}
 return (g);
}




int main(){
	
	//Initialize Seed
	srand(time (NULL) );	
	//Create Random Start from range 0 to 99
	long int start = rand () % 99 + 1 ;
	//Create Random Stop from range 999 to 99999 (Nighty - Nine Thousand )	
	long int stop =  rand () % 99999  + 999 ;
	
	cout<<"Random start "<<start <<endl;
	cout<<"Random end " <<stop <<endl;

	PrimeSieve ps;
	try
	{
		ps.generatePrimes(start ,stop ,callback);
	 //	ps.prlong intPrimes(start ,stop );

	}catch (stop_primesieve & e  ){
	//cerr << " Error " << e.what() <<endl; 
	}
	//Random Number
	long int  num1  =  rand() % 99 + 1 ; 	
	long int  num2  =  rand() % 500 +  100;

	 //P and Q are 2 large random number
	 unsigned  long int  p = primes[num1];
	 unsigned long int  q = primes[num2];

	 //Calculate n
	unsigned long int n = p * q;
	
	//Calculate phi
	unsigned long int phi = (p -1 ) * (q -1);

	//Calculate e s.t. 
	
	cout << " num1 =	" << num1 <<endl;	
	cout << " num2 =	" << num2 <<endl;	
	cout << " p =	" << p <<endl;	
	cout << " q =	" << q <<endl;	
	cout << " n =	" << n <<endl;	
	cout << " phi =  "<< phi <<endl;	

	try{
	 ps.generatePrimes(1, phi, callback1); 
	}catch(stop_primesieve &e ){ }
	unsigned long int ev=0,e=0;
	for(unsigned long int i = 0 ; i <  primes1.size() ; i++){
    	ev = euclid(primes1[i],phi);	
	 if(ev == 1){
	         e = primes1[i];
		 break;
		}
	}
	cout << "Public key "<<e <<" and " <<n<<endl;
	unsigned long int ch,ans,m = 32,d,x = 0 ,y = 0;
	d = extended_euclid(e,phi,x,y);
       cout << "Private Key " << d << " and " <<n <<endl;
	cout << " check d*e = 1 (mod phi) "<<endl;
	ch = d*e;
	ans = euclid(ch,phi);
 	cout<<"Check 1 "<<ans<<endl;
	unsigned long c = exp_calc(m ,n,e);
        cout << "  encrypt(e,n) " <<c <<endl;
	unsigned long mdec = exp_calc(c,n,d);
	cout<< "decrypted " <<mdec <<endl;

return 0;
}




