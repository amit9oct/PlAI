PlAI
====

plAI (pronounced as "play") is a competition based on your artificial intelligence skills. 
One has to develop (Code in C++) an AI bot for the provided video-game interface. 
It will contest in a tournament against other AI bots.
The problem statement was as follows :

The video-game is about two rafts competing in a sea to collect as many fish as possible in a given time. 
You are expected to implement an AI function which, on taking certain raft parameters (described below) as input, decides what the raft is to do next.

You will be required to submit a header file and a cpp file. Refer the "Bot Coding Guide" in resources for specific details.

The detailed game specification is as follows:

The map:

Every match is played on a map. 
A map is made up of two kind of regions: traversable by rafts (water), and not traversable by rafts (islands). 
If a raft happens to hit an island during the game, it gets bounced off. 
Additionally, it faces some damage, proportional to the impulse of collision. Every map has fish scattered around. The number of fish in the map are limited in a match. Moreover, fish locations are fixed for a given map and do not change during a match.

The raft:

A raft is circular in shape.

Your AI function must return three controls:

1. Thrust vector (A 2D vector of magnitude less than or equal to 1). 
   This vector is responsible for causing raft’s acceleration. Higher the magnitude, more the acceleration.

2. Brake (a Boolean variable). 
   Setting it ‘true’ turns on drag brakes, due to which the raft slows down at rate proportional to square of its speed. The drag-brake constant is very high.

3. Cannon Vector (A 2D vector of magnitude less than or equal to 1). 
   Setting this vector to a non-zero value causes the raft to fire a cannon ball, direction and speed of which, is governed by this vector.

Note that there is always a small drag force acting on a raft, in direction opposite to direction of velocity, proportional to square of its speed, but with a small drag constant. This force ensures that a raft does not reach infinite speed upon consistent application of thrust.

A raft can see only up to a limited distance in the sea. Thus only a limited part of the map, circular in shape, is visible to a raft. Similarly, rival rafts can see each other only when they are in each other’s visibility region.

A raft collects a fish when it comes within a certain radius of the fish.

A raft has limited life. There are two ways in which a raft can acquire damage:
1. By colliding with land or the opponent raft.
2. From opponent’s cannon balls (explained below).

If a raft’s health gets depleted, it gets destroyed, and the opponent is awarded victory.

Cannon Balls:

A raft can fire cannon balls at its enemy. For that purpose, it must set the Cannon vector to a non-zero value.

Note the following points:

• Cannon balls travels at a finite speed and can get spotted by a raft when they enter its visibility region, giving the raft some time to duck.

• A raft cannot fire cannon balls at infinite rate. There is a minimum time lag between two shots.

Parameters Known to the AI function:

1. The map points inside or on the circle of visibility.
2. Raft’s own state parameters: position, velocity, fish count, remaining health.
3. Other game parameters such as map width, map height, time remaining, etc.
4. Position of opponent raft if it is within visibility radius.
5. Positions of any missiles within visibility radius.
