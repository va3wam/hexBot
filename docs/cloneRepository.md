# Cloning the HexBot Repository

This page walks you through how to clone the HexBot GitHub repository to your local Git repository. 

If you are new to making VA3WAM projects and wish to emulate the local directory structure that we use then please read 
[this](https://va3wam.github.io/versionControl/#local-directory-setup).

## Step by step instructions

1. In a terminal window, navigate to the root of your local Git project directory. ```cd .../VisualStudioCode/PlatformIO/Projects```
2. Clone the remote origin server. ```git clone https://github.com/va3wam/hexBot.git```
3. Confirm that you now see a sub-directory off your local project directory named *hexBot*. 
4. Go into the hexBot directory (if you are not already there) and issue the command ```git remote```. If you get back the response *origin* then jump to step 6. If you get a blank response back then proceed to step 5.
5. Issue the command ```git remote add origin https://github.com/va3wam/hexBot.git``` to set up the remote. Now repeat step 4. 
6. At this point you have successfully cloned the Hexbot repository. Now you need to set up your PlatformIO IDE.

# Set up PlatformIO

1. In the hexBot directory create a file called platformio.ini.
2. Copy the content of the appropriate platform template from the [AA](/AA) directory. For MAC use [*platformIO-MAC-example.txt*](/AA/platformIO-MAC-example.txt).
3. Open Visual Studio Code. Make sure that there are no active projects or files open.
4. Navigate to the PlatformIO splash screen (use the house icon in the bottom left bar). Make sure that there are no active projects or files open.
5. Click the open project button.
6. Navigate to the hexBot directory.
7. Click the Open "hexBot" button. 
8. If you wish to work on this repository you will need to click the "Yes I trust the authors" button.
9. Assuming everything has gone well you are all set up with a local repository and an associated remote origin and you are ready to start developing your additions to the repository.

NOTE: Please do not work in the main branch but rather create branches in which to work. You can read about our prefered workflow [here](https://va3wam.github.io/versionControl/#git-workflow).

# Visual Studio Code Plugins

A quick note on Visual Studio Plugins. We recommand that you install the following:

1. [PlatformIO](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) (embedded system IDE).
2. [GitHub Pull Requests and Issues](https://marketplace.visualstudio.com/items?itemName=GitHub.vscode-pull-request-github) (Perform github tasks from VCS). See [this article](https://code.visualstudio.com/docs/editor/github).
3. [GitLens](https://marketplace.visualstudio.com/items?itemName=eamodio.gitlens) (shows full commit history inline in VSC). 
