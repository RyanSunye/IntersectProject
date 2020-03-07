| 项目                        | 内容                                                         |
| --------------------------- | ------------------------------------------------------------ |
| 课程：北航-2020-春-软件工程 | [博客园班级博客]( https://edu.cnblogs.com/campus/buaa/BUAA_SE_2020_LJ) |
| 要求：求交点个数            | [个人项目作业](https://edu.cnblogs.com/campus/buaa/BUAA_SE_2020_LJ/homework/10429) |
| 班级：005                   | [Sample](https://github.com/github/platform-samples.git)     |
| GitHub地址                  | [IntersectProject](https://github.com/RyanSunye/IntersectProject.git) |

## 一、PSP估算

1. 在开始实现程序之前，在下述 PSP 表格记录下你估计将在程序的各个模块的开发上耗费的时间。（0.5'）
2. 在你实现完程序之后，在下述 PSP 表格记录下你在程序的各个模块上实际花费的时间。（0.5'）

| PSP2.1                                  | Personal Software Process Stages        | 预估耗时（分钟） | 实际耗时（分钟） |
| :-------------------------------------- | :-------------------------------------- | :--------------- | :--------------- |
| Planning                                | 计划                                    |                  |                  |
| · Estimate                              | · 估计这个任务需要多少时间              | 10               | 10               |
| Development                             | 开发                                    |                  |                  |
| · Analysis                              | · 需求分析 (包括学习新技术)             | 20               | 60               |
| · Design Spec                           | · 生成设计文档                          | 10               | 10               |
| · Design Review                         | · 设计复审 (和同事审核设计文档)         | 5                | 0                |
| · Coding Standard                       | · 代码规范 (为目前的开发制定合适的规范) | 5                | 0                |
| · Design                                | · 具体设计                              | 20               | 60               |
| · Coding                                | · 具体编码                              | 60               | 120              |
| · Code Review                           | · 代码复审                              | 20               | 0                |
| · Test                                  | · 测试（自我测试，修改代码，提交修改）  | 30               | 60               |
| Reporting                               | 报告                                    |                  |                  |
| · Test Report                           | · 测试报告                              | 20               | 60               |
| · Size Measurement                      | · 计算工作量                            | 20               | 10               |
| · Postmortem & Process Improvement Plan | · 事后总结, 并提出过程改进计划          | 20               | 60               |
|                                         | 合计                                    | 220              | 450              |

如图所示，第一次项目的估计情况是严重与事实不符的，时间上花费了两倍有余，可能是因为事先根本对这些程序没有非常清晰的概念。





## 二、思路及设计

> 解题思路描述。即刚开始拿到题目后，如何思考，如何找资料的过程。（3'）
>
> 设计实现过程。设计包括代码如何组织，比如会有几个类，几个函数，他们之间关系如何，关键函数是否需要画出流程图？单元测试是怎么设计的？（4'）
>
> 代码说明。展示出项目关键代码，并解释思路与注释说明。（3'）

### 1. 解题思路

最开始最直接的想法就是暴力枚举，每次取一条，和其他所有图形求交点，加入集合中，让集合自动去重。复杂度为$O(N^2)$ ，对于$1\leq N\leq 1000$ 完全没问题，但是经过试验，$N>10^5$ 时不能达到性能要求。

实际上每次取出一条，不用和其他所有图形都求一遍，之前取出过的图形已经求过了不用再求，只用和没有取出的图形求一遍，但是这种思路复杂度没有下降，仍然是一种“暴力求解法”。

转而思考其他方法，动态规划就是一种极佳的办法，也在网络上搜到类似的题目：[求直线交点数目](https://blog.csdn.net/qaz135135135/article/details/52163461?depth_1-utm_source=distribute.pc_relevant.none-task&utm_source=distribute.pc_relevant.none-task)，但是并不符合题意，因为他们有一个很重要的假设，**任意三条直线不想交与一点**。



我们知道，如果**只有直线相交**，**任意三条直线不交一点**，且**没有直线平行**，则总数是固定的$\frac{n(n-1)}{2}$，而每出现下面所示的情况，总数都会相应减小：

- 聚合点（n条线交于一点）：总数减$\frac{n(n-1)}{2}-1$
- 平行线（n条线平行）：总数减$\frac{n(n-1)}{2}$

平行线很好说，建立集合列一个个加进来就好，然而真正要命的是聚合点怎么去寻找。三条直线交于一点，不仅需要考虑斜率，还得考虑截距，即`ax+by+c=0` 中a、b、c都需要考虑。n条直线相交于一点即以下方程组有解：

<p>
$$\begin{cases} a_1 x+b_1y=-c_1\\ a_2 x+b_2y=-c_2\\...\\ a_n x+b_ny=-c_n\\ \end{cases} $$


相当于一个维数大于秩的矩阵有解：
<p>
$$ \begin{pmatrix} a_{1}  & b_{1}\\ \vdots & \vdots\\ a_{n}  & b_{n} \end{pmatrix} \begin{pmatrix} x\\ y \end{pmatrix} = -\begin{pmatrix} c_1\\ \vdots\\c_n \end{pmatrix}$$

相当于：
<p>
$$ \begin{pmatrix} a_{1}  & b_{1} & c_1\\ \vdots & \vdots &\vdots\\ a_{n}  & b_{n} &c_n \end{pmatrix} \begin{pmatrix} x\\ y \\1 \end{pmatrix} = 0$$

其中，<p>$$\begin{pmatrix} a_{1} \\ \vdots\\ a_{n}  \end{pmatrix}$$ $$\begin{pmatrix} b_{1} \\ \vdots\\ b_{n}  \end{pmatrix}$$ $$\begin{pmatrix} c_{1} \\ \vdots\\ c_{n}  \end{pmatrix}$$ 是在n维空间中的一个向量，而它们的线性组合要能为0向量（其中c为必要项），最终要保证的是三个向量共面！

然而就算你能以$O(1)$的复杂度判断多条直线是否相交与一点，要遍历所有的组合又好比一颗巨大的树。最终只能望而却步。



### 2. 设计实现过程

主函数：每次输入一个图形，与其他所有图形进行相交运算，将所得的结果存入交点集合

Dot类：继承与$Pair<float, float>$ ，表示点的坐标或者一个向量，能进行加减乘除运算，同时有求模长、单位化方法

```c++
class Dot : public pair<float, float> {
public:
    Dot(float a, float b) {
        first = a;
        second = b;
    }

    inline Dot operator+(Dot dot) { return {first + dot.first, second + dot.second}; }
    inline Dot operator-(Dot dot) { return {first - dot.first, second - dot.second}; }
    inline Dot operator*(float t) { return {first * t, second * t}; }
    inline Dot operator/(float t) { return {first / t, second / t}; }

    inline float norm() { return first*first + second*second; }
    inline float abs() { return sqrt(norm()); }
    inline void unify() { *this=*this/abs(); }

};
```



Line类：有通过两个点坐标初始化方法和三个参数`a,b,c`初始化方法，有判断是否与另一条线平行，求与另一条线交点的方法

```c++
class Line {
public:
    float a, b, c;

    Line(float x0, float y0, float x1, float y1);
    Line(float aa, float ab, float ac);

    bool parallel(Line l);
    void intersect(set<Dot> *intersections, Line l);
    Dot intersect(Line l);
}
```



Circle类：有通过圆心坐标和半径初始化方法，求到一条直线距离，求与另一个圆交点，求与直线的交点方法。

```c++
class Circle {
public:
    float x, y, r;

    Circle(float ax, float ay, float ar) : x(ax), y(ay), r(ar) {}

    float distance(Line l);
    void intersect(set<Dot> *intersections, Line l);
    void intersect(set<Dot> *intersections, Circle c);
};
```



### 3. 单元测试

单元测试分别设计了直线与直线相交（包括平行和相交），圆与直线相交（包括相离、相切、相交），圆与圆相交（包括相离、相切、相交）三种情况，输出最后的交点坐标。

在这三种测试下，结果均正确。



### 4. 关键代码说明

因为交点个数可能是0、1、2个，没法设定一个定长的返回值，故只好传入一个指向点集的指针，有几个交点就存几个进去。

首先是`Line`的两个intersect方法：

```c++
// 直接通过公式，返回交点，不想交则报错
Dot Line::intersect(Line l) { 
    if(parallel(l)) throw exception();
    return Dot(b * l.c - l.b * c, l.a * c - a * l.c) / (a * l.b - l.a * b);
}

// 将交点加入集合中，忽略错误
void Line::intersect(set<Dot> *intersections, Line l) {
    try {
        intersections->insert(intersect(l));
    } catch (exception e) {}
}
```

其次是`Circle`的两个intersect方法，和circle相交的算法直接通过公式计算，不再赘述。而与直线相交需要先做一个到该直线的垂线，求出垂足：

```c++
void Circle::intersect(set<Dot> *intersections, Line l) {
    float d = distance(l);
    if (d > r) return;
    Line ll(l.b, -l.a, l.a * y - l.b * x);	// 垂线
    Dot dot = ll.intersect(l);	// 垂足
    if (d == r) {
        intersections->insert(dot);
        return;
    }
    float t = sqrt(r * r - d * d);	// 距垂足长度
    Dot direction(l.b, -l.a);	// 方向向量
    direction.unify();			// 单位化
    intersections->insert(dot + direction * t);
    intersections->insert(dot - direction * t);
}
```



## 三、性能及优化

> 记录在改进程序性能上所花费的时间，描述你改进的思路，并展示一张性能分析图（由 VS 2019 的性能分析工具自动生成），并展示你程序中消耗最大的函数。（3'）

| N     | 时间(ms) |
| ----- | -------- |
| 200   | 9        |
| 400   | 36       |
| 600   | 92       |
| 800   | 175      |
| 1000  | 303      |
| 2000  | 1429     |
| 3000  | 3458     |
| 4000  | 6463     |
| 5000  | 9820     |
| 10000 | 40873    |

如图所示采用暴力解法，结果大致呈现平方级复杂度，$t=9(\frac{N}{200})^2$，当N取 500w，需要时间5625Mms =1562.5h是根本不可接受的。 

通过性能分析图的描述如上，我发现程序中消耗最大的函数是`void intersect(set<Dot> *intersections, Circle c);`方法：

不可避免地出现了大量不可简化的计算。

```c++
void Circle::intersect(set<Dot> *intersections, Circle c) {
    float a1, b1, R1, a2, b2, R2;
    a1 = x;
    b1 = y;
    R1 = r;

    a2 = c.x;
    b2 = c.y;
    R2 = c.r;

    float R1R1 = R1 * R1;
    float a1a1 = a1 * a1;
    float b1b1 = b1 * b1;

    float a2a2 = a2 * a2;
    float b2b2 = b2 * b2;
    float R2R2 = R2 * R2;

    float subs1 = a1a1 - 2 * a1 * a2 + a2a2 + b1b1 - 2 * b1 * b2 + b2b2;
    if(subs1<=0) return;

    float subs2 = -R1R1 * a1 + R1R1 * a2 + R2R2 * a1 - R2R2 * a2 + a1a1 * a1 - a1a1 * a2 - a1 * a2a2 + a1 * b1b1 -
                  2 * a1 * b1 * b2 + a1 * b2b2 + a2a2 * a2 + a2 * b1b1 - 2 * a2 * b1 * b2 + a2 * b2b2;
    float subs3 = -R1R1 * b1 + R1R1 * b2 + R2R2 * b1 - R2R2 * b2 + a1a1 * b1 + a1a1 * b2 - 2 * a1 * a2 * b1 -
                  2 * a1 * a2 * b2 + a2a2 * b1 + a2a2 * b2 + b1b1 * b1 - b1b1 * b2 - b1 * b2b2 + b2b2 * b2;
    float sigma = sqrt((R1R1 + 2 * R1 * R2 + R2R2 - a1a1 + 2 * a1 * a2 - a2a2 - b1b1 + 2 * b1 * b2 - b2b2) *
                       (-R1R1 + 2 * R1 * R2 - R2R2 + subs1));

    Dot dot1(subs2, subs3), dot2(b1 - b2, a2 - a1);
    intersections->insert((dot1 + dot2 * sigma) / (2 * subs1));
    intersections->insert((dot1 - dot2 * sigma) / (2 * subs1));
}
```
