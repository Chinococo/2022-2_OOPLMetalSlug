from PIL import Image
import os
import sys


def resize_all(scale):
    files = os.listdir()
    print(f"files: {files}")

    for f in files:
        if os.path.isdir(f):
            print(f"{f}: dir, passed.")
            continue

        name, ext = os.path.splitext(f)

        supported_exts = {".bmp"}
        if ext not in supported_exts:
            print(f"{f}: not {supported_exts} file, passed.")
            continue

        im = Image.open(f)
        print(f"processing {f}, size={im.size}... ", end="")
        new_width = round(im.width * scale)
        new_height = round(im.height * scale)
        im = im.resize((new_width, new_height))
        im.save(f)
        print("done.")


def main():
    # scale = float(sys.argv[1]) if len(sys.argv) > 1 else 1
    resize_all(2.2)


if __name__ == "__main__":
    main()
