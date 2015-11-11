# miniboot
bootloader written by myself 
本bootloader 实现的功能暂定为:
1、设置异常向量表
2、设置cpu为svc32模式
3、关闭看门狗
4、关闭中断
5、时钟初始化
6、刷新I/D caches
7、关闭MMU和caches
8、初始化内存控制器
9、简单初始化NAND flash 控制器
10、将bootloader 加载到内存中
11、初始化栈
12、清除bss段
13、串口初始化
14、网卡初始化
15、初始化LCD
16、解析、执行用户命令

