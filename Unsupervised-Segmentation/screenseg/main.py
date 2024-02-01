import os.path

from split_and_concat import split_and_save
from split_and_concat import concat_and_save
from segmentation import seg

import time

raw_image = r"C:\Unsupervised-Segmentation\screenseg\raw_image\2023-11-10-09-24-03"
folder_name = os.path.basename(raw_image)
pre0 = "original-0-"
pre1 = "original-1-"
preprocessed_image = r"C:\Unsupervised-Segmentation\screenseg\preprocessed_image"
processed_image = r"C:\Unsupervised-Segmentation\screenseg\processed_image"
segmented_image = r"C:\Unsupervised-Segmentation\screenseg\segmented_image"

start_time = time.time()

split_and_save(raw_image, pre0+folder_name+".jpg", preprocessed_image)

end_time1 = time.time()
print("split completed, cost time", end_time1 - start_time)

for i in range(2, 13):
    for j in range(6, 13):
        name = f"({i},{j}).jpg"
        start_time2 = time.time()
        seg(preprocessed_image, name, processed_image)
        end_time2 = time.time()
        print(f"miniimage({i},{j}) is segmented, cost time", end_time2 - start_time2)

start_time3 = time.time()
concat_and_save(processed_image, segmented_image)
end_time3 = time.time()