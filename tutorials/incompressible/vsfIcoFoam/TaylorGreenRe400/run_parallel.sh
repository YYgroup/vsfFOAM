#!/bin/sh
blockMesh
funkySetFields -time 0
decomposePar
mpirun -n 8 vsfIcoFoam -parallel
reconstructPar
