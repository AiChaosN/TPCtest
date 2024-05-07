#!/bin/bash

# 清空或创建执行时间的文件
echo "Execution times:" > execution_times.txt

# 遍历当前目录下所有以q开头的文件，按数字顺序排序
for file in $(ls q* | sort -V)
do
  if [[ -x "$file" ]]  # 检查文件是否可执行
  then
    # 直接执行文件并通过grep命令提取含有"exe time"的行
    echo -n "$file " >> execution_times.txt  # 先将文件名写入文件
    ./$file | grep "exe time" >> execution_times.txt
  fi
done

echo "All execution times have been collected."
