#!/bin/bash

# 清空或创建执行时间的文件
echo "Execution times:" > execution_times.txt

# 遍历当前目录下所有以q开头且以.bc结尾的文件，按数字顺序排序
for bc_file in $(ls q*.bc | sort -V)
do
  # 检查.bc文件是否存在
  if [[ -f "$bc_file" ]]
  then
    # 使用lli执行.bc文件并通过grep命令提取含有"exe time"的行
    echo -n "${bc_file%.*} " >> execution_times.txt  # 先将文件名写入文件，移除.bc后缀
    lli "$bc_file" | grep "exe time" >> execution_times.txt
  else
    echo "Bitcode file $bc_file not found." >> execution_times.txt
  fi
done

echo "All execution times have been collected."
