standard project
cd build
cmake ..
make

generate xcode project
cd "build XCode"
cmake -G Xcode ..

normal make needs to "make install" with the bundle utils thing
frameworks folder needs SDL2.framework SDL2_image.framework SDL2_mixer.framework SDL2_ttf.framework

TODO: add some sort of check if missing assets, exit
IMPORTANT: Mac is the only platform whereby includes have to have a forward slash
Correct:   #include <Engine/Button.h>
Incorrect: #include <Engine\Button.h>