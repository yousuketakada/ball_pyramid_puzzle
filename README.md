# Twenty-Ball Pyramid Puzzle

## Introduction

TODO

![diagram](./fig/diagram.drawio.svg)

## The problem

```
// Problem
// -------
//
// Suppose we have twenty balls of equal size and stack them up to make a pyramid.
// The "pyramid" here is actually a regular tetrahedron; its base is an equilateral triangle
// composed of ten balls closely packed together such that their centers form a triangular lattice:
//
//            0
//           / \                    10
//          /   \                    o
//         1-----2                  / \              16
//        / \   / \                /   \              o
//       /   \ /   \           11 o-----o 12         / \        19
//      3-----4-----5            / \   / \          /   \        o
//     / \   / \   / \          /   \ /   \        o-----o
//    /   \ /   \ /   \        o-----o-----o      17    18
//   6-----7-----8-----9      13    14    15
//
//          0-th                    1st              2nd        3rd
//         (Base)                                              (Top)
//
// The upper, first to third (top), layers are again triangular lattice layers,
// composed of six, three, and one ball(s), respectively.
//
// The problem we want to solve is how many ways we would have to make the pyramid
// if the balls were glued together with right angles into six polyomino-like pieces:
//
//                      o
//                      |
//   o                  o                 o
//   |                  |                 |
//   o      o--o--o     o       o         o        o
//   |         |        |       |         |        |
//   o--o      o        o       o--o      o        o
//
//   'L'      'T'      'I'      'v'      'i'      'd'
//
// Solution
// --------
//
// At first, it might seem impossible to make a triangular pyramid from right-angled pieces.
// To see why it is possible, notice that the pyramid is in fact part of the close sphere packing
// called the face-centered cubic or FCC.
// (To find an FCC in the pyramid, place three more balls in the second layer so that they touch
// two of the three balls originally placed, then the ball numbered 4 in the base and the balls in
// the above layers form an FCC; see also: https://mathworld.wolfram.com/CubicClosePacking.html)
//
// The FCC packing can also be obtained by stacking, as closely as possible, layers of spheres
// such that their centers form a square lattice (instead of a triangular lattice).
// We can find such square lattice layers in the pyramid by sectioning it with planes parallel to
// a pair of opposite edges, say, 0-1-3-6 and 9-15-18-19:
//
//   0 o
//     |     2 o--o 10     5 12 16
//   1 o       |  |        o--o--o     9 15 18 19
//     |     4 o--o 11     |  |  |     o--o--o--o
//   3 o       |  |        o--o--o
//     |     7 o--o 13     8 14 17
//   6 o
//
// Similarly, one can find two more sets of square lattice layers in the pyramid:
// TODO: write two more diagrams
// 
// TODO: Write some short description of the problem and
// the strategy for solution that helps renders understand the code.
//
// We shall fix the orientation of an asymmetric piece called 'L' and
// try to place it only in the first set of parallel square lattice layers
// so that solutions thus obtained are unique up to rotation and reflection.
//
// Solutions are shown in the layer-by-Layer view from bottom to top
// (i.e., the horizontal parallel triangular lattice layers):
//
```

TODO

## A solution

TODO

## Note on references

TODO
