from PIL import Image
import os


def scale_bmp(img: Image, scale: float) -> Image:
    print(f"scale = {scale}")

    img = img.resize((int(img.width*scale), int(img.height*scale)))

    print(f"done, new size = ({img.width}, {img.height})")
    return img


def main() -> None:
    max_width = 90
    max_height = 90

    for filename in os.listdir():
        print(f"{filename}: checking...", end="")

        if not filename.endswith(".bmp"):
            print("not bmp, skipped")
            continue

        print("bmp, processing...", end="")

        img = Image.open(filename)

        ratio = min(max_width/img.width, max_height/img.height)

        img = img.resize((int(img.width*ratio), int(img.height*ratio)))
        bg = Image.new("RGB", (max_width, max_height), (0, 0, 0))
        bg.paste(img, (int((bg.width-img.width)/2), int((bg.height-img.height)/2)))
        bg.save(filename)

        print(f"done, new size = ({bg.width}, {bg.height})")
        img.close()
        bg.close()


if __name__ == "__main__":
    main()
