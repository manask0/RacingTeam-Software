ROS is not an actual OS, but a middleware. 

Why ROS is not an OS. 
OS is the lowest level software that controls hardware, manages system resources, provides foundation on which all other software runs. It must manage processes (schedule cpu time, context switching, preemption, handle multitasking), manage memory (allocate ram, segmentation, prevent one program from accessing another's memory). ROS is not an OS since it doesn't work without LINUX.


ROS uses nodes (small programs that each do one node like camera node which publishes images).
How nodes communicate - they need continuous data streams, quick questions, tasks that take time and give feedback. There are 3 communication models - 
a) Topic - named data stream. One node publishes, many nodes subscribe and data flows continuously. No direct connection between sender and receiver. Sender does not know who is listening. No confirmation and no reply. Used for sensor data, state updates and commands that update often.  Asynchronous. No structure. 
b) Services - Requests / Response. One to one, client sends request and server sends response. Synchronous. (ie one thing waits for another to finish before continuing). Blocks thread for too long if server takes time to respond.  ( **A thread is just “one line of execution” — one sequence of steps being followed in order.**)
c) Actions - Long running tasks with feedback. An action includes a goal, feedback (continuous), result and cancel support. eg 

Goal: Go to (x=10, y=5)
Feedback: 30% complete
Feedback: Avoiding obstacle
Result: Reached destination

Services can't be used for sensor data because services are one-one but we often want multiple receivers for sensor data. Also, services require every request to be responded to but for sensor data, old data is useless so we want missed data --> move on. 

### ROS Humble Hawksbill 
Distribution of ROS 2 (version)
need to run source /opt/ros/humble/setup.bash every time we want to use ros.

ROS 2 nodes on the same domain can freely discover and send messages to each other, while ROS 2 nodes on different domains cannot. for safety, choose 0-101. (read up why later) #later

(note - if apartment is like os, port is like door number ie tells where exactly data from the network should go to)

rqt is a graphical user interface (GUI) tool for ROS 2. Everything done in rqt can be done on the command line, but rqt provides a more user-friendly way to manipulate ROS 2 elements.


ros2 run turtlesim turtlesim_node to run turtlesim.



A ROS workspace is a directory with a particular structure. Commonly there is a `src` subdirectory. Inside that subdirectory is where the source code of ROS packages will be located. Typically the directory starts otherwise empty.
colcon does out of source builds. By default it will create the following directories as peers of the `src` directory:

- The `build` directory will be where intermediate files are stored. For each package a subfolder will be created in which e.g. CMake is being invoked.
    
- The `install` directory is where each package will be installed to. By default each package will be installed into a separate subdirectory.
    
- The `log` directory contains various logging information about each colcon invocation.


### Colcon workflow


1) Workspace is a directory with particular structure. Usually contains a /src subdirectory, where source code of ROS packages will be located.
2) build subdirectory is where intermediate files will be stored.
3) Install subdirectory is where packages are installed to.
4) log directory contains logging information.

a) Install colcon - sudo apt install python3-colcon-common-extensions
b) creating workspace - mkdir -p ~/workspace_name/src (the -p ensures parent is created and error is not thrown)
cd workspace_name
c) Adding sources
ex - git clone https://github.com/ros2/examples src/examples -b humble
git clone - make a copy of this repo <link of repo> destination path
-b humble means humble branch of the repo

> **Underlay = an existing ROS environment you build on.**

> **Overlay = your workspace that adds or overrides packages.**

d) Building workspace (> **build takes all ROS packages in your workspace and turns them into runnable ROS software.**)
in the root of the workspace, 
a) colcon build --symlink-install --executor sequential` (so python files neednt be rebuilt after every edit)
 This allows the installed files to be changed by changing the files in the `source` space (e.g. Python files or other non-compiled resources) for faster iteration.
 Running `colcon build` may freeze the screen and mouse of systems that are CPU-, RAM- and I/O-limited (e.g., Raspberry Pi), so it might be useful to use the `--executor sequential` argument to build the packages one by one instead of using parallelism.

b) colcon test

Before being able to use any of these executables / installed libraries, we need to add them to path. 
c) source install/setup.bash will add all requried elements to path

- If you do not want to build a specific package place an empty file named `COLCON_IGNORE` in the directory and it will not be indexed.
    
- If you want to avoid configuring and building tests in CMake packages you can pass: `--cmake-args -DBUILD_TESTING=0`.
    
- If you want to run a single particular test from a package:

Every ROS 2 package **must** have a package.xml which is used by colcon to understand dependencies, build system and metadata.

Different build types - 
ament_cmake (cpp nodes), ament_python(python nodes), pure_cmake (non ROS libraries)


ros2 pkg create my_pkg --build-type ament_python

![[Pasted image 20260106104738.png]]


### Packages
A single workspace can contain as many packages as you want, each in their own folder. You can also have packages of different build types in one workspace (CMake, Python, etc.). You cannot have nested packages.Best practice is to have a `src` folder within your workspace, and to create your packages in there. This keeps the top level of the workspace “clean”.

Workflow to create package - 
a) cd src
b) ros2 pkg create --build-type ament_python --license Apache-2.0 <package_name>
 eg ros2 pkg create --build-type ament_python --license Apache-2.0 --node-name my_node my_package createsa simple Hello World type executable in the package.


------------------------------------
### Checkpoint Documentation

mkdir -p wsname/src
cd wsname
echo $ROS_DISTRO (if humble is printed then ROS was already initialize else intialize)
Create a package -> cd src
ros2 pkg create name_of_pkg --build-type ament_python --dependencies rclpy std_msgs

directory structure after this
name_of_pkg/ (this is the inner folder, same name as the pkg). This is where node source code lives.
package.xml contains the metadata and dependency contract. Describes the package to ros. (without it build would fail)
resource/name_of_pkg is a plain text file that is used by ros to discover packages via ament index. Without it, pkg will build but can't run.
setup.py gives build and install instructions for python
