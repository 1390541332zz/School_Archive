Exercise 03: vagrant
---------------------

The goal of this exercise is to learn how to use Vagrant to setup and use a virtual environment.

Prerequisites:

* You have completed ``Exercise 01: Setup`` and have a working installation of VirtualBox and Vagrant 
* You have read through the [Vagrant Getting Started](https://www.vagrantup.com/docs/getting-started/) guide.

Steps:

1. Create a working directory somewhere on your computer. Open your command line terminal and make a working directory. Then change to that directory.
2. Clone the assignment for today after accepting the Github invitation at the link above. 

	```
	git clone https://github.com/ECE3574Fall2017/exercise03-USER.git
	```
	where USER is your GitHub username. You will have to enter your GitHub username and password. 
	
3. Change to the repository directory and look at the contents of the ``Vagrantfile``. Write a simple C++ hello world program in  ``hello.cpp``. Add it to the git index and commit it as in exercise 02.

4. Run vagrant to setup the virtual machine.

	```
	vagrant up
	```
	This will take a few minutes to complete.
	
5. Login to the machine.

	```
	vagrant ssh
	```
	You are now at the command line inside the Linux virtual machine.
6. See what directory you are in

	```
	pwd
	```
You are in the /home/ubuntu directory. This is the home directory for the default user setup by Vagrant.

7. List the files in the host operating system shared with the machine.

	```
	ls /vagrant
	```
You should see the files ``Vagrantfile`` and ``hello.cpp``, and a log file created by Vagrant.

8. Compile the hello file using the g++ compiler installed by Vagrant when it setup the machine

	```
	g++ -o hello.exe /vagrant/hello.cpp
	```

9. Run the executable you just built.

	```
	./hello.exe
	```
It should print a familiar message.

10. Logout of the machine

	```
	logout
	```
You are now back in your host terminal, but the machine is still running!

11. Edit the ``hello.cpp`` file using for favorite editor to change the message printed. Log back into the machine, compile, and run as above. Then logout.
12. Now, halt the machine.

	```
	vagrant halt
	```

13. Since we no longer need the machine we can destroy it.

	```
	vagrant destroy
	```
	It prompts you to be sure.

14. Now, use git to commit the source file you changed to the local repository.

	```
	git add hello.cpp
	git commit -m "Changed the message printed"
	```

15. Finally, use git push to synchronize the repository with that on GitHub

	```
	git push
	```
	You will have to enter your GitHub username and password.

You have completed the Exercise.

**This is the basic process for verifying your code works as you expect in the grading environment.**


