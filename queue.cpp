//编译:
//g++ -ggdb3 -o x ./queue.cpp

//<队列>实现简介:
//queue 主要依赖deque 来实现, 实际就是对deque 的"剪裁输出".
//queue 是一种<适配器>容器, 一种先进先出(FIFO)的数据结构.

//queue 构造函数都需要: <_Sequence 实体>传入, 但是:
//template<typename _Tp, typename _Sequence = deque<_Tp> >
//这句表明, _Tp 是类型, _Tp 类型传入后, 又变成了deque 的实化类型.
//最终实际是传入一个<deque 实体>到queue 构造函数里面进行初始化.


//实现文件: /usr/include/c++/6.3.0/bits/stl_queue.h

//stl_queue.h 容器列表:
//class queue,          [基于<deque>实现]queue 的声明与实现.
//class priority_queue, [基于<deque>实现]priority_queue 的声明与实现.
//ps: 迭代器还是用deque 的迭代器


//ps: 以上两个容器的实现, 都是先声明结构体or 类, 后续跟着具体实现.
//    例如:声明迭代器, 实现迭代器. 声明类, 实现类.
//    根据类名(), 你可以很容易找到构造函数和释构函数



//queue api list
/*

back()返回最后一个元素
empty()如果队列空则返回真
front()返回第一个元素
pop()删除第一个元素
push()在末尾加入一个元素
size()返回队列中元素的个数

*/


#include <stdio.h>
#include <queue>

#include <deque>
#include <list>
#include <string>

using namespace std;

//测试函数
int main(void){
  
  //创建队列
  queue<int> test1;         // empty queue
  queue<string> test9;      //字符队列
  queue<deque<int>> test8;  //内嵌队列
  //queue<int> test7(3,100);  //初始化队列--失败!

  //初始化式, 创建队列
  //int arr_tmp[] = {1,2,3};
  //queue<int> test_arr(arr_tmp,arr_tmp+2);

  deque<int> x1(3,100);  // deque with 3 elements
  list<int> x2(2,200);   // list with 2 elements

  queue<int> test2(x1);  // queue initialized to copy of deque
  queue<int,list<int>> test3(x2);//实际不是在list 的基础上创建queue
                                 //实际上是将list 里面的所有元素转移到queue 里面
                                 //queue 实际上还是deque 结构.

  //bool empty();  判断队列是否为空
  if(test1.empty())
    printf("'test1 queue' now is empty!!\n");

  //测试对空queue 进行元素查看操作(空 and 完全没有初始化过任何元素)
  //结果: 内存溢出!! 所以查看元素操作也必须检索queue 是否为空！！！
  //printf("'test1 queue' back() now is %d\n", test1.back());
  //printf("'test1 queue' front() now is %d\n", test1.front());
  
  //void push(const T& x);  压入元素--从back 压入
  test1.push(1);
  test1.push(2);
  test1.push(3);

  
  //size_type size();  查看队列size()
  //其实你可以做个断言, size() >= 0, 不过没啥实用性.
  printf("'test1 queue' size() now is %d\n", test1.size());

  
  //value_type& back();  查看队列头元素
  if(!test1.empty())
    printf("'test1 queue' back() now is %d\n", test1.back());

  //value_type& front();  查看队列尾元素
  if(!test1.empty())
    printf("'test1 queue' front() now is %d\n", test1.front());
  

  //void pop();  弹出元素--从front 弹出
  if(!test1.empty())
    test1.pop();
  
  if(!test1.empty())
    printf("'test1 queue' back() now is %d\n", test1.back());

  if(!test1.empty())
    printf("'test1 queue' front() now is %d\n", test1.front());

  if(!test1.empty())
    test1.pop();

  if(!test1.empty())
    printf("'test1 queue' back() now is %d\n", test1.back());

  if(!test1.empty())
    printf("'test1 queue' front() now is %d\n", test1.front());



  //对空队列进行--back(), front() 取值测试
  test1.pop();
  test1.pop();//但是你这样违规pop 空, queue 就废了, 变成一个坏容器
  test1.pop();
  printf("'test1 queue' size() now is %d\n", test1.size());
  printf("'test1 queue' back() now is %d\n", test1.back());
  printf("'test1 queue' front() now is %d\n", test1.front());
  if(test1.empty())//仅当size() == 0, empty() 才会返回true
    printf("'test1 queue' now is empty!!\n");
  test1.pop();//pop() 空队列也不会失败, 跟stack 相反??


  //back() 永远是3, 证明what? 就算pop 空栈, back() 都仍然是3 ??
  //证明只有在push() 操作的时候, 才会更新back()
  //只有在pop() 操作的时候, 才会更新front()
  //back(), front() 只是记录游标, 数据不一定准确.

  //所以绝对不能随意在back() 取数据, 这个数据不一定准确, 可能失实!!
  //你对队列front() 取一次数据, 就应该pop() 消除一个
  printf("'test1 queue' back() now is %d\n", test1.back());
  return 0;
}


