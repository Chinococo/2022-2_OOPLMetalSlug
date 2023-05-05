from PIL import Image
import os

num_key_frames = 8

for image_name in os.listdir():
    if os.path.isfile(image_name) and os.path.splitext(image_name)[1].endswith("gif"):
        with Image.open(image_name) as img:
            for i in range(num_key_frames):
                img.seek(img.n_frames // num_key_frames * i)
                img.save('{}.bmp'.format(i))