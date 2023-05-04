from PIL import Image
import os
import sys

argc = len(sys.argv)

if argc == 1:
    scale = 1
else:
    scale = int(sys.argv[1])

ext_from = ".png"

for file in os.listdir():
    if os.path.isdir(file):
        continue

    ext = os.path.splitext(file)[-1]

    if ext == ".py" or ext != ext_from:
        continue

    img = Image.open(file)
    rgb_image = img.convert("RGB")
    width, height = rgb_image.size
    bmp_image = Image.new("RGB", (width * scale, height * scale), (255, 255, 255))
    bmp_image.paste(rgb_image)
    img.save(f'./{os.path.splitext(file)[0]}.bmp')