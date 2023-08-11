from PIL import Image

# img = Image.new( 'RGB', (255,255), "black") # Create a new black image
# pixels = img.load() # Create the pixel map
# for i in range(img.size[0]):    # For every pixel:
#     for j in range(img.size[1]):
#         pixels[i,j] = (i, j, 100) # Set the colour accordingly

# img.show()

block_size = 24

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

width = block_size
height = block_size
img = Image.new('RGB', (width, height))
pixels = img.load()
for i in range(block_size):
    for j in range(block_size):
        if i == 0 or i == block_size - 1 or j == 0 or j == block_size - 1:
        	pixels[i,j] = (0xff, 0xff, 0xff)
        else:
        	pixels[i,j] = (0xff, 0x00, 0x00)

img.show()
