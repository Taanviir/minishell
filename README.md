## minishell
Minishell is a simple shell clone designed to teach C programming and the basics of the Linux system. 

- A simplified hands-on learning experience for understanding how the shell interprets user commands, executes them, and communicates with the underlying system.

- Building a mini shell from scratch helps to understand how the shell interprets user commands, executes them, and interacts with the operating system

- Essential system-level concepts such as processes, signals, and file descriptors

[logo]

[picture of it running]


#### _A list of built in commands to implement_

``` console
- cd : Change the current directory // can be implemented with chdir sys call

- echo : Print a message to the terminal.

- exit : Exit the shell.

- export : Set an environment variable.

- history : Display a list of previously executed commands.

- pwd : Print the current working directory.

- source : Execute commands from a file in the current shell.

- alias : Create an alias for a command.

- bg : Move a job to the background.

- fg : Move a job to the foreground.

- jobs : Display a list of active jobs.

- kill : Send a signal to a process.

- set : Set shell options and positional parameters.

- shift : Shift positional parameters to the left.

- test : Evaluate conditional expressions.

- trap : Set a command to be executed when a signal is received.
```

// interesting stuff to explore
>#include <dirent.h>
>has functinos like opendir, which returns a pointer to a struct that allows traversing directories
>and some info about files, might work the same way as **read**

> lstat for file info

---
##### usefull resources

>[Github - sample](https://github.com/maiadegraaf/minishell)
  >
  >[Blogpost guide](https://brennan.io/2015/01/16/write-a-shell-in-c/)
  >
  >[Minishell guide](https://harm-smits.github.io/42docs/projects/minishell)