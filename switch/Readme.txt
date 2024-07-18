Copy the PhantomDogs folder to the switch sd card -> /switch/PhantomDogs/
Get the "Nancy Drew #7 Ghost Dogs of Moon Lake" game files and copy to this folder as well
Should look like /switch/PhantomDogs/DataFiles and /switch/PhantomDogs/HDSound   ...etc
You can copy the whole game folder if you want, but only needs the subfolders to run

run compile.bat to open the devkitpro msys terminal to the current directory.
type 'make'
Should build successfully and spit out a .nro file in this folder
Copy the PhantomDogs.nro to the switch sd card at /switch/PhantomDogs.nro