#!/bin/bash
# ./exe_run.sh 0.01G 10

# 检查是否提供了两个参数
if [ $# -ne 2 ]; then
  echo "Usage: $0 <parameter_name> <time_limit>"
  exit 1
fi

# 获取输入参数
parameter_name=$1
time_limit=$2

# 清空或创建执行时间的文件，文件名包含参数名
output_file="execution_times_${parameter_name}.txt"
echo "Execution times:" > $output_file

# 设置文件所在目录
BIN_DIR="../bin"

# 按顺序遍历 q1 到 q22
for i in {1..22}; do
  file="${BIN_DIR}/q${i}"
  if [[ -x "$file" ]]; then  # 检查文件是否可执行
    # 记录文件名和参数
    echo -n "$file $parameter_name " >> $output_file

    # 使用 timeout 限制程序执行时间
    output=$(timeout $time_limit ./$file $parameter_name 2>&1 | grep "exe time")

    # 检查程序是否超时
    if [ $? -eq 124 ]; then
      echo " (timed out)" >> $output_file
    else
      echo "$output" >> $output_file
    fi
  else
    echo "$file is not executable or does not exist, skipping..." >> $output_file
  fi
done

echo "All execution times have been collected."
