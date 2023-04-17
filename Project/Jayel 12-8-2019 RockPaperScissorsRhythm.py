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
   userChoice = "none"
   
   def __init__(self):
      self.win = tk.Tk()
      self.win.title("Rock Paper Scissors Rhythm")

      self.game_frame, self.status_frame = self.create_frames()

      self.game_is_running = False
      self.count = 0

      self.rock_photo = PhotoImage(file="rock.png")
      self.paper_photo = PhotoImage(file="paper.png")
      self.scissors_photo = PhotoImage(file="scissors.png")
      self.win_photo = PhotoImage(file="checkmark.png")
      self.lose_photo = PhotoImage(file="x.png")

      self.var = tk.StringVar()
      self.var.set(self.count)

      self.rock_label, self.paper_label, self.scissors_label = self.create_hands()

      self.countdown = self.create_countdown()

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

   def set_callbacks(self):
      self.win.bind("<a>",self.rockClick)
      self.win.bind("<s>",self.paperClick)
      self.win.bind("<d>",self.scissorsClick)

   def start(self, entry):
      if self.start_button['text'] == 'Start':
         self.game_is_running = True
         entry.config(state='disabled')

         try:
            self.bpm = int(entry.get())
         except ValueError:
            self.bpm = 60
         else:
            if self.bpm > 300:  # limits BPM
               self.bpm = 300
            elif self.bpm <= 0:
               self.bpm = 60
   
         metronome(self.win, self.bpm, self.count, self.game_is_running)
         self.start_button['text'] = "Stop"
         self.start_button.config(fg="red")

         print("game is running")
         
      else:
         self.game_is_running = False
         
         self.rock_label.grid(row=0, column=0, sticky=tk.N + tk.E + tk.W)
         
         entry.config(state='normal')
         
         metronome(self.win, self.bpm, self.count, self.game_is_running)
         self.start_button['text'] = "Start"
         self.start_button.config(fg="green")

         print("game is not running")

   def compChoice(self):
      comp = random.randint(0,2)
      comp_choice = "none"
      if comp == 0:
         comp_choice = "rock"
         self.rock_label.grid()
         self.paper_label.grid_remove()
         self.scissors_label.grid_remove()

      elif comp == 1:
         comp_choice = "paper"
         self.paper_label.grid()
         self.rock_label.grid_remove()
         self.scissors_label.grid_remove()
         
      elif comp == 2:
         comp_choice = "scissors"
         self.scissors_label.grid()
         self.rock_label.grid_remove()
         self.paper_label.grid_remove()
         
      print("Computer chose:",comp_choice)
      return comp_choice

   def rockClick(self, event):
      self.userChoice = "rock"
      print("rock")
   def paperClick(self, event):
      self.userChoice = "paper"
      print("paper")
   def scissorsClick(self, event):
      self.userChoice = "scissors"
      print("scissors")
   
   def win_round(self, event):
      pass
   
   def quit(self):
      really_quit = messagebox.askyesno("Quiting?", "Do you really want to quit?")
      if really_quit:
         self.win.destroy()

class metronome(RPSR):
   def __init__(self, root, entry, count, start):

      self.root = root
      
      self.start = start
      print(self.start)
      self.entry = entry
      self.count = count
      self.beat = 4
      self.time = 0

      if self.start == True:
         self.start_counter()
         print("metronome has started")
         print(self.bpm)
      elif self.start == False:
         self.stop_counter()
            
   def stop_counter(self):
      self.start = False
      print("metronome has stopped")

   def start_counter(self):
      if self.start == True:
         self.bpm = int(self.entry)

         if self.beat == 4:
            self.time = int((60 / self.bpm - 0.1) * 1000)

         self.count += 1

         if self.count == 3:
             Beep(880, 100)
         elif self.count >= self.beat:
             self.count = 0
             Beep(440, 100)
         else:
             Beep(440, 100)

         if self.count == 3:
            RPSR.compChoice(self)

         self.root.after(self.time, lambda: self.start_counter())


if __name__=="__main__":
   main()
      
