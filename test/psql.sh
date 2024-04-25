
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
echo -n "" > ./sql_ans/ans.txt
echo -n "" > ./sql_ans/psql_time.txt

for i in {1..22}
do
    # 使用子 shell 来执行命令，捕获所有输出
    (echo '\timing on'; cat ../query/query$i.sql) | sudo -u postgres psql -p 5432 -d tpch 2>&1 | tee >(grep 'Time:' >> ./sql_ans/psql_time.txt) | grep -v 'Time:' >> ./sql_ans/ans.txt
done
