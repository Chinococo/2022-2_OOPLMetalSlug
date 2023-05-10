from PIL import Image

# 打开图像文件
image = Image.open("enemy_platform_1_broken.bmp")

# 调整图像大小
width, height = image.size
new_size = (width * 2, height * 2)
resized_image = image.resize(new_size)

# 保存调整后的图像
resized_image.save("enemy_platform_1_broken.bmp")
