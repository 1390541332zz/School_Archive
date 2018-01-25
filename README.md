# MSP432 Mistery Color Program Instructions

The objective of this quiz is a dry-run to check out a project from GitHub into CCS, make some changes to it, and upload the resulting changes back to GitHub. You will use this procedure to implement labs and an occasional homework in ECE 2534. Before you start, make sure you have CCS installed.

## Preparatory steps: Downloading and compiling the program

1. Copy the link to this repository
2. Import the link as a project in CCS (refer to the CCS installation instructions if you do not recall the procedure).
2. Compile the program in CCS and download it to the board using the CCS debugger
3. Observe the color of the LED on the board when the program is running

## Making changes and adding a file

4. In the C source code, adjust the comments: add your name, as well as the color you have observed
5. Using your smartphone, take a picture of the board while the LED is on. Upload the picture to your Desktop
6. In CCS project explorer, right-click this project and select 'Add Files ...'
7. Select the picture from your Desktop, and add it to your project. Select 'Copy Files' in the popup menu.

## Uploading changes to GitHub

8. In CC project explorer, right-click this project and select 'Team ...' - 'Commit'
9. In the Git Staging Popup window, drag files from 'Unstaged Changes' into 'Staged Changes'. 
If you did the previous steps correctly, you would see two files in the Unstaged Changes list: main.c and the picture you have added to the project.
10. In the 'Commit Message' pane of the Git Staging Popup window, add a comment that describes your change. 
For example: 'I am completing Quiz 3!'
11. Press 'Commit and Push'
12. Observe the new popup window closely. It should indicate that both files have been sending back to GitHub
13. Refresh the Github.com repository of this project in your browser. Verify that your changes were correctly uploaded.
14. That completes the quiz. You don't have to submit anything on canvas. The commit time of your upload will count as the turn-in time.
