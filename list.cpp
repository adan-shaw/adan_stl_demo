//编译:
//g++ -ggdb3 -o x ./list.cpp

//<list>实现简介: 
//最原始的<list 系列>容器, 基于自分配内存来实现.
//list 是一种<链线性>容器, 是一种<链表>的数据结构, 用链表的方式实现.
//擅长频繁插入, 断开等操作, 
//也有信息载体记录链表信息, 防止因为求list size() 触发<全链遍历>.
//但是不擅长对元素进行排序, 查找.(查找复杂度: O(1-n) 不定)


//实现文件: /usr/include/c++/6.3.0/bits/stl_list.h

//stl_list.h 容器列表:
//struct _List_node_base, 基础节点
//struct _List_node, (public 继承from _List_node_base), 节点
//struct _List_iterator, 迭代器
//struct _List_const_iterator, 常量迭代器

// class _List_base, 队列信息记录器
// class list, (protected 继承from _List_base), list 的具体实现.


//list api list
/*

assign() 给list赋值
back() 返回最后一个元素
begin() 返回指向第一个元素的迭代器
clear() 删除所有元素
empty() 如果list是空的则返回true
end() 返回末尾的迭代器
erase() 删除一个元素
front() 返回第一个元素
get_allocator() 返回list的配置器
insert() 插入一个元素到list中
max_size() 返回list能容纳的最大元素数量
merge() 合并两个list
pop_back() 删除最后一个元素
pop_front() 删除第一个元素
push_back() 在list的末尾添加一个元素
push_front() 在list的头部添加一个元素
rbegin() 返回指向第一个元素的逆向迭代器
remove() 从list删除元素
remove_if() 按指定条件删除元素
rend() 指向list末尾的逆向迭代器
resize() 改变list的大小
reverse() 把list的元素倒转
size() 返回list中的元素个数
sort() 给list排序
splice() 合并两个list
swap() 交换两个list
unique() 删除list中重复的元素

*/


#include <stdio.h>
#include <list>
using namespace std;

