import time

class progressBar:
    __scale = 100
    __start = 0
    def __init__(self) -> None:
        print("开始".center(self.__scale//4,"-"))
        self.__start = time.perf_counter()

    def __del__(self):
        print("\n结束".center(self.__scale//4,"-"))

    def setProgress(self,i):
        if i > 100:
            i = 100;
        a = "*" * ((i+1)//2)
        b = "." * ((self.__scale - (i+1))//2)
        c = (i / self.__scale) * 100
        dur = time.perf_counter() - self.__start
        print("\r{:^3.0f}%[{}->{}]{:.2f}s".format(c,a,b,dur),end = "")