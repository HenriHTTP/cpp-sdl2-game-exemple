# About Project

This project is a game exemple made in SDL2 and GLEW.This project using interfaces for implement class also use structs. 

# Dependencies Project

## Installing clang-format

Open the terminal.

- Update the package list with the command:

```bash
sudo apt-get update
```

- Next, install clang-format with the command:

```bash
sudo apt-get install clang-format
```

- After the installation is complete, you can check the installed version with the following command:

```bash
clang-format --version
```

## Installing cmake

- Open the terminal.
- Update the package list with the command:

```bash
sudo apt update
```

- Next, install cmake with the command:

```bash
sudo apt install cmake
```

- After the installation is complete, you can check the installed version with the following command:

```bash
clang-format --version
```

## Installing SDL2

Open the terminal.

- Update the package list with the command:

```bash
sudo apt-get update
```

- Next, install SDL2 with the command:

```bash
sudo apt install libsdl2-2.0-0 libsdl2-dev
```

- After the installation is complete, you can check the installed version with the following command:

```bash
sdl2-config --version
```

## Installing GLEW

Open the terminal.

- Update the package list with the command:

```bash
sudo apt-get update
```

- Next, install GLEW with the command:

```bash
sudo apt install libglew-dev
```

- After the installation is complete, you can check the installed version with the following command:

```bash
glewinfo
```

# Debug and build project

- Open the terminal inside this project
- Create a build folder with the command:

```bash
mkdir cmake-debug
```

- To enter inside the cmake-debug folder with the command:

```bash
cd cmake-debug
```

- For build project inside the cmake-debug folder with the command:

```bash
cmake ..
```

- For gerate binary project inside the cmake-debug folder with the command:

```bash
make
```

- Execute project with the command:

```bash
./SDL2_OpenGL_Demo
```

# visual studio code configurations

## settings.json

**for use this configuration in your vscode are you do need install clang-format**

- linux exemple:

```json
//linux
{
  "editor.formatOnSave": true,
  "C_Cpp.clang_format_path": "/usr/bin/clang-format",
  "C_Cpp.clang_format_style": "Google"
}
```
