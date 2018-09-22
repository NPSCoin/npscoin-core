
Debian
====================
This directory contains files used to package npscoind/npscoin-qt
for Debian-based Linux systems. If you compile npscoind/npscoin-qt yourself, there are some useful files here.

## npscoin: URI support ##


npscoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install npscoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your npscoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/npscoin128.png` to `/usr/share/pixmaps`

npscoin-qt.protocol (KDE)

