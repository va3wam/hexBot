<!-- Cloning Instructions -->
<span style="background-color: green">
This is a template repository to be cloned when making a class intended to become part of the Aging Apprentice API (3API) class library. Instructions for using this template repository are as follows.  

## Make repo on Github
- Navigate to the Aging Apprentice template repo [here](https://github.com/theAgingApprentice/aaTemplate).
- Click the Use this template button.
- Follow the online instructions.
- Be sure to click the *include all branches* option.

## Make local repo
- Navigate to the project folder on your local hard drive.
- Issue the command `git clone https://github.com/va3wam/{project name}`
- Navigate into the newly created directory `cd {project name}`
- ~~Create a local gh-pages branch to host Doxygen output~~
   - ~~Issue the command `git checkout --orphan gh-pages`~~
   - ~~Issue the command `git reset --hard`~~
   - ~~Issue the command `git commit --allow-empty -m "Initializing gh-pages branch"`~~
- Invite new contributors if required to do the next steps. 
   - Go to your new Github repo with yoour browser.  
   - Settings/Manage Access/Invite a collaborator/enter name.
- ~~Push local gh-pages branch to origin on Github.~~ 
   - ~~Back on local machine issue the command `git push origin gh-pages`.~~
   - ~~Issue the command `git checkout main`.~~
- Move *template/use-this-platformio.ini* file to root of your local repo.
- Rename *use-this-platformio.ini* to *platformio.ini*.
- Delete *template* folder.
- Open project in PlatformIO.
   - Start Visual Studio Code. 
   - Start PlatformIO.
- Open project.

## Edit Doxyfile
There is a file called Doxyfile in the root of the repository. Make the following edits.
- PROJECT_NAME           = {project name}
- PROJECT_BRIEF          = "Brief explanation of what class does."

## Source Files
Write the library using the tempates provided in the src directory off of the root of this repo.

## Examples
Write at least one example script using the template in examples/simpleExample off the root of this repo. 

## Edit this README.md file
* The basic edits that you should make to this README file are noted below in bold text labelled **Edit 1** through **Edit 7**. You may wish to make additional edits as you see fit.
* Once you are done with these instructions you can delete them starting from the top of the file and ending with the line below. What remains will be a well formatted README file. 

<!-- This is where your README file starts. Delete everyth0ing above -->
---
</span>


[![LICENSE](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/mmistakes/minimal-mistakes/master/LICENSE)
[![Doxygen Action](https://github.com/theAgingApprentice/aaChip/actions/workflows/main.yml/badge.svg?event=push)](https://github.com/theAgingApprentice/aaChip/actions/workflows/main.yml)

**Edit 1 - update title**

# Put your title here 

## Table of contents
* [Overview](#Overview)
* [Dependencies](#Dependencies)
* [Author(s)](#Author)
* [Development environment](#Development-environment)
* [Code documentation](#Code-documentation)
* [Microprocessor compatibility](#Microprocessor-compatibility)
* [Installing](#Installing)
* [Running tests](#Running-tests)
* [Releases](#Releases)
* [Acknowledgements](#Acknowledgements)

## Overview
**Edit 2 - Update this block of text with an explanation of what the class you are making does. For example:** 

This repository contains an Arduino class that does winderful things. This is part of a series of classes 
made to support a standard set of APIs for experimental robot platforms. 

## Dependencies
This class depends on <a href="https://github.com/espressif/arduino-esp32">
Arduino.h</a> being present on your system. This is the Arduino core library
that comes bundled with PlatformIO.

**Edit 3 - Add other dependencies here.**

## Author
Written by Old Squire for the Aging Apprentice.

**Edit 4. Update author information above and remove this line.**

## Development environment
This library was written using the following tools:
* [<img src="/img/vscLogo.png" width="15" height="15">](https://code.visualstudio.com/docs) 
Microsoft's Visual Studio Code source code editor. 
* [<img src="/img/pioLogo.png" width="20" height="15">](https://platformio.org/) 
PlatformIO plugin 
[embedded software](https://en.wikipedia.org/wiki/Embedded_software) application 
[IDE](https://en.wikipedia.org/wiki/Integrated_development_environment). 

<span style="color:green">suggestion:</span> If you are using the standard 
Arduino IDE for your project then you should probably avoid using this library 
unless you are comfortable navigating the subtle differences bewteen how your 
envoronment bahaves and how the environment used to create this library behaved.

## Code documentation
As part of our CI/CD software development process we use 
[Github Actions](https://docs.github.com/en/actions) to automatically generate
up-to-date documentation via [Doxygen](https://www.doxygen.nl/index.html) every 
time the **main** branch gets updated. The output from Doxygen is placed in the 
**root** diretory of the **gh-pages** branch. This repository has an associated 
[Github Pages](https://pages.github.com/) site that contains all of the Doxygen
tags and assorted embedded comments from the code itself. This documentation 
can be viewed in your web browser 
**Edit 5 - Update URL {projectName} for Doxygen online docs**
[here](https://theagingapprentice.github.io/{projectName}/html/index.html).    

## Microprocessor compatibility
This library has only been tested on the [Adafruit Huzzah32](https://learn.adafruit.com/adafruit-huzzah32-esp32-feather) development board containing the [Espressif ESP WROOM32 SOC](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf) featuring a pair of [Cadence/Xtensa®32-bit LX6 microprocessors](https://mirrobo.ru/wp-content/uploads/2016/11/Cadence_Tensillica_Xtensa_LX6_ds.pdf). 

## Installing
These instructions assume that you have [Git](https://git-scm.com/) installed on 
your computer.

1. Navigate to the Arduino project directory on your computer.
2. Issue the command `git clone https://github.com/theAgingApprentice/{projectName.git}`.
3. Issue the command `git remote`. If you get back the response *origin* then 
you are all set. If you get a blank response back then you must set up an 
association to the remote repository by issuing the command `git remote add 
origin https://github.com/theAgingApprentice/{projectName.git}` to set up the remote. 

## Running tests
As part of our CI/CD software development process we want to run automated tests 
every time new code is pushed to the main branch. To date we have not managed to
do this though we have experimented with the PlatformIO C/C++ unit testing tool 
called [unity](https://github.com/ThrowTheSwitch/Unity). We have a dummy script
called [test_main.cpp](test/test_main.cpp) located located in the test directory 
off the root of the repository. This test does nothing useful at the moment and
it may not even make sense to run tests on a class such as this. Full 
instructions on how to write and run these test can be found on the PlatformIO 
website 
[here](https://docs.platformio.org/en/latest/tutorials/espressif32/arduino_debugging_unit_testing.html#writing-unit-tests). 
If you wish to run the tests you must do so manally while in Visual Studio Code 
and PlatformIO:

1. Click the PlatformIO Icon in the Visual Studio Code Activity bar along the left
hand side of your screen.
2. Expand the Advanced menu item.
3. Click the Test menu item.

The tests will then run and show you results like this.

```
test/test_main.cpp:58:test_string_concat        [PASSED]
test/test_main.cpp:59:test_string_substring     [PASSED]
test/test_main.cpp:60:test_string_index_of      [PASSED]
test/test_main.cpp:61:test_string_equal_ignore_case     [PASSED]
test/test_main.cpp:62:test_string_to_upper_case [PASSED]
test/test_main.cpp:63:test_string_replace       [PASSED]
-----------------------
6 Tests 0 Failures 0 Ignored
==================================== [PASSED] Took 13.70 seconds 
Test    Environment    Status    Duration
------  -------------  --------  ------------
*       featheresp32   PASSED    00:00:13.699
==================================== 1 succeeded in 00:00:13.699 
```

We are also looking at PlatformIO's support of 
[Github Actions](https://docs.platformio.org/en/latest/integration/ci/github-actions.html) 
to see what can be accomplished for Arduino projects. We do not want to pay to 
use TravisCI. 

## Releases
* We use the [SemVer](http://semver.org/) numbering scheme for our releases. 
* The latest stable release is [v1.0.0](https://github.com/theAgingApprentice/{projectName}/releases/tag/v1.0.0). **Edit 6 - replace {projectName}** 

## Examples
There is an [example sketch](https://github.com/theAgingApprentice/{projectName}/blob/main/examples/simpleExample/simpleExample.cpp) that shows you how to use this class. **Edit 7 - replace {projectName}**  

## Acknowledgements
* The many folks involved in porting the Arduino libraries over to the ESP32 SOC.
* Adafruit for their excellent freely available tutorials.
