## About
Core Wars is a programming game in which two or more programs run in a simulated virtual machine with the goal of terminating 
every other program and surviving as long as possible. Corewar is project of algorithmic branch at Unit Factory school same as
42 school. More about corewar game at (https://en.wikipedia.org/wiki/Core_War)
Known as Warriors, these programs are written in an assembly language, some of them are located in "resourses" folder to run
these things now.

## Implementation
This Core War follow directives to our specific task, that means it's project a little different fom original Core War. It's 
included more different instructions and each process has their own registers. 
(https://docs.google.com/spreadsheets/d/1SUyQ436oSkVOP07g-zQTM7NeTfxs_Fam2Iky7Cmd3A0/edit#gid=2052301650)

There how it's look at visual mode with ncurses:
![Alt text](https://media.giphy.com/media/KYoOENOLHJ2MJNb76j/giphy.gif "Vis mode")

You can see there:
- Game board: it's memory of our virtual machine 64x64 grid of bytes
- Warriors: small programs each of them has their own color, white color is the blank memmory
- Cursors: it's not belongs to Warriors, but it's how read instructions of Warriors and trigger to execute their instruction
		   code. Cursors movements with inverted color, jumps according to Warriors instructions specific.

There main rules to determines who wins:
- CYCLE_TO_DIE: cycles, the machine needs to make sure that each process.has executed at least one live since the last check. A 
				process that does not abide by this rule will be killed immediately. When cycles of the gamereaches to 
				CYCLE_TO_DIE value game decrease CYCLE_TO_DIE value and next round to CYCLE_TO_DIE will be shorter for cursors
				movements.
- Lives: when cursor reaches to 01 cell it's will be to trigger to count appropriate number lives

## Build
This will be work on Linux or MacOs terminal:

   Release build:

```
$ make
```
	
   Compile of Core War programs you  can add max 4 Warriors in one battle and also you can add 4 times this Warrior and there will be start fight against one each other:

```
$ ./asm resourses/Gagnant.s.s 
```
	
   and another one, or other whatever you like in that folder:

```
$ ./asm resourses/zork.s
```

There some keyboard events for game process,SPACE to start/stop game, +/- keys in right side of keyboard, CTRL+C to exit game if
you not like wait to end of the game. It's IMPORTANT open terminal on full screen for run visual mode! So execute command:

```
$ ./corewar -v resourses/Gagnant.s.cor resourses/zork.cor
```

There some commands for arguments

```
$ ./corewar
```