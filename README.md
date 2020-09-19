# Geogebra2

## Description

Ray tracing project: one can draw a couple of prisms (convex or non-convex polygons) with different refractive indices, set the starting point and the direction of the light ray and obtain the trajectory of the ray with physically correct refractions, as defined by the [Snell's law](https://en.wikipedia.org/wiki/Snell%27s_law).

## How to run

Requirements: you must have Qt Creator installed.

Open the project in Qt Creator. You will see a window representing a 2D plane with two input modes - prism drawing mode and ray tracing mode.

In the first mode you can draw prisms - non-intersecting and non-self-intersecting polygons - and add their refractive indices (real numbers between 1.00 and 4.00). If you draw something that doesn't meet the rules described above, a warning will appear. The refractive index of the plane is set to 1.00.

In the second mode you can add light rays by setting the starting point and the direction. After that the trajectory of all rays will appear, featuring physically correct refractions.

You can switch modes as many time as you wish, no data (neither of prisms nor of rays) is lost. After adding a new prism, all light rays trajectories are recomputed and redrawn.
