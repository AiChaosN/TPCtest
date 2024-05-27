import matplotlib.pyplot as plt
import numpy as np
from matplotlib.backends.backend_pdf import PdfPages

def extract_times(file_path):
    times = [-1] * 22  # Initialize all times to -1
    with open(file_path, 'r') as file:
        for line in file:
            if "exe time:" in line:
                parts = line.split()
                query_part = parts[0].split('/')[-1]  # Handle ../bin/qX and qX formats
                query_num = int(''.join(filter(str.isdigit, query_part)))
                time = float(parts[-2])
                times[query_num - 1] = time
            elif "Execution Time:" in line:
                parts = line.split()
                query_num = int(parts[0].lstrip("query").rstrip(":"))
                time = float(parts[-2])
                times[query_num - 1] = time
    return times

# 彩色图
# def plot_graphs(a, b, c, exclude_queries, bar_output_path, scatter_output_path):
#     queries = np.arange(1, 23)
#     query_names = [f'q{i}' for i in range(1, 23)]
    
#     # Filter out queries where any of the values is -1 or in the exclude list
#     valid_indices = [i for i in range(len(a)) if a[i] != -1 and b[i] != -1 and c[i] != -1 and (i+1) not in exclude_queries]
    
#     queries = queries[valid_indices]
#     query_names = [query_names[i] for i in valid_indices]
#     a = [a[i] for i in valid_indices]
#     b = [b[i] for i in valid_indices]
#     c = [c[i] for i in valid_indices]
    
#     # Bar Chart
#     plt.figure(figsize=(12, 8))
#     width = 0.2
#     plt.bar(np.arange(len(queries)) - width, a, width=width, label='exe time')
#     plt.bar(np.arange(len(queries)), b, width=width, label='jit time')
#     plt.bar(np.arange(len(queries)) + width, c, width=width, label='psql time')
#     plt.xlabel('Query')
#     plt.ylabel('Time (ms)')
#     plt.yscale('log')
#     plt.xticks(np.arange(len(queries)), query_names)
#     plt.yticks([10**i for i in range(0, int(np.ceil(np.log10(max(max(a), max(b), max(c))))) + 1)])
#     plt.title('Execution Times by Query')
#     plt.legend()
#     plt.savefig(bar_output_path)
#     plt.close()
    
#     # Scatter Plot
#     plt.figure(figsize=(12, 8))
#     ratio_a_c = np.array(a) / np.array(c)
#     ratio_b_c = np.array(b) / np.array(c)
#     plt.scatter(np.arange(len(queries)), ratio_a_c, color='blue', label='exe/psql')
#     plt.scatter(np.arange(len(queries)), ratio_b_c, color='red', label='jit/psql')
#     plt.xlabel('Query')
#     plt.ylabel('Ratio')
#     plt.yscale('log')
#     plt.xticks(np.arange(len(queries)), query_names)
#     plt.yticks([10**i for i in range(-1, int(np.ceil(np.log10(max(max(ratio_a_c), max(ratio_b_c))))) + 1)])
#     plt.title('Ratios of Execution Times (exe/c and jit/c)')
#     plt.legend()
#     plt.savefig(scatter_output_path)
#     plt.close()

# 黑白
def plot_graphs(a, b, c, exclude_queries, bar_output_path, scatter_output_path):
    queries = np.arange(1, 23)
    query_names = [f'q{i}' for i in range(1, 23)]
    
    # Filter out queries where any of the values is -1 or in the exclude list
    valid_indices = [i for i in range(len(a)) if a[i] != -1 and b[i] != -1 and c[i] != -1 and (i+1) not in exclude_queries]
    
    queries = queries[valid_indices]
    query_names = [query_names[i] for i in valid_indices]
    a = [a[i] for i in valid_indices]
    b = [b[i] for i in valid_indices]
    c = [c[i] for i in valid_indices]
    
    with PdfPages(bar_output_path) as pdf:
        # Bar Chart
        plt.figure(figsize=(12, 8))
        width = 0.2
        plt.bar(np.arange(len(queries)) - width, a, width=width, color='black', label='exe time')
        plt.bar(np.arange(len(queries)), b, width=width, color='grey', label='jit time')
        plt.bar(np.arange(len(queries)) + width, c, width=width, color='lightgrey', label='psql time')
        plt.xlabel('Query')
        plt.ylabel('Time (ms)')
        plt.yscale('log')
        plt.xticks(np.arange(len(queries)), query_names)
        plt.yticks([10**i for i in range(0, int(np.ceil(np.log10(max(max(a), max(b), max(c))))) + 1)])
        plt.title('Execution Times by Query')
        plt.legend()
        pdf.savefig()
        plt.close()

    with PdfPages(scatter_output_path) as pdf:
        # Scatter Plot
        plt.figure(figsize=(12, 8))
        ratio_a_c = np.array(a) / np.array(c)
        ratio_b_c = np.array(b) / np.array(c)
        plt.scatter(np.arange(len(queries)), ratio_a_c, color='black', label='exe/psql')
        plt.scatter(np.arange(len(queries)), ratio_b_c, color='grey', label='jit/psql')
        plt.xlabel('Query')
        plt.ylabel('Ratio')
        plt.yscale('log')
        plt.xticks(np.arange(len(queries)), query_names)
        plt.yticks([10**i for i in range(-1, int(np.ceil(np.log10(max(max(ratio_a_c), max(ratio_b_c))))) + 1)])
        plt.title('Ratios of Execution Times (exe/c and jit/c)')
        plt.legend()
        pdf.savefig()
        plt.close()
        
sizes = ['0.01G', '0.1G', '1G']
psql_sizes = ['001g', '01g', '1g']
exclude_queries = [2, 5, 7, 8, 9, 10, 19]

for i in range(len(sizes)):
    file_a = f"../src/execution_times_{sizes[i]}.txt"
    file_b = f"../src/jit_execution_times_{sizes[i]}.txt"
    file_c = f"../test/tpch_{psql_sizes[i]}_time.txt"
    
    times_a = extract_times(file_a)
    times_b = extract_times(file_b)
    times_c = extract_times(file_c)
    
    plot_graphs(
        times_a, times_b, times_c, exclude_queries,
        bar_output_path=f'bar_chart_{psql_sizes[i]}.png',
        scatter_output_path=f'scatter_plot_{psql_sizes[i]}.png'
    )
