# Chapter 6 Surface Normals and Multiple Objects

## Unit Vectors:
#### To find a Unit Vector
1. Compute the length (magnitude) of the vector v=(x,y,z):
$$||v||=\sqrt{x^2+y^2+z^2}$$

2. Divide each component by that length (length$=||v||$):

$$\hat{\mathbf{v}}=\bigg(\frac{x}{||v||}, \frac{y}{||v||}, \frac{z}{||v||}\bigg)$$


## Surface Normals
**A surface normal is a vector that is perpendicular to the surface at the point of intersection.**
For a sphere, the **outward normal** is in the direction of the hit point minus the center:
$$P-C$$


## Visualizing Normals
- assume $n$ is a unit length vector (each component is between -1 and 1)
- map each component to the interval from 0 to 1
- map (x, y, z) to (red, green, blue)

### But the unit vector components range from -1 to 1
- Since the components range from -1 to 1, we need to map these to the interval from 0 to 1
- One way to do this is to add +1 to each component and divide the component by 2.
    - If the component was previously -1, by adding 1 we are at 0. Thus the components are scaled
    - If the component was previously 1, by adding 1 we end up at 2. Then we must divide by 2 to get 1.
- $$\frac{x+1}{2}, \frac{y+1}{2}, \frac{z+1}{2}$$
- In the code, within `ray_color`
```cpp
if (t > 0.0) {
    vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
    return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
}
```

## hit_sphere() previously:
- Before we were just checking if there was a solution or not `return (discriminant >= 0);`
- Previously, hit_sphere only told you yes/no if the ray intersected the sphere.
- In ray_color, any ray that returned true would just get color(1,0,0), so the whole sphere appeared solid red—no shading or normal information.


## How hit_sphere() changes:
- Now we check to see: 
    - if the ray hits the sphere
    - and the intersection point closest to the ray origin by returning `(-b - std::sqrt(discriminant)) / (2.0*a);` in hit_sphere().
    - `(-b + std::sqrt(discriminant))/ (2.0*a)` would instead give us the ray intersection point on the backside of the sphere.

## 6.1 PPM result
![Img 638941400414055052](../img_638941400414055052.png)