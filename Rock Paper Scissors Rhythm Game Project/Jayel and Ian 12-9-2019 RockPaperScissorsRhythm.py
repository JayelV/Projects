### Rock Paper Scissors Rhythm

import tkinter as tk
from tkinter import ttk
from tkinter import PhotoImage
import random
from tkinter import messagebox
from winsound import Beep

__authors__ = "Jayel Versoza, Ian Sherrer"
__date__ = "11 December 2019"

def main():
   program = RPSR()
   program.win.mainloop()
   

class RPSR: ### class for the basic RPSR game
   STATUS_BACKGROUND = "white"
   
   def __init__(self):
      self.win = tk.Tk()
      self.win.title("Rock Paper Scissors Rhythm")

      self.game_frame, self.status_frame = self.create_frames()

      self.game_is_running = False
      self.bpm = 0
      self.count = 0
      self.beat = 4
      self.time = 0

      self.rock_photo = PhotoImage(file="rock.png")
      self.paper_photo = PhotoImage(file="paper.png")
      self.scissors_photo = PhotoImage(file="scissors.png")
      self.win_photo = PhotoImage(file="checkmark.png")
      self.lose_photo = PhotoImage(file="x.png")

      self.var = tk.StringVar()
      self.var.set(self.count)

      self.rock_label, self.paper_label, self.scissors_label = self.create_hands()

      self.label_count = self.create_countdown()

      self.userChoice = self.set_callbacks()

      self.keyA_label, self.keyS_label, self.keyD_label, self.point_counter, self.start_button, self.quit_button = self.create_status_widgets()
      self.set_callbacks()
      
   def create_frames(self):
      game_frame = tk.Frame(self.win, width=600, height=600, bg=RPSR.STATUS_BACKGROUND)
      game_frame.grid(row=0, column=0)

      status_frame = tk.Frame(self.win, width=150, height=600)
      status_frame.grid(row=0, column=1, sticky=tk.E + tk.W + tk.N + tk.S, ipadx=6)
      
      return game_frame, status_frame
      
   def create_hands(self):
      #Placement of hand pictures.
      #The "rock" state will also be the rest state.

      scissors_label = tk.Label(self.game_frame, image=self.scissors_photo)
      scissors_label.grid(row=0, column=0, sticky=tk.N + tk.E + tk.W)

      paper_label = tk.Label(self.game_frame, image=self.paper_photo)
      paper_label.grid(row=0, column=0, sticky=tk.N + tk.E + tk.W)
            
      rock_label = tk.Label(self.game_frame, image=self.rock_photo)
      rock_label.grid(row=0, column=0, sticky=tk.N + tk.E + tk.W)

      return rock_label, paper_label, scissors_label

   def create_countdown(self):
      label_count = tk.Label(self.game_frame, textvariable=self.var, font=("Arial", 65), bg=RPSR.STATUS_BACKGROUND)
      label_count.grid(row=1, column=0, columnspan=2)

      return label_count
      
   def create_status_widgets(self):
      #Labels. Shows the score: number of wins, number of losses, number
      #of draws, etc.

      keyA_label = tk.Label(self.status_frame, text="a -> ROCK", font=("Arial", 15))
      keyA_label.pack(side="top", fill=tk.Y)

      keyS_label = tk.Label(self.status_frame, text="s -> PAPER", font=("Arial", 15))                     
      keyS_label.pack(side="top", fill=tk.Y)

      keyD_label = tk.Label(self.status_frame, text="d -> SCISSORS", font=("Arial", 15))
      keyD_label.pack(side="top", fill=tk.Y)

      spacer = tk.Label(self.status_frame, text="")
      spacer.pack(side="top", fill=tk.Y, expand=True)

      point_label = tk.Label(self.status_frame, text="Points:", font=("Arial", 15))
      point_label.pack(side="top", fill=tk.Y, expand=True)

      point_counter = tk.Label(self.status_frame, text="0", font=("Arial", 15))
      point_counter.pack(side="top", fill=tk.Y, expand=True)

      spacer = tk.Label(self.status_frame, text="")
      spacer.pack(side="top", fill=tk.Y, expand=True)

      label_bpm = tk.Label(self.status_frame, text="BPM:", font=("Arial", 15))
      label_bpm.pack(side="top", fill=tk.Y, expand=True)

      entry = tk.Entry(self.status_frame, width=10, font=("Arial", 15), justify="center")
      entry.insert(0, "120")
      entry.pack(padx=5, expand=True)

      spacer = tk.Label(self.status_frame, text="")
      spacer.pack(side="top", fill=tk.Y, expand=True)

      #Menu buttons such as different modes that we'll figure out later
      #Start button switches with Stop button, Quit button, idk
      start_button = tk.Button(self.status_frame, text="Start", font=("Arial", 15), fg="green",
                               command=lambda: self.start(entry))
      start_button.pack(side="top", fill=tk.Y, expand=True, ipadx=10)

      spacer = tk.Label(self.status_frame, text="")
      spacer.pack(side="top", fill=tk.Y, expand=True)
      
      quit_button = tk.Button(self.status_frame, text="Quit", font=("Arial", 15),
                              command=lambda: self.quit())
      quit_button.pack(side="top", fill=tk.Y, expand=True, ipadx=10)
      
      return keyA_label, keyS_label, keyD_label, point_counter, start_button, quit_button

   def start(self, entry):
      if self.start_button['text'] == 'Start':
         self.game_is_running = True
         entry.config(state='disabled')

         self.start_button['text'] = "Stop"
         self.start_button.config(fg="red")

         #self.Met = metronome(self.win, self.bpm, self.count, self.game_is_running)

         print("game is running")
         
         if self.game_is_running:
            try:
               self.bpm = int(entry.get())
            except ValueError:
               self.bpm = 60
            else:
               if self.bpm > 300:  # limits BPM
                  self.bpm = 300
                  
            self.counter()
         
      else:
         self.count = 0
         the_label = self.rock_label.grid()

         #self.bpm = 0

         self.game_is_running = False
         entry.config(state='normal')
         
         self.start_button['text'] = "Start"
         self.start_button.config(fg="green")

         #self.Met = metronome(self.win, self.bpm, self.count, self.game_is_running)

         print("game is not running")

   def counter(self):
      if self.game_is_running:
         if self.beat == 4:
            try:
               self.time = int((60 / self.bpm - 0.1) * 1000)
               print(self.time)
            except ZeroDivisionError:
               self.time = 900

         self.count += 1
         self.var.set(self.count)

         if self.count == 3:
            self.label_count['text'] = "3"
            self.label_count.config(fg="red")
            self.compChoice()
            Beep(659, 100)
            
         elif self.count >= self.beat:
            self.count = 0
            self.label_count.config(fg="green")
            Beep(880, 100)

         elif self.count < 3:
            self.label_count.config(fg="black")
            self.rock_label.grid()
            Beep(440, 100)
            
         self.win.after(self.time, lambda: self.counter())

   def compChoice(self):
      comp_choice = "none"
      comp = random.randint(0,2)
      if comp == 0:
         comp_choice = 0
         self.rock_label.grid()
         self.paper_label.grid_remove()
         self.scissors_label.grid_remove()

      elif comp == 1:
         comp_choice = 1
         self.paper_label.grid()
         self.rock_label.grid_remove()
         self.scissors_label.grid_remove()
         
      elif comp == 2:
         comp_choice = 2
         self.scissors_label.grid()
         self.rock_label.grid_remove()
         self.paper_label.grid_remove()
      else:
         comp_choice = "none"

      print("Computer chose", comp_choice)
      return comp_choice

   def set_callbacks(self):
      self.win.bind("<a>",self.rockClick)
      self.win.bind("<s>",self.paperClick)
      self.win.bind("<d>",self.scissorsClick)

   def rockClick(self, event):
      userChoice = 0
      print("rock")
      self.win_round()
      return userChoice
   def paperClick(self, event):
      userChoice = 1
      print("paper")
      self.win_round()
      return userChoice
   def scissorsClick(self, event):
      userChoice = 2
      print("scissors")
      self.win_round()
      return userChoice
   
   def win_round(self):
      if self.compChoice == 0:
         if self.userChoice == 1:
            self.point_counter['text'] = str(int(self.point_counter['text']) + 1)
         elif self.userChoice == 2:
            self.point_counter['text'] = str(int(self.point_counter['text']) - 1)
         else:
            print("Draw: No points")
            
      elif self.compChoice == 1:
         if self.userChoice == 0:
            self.point_counter['text'] = str(int(self.point_counter['text']) - 1)
         elif self.userChoice == 2:
            self.point_counter['text'] = str(int(self.point_counter['text']) + 1)
         else:
            print("Draw: No points")

      elif self.compChoice == 2:
         if self.userChoice == 0:
            self.point_counter['text'] = str(int(self.point_counter['text']) + 1)
         elif self.userChoice == 1:
            self.point_counter['text'] = str(int(self.point_counter['text']) - 1)
         else:
            print("Draw: No points")
      else:
         print("Not Valid play")
   
   def quit(self):
      really_quit = messagebox.askyesno("Quiting?", "Do you really want to quit?")
      if really_quit:
         self.win.destroy()

class metronome:
   def __init__(self, root, entry, count, start):

      self.root = root
      
      self.start = start
      print(self.start)
      self.bpm = entry
      print(self.bpm)
      self.count = count
      self.beat = 4
      self.time = 0

      if self.start == True:
         self.start_counter()
      elif self.start == False:
         self.stop_counter()

   def start_counter(self):
      if not self.start:
         try:
            self.bpm = int(entry.get())
         except ValueError:
            self.bpm = 60
         else:
            if self.bpm > 300:  # limits BPM
               self.bpm = 300
            elif self.bpm <= 0:
               self.bpm = 60
         self.start = True
         self.met_counter()
      print("metronome has started")
         
   def stop_counter(self):
      self.start = False
      self.count = 0
      
      print("metronome has stopped")

   def met_counter(self):
      if self.start:
         self.time = int((60 / self.bpm - 0.1) * 1000)

         self.count += 1
         self.var.set(self.count)

         if self.count == 3:
            print("BEEP")
            Beep(880, 200)

         elif self.count >= self.beat:
            self.count = 0
            print("beep if win or lose")
            Beep(440, 200)
         else:
            print("beep")
            Beep(440, 200)
            
         self.root.after(self.time, lambda: self.met_counter())


if __name__=="__main__":
   main()
      
