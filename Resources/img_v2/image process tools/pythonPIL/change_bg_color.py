from PIL import Image
import os

def make_rgba_background_transparent(img, background_rgb):
        new_data = []
        for item in img.getdata():
            if item[:3] == background_rgb:
                new_data.append((255, 255, 255, 0))
            else:
                new_data.append(item)
        new_image = Image.new("RGBA", img.size)
        new_image.putdata(new_data)
        return new_image

def main():
    print(os.listdir())
    for f in os.listdir():
        name, ext = os.path.splitext(f)
        
        if os.path.isdir(f) or ext != ".bmp":
            continue
        
        print(f"processing {f}")
        im = Image.open(f)
        bg_from = (153, 217, 234)
        im = make_rgba_background_transparent(im, bg_from)
        
        bg_black = (0, 0, 0)
        im_new = Image.new("RGBA", im.size, bg_black)
        im_new = Image.alpha_composite(im_new, im)
        im_new.save(f)

main()