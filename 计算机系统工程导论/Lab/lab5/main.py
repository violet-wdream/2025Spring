import os
import ctypes
import subprocess
import sys


# 模拟Canary保护
def canary_demo():
    buffer = bytearray(64)
    canary = os.urandom(8)  # 随机canary值

    # 模拟栈溢出攻击
    payload = b"A" * 64 + canary + b"B" * 8 + b"\xef\xbe\xad\xde"
    try:
        # 检测canary是否被修改
        if payload[64:72] != canary:
            raise BufferError("Stack smashing detected")
        print("Canary保护模拟: 攻击成功")
    except BufferError as e:
        print(e)


# Windows兼容的ASLR演示
def aslr_demo():
    print("\nASLR地址示例:")
    try:
        # 获取当前进程的基地址
        base_addr = ctypes.windll.kernel32.GetModuleHandleW(None)
        print(f"当前进程基地址: 0x{base_addr:X}")

        # 获取kernel32.dll的基地址
        kernel32_addr = ctypes.windll.kernel32.GetModuleHandleW("kernel32.dll")
        print(f"kernel32.dll基地址: 0x{kernel32_addr:X}")
    except Exception as e:
        print(f"ASLR演示失败: {str(e)}")


# Windows兼容的GOT表演示
def got_demo():
    print("\nGOT表权限检查(模拟):")
    print("在Windows上，类似概念是IAT（导入地址表）")
    print("使用工具如CFF Explorer可以查看DLL导入和权限")


def main():
    print("=" * 50)
    print("缓冲区溢出防护技术演示 (Windows兼容版)")
    print("=" * 50)

    canary_demo()
    aslr_demo()
    got_demo()

if __name__ == "__main__":
    main()