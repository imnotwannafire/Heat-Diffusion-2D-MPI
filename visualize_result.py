import numpy as np
import matplotlib.pyplot as plt

# Đọc dữ liệu từ tệp result.txt
data = []
with open('result.txt', 'r') as file:
    for line in file:
        values = line.split('\t')
        try:
            row = [float(value) for value in values if value.strip() != '']
            data.append(row)
        except ValueError:
            # Loại trừ giá trị không hợp lệ
            pass
data = np.array(data)

# Tạo lưới cho biểu đồ
m, n = data.shape
x = np.linspace(0, n-1, n)
y = np.linspace(0, m-1, m)
X, Y = np.meshgrid(x, y)

# Biểu diễn nhiệt độ bằng một biểu đồ màu
plt.figure(figsize=(10, 6))
plt.pcolormesh(X, Y, data, cmap='hot', shading='auto')
plt.colorbar(label='Temperature')
plt.title('Heat Distribution')
plt.xlabel('X')
plt.ylabel('Y')
plt.show()
