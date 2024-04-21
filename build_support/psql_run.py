import psycopg2

# 数据库连接参数
conn = psycopg2.connect(
    dbname="your_dbname", 
    user="your_username", 
    password="your_password", 
    host="your_host", 
    port="your_port"
)

# 创建一个cursor对象
cur = conn.cursor()

# 创建表的SQL命令
create_table_query = '''
CREATE TABLE IF NOT EXISTS employees (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100),
    position VARCHAR(100),
    office VARCHAR(50),
    age INTEGER,
    start_date DATE,
    salary INTEGER
);
'''

# 执行SQL命令
cur.execute(create_table_query)

# 提交事务
conn.commit()

# 关闭cursor和连接
cur.close()
conn.close()
