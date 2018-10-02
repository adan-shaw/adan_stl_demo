//编译:
//g++ -ggdb3 -o x ./vector.cpp

//<向量>实现简介: 
//最原始的<向量系列>容器, 基于自分配内存来实现.
//vector 是一种<数组>容器, 是一种<数组自动增长>的数据结构.


//实现文件: /usr/include/c++/6.3.0/bits/stl_vector.h

//stl_vector.h 容器列表:
//struct _Vector_base, 向量的信息记录体

// class vector,       vector 的声明与实现.[并没有基于<任何容器的基础上>实现]
//                     裸奔, 自己分配内存, 自己管理.



//vector api list
/*

assign() 对Vector中的元素赋值
at() 返回指定位置的元素
back() 返回最末一个元素
begin() 返回第一个元素的迭代器
capacity() 返回vector所能容纳的元素数量(在不重新分配内存的情况下）
clear() 清空所有元素
empty() 判断Vector是否为空（返回true时为空）
end() 返回最末元素的迭代器(译注:实指向最末元素的下一个位置)
erase() 删除指定元素
front() 返回第一个元素
get_allocator() 返回vector的内存分配器
insert() 插入元素到Vector中
max_size() 返回Vector所能容纳元素的最大数量（上限）
pop_back() 移除最后一个元素
push_back() 在Vector最后添加一个元素
rbegin() 返回Vector尾部的逆迭代器
rend() 返回Vector起始的逆迭代器
reserve() 设置Vector最小的元素容纳数量
resize() 改变Vector元素数量的大小
size() 返回Vector元素数量的大小
swap() 交换两个Vector

 */


#include <stdio.h>
#include <vector>
using namespace std;

//测试函数
int main(void){
  //创建空的向量
  vector<int> x1;                       // empty vector of ints
  vector<int> x2(4,100);                // four ints with value 100
  vector<int> x3(x2.begin(),x2.end());  // iterating through x2
  vector<int> x4(x3);                   // a copy of x3


  //void clear();  清空向量
  x1.clear();
  x3.clear();


  //bool empty();  判断向量是否为空
  if(x1.empty())
    printf("x1 vector is now empty\n");
  if(x2.empty())
    printf("x2 vector is now empty\n");
  if(x3.empty())
    printf("x3 vector is now empty\n");
    

  //size_type size();  返回vector 的size()
  printf("x2 vector size() is now %d\n", x2.size());


  //void push_back(const T& x);  向vector 尾部压入元素
  x2.push_back(321);
  x2.push_back(123);


  //reference at(size_type n);下表访问元素
  int tmp = 0;
  if(!x2.empty()){
    int size = x2.size();
    for(;tmp < size;tmp++)//第一种遍历元素的方法: at() 遍历
      printf("at(%d) = %d\n", tmp, x2.at(tmp));

    for(tmp = 0;tmp < size;tmp++)//直接下标访问
      printf("x2[%d] = %d\n", tmp, x2[tmp]);
  }


  //iterator begin();  //返回向量--顺向front() 元素的迭代器
  //iterator end();  //返回向量--顺向end() 元素的迭代器

  //iterator rbegin();  //返回向量--逆向front() 元素的迭代器
  //iterator rend();  //返回向量--逆向end() 元素的迭代器
  if(!x2.empty()){
    vector<int>::iterator it;//顺向迭代器遍历(比较安全一点的方法)
    for(it = x2.begin(); it != x2.end(); *it++)
      printf("%d\n", *it);

    printf("\n");
          
    vector<int>::reverse_iterator rit;//逆向迭代器遍历
    for(rit = x2.rbegin(); rit != x2.rend(); *rit++)
      printf("%d\n", *rit);
  }


  //iterator erase(iterator position);  通过迭代器删除元素
  if(!x2.empty() && x2.size() == 6){
    //***************
    vector<int>::iterator it;//删除可以不用迭代器
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
    x2.pop_back();
  }
  if(x2.empty())
    printf("x2 vector is now empty\n");//元素已经删空


  //对空vector 错误操作测试
  x2.pop_back();//pop_back 只对尾操作, 可以pop 成负数
  x2.pop_back();//所以任何pop 操作都要检索vector 是否为empty()
  x2.pop_back();//否则vector 可能会被pop 坏
  printf("x2 front = %d, back = %d, 头不等于尾\n", x2.front(), x2.back());

  if(x2.empty())
    printf("x2 vector is now empty\n");

  printf("x2 vector size() is now %d\n", x2.size());


  //void resize(size_type sz, T c = T());如果容器已经坏了, 那么:
  x2.resize(0);//重新修改空vector 为0.

  printf("x2 vector size() is now %d\n", x2.size());
  if(x2.empty())
    printf("x2 vector is now empty\n");
  

  x2.resize(10,123);//重新创建10个元素, 每个元素都是123

  printf("x2 vector size() is now %d\n", x2.size());
  if(x2.empty())
    printf("x2 vector is now empty\n");
  
  
  //void swap(vector<T,Allocator>& vec);
  printf("\n\n交换元素测试\n");
  vector<int>::iterator it;
  if(x1.empty()){
    x1.swap(x2);
    for(it = x1.begin(); it != x1.end(); *it++)
      printf("%d\n", *it);

    if(x2.empty())
      printf("x2 vector is now empty\n");
  }


  return 0;
}


