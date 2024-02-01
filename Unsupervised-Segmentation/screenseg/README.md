# filefolder: rawimage
存放了待分割的图像

每一张图像的大小为16380*20000

# filefolder: preprocessedimage
存放了将rawimage中待分割图像预处理后的图像

rawimage中的每一张图像被分割成13*16个小块后被放在这里

每个小块的大小为1260*1250

# filefolder: processedimage
存放了将preprocessedimage中的每一个小块进行图像分割后全部小块

# filefolder: segmentedimage
存放了将processedimage中的小块拼起来之后的分割好的图片

# file: myRAGthresholding.py
该文件对小块进行操作，将每一个小块进行图像分割
即对于文件夹preprocessedimage中的图像进行分割而后保存到文件夹processedimage中
