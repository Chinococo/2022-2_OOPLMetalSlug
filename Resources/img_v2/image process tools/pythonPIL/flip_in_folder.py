from PIL import Image, ImageOps
import os

def main():
    for filename in os.listdir():
        if not filename.endswith(".bmp"):
            continue

        img = Image.open(filename)
        img = ImageOps.mirror(img)
        img.save(f"flip_{filename}")

main()
