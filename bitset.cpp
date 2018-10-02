//编译:
//g++ -ggdb3 -o x ./bitset.cpp

//简介
//C++ bitset 一种<位操作-集合>的数据结构
//bitsets使用许多二元操作符, 比如逻辑和, 或等...

//bitset api list(略)


#include <stdio.h>
#include <string>
#include <bitset>
#include <iostream>
using namespace std;

//测试函数
//(函数不接受 '-' 字符串 , best 也是关键字)
int main(void){
  //1. 初始化<位集合>
  //将int = 32 bit 推如位容器, 即这个bitset 存在32 个元素.
  bitset<32> x1;
  bitset<32> x2(120ul);//unsigned long = 120

  bitset<32> x3(string("01011"));// initialize from string


  //bool any(); 判断<位集合>是否有被置1 的位
  if(x1.any())
    printf("x1<位集合>如果有任何一个位被置1, 就返回true\n");
  if(x3.any())
    printf("x3<位集合>如果有任何一个位被置1, 就返回true\n");


  //bool none(); 判断<位集合>是否, 没有任何被置1 的位
  if(x1.none())
    printf("x1<位集合>没有任何一个位被置1, 就返回true\n");
  if(x3.none())
    printf("x3<位集合>没有任何一个位被置1, 就返回true\n");


  //size_t count(); 统计<位集合>被置1 的位数的count
  //size_t size();  求出<位集合>所有的位数, 必然等于初始化时候的32
  printf("x3<位集合>被置1 的位数count = %d, 未被被置1 的位数count = %d\n",
    x3.count(), x3.size()-x3.count());


  //bitset<N>& flip();
  //4.flip() 反转bits中的位, 返回一个新的bitset<N>
  bitset<32> x4 = x3.flip();
  x1 = x1.flip(31);//32 位的<位集合>, 求反最高是31 位 = 1. 
  //x1 = x1.flip(string("10101010")); //错误的定义, 字符串初始化, 
                                      //只能在<位集合>类构造的时候用
  //to_string() 转换<位集合>为字符串
  cout << x4.to_string() << endl;//这里用cout 是因为c 语言printf 不能输出二进制
  cout << x1.to_string() << endl;//printf 只能输出8,10,16 进制的数字
                                 //但是可以转换为字符串
  //to_ulong() 转换<位集合>为unsigned long
  printf("x4 = %d\n",x4.to_ulong());
  printf("x1 = %d\n",x1.to_ulong());


  //bitset<N>& reset();  重置某个位为0
  bitset<32> x44 = x4.reset();//默认全部清0
  bitset<32> x11 = x1.reset(31);//只清0 第31 位
  cout <<"x44" << x44.to_string() << endl;
  cout <<"x11" << x11.to_string() << endl;


  //bitset<N>& set();  重置某个位为1
  bitset<32> x111 = x1.set(2);//重置第二位为1
  cout <<"x111" << x111.to_string() << endl;
  x111 = x1.set(0);//将0 位也置1


  //bool test(size_t pos);  如果目标位为1, 则返回true
  if(x111.test(2))
    printf("x111.test(2) = 1, 即返回true\n");
  if(x111.test(1))
    printf("x111.test(1) = 1, 即返回true\n");
    if(x111.test(0))
    printf("x111.test(0) = 1, 即返回true\n");


  printf("bitset test finish\n");
  return 0;
}




