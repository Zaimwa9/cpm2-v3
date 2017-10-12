Coding exercise Language: C

The goal is to create a PM2 process manager like in C.

Features

This CPM2 will have to handle some basics feature of the real PM2:

Daemonization of binaries (fork) 
Auto restart of exited binary Start / Restart / Delete of script 
Basic process listing 
CLI UX

Here is how the CLI should look like:
```
Start the CPM2 Daemon in background
$ cpm2 daemon_start

Send the my_ls path to the CPM2 daemon and fork it, output logs anywhere you like
$ cpm2 start ./my_ls

Communicate with CPM2 daemon and retrieve currently running processes
$ cpm2 list

Restart application
$ cpm2 restart my_ls

Stop, kill application
$ cpm2 delete my_ls

Kill CPM2 Daemon
$ cpm2 kill
```
