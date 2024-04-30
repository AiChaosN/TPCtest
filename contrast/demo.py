import re  # 导入正则表达式模块
import matplotlib.pyplot as plt

def read_execution_times(file_path):
    times = [0.0] * 22
    with open(file_path, 'r') as file:
        for line in file:
            if "exe time" in line or "Execution Time" in line:

                match = re.search(r'(\d+)', line)
                if match:
                    query_number = int(match.group(1))
                    time = float(line.split()[-2]) 
                    if query_number <= 22:
                        times[query_number - 1] = time 
    return times


def calculate_increase_ratios(list1, list2):
    ratios = []
    for value1, value2 in zip(list1, list2):
        if value1 == 0 or value2 == 0:
            ratios.append(0.0) 
        else:
            increase = (value2 - value1) / value1 
            increase = round(increase, 2) 
            ratios.append(increase)
    return ratios

def plot_lists(data_lists, labels=None, title="Multi-Line Plot", xlabel="X-axis", ylabel="Y-axis"):

    for i, data in enumerate(data_lists):
        if labels and len(labels) == len(data_lists):
            plt.plot(data, label=labels[i])
        else:
            plt.plot(data, label=f"Line {i+1}")
    
    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    if labels:
        plt.legend()
    plt.grid(True)
    plt.show()



# open
bin_times = read_execution_times('../bin/execution_times.txt')
bitcode_times = read_execution_times('../bitcode/execution_times.txt')
psql_times = read_execution_times('../test/sql_ans/psql_time.txt')

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

# per average
per_bin_to_psql_ratios = (sum(bin_to_psql_ratios)-bin_to_psql_ratios[19]) / (len(bin_to_psql_ratios)-3)
per_bitcode_to_psql_ratios = (sum(bitcode_to_psql_ratios)-bitcode_to_psql_ratios[19]) / (len(bitcode_to_psql_ratios)-3)
print("\nAverage Increase Ratios:")
print("BIN to PSQL:", per_bin_to_psql_ratios)
print("Bitcode to PSQL:", per_bitcode_to_psql_ratios)

# plt
plot_lists([bin_to_psql_ratios, bitcode_to_psql_ratios], 
           labels=["BIN to PSQL", "Bitcode to PSQL"],
           title="Execution Time Increase Ratios",
           xlabel="Query Number",
           ylabel="Increase Ratio")

print("Done!")




