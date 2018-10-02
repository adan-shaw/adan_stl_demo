//编译:
//g++ -ggdb3 -o x ./priority_queue.cpp

//<优先队列>实现简介: 
//priority_queue 是一种<适配器>容器, 一种<带优先级操作>的先进先出(FIFO)的数据结构.
//会自动根据int 的数值大小排序!! 数值大的在top() !! 而且只能读出top() ...


//实现文件: /usr/include/c++/6.3.0/bits/priority_queue.h

//priority_queue.h 容器列表:
//class queue,          [基于<deque>实现]queue 的声明与实现.
//class priority_queue, [基于<deque>实现]priority_queue 的声明与实现.
//ps: 迭代器还是用deque 的迭代器



//priority_queue api list
/*

empty() 如果优先队列为空，则返回真
pop() 删除第一个元素
push() 加入一个元素
size() 返回优先队列中拥有的元素的个数
top() 返回优先队列中有最高优先级的元素

*/


#include <stdio.h>
#include <queue>
using namespace std;

//测试函数
int main(void){
  //创建优先队列
  priority_queue<int> x1;
  int arr_tmp[]= {10,60,50,20};
  priority_queue<int> x2(arr_tmp,arr_tmp+3);


  //size_type size();  现实优先队列size()
  printf("x1 priority_queue size() now is %d\n",x1.size());
  printf("x2 priority_queue size() now is %d\n",x2.size());


  //bool empty();  判断优先队列是否为空
  if(x1.empty())
    printf("x1 priority_queue is now empty\n");
  if(x2.empty())
    printf("x2 priority_queue is now empty\n");


  //const value_type& top()const;  查看top 值
  if(!x2.empty())
    printf("x2 priority_queue top() is now %d\n", x2.top());


  //void pop();  弹出top 值
  if(!x2.empty())
    x2.pop();
  if(!x2.empty())
    printf("x2 priority_queue top() is now %d\n", x2.top());


  //void push(const T& x);  压入一个新的最大值
  x2.push(1111);
  if(!x2.empty())
    printf("x2 priority_queue top() is now %d\n", x2.top());


  //size_type size();  查看优先队列的容量
  printf("x2 priority_queue size() is now %d\n", x2.size());


  //清空优先队列
  if(!x2.empty())
    x2.pop();
  if(!x2.empty())
    x2.pop();
  if(!x2.empty())
    x2.pop();
  printf("x2 priority_queue size() is now %d\n", x2.size());
  if(x2.empty())
    printf("x2 priority_queue is now empty\n");

  //未初始化的<优先队列top> 为空指针, 不能操作, 否则内存溢出
  //printf("x1 priority_queue top() is now %d\n", x1.top());

  x2.pop();
  x2.pop();//超出pop() 测试 okay
  if(x2.empty())
    printf("x2 priority_queue is now empty\n");

  printf("x2 priority_queue size() is now %d\n", x2.size());
  //溢出仍能工作, 但是没啥意义.
  printf("x2 priority_queue top() is now %d\n", x2.top());




  return 0;
}


