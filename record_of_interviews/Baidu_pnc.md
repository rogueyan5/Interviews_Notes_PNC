# 百度自动驾驶技术部L4——提前批——预测决策规划控制面经

## 一面
1.自我介绍<br>
2.介绍fem算法原理，评价函数包含哪些项，fem是哪些英文单词的缩写，约束是如何进行设计的，权重系数是如何设计的？<br>
3.常见的优化求解器包括哪些？二次规划的求解器的底层原理有什么，各自有什么优缺点？<br>
答：hpipm、osqp、qpoases，常见求解方法有内点法、积极集法<br>
4.追问osqp求解器的求解原理，qpoases求解器原理，两种求解方法有什么区别？积极集法的求解原理是什么<br>
5.处理非线性优化问题时，求解和线性的有什么区别？<br>
6.求解优化问题时，是如何处理非线性约束的？<br>
7.详细描述一下梯度下降法的求解过程。
8.lqr控制器的稳定性应当如何证明，q矩阵会对系统稳定性产生什么影响？<br>
9.lqr矩阵是如何求解的，为什么选择对Riccati方程用迭代法求解而不直接去求其解析解？<br>
10.当遇到lqr基于的模型失真时，该如何保证控制器的性能？<br>
11.mpc和lqr算法的区别有哪些？<br>
12.卡尔曼滤波的核心思想是什么，包含哪些主要步骤，参数是如何确定的？<br>
13.方程式控制策略中横摆力矩控制的控制目标是什么？<br>
14.在方程式控制策略的纵向控制上有什么设计，利用了什么控制器，目标是什么？<br>

Coding:
用C++实现一个PID控制器类，要求包含积分抗饱和环节

反问：
1.L2 L4控制算法承担的职责有何不同？
2.自驾控制算法未来发展和改进？
3.面评，待提升和学习的点