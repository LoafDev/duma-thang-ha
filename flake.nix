{
  description = "C++ projects";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/master";
  };

  outputs = { nixpkgs, ... }:
  let
    system = "x86_64-linux";
    pkgs = nixpkgs.legacyPackages.${system};
  in {
    devShells.x86_64-linux.default = pkgs.mkShell { nativeBuildInputs = with pkgs; [
      clang
      cmake
      glfw

      # vulkan
      vulkan-headers
      # vulkan-loader
      # vulkan-validation-layers
      # vulkan-tools
      # shaderc
    ];};
  };
}
