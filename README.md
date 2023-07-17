# Newbix -- A newbie's Operating System

## How to build and run
**Prerequisite**: grub2-mkrescue and xorriso
```Bash
## If you are in Ubuntu 20.04 ##
$ sudo apt update
$ sudo apt install grub-common
$ sudo apt install xorriso
```

```Bash
## If you encounter -lgcc related issue ##
$ sudo apt install gcc-multilib
```

```Bash
## If you encounter grub2-mkrescue related issue ##
$ sudo ln -sT /usr/bin/grub-mkrescue /usr/bin/grub2-mkrescue
```

```Bash
$ make
```
