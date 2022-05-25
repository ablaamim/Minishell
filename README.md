
<h1 align=center>
	<b> :skull:  Minishell : Untitled mini-HELL as well !</b>
	<b> GUDIE : How to succeed to fail and lose all your friends!<b>
</h1>

---

</p>
<p align="center">
<img src="https://miro.medium.com/max/1000/1*VyyVo0PiByEqMMPUs4_QaQ.gif" width="500">
<p/>

> “The Linux philosophy is 'to laugh in the face of danger".

> “All operating systems sucks, but Linux just sucks less.”

>  “An infinite number of monkeys typing into GNU emacs would never make a good program.”

---

<div align=center>
<img src=https://github.com/ablaamim/Minishell/blob/master/img/minishellm.png />
</div>

---

<h1 align=center>
	<b>Introduction : </b>
</h1>

---
	add_history(input_readline);

The objective of this project is to create a simple shell and learn a lot about
processes and file descriptors.
The existence of shells is linked to the very existence of IT.
With Minishell project, we’ll be able to travel through time and come back to
problems people faced when Windows didn’t exist.

---

<h1 align=center>
	<b> :cyclone: Built-in functions to implement : </b>
</h1>


---

| Command | Description  |
|--- |--- |
| **echo** | Echo the STRING(s) to standart output. **-n** flag: do not output the trailing newline. |
| **cd** | Change the shell working directory	(with a relative or absolute path). |
| **pwd** | Print name of current/working directory. |
| **export** | Set export attribute for shell variables. |
| **unset** | Unset values of shell variables. |
| **env** | Print the environment. |
| **exit** | Cause the shell to exit with the exit status specified. |

---

<h1 align=center>
	<b> :hourglass:  Step by step : </b>
</h1>

---

:construction: Project Organization :

```
.
├── includes/
├── srcs/
├── Makefile
```
---

#### Arguments handling / Prompt implementation :

> Entry point of our program is the main, we will handle errors starting from there.

#### main() function :

###### Arguments verification && closing file descriptors beyond fd == 2:

	* if argc == 1 : launch program.
	* else (argc > 1 or argc < 1) : Error.

```c
/*Close all used file descriptors beyond fd == 2*/

void	ft_close_file_descriptors(void)
{
	int	fd;

	fd = open("console", O_RDWR);
	while (fd >= 0)
	{
		if (fd >= 3)
			close(fd);
		break ;
	}
}

int	main(int argc, char **argv)
{
	/* Normal behavior, since the executable doesnt take args dynamically */
	if (argc == 1)
	{
		/* Launch prompt */
		ft_prompt();
	}
	/* ERROR */
	else
		ERROR;
	return (EXIT_SUCCESS);
}
```
#### Prompt launching :

> In Linux, much of your work occurs from a command prompt, also known
as the shell, or BASH (Bourne-Again Shell). The shell interprets your
commands and passes them to the operating system for execution.

* ft_prompt() && read_input() && ft_save_history

> I retrieve input from user using readline() function [man readline](https://www.man7.org/linux/man-pages/man3/readline.3.html).
> Adding user input in history using add_history (Also read readline manual).

```c
void	ft_save_history(char *input) // Add history
{
	if (input && *input)
		ft_save_history(input);
}

int		read_input(void)
{
	char	*input_readline; // string to save input
	int		check_returns; // return values checker

	check_returns = 0x1; //normal state return to work properly is 1, 
	every other value is a form of error handling.
	input_readline = readline("minishell$>"); // Read input from user, save it as well && display a message prompt
	if (!input_readline) // if input_readline == NULL return 0
		return (0x0);
	free(input_readline);
	return (check_returns);
}

void	ft_prompt(void)
{
	int	check_return = 0x0;

	/*Infinite loop to keep the program running*/
	while (0x1)
	{
		check_return = read_input();
		/*if return == 1 --> exit */
		if (!check_return)
			/* EXIT_MINISHELL is nothing but a define in the header file*/
			write(2, EXIT_MINISHELL, sizeof(EXIT_MINISHELL));
	}
}

```

---
