# 地平线——提前批——规控面经

## 一面
### 自我介绍<br>
### 项目介绍
### 八股
1. 申请内存new和delete，对应malloc和free有什么区别？
new实际上执行两个过程：1）分配未初始化的内存空间(malloc)。2）使用构造函数初始化
delete也有两个过程：1）析构函数对对象进行析构。2）回收内存(free)
对于非内部数据而言，malloc/free无法满足构造和析构的功能。
同时谨记，new是一个类型，malloc是一个字节长度；delete是delete一个类型，free是一个字节长度。
2. 虚函数内部是怎么实现的？
一个类中包含虚函数，编译器会为该类生成一个虚函数表，保存该类中虚函数的地址。
派生类继承父类，也一定有虚函数，编译器也会为派生类生成自己的虚函数表。
当我们定义一个类型时，编译器会检测该类型是否有虚函数，为该类生成一个虚函数指针，指向该类型的虚函数表。
3. c++的设计模式？
设计模式是在软件设计中常见的解决问题的可复用方案。它们提供了经过验证的方法和指导原则，帮助开发人员解决常见的设计问题，并促进可维护、灵活和可扩展的代码编写。
1）创建型设计模式
一个常见的设计模式是工厂模式（Factory Pattern）。工厂模式属于创建型设计模式，它提供了一种创建对象的方式，而无需直接在代码中实例化具体的对象。
2）行为型模式
命令模式 (Command): 将一个请求封装为一个对象，从而使你可用不同的请求对客户进行参数化。

### Coding:
实现memcpy函数
功能：从原地址拷贝到目标地址
主要思路： 将传入的数据类型强转为char，char 的字节是1，可以一个字节一个字节进行拷贝，这样可以实现对任意数据类型进行拷贝。
同时在c++中数组中的元素是存储在一块连续的地址上，因此可以直接将地址++遍历每一个元素。

## 二面
1. 在MPC求解问题中，会有状态变量和控制量权重调整，有什么方法能够更好的进行调整吗？
可以基于逆强化学习的方法，如果你有很多数据，那么就可以利用这些数据做不同场景的分类，比如某些场景更关注舒适性，某些场景更关注逃生成功率。
2. 如何用A*替换em动态规划中的dp进行决策？

3. 如何计算一个点到一条线段的投影？

4. 什么叫凸优化问题？
1）必须要有凸空间  2）代价函数必须是凸的
5. 除了二次规划问题，你还了解什么凸优化问题？osqp求解器的原理是什么？
