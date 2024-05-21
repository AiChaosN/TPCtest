#!/bin/bash

# 清空或创建执行时间的文件
echo "Execution times:" > execution_times.txt

# 设置文件所在目录
BIN_DIR="../bin"

# 按顺序遍历 q1 到 q22
for i in {1..22}; do
  file="${BIN_DIR}/q${i}"
  if [[ -x "$file" ]]  # 检查文件是否可执行
  then
    # 直接执行文件并通过 grep 命令提取含有 "exe time" 的行
    echo -n "$file " >> execution_times.txt  # 先将文件名写入文件
    ./$file | grep "exe time" >> execution_times.txt
  else
    echo "$file is not executable or does not exist, skipping..." >> execution_times.txt
  fi
done

echo "All execution times have been collected."
