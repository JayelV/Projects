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

      self.label_win, self.label_lose = self.win_or_lose()
      self.label_win.grid_remove()
      self.label_lose.grid_remove()

      self.keyA_label, self.keyS_label, self.keyD_label, self.point_counter, self.win_counter, self.lose_counter, self.draw_counter, self.start_button, self.quit_button = self.create_status_widgets()
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

   def win_or_lose(self):
      label_win = tk.Label(self.game_frame, image=self.win_photo)
      label_win.grid(row=1, column=0, columnspan=2)

      label_lose = tk.Label(self.game_frame, image=self.lose_photo)
      label_lose.grid(row=1, column=0, columnspan=2)

      return label_win, label_lose
      
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

      point_label = tk.Label(self.status_frame, text="Total Points:", font=("Arial", 15))
      point_label.pack(side="top", fill=tk.Y, expand=True)

      point_counter = tk.Label(self.status_frame, text="0", font=("Arial", 15))
      point_counter.pack(side="top", fill=tk.Y, expand=True)

      win_label = tk.Label(self.status_frame, text="Wins:", font=("Arial", 9))
      win_label.pack(side="top", fill=tk.Y, expand=False)
      win_counter = tk.Label(self.status_frame, text="0", font=("Arial", 9), fg="green")
      win_counter.pack(side="top", fill=tk.Y, expand=False)

      lose_label = tk.Label(self.status_frame, text="Losses:", font=("Arial", 9))
      lose_label.pack(side="top", fill=tk.Y, expand=False)
      lose_counter = tk.Label(self.status_frame, text="0", font=("Arial", 9), fg="red")
      lose_counter.pack(side="top", fill=tk.Y, expand=False)

      draw_label = tk.Label(self.status_frame, text="Draws:", font=("Arial", 9))
      draw_label.pack(side="top", fill=tk.Y, expand=False)
      draw_counter = tk.Label(self.status_frame, text="0", font=("Arial", 9), fg="black")
      draw_counter.pack(side="top", fill=tk.Y, expand=False)

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
      
      return keyA_label, keyS_label, keyD_label, point_counter, win_counter, lose_counter, draw_counter, start_button, quit_button

   def start(self, entry):
      if self.start_button['text'] == 'Start':
         self.game_is_running = True
         entry.config(state='disabled')

         self.start_button['text'] = "Stop"
         self.start_button.config(fg="red")

         self.point_counter['text'] = "0"
         self.win_counter['text'] = "0"
         self.lose_counter['text'] = "0"
         self.draw_counter['text'] = "0"

         self.keyA_label.config(fg="black")
         self.keyS_label.config(fg="black")
         self.keyD_label.config(fg="black")

         self.userChoice = "none"
         
         if self.game_is_running:
            try:
               self.bpm = int(entry.get())
            except ValueError:
               self.bpm = 60
            else:
               if self.bpm > 300:
                  self.bpm = 300
                  
            self.counter()
         
      else:
         self.count = 0
         the_label = self.rock_label.grid()

         self.game_is_running = False
         entry.config(state='normal')

         self.keyA_label.config(fg="black")
         self.keyS_label.config(fg="black")
         self.keyD_label.config(fg="black")

         self.label_win.grid_remove()
         self.label_lose.grid_remove()
         
         self.start_button['text'] = "Start"
         self.start_button.config(fg="green")

   def counter(self):
      if self.game_is_running:
         if self.beat == 4:
            try:
               self.time = int((60 / self.bpm - 0.1) * 1000)
               
            except ZeroDivisionError:
               self.time = 900

         self.count += 1
         self.var.set(self.count)

         if self.count == 3:
            self.label_count['text'] = "3"
            self.label_count.config(fg="red")
            self.compSelection = self.compChoice()
            Beep(659, 100)
            
         elif self.count >= self.beat:
            self.win_round()
            self.count = 0
            self.label_count.config(fg="black")

         elif self.count < 3:
            self.label_count.config(fg="black")
            self.rock_label.grid()
            Beep(440, 100)
            self.label_win.grid_remove()
            self.label_lose.grid_remove()

            self.keyA_label.config(fg="black")
            self.keyS_label.config(fg="black")
            self.keyD_label.config(fg="black")
            
         self.win.after(self.time, lambda: self.counter())

   def compChoice(self):
      ### Computer chooses from either rock, paper, or scissors
      comp_choice = "none"
      comp = random.randint(0,2)
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
      else:
         comp_choice = "none"

      return comp_choice

   def rockClick(self, event):
      if self.count >= 3:
         self.userChoice = "rock"
         self.keyA_label.config(fg="green")
         self.keyS_label.config(fg="black")
         self.keyD_label.config(fg="black")
      else:
         self.userChoice = "none"
         self.label_lose.grid()
         self.keyA_label.config(fg="red")
         self.keyS_label.config(fg="red")
         self.keyD_label.config(fg="red")
      
   def paperClick(self, event):
      if self.count >= 3:
         self.userChoice = "paper"
         self.keyS_label.config(fg="green")
         self.keyA_label.config(fg="black")
         self.keyD_label.config(fg="black")
      else:
         self.userChoice = "none"
         self.label_lose.grid()
         self.keyA_label.config(fg="red")
         self.keyS_label.config(fg="red")
         self.keyD_label.config(fg="red")

   def scissorsClick(self, event):
      if self.count >= 3:
         self.userChoice = "scissors"
         self.keyD_label.config(fg="green")
         self.keyA_label.config(fg="black")
         self.keyS_label.config(fg="black")
      else:
         self.userChoice = "none"
         self.label_lose.grid()
         self.keyA_label.config(fg="red")
         self.keyS_label.config(fg="red")
         self.keyD_label.config(fg="red")

   def set_callbacks(self):
      self.win.bind("<a>",self.rockClick)
      self.win.bind("<s>",self.paperClick)
      self.win.bind("<d>",self.scissorsClick)
   
   def win_round(self):
      if self.compSelection == "rock":
         if self.userChoice == "paper":
            self.point_counter['text'] = str(int(self.point_counter['text']) + 1)
            self.win_counter['text'] = str(int(self.win_counter['text']) + 1)
            self.label_win.grid()
            Beep(1109, 30)
            Beep(880, 70)
         elif self.userChoice == "scissors":
            self.lose_counter['text'] = str(int(self.lose_counter['text']) + 1)
            if str(self.point_counter['text']) <= '0':
               self.point_counter['text'] = str(int(self.point_counter['text']) - 0)
            else:
               self.point_counter['text'] = str(int(self.point_counter['text']) - 1)
            self.label_lose.grid()
            Beep(294, 30)
            Beep(294, 70)
         else:
            self.draw_counter['text'] = str(int(self.draw_counter['text']) + 1)
            Beep(659, 100)
            
      elif self.compSelection == "paper":
         if self.userChoice == "rock":
            self.lose_counter['text'] = str(int(self.lose_counter['text']) + 1)
            if str(self.point_counter['text']) <= '0':
               self.point_counter['text'] = str(int(self.point_counter['text']) - 0)
            else:
               self.point_counter['text'] = str(int(self.point_counter['text']) - 1)
            self.label_lose.grid()
            Beep(294, 30)
            Beep(294, 70)
         elif self.userChoice == "scissors":
            self.point_counter['text'] = str(int(self.point_counter['text']) + 1)
            self.win_counter['text'] = str(int(self.win_counter['text']) + 1)
            self.label_win.grid()
            Beep(1109, 30)
            Beep(880, 70)
         else:
            self.draw_counter['text'] = str(int(self.draw_counter['text']) + 1)
            Beep(659, 100)

      elif self.compSelection == "scissors":
         if self.userChoice == "rock":
            self.point_counter['text'] = str(int(self.point_counter['text']) + 1)
            self.win_counter['text'] = str(int(self.win_counter['text']) + 1)
            self.label_win.grid()
            Beep(1109, 30)
            Beep(880, 70)
         elif self.userChoice == "paper":
            self.lose_counter['text'] = str(int(self.lose_counter['text']) + 1)
            if str(self.point_counter['text']) <= '0':
               self.point_counter['text'] = str(int(self.point_counter['text']) - 0)
            else:
               self.point_counter['text'] = str(int(self.point_counter['text']) - 1)
            self.label_lose.grid()
            Beep(294, 30)
            Beep(294, 70)
         else:
            self.draw_counter['text'] = str(int(self.draw_counter['text']) + 1)
            Beep(659, 100)

      else:
         Beep(659, 100)
   
   def quit(self):
      really_quit = messagebox.askyesno("Quiting?", "Do you really want to quit?")
      if really_quit:
         self.win.destroy()


if __name__=="__main__":
   main()
      
