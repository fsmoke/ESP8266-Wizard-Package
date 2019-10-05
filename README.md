# ESP8266-Wizard-Package
Esp8266 visual studio add-in

Originally forked this add in https://bbs.espressif.com/viewtopic.php?t=3577
All copyrights saved.

# Fixes in this version

* Removed VsixInstaller and dependencies from setup script, instead used regkey to determine vs2017 path to run native VsixInstaller
* Fixed irom flash address for NON-OS SDK 2.X.X(and above) versions (was 40000, must be 10000)
* Removed old version of Visual studio(2013, 2015)
* Replaced some graphical files
* Reorganization of project directories(to avoid building to source directory)
* Removed source code from distrib, instead source code can be retrieved from here(source link add to distrib)
* Added new versions NON-OS SDK

# TODO for future versions

* Add new versions of RTOS SDK
* Add support vs2019
* May be return support vs2015
* Rewrite some code templates to support new mamory map declaration (NON-OS SDK 3.X.X)
