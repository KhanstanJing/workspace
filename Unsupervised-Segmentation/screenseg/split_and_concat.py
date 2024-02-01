from PIL import Image
import os

Image.MAX_IMAGE_PIXELS = 500000000

def split_and_save(input_folder, name, output_folder):
    input_path = os.path.join(input_folder, name)
    image = Image.open(input_path)

    # 切割图片并保存
    for i in range(16):
        for j in range(13):
            # 计算切割区域的位置
            left = j * 1260
            top = i * 1250
            right = left + 1260
            bottom = top + 1250

            # 切割图片
            miniimage = image.crop((left, top, right, bottom))

            # 生成保存路径和文件名
            mininame = f"({i},{j})"
            output_path = os.path.join(output_folder, mininame + '.jpg')

            # 保存图片
            miniimage.save(output_path)

def concat_and_save(input_folder, output_folder):
    width = 16380
    high = 20000
    result = Image.new('RGB', (width, high))

    # i应该是0到15共16行，j应该是0到12共13列
    for i in range(2,13):
        for j in range(6,13):

            filename = f"({i},{j}).jpg"
            input_path = os.path.join(input_folder, filename)

            try:
                img = Image.open(input_path)
            except FileNotFoundError:
                print(f"file '{filename}' not found")
                continue

            x_offset = j * 1260
            y_offset = i * 1250

            result.paste(img, (x_offset, y_offset))

    output_path = os.path.join(output_folder, "segmented.jpg")
    result.save(output_path)

