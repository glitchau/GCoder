
## Overview
**GCoder v0.1** is a windows based custom GCODE creator/editor

Initially designed to generate tool paths for welding 18650 battery to nickel strips using a KWeld.

## Dependancies
Using VCPkg install:
- QT5
- Boost
- yaml-cpp

## Building GCoder

    git clone https://github.com/glitchau/GCoder.git
    Open GCoder/CMakeList.txt in visual studio 2019
    Build
    Copy GCoderParameters.yaml to your build folder (this is hardcoded to be next to the GCoder.exe and is required)
    Edit GCoderParameters.yaml if required
    Open GCoder.exe
    
    
## Notes
1. The core piece of this software doesn't require Boost and can be removed quite easily
2. The code includes a lot of print outs used for debugging
3. Feel free to contact me if you want to update or work on this code 
