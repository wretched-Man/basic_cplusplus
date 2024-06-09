//
//Work out the first ten digits of the sum of the following one-hundred
//50-digit numbers.
//The numbers have been stored in the file.
#include <iostream>
#include <iomanip>
#include <fstream>
#include <gmpxx.h>


int main(){
    mpz_class a, temp;
    std::ifstream ifile("Euler13help.txt");
    if(!ifile) {std::cout << "Could not open file."; exit(-1);}

    std::string my_file;
    while(ifile >> my_file){
        a+=(temp = my_file);
    }

    std::cout  << std::setprecision(10) << a.get_str().substr(0, 10) << std::endl;
    return 0;
}
