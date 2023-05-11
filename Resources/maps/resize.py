from PIL import Image

# 打开图像文件
for i in range(1,9,1):
    image = Image.open(f"water_01_0{i}.bmp")

    # 调整图像大小
    width, height = image.size
    new_size = (2394, 132)
    resized_image = image.resize(new_size)

    # 保存调整后的图像
    resized_image.save(f"water_01_0{i}.bmp")
