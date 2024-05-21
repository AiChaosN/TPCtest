import matplotlib.pyplot as plt

# 定义一个函数来读取文件并提取数据
def read_data(file_path):
    queries = []
    times = []
    with open(file_path, 'r') as file:
        for line in file:
            parts = line.split(':  Execution Time: ')
            query = parts[0].strip()
            time = float(parts[1].strip().replace(' ms', ''))
            queries.append(query)
            times.append(time)
    return queries, times

# 读取数据
file_path = 'path_to_your_file.txt'  # 请将此处替换为实际的文件路径
queries, times = read_data(file_path)

# 绘制图表
plt.figure(figsize=(10, 5))
plt.plot(queries, times, marker='o')
plt.xlabel('Query')
plt.ylabel('Execution Time (ms)')
plt.title('Query Execution Times')
plt.xticks(rotation=45)
plt.grid(True)
plt.tight_layout()

# 显示图表
plt.show()
