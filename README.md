# Simulated-Annealing
A simple algorithm for calculating minimum value of a complex function given an exact range of variables.

## 0 代码简介

### 0.1 运行方法
直接将代码clone到本地，引用SA.h头文件，运行SA.cpp即可。

### 0.2 代码功能

以二元函数f(x,y) = sin(x)+cos(y)+0.2(x+y)为例，从(1,1)出发，使用模拟退火算法求解该函数在(-4,-6)到(6,6)区间内的最小值。寻优过程示意图如下：

![](https://raw.githubusercontent.com/xie96808/Simulated-Annealing/master/img/func1.png)


最终得到的最佳函数值为-2.98249，模拟退火算法计算全过程存储在uu.txt中。

## 1 模拟退火物理背景介绍
金属退火是将金属加热到一定温度，保持足够时间，然后以适宜速度冷却(通常是缓慢冷却，有时是控制冷却)的一种金属热处理工艺。而模拟退火算法来源于固体退火原理，将固体加温至充分高，再让其徐徐冷却，加温时，固体内部粒子随温升变为无序状，内能增大，而徐徐冷却时粒子渐趋有序，在每个温度都达到平衡态，最后在常温时达到基态，内能减为最小。

![](https://raw.githubusercontent.com/xie96808/Simulated-Annealing/master/img/E.png)

如上图，处在低温状态时，固体中分子具有的内能很低，在原本的位置上做小范围的振动。若是将固体加热到一定温度，分子内能将会增加，热运动加剧，分子排列的无序度增加。此时再将温度缓缓降低，在每个温度都达到平衡态（即准静态过程），分子具有的能量逐渐降低，最终回归到有序排列的状态，分子内能也跟着降到最低。

## 2 模拟退火基本原理
### 2.1 局部寻优与全局寻优
模拟退火算法(Simulated Annealing, SA)最早的思想是由N. Metropolis等人于1953年提出。模拟退火算法是基于Monte-Carlo 迭代求解策略的一种随机寻优算法，其出发点是基于物理中固体物质的退火过程与一般组合优化问题之间的相似性。介绍模拟退火前，有必要先介绍一下爬山算法。

![](https://raw.githubusercontent.com/xie96808/Simulated-Annealing/master/img/mountain.png)
爬山算法是一种简单的贪心搜索算法，该算法每次从当前解的临近解空间中选择一个最优解作为当前解，直到达到一个局部最优解。爬山算法实现很简单，其主要缺点是会陷入局部最优解，而不一定能搜索到全局最优解。如上图所示：我们要求取定义域内该曲线的最大值。假设C点为当前解，爬山算法搜索到A点这个局部最优解就会停止搜索，因为在A点无论向哪个方向小幅度移动都不能得到更优的解。
而模拟退火算法则是从某一较高初温出发，伴随温度参数的不断下降，结合一定的概率突跳特性在解空间中随机寻找目标函数的全局最优解，即在局部最优解能概率性地跳出并最终趋于全局最优。下图关于求解定义域范围内函数最大值的动图可以帮助大家更好地理解本模型：
![](https://raw.githubusercontent.com/xie96808/Simulated-Annealing/master/img/SA_gif.gif)

这里的“一定的概率”的计算参考了金属冶炼的退火过程，这也是模拟退火算法名称的由来。将温度T当作控制参数，目标函数值f视为内能E，而固体在某温度T时的一个状态对应一个解，然后算法试图随着控制参数T的降低，使目标函数f(内能E)也逐渐降低，直至趋于全局最小值（退火中低温时的最低能量状态），就像金属退火过程一样。

### 2.2 Metropolis准则

上文提到，模拟退火算法可以结合一定的概率突跳特性在解空间中随机寻找目标函数的全局最优解，即在局部最优解能概率性地跳出并最终趋于全局最优。具体是怎么实现"突跳"的呢？
设$E_t$为当前能量值，$E_{t+1}$为下一时刻的能量值，需要求解的是全范围内的能量最小值，接受概率为$P$,那么：
● 若下一时刻的能量值相较当前能量值更小，则完全接受该点的坐标与能量值，$P = 1$
● 若下一时刻的能量值更大，则以一定的概率接受这个新点的坐标与能量值，接受的概率为$e^{\frac{-(E_{t+1}-E_t)}{kT}}$，表达式为：
$P=\left\{
\begin{aligned}
1\qquad\qquad\quad,E_{t+1} < E_t\\
e^{\frac{-(E_{t+1}-E_t)}{kT}}, E_{t+1} >= E_t
\end{aligned}
\right.$
其中k是接受概率系数，一般取$k = 1$。
![](https://raw.githubusercontent.com/xie96808/Simulated-Annealing/master/img/metropolis.png)
Metropolis准则使得在目标点有可能陷入局部最优解B、C、E时，及时跳出，从而可能寻找到更优的全局最优解。

### 2.3 随机种子选取
在每个新温度or新的迭代次数下，我们究竟是如何完成"跳变"的呢？答案是通过一个随机生成的数字进行前/后移动。随机种子选取准则有两种方法：

![](https://raw.githubusercontent.com/xie96808/Simulated-Annealing/master/img/gauss.png)

![](https://raw.githubusercontent.com/xie96808/Simulated-Annealing/master/img/realdistribution.png)
### 2.4 基于随机种子的参数跳变方法

#### 2.4.1 Fast
![](https://raw.githubusercontent.com/xie96808/Simulated-Annealing/master/img/fast.png)

#### 2.4.2 Cauchy
![](https://raw.githubusercontent.com/xie96808/Simulated-Annealing/master/img/cauchy.png)

#### 2.4.3 Boltzmann
![](https://raw.githubusercontent.com/xie96808/Simulated-Annealing/master/img/boltzmann.png)

### 2.5 退火策略
### 3 算法流图及代码示例
![](https://raw.githubusercontent.com/xie96808/Simulated-Annealing/master/img/process1.png)

![](https://raw.githubusercontent.com/xie96808/Simulated-Annealing/master/img/process2.png)

### 4 模拟退火算法当前结果展示

