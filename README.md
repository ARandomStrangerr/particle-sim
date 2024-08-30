This is acutually what i would rather do for project.  
I hate making a web-application. I am Mathematics major, not Software-Engineer.  
# Introduction
This project uses Verlet Integration formula to calculate the next position of an object:  
$x_{n+1} = 2x_n - x_{n-1} + a \Delta t^2$  
$= x_n + x_n - x_{n-1} + a \Delta t^2$ (we will use this formula)  
$= x_n + v_{n-1} \Delta t + a \Delta t^2$
$= x_n + (v_{n-1} + a \Delta t)\Delta t$  
$= x_n + v_n \Delta t$  
For $x_{n+1}$ = next position, $x_n$ = current position, v = velocity, a = acceleration, and $\Delta t$ = time period.  
Roughly speaking, the next position = previous position + velocity * period.  
It is like constant velocity formula but. We can do it here because we consider period = $dt$, with super small time frame, we can treat velocity like a straight line (a.k.a. constant velocity).  
# Code Iteration
## Draw a Static Object on Screen
To move and object on screen, we first must have an object that is not moving.  
![static object illustration](https://github.com/ARandomStrangerr/particle-sim/blob/main/Screenshot%202024-08-28%20at%206.38.34%20PM.png)
## Move an Object With Initial Velocity
Like most physic problem, we must have frame of reference.  
For a screen of 800x600, let define 1 pixel to be 1 meter, and we want the time in the computer to synchronize with the real time.  
Let the object moves at velocity of A m/s, and $\Delta t = 1$; when we decrease the time, we should decrease the initial velocity also, since shorter time, same velocity, mean shorter distance.  
For the time: it is best by the following diagram:  
|-- Calculation time --|-- Sleep time --| = $dt$, because drawing 1 object is super quick so the calculation time is neglectable; hence, we can just set the sleep time = $dt$.  
![constant velocity object illustration](https://github.com/ARandomStrangerr/particle-sim/blob/main/constantVelocity.gif)
## Make the Moving Object Stay Inside Screen
to make the ball stay inside the screen, when the ball goes out of the screen, we set its position again to be inside
![object stay insde screen](https://github.com/ARandomStrangerr/particle-sim/blob/main/constantVelocityStayInScreen.gif)  
As we can see, there are two problems that we need to tackles:  
- The ball should bounce
- The ball should stay inside screen entirely.
### Bouncy Ball
When the ball is outside, we set the ball back to inside without updating the previous position, this result into a converges sequence to 0.
To fix this, we set the perious position to be the current position outside of the box, and the current position to be inside the box "orthorgonally"  
![object stay insde screen 2](https://github.com/ARandomStrangerr/particle-sim/blob/main/constantVectorStayInScreen1.gif). 
Why the ball behave in such a weird way? Remember that we set the ball position back orthorgonally, meaning that we set the previous position to be outside, and whatever (x,y) component outside will be set inside.
So now by looking the displacement vector, the object moving orthorgonal to the edges that it touches. The slanted agnle that we have before did not perseved with this method.  
