# 1.1 vs环境搭建

1. 右键工程 -> Build Dependencies -> 自定义 -> 选中asm
2. 添加源文件：如Main.asm（以.asm结尾即可)
3. 安装插件ASMDUDE
4. 设置程序入口点： 连接器 -> 高级 -> 在 Entry Point处手动输入main
5. 代码示例

```assembly
.586	
.model	flat, stdcall
option	casemap:none

.data	

.code
main proc

	ret	
main endp	
end	
```

# 1.2 数据存储单元

* 计算机存取单元
  * 硬盘
  * 内存
  * CPU(寄存器)

### 寄存器

* 寄存器是位于CPU内部(每个CPU核心都有对应的一套独立寄存器)
* 通用寄存器 ： EAX ECX EDX EBX ESP EBP ESI EDI
* 段寄存器: CS SS DS ES FS GS
* 标志寄存器: EFLAGS
* 指令指针寄存器: EIP



# 1.3 通用寄存器

* 通用寄存器(32位)

用途是推荐的用途，而不是只能用于的操作

| 寄存器 | 用途                   | 编号 | 范围                    |
| :----- | ---------------------- | ---- | ----------------------- |
| EAX    | 累加器 乘除指令使用EAX | 0    | 0x00000000 ~ 0xFFFFFFFF |
| ECX    | 循环计数器             | 1    | 0x00000000 ~ 0xFFFFFFFF |
| EDX    | I/O指针                | 2    | 0x00000000 ~ 0xFFFFFFFF |
| EBX    | DS段的数据指针         | 3    | 0x00000000 ~ 0xFFFFFFFF |
| ESP    | 堆栈指针指向线程栈顶   | 4    | 0x00000000 ~ 0xFFFFFFFF |
| EBP    | 堆栈指针指向线程栈底   | 5    | 0x00000000 ~ 0xFFFFFFFF |
| ESI    | 字符串操作源指针       | 6    | 0x00000000 ~ 0xFFFFFFFF |
| EDI    | 字符串操作目标指针     | 7    | 0x00000000 ~ 0xFFFFFFFF |

* 通用寄存器对应关系

16位和8位寄存器位于32位寄存器内部，并没有新的寄存器

![image-20230922092706230](https://yeshooonotes.oss-cn-shenzhen.aliyuncs.com/notespic/202309220927269.png)

并不是每个32位寄存器里都有8位寄存器

| 32Bit | 16Bit | 8Bit   |
| ----- | ----- | ------ |
| EAX   | AX    | AH和AL |
| ECX   | CX    | CH和CL |
| EDX   | DX    | DH和DL |
| EBX   | BX    | BH和BL |
| ESP   | SP    | 无     |
| EBP   | BP    | 无     |
| ESI   | SI    | 无     |
| EDI   | DI    | 无     |

### x86dbg注意事项

暂时只断入口点

![image-20230922100316430](https://yeshooonotes.oss-cn-shenzhen.aliyuncs.com/notespic/202309221003485.png)

#### 1.选中某一行按空格开始编辑

#### 2. 双击寄存器区块的EIP可以跳转到绿色执行点

#### 3. 点击步进/F8让绿色执行当前行

![image-20230922101123431](https://yeshooonotes.oss-cn-shenzhen.aliyuncs.com/notespic/202309221011458.png)

### vs2019

1. 断点--debug --register

2. 右键窗口显示 cpu，cpu段和flags

   ```cpp
   .586	
   .model	flat, stdcall
   option	casemap:none
   
   .data	
   
   .code
   main proc
   	; 在纯汇编中，16进制数后面要加个H/h
   	; 如果第一位以字母开头，要在他前面加一个0
   	mov EAX, 0Fh
   	mov	AX, 0DDDDh
   	mov AH, 11h
   	mov AL, 22h
   
   
   	ret	
   main endp	
   end	
   ```

   

# 1.4 段寄存器

段寄存器需要进入内核才能感知到

* CPU - 保护模式---两个重要的机制

  详见内核，通过这两种机制保证运行的完整和正确性

  * 段的机制
  * 页的机制

* 常见段寄存器： CS SS DS ES FS GS(x64下才有)

  * CS - Code Segment 代码段
  * SS - Stack Segment 堆栈段
  * DS - Data Segment 数据段，==大部分基础从这寻址==
  * ES - Extend Segment 扩展段， ==很多复合指令都会用ES修饰==
  * ==FS== - 最特殊，是基于线程而言， R3 指向 **_TEB** ,R0指向**_KPCR**,ring是环的意思，cpu的级别划分，常用的是0环和3环，0环是内核层
  * GS

* ==段寄存器位宽==： 

  **位宽是96**

  x86dbg

  ![image-20230922112146754](https://yeshooonotes.oss-cn-shenzhen.aliyuncs.com/notespic/202309221121788.png)

  vs2019

  ![image-20230922112402605](https://yeshooonotes.oss-cn-shenzhen.aliyuncs.com/notespic/202309221124638.png)

  

  

* Segment Selector 

  上面看到的0023 和002b等叫做段选择子 ,段选择子有三部分组成，基于位数

  * RPL/CPL (0 ~ 1位)

  * TI ( 2 ~ 2位)

  * INDEX (3 ~ 15位)

    ![image-20230922113720832](https://yeshooonotes.oss-cn-shenzhen.aliyuncs.com/notespic/202309221138563.png)

  * 通过段选择子才能找到段描述符Segment Descriptor

    * P:是否有效
    * DPL：特权级别
    * S:
    * TYPE: 具体类型
    * LIMIT
    * BASE

# 1.5 指令指针寄存器EIP

* EIP寄存器当中存储的是下一条即将要执行的指令地址

# 1.6 标志寄存器EFLAGS

* EFLAGS 寄存器占4个字节32位
* 由一堆标志位共同组成EFLAGS寄存器且每个标志位占据一个二进制位

灰颜色表示值是固定的，不能修改

CF: 进位标志

PF: 奇偶标志

AF: 辅助进位标志

ZF: 零标志位

SF: 符号标志位

DF:

TF:

IF: 中断

DF：方向位

![image-20230922155753617](https://yeshooonotes.oss-cn-shenzhen.aliyuncs.com/notespic/202309221557743.png)

x86dbg和vs中的命名有区别，推荐看x86dbg中的名字

![image-20230922155400769](https://yeshooonotes.oss-cn-shenzhen.aliyuncs.com/notespic/202309221554826.png)

x86dbg中可以点击更改值





![image-20230922155531352](https://yeshooonotes.oss-cn-shenzhen.aliyuncs.com/notespic/202309221555481.png)

### 1.6.1 进位标志位CF： Carry Flag

最高有效位本身发生进位或者借位时，才是1

![image-20230925151745492](https://yeshooonotes.oss-cn-shenzhen.aliyuncs.com/notespic/202309251517548.png)



溢出

![image-20230922162954679](https://yeshooonotes.oss-cn-shenzhen.aliyuncs.com/notespic/202309221629283.png)

向最高有效位借位

![image-20230922162920872](https://yeshooonotes.oss-cn-shenzhen.aliyuncs.com/notespic/202309221629409.png)

### 1.6.2 奇偶标志位PF: Parity Flag

只看最低有效字节

注意0是偶数，

![image-20230925093923192](https://yeshooonotes.oss-cn-shenzhen.aliyuncs.com/notespic/202309250939234.png)

### 1.6.3 辅助进位标志AF:  Auxiliar Carry Flag

忽略网上的字节和字操作等，因为只有第四位进位才会置1

![image-20230925111638185](https://yeshooonotes.oss-cn-shenzhen.aliyuncs.com/notespic/202309251116298.png)

### 1.6.4 零标志位ZF: Zero Flag 

 ![image-20230925142647782](https://yeshooonotes.oss-cn-shenzhen.aliyuncs.com/notespic/202309251426837.png)

### 1.6.5 符号标志位SF: Signed Flag

运算结果的最高有效位是几就是几

![image-20230925143813227](https://yeshooonotes.oss-cn-shenzhen.aliyuncs.com/notespic/202309251438282.png)

### 1.6.6 方向标志位DF：Direction Flag

串是指字符串

![image-20230925150633206](https://yeshooonotes.oss-cn-shenzhen.aliyuncs.com/notespic/202309251506272.png)

### 1.6.7 溢出标志位OF: Overflow Flag:

计算机内部没有有符号还是无符号这个说法

![image-20230925153110690](https://yeshooonotes.oss-cn-shenzhen.aliyuncs.com/notespic/202309251531759.png)

### 1.6.8 EFLAGS寄存器

![image-20230925155659147](https://yeshooonotes.oss-cn-shenzhen.aliyuncs.com/notespic/202309251556213.png)
