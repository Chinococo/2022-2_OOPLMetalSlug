from PIL import Image, ImageOps
import os


def to_black_background(image: Image, background_color: tuple) -> Image:
    data = []
    for item in image.getdata():
        if item[:3] == background_color:
            data.append((0, 0, 0, 255))
        else:
            data.append(item)
    image.putdata(data)
    return image


def resize_canvas_and_scale(image: Image, canvas_size: tuple) -> Image:
    canvas = Image.new("RGB", canvas_size, (0, 0, 0))
    
    ratio = min(canvas.width / image.width, canvas.height / image.height)
    new_width = int(image.width * ratio)
    new_height = int(image.height * ratio)
    image = image.resize((new_width, new_height))

    pos_width = (canvas.width - image.width) // 2
    pos_height = (canvas.height - image.height) // 2
    canvas.paste(image, (pos_width, pos_height))
    return canvas


def process_image(background_color, canvas_size):
    for file in os.listdir():
        name, ext = os.path.splitext(file)

        if ext != ".png":
            continue

        print(f"processing {file}... ", end="")

        try:
            image = Image.open(file)
            
            image.convert("RGB")
            
            image = to_black_background(image, background_color)
            image = resize_canvas_and_scale(image, canvas_size)
            
            image.save(f"{name}.bmp", "BMP")

            image = ImageOps.mirror(image)
            image.save(f"flip_{name}.bmp", "BMP")

            print("done")

        except Exception as e:
            print(f"failed: {e}")


if __name__ == "__main__":
    #background_color = (153, 217, 234) # marco
    background_color = (86, 177, 222) # soldier
    canvas_size = (90, 90)
    process_image(background_color, canvas_size)
