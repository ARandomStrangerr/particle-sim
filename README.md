<h1>Introduction</h1>

This code use verlet invergration to simulate a movement of objects on screen.

About Strom Verlet Integration, it is essentially a solution to kinematic equation of motion for any object:
<p align="center">$x = x_0 + v_0 t + \frac{1}{2} a t^2 + \frac{1}{6} b t^3 + \cdots$</p>

What does this looks like? A <b>Taylor Series</b> of $x(t)$ about $t-\Delta t$:

<p align="center">$x(t \pm \Delta t) = \frac{x(t-\Delta t)}{0!}(t-t+\Delta t)^0 + \frac{x'(t-\Delta t)}{1!}(t-t+\Delta t)^1 + \frac{x''(t-\Delta t)}{2!}(t-t+\Delta t)^2+\frac{x'''(t-\Delta t)}{3!}(t-t+\Delta t)^3 + \cdots$</p>
<p align="center">$= x(t-\Delta t) + x'(t-\Delta t)\Delta t + \frac{x''(t-\Delta t)}{2}\Delta t^2 + \frac{x'''(t-\Delta t)}{6}\Delta t^3 + \cdots$</p>
<p>Technically, the equation saying: the current position can be described by previous position.</p>
<p>we know $x(t)$ = position $\Rightarrow x'(t)=$ velocity $=v(t)$ and $x''(t)=$ acceleration $=a(t)$</p>
<p>substitute into the above equation, we have:</p>
<p align="center">$x(t-\Delta t) = x(t-\Delta t) + v(t-\Delta t)\Delta t + \frac{1}{2}a(t-\Delta t)\Delta t^2 + \frac{1}{6}x'''(t-\Delta t)\Delta t^3 + \cdots$</p>
<p>This is the form of the first equation. Since the computer can only describe finite term, lets trucate the terms:</p>
<p align="center">$= x(t-\Delta t) + v(t-\Delta t)\Delta t + \frac{1}{2}a(t-\Delta t)\Delta t^2 + O(x^3)$</p>
<p align="center">$\approx x(t-\Delta t) + v(t-\Delta t)\Delta t + \frac{1}{2}a(t-\Delta t)\Delta t^2$</p>
This is the formula that we will use for the simulation.
to determine current position, we must have the position, velocity, and acceleration of previous position.
