### Rock Paper Scissors Rhythm

import tkinter as tk
from tkinter import PhotoImage
import random
from tkinter import messagebox
import winsound
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

      self.game_frame, self.status_frame = self.create_frames() ### sets the frame for the hands and countdown, sets the GUI frame

      ### Initial settings when the program runs
      self.game_is_running = False 
      self.bpm = 0
      self.count = 0
      self.beat = 4
      self.time = 0

      ### Pictures
      self.rest_photo = PhotoImage(file="rest.png")
      self.rock_photo = PhotoImage(file="rock.png")
      self.paper_photo = PhotoImage(file="paper.png")
      self.scissors_photo = PhotoImage(file="scissors.png")
      self.win_photo = PhotoImage(file="checkmark.png")
      self.lose_photo = PhotoImage(file="x.png")

      ### Variable for the countdown, sets it at self.count
      self.var = tk.StringVar()
      self.var.set(self.count)
      
      ### Labels for the hands
      self.rest_label, self.rock_label, self.paper_label, self.scissors_label = self.create_hands()

      ### Label for the countdown
      self.label_count = self.create_countdown()

      ### Labels for the win and lose checkmark and x. Set to be hidden when the program runs.
      self.label_win, self.label_lose = self.win_or_lose()
      self.label_win.grid_remove()
      self.label_lose.grid_remove()

      ### GUI labels
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

      scissors_label = tk.Label(self.game_frame, image=self.scissors_photo)
      scissors_label.grid(row=0, column=0, sticky=tk.N + tk.E + tk.W)

      paper_label = tk.Label(self.game_frame, image=self.paper_photo)
      paper_label.grid(row=0, column=0, sticky=tk.N + tk.E + tk.W)
            
      rock_label = tk.Label(self.game_frame, image=self.rock_photo)
      rock_label.grid(row=0, column=0, sticky=tk.N + tk.E + tk.W)

      rest_label = tk.Label(self.game_frame, image=self.rest_photo)
      rest_label.grid(row=0, column=0, sticky=tk.N + tk.E + tk.W)

      return rest_label, rock_label, paper_label, scissors_label

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

      point_label = tk.Label(self.status_frame, text="Total Points:", font=("Arial", 17))
      point_label.pack(side="top", fill=tk.Y, expand=True)

      point_counter = tk.Label(self.status_frame, text="0", font=("Arial", 17))
      point_counter.pack(side="top", fill=tk.Y, expand=True)

      win_label = tk.Label(self.status_frame, text="Wins:", font=("Arial", 9))
      win_label.pack(side="top", fill=tk.Y, expand=False)
      win_counter = tk.Label(self.status_frame, text="0", font=("Arial", 9), fg="green") ### Counter for wins
      win_counter.pack(side="top", fill=tk.Y, expand=False)

      lose_label = tk.Label(self.status_frame, text="Losses:", font=("Arial", 9))
      lose_label.pack(side="top", fill=tk.Y, expand=False)
      lose_counter = tk.Label(self.status_frame, text="0", font=("Arial", 9), fg="red") ### Counter for losses
      lose_counter.pack(side="top", fill=tk.Y, expand=False)

      draw_label = tk.Label(self.status_frame, text="Draws:", font=("Arial", 9))
      draw_label.pack(side="top", fill=tk.Y, expand=False)
      draw_counter = tk.Label(self.status_frame, text="0", font=("Arial", 9), fg="black") ### Counter for draws
      draw_counter.pack(side="top", fill=tk.Y, expand=False)

      spacer = tk.Label(self.status_frame, text="")
      spacer.pack(side="top", fill=tk.Y, expand=True)

      label_bpm = tk.Label(self.status_frame, text="BPM:", font=("Arial", 15))
      label_bpm.pack(side="top", fill=tk.Y, expand=True)

      entry = tk.Entry(self.status_frame, width=10, font=("Arial", 15), justify="center") ### Entry box to set BPM
      entry.insert(0, "100")
      entry.pack(padx=5, expand=True)

      spacer = tk.Label(self.status_frame, text="")
      spacer.pack(side="top", fill=tk.Y, expand=True)

      #Start button switches with Stop button, Quit button
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
         entry.config(state='disabled') ### Disable the entry box when the game runs so that nothing else gets typed in as the player plays the game

         self.start_button['text'] = "Stop" ### When the "Start" button is pressed, it turns into a "Stop" button
         self.start_button.config(fg="red")

         self.point_counter['text'] = "0" ### All points are reset to a new game
         self.win_counter['text'] = "0"
         self.lose_counter['text'] = "0"
         self.draw_counter['text'] = "0"

         self.keyA_label.config(fg="black") ### Returns all key label colors as black
         self.keyS_label.config(fg="black")
         self.keyD_label.config(fg="black")

         self.userChoice = "none"
         
         if self.game_is_running:
            try:
               self.bpm = int(entry.get()) ### Takes input from entry box above
            except ValueError: ### Sets bpm if user does not put a value in the entry box
               self.bpm = 40
            else:
               if self.bpm > 200: ### Sets limits to bpm
                  self.bpm = 200
               elif self.bpm < 40:
                  self.bpm = 40
                  
            self.counter()
         
      else: ### When "Stop" button is pushed
         self.count = 0
         the_label = self.rest_label.grid()

         self.game_is_running = False
         entry.config(state='normal') ### Enable the entry box

         self.keyA_label.config(fg="black") ### Returns all key label colors as black
         self.keyS_label.config(fg="black")
         self.keyD_label.config(fg="black")

         self.label_win.grid_remove() ### Make the win and lose labels disappear
         self.label_lose.grid_remove()
         
         self.start_button['text'] = "Start" ### Turn the "Stop" button into a "Start" button
         self.start_button.config(fg="green")

   def counter(self): ### Calculates and runs input BPM
      if self.game_is_running:
         if self.beat == 4:
            try:
               self.time = int(((60 / self.bpm - 0.1) * 1000) - 100) ### Sets the wait time between each count
               
            except ZeroDivisionError:
               self.time = 900

         self.count += 1 ### Adds the counter by 1 every beat
         self.var.set(self.count)

         if self.count == 3:
            self.label_count['text'] = "3" ### The 3 is red to indicate that the player should press 'a', 's', or 'd'
            self.label_count.config(fg="red")
            self.compSelection = self.compChoice() ### The computer makes a choice
            Beep(659, 200) ### Pitch of beep higher than 1 and 2 as a warning to the player
            
         elif self.count >= self.beat:
            self.win_round() ### Directs to win_round method
            self.count = 0 ### Returns counter to 1 if after 4
            self.label_count.config(fg="black")

         elif self.count < 3:
            self.label_count.config(fg="black")
            self.rest_label.grid()
            Beep(440, 200)
            
            self.label_win.grid_remove()
            self.label_lose.grid_remove()

            self.reset_hand() ### Directs to reset_hand method

            self.keyA_label.config(fg="black") ### Returns all key label colors as black
            self.keyS_label.config(fg="black")
            self.keyD_label.config(fg="black")
            
         self.win.after(self.time, lambda: self.counter()) ### Runs the counter again after waiting the calculated time

   def compChoice(self):
      ### Computer chooses from either rock, paper, or scissors
      comp_choice = "none"
      comp = random.randint(0,2)
      if comp == 0:
         comp_choice = "rock"
         self.rock_label.grid() ### Rock picture is revealed, hides other pictures. This is the same for the other two choices
         self.rest_label.grid_remove()
         self.paper_label.grid_remove()
         self.scissors_label.grid_remove()

      elif comp == 1:
         comp_choice = "paper"
         self.paper_label.grid()
         self.rest_label.grid_remove()
         self.rock_label.grid_remove()
         self.scissors_label.grid_remove()
         
      elif comp == 2:
         comp_choice = "scissors"
         self.scissors_label.grid()
         self.rest_label.grid_remove()
         self.rock_label.grid_remove()
         self.paper_label.grid_remove()
      else:
         comp_choice = "none"

      return comp_choice

   def rockClick(self, event):
      if self.count >= 3: ### Has to be pressed on the 3 count
         self.userChoice = "rock" ### User has pressed the key to choose "rock". Same for other two choices
         self.keyA_label.config(fg="green") ### The label for "rock" on the top of the GUI turns green to indicate that the player chose "rock"
         self.keyS_label.config(fg="black")
         self.keyD_label.config(fg="black")
      else:
         self.userChoice = "none" ### If pressed too early or too late, a draw is made, the "x" shows up, and the labels turn red
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

   def set_callbacks(self): ### Binds each 'Click' to their respective buttons
      self.win.bind("<a>",self.rockClick) 
      self.win.bind("<s>",self.paperClick)
      self.win.bind("<d>",self.scissorsClick)
   
   def win_round(self): ### Sets the conditionals and adds to point counters
      if self.compSelection == "rock":
         if self.userChoice == "paper":
            self.point_counter['text'] = str(int(self.point_counter['text']) + 1) ### If player won a round, the total points goes up by 1
            self.win_counter['text'] = str(int(self.win_counter['text']) + 1) ### Win counter also goes up by 1
            self.label_win.grid() ### The checkmark picture is shown
            Beep(1109, 70) ### A cheery beep indicates a win
            Beep(880, 130)
         elif self.userChoice == "scissors":
            self.lose_counter['text'] = str(int(self.lose_counter['text']) + 1) ### If player loses a round, lose counter goes up by 1
            if str(self.point_counter['text']) <= '0':
               self.point_counter['text'] = str(int(self.point_counter['text']) - 0) ### If Total points is 0, there is no decrease to a negative number
            else:
               self.point_counter['text'] = str(int(self.point_counter['text']) - 1) ### Else, total points go down by 1
            self.label_lose.grid() ### The 'x' picture is shown
            Beep(294, 70) ### A low-pitched beep indicates a loss
            Beep(294, 130)
         else:
            self.draw_counter['text'] = str(int(self.draw_counter['text']) + 1) ### IF a draw, no points are made, but the draw counter goes up by 1
            Beep(659, 200) ### The same pitched beep as the one in 3
            
      elif self.compSelection == "paper":
         if self.userChoice == "rock":
            self.lose_counter['text'] = str(int(self.lose_counter['text']) + 1)
            if str(self.point_counter['text']) <= '0':
               self.point_counter['text'] = str(int(self.point_counter['text']) - 0)
            else:
               self.point_counter['text'] = str(int(self.point_counter['text']) - 1)
            self.label_lose.grid()
            Beep(294, 70)
            Beep(294, 130)
         elif self.userChoice == "scissors":
            self.point_counter['text'] = str(int(self.point_counter['text']) + 1)
            self.win_counter['text'] = str(int(self.win_counter['text']) + 1)
            self.label_win.grid()
            Beep(1109, 70)
            Beep(880, 130)
         else:
            self.draw_counter['text'] = str(int(self.draw_counter['text']) + 1)
            Beep(659, 200)

      elif self.compSelection == "scissors":
         if self.userChoice == "rock":
            self.point_counter['text'] = str(int(self.point_counter['text']) + 1)
            self.win_counter['text'] = str(int(self.win_counter['text']) + 1)
            self.label_win.grid()
            Beep(1109, 70)
            Beep(880, 130)
         elif self.userChoice == "paper":
            self.lose_counter['text'] = str(int(self.lose_counter['text']) + 1)
            if str(self.point_counter['text']) <= '0':
               self.point_counter['text'] = str(int(self.point_counter['text']) - 0)
            else:
               self.point_counter['text'] = str(int(self.point_counter['text']) - 1)
            self.label_lose.grid()
            Beep(294, 70)
            Beep(294, 130)
         else:
            self.draw_counter['text'] = str(int(self.draw_counter['text']) + 1)
            Beep(659, 200)

      else: ### If no valid play is made for some odd reason, does nothing except a beep
         Beep(659, 200)

   def reset_hand(self): ### When called, the player's choice returns to none, so that the last choice they made doesn't carry over another round
      self.userChoice = "none"
   
   def quit(self): ### When the "Quit" button is pressed, a popup messagebox will ask to confirm the action before exiting the game.
      really_quit = messagebox.askyesno("Quiting?", "Do you really want to quit?")
      if really_quit:
         self.win.destroy()


if __name__=="__main__":
   main()
      
