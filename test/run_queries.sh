#!/bin/bash

# ./run_queries.sh tpch_01g all 10

# 检查参数是否提供
if [ $# -lt 3 ]; then
  echo "Usage: $0 <db_name> <all|qN> <timeout_seconds>"
  exit 1
fi

# 获取输入参数
DB_NAME=$1
MODE=$2
TIMEOUT=$3

# 启动 PostgreSQL 服务（如果需要）
if [ "$4" == "start" ]; then
    sudo service postgresql status
    sudo service postgresql start
fi

# 定义输出文件
if [ "$MODE" == "all" ]; then
  OUTPUT_FILE="./${DB_NAME}_time.txt"
  echo -n "Execution times:" > $OUTPUT_FILE

  for i in {1..22}
  do
    echo "Running query$i..."
    (
      echo "PREPARE plan$i AS $(cat ../query/query$i.sql);"
      echo "EXPLAIN ANALYZE EXECUTE plan$i;"
    ) | timeout $TIMEOUT sudo -u postgres psql -p 5432 -d $DB_NAME 2>&1 | tee >(grep 'Execution Time' | sed "s/^/query$i: /" >> $OUTPUT_FILE) > /dev/null

    # 检查上一个命令是否因超时而失败
    if [ $? -eq 124 ]; then
      echo "query$i: exceeded timeout of $TIMEOUT seconds, skipped." >> $OUTPUT_FILE
    fi
  done
else
  # 提取查询编号
  QUERY_NUM=$(echo $MODE | sed 's/q//')
  OUTPUT_FILE="./${DB_NAME}_q${QUERY_NUM}.txt"
  echo -n "Execution times:" > $OUTPUT_FILE

  echo "Running query$QUERY_NUM..."
  (
    echo "PREPARE plan${QUERY_NUM} AS $(cat ../query/query${QUERY_NUM}.sql);"
    echo "EXPLAIN ANALYZE EXECUTE plan${QUERY_NUM};"
  ) | timeout $TIMEOUT sudo -u postgres psql -p 5432 -d $DB_NAME 2>&1 | tee >(grep 'Execution Time' | sed "s/^/query${QUERY_NUM}: /" >> $OUTPUT_FILE) > /dev/null

  # 检查上一个命令是否因超时而失败
  if [ $? -eq 124 ]; then
    echo "query${QUERY_NUM}: exceeded timeout of $TIMEOUT seconds, skipped." >> $OUTPUT_FILE
  fi
fi
