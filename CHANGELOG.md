## 0.1.2

- SDL include to allow Windows users to compile and use the project 
- Use SDL functions for tan, sin, cos, modulo and floor
- Refactor to improve memory allocation of objects
    - Some objects already had allocated memory for
- Refactored make file to allow other platforms to use it

Thank you to [skeeto](https://github.com/skeeto) for pointing this out, and show how I could fix it!

## 0.1.1

- Rendering floor and roof (simple color)
- Improved docs and code readability 
- Render wolfenstein wall textures

## 0.1.0

Created the prototype with Javascript (git ignored)
This version has a minimal working version of the C implementation with SDL. It features:
- Rendering white walls
- Shadow on the fall depending on vertical hit or not
- Black background (no floor or roof)
- Scalable minimap
- Player are rendered in the minimap
- Rendering FOV of the player in the minimap 