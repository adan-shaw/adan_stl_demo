//编译:
//g++ -ggdb3 -o x ./map.cpp

//<map>实现简介: 
//基于红黑树实现的map 集合功能, 是一种有序关联容器.
//提供快速查找, 较快的增删速度(查找复杂度: O(log n) )

//typedef _Rb_tree<key_type, value_type, _Identity<value_type>,
//		      key_compare, _Key_alloc_type> _Rep_type;//声明红黑树的别名
//_Rep_type _M_t;//The actual tree structure.
//这两句表明map 是红黑树实现的, 迭代器也是红黑树迭代器.
//这两句声明了一个红黑树容器, 并且将其<别名化: _Rep_type>


//实现文件: /usr/include/c++/6.3.0/bits/stl_map.h

//stl_map.h 容器列表:
//class map,     map 的声明与实现.



//map api list
/*

begin() 返回指向map头部的迭代器
clear() 删除所有元素
count() 返回指定元素出现的次数
empty() 如果map为空则返回true
end() 返回指向map末尾的迭代器
equal_range() 返回特殊条目的迭代器对
erase() 删除一个元素
find() 查找一个元素
get_allocator() 返回map的配置器
insert() 插入元素
key_comp() 返回比较元素key的函数
lower_bound() 返回键值>=给定元素的第一个位置
max_size() 返回可以容纳的最大元素个数
rbegin() 返回一个指向map尾部的逆向迭代器
rend() 返回一个指向map头部的逆向迭代器
size() 返回map中元素的个数
swap() 交换两个map
upper_bound() 返回键值>给定元素的第一个位置
value_comp() 返回比较元素value的函数

*/


#include <iostream>
#include <stdio.h>
#include <map>
using namespace std;


