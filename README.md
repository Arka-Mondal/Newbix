# Newbix -- A newbie's Operating System

## How to build and run

```Bash
$ make
```
### Installing some development tools might be required
#### Fedora
```Bash
$ sudo dnf install gcc make xorriso
```
For fedora users, `grub2` is probably already installed, so you are good to go.

#### Ubuntu 20.04 and later
```Bash
$ sudo apt update
$ sudo apt install build-essential grub-common xorriso
```

## Troubleshoot

##### If you encounter -lgcc related issue
```Bash
$ sudo apt install gcc-multilib
```

##### If you encounter grub2-mkrescue related issue
```Bash
$ sudo ln -sT /usr/bin/grub-mkrescue /usr/bin/grub2-mkrescue
```
