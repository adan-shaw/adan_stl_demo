//编译:
//g++ -ggdb3 -o x ./deque.cpp

//<双向队列>实现简介: 
//最原始的<队列系列>容器, 基于自分配内存来实现.
//deque 是一种<适配器>容器, 一种先进先出(FIFO)的数据结构.
//注意: 根据at() 函数的实现:
/*
at(size_type __n){
	_M_range_check(__n);//这个函数只是检查__n >= this->size(), 常规溢出检查

	return (*this)[__n];//可以断定,deque 实际就是在数组上面实现的, 
                      //所有deque 相关的容器也是有数组属性.
}
*/

//实现文件: /usr/include/c++/6.3.0/bits/stl_deque.h

//stl_deque.h 容器列表:
//struct _Deque_iterator, 实现大部分是内联函数, 这意味着:
//                        迭代器操作基本都是真实代码操作, 都是一些逻辑操作.
//                        向前向后, 提取目标数据等.

// class _Deque_base,     deque 的声明与实现.[并没有基于<任何容器的基础上>实现]
//                        裸奔, 自己分配内存, 自己管理.

//ps: 以上两个容器的实现, 都是先声明结构体or 类, 后续跟着具体实现.
//    例如:声明迭代器, 实现迭代器. 声明类, 实现类.
//    根据类名(), 你可以很容易找到构造函数和释构函数




//deque api list
/*

assign() 设置双向队列的值
at() 返回指定的元素
back() 返回最后一个元素
begin() 返回指向第一个元素的迭代器
clear() 删除所有元素
empty() 返回真如果双向队列为空
end() 返回指向尾部的迭代器
erase() 删除一个元素
front() 返回第一个元素
get_allocator() 返回双向队列的配置器
insert() 插入一个元素到双向队列中
max_size() 返回双向队列能容纳的最大元素个数
pop_back() 删除尾部的元素
pop_front() 删除头部的元素
push_back() 在尾部加入一个元素
push_front() 在头部加入一个元素
rbegin() 返回指向尾部的逆向迭代器
rend() 返回指向头部的逆向迭代器
resize() 改变双向队列的大小
size() 返回双向队列中元素的个数
swap() 和另一个双向队列交换元素

*/


#include <stdio.h>
#include <deque>
using namespace std;

//测试函数
int main(void){
  //创建双向队列
  deque<int> x1;                       // empty deque of ints
  deque<int> x2 (4,100);               // four ints with value 100
  deque<int> x3 (x2.begin(),x2.end()); // iterating through x2
  deque<int> x4 (x3);                  // a copy of x3

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  deque<int> x5 (myints, myints + sizeof(myints) / sizeof(int) );


  //void clear();  清空双向队列
  x1.clear();
  x3.clear();


  //bool empty();  检查双向队列是否为空
  if(x1.empty())
    printf("x1 deque is now empty\n");
  if(x2.empty())
    printf("x2 deque is now empty\n");
  if(x3.empty())
    printf("x3 deque is now empty\n");


  //size_type size();  返回deque 的size()
  printf("x2 deque size() is now %d\n", x2.size());


  //void push_back(const T& x);  向deque 尾部压入元素
  x2.push_back(321);

  //void push_front(const T& x);  向deque 头部压入元素
  x2.push_front(123);


  //reference at(size_type n);下表访问元素
  int tmp = 0;
  if(!x2.empty()){
    int size = x2.size();
    for(;tmp < size;tmp++)//第一种遍历元素的方法: at() 遍历
      printf("at(%d) = %d\n", tmp, x2.at(tmp));

    for(tmp = 0;tmp < size;tmp++)//直接下标访问
      printf("x2[%d] = %d\n", tmp, x2[tmp]);
  }


  //iterator begin();  //返回双向队列--顺向front() 元素的迭代器
  //iterator end();  //返回双向队列--顺向end() 元素的迭代器

  //iterator rbegin();  //返回双向队列--逆向front() 元素的迭代器
  //iterator rend();  //返回双向队列--逆向end() 元素的迭代器
  if(!x2.empty()){
    deque<int>::iterator it;//顺向迭代器遍历(比较安全一点的方法)
    for(it = x2.begin(); it != x2.end(); *it++)
      printf("%d\n", *it);

    printf("\n");
          
    deque<int>::reverse_iterator rit;//逆向迭代器遍历
    for(rit = x2.rbegin(); rit != x2.rend(); *rit++)
      printf("%d\n", *rit);
  }


  //iterator erase(iterator position);  通过迭代器删除元素
  if(!x2.empty() && x2.size() == 6){
    //***************
    deque<int>::iterator it;//删除可以不用迭代器
    it = x2.begin();
    for(tmp=1;tmp<3;tmp++){//移除begin() 下一个元素, 两次
      //x2.erase(*it+=1);//等价于*it++ 移动迭代器
      x2.erase(it+=1);
    }
    //***************
    x2.erase(x2.begin()+1,x2.begin()+3);//再删除2 个元素. 这次是迭代器段删除

    for(it = x2.begin(); it != x2.end(); *it++)
      printf("%d\n", *it);//打印剩余的123,321

  //void pop_back();  //从尾部弹出元素
    x2.pop_back();
  //reference front();  //返回front 元素
  //reference back();  //返回back 元素
    printf("x2 front = %d, back = %d, 头等于尾\n", x2.front(), x2.back());
  //void pop_front();  //从头部弹出元素
    x2.pop_front();
  }
  if(x2.empty())
    printf("x2 deque is now empty\n");//元素已经删空


  //对空deque 错误操作测试
  x2.pop_front();//pop_front 只对头操作, 可以pop 成负数
  x2.pop_front();//所以任何pop 操作都要检索deque 是否为empty()
  x2.pop_front();//否则deque 可能会被pop 坏
  printf("x2 front = %d, back = %d, 头不等于尾\n", x2.front(), x2.back());

  if(x2.empty())
    printf("x2 deque is now empty\n");

  printf("x2 deque size() is now %d\n", x2.size());


  //void resize(size_type sz, T c = T());如果容器已经坏了, 那么:
  x2.resize(0);//重新修改空deque 为0.

  printf("x2 deque size() is now %d\n", x2.size());
  if(x2.empty())
    printf("x2 deque is now empty\n");
  

  x2.resize(10,123);//重新创建10个元素, 每个元素都是123

  printf("x2 deque size() is now %d\n", x2.size());
  if(x2.empty())
    printf("x2 deque is now empty\n");


  //void swap(list<T,Allocator>& dqe);
  printf("\n\n交换元素测试\n");
  deque<int>::iterator it;
  if(x1.empty()){//这是根据当前逻辑做的判断, 实际使用时不一定需要
    x1.swap(x2);
    for(it = x1.begin(); it != x1.end(); *it++)
      printf("%d\n", *it);

    if(x2.empty())
      printf("x2 deque is now empty\n");
  }


  return 0;
}


