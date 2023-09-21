# 1. vs环境搭建

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

