from pong import Pong

def main():
  pong = Pong("../input.csv")
  print("Solution to part one: " + str(pong.render_map()))

  pong = Pong("../input.csv",play=True)
  pong.play()


if __name__=="__main__":
  main()