//测试函数
int main(void){
  //创建集合
  map<int,int> x1;                         // empty map of ints

  map<int,int> x2;                         // pointers used as iterators
  x2.insert(pair<int,int>(0,10));
  x2.insert(pair<int,int>(1,20));
  x2.insert(pair<int,int>(2,30));
  x2.insert(pair<int,int>(3,40));
  x2.insert(pair<int,int>(4,50));

  map<int,int> x3 (x2);                    // a copy of x2
  map<int,int> x4 (x2.begin(), x2.end());  // iterator ctor.


  //void clear();  清空map
  x1.clear();
  x3.clear();

  
  //bool empty();  检查map 是否为空
  if(x1.empty())
    printf("x1 map is now empty\n");
  if(x2.empty())
    printf("x2 map is now empty\n");
  if(x3.empty())
    printf("x3 map is now empty\n");


  //size_type size();  返回map 的size()
  printf("x2 map size() is now %d\n", x2.size());


  //iterator begin();  //返回map--顺向front() 元素的迭代器
  //iterator end();  //返回map--顺向end() 元素的迭代器

  //iterator rbegin();  //返回map--逆向front() 元素的迭代器
  //iterator rend();  //返回map--逆向end() 元素的迭代器
  if(!x2.empty()){
    map<int,int>::iterator it;//顺向迭代器遍历(比较安全一点的方法)
    printf("正向遍历x2\n");
    for(it = x2.begin(); it != x2.end(); *it++)
      printf("key=%d, val=%d\n", (*it).first,(*it).second);

    printf("\n\n");
    
    printf("反向遍历x2\n");
    map<int,int>::reverse_iterator rit;//逆向迭代器遍历
    for(rit = x2.rbegin(); rit != x2.rend(); *rit++)
      printf("key=%d, val=%d\n", *rit, (*rit).second);
  }
  

  //删除元素
  map<int,int>::iterator it;
  it=x2.begin();
  printf("erase first: key=%d,val=%d\n",*it,(*it).second);
  x2.erase(it);//删除第一个值

  x2.erase(2);

  it=x2.find(3);
  printf("erase <%d-%d>\n",*it,*x2.end());
  x2.erase(it, x2.end());//删除3 后面的--也就是删除少于3 的值
                         //注意map 是自动排序的, 从小到大排序


  //打印删除后的剩下元素--应该剩下一个20
  printf("\n\n");
  for(it = x2.begin(); it != x2.end(); *it++)
    printf("key=%d, val=%d\n", (*it).first,(*it).second);
  printf("\n");


  //插入新元素
  //千万不要用这样的数字表示, 如: 023, 0203
  //这表示不是十进制的数字, 麻烦
  it=x2.begin();
  x2.insert (it, pair<int,int>(9,123));
  x2.insert (it, pair<int,int>(9,65));
  x2.insert (it, pair<int,int>(11,3));
  x2.insert (it, pair<int,int>(91,21));
  


  //void swap(map<Key,Compare,Allocator>& st);  map 之间交换元素
  x1.swap(x2);

  //打印交换后的结果
  map<int,int>::reverse_iterator rit;
  printf("x2\n");
  for(rit = x2.rbegin(); rit != x2.rend(); *rit++)
    cout << "key=" << (*rit).first << " val="<< (*rit).second << endl;
  printf("\n\n");

  printf("x1\n");
  for(rit = x1.rbegin(); rit != x1.rend(); *rit++)
    cout << "key=" << (*rit).first << " val="<< (*rit).second << endl;
  printf("\n\n");


  
  //*********
  //查找类方法
  //*********
  //size_type count(cont key_type& x);  统计某个值元素的个数
  printf("x1, element '20' count is %d\n",x1.count(20));
  printf("x1, element '11' count is %d\n",x1.count(11));


  //iterator find(const key_type& x);  查找指定元素
  it=x1.find(11);
  if(it != x1.end())
    printf("x1.find(11) = %d\n", *it);
  else
    printf("x1.find(11) fail! no element<11>\n", *it);

  
  //************************************************************
  //查找区域内的元素值, 暂时弃用, 不知道用途
  //pair<iterator,iterator> equal_range ( const key_type& x ) const;
  //pair是将2个数据组合成一个数据, 当需要这样的需求时就可以使用pair, 
  //如stl中的map就是将key和value放在一起来保存...
  //但是这里, pair->first = lower_bound, pair->second = upper_bound

  //所以?? 在map 里面, pair 总是指向两个连续元素？？
  //pair<map<int,int>::iterator,map<int,int>::iterator> ret;
  //ret = x1.equal_range(20);//不知道有什么用.
  //printf("%d--%d\n", *ret.first,*ret.second);
  //printf("\n\n");
  //************************************************************

  
  //返回指向首个不小于<给定键>的元素的迭代器 -- <给定键>不一定要存在于map 中
  //不小于, 但是等于也算是不小于
  //iterator lower_bound(const key_type& x);
  it = x1.lower_bound(25);
  if(it != x1.end())
    printf("lower_bound(25) = %d\n", *it);


  //返回指向首个大于给定键的元素的迭代器 -- <给定键>不一定要存在于map 中
  //大于, 等于不算大于!!
  //iterator upper_bound(const key_type& x);
  it = x1.upper_bound(25);
  if(it != x1.end())
    printf("upper_bound(25) = %d\n", *it);

  
  //一个删除区域元素的demo:
  map<int,int> mymap;
  map<int,int>::iterator itlow,itup;
  for(int i=1; i<10; i++) 
    mymap[i]=i*10;                   // 10 20 30 40 50 60 70 80 90
  //下限包含3=30, 即小于, 等于. 上限排除等于, 走向更高的7-70.
  //但实际删除区域即3-7. 连同6-60 一起删除.
  //如果连用两个lower_bound, 不能删除6-60. 连用两个upper_bound, 则3-30不能删除.
  //反过来用, 则3-30, 6-60 都不会删除.
  itlow=mymap.lower_bound(3);        //       ^
  itup=mymap.upper_bound(6);         //                   ^

  mymap.erase(itlow,itup);           // 10 20 70 80 90

  cout << "mymap contains:\n";
  for (it=mymap.begin(); it!=mymap.end(); it++)
    cout << "key=" << (*it).first << " val="<< (*it).second << endl;
  
  printf("\n\n");

  
  //暂时不知道有什么用, 而且这个用法是错误的.
  /*
  //*********
  //比较类方法
  //*********
  //key_comp 键比较--返回用于比较键的函数
  //[实际就是拷贝出key 来, 但在map 中, key = value]
  map<int,int>::key_compare kcomp;
  kcomp = x1.key_comp();

  //打印
  int highest=x1.rbegin()->first;
  it=x1.begin();
  do{
    cout << "key=" << (*it).first << " val="<< (*it).second << endl;
  }while(kcomp((*it++).first,highest));
  printf("\n\n");


  //value_comp 值比较--返回用于在value_type类型的对象中比较键的函数
  //[实际就是拷贝出value 来, 但在map 中, key = value]
  map<int,int> vomp;
  pair<int,int> phighest;

  //打印
  phighest=*x1.rbegin();
  it=x1.begin();
  do{
    cout << "key=" << (*it).first << " val="<< (*it).second << endl;
  }while(vomp.value_comp()(*it++,phighest));
  printf("\n\n");
  */
  

  return 0;
}



