#### Name - Khushi

#### Roll No. - 2021101017

#### Operating system- UBUNTU

---

### **Commands to run:**

From the root directory of project, run `make all` followed by `./shell`

---

## File & Functions

- `main.c`
  - Run Shell Loop for taking in commands.
  - Extract Arguments from command
  - Bind functions from different files together
  - Manage history of the commands and background process handling
  - manage promts
- `cd.c`
  - Manages the _cd_ command outputs
  - giving more than 2 arguements with cd as the first arguement gives error
  - It follows the standard implementation of the _cd_ command of the `bash` shell
  - For the `cd ..` command, the shell will reach to the parent directory of the current directory till the directory is `/`
- `pwd`
  - it emulates the actual _pwd_ command of the `bash` shell
  - it prints on the terminal absolute path of the current working directory
- `history.c`

  - implements functions to print the lates commands in the history (10 commands)
  - Stores maximum 20 commands

- `echo.c`

  - Prints user input after removing excess spaces/tabs

- `ls.c`

  - Prints all files/sub-directories in a location
  - Flags implemented: `a` and `l`
  - Multiple directories supported

- `pinfo.c`

  - Prints info about process with given PID (current process if none is given)

- `headers.h`

  - contains all the headers files

- `fg.c`
  - contains impementation of the forground and background process
  - uses `execvp` buit-in command to implement the commands
  - in case of foreground processes, if the program to more than 1 sec, the prompt will show it for one iteration
  - whenever any background process gets over, the process name along wiht its pid will be outputed
  - the background processes are stored in a linked list

- `discover.c`
  - finds the file or directory(prints all the pths if nothing given in "") given from the target directory given(if not given take current directory).

- `commands.c`
  - Contains all the commands which direct to their respective header file.

- `execute.c`
  - Contains code that handles the input output redirection and pipe just without redirection.

- `jobs.c`
  - Contains the input `jobs` , `sig` , `fg` , `bg`.
  - `jobs` mention all the commands running or stopped.
  - `sig` take two numbers for is the process that is running and second is corresponding to the singal in signal(7) man page list.
  - `fg` brings the process with corresponding pid from the bg to the foreground.
  - `Assumptions`: when a process is brought from bg to fg then when the process exits then it displays a message in terminal that it exited normally/abnormally.
  - `bg` changes the stopped process with corresponding pid to running.


### Other Implementations

###### Commands/functions which don't have a separate file.

- Signals

  - `Ctrl+C` Stops the current process.
  - `Ctrl+D` Exits the shell.
  - `Ctrl+Z` Sends the running process in the background.

- Background Processes Manipulations

  - Implementation of background processes list, removing/adding them from/to the list is done in `main.c`.

- Exiting from the Shell
  - `exit` command.

## Assumptions

- Reasonable assumptions are made for things like length of current path, number of commands, command length, etc. The shell will work perfectly for all "day to day work".

- `user` and `hostname` will be constant throughout the life of current shell instance.

- `echo` will treat everything as normal character.

- File and directory names shouldn't contain spaces or special characters. (Some commands may work even without this.)

- `pinfo` may break on systems not running Ubuntu. This command uses `/proc` files which may not be same for other OS.

- Every user input will be stored as it is in history, given it is not same as the last input and contains at least one character other than space or tab.

- Prompt will display only _terminated normally_ or _terminated abnormally_ when a background process ends.

- Prompt will check exist status of background processes the very moment _SIGCHLD_ signal is called and the message that a particular background process has ended will be printed automatically

- Any error while running a command will result in aborting the command after printing an error message.

- `&` (used for running process in background) can come anywhere in command.
Under the Shadow
- `output.txt` file is used to save the history of commands after the shell has exited.
  It is assumed that shell will be run as a single process and no 2 processes will run the shell concurrently.

# C-Shell
