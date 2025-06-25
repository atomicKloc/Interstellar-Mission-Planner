# Interstellar-Mission-Planner
A simple tool meant for calculating delta V requirements, or finding the limits of an existing vessel, for interstellar journeys, taking into account special relativity effects, along with acceleration.

## Use
The program simulates a space mission with the perameters you gave it, it will always obey the limits you set, you can calculate specific values by setting them very high or low. If you want to for instance to find the fastest time you can get some place with the delta v you have, you can set the Target Mission Duration to 0, If you wish to instead find the delta v requirements of a mission, you can set the Delta V to a very high value, and the program will tell you how much delta v you need for the distance and time constraints, ect.

## The Parameters
The program will try to ensure that none of these values are exceeded.

### Available Delta V
If your ship burs its engines continuously until it's out of fuel, this is the velocity that it will achieve, you can't use more delta v than this, ignoring relatevistic effects.

### Expiry Time
Due to relativistic effects, that is that the crew experiences different time than those not on the ship, it's important to take into account the time that the cargo/crew will remain viable, a package might need to be delivered in the next 100 years, but the package might only experience 10, depending on speed.

### Target Mission Duration
The time in which the mission needs to be completed from the perspective of a stationary observer.

## Parameter Priority

The program will ask for various parameters and goals for your ship, the program prioritizes targets in this order, from most to least important :
Available Delta V -> Cargo Expiry Time -> Target Mission Duration
