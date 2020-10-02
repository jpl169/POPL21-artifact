import matplotlib
import matplotlib.pyplot as plt
import numpy as np

labels = ["posit_ln(x)", "posit_log2(x)", "posit_sinpi(x)", "posit_cospi(x)", "posit_sqrt(x)", "average"]

ovhdFile = open("P16OvhdRslt.txt", "r")

positAgainstspm = [float(num) for num in ovhdFile.readline().split(" ")]

x = np.arange(len(labels))  # the label locations
width = 0.35  # the width of the bars

fig, ax = plt.subplots()
ax.set_ylim(0, 1.5)
ax.axhline(0.5, color="gray", ls = '--', linewidth = 0.5, zorder = 0)
ax.axhline(1, color="gray", ls = '--', linewidth = 0.5, zorder = 0)
ax.axhline(1.5, color="gray", ls = '--', linewidth = 0.5, zorder = 0)
ax.axhline(2, color="gray", ls = '--', linewidth = 0.5, zorder = 0)
ax.axhline(2.5, color="gray", ls = '--', linewidth = 0.5, zorder = 0)
rects1 = ax.bar(x - width/2, positAgainstspm, width, zorder = 100)

# Add some text for labels, title and custom x-axis tick labels, etc.
plt.xticks(rotation=25, ha="right", rotation_mode="anchor")
ax.set_ylabel('Speedup')
#ax.set_title('Performance speedup')
ax.set_xticks(x)
ax.set_xticklabels(labels)


def autolabel(rects):
    """Attach a text label above each bar in *rects*, displaying its height."""
    for rect in rects:
        height = rect.get_height()
        if height == 0.0:
            ax.annotate('N/A'.format(height),
                    xy=(rect.get_x() + rect.get_width() / 2, 0.08),
                    xytext=(5, 3),  # 3 points vertical offset
                    textcoords="offset points",
                    ha='center', va='bottom')

autolabel(rects1)


fig.tight_layout()

plt.gcf().set_size_inches(4.5, 1.3)
plt.savefig('positOverheadInternal.pdf', bbox_inches='tight', pad_inches = -0.001)
