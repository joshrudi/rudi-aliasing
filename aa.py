import numpy as np
import cv2

# background info: Since colors do not scale linearly as with is the case for intensity (think greyscale) we are in a bit of a pickle.
# The good news is that some really smart people figured this out a long time ago with something called the L*a*b colorspace.
# It essentially allows us to linearly average out colors so they appear as they do to the human eye and not to computers (yay!)
# Also, there is a 3D "cube" method I ran into but haven't attempted using.  I'll link both of these below:
# https://en.wikipedia.org/wiki/CIELAB_color_space
# http://www.hugi.scene.org/online/coding/hugi%2013%20-%20coantia2.htm

# performs basic weighted AA
def antialias(im):

    # making a copy because of how referencing works in python
    aa = im.copy()
    
    # iterate through x and y values, as well as the L*a*b values (c for color)
    for y in range(1, len(im)-1):

        for x in range(1, len(im[x])-1):

            for c in range(0, 3):
            
                # Amazing formula.  Its really simple too, we just take the average between the (avg of surrounding pixels) & our current pixel
                aa[y][x][c] = 1/2 * (int(im[y][x][c]) + 1/4 * (int(im[y+1][x][c]) + int(im[y-1][x][c]) + int(im[y][x+1][c]) + int(im[y][x-1][c])))
    
    return aa


# read image as rgb array
im = cv2.imread('src_img/600p.png')

# convert to Lab colorspace
im = cv2.cvtColor(im, cv2.COLOR_RGB2Lab)

# perform 2xAA
for i in range(2):
    im = antialias(im)

# convert back to RGB colorspace
im = cv2.cvtColor(im, cv2.COLOR_Lab2RGB)

# save AA image
cv2.imwrite('processed_img/600pAA.png', im)