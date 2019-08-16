# Jerry-Rig

## UPDATE
Jerry-Rig is now discontinued. Handbrake over the years has evolved much since the last time I used it in 2012. As it stands now, handbrake produces almost the exact same output as Jerry-Rig in terms of quality. The key difference between Jerry-Rig and handbrake is that handbrake does the same job **much** faster. For example on a threadripper based system, encoding a high quality bluray will take around 3 hours on Jerry-Rig. With handbrake an equivalent file can be made in 20 minutes. There is no longer a need for Jerry-Rig.

---------------


A GUI wrapper for both FFMPEG and LibAv to help my friend Jerry compress videos. Its basically like handbrake, except the output isn't garbage.

![Main screen](https://random-hackery.net/gitImages/Jerry-Rig/jrMain.png) 

***
## Features
- batch renders!
- x264 encoding

***
## How to Build
Jerry-Rig was created using QT 5. As such building is quite simple. 

Prereqs:

- QT5
- FFMPEG or LibAV
- libx264

To Build:

run

	qmake
	make

Installer package coming soon....


