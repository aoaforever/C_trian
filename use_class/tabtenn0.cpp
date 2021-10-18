#include "tabtenn0.h"
#include <iostream>

TableTennisPlayer::TableTennisPlayer(const string &fn,
const string &ln , bool ht): firstname(fn), lastname(ln),hasTable(ht){}

void TableTennisPlayer::Name() const {
    std::cout<<lastname<< ", "<<firstname;
}

//创建派生类对象时，程序首先创建基类对象，这意味着基类对象应当在程序进入派生类
//构造函数之前被创建。C++使用成员初始化列表语法来完成这种工作。
RatedPlayer::RatedPlayer(unsigned int r , const string & fn, const string &ln, bool ht ):TableTennisPlayer(fn,ln,ht){
    rating = r;
}

RatedPlayer::RatedPlayer(unsigned int r , const TableTennisPlayer& tp):TableTennisPlayer(tp), rating(r){}