#include<iostream>
#include"tabtenn0.h"
//g++ usett0.cpp tabtenn0.cpp -o usett0 && "d:\code\C++_trian\use_class\"usett0
using std::string;


int main(void){
    using std::cout;
    TableTennisPlayer player1("Chuck", "Blizzard", true);
    TableTennisPlayer player2("Tara", "Boomdea", false);

    player1.Name();
    if (player1.HasTable())
        cout<< ": has a table.\n";
    else 
        cout<<": hasn't a table.\n";
    
    player2.Name();
    if (player2.HasTable())
        cout<< ": has a table.\n";
    else 
        cout<<": hasn't a table.\n";


    
    return 0;
}