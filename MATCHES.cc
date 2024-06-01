// https://discuss.codechef.com/t/matches-editorial/38839
/**
 * @file MATCHES.cc
 * @brief Given 2 values A and B, how may matches are needed to write S = A + B?
 */

#include <iostream>
int main(){
    //Define no of sticks needed by each digit {0 - 9}
    int totSticks[] = {6,2,5,5,4,5,6,3,7,6};
    int times{}, a{}, b{}; //t -> no of times to run the program
    std::cin >> times;
    for(; times>0; --times){
        std::cin >> a>>b;
        int result = a+b, noOfSticks{};
        while(result > 9){
            noOfSticks+=totSticks[result%10];
            result/=10;
        }
        noOfSticks+=totSticks[result];
        std::cout << noOfSticks << "\n";
    }
}