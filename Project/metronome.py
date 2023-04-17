import time
 
def main(bpm = 120, bpb = 4):
   sleep = 60.0 / bpm
   counter = 0
   while True:
      counter += 1
      number1 = counter / 3
      if counter % bpb:
         print('tick')
      if number1:
         print('1')
      else:
         print('TICK')
      time.sleep(sleep)
 
 
main()
