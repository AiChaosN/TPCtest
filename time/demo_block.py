import matplotlib.pyplot as plt
import numpy as np

# 手动编写的代码执行时间数据（使用JIT）
hand_code_jit = {
    'q1': 1.111, 'q3': 0.211, 'q4': 0.214, 'q5': 0.857,
    'q6': 0.121, 'q7': 7.881, 'q8': 0.007, 'q9': 0.412, 'q10': 0.655,
    'q11': 0.018, 'q12': 0.202, 'q13': 0.075, 'q17': 1.06,
    'q19': 0.759, 'q21': 0.102
}

# 手动编写的代码执行时间数据（不使用JIT）
hand_code_no_jit = {
    'q1': 1.234, 'q3': 0.287, 'q4': 0.201, 'q5': 1.191,
    'q6': 0.105, 'q7': 5.898, 'q8': 0.014, 'q9': 0.424, 'q10': 0.502,
    'q11': 0.022, 'q12': 0.248, 'q13': 0.068, 'q17': 0.842,
    'q19': 0.593, 'q21': 0.114
}

# Psql执行时间数据
psql = {
    'q1': 5.022, 'q3': 1.016, 'q4': 1.247, 'q5': 0.472,
    'q6': 0.715, 'q7': 0.962, 'q8': 0.129, 'q9': 2.274, 'q10': 1.194,
    'q11': 0.13, 'q12': 1.427, 'q13': 1.363, 'q17': 0.084,
    'q19': 0.975, 'q21': 0.145
}

queries = list(hand_code_jit.keys())
# 将查询按照字母顺序排列
queries.sort(key=lambda x: int(x[1:]) if x[1:].isdigit() else x)

# 查询执行时间的柱状图
plt.figure(figsize=(14, 6))
plt.bar(np.arange(len(queries)) - 0.2, [hand_code_jit[query] for query in queries], width=0.2, label='Hand Code (JIT)', color='b')
plt.bar(np.arange(len(queries)), [hand_code_no_jit[query] for query in queries], width=0.2, label='Hand Code (No JIT)', color='g')
plt.bar(np.arange(len(queries)) + 0.2, [psql[query] for query in queries], width=0.2, label='PSQL', color='r')
plt.xlabel('Queries')
plt.ylabel('Execution Time (ms)')
plt.title('Execution Time Comparison for Different Queries')
plt.xticks(np.arange(len(queries)), queries, rotation=45, ha='right')
plt.legend()
plt.tight_layout()

plt.show()