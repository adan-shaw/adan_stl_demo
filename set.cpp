//编译:
//g++ -ggdb3 -o x ./set.cpp

//<集合>实现简介: 
//基于红黑树实现的set 集合功能, 是一种有序关联容器.
//提供快速查找, 较快的增删速度(查找复杂度: O(log n) )

//typedef _Rb_tree<key_type, value_type, _Identity<value_type>,
//		      key_compare, _Key_alloc_type> _Rep_type;//声明红黑树的别名
//_Rep_type _M_t;// Red-black tree representing set.
//这两句表明set 是红黑树实现的, 迭代器也是红黑树迭代器.
//这两句声明了一个红黑树容器, 并且将其<别名化: _Rep_type>


//实现文件: /usr/include/c++/6.3.0/bits/stl_set.h

//stl_set.h 容器列表:
//class set,     set 的声明与实现.



//set api set
/*
1. begin()--返回指向第一个元素的迭代器
2. clear()--清除所有元素
3. count()--统计某个值元素的个数
4. empty()--如果集合为空, 返回true
5. end()--返回指向最后一个元素的迭代器
6. equal_range()--返回集合中与给定值相等的上下限的两个迭代器
7. erase()--删除集合中的元素
8. find()--返回一个指向被查找到元素的迭代器
9. get_allocator()--返回集合的分配器
10. insert()--在集合中插入元素
11. lower_bound()--返回指向大于(或等于)某值的第一个元素的迭代器
12. key_comp()--返回一个用于元素间值比较的函数
13. max_size()--返回集合能容纳的元素的最大限值
14. rbegin()--返回指向集合中最后一个元素的反向迭代器
15. rend()--返回指向集合中第一个元素的反向迭代器
16. size()--集合中元素的数目
17. swap()--交换两个集合变量
18. upper_bound()--返回大于某个值元素的迭代器
19. value_comp()--返回一个用于比较元素间的值的函数
*/


#include <iostream>
#include <stdio.h>
#include <set>
using namespace std;

