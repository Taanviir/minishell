## minishell
This project was made as a collaborative effort between [samih713](https://github.com/samih713/) and [Taanviir](https://github.com/Taanviir)

Minishell is a simple shell clone designed to teach C programming and the basics of the Linux system. It provides a simplified hands-on learning experience for understanding how the shell interprets user commands, executes them, and communicates with the underlying system. Building a mini shell from scratch helps to understand how the shell interprets user commands, executes them, and interacts with the operating system, covering essential system-level concepts such as processes, signals, and file descriptors.

![image](https://github.com/Taanviir/minishell/assets/66136914/a5a23a00-baae-411c-81da-c64e331cc2e3)

---
### How to Use
Clone the repository using 
```
git clone https://github.com/Taanviir/minishell.git
```
Navigate to the cloned directory using
```
cd minishell
```
Compile the shell using
```
make
```
Run the shell using
```
./minishell
```

To check for memory leaks use
```
valgrind --show-leak-kinds=all --leak-check=full --suppressions=vg_rlsuppressions.supp ./minishell
```

---
### Resources

>[Github - Sample](https://github.com/maiadegraaf/minishell)
>
>[Blogpost Guide](https://brennan.io/2015/01/16/write-a-shell-in-c/)
>
>[Minishell Guide](https://harm-smits.github.io/42docs/projects/minishell)
>
>[Shell Program Explained Video](https://www.youtube.com/watch?v=ubt-UjcQUYg)

