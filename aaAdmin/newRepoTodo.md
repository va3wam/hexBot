Back to [README](https://github.com/theAgingApprentice/icUnderware/blob/main/README.md)
---

This document contains a 'to do list' of actions to take to start your project using the icUnderware template repository. ```These instructions assume that you have Git installed on your machine and were written using a Mac. It may be that procedures on Windows and Linux machines differ slightly.```

## Process Overview

The following is a brief list of the steps you must take in order to make use of this template repository. Some of the more involved steps include links to a section further down in this document with greater details. 

1. Clone the [icUnderware repository](#Cloning-the-template).
2. Make a [local repo](#Making-a-local-repo).
3. Edit the [Doxyfile](#Editing-the-Doxyfile).
4. Edit the [README.md](#Edit-the-READMEmd-file).
5. Move/rename ```./aaAdmin/platformio.ini.temp``` to ```./platformio.ini```.  
6. Curate the [Github labels](#Curating-the-Github-Labels) in the new repository.
7. [Next steps](#Next-steps).

## Cloning the template

- In your web browser, navigate to the Aging Apprentice template repo [here](https://github.com/theAgingApprentice/icUnderware).
- Click the ```Use this template``` button.
- Follow the online instructions.
- Be sure to click the ```include all branches``` option.
- Invite new contributors if required to do the next steps. 
   - Go to your new Github repo with your browser.  
   - Settings/Manage Access/Invite a collaborator/enter name.
- Click on the ```Code``` button then click on the clipboard icon to copy the URL. 

## Making a local repo

- Get into Visual Studio Code terminal window with no projects open.
- Navigate to the project folder on your local hard drive.
- Issue the command `git clone https://github.com/theAgingApprentice/{project name}` (you can paste the URL that you copied in the previous step)
- Navigate into the newly created directory `cd {project name}`
- Rename **template_platformio.ini_tmp** to **platformio.ini** in the root of your repo.
- Open project in PlatformIO.
   - Start Visual Studio Code. 
   - Start PlatformIO.
- Open project.
## Editing the Doxyfile

There is a file called Doxyfile in the root of the repository. Make the following edits.
- PROJECT_NAME           = {project name}
- PROJECT_BRIEF          = "Brief explanation of what class does."
## Edit the README.md file

Update the README.md file to reflect what your project is all about. 
## Curating the Github Labels

```This process only works on unix systems. A windows script could be made to do this on windows machines```. Github uses [Labels](https://docs.github.com/en/issues/using-labels-and-milestones-to-track-work/managing-labels#about-labels) to provide extra meta data for [Issues](https://docs.github.com/en/issues/tracking-your-work-with-issues/about-issues). It is a good practice to link Issues when merging a branch to main. The default list of Labels that come with a new generic repository are a bit limited. The icUnderware template repository has an easy solution for replacing the standard Labels with a curated list of Labels. In order to use our curated list of Github Labels do the following:

1. Create a Github [personal access Token](https://github.com/settings/tokens). Be sure to select REPO scope. Save the token somewhere safe as you cannot find it again once you close the tab. 
2. Navigate to the aaAdmin directory of the new local repository that you created.   
3. In the bash shell script *updateGithubLabels*, change the targetGithubName value to your Github name.
4. Make sure that the bash script is an executable (chmod u+x updateGithubLabels).
5. Run the script: ./updateGithubLabels taregtRepoName githubPersonalToken 
6. If all goes well you should see 
   - A bunch of messages scroll by in your terminal.
   - In the issues tab of your code repoitory click the Labels button and you should see the curated list of labels. 

# Next steps

Congratulations, you can now start working on your new project! Note that the repository you are using makes use of a number of Github features that you may not be all that familiar with. If you are having trouble getting somethng to work for you check out the [helpful hints](helpfulHints.md) page.
