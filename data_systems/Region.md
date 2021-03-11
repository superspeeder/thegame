# What does it represent
It represents a region of 32x32 chunks (1024x1024 tiles)

# What does it contain

## This file will contain:
- The region position
- Changes made within the region

## How is it formatted:
> Side Note
> If you want to read it, I suggest using a hex editor. I will write a script that can edit them with python one day but its not done yet

Region Position: 8bytes (32bit signed int x, 32bit signed int y)
Changes: 12bytes (32bit unsigned int x, 32bit unsigned int y, 32bit signed int tile_id)
