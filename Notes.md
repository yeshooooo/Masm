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

