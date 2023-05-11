from PIL import Image
import os
import sys


def get_scale() -> float:
    argc = len(sys.argv)
    scale = float(sys.argv[1]) if argc > 1 else 1
    return scale


def main() -> None:
    scale = get_scale()
    print(f"scale = {scale}")

    for filename in os.listdir():
        print(f"{filename}: checking...", end="")

        if not filename.endswith(".bmp"):
            print("not bmp, skipped")
            continue

        print("bmp, processing...", end="")

        img = Image.open(filename)
        img = img.resize((int(img.width*scale), int(img.height*scale)))
        img.save(filename)

        print(f"done, new size = ({img.width}, {img.height})")
        img.close()


if __name__ == "__main__":
    main()
