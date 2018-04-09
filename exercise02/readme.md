Exercise 02: git
-----------------

The goal of this exercise is to use git to control the source of a simple command line C++ application.

Prerequisites:

* You have completed ``Exercise 01: Setup`` and have a working command line with compiler and git accessible. 
* You have read through Chapter 1 of the [Pro Git Book](https://git-scm.com/book/en/v2).

Steps:

1. Create a working directory somewhere on your computer. Open your command line terminal and make a working directory. Then change to that directory.
2. Clone the assignment for today. 
3. Change to the repository directory. Write a program in ``hello.cpp`` to print "Hello World!" to standard output.
4. Add the ``hello.cpp`` file to the index

	```
	git add hello.cpp
	```
5. Commit the change with a message

	```
	git commit -m "Added hello program"
	```
6. Use git log to see the results

	```
	git log
	```
7. Change the program to add another line of output "My name is <name>", wher e<name> is your name.

8. Add the change to the index

	```
	git add hello.cpp
	```
   
9. Use git status to see the state of the repository

	```
	git status
	```
   
10. Commit the change with a message

	```
	git commit -m "Added my name."
	```
11. Use git log to verify the results

	```
	git log
	```
12. Use git push to synchronize the repository with that on GitHub

	```
	git push
	```
	You will have to enter your GitHub username and password.

**This is how you will turn in exercises and project code in this course**.
