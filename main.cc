/*************************************************************************
    > File Name: main.cc
    > Author: 朱会茗
    > Mail: 1294206499@qq.com
    > Created Time: 2018年12月19日 星期三 16时39分49秒
 ************************************************************************/

#include <iostream>

#include "include/vector/vector.h"
#include "include/BPT.h"
using namespace std;

int main() {
    BPT<int> test;
    for(int i = 0; i < 6; i++){
        test.insert(i);
    }
    return 1;
}
