#!/bin/bash

# 检查是否提供了两个参数
if [ $# -ne 2 ]; then
  echo "Usage: $0 <parameter_name> <time_limit>"
  exit 1
fi

# 获取输入参数
parameter_name=$1
time_limit=$2

# 清空或创建执行时间的文件，文件名包含参数名
output_file="jit_execution_times_${parameter_name}.txt"
echo "Execution times:" > $output_file

# 设置文件所在目录
BITCODE_DIR="../bitcode"

# 按顺序遍历 q1.bc 到 q22.bc
for i in {1..22}; do
  bc_file="${BITCODE_DIR}/q${i}_linked.bc"
  
  # 检查 .bc 文件是否存在
  if [[ -f "$bc_file" ]]
  then
    # 记录文件名和参数
    echo -n "q${i} " >> $output_file  # 先将文件名写入文件，移除 .bc 后缀
    
    # 使用 timeout 和 lli 执行 .bc 文件，并加载所需的其他 .bc 文件
    output=$(timeout $time_limit lli "$bc_file" "$BITCODE_DIR/Structs.bc" 2>&1 | grep "exe time")
    
    # 检查程序是否超时
    if [ $? -eq 124 ]; then
      echo " (timed out)" >> $output_file
    else
      echo "$output" >> $output_file
    fi
  else
    echo "Bitcode file $bc_file not found, skipping..." >> $output_file
  fi
done

echo "All execution times have been collected."
