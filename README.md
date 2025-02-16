<h1>Introduction</h1>

This code use verlet invergration to simulate a movement of objects on screen.

About Strom Verlet Integration, it is essentially a solution to kinematic equation of motion for any object:
<p align="center">$x = x_0 + v_0 t + \frac{1}{2} a t^2 + \frac{1}{6} b t^3 + \cdots$</p>

What does this looks like? A <b>Taylor Series</b> of $x(t)$ about $t-\Delta t$:

<p align="center">$x(t) = \frac{x(t-\Delta t)}{0!}(t-t+\Delta t)^0 + \frac{x'(t-\Delta t)}{1!}(t-t+\Delta t)^1 + \frac{x''(t-\Delta t)}{2!}(t-t+\Delta t)^2+\frac{x'''(t-\Delta t)}{3!}(t-t+\Delta t)^3 + \cdots$</p>
<p align="center">$= x(t-\Delta t) + x'(t-\Delta t)\Delta t + \frac{x''(t-\Delta t)}{2}\Delta t^2 + \frac{x'''(t-\Delta t)}{6}\Delta t^3 + \cdots$</p>
<p>Technically, the equation saying: the current position can be described by previous position.</p>
<p>we know $x(t)$ = position $\Rightarrow x'(t)=$ velocity $=v(t)$ and $x''(t)=$ acceleration $=a(t)$</p>
<p>substitute into the above equation, we have:</p>
<p align="center">$x(t-\Delta t) = x(t-\Delta t) + v(t-\Delta t)\Delta t + \frac{1}{2}a(t-\Delta t)\Delta t^2 + \frac{1}{6}x'''(t-\Delta t)\Delta t^3 + \cdots$</p>
<p>This is the form of the first equation. Since the computer can only describe finite term, lets trucate the terms:</p>
<p align="center">$= x(t) + v(t-\Delta t)\Delta t + \frac{1}{2}a(t-\Delta t)\Delta t^2 + O(x^3)$</p>
<p align="center">$\approx x(t-\Delta t) + v(t-\Delta t)\Delta t + \frac{1}{2}a(t-\Delta t)\Delta t^2$</p>
<p>This is the formula that we will use for the simulation.
to determine current position, we must have the position, velocity, and acceleration of previous position. (fun fact, i think that this is just the kinematic equations for constant velocity at highschool that we used to study.</p>

<h1>Implementation and Iteration</h1>
<h2>Display tool</h2>
<p>The whole point of simulation is to make something visible. therefore, a display tool must be choosen. for that, i choose `SFML`.</p>
to <a href="https://formulae.brew.sh/formula/sfml"><b>install sfml</b></a> on a mac machine, use the following command (of course you must have <a href="https://brew.sh/">brew</a> first

```Shell
brew install sfml@2
```
<h2>Drawn an object on screen</h2>
