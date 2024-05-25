import re  # 导入正则表达式模块
import matplotlib.pyplot as plt
###
#def read_execution_times(file_path):
#   times = [0.0] * 16
#    with open(file_path, 'r') as file:
#        for line in file:
#            if "exe time" in line or "Execution Time" in line:
#
#                match = re.search(r'(\d+)', line)
#                if match:
#                    query_number = int(match.group(1))
#                    time = float(line.split()[-2])
#                    if query_number <= 22:
#                        times[query_number - 1] = time
#    return times
###

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

def calculate_increase_ratios(dict1, dict2):
    ratios = {}
    for key in dict1.keys():
        value1 = dict1[key]
        value2 = dict2.get(key, 0)
        if value1 == 0 or value2 == 0:
            ratios[key] = 0.0
        else:
            increase = (value2 - value1) / value1
            increase = round(increase, 2)
            ratios[key] = increase
    return ratios

def plot_ratios(ratios_dict1, ratios_dict2, labels=None, title="Scatter Plot", xlabel="X-axis", ylabel="Y-axis", plt_name="scatter_plot", save=False):
    keys = sorted(ratios_dict1.keys(), key=lambda x: int(x[1:]))
    ratios1 = [ratios_dict1[key] for key in keys]
    ratios2 = [ratios_dict2[key] for key in keys]

    plt.plot(keys, ratios1, marker='o', color='blue', label=labels[0])
    plt.plot(keys, ratios2, marker='o', color='red', label=labels[1])

    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.legend()
    plt.grid(True)
    if save:
        plt.savefig(f"{plt_name}.png")
    plt.show()

# open
bin_times = hand_code_jit
bitcode_times = hand_code_no_jit
psql_times = psql

# print
print("\nevery way time: ")
print("BIN Times:", bin_times)
print("Bitcode Times:", bitcode_times)
print("PSQL Times:", psql_times)

# increase ratio
bin_to_psql_ratios = calculate_increase_ratios(bin_times, psql_times)
bitcode_to_psql_ratios = calculate_increase_ratios(bitcode_times, psql_times)

print("\nevery way increase ratio: ")
print("BIN to PSQL Ratios:", bin_to_psql_ratios)
print("Bitcode to PSQL Ratios:", bitcode_to_psql_ratios)

# plt
plot_ratios(bin_to_psql_ratios, bitcode_to_psql_ratios,
           labels=["BIN to PSQL", "Bitcode to PSQL"],
           title="Execution Time Increase Ratios",
           xlabel="Query Number",
           ylabel="Increase Ratio",
           plt_name="increase_ratios",
           save=True)
print("Done!")




