# Cloning the HexBot Repository

This page walks you through how to clone the HexBot GitHub repository to your local Git repository. 

```If you are new to making VA3WAM projects and wish to emulate the local directory structure that we use then please read [this](https://va3wam.github.io/versionControl/#local-directory-setup).```

## Step by step instructions
1. In a terminal window, navigate to the root of your local Git project directory. ```cd .../VisualStudioCode/PlatformIO/Projects```
2. Clone the remote origin server. ```git clone https://github.com/va3wam/hexaBot.git```
3. Confirm that you now see a sub-directory off your local project directory named *hexaBot*. (Note the robot name chnaged from hexabot to HexBot but the repo reference had already been made. Sorry for the confusion).
4. Go into the hexaBot directory (if you are not already there) and issue the command ```git remote```. If you get back the response *origin* then jump to step 6. If you get a blank response back then proceed to step 5.
5. Issue the command ```git remote add origin https://github.com/va3wam/hexaBot.git to set up the remote. Now repeat step 4. 
6. Assuming everything has gone well you are all set up with a local repository and an associated remote. At this point you can start developing your additions to the repository.

Please do not work in the main branch but rather create branches in which to work. You can read about our prefered workflow [here](https://va3wam.github.io/versionControl/#git-workflow).
