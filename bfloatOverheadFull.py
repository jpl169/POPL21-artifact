import matplotlib
import matplotlib.pyplot as plt
import numpy as np

labels = ["bfloat_ln(x)", "bfloat_log2(x)", "bfloat_log10(x)", "bfloat_exp(x)", "bfloat_exp2(x)", "bfloat_exp10(x)", "bfloat_sinpi(x)", "bfloat_cospi(x)", "bfloat_sqrt(x)", "bfloat_cbrt(x)", "average"]

ovhdFile = open("B16OvhdRslt.txt", "r")


bfloatAgainstFloat = [float(num) for num in ovhdFile.readline().split(" ")]
bfloatAgainstDouble = [float(num) for num in ovhdFile.readline().split(" ")]


x = np.arange(len(labels))  # the label locations
width = 0.35  # the width of the bars

fig, ax = plt.subplots()
ax.set_ylim(0, 2.5)
ax.axhline(0.5, color="gray", ls = '--', linewidth = 0.5, zorder = 0)
ax.axhline(1, color="gray", ls = '--', linewidth = 0.5, zorder = 0)
ax.axhline(1.5, color="gray", ls = '--', linewidth = 0.5, zorder = 0)
ax.axhline(2, color="gray", ls = '--', linewidth = 0.5, zorder = 0)
ax.axhline(2.5, color="gray", ls = '--', linewidth = 0.5, zorder = 0)
rects1 = ax.bar(x - width/2, bfloatAgainstFloat, width, label='Speedup over float libm', zorder = 100)
rects2 = ax.bar(x + width/2, bfloatAgainstDouble, width, label='Speedup over double libm', zorder = 100)

# Add some text for labels, title and custom x-axis tick labels, etc.
plt.xticks(rotation=25, ha="right", rotation_mode="anchor")
ax.set_ylabel('Speedup')
#ax.set_title('Performance speedup')
ax.set_xticks(x)
ax.set_xticklabels(labels)
ax.legend(bbox_to_anchor=(-0.12, 1.2, 1.17, 0.2), loc="lower left", mode="expand", ncol=2)


def autolabel(rects):
    """Attach a text label above each bar in *rects*, displaying its height."""
    for rect in rects:
        height = rect.get_height()
        if height > 2.5:
            ax.annotate('{:.1f}'.format(height),
                    xy=(rect.get_x() + rect.get_width() / 2, 2.5),
                    xytext=(0, 3),  # 3 points vertical offset
                    textcoords="offset points",
                    ha='center', va='bottom', rotation=90)

autolabel(rects1)
autolabel(rects2)


fig.tight_layout()

plt.gcf().set_size_inches(4.5, 2)
plt.savefig('bfloatOverheadFull.pdf', bbox_inches='tight', pad_inches = -0.001)
