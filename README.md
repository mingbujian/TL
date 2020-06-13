1、设计概况：

1）代码组织：
插件模式，参考NF，但每次tick只对插件调用，也就是动态库里的逻辑tick由设计者自行决定：https://github.com/ketoo/NoahGameFrame

2）网络层：
TCP, UDP的封装，参考LibEvent，参考UDP封装可靠连接。

3）上层逻辑：
架构设计了，设计模式支撑。

4）数据层：
redis实现的共享内存 + mysql，这样可以省事，避免直接使用redis，而容易产生瓶颈，把redis定制为共享内存机制，还是毕竟可靠的。
redis共享内存参考：https://github.com/edgarsi/redis-module-shm，https://cloud.tencent.com/developer/article/1005882

2、上层逻辑：尽量让各个功能独立

3、架构设计：
1）状态机
2）实体与组件
3）随机化
4）NF的插件模式

4、需要的功能设计：(参考：GameplayKit）
1）四叉树
2）寻路
3）极小化极大策略
4）代理，目标，行为
5）规则系统
6）同屏人数

5、维护一个时间，这个对逻辑很重要

6、技能系统

7、统一编码


