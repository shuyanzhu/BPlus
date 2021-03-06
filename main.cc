/*************************************************************************
> File Name: main.cc
> Author: 朱会茗
> Mail: 1294206499@qq.com
> Created Time: 2018年12月19日 星期三 16时39分49秒
************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <stdlib.h>

//#include "include/vector/vector.h"
#include "include/BPT.h"
using namespace std;
int main()
{
    BPT<int> test(5);
    volatile clock_t t1, t2;
    int i = 0;
    t1 = clock();

    // test.deserialize("data");
    // test.print(0);
    // 顺序/倒序插入速度测试
    for (int i = 0; i < 10000000; i++) {
        // test.insert(i);
        test.insert(i);
        // test.print(1);
    }
    // test.print(0);

    // for (int i = 0; i < 10000000; i++) {
    // test.insert(10000000-i);
    //}

    //// 乱序插入、删除正确性测试，速度测试
    // srand(1);
    // for (int i = 0; i < 10000000; i++) {
    //     test.insert(rand()*rand());
    // }
    //  test.print(0);
    //  test.search(17400);
    //  for (int i = 0; i < 1000000; i++) {
    //     test.remove(rand() % 10000000);
    // }
    //  test.print(0);
    // test.print(0);
    t2 = clock();
    printf("time: %ld\n%d\n", (t2 - t1) / CLOCKS_PER_SEC, test.h);
    // system("pause");
    return 0;
}
