from PIL import Image

# 打开图像文件
image = Image.open("background3.bmp")

# 调整图像大小
width, height = image.size
new_size = (int(width * 1.0), int(height * 1.1))
resized_image = image.resize(new_size)

# 保存调整后的图像
resized_image.save("background3.bmp")
