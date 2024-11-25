# 🐍 Cobra: A Retro Snake Game in C

[![GitHub stars](https://img.shields.io/github/stars/lavradodosilicio/cobra.svg?style=social&label=Stars)](https://github.com/lavradodosilicio/cobra)
[![GitHub forks](https://img.shields.io/github/forks/lavradodosilicio/cobra.svg?style=social&label=Fork)](https://github.com/lavradodosilicio/cobra)
[![GitHub release](https://img.shields.io/github/release/lavradodosilicio/cobra.svg)](https://github.com/lavradodosilicio/cobra/releases)

## 🎮 Game Overview
Cobra is an immersive snake game for Linux, crafted with passion and C programming prowess. Experience a nostalgic journey through retro-style gameplay with innovative features that set it apart from traditional snake games.

![Main Menu Screenshot](https://github.com/lavradodosilicio/cobra/blob/main/screenshots/Captura%20de%20tela%20de%202021-01-07%2018-02-55.png)

## ✨ Standout Features

### 🚀 Cutting-Edge Gameplay
- [x] **Animated Intro:** Stunning ASCII Art animation
- [x] **Retro Menu Design:** Nostalgic user interface
- [x] **Intelligent Enemies:** A* algorithm for "smart" snake opponents
- [x] **Dynamic Obstacles:** Challenging game environment
- [x] **Immersive Sound Effects:** Bass library audio integration

### 🔜 Coming Soon
- [ ] Leaderboard/Records System
- [ ] Customization Options
- [ ] Comprehensive Help Menu

## 🛠 Installation Guide

### Prerequisites
- Linux (Tested on Ubuntu)
- Git
- Basic development tools
- GCC Compiler

### 1. Clone the Repository
```bash
git clone https://github.com/lavradodosilicio/cobra.git
cd cobra
```

### 2. Install Dependencies
#### A* Library
For x86 machines:
```bash
sudo dpkg -i lib/libastar0_0.9-2_i386.deb
```
For x64 machines:
```bash
sudo dpkg -i lib/libastar0_0.9-1_amd64.deb
```

#### BASS Library
```bash
sudo cp lib/libbass.so /usr/local/lib
sudo chmod a+rx /usr/local/lib/libbass.so
sudo ldconfig
```

## 🎮 How to Play

### Controls
- **⬆️⬇️⬅️➡️:** Navigate snake or menu
- **Space:** Pause game
- **Enter:** Select menu option

## 🖼 Gameplay Screenshots
[https://github.com/engjango/cobra/blob/main/cobra-snake-gameplay.mp4](https://github.com/engjango/cobra/raw/refs/heads/main/cobra-snake-gameplay.mp4)
![Intro Screen](https://github.com/lavradodosilicio/cobra/blob/main/screenshots/Captura%20de%20tela%20de%202021-01-09%2020-30-22.png)
![Gameplay Animation](https://github.com/lavradodosilicio/cobra/blob/main/screenshots/Captura%20de%20tela%20de%202021-01-07%2018-02-52.png)
![Game Scene](https://github.com/lavradodosilicio/cobra/blob/main/screenshots/Captura%20de%20tela%20de%202021-01-07%2018-02-42.png)

## 🚀 Quick Start
```bash
cd cobra
make
./cobra
```

## 📦 Dependencies
- libastar (Version 0.9)
- bass (Latest version)

## 🤝 Contributing
We welcome contributions! Please follow these steps:

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

### Contribution Guidelines
- Follow existing code style
- Write clear, commented code
- Include tests for new features
- Update documentation

## 🐛 Reporting Issues
Found a bug? Please open an issue with:
- Detailed description
- Steps to reproduce
- Your environment details

## 🌟 Show Your Support
Give a ⭐ if you enjoyed the game!

## 📄 License
MIT License

## 📞 Contact
- Project Link: [https://github.com/lavradodosilicio/cobra](https://github.com/lavradodosilicio/cobra)
- Creator: @engjango (Jango)

## 🏆 Acknowledgments
- A* Library by Alexios.
- BASS Library by UN4SEE.
