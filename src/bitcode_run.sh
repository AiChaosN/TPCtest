#!/bin/bash

# 清空或创建执行时间的文件
echo "Execution times:" > jit_execution_times.txt

# 设置文件所在目录
BITCODE_DIR="../bitcode"

# 按顺序遍历 q1.bc 到 q22.bc
for i in {1..22}; do
  bc_file="${BITCODE_DIR}/q${i}_linked.bc"
  
  # 检查 .bc 文件是否存在
  if [[ -f "$bc_file" ]]
  then
    # 使用 lli 执行 .bc 文件，并加载所需的其他 .bc 文件
    echo -n "q${i} " >> jit_execution_times.txt  # 先将文件名写入文件，移除 .bc 后缀
    lli "$bc_file" "$BITCODE_DIR/Structs.bc" | grep "exe time" >> jit_execution_times.txt
  else
    echo "Bitcode file $bc_file not found, skipping..." >> jit_execution_times.txt
  fi
done

echo "All execution times have been collected."
