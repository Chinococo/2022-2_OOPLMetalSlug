"""
Convert all .png files into .bmp
and merge body and leg into figure.
"""


from PIL import Image
import os


def convert_scale_to_bmp():
    ########################################
    # adjustable variables
    ext_from = "png"
    scale = 1
    ########################################

    for d in os.listdir():
        img_name, ext = os.path.splitext(d)
        if os.path.isfile(d) and ext.endswith(ext_from):
            img = Image.open(d)
            img.save(f"./{img_name}.bmp")


def merge_figure():
    ########################################
    # adjustable variables
    file_prefix = "idle"
    body_frames = 4
    leg_frame = 4
    leg_crop_tweak_top = 16
    leg_crop_tweak_bottom = -2
    body_leg_margin = -8
    background_rgb = (153, 217, 234)
    ########################################

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

    # open all images of body in frames, and leg
    body_imgs = [Image.open(f"{file_prefix}_{i}.bmp") for i in range(body_frames)]
    leg_img = Image.open(f"{file_prefix}_{leg_frame}.bmp")

    # crop out upper background
    leg_img = leg_img.crop((0, leg_crop_tweak_top, leg_img.width, leg_img.height + leg_crop_tweak_bottom))

    # overlay cropped leg image on every body image in frames
    figure_imgs = []
    for body_img in body_imgs:
        figure_img = Image.new("RGBA", (leg_img.width, body_img.height + leg_img.height + body_leg_margin), background_rgb)

        # resize canvas of body image
        body_extend = Image.new("RGBA", figure_img.size, background_rgb)
        body_extend.paste(body_img, (0, 0))

        # resize canvas of leg image
        leg_extend = Image.new("RGBA", figure_img.size, background_rgb)
        leg_extend.paste(leg_img, (0, body_img.height + body_leg_margin))

        # merge body and leg into figure
        body_extend = make_rgba_background_transparent(body_extend, background_rgb)
        leg_extend = make_rgba_background_transparent(leg_extend, background_rgb)
        figure_img = Image.alpha_composite(figure_img, leg_extend)
        figure_img = Image.alpha_composite(figure_img, body_extend)

        figure_imgs.append(figure_img)

    for i, figure_img in enumerate(figure_imgs):
        figure_img.save(f"{file_prefix}_{i}.bmp")


def main():
    convert_scale_to_bmp()
    merge_figure()


if __name__ == "__main__":
    main()