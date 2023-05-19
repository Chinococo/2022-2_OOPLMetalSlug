from PIL import Image, ImageOps
import os


def main():
    for filename in os.listdir():
        if not filename.endswith(".bmp"):
            continue
        img = Image.open(filename)
        img = ImageOps.flip(img)
        img.save(f"flip_{filename}")


if __name__ == "__main__":
    main()
