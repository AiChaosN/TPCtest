
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





