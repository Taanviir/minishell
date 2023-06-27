## minishell
Minishell is a simple shell clone designed to teach C programming and the basics of the Linux system.

- A simplified hands-on learning experience for understanding how the shell interprets user commands, executes them, and communicates with the underlying system.

- Building a mini shell from scratch helps to understand how the shell interprets user commands, executes them, and interacts with the operating system

- Essential system-level concepts such as processes, signals, and file descriptors

[logo]

[picture of it running]

### Tokenizing the command

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

## Currently working on
`get_token.c` breaks up the input command into tokens, that could be either an __`operator`__ or __`a`__ a word that could be either a command, file name, arguments... etc


# Quoting
Is used to remove special meaning from characters or words in the shell.
- Preserve the literal meaning of an operator
- Prevent reserved keywords from being recognized as such
- Prevent parameter expansion and substitutions within `here_doc????`

The following characters represent themselves when quoted

	|  &  ;  <  >  (  )  $  `  \  "  '  <space>  <tab>  <newline>
Quoting can be done in 3 ways
- Escape character `\`
- Single-Quotes `'`
- Double-Quotes `"`

## Escape character - backslash `\`
Can be either a line break or an escape character
## Single Quote `'`
Preserves the meaning of all characters until the next `'` is encountered. A single quote cannot occur within single quotes





