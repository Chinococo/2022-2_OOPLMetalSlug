from PIL import Image

# 打开图像文件
image = Image.open("miniboss1_01.bmp")

# 调整图像大小
width, height = image.size
#new_size = (464,582)
new_size = (int(width * 3), int(height * 3))
resized_image = image.resize(new_size)

# 保存调整后的图像
resized_image.save("miniboss1_01.bmp")
