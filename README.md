<h1 align=center>
	<b> :skull:  Minishell : How to succeed to fail and lose all your friends!</b>
<h1>

<p align="center">
	<img src="https://github.com/ablaamim/Minishell/blob/master/img/127766732-743a1cf4-6d1e-4663-b8d6-1705f69c63dd.png" width="500">
<p/>

---

<h1 align="center">
	<b> :book: Quotes : </b>
</h1>

```

$> echo “The Linux philosophy is to laugh in the face of danger 8D !".

$> echo “All operating systems sucks, but Linux just sucks less.”

$> echo “An infinite number of monkeys typing into GNU emacs would never make a good program.”
```

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

Besides that it is meant to make you suffer, read a lot of documentations,
lose your sanity and become bugs intact.

This is a manual to read RELIGIOUSLY before starting [man bash](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)

<h1 align=center>
<img src="https://64.media.tumblr.com/31402d1cf6ddb5c2db18cb3a5f258b54/tumblr_otyab9Gzzc1w4t58uo1_540.gifv" width="500">
<h1>

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

:construction: Project Organization in root of the repository :

---

```
.
.
├── includes/
├── srcs/
├── Makefile
.
.
```
---
