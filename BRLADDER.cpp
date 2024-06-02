//https://www.codechef.com/problems/BRLADDER
//The problem statement is long and its stating is best left in the link above
#include <iostream>
#include <string>
#include <vector>

using std::cin; using std::cout; using std::string; using std::vector;

#define ROAD_EXIST 0
#define ROAD_NOT_EXIST 1

int cmp(const int& a, const int& b){
    //Every road has 2 connections
    if(a+2 == b){
        return ROAD_EXIST;
    }
    
    if(a%2 == 0 && (a-1 == b) ){
        //Even numbered roads
        return ROAD_EXIST;
    }

    if(a%2 == 1 && (a+1 == b) ){
        //Odd numbered roads
        return ROAD_EXIST;
    }

    return ROAD_NOT_EXIST;
}

int main(){
    string sst = "";
    int Q{}, a{}, b{};
    cin >> Q; //No. of queries
    if(Q > 1000 || !Q)  {return -1;}
    vector<string> results;
    vector<string> options = {"YES","NO"};

    for(; Q > 0; Q--){
        cin >> a >> b;

        //constraint checking
        if(a==b){ return -1;  }
        if( !a || !b) { return -1;  }
        if( (a > 1000000000) || (b > 1000000000) ){ return -1;  }

        results.push_back(options[cmp(a, b)]);
    }

    for(auto res : results){
        cout << res << std::endl;
    }
}
