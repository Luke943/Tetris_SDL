from PIL import Image, ImageColor

# img = Image.new( 'RGB', (255,255), "black") # Create a new black image
# pixels = img.load() # Create the pixel map
# for i in range(img.size[0]):    # For every pixel:
#     for j in range(img.size[1]):
#         pixels[i,j] = (i, j, 100) # Set the colour accordingly

# img.show()

block_size = 16
colours = [
    ImageColor.getrgb("cyan"),
    ImageColor.getrgb("red"),
    ImageColor.getrgb("green"),
    ImageColor.getrgb("yellow"),
    ImageColor.getrgb("purple"),
    ImageColor.getrgb("orange"),
    ImageColor.getrgb("blue"),
    ImageColor.getrgb("white"),
    ImageColor.getrgb("gray"),
]

# # Border
# width = block_size * 12
# height = block_size * 21
# img = Image.new('RGB', (width, height))
# pixels = img.load()
# for i in range(block_size):
#     for j in range(height):
#         pixels[i,j] = (0x88, 0x88, 0x88)
# for i in range(width - block_size, width):
#     for j in range(height):
#         pixels[i,j] = (0x88, 0x88, 0x88)
# for i in range(width):
#     for j in range(height - block_size, height):
#         pixels[i,j] = (0x88, 0x88, 0x88)

# img.show()

# img.save("playfieldborder.bmp")

# Red block

width = block_size * len(colours)
height = block_size
img = Image.new("RGB", (width, height))
pixels = img.load()
for k, colour in enumerate(colours):
    for i in range(block_size):
        for j in range(block_size):
            if i == 0 or i == block_size - 1 or j == 0 or j == block_size - 1:
                pixels[k * block_size + i, j] = ImageColor.getrgb("white")
            else:
                pixels[k * block_size + i, j] = colour

img.show()

img.save("blocks.bmp")
