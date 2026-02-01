# dnf-clone
A DNF clone made in pure C (package manager)

> [!WARNING]
> This package manager is still not complete and shouldn't be used for daily use
> In the next few releases the package manager should have be able to download required dependencies for packages automatically and search for packages
> So I think I can say that it you will be able to use it daily in the few releases (v0.0.2-alpha and v0.0.3-alpha)

DNF is the fedora package manager, A package manager is a program that makes it's users able to install, update, and uninstall packages
I made my own simple package manager, It uses libcurl to be send requests to the Fedora repos

# **Installation:**

**NOTE: There is already a pre-compiled binary in this program. If you want to compile the program yourself, Use this method**

**Another NOTE: If you don't want to install ```gcc```, You can use ```cc```. It will be the exact same compilation command except ```gcc``` will be ```cc```** 


Arch Linux: ```sudo pacman -S gcc curl```
Fedora: ```sudo dnf install gcc libcurl libcurl-devel```
Debian: ```sudo apt install gcc libcurl4```

# **Compilation:**

On all systems, ```cc -o dnf dnf.c```

# **How to use**

**NOTE: The 'search' mode is not currently available**

```./dnf <mode> <package-name>```

Where mode is either install or download and package-name is the full name of the package in the fedora repos (without ".rpm")

The mode 'download' downloads the RPM of the requested file without installing it and the mode 'install' does the same thing as the 'download' mode but it also uses ```rpm -ivh``` to install the file

A full list of modes can be found in the application by using the ```--modes-list``` option.

The program currently also doesn't have the ability to download required dependencies for the program. Although it will be added in the next release of the program (v0.0.2-alpha)










