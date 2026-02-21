# Niqqa Engine

A vulkan engine made with tears from a masochist with the help of someone who doesn't know one bit about vulkan.

## Installation

Right now the only way to get the executable is to build from source

### build from source

#### Install dependencies

There are only two required dependencies: Vulkan SDK and GLFW 3

##### Ubuntu or Debian
Find `glfw` and `vulkan` yourself

##### NixOS
(Flake required): `nix develop` to at the root of this repo to install all dependencies

#### Building from source
Clone repo
`git clone https://github.com/Vietphogn/duma-thang-ha/`

build with cmake
```
  mkdir build && cd build &&
  cmake .. &&
  make
```
