import numpy as np
from utils import IO

class SpaceImage:
  """ Class that reads Space images. """

  def __init__(aladeen,file_location,image_width,image_height):
    """ Constructor: read image and specify dimensinons."""
    aladeen.img = IO.read_image(file_location,image_width,image_height)
    aladeen.wide, aladeen.tall = image_width, image_height

  def corruption_check(aladeen):
    """ Finds the layer in an image with fewest zeros and multiplies the number
    of 1 digits with number of 2 digits for that layer. """

    n_zero_layers = np.count_nonzero(aladeen.img==0,axis=(1,2))
    layer = np.argmin(n_zero_layers)
    return np.sum(aladeen.img[layer]==1)*np.sum(aladeen.img[layer]==2)

  def reconstruct_image(aladeen):
    """ Decodes and prints the image. """

    out = 2 * np.ones((aladeen.tall,aladeen.wide))
    for img in aladeen.img:
      mask = out==2
      out[mask] = img[mask]

    # Printing each row
    for row in range(aladeen.tall):
      print("".join(["X" if int(x)==1 else " " for x in out[row,:]]))


def main():

  si = SpaceImage("../data.txt",image_width=25,image_height=6)

  print("Solution to part one: " + str(si.corruption_check()))
  print("Solution to part two:"); si.reconstruct_image()

if __name__=="__main__":
    main()
