# cub3D

## Description

This project's goal was to write our own "Wolfenstein 3D"-like game

Read the [project's PDF](https://github.com/m3tra/11_cub3D/blob/master/en.subject.pdf) for more info

## Running the program

Make sure you have dependencies installed

```sh
# For debian-based distros:
sudo apt install xorg-dev libbsd-dev
```

To run the project:

```sh
chmod +x ./lib/minilibx-linux/configure

make && ./bin/cub3D
```

## Cleaning up

To remove all files from the build process:

```sh
make clean_all
```
