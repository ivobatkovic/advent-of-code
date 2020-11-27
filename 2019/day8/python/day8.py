import numpy as np
from utils import IO
import time
class SpaceImage:
  """ Class that reads Space images. """

  def __init__(self,file_location,image_width,image_height):
    """ Constructor: read image and specify dimensinons."""
    self.img = IO.read_image(file_location,image_width,image_height)
    self.wide, self.tall = image_width, image_height

  def corruption_check(self):
    """ Finds the layer in an image with fewest zeros and multiplies the number
    of 1 digits with number of 2 digits for that layer. """

    n_zero_layers = np.count_nonzero(self.img==0,axis=(1,2))
    layer = np.argmin(n_zero_layers)
    return np.sum(self.img[layer]==1)*np.sum(self.img[layer]==2)

  def reconstruct_image(self):
    """ Decodes and prints the image. """

    out = 2 * np.ones((self.tall,self.wide))
    for img in self.img:
      mask = out==2
      out[mask] = img[mask]

    # Printing each row
    for row in range(self.tall):
      print("".join(["X" if int(x)==1 else " " for x in out[row,:]]))


def main():

  si = SpaceImage("../data/input.txt",image_width=25,image_height=6)

  # Solve puzzle
  t0 = time.time()
  part_one = si.corruption_check()
  time_part_one = round((time.time()-t0)*1e3)
  print("Solution to part one: %s (time taken %s[ms])" % (
      part_one, time_part_one))
  
  print("Solution to part two:")
  t0 = time.time()
  si.reconstruct_image()
  time_part_two = round((time.time()-t0)*1e3)
  print( "(time taken %s[ms])" % (time_part_two))


if __name__=="__main__":
    main()
