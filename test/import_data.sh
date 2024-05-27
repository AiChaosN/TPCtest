#!/bin/bash

# ./import_data.sh data_0.1G tpch_01g

# 检查参数是否提供
if [ $# -ne 2 ]; then
  echo "Usage: $0 <data_directory> <db_name>"
  exit 1
fi

# 获取输入参数
DATA_DIR=$1
DB_NAME=$2

# 获取当前脚本所在目录的绝对路径
SCRIPT_DIR=$(dirname "$(realpath $0)")

# 获取数据目录的绝对路径
ABS_DATA_DIR=$(realpath "$SCRIPT_DIR/../$DATA_DIR")

# 设置数据库和表的相关信息
DB_PORT=5432
DB_USER="postgres"
PSQL="sudo -u $DB_USER psql -p $DB_PORT -d $DB_NAME"

# 导入表结构
$PSQL -f "$SCRIPT_DIR/create_table.sql"

# 创建tbl文件夹并移动tbl文件
cd $ABS_DATA_DIR
rm -rf tbl
mkdir tbl

for i in `ls *.tbl`
do
  name="tbl/$i"
  echo $name
  touch $name
  chmod 777 $name
  sed 's/|$//' $i >> $name
done

# 导入数据
$PSQL <<EOF
\copy lineitem FROM '$ABS_DATA_DIR/tbl/lineitem.tbl' WITH (FORMAT csv, DELIMITER '|', HEADER false);
\copy orders FROM '$ABS_DATA_DIR/tbl/orders.tbl' WITH (FORMAT csv, DELIMITER '|', HEADER false);
\copy customer FROM '$ABS_DATA_DIR/tbl/customer.tbl' WITH (FORMAT csv, DELIMITER '|', HEADER false);
\copy part FROM '$ABS_DATA_DIR/tbl/part.tbl' WITH (FORMAT csv, DELIMITER '|', HEADER false);
\copy partsupp FROM '$ABS_DATA_DIR/tbl/partsupp.tbl' WITH (FORMAT csv, DELIMITER '|', HEADER false);
\copy supplier FROM '$ABS_DATA_DIR/tbl/supplier.tbl' WITH (FORMAT csv, DELIMITER '|', HEADER false);
\copy nation FROM '$ABS_DATA_DIR/tbl/nation.tbl' WITH (FORMAT csv, DELIMITER '|', HEADER false);
\copy region FROM '$ABS_DATA_DIR/tbl/region.tbl' WITH (FORMAT csv, DELIMITER '|', HEADER false);
EOF
