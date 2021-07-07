# cobra
Snake game for Linux and learning C purpose. Cobra is a snake game written in C with and contains a few thousands of lines, it also implements animations, retro menu, snake enemies and sound effects.

![Screenshot main menu](https://github.com/lavradodosilicio/cobra/blob/main/screenshots/Captura%20de%20tela%20de%202021-01-07%2018-02-55.png)

# Features

- [x] Intro animation (animated ASCII Art)
- [x] Menu (retro)
- [x] Sound effects (bass library)
- [x] A* algorithm ("smart" enemies)
- [x] Obstacles
- [ ] Records List
- [ ] Config options
- [ ] Help menu

# Install Dependencies

## Linux (Ubuntu)

```
git clone https://github.com/lavradodosilicio/cobra.git
cd cobra/lib/
```
### A* Library (https://www.bedroomlan.org/projects/libastar/)
For x86 machines, run the code below
```
sudo dpkg -i install libastar0_0.9-2_i386.deb
```
or in case of x64 Machines,
```
sudo dpkg -i install libastar0_0.9-1_amd64.deb
```
### BASS Library (http://www.un4seen.com/)
Now, install the bass library, i.e.,
```
sudo cp libbass.so /usr/local/lib   (to copy bass library into linux lib)
sudo chmod a+rx /usr/local/lib/libbass.so   (to load the lib)
sudo ldconfig  (to autoconfig)
```

# Compile and Run

Once you have the dependencies (see above), run the following commands in your terminal.

```
cd ..
make
./cobra
```

# Controls

* Arrow keys to control the snake direction of movement or select menu option.
* Space to pause.
* Enter to select option.

# Screenshots

![Screenshot intro](https://github.com/lavradodosilicio/cobra/blob/main/screenshots/Captura%20de%20tela%20de%202021-01-09%2020-30-22.png)
![Screenshot animation](https://github.com/lavradodosilicio/cobra/blob/main/screenshots/Captura%20de%20tela%20de%202021-01-07%2018-02-52.png)
![Screenshot intro](https://github.com/lavradodosilicio/cobra/blob/main/screenshots/Captura%20de%20tela%20de%202021-01-07%2018-02-42.png)

# Dependencies

* libastar
* bass
