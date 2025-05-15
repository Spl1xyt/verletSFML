# Verlet Particles with SFML

This is a C++ implementation of a basic particle system using Verlet integration, rendered with SFML. The simulation includes boundary constraints and collision handling between particles, enabling realistic motion within a confined space.

![screen](https://github.com/user-attachments/assets/3e7c964c-b9d2-4db4-8d0d-2243415b062e)

## Supported Platforms

- [x] Linux
- [ ] Windows
- [ ] macOS


## Install dependencies
- Arch:
```sh
sudo pacman -S sfml
```
- Ubuntu/Debian:
```sh
sudo apt install libsfml-dev
```


## How to install and Run ?

1. Download or clone the repository to your computer:
```sh
git clone https://github.com/Spl1xyt/verletSFML.git
```

2. Navigate to the project folder:
```sh
cd verletSFML
```

3. Compile the program:
```sh
make all
```

4. Just start the program:
```sh
./particles
```

## Future Improvements
- [x] Implement spatial partitioning (grid-based)
- [ ] Add multi-threading support
- [ ] Support circular boundary shapes
- [ ] Enable interaction: move particles with the mouse
