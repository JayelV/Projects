#!/usr/bin/python3

import fcntl, os, getpass, sys, time
from subprocess import *
from datetime import datetime, timedelta

getting_started = True
is_primary = False
log_file = ''
exe_name = ''

def system(cmd):
  return "".join(map(chr, Popen(cmd, shell=True, stdout=PIPE, stderr=STDOUT).communicate()[0]))
  # return run(cmd.split(), capture_output=True, text=True).stdout

def run_prog(message_dir, message_id, input_file_name = False):
  global exe_name
  # time.sleep(1)  # to avoid some kind of problem with too much output!
  if input_file_name:
    with open(input_file_name, "rb") as f:
      incoming_data = ("- message_id: " + str(message_id) + "\n").encode()
      incoming_data += f.read()
  else:
    incoming_data = ('').encode()
  proc = Popen('./' + exe_name, env={**os.environ, 'message_dir': message_dir})
  current_message_file = message_dir + "current_message"
  with open(current_message_file, "wb") as f:
    f.write(incoming_data)
  try:
    proc.communicate(timeout=30)
    print_to_log("  run_prog len(incoming_data) " + str(len(incoming_data)))
    os.remove(current_message_file)
  except Exception as e:
    print("  Error:  run_prog could not run:", e)
    proc.kill()
    proc.communicate()
    exit()

def find_next_message_after(message_dir, msg_file = False):
  files = system("ls " + message_dir + "??.*").split('\n')
  # print('files', files)
  if not msg_file and len(files) >0 and len(files[0]) > len(message_dir):
    return files[0][len(message_dir):]
  for i in range(len(files)):
    if message_dir + msg_file == files[i]:
      if i+1 < len(files) and len(files[i+1]) > len(message_dir):
        return files[i+1][len(message_dir):]
  return 'exit'

def clear_directory(message_dir):
  if os.path.isdir(message_dir):
    files = system("ls " + message_dir + "??.*").split('\n')
    files.append(message_dir + 'next_message')
    files.append(message_dir + 'log')
    for fname in files:
      if os.path.isfile(fname):
        os.remove(fname)

def print_to_log(msg):
  global log_file, exe_name
  with open(log_file, 'a') as f:
    f.write(datetime.now().strftime("%H:%M:%S"))
    f.write(' ' + exe_name)
    f.write(' ' + msg + '\n')

def check_for_message(message_dir, next_file):
  global exe_name, getting_started, is_primary
  if getting_started and is_primary:
    getting_started = False
    clear_directory(message_dir)
  if not os.path.isfile(next_file):
    try:
      with open(next_file, 'w') as f:
        f.write('')
    except:
      print("Error:  unable to create file", next_file)
      exit()
  with open(next_file, "r") as g:
    msg_file = g.read().rstrip()
    g.close()
    print_to_log('  msg_file ' + msg_file)
    next_message_name = False
    message_id = 1   # what should this be?
    if len(msg_file) > 3 and msg_file[0:2].isdigit() and '.' == msg_file[2]:
      getting_started = False # valid next
      if exe_name == msg_file[3:]:
        run_prog(message_dir, message_id, message_dir + msg_file)
        next_message_name = find_next_message_after(message_dir, msg_file)
    elif getting_started:  # wait, for now
      return False
    elif 'exit' == msg_file:
      exit()
    elif 0 == len(msg_file):  # probably at start
      run_prog(message_dir, message_id)
      next_message_name = find_next_message_after(message_dir)
    else:
      print("Error:  msg_file is " + msg_file)
      exit()
    if next_message_name:
      with open(next_file, "w") as g2:
        g2.write(next_message_name + '\n')
      return True
  return False

def main():
  # print(find_next_message_after('olaf/', '02.prog3')); exit()
  # check_for_message('prog2.py', 'olaf/', 'olaf/next_file'); exit()
  global log_file, exe_name, is_primary

  if len(sys.argv) > 1 and '-primary' == sys.argv[1]:
    is_primary = True
    del sys.argv[1]
  if len(sys.argv) != 2 and len(sys.argv) != 3:
    print("Usage:", sys.argv[0], "[-primary] exe_name [shared_id]")
    exit()
  
  exe_name = sys.argv[1]
  if len(sys.argv) == 3:
    shared_id = sys.argv[2]
  else:
    shared_id = getpass.getuser()
  share_dir = "/usr/local/cs/cs251/share/"
  message_dir = share_dir + shared_id + '/'
  # print('message_dir', message_dir); exit()
  lock_file = message_dir + 'lock_file'
  log_file = message_dir + 'log'
  next_file = message_dir + 'next_message'
  if not os.path.isdir(message_dir):
    try:
      os.mkdir(message_dir)
    except:
      print("Error:  unable to create directory", message_dir)
      exit()

  with open(lock_file, "w") as f:
    if f.writable():
      # print('is writable, attempting to lock.')
      forever = True
      while forever:
        # forever = False
        try:
          fcntl.lockf(f, fcntl.LOCK_EX)
          print_to_log('  lock_file locked.')
        except:
          print_to_log('  not able to lock lock_file?')
        got_one = check_for_message(message_dir, next_file)
        print_to_log('  unlocking lock_file')
        if got_one:
          time.sleep(1)
        fcntl.lockf(f, fcntl.LOCK_UN)
        time.sleep(1)
    else:
      print('  lock_file not writable')

if __name__ == "__main__":
  main()
