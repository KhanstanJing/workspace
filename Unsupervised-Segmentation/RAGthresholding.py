from skimage import data, segmentation, color, io
from skimage import graph
from matplotlib import pyplot as plt
import time


#img = data.coffee()
# 读取我的图像
# img= io.imread('mytryimage/woof.jpg', as_gray=True)
starttime = time.time()
img= io.imread('mytryimage/边界左中1280.jpg')

# slic将图片划分为区域，其中compactness越大形状越规则，n_segments越大每个区域越小
labels1 = segmentation.slic(img, compactness=240, n_segments=120, start_label=1)
# 上面生成了标签图像，该标签将图片划分成不同的区域，每个区域都有对应的编号，下面的代码将标签映射到图像上，取得是每个区域的平均值
out1 = color.label2rgb(labels1, img, kind='avg', bg_label=0)

endtime1 = time.time()

runtime1 = endtime1 - starttime

g = graph.rag_mean_color(img, labels1)
labels2 = graph.cut_threshold(labels1, g, 29)
out2 = color.label2rgb(labels2, img, kind='avg', bg_label=0)

endtime2 = time.time()

runtime2 = endtime2 - starttime

fig, ax = plt.subplots(nrows=4, sharex=True, sharey=True, figsize=(6, 8))

print("endtime1 = ", runtime1, "endtime2 = ", runtime2)

ax[0].imshow(out1)
ax[1].imshow(out2)
# ax[2].imshow(labels1)
# ax[3].imshow(labels2)

for a in ax:
    a.axis('off')

plt.tight_layout()
#plt.show()