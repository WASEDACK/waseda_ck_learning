# ITS SIL Introduction
## 基本框架
**master_map,map_for_control,control_preprocess,control_algorithm,simulator,localization**联合仿真，实现了从规划到控制的功能验证。SIL模块之间的基础联系如下图所示：

##模块功能
**master_map**用来读取处理全局地图，此时的地图包含车道线等全局复杂信息。
|输入信号topic|信号含义|信号用途|
|:------:|:------:|:------:|
|/gnss/pose|初始姿态|依据当前定位读取附近小地图|



|输出信号topic|信号含义|
|:------:|:------:|
|/master_map/submap|当前车辆位置小地图|
|/master_map/navmap| |
|/master_map/speed_limit||


**map_for_control**用来处理局部小地图，讲车道线等信息生成为waypoints。

|输入信号topic|信号含义|信号用途|
|:------:|:------:|:------:|
|/master_map/submap|当前车辆位置小地图|计算生成路点信息|
|/localization/pose|当前车辆定位信息|计算生成路点信息|
|/vehicle/twist|当前车辆位置速度信息|计算生成路点信息|



|输出信号topic|信号含义|
|:------:|:------:|
|/planning/way_points|计算生成的路点信息|


**control_prepocess**用来对waypoints进行预先处理，比如从一长串waypoints中通过计算选出车辆要追随的一个或几个路点，供算法模块使用。

**control_algorithm**是SIL核心算法模块，以pure_pursuit为例，此横向控制算法包括pure_pursuit.py和pure_pursuit_utils.py，其中pure_pursuit.py为核心算法模块，pure_pursuit_utils.py内封装了一部分函数供核心模块使用。输入信号为来自control_prepocess的处理后的目标路点。

|输出信号topic|信号含义|
|:------:|:------:|
|/gatekeeper/cmd_vel_with_limits|计算得出的在合理范围內的控制量信息|
|pure_pursuit/rviz/target_waypoint|用于Rviz中的路点显示|
|pure_pursuit/rviz/front_car|用于Rviz中的前车显示|

**localization**模拟了车辆定位功能，输入信号为当前车辆姿态和速度信息，输出信号为/gnss/pose和/localization/pose，后期可能会将部分simulator显示功能移动至此。


**sparrow_simulator**实现了地图、车辆、规划路线、控制点和历史轨迹的显示与更新,尽可能的模拟了实车状况。
|输入信号topic|信号含义|信号用途|
|:------:|:------:|:------:|
|/initialpose|初始化位置信息|用于车辆位置初始化或重置|
|/move_base_simple/goal|目标姿态|
|/planning/way_points|路点信息|用于Rviz的路点显示|




|输出信号topic|信号含义|
|:------:|:------:|
|/locailization/pose|当前车辆位置信息|
|/vehicle/twist|发送车速和转角给算法模块|
|/sparrow/simulator/viz_his_track|历史轨迹点|
|/sparrow/simulator/dashboard|仪表显示数据|

**sparrow_communicate_sil**实现各个模块之间的信息传递的功能：包括接收初始位置，接收控制命令，接收CAN消息，发布车辆状态，发布定时器消息等等。
|输入信号topic|信号含义|信号用途|
|:------:|:------:|:------:|
|sparrow/simulator/initial_pose|初始化位置信息|包装成/can_tx|
|/gatekeeper/cmd_vel_with_limits|计算得出的在合理范围內的控制量信息|包装成/can_tx|
|/can_rx|解码成为pose和sts|

|输出信号topic|信号含义|
|:------:|:------:|
|/can_tx|通信|
|/sparrow/simulation/curr_pose|当前车辆位置信息|
|/sparrow/simulation/veh_sts|当前车辆状态信息|

**sparrow_simulator_engine**模拟了车辆的运动过程，根据算法模块计算的速度及轮胎转角实时反馈车辆的位置与横摆角变化;
|输入信号topic|输入信号名称 |信号含义|
|:-----:|:------:|:------:|
|/can_tx|MsgInitPose|初始姿态|
|/can_tx|MsgInitYaw|初始Yaw|
|/can_tx|MsgCtrlCmd|控制指令|


|输出信号topic|输出信号名称|信号含义|
|:------:|:-----:|:----:|
|/can_rx|MsgCurrPose|当前姿态|
|/can_rx|MsgVehSts|车辆状态（当前速度，Yaw，拖车转角）|

###模拟器数学模型
带有拖车的车辆运动学模型：



$$\begin{bmatrix}
\dot{x}\\\dot{y}
\\ \dot{\theta }
\\\dot{\alpha}
\end{bmatrix}=\begin{bmatrix}
cos(\theta)\\sin(\theta) 
\\ \frac{1}{L_1}tan(\delta)
\\-\frac{1}{L_2}sin(\alpha-\theta)
\end{bmatrix}
v$$

其中，$x$，$y$和$\theta$为车辆的位置和航向角；$v$和$\delta$为车辆的纵向速度和方向盘转角。$L_1$和$L_2$为头车长度和拖车长度。该微分方程的解为车辆运动的路径，即通过该运动微分方程迭代出来的路径能够满足非完整性约束和几何约束。
将上述模型离散化可以得到：

$$\begin{bmatrix}
x(t)\\y(t)
\\ \theta(t)
\\\alpha(t)
\end{bmatrix}=\begin{bmatrix}
x(t-1)\\y(t-1)
\\ \theta(t-1)
\\\alpha(t-1)
\end{bmatrix}+\Delta t\begin{bmatrix}
cos(\theta(t-1))\\sin(\theta(t-1)) 
\\ \frac{1}{L_1}tan(\delta)
\\-\frac{1}{L_2}sin(\alpha(t-1)-\theta(t-1))
\end{bmatrix}v(t)$$

其中，$\Delta t$为采样时间间隔；$x(t-1)$，$y(t-1)$和$\theta(t-1)$为$t-1$时刻车辆的状态；$v(t)$和$\delta(t)$为$t$时刻车辆的输入；可迭代出$t$时刻车辆的状态$x(t)$，$y(t)$和$\theta(t)$。



sparrow_simulator_engine是根据车辆初始状态$x(t_0)$,$y(t_0)$,$\theta(t_0)$和车辆纵向速度$v(t)$,方向盘转角$\delta(t)$通过运动学离散方程迭代出车辆运动的路径。实现要点为：

- 位置控制器：把路径点转化成纵向速度期望$v(t)$和方向盘转角的期望$\delta(t)$作为运动学模型的输入


- 时间戳：运动学是关于时间$t$的微分方程，迭代求解时各状态量和$\Delta t$在时间上要对齐



- 初始状态：迭代时要给出车辆初始状态$x(t_0)$，$y(t_0)$，和$\theta(t_0)$

##信息流如图所示

