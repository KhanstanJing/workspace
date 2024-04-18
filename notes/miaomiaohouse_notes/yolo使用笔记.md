# 断点恢复

在exp2的时候epoch141时断掉了，可能是电脑被别人动过，总之正好可以试一下断点恢复。

先使用了命令行输入的方法：

命令行输入：

```
yolo train resume path\to\ckpt.pt
``` 

这个方法会继续训练，但是会新产生一个result文件夹，后续输出结果在result文件夹中，打开其中的.csv文件，可以看到输出是从141开始的，因此想看看能不能直接从之前的文件夹恢复。

分析原因参考了下面的代码：

Python：

```
from ultralytics import YOLO

model = YOLO('path\to\ckpt.pt')

results = model.train(resume=true)
```

python代码中，可以看到，model的.train()方法调用后赋给了results，因此

# 训练方法
