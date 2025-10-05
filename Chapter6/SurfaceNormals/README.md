# Chapter 6 Surface Normals and Multiple Objects

# 6.1 Shading with Surface Normals

## Unit Vectors:
#### To find a Unit Vector
1. Compute the length (magnitude) of the vector v=(x,y,z):
$$||v||=\sqrt{x^2+y^2+z^2}$$

2. Divide each component by that length (length $=||v||$):

$$\hat{\mathbf{v}}=\bigg(\frac{x}{||v||}, \frac{y}{||v||}, \frac{z}{||v||}\bigg)$$


## Surface Normals
**A surface normal is a vector that is perpendicular to the surface at the point of intersection.**
For a sphere, the **outward normal** is in the direction of the hit point minus the center:
$$P-C$$


### Why $P-C$?
- The Ray Intersection Point is P, this is where the ray from our camera hits the sphere
- then we compute the direction of the outward normal using P-C, or more accurately: $\frac{P-C}{||P-C||}=\hat{V}$
- Then $\hat{V}$ is set to originate from P outwards, to give us the outward normal

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


# 6.2 Simplifying the Ray-Sphere Intersection

## Dot Product and Length
- **"a vector dotted with itself is equal to the squared length of that vector"**
- Proof:
    - Dot Product of itself: $$v⋅v=v_xv_x+v_yv_y+v_zv_z=v_x^2+v_y^2+v_z^2$$
    - Length of a vector: $$||v||=\sqrt{v_x^2+v_y^2+v_z^2}$$
    - Squared Length of a vector: $$||v||^2=v_x^2+v_y^2+v_z^2$$


## Revisiting `hit_sphere()` and simplifying
- note how the equation for `b` in `hit_sphere()` is multiplied by 2:
    - `b = -2.0 * dot(r.direction(), oc)`
    - $$b=-2d⋅(C-Q))$$

**Simplifying**
- if $b=−2h$, the quadratic equation can be simplified to:
    - $$x = {-b \pm \sqrt{b^2-4ac} \over 2a}$$
    - $$x = {-(-2h) \pm \sqrt{(-2h)^2-4ac} \over 2a}$$
    - $$x = {2h \pm \sqrt{4h^2-4ac} \over 2a}$$
    - $$x = {2h \pm \sqrt{4(h^2-ac)} \over 2a}$$
    - $$x = {2h \pm \sqrt{4}⋅\sqrt{(h^2-ac)} \over 2a}$$    
    - $$x = {2h \pm 2\sqrt{h^2-ac} \over 2a}$$
- and to factor out 2 from the whole equation
    - $$x = {2(h \pm \sqrt{h^2-ac}) \over 2a}$$
    - $$x = {h \pm \sqrt{h^2-ac} \over a}$$

### `hit_sphere()` previously:
ray intersection equation: $$t^2(d⋅d)-2t(d⋅(C-Q))+(C-Q)⋅(C-Q)-r^2=0$$

```cpp
double hit_sphere(const vec::point3& center, double radius, const ray& r) {
    vec::vec3 oc = center - r.origin(); // oc = C - Q (Q = ray origin)
    auto a = dot(r.direction(), r.direction()); // a = d·d
    auto b = -2.0 * dot(r.direction(), oc); // b = -2 (d·(C−Q))
    auto c = dot(oc, oc) - radius * radius; // c = (C−Q)·(C−Q) - r^2
    auto discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return -1.0;
    }
    else {
        return (-b - std::sqrt(discriminant)) / (2.0 * a);
    }
}
```
Remember: **"a vector dotted with itself is equal to the squared length of that vector"**.

Since `a` was previously `a = d·d`, we can just replace it with `a = r.direction().length_squared()`

Then we also have `b = -2 (d·(C−Q))`. As we saw earlier in the quadratic equation, we can simplify by setting $b=−2h$.
Then we need to solve for $h$:

Currently: $b=-2d·(C−Q))$ so if $b=−2h$:

$$h=\frac{b}{-2}$$

$$h=\frac{-2d·(C−Q))}{-2}$$

$$h=d·(C−Q))$$

And since the `hit_sphere()` function, is more concerned with the quadratic equation 
than the ray equation, we can safely replace `b = -2.0 * dot(r.direction(), oc);` with
`h = dot(r.direction(), oc);`

Previously `c = dot(oc, oc) - radius * radius`

Same concept of **"a vector dotted with itself = squared length of that vector**
is applied to `c`. There are no additional concepts applied to `c` so we get:

`c = oc.length_squared() - radius*radius`


### `hit_sphere()` now:
```cpp
double hit_sphere(const vec::point3& center, double radius, const ray& r) {
    vec::vec3 oc = center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = h * h - a * c;

    if (discriminant < 0) {
        return -1.0;
    }
    else {
        return (h - std::sqrt(discriminant)) / a;
    }
}
```

- note that the `discriminant = h*h - a*c` which also lines up with the simplification



# 6.3 Abstraction for Hittable Objects

