//https://www.codechef.com/problems/FRGAME
/*
  Nitin and Sobhagya were playing a game with coins. If Sobhagya has more coins then he is
  winning, otherwise Nitin is winning. Note that this means if both Nitin and Sobhagya have
  the same number of coins, then Nitin is winning. Initially Nitin has A coins while Sobhagya
  has B coins. Then Ritik came and gave his C coins to the player who is not winning currently,
  after which Satyarth came and repeated the same process (gave his D coins to the player who
  is not winning currently).

  Find the final winner of the game.
*/

#include <iostream>
#include <algorithm>

using std::cin;

int main(){
    //coins that each have. Nitin[0], Sobhagya[1] ...
    int coins[4]; 

    //No of test cases
    int T;
    cin >> T;

    //Constraint checking
    if(!T || T > 1000) {return -1;}

    std::string result;

    for(; T>0; --T){
        cin >> coins[0] >> coins[1] >> coins[2] >> coins[3];
        
        //Find winner
        for(int i = 0; i < 2; i++){
            //Two passes because of the 2 additional friends
            if(coins[0] >= coins[1]){ //NITIN is winning
                coins[1] += coins[2 + i];
            }
            else{
                coins[0] += coins[2 + i];
            }
        }

        
        if(coins[0]>=coins[1]){ //NITIN is winning
            result.append("N\n");}
        else
            result.append("S\n");
    }
    std::cout << result;
    return 0;
}
