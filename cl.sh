#!/bin/bash

#######################################################
#作用:
#  本脚本的作用在于统计指定文件夹内，指定类型代码的行数
#注:
#  本脚本目前只支持Linux平台
#选项:
#  第一个选项为需要统计的文件夹路径
#    -如果本脚本和要统计的文件夹在统一工作目录，则可以使用相对路径
#    -否则务必使用绝对路径
#  第二个选项为需要统计的代码类型，有以下类型：
#    -c:   C语言源文件代码
#    -cc:  C++语言源文件代码
#    -h:   C/C++语言头文件代码
#    -p:   Python语言代码
#    -g:   Go语言代码
#    -j:   Java语言代码
#
#作者:aideny
#######################################################


# 获取要统计的文件目录
path=$1

# 获取要统计的代码类型
code_type=$2

option=""

if [ ${code_type} = "-c" ]; then
  option="*.c"
elif [ ${code_type} = "-cc" ]; then
  option="*.cc"
elif [ ${code_type} = "-h" ]; then
  option="*.h"
elif [ ${code_type} = "-p" ]; then
  option="*.py"
elif [ ${code_type} = "-g" ]; then
  option="*.go"
elif [ ${code_type} = "-j" ]; then
  option="*.java"
else 
  echo "检查选项是否支持！"
  exit 1
fi

echo "开始统计..."

# 进行统计
if test -z ${path}
then
  echo "Usage: ./cl.sh [filepath][option]"
else 
  # 这个方法如果找不到指定语言的代码，会卡住
  # wc -l `find ${path} -name ${option}` | tail -n1
  find ${path} -name ${option} | xargs wc -l | tail -n1
fi

