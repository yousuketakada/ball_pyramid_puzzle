# Twenty-Ball Pyramid Puzzle

## Introduction

TODO

## The problem

Suppose we have twenty balls of equal size and stack them up to make a pyramid.
The "pyramid" here is actually a regular tetrahedron; its base is an equilateral triangle
composed of ten balls closely packed together such that their centers form a triangular lattice:

```
          0
         / \                    10
        /   \                    o
       1-----2                  / \              16
      / \   / \                /   \              o
     /   \ /   \           11 o-----o 12         / \        19
    3-----4-----5            / \   / \          /   \        o
   / \   / \   / \          /   \ /   \        o-----o
  /   \ /   \ /   \        o-----o-----o      17    18
 6-----7-----8-----9      13    14    15

        0-th                    1st              2nd        3rd
       (Base)                                              (Top)
```

The upper, first to third (top), layers are again triangular lattice layers,
composed of six, three, and one ball(s), respectively.

The problem we want to solve is how many ways we would have to make the pyramid
if the balls were glued together with right angles into six polyomino-like pieces:

```
                    o
                    |
 o                  o                 o
 |                  |                 |
 o      o--o--o     o       o         o        o
 |         |        |       |         |        |
 o--o      o        o       o--o      o        o

 'L'      'T'      'I'      'v'      'i'      'd'
```

## A solution

At first, it might seem impossible to make a triangular pyramid from right-angled pieces.
To see why it is possible, notice that the pyramid is in fact part of the close sphere packing
called the face-centered cubic or FCC.
(To find an FCC unit cube in the pyramid, place three more balls in the second layer
so that each of them touches two of the three existing balls.
Then the ball numbered 4 in the base and the balls in the above layers form the unit cube;
the six balls numbered 11, 12, 14, 16, 17, and 18 lie at the centers of the faces and
the other eight balls at the vertices.
See also: https://mathworld.wolfram.com/CubicClosePacking.html)

The FCC packing can also be obtained by stacking, as closely as possible, layers of spheres
such that their centers form a square lattice (instead of a triangular lattice).
We can find such square lattice layers in the pyramid by sectioning it with planes parallel to
a pair of opposite edges, say, 0-1-3-6 and 9-15-18-19:

```
 0 o
   |     2 o--o 10     5 12 16
 1 o       |  |        o--o--o     9 15 18 19
   |     4 o--o 11     |  |  |     o--o--o--o
 3 o       |  |        o--o--o
   |     7 o--o 13     8 14 17
 6 o
```

Similarly, we can find two more sets of parallel square lattice layers in the pyramid, i.e.,
a set of square lattice layers parallel to 6-7-8-9 and 0-10-16-19:

```
 6 o
   |     3 o--o 13     1 11 17
 7 o       |  |        o--o--o     0 10 16 19
   |     4 o--o 14     |  |  |     o--o--o--o
 8 o       |  |        o--o--o
   |     5 o--o 15     2 12 18
 9 o
```

and a set of square lattice layers parallel to 0-2-5-9 and 6-13-17-19:

```
 0 o
   |    10 o--o 1      3 11 16
 2 o       |  |        o--o--o     6 13 17 19
   |    12 o--o 4      |  |  |     o--o--o--o
 5 o       |  |        o--o--o
   |    15 o--o 8      7 14 18
 9 o
```

Now that we have got those square lattice layers in which we can place the polyomino-like pieces,
it is not particularly difficult to solve the puzzle by hand.
Rather than writing a description of the solution in words,
I have written a [program](./puzzle.cpp) for it,
which will print all the solution configurations formatted as a pyramid.
For instance, the first solution found is given by

```
         (i)
         / \
        /   \                   (i)
      (T)---(L)                 / \
      / \   / \                /   \             (i)
     /   \ /   \             (T)---(T)           / \
   (d)---(L)---(v)           / \   / \          /   \       (I)
   / \   / \   / \          /   \ /   \       (T)---(I)
  /   \ /   \ /   \       (L)---(v)---(I)
(d)---(L)---(v)---(I)
```

where I have fixed the orientation of an asymmetric piece called `L` and
tried to place it only in the first set of parallel square lattice layers
(i.e., those parallel to 0-1-3-6 and 9-15-18-19)
so that solutions thus obtained are unique up to rotation and reflection.

Since the two straight pieces `I` and `i` form two adjacent edges of the pyramid
(sharing the top ball),
it is trivial to obtain another solution by exchanging those two pieces.
It turns out that there is no other solution, however.

## Note on references

TODO
