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

using namespace std;

class stop_primesieve : public exception {};

vector<int> primes;

void callback ( unsigned int prime ){
 
//Check condition if more than 1000 quit generating 
 if(primes.size() == 1000) throw stop_primesieve();
 
 //Store Random 1000 primes
 primes.push_back(prime);
 
}



int main(){
	
	//Initialize Seed
	srand(time (NULL) );	
	//Create Random Start from range 0 to 99
	int start = rand () % 99 + 1 ;
	//Create Random Stop from range 999 to 99999 (Nighty - Nine Thousand )	
	int stop =  rand () % 99999  + 999 ;
	
	cout<<"Random start "<<start <<endl;
	cout<<"Random end " <<stop <<endl;

	PrimeSieve ps;
	try
	{
		ps.generatePrimes(start ,stop ,callback);
	 //	ps.printPrimes(start ,stop );

	}catch (stop_primesieve & e  ){
	//cerr << " Error " << e.what() <<endl; 
	}
	//Random Number
	int  num1  =  rand() % 99 + 1 ; 	
	int  num2  =  rand() % 500 +  100;

	 //P and Q are 2 large random number
	long long unsigned  int  p = primes[num1];
	long long unsigned int  q = primes[num2];

	 //Calculate n
	long long unsigned int n = p * q;
	
	//Calculate phi
	long long unsigned int phi = (p -1 ) * (q -1);

	//Calculate e s.t. 
	
	cout << " num1 =	" << num1 <<endl;	
	cout << " num2 =	" << num2 <<endl;	
	cout << " p =	" << p <<endl;	
	cout << " q =	" << q <<endl;	
	cout << " n =	" << n <<endl;	
	cout << " phi =  "<< phi <<endl;	

	euclid(a,b);	

return 0;
}




