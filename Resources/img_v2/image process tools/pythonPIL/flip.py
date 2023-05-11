from PIL import Image
import os
import sys


def resize_all(path=os.path.abspath(os.getcwd())):
    files = os.listdir(path=path)
    print(f"files: {files}")

    for f in files:
        if os.path.isdir(f):
            print(f"{f}: dir, passed.")
            resize_all( path=path + '/' + f)
            continue

        name, ext = os.path.splitext(path + '/' + f)

        supported_exts = {".bmp"}
        print(path + '/' + f)
        if ext not in supported_exts:
            print(f"{f}: not {supported_exts} file, passed.")
            continue
        print(path + '/' + f)
        im = Image.open(path + '/' + f)
        print(f"processing {f}, size={im.size}... ", end="")
        im = im.transpose(Image.FLIP_LEFT_RIGHT)
        im.save(path + '/' + 'flip_'+f)
        print("done.")


def main():
    # scale = float(sys.argv[1]) if len(sys.argv) > 1 else 1
    resize_all()


if __name__ == "__main__":
    main()