//测试函数
int main(void){
  //创建集合
  set<int> x1;                         // empty set of ints

  int myints[]= {10,20,30,40,50};
  set<int> x2 (myints,myints+5);       // pointers used as iterators

  set<int> x3 (x2);                    // a copy of x2
  set<int> x4 (x2.begin(), x2.end());  // iterator ctor.


  //void clear();  清空set
  x1.clear();
  x3.clear();


  //bool empty();  检查set 是否为空
  if(x1.empty())
    printf("x1 set is now empty\n");
  if(x2.empty())
    printf("x2 set is now empty\n");
  if(x3.empty())
    printf("x3 set is now empty\n");


  //size_type size();  返回set 的size()
  printf("x2 set size() is now %d\n", x2.size());


  //iterator begin();  //返回set--顺向front() 元素的迭代器
  //iterator end();  //返回set--顺向end() 元素的迭代器

  //iterator rbegin();  //返回set--逆向front() 元素的迭代器
  //iterator rend();  //返回set--逆向end() 元素的迭代器
  if(!x2.empty()){
    set<int>::iterator it;//顺向迭代器遍历(比较安全一点的方法)
    for(it = x2.begin(); it != x2.end(); *it++)
      printf("%d\n", *it);

    printf("\n");
          
    set<int>::reverse_iterator rit;//逆向迭代器遍历
    for(rit = x2.rbegin(); rit != x2.rend(); *rit++)
      printf("%d\n", *rit);
  }
  
  
  //删除元素--三种删除方式
  //void erase(iterator position);//单个迭代器删除
  //size_type erase(const key_type& x);//常量值输入删除
                                       //值不存在就不删除, 也不会失败
  //void erase(iterator first, iterator last);//迭代器区域删除
  set<int>::iterator it;
  it=x2.begin();
  printf("erase first:%d\n",*it);
  x2.erase(it);//删除第一个值

  x2.erase(30);
  
  set<int>::reverse_iterator rit=x2.rbegin();
  printf("last element value is:%d\n",*rit);

  it=x2.find(40);
  printf("erase <%d-%d>\n",*it,*x2.end());
  x2.erase(it, x2.end());//删除40 后面的--也就是删除少于40 的值
                         //注意set 是自动排序的, 从小到大排序

  //question--已解决, 迭代器指向end() 是没有意义的, 如果反向查找, 请用rbegin()
  //stl 就是为了解决反向查找的问题, 才引入begin(), rbegin() 两个索引的.
  //end() 只是指引内存区域, 并不代表元素值地址!!
  //同时反向索引需要用: set<int>::reverse_iterator rit; 反向迭代器
  printf("为什么<*x2.end()> = 3,但是x2.erase(it,x2.end());却仍然正确?\n");
  printf("<40-3> ???\n");
  it = x2.end();
  printf("使用迭代器表示.end()后, it = x2.end(), *it=%d\n", *it);
  //


  //打印删除后的剩下元素--应该剩下一个20
  printf("\n\n");
  for(it = x2.begin(); it != x2.end(); *it++)
    printf("%d\n", *it);
  printf("\n");


  //插入新元素(有两种方式插入)
  //pair<iterator,bool> insert(const value_type& x);
  //iterator insert(iterator position, const value_type& x);
  x2.insert(123);
  x2.insert(23); //千万不要用这样的数字表示, 如: 023, 0203
  x2.insert(203);//这表示不是十进制的数字, 麻烦
  x2.insert(60);
  x2.insert(60);//插入相同值测试(不会失败, 但是元素会被替换,
                //但是替换了还是60, 没有意义)


  //void swap(set<Key,Compare,Allocator>& st);  set 之间交换元素
  x1.swap(x2);
  //打印测试结果
  for(rit = x2.rbegin(); rit != x2.rend(); *rit++)
    printf("x2-%d\n", *rit);
  for(rit = x1.rbegin(); rit != x1.rend(); *rit++)
    printf("x1-%d\n", *rit);
  printf("\n\n");


  //*********
  //查找类方法
  //*********
  //size_type count(cont key_type& x);  统计某个值元素的个数
  printf("x1, element '20' count is %d\n",x1.count(20));
  printf("x1, element '50' count is %d\n",x1.count(50));


  //iterator find(const key_type& x);  查找指定元素
  it=x1.find(203);
  if(it != x1.end())
    printf("x1.find(203) = %d\n", *it);
  else
    printf("x1.find(203) fail! no element<203>\n", *it);
  
  //************************************************************
  //查找区域内的元素值, 暂时弃用, 不知道用途
  //pair<iterator,iterator> equal_range ( const key_type& x ) const;
  //pair是将2个数据组合成一个数据, 当需要这样的需求时就可以使用pair, 
  //如stl中的map就是将key和value放在一起来保存...
  //但是这里, pair->first = lower_bound, pair->second = upper_bound

  //所以?? 在set 里面, pair 总是指向两个连续元素？？
  pair<set<int>::iterator,set<int>::iterator> ret;
  ret = x1.equal_range(20);//不知道有什么用.
  printf("%d--%d\n", *ret.first,*ret.second);
  printf("\n\n");
  //************************************************************

  
  //返回指向首个不小于<给定键>的元素的迭代器 -- <给定键>不一定要存在于set 中
  //不小于, 但是等于也算是不小于
  //iterator lower_bound(const key_type& x);
  it = x1.lower_bound(25);
  if(it != x1.end())
    printf("lower_bound(25) = %d\n", *it);


  //返回指向首个大于给定键的元素的迭代器 -- <给定键>不一定要存在于set 中
  //大于, 等于不算大于!!
  //iterator upper_bound(const key_type& x);
  it = x1.upper_bound(25);
  if(it != x1.end())
    printf("upper_bound(25) = %d\n", *it);


  //一个删除区域元素的demo:
  set<int> myset;
  set<int>::iterator itlow,itup;
  for(int i=1; i<10; i++) 
    myset.insert(i*10);               // 10 20 30 40 50 60 70 80 90
  //下限包含30, 即小于, 等于. 上限排除等于, 走向更高的70.
  //但实际删除区域即30-70. 连同60 一起删除.
  //如果连用两个lower_bound, 不能删除60. 连用两个upper_bound, 则30 不能删除.
  //反过来用, 则30, 60 都不会删除.
  itlow=myset.lower_bound(30);        //       ^
  itup=myset.upper_bound(60);         //                   ^

  myset.erase(itlow,itup);            // 10 20 70 80 90

  cout << "myset contains:";
  for (it=myset.begin(); it!=myset.end(); it++)
    cout << " " << *it;
  cout << endl;
  printf("\n\n");


  //*********
  //比较类方法
  //*********
  //key_compare key_comp();
  //key_comp 键比较--返回用于比较键的函数
  //[实际就是拷贝出key 来, 但在set 中, key = value]
  set<int>::key_compare kcomp;
  kcomp = x1.key_comp();

  //打印
  int highest=*x1.rbegin();
  it=x1.begin();
  do{
    cout << " " << *it;
  }while(kcomp(*it++,highest));
  printf("\n\n");


  //value_compare value_comp();
  //value_comp 值比较--返回用于在value_type类型的对象中比较键的函数
  //[实际就是拷贝出value 来, 但在set 中, key = value]
  set<int>::value_compare vomp;
  vomp = x1.value_comp();

  //打印
  highest=*x1.rbegin();
  it=x1.begin();
  do{
    cout << " " << *it;
  }while(vomp(*it++,highest));
  printf("\n\n");



  return 0;
}









