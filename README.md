RiverModel written in C++ - Version 2.0
===================================

Purpose
-------

RiverModel is a cross-platform simulator for the carbon flow in the Mississippi river. The first model was written in NetLogo(see http://ccl.northwestern.edu/netlogo/) and it took 4.5 days to simulate a year of carbon flow in the river. 

The goal of the 2011 USGS team was to reduce the runtime to ~1 hour while preserving the same functionalities.  They implemented the new version in C and used Python for the user interface. This version modified the flow timestep from five seconds to one minute which reduced the runtime to about ~10 hours to simulate a year long of carbon flow.

The 2012 USGS team was primarily tasked with gui improvements and adding some new functionality to the model.  However, in the course of making these improvements we removed python in favor of the QT framework for GUI development, moved to Object Oriented C++, resolved some of the fundamental flaws we found in the existing flow logic, and refactored the model to improve data locality and take advantage of multicore processing.  These changes allowed the simulation of a year's data in under an hour and allowed us to quickly prototype our UI in a graphical editor. 

Table of Contents
-----------------

* [Requirements](#requirements)
* [Running the Model](#running)
* [Implementation](#implementation)
* [Testing](#testing)
* [Team](#team)

<a name="requirements"/>
Requirements
------------

You will need the following components to run/modify RiverModel:

1. The QT 5.0.2+ framework

<a name="running"/>
Running the Model
-----------------

You can run the GUI model as follows:

On linux:
```
pwd
> /Users/<username>/USGS2012/main
qmake RiverModelGUI.pro
make release
cd ..
./Rivermodel
```

On Windows:

1. Open the RiverModelGUI.pro file in <ProjectRoot>/main with QTCreator.
1. Change the build mode from debug to release
1. Click the button to build and run

Note, it is also possible to build the program from the commandline on windows, but you will need to add certain QT directories to your system path.

<a name="implementation"/>
Implementation
--------------
Please read our massive project report on the Senior Project wiki.  It should (hopefully) answer most questions about the design decisions we made.

<a name="testing"/>
Testing
-------
Drew wrote testcases to verify various parts of the model including the correctness of the new flow algorithm.  Please add more tests to ensure the model is accurate and useful to the USGS researchers.

You can run the tests as follows:
```
cd <Project Root>/
qmake
make check
```


<a name="team"/>
2012 Team
----
1. Bill Bindi: billdbindi@gmail.com
1. Drew Cross: drew.cross@outlook.com
1. Grace Link: link3@illinois.edu
1. Eric Parsons: ecp@outlook.com

2011 Team
----
1. Efe Karakus: efekarakus@gmail.com
1. Nathan DeGrand: degrand1@illinois.edu
1. Tom Loboda: loboda1@illinois.edu
1. Chris Freund: freund3@illinois.edu