//测试函数
int main(void){
  //创建list
  list<int> x1;                       // empty list of ints
  list<int> x2 (4,100);               // four ints with value 100
  list<int> x3 (x2.begin(),x2.end()); // iterating through x2
  list<int> x4 (x3);                  // a copy of x3

  // the iterator constructor can also be used to construct from arrays:
  int arr_tmp[] = {16,2,77,29};
  list<int> x5 (arr_tmp, arr_tmp + sizeof(arr_tmp) / sizeof(int) );


  //void clear();  清空list
  x1.clear();
  x3.clear();


  //bool empty();  检查list 是否为空
  if(x1.empty())
    printf("x1 list is now empty\n");
  if(x2.empty())
    printf("x2 list is now empty\n");
  if(x3.empty())
    printf("x3 list is now empty\n");


  //size_type size();  返回list 的size()
  printf("x2 list size() is now %d\n", x2.size());


  //void push_back(const T& x);  向list 尾部压入元素
  x2.push_back(321);

  //void push_front(const T& x);  向list 头部压入元素
  x2.push_front(123);


  //iterator begin();  //返回list--顺向front() 元素的迭代器
  //iterator end();  //返回list--顺向end() 元素的迭代器

  //iterator rbegin();  //返回list--逆向front() 元素的迭代器
  //iterator rend();  //返回list--逆向end() 元素的迭代器
  if(!x2.empty()){
    list<int>::iterator it;//顺向迭代器遍历(比较安全一点的方法)
    for(it = x2.begin(); it != x2.end(); *it++)
      printf("%d\n", *it);

    printf("\n");
          
    list<int>::reverse_iterator rit;//逆向迭代器遍历
    for(rit = x2.rbegin(); rit != x2.rend(); *rit++)
      printf("%d\n", *rit);
  }



  //注意: 由于list 不是连续线性容器, 你不能通过it+=1 来取得下一个元素
  //      必须全部是指针操作...
  //list 指针操作demo
  //list<unsigned int>::iterator it1,it2;//一点也不容出错
  list<int>::iterator it1,it2;           //unsigned int != int
  int tmp = 0;  
  for(tmp=1; tmp<10; tmp++)
    x1.push_back(tmp*10);

                          // 10 20 30 40 50 60 70 80 90
  it1 = it2 = x1.begin(); // ^^
  advance (it2,6);        // ^                 ^
  ++it1;                  //    ^              ^

  it1 = x1.erase (it1);   // 10 30 40 50 60 70 80 90
                          //    ^           ^

  it2 = x1.erase (it2);   // 10 30 40 50 60 80 90
                          //    ^           ^

  ++it1;                  //       ^        ^
  --it2;                  //       ^     ^

  x1.erase (it1,it2);     // 10 30 60 80 90
                          //        ^
  //iterator erase(iterator position);  通过迭代器删除元素
  //x1.clear();//splice() 测试要用 -- 整个元素插入


  
  if(!x2.empty() && x2.size() == 6){

  //void pop_back();  //从尾部弹出元素
    x2.pop_back();
  //reference front();  //返回front 元素
  //reference back();  //返回back 元素
    printf("x2 front = %d, back = %d, 头等于尾\n", x2.front(), x2.back());
  //void pop_front();  //从头部弹出元素
    x2.pop_front();
    x2.pop_front();
    x2.pop_front();
    x2.pop_front();
    x2.pop_front();
  }
  if(x2.empty())
    printf("x2 list is now empty\n");//元素已经删空
  printf("x2 list size() is now %d\n", x2.size());


  //对空list 错误操作测试
  //x2.pop_front();//list 由于是指针实现的, 绝对不能pop 空一次,
  //x2.pop_front();//否则指针会溢出.
  //x2.pop_front();
  
  //空队列的x2.front() == NULL == 0 !! 
  //注意, 这里不是数值等于0 的意思, 而是空指针的意思
  printf("x2 front = %d,back = %d,空list 头尾\n", x2.front(), x2.back());


  //void resize(size_type sz, T c = T());如果容器已经坏了, 那么:
  x2.resize(0);//重新修改空list 为0.

  printf("x2 list size() is now %d\n", x2.size());
  if(x2.empty())
    printf("x2 list is now empty\n");
  

  x2.resize(10,123);//重新创建10个元素, 每个元素都是123

  printf("x2 list size() is now %d\n", x2.size());
  if(x2.empty())
    printf("x2 list is now empty\n");


  //void sort();对元素进行排序处理
  printf("\n\n");
  x2.sort();
  list<int>::iterator it;
  for(it = x2.begin(); it != x2.end(); *it++)
    printf("%d\n", *it);
  printf("\n\n");
  x2.push_back(11111);
  x2.push_back(111);
  x2.push_front(11112);
  x2.sort();
  for(it = x2.begin(); it != x2.end(); *it++)
    printf("%d\n", *it);


  printf("\n\n融合两个list, 将某个list 插入另一个list 中. 测试\n");
  //void splice ( iterator position, list<T,Allocator>& x );
  //连接两个list
  if(!x1.empty()){
    it = x2.begin();
    printf("x2.begin() = %d\n",*it);
    ++it;// x2 points to 2
    x2.splice(it,x1);//将x1 所有元素插入x2, x1 清空
    if(x1.empty())
      printf("x1 list is now empty\n");
    
    for(it = x2.begin(); it != x2.end(); *it++)
      printf("%d\n", *it);
  }


  printf("\n\n交换元素测试\n");
  //void swap(list<T,Allocator>& lst);
  if(x1.empty()){
    x1.swap(x2);
    for(it = x1.begin(); it != x1.end(); *it++)
      printf("%d\n", *it);

    if(x2.empty())
      printf("x2 list is now empty\n");
  }


  printf("\n\n去除重复元素值测试\n");
  //void unique();
  printf("x1 list size() is now %d\n", x1.size());
  x1.unique();
  printf("x1 list size() is now %d\n", x1.size());
  for(it = x1.begin(); it != x1.end(); *it++)
    printf("%d\n", *it);
  

  return 0;
}



