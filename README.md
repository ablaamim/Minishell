
<h1 align=center>
	<b> :skull:  Minishell : As much beautiful as a shell !</b>
</h1>


---

<div align=center>
<img src=https://github.com/ablaamim/Minishell/blob/master/img/minishellm.png />
</div>

---

<h1 align=center>
	<b>Introduction : </b>
</h1>

---

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
| **echo** | Echo the STRING(s) to standart output. **-n** flag:
do not output the trailing newline. |
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

* Arguments handling / Prompt implementation :

# main.c

> Arguments verification :

	* if argc == 1 : launch program.
	* else : Error.

```c
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

---
