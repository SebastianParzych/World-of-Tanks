 # World of Tanks game
 ## Purpose
 Main purpose of this project is to understand object oriented programming.
 ## Gameplay
The player controls the vehicle of his choice and tries to destroy computer-controlled tanks. 
### Vehicle types
There are three aviable classes of tanks, which can appear in battlefield:
* **Light tank**-The fastest vehicle, with has the best view range, but worst gun.
* **Medium Tank**- Well-rounded vehicle, with decent movability  and gun.
* **Heavy Tank**- The slowest vehicle with the biggest number of health points. It also deals the most damage with a single shell.
#### The main parameters are presented above, in fact, there are more of them, e.g. reverse speed, rotation speed, turret rotation speed.
### Features 
* Each tank on the battlefield can see opponents, which are in tank's view range. When an enemy comes into line of sight of a computer-controlled tank, it is automatically detected, and the computer starts tracking the enemy vehicle with a gun and then fires a shot.  
* Each opponent can focus on two tanks at the same time. first - The tank it aims at. 2- The tank or obstacle closest to the enemy. Thanks to that, there are rarely collisions between vehicles. 
* After leaving the map, the tank immediately goes to the center of the map.
* Depending on the number of vehicles on the battlefield, chests containing random tank upgrades are created on the map.
* Structures of a bushes are randomly generated.
* Vehicle spawns are adjusted to the number of vehicles on the battlefield- spawned tanks cannot be close to each other.

<p align="center">
  <img width="720" height="400" src="https://user-images.githubusercontent.com/76798626/128071524-29fa3b2b-5f76-47c6-8b6d-a47c35a1fc9b.gif">
</p>

## CLass Hierarchy
* CMap
* ICObject
  * ICMovableObject
    * CShell
    * CTank
  * ICStaticObject
    * CGrass
    * CImprovements
* QGraphicsRecItem
  * ICGObject
    * CGGrass
    * CGImprovements
    * CGShell
    * CGTank
 * QMainWindow
    * GameWindow
    * MainWindow
 * QObject
    * CGame
 ### Example diagrams
<p align="center">
  <b>Inheritance diagram fo ICObject.:</b><br>
  
  <img src="https://user-images.githubusercontent.com/76798626/128076727-6f9323c4-75b4-4af0-86a7-fe820be5e333.png">
</p>
<p align="center">
  <b>Inheritance diagram fo ICGObject.:</b><br>

  <img src="https://user-images.githubusercontent.com/76798626/128077175-36c50fc0-bd86-48be-9d3f-dfd3c64c5841.png">
</p>

# Read More
### For more information about structure of project open in [doc](https://github.com/SebastianParzych/World-of-Tanks/tree/main/doc/html) file doxygen documentation.







