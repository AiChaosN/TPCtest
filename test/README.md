# 1. 测试结果准确性

## 1.1 将表导入psql数据库

### 1.1.1 下载psql数据库

```
sudo apt-get update
apt install postgresql
```

### 1.1.2 开启psql数据库服务端

```
sudo service postgresql start
```

### 1.1.3 登录psql数据库

以postgres用户登录psql数据库
```
sudo -u postgres psql
```

### 1.1.4 创建数据库

创建名为tpch的数据库,并进入
```
create database tpch;
\c tpch
```

### 1.1.5 创建表结构

表结构在TPC-H目录下
```
vim TPC-H V3.0.1/dbgen/dss.ddl
```

将表结构导入数据库,在目录test下执行:
```
sudo -u postgres psql -p 5432 -d tpch -f ./create_table.sql
```

### 1.1.6 导入数据

由于tbl文件最后有'/'符号导致psql无法读取,需要将其删除，
创建tbl文件夹,并将tbl文件移动到tbl文件夹下。
运行以下代码来进行正则替换：
```
for i in `ls *.tbl`
do
 name="tbl/$i"
 echo $name
 `touch $name`
 `chmod 777 $name`
 sed 's/|$//' $i >> $name;
done
```

导入数据 
```
\copy lineitem FROM '~/mylab/9992/TPCtest/data/tbl/lineitem.tbl' WITH (FORMAT csv, DELIMITER '|', HEADER false);
\copy orders FROM '~/mylab/9992/TPCtest/data/tbl/orders.tbl' WITH (FORMAT csv, DELIMITER '|', HEADER false);
\copy customer FROM '~/mylab/9992/TPCtest/data/tbl/customer.tbl' WITH (FORMAT csv, DELIMITER '|', HEADER false);
\copy part FROM '~/mylab/9992/TPCtest/data/tbl/part.tbl' WITH (FORMAT csv, DELIMITER '|', HEADER false);
\copy partsupp FROM '~/mylab/9992/TPCtest/data/tbl/partsupp.tbl' WITH (FORMAT csv, DELIMITER '|', HEADER false);
\copy supplier FROM '~/mylab/9992/TPCtest/data/tbl/supplier.tbl' WITH (FORMAT csv, DELIMITER '|', HEADER false);
\copy nation FROM '~/mylab/9992/TPCtest/data/tbl/nation.tbl' WITH (FORMAT csv, DELIMITER '|', HEADER false);
\copy region FROM '~/mylab/9992/TPCtest/data/tbl/region.tbl' WITH (FORMAT csv, DELIMITER '|', HEADER false);
```

导入关系在dss.ri文件中
```
sudo -u postgres psql -p 5432 -d tpch -f ./create_relation.sql
```


运行sql文件:
```
sudo -u postgres psql -p 5432 -d tpch -f ./query1.sql
```

