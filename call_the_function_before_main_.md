## 在main函数之前和之后调用函数

### 之前

> 直接利用gcc提供的特殊选项 \_\_attribute\_\_

```c
#include <stdio.h>

void func_begin(void) __attribute__ ((constructor)); //注册全局对象析构函数
void func_begin(void){
    printf("begin\n");
}

int main(){
    printf("main\n");
    return 0;
}
```

> 同样是利用gcc提供的特殊选项 \_\_attribute\_\_，但是这个是根据".ctor"段的特殊原因，在 ".ctor"段中添加函数指针达到在main函数之前执行的原理

```c
#include <stdio.h>

void func(void){
    printf("begin\n");
}
typedef void(*fun_p)(void);
fun_p __attribute__ ((section(".ctors"))) fun_pointer = &func;

int main(){
    printf("main\n");
   	return 0;
}
```



### 之后

> 利用gcc提供的特殊选项 \_\_attribute\_\_

```c
#include <stdio.h>

void func_end(void) __attribute__ ((destructor)); //注册全局对象析构函数
void func_end(void){
    printf("end\n");
}

int main(){
    printf("main\n");
    return 0;
}
```

> 利用 atexit 函数注册在 exit 函数中执行的收尾函数

```c
#include <stdio.h>
#include <stdlib.h> //使用 atexit 需要包含这个头文件

void func_end(void){
    printf("end\n");
}

int main(){
    atexit(func_end);
    printf("main\n");
    return 0;
}
```

