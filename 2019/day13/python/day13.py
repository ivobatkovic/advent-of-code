from pong import Pong
import time
def main():

  # Part one
  t0 = time.time()
  pong = Pong("../data/input.csv")
  part_one = pong.render_map()
  time_part_one = round((time.time()-t0)*1e3)
  print("Solution to part one: %s (time taken %s[ms])" % (
      part_one, time_part_one))

  t0 = time.time()
  pong = Pong("../data/input.csv", play=True)
  part_two = pong.play()
  time_part_one = round((time.time()-t0)*1e3)
  print("Solution to part one: %s (time taken %s[ms])" % (
      part_two, time_part_one))



if __name__=="__main__":
  main()
