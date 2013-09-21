DDO Quest Helper
============================

This is just a little program that lets you keep track of what quests you have completed in DDO, and at what difficulty.

It only handles heroic free to play quests at the moment, but room is there to expand if anyone wants to add further capability later. I'll probably do it if I ever make it that far in DDO.

Quest data was taken from http://ddowiki.com/page/Guide_to_Free_to_Play , and the data should be current for Update 19 Patch 1.

Problems:
----------------------
You can edit more fields than you should be able to, so only edit the column to do with what difficulty you have completed the quest on.

You have to click on the difficulty cell twice to get the dropdown to appear.


Compiling Instructions:
----------------------

Linux:

Dependancies (take these with a grain of salt, I havn't checked these exactly):
For Debian/Ubuntu

- libqt4-core
- libqt4-gui
- libqt4-sql
- libqt4-sql-sqlite

To compile you will also need:
- qt4-qmake
- libqt4-dev

For Arch:
- qt-4

In the folder run qmake && make. In some cases due to qt4 being out of date, you may need to run qmake-qt4 && make instead.

Windows + OSX:
No idea

License
-------

DDO Quest Helper is copyrighted free software made available under the terms of the GPLv3

Copyright: (C) 2013 by apocolypse600. All Rights Reserved.
