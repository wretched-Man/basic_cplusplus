//https://projecteuler.net/problem=12
//The problem statement is best stated in the link above
//when building link against -lgmp and -lgmpxx
#include <iostream>
#include <vector>
#include <gmp.h>
#include <gmpxx.h>
#include <unordered_map>

std::vector<int> count_all_appearances(mpz_class n){
    //takes a triangular number returns the number of times each prime factor appears
    std::vector<int> cnt, ret_int;
    if(n == 1) {cnt.push_back(1); return cnt;};
    while (n % 2 == 0){
        cnt.push_back(2); n = n/2;
    }

    for (int i = 3; i <= sqrt(n); i = i + 2){
        while (n % i == 0){ cnt.push_back(i); n = n/i; }
    }

    if (n > 2) cnt.push_back(n.get_ui());
    std::unordered_map<int, size_t> counts;
    for (auto v : cnt) {++counts[v]; }
    for (auto const &p : counts){
        ret_int.push_back(p.second);
    }

    return ret_int;
}

int main(){
    for (int i = 1; i < 30000; i++){
        mpz_class xy = i*(i+1)/2; //triangular
        std::vector<int> appearances = count_all_appearances(xy);
        int div{1};
        for(auto  & x:appearances){ ++x; div*=x; }
        if(div >=501){
            std::cout << xy <<" -> " << div << "\n";
        }
    }
    return 0;
}
