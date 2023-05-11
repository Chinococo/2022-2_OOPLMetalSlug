from PIL import Image
import os

# Set the directory path where your images are located
directory = "/path/to/your/images"

# Set the desired size for the BMP images
width = 800
height = 600

# Set the background color for the BMP images
background_color = (0, 0, 0)

# Loop through each file and subdirectory in the directory
for root, dirs, files in os.walk(directory):
    for filename in files:
        # Check if the file is an image
        if filename.endswith(".png") or filename.endswith(".jpg") or filename.endswith(".jpeg"):
            # Open the image
            img = Image.open(os.path.join(root, filename))
            # Convert the image to BMP format
            img = img.convert("RGB")
            # Resize the image while centering the contents
            img_width, img_height = img.size
            if img_width > width or img_height > height:
                ratio = min(width / img_width, height / img_height)
                new_width = int(img_width * ratio)
                new_height = int(img_height * ratio)
                img = img.resize((new_width, new_height), resample=Image.LANCZOS)
            bg = Image.new("RGB", (width, height), background_color)
            x_offset = int((width - img.width) / 2)
            y_offset = int((height - img.height) / 2)
            bg.paste(img, (x_offset, y_offset))
            # Save the image in BMP format
            bmp_filename = os.path.splitext(filename)[0] + ".bmp"
            bg.save(os.path.join(root, bmp_filename), "BMP")
