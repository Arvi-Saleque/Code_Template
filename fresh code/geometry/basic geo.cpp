// basic geometry
// be careful! [θ in radians]
Chord Length of a Circle
L = 2r * sin(θ / 2)
Arc Length of a Circle
L = r * θ
Sector Area of a Circle
A = (1/2) * r^2 * θ
Area of Segment = Area of Sector - Area of Triangle
A = (1/2) * r^2 * (θ - sin(θ))
Length of a Common Chord of Two Circles
L = 2 * sqrt( R^2 - ((d^2 + R^2 - r^2) / (2d))^2 )

kissing circles 
The plus sign gives the curvature of the inner circle tangent to the three.
The minus sign gives the curvature of the outer circle enclosing the three.
k4 = k1 + k2 + k3 ± 2 * sqrt(k1*k2 + k2*k3 + k3*k1)
// where ki = 1 / ri (curvature), ri = radius of circle i

// Given medians ma, mb, mc
s = (ma + mb + mc) / 2
D = sqrt(s * (s - ma) * (s - mb) * (s - mc))
A = (4 / 3) * D  // Area of original triangle

//common formula is Area 
= (1/2) * perimeter * apothem
    
// General Polygon
Each_Interior_Angle = ((n - 2) * π) / n
Number_of_Diagonals = n * (n - 3) / 2

// Regular Polygon
// a = length of one side
// R = circumradius (radius of circumscribed circle)
// r = apothem (inradius, perpendicular from center to a side)
Side, a = 2 * R * sin(π / n)
Apothem, r = a / (2 * tan(π / n))
Circumradius = a / (2 * sin(π / n))
Central_Angle = 360 / n
Area_from_side = (n * a^2) / (4 * tan(π / n))
Area_from_apothem = (1/2) * n * a * r
Area_from_R = (1/2) * n * R^2 * sin(2π / n)

// Volume of a spherical cap of height h
V_cap = (π * h^2 * (3*R - h)) / 3
// Total volume of sphere
V_total = (4.0 / 3.0) * π * R^3

// s = semi-perimeter = (a + b + c) / 2
// R = circumradius (radius of circumcircle)
// r = inradius (radius of incircle)
// Ra, Rb, Rc = exradii opposite to a, b, c respectively
    
// Incircle (circle tangent to all sides inside triangle)
Inradius = r = A / s //onto
// Circumcircle (passes through all triangle vertices)
Circumradius = R = (a * b * c) / (4 * A) //pori
// Excircle (touches one side and extensions of other two)
Exradius_Opposite_a = Ra = A / (s - a)

// Triangle Area Formulas
// Equilateral Triangle (all sides equal)
Area = (sqrt(3) / 4) * a^2
// Isosceles Triangle (two sides equal)
Area = (b / 4) * sqrt(4a^2 - b^2)

// 3D Volume Formulas
// Symbol Definitions:
// l = length, w = width, h = height
// a = edge length
// r = radius, d = diameter
// R = base radius (for cone/cylinder), H = height
// Cylinder
Volume = π * r^2 * h
// Cone
Volume = (1/3) * π * r^2 * h
// Sphere
Volume = (4/3) * π * r^3
// Hemisphere
Volume = (2/3) * π * r^3
// Triangular Prism
Volume = (1/2) * b * h * l
// where b = triangle base, h = triangle height, l = length/depth
// Pyramid (square or rectangular base)
Volume = (1/3) * base_area * height
// Tetrahedron (regular, edge = a)
Volume = (a^3) / (6 * sqrt(2))
// Frustum (of cone or pyramid)
Volume = (1/3) * π * h * (R^2 + r^2 + R*r)
// R = larger base radius, r = smaller radius, h = vertical height
// Torus (donut shape)
Volume = 2 * π^2 * R * r^2
// R = distance from center of tube to center of torus
// r = radius of tube
