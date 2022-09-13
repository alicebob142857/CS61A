# EDCHost24
## 注意：先将icon和labyrinth文件夹添加到运行程序的文件夹中！！！

## 软件使用方法

- **串口与摄像头选择：**程序开始运行后，首先会弹出 `设置` 窗口，选择串口端口号Port1，Port2和摄像头编号。

- **角点标定：**比赛开始之前首先要校正场地坐标。方法为依次点场地的四个角，顺序是**左上-右上-左下-右下**。已经标定的场地。使用过程中，也可以点击 `重设边界点` 以重新标定比赛场地坐标。

- **颜色参数设置：**在 `设置` 中调节识别参数，进行小车位置的识别。
  
  参数使用的是 HSV(Hue, Saturation, Value) 颜色空间，HSV颜色空间示意图如下：
  
  ![HSV](.\HSV.jpg)
  
  色调的上下限是Hue1L和Hue1H；
  
  饱和度的下限是Sat1L，上限固定为255；
  
  亮度的下限是ValueL，上限固定为255；
  
  有效面积的下限是AreaL，上限未设定。
  
  点击 `保存`，颜色参数将会保存至程序同一文件夹下；点击 `读取`，可读取程序同一文件夹下所保存的颜色参数。
  
  > 参考调节技巧：先把SatxL调至最小，再调Hue确定一个范围，并放松至适当宽；最后调高SatxL到没有误识别点就基本可以了。新版本上位机增加蒙版显示功能，可查看识别的中间效果。
  
- 单击 `开始` 以开始比赛进程。

- 单击 `新比赛` 以开始全新比赛。

- 单击 `暂停`，比赛暂停。

- 单击 `继续`，暂停的比赛继续进行。

- 在上下半场的第一阶段设置隔离区时，由裁判在小车停止并点亮 LED 时点击 `设置隔离区`，在小车所在的格点设置隔离区。（若上位机识别小车距离任何格点超过五厘米，则不能成功设置隔离区）

- 单击 `开始录像`，开始录像；再次单击，结束录像。结束后，会将比赛过程录制成视频，生成以时间为文件名的视频文件，储存在`video`文件夹下，并生成同名的txt文件，记录犯规记录信息。

## 通信模块使用方法
使用ZigBee进行通信。首先将模块按照“ZigBee”文件夹中的《DL-30按键配置使用说明书》进行配置，再连接至电脑后打开上位机（或进入上位机“设置”中手动选择端口）即可。

通信模块设置参数：

- 波特率：115200

- 频道：设置为只有右下角的灯闪烁

- 工作模式：广播模式


## 通信协议

通信协议见“EDC21通信协议v x.x”。

通信协议在数据包第28、29字节增加了CRC16校验码，多项式0x8005，初始值0xFFFF。可在网站[https://crccalc.com/](https://crccalc.com/)上进行在线计算（其中的CRC-16/MODBUS）。注意，这里所计算的是数据包中除去最后四行（**第0~27字节**，包含了保留位，不包含末尾的0x0D、0x0A）的校验码。关于校验码，提供一个示例程序crc16.c，位于“ZigBee”文件夹中，包含了一个计算CRC16校验码的函数`unsigned short crc16(unsigned char *data_p, unsigned char length)`。

## 从源码编译

- 测试环境：Microsoft Visual Studio 2017, .NET Framework 4.6。打开EDCHost21.sln后直接生成解决方案即可。
- 运行前将ForDebug文件夹下的dll.zip解压为文件夹后放至"<项目路径>\EDCHost21\bin\Debug"路径下。“data.txt”是颜色设置参考数值，也可放在"<项目路径>\EDCHost21\bin\Debug"路径下，程序将自动读取。
