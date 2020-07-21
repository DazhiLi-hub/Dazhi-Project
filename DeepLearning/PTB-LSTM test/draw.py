import json
import matplotlib.pyplot as plt
with open("./result.json") as f:
    results = json.load(f)
x_axis=[]
y_axis=[]
for k,v in results.items():
    x_axis.append(k)
    y_axis.append(v)
plt.title("Training Status")
plt.plot(x_axis, y_axis, color="r", linestyle="-", linewidth=1.0)
plt.xlabel("Training Batches")
plt.ylabel("Perplexity")
plt.show()