## Search-and-Rescue-Robot
#EE101 Final Project

In this project you will use the robot platform to create an electro-mechanical search & 
rescue robot. The robot must be able to navigate through a series of obstacles (i.e. a 
tunnel of sorts) and find and rescue a victim (colored block) by moving it to safety (i.e. 
off of the robot area oval). 
 
You will use your Arduino Uno board to interface to the robot shield to control two 
motors and to read some number of sensors – e.g. a color sensor, an infrared sensor, 
and other sensors as the team decides. You will create an algorithm to instruct the 
robot to navigate the obstacles and find and rescue the victim (i.e. colored block) and 
write all of the code needed to implement that algorithm. Structured coding techniques 
should be employed for the best score. 
 
Items needed 
- Robot Platform(s) (w/battery pack) – provided by team (including batteries) 
- Arduino Uno board (or equivalent) – provided by the team 
- YourDuino sensors, etc. as deemed necessary – provided by the team 
- Any other materials / electronics used must be provided solely by the team 
 
- Note: some additional electronics (e.g. robot shield, color sensor) MAY be 
provided – their use (if provided) is at the team’s discretion and they must be 
returned in good working order 
 
- Robot Arena – available in lab (oval track) 
- Multiple colored blocks 
- “Tunnel” 
 
There are a number of documents posted on the class Bb including 
- Motor controller documentation 
- Robot shield schematic (if provided) 
- Color sensor schematic (if provided) 
- Infrared sensor schematic (if provided) 
 
Additionally, you will likely find your previous lab work useful for utilizing other sensors. 
The intent of this project is for each team to research the provided materials as well as 
any other information they deem necessary to complete the task. Each team must 
develop their own unique algorithm / solution. No sharing or “googling” or plagiarizing 
or colluding others’ work regardless of the format it may be available in or where it may 
be available. 
 
Note: While some information related to the project may be discussed in class there is 
no plan to provide significant detail for every aspect of the project during class time. 

##Grading 
  There are several components of the project. Each component is weighted as shown in 
    the table below. Each team member will receive the same grade with the exception of 
    teamwork. 
 
#Solution (i.e. does the robot rescue the victim): 
  There are three different colored blocks on the other side of the 
    obstacle. Only the blue block is to be rescued (i.e. pushed off of 
    the robot area oval). No other blocks may be removed from the 
    arena. 
  The time required to rescue the victim may also be factored in. 
  The robot must leave the area after the victim as been rescued in 
    somewhat of an opposite direction to that which the victim was 
    freed. It does not need to re-navigate back through the obstacles. 

 
(25 maximum) 

 
#Code / Algorithm: 
  Was structured coding techniques used? 
  Is the code readable? 
    o Is there good documentation in the code?  
    o Is there good use of labels? Meaningful variable names, etc.? 
  Is the algorithm efficient? Does it make sense for the problem? 
  The code must be submitted during the final project evaluation but 
  should the entire code should NOT be part of the oral presentation. 
    o Key code segments may be appropriate to be included in the 
      oral presentation. 
    o Only the simple text file for the code is to be submitted. 
    o Electronic submission required (sustainability don’t ya know!). 

 
(25 maximum) 

 
#Mechanical “Soundness” 
  Is the robot put together well? 
  Is it neat? Is it self-contained? Is it stable? 

 
(10 maximum) 

 
#Evidence of Teamwork 
  Is there significant information indicating that all members of the 
    team participated in the overall project? 
  During the presentation and periodic project quiz evaluations, it 
    should be obvious how the team is working together and who is 
    doing what on the project. 

 
(15 maximum) 

#Oral Presentation 
  Is there a block diagram? 
  Is there a flow chart showing the algorithm? 
  Length (not too long / not too short)? 
  Is the important information communicated? 
  Are the slides organized, neat, to the point, not trivial? 
  The presentation must be submitted at the final project review. 
    o Power point or .pdf are the only acceptable formats. 
    o Electronic submission required (sustainability don’t ya know!). 

 
(15 maximum) 

 
#Extra Features 
  Any innovative or unique features incorporated in the solution? 
    o e.g. additional sensors or other features that make the teams’ 
      solution stand out from the others 
  o note: a blinking LED will not be considered an extra feature 

 
(10 maximum) 

##Project Description 
You will create a robot that can navigate through an obstacle (i.e. a tunnel of sorts) and 
find a blue block and push it out of the oval robot arena using your own robot platform 
that is controlled by an Arduino (also supplied by you). Figure 1 illustrates a typical bare 
minimum block diagram of the robot system from the components that are to be 
provided by each team. 
 
The Motor Controller is an Arduino shield that has a TB6612FNG integrated circuit (IC). 
This IC can be used to provide the current drive and other controls for two small motors. 
The datasheet for this device can be found on the class Bb. 
 
IR1 and IR2 are infrared sensors that are loaned to your team from the instructor. They 
can be used to detect white or dark objects (to mention just a few of its capabilities). 
 
CS is a color sensor that you can build from the components in the Arduino kit (or may 
be provided to you by the instructor). This color sensor can be built just like the one that 
was done in one of the class labs. 
 
Other sensors will likely be needed depending on your solution to the project. It is 
“assumed” that each team will show a complete detailed block diagram of their final 
system during their oral presentation. 
 
There are three different colored blocks that the robot may encounter – red, green, and 
blue. Only the blue block is to be pushed out of the oval arena. Neither of the other two 
blocks may be disturbed. 
 
#Procedure 
Unlike other labs you have done in this course, the project is somewhat open ended in 
that you, as an engineering student, will provide the entire solution. All algorithms, 
code, electrical connections, mechanical assembly, etc. are to be developed and 
implemented as part of the project. No detailed instructions or information will be given. 
Of course, questions related to the project or components will be answered. 
 
Each teams’ method to create their robot must be their own. A rough outline of the work 
required is provided as an aide below. A team’s solution may or may not include each 
of these steps. Other steps may be necessary depending on the team’s solution to the 
project. 
 
- assemble the robot as deemed by the team to implement the best techniques 
needed for their algorithm 
- write code to operate the interface to the motor controller and drive the motors 
- determine any differences in motor drive speed and develop methods as needed 
to compensate them (i.e. does one have more torque and that other?, does one 
spin faster / slower than the other for a given speed setting?) 
- write code to collect data from the infrared sensors 
- determine the infrared sensors sensitivity to light and dark in various lighting 
conditions such that they can be used to detect the white and black of the arena 
- write whatever other code is needed for whatever other sensors, etc. the team 
decides to utilize 
- develop an algorithm to control the motors from data from the infrared sensors 
and other sensors 
- test and modify the algorithm as needed to enable the search and rescue robot 
to operate autonomously 
- other work to provide the required solution 
 
 
