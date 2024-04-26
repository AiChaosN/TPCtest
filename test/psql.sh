
if [ "$1" == "start" ]; then
    # 判断是否已经启动
    sudo service postgresql status
    # 如果没有启动，启动
    sudo service postgresql start
fi


if [ "$1" == "new" ]; then
    # 创建新表
    CREATE DATABASE tpch
    # 进入新表
    \c tpch
fi

if [ "$1" == "stop" ]; then
    sudo service postgresql stop
    exit 0
fi

# 以初始化用户进入psql
# sudo -u postgres psql 

# 创建新表
# CREATE DATABASE tpch



# 生成sql结果到sql_ans中
# for i in {1..22}
# do
#     (echo '\timing on'; cat ../query/query$i.sql) | sudo -u postgres psql -p 5432 -d tpch > ./sql_ans/ans$i.txt
# done

# 生成psql时间到psql_time.txt 统一放置
# 先清空或创建文件，确保文件是空的
echo -n "" > ./sql_ans/psql_time.txt

# for i in {1..22}
# do
#     echo "Running query$i and saving results to CSV..."
#     # 准备 SQL 语句并确保正确的引号使用
#     sql_query=$(cat ../query/query$i.sql | sed "s/'/''/g") # 转义单引号
#     # 使用子 shell 来执行命令，将 SQL 查询结果导出到 CSV 文件
#     (
#         echo "\Copy ($sql_query) TO '../sql_ans/query${i}.csv' WITH CSV HEADER;"
#     ) | sudo -u postgres psql -p 5432 -d tpch >/dev/null
# done

for i in {1..22}
do
    echo "Running query$i..."
    # 使用子 shell 来执行命令，捕获所有输出
    (
      echo "PREPARE plan$i AS $(cat ../query/query$i.sql);"
      echo "EXPLAIN ANALYZE EXECUTE plan$i;"
    ) | sudo -u postgres psql -p 5432 -d tpch 2>&1 | tee >(grep 'Execution Time' | sed "s/^/query$i: /" >> ./sql_ans/psql_time.txt) > /dev/null
done