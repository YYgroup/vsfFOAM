Copyright (C) 2023 YYGroup <yyg@pku.edu.cn>

# [vsfFOAM](http://www2.coe.pku.edu.cn/subpaget.asp?id=505)

The vortex-surface field (VSF) provides a systematic Lagrangian-based framework 
for the identification, characterization, and modeling of flow structures. As a 
general flow diagnostic tool, the numerical VSF solution can be constructed in 
arbitrary flow fields by solving a pseudo-transport equation driven by the 
frozen, instantaneous vorticity. From post-processing of large-scale database 
of numerical simulations, the VSF elucidates mechanisms in the flows with 
essential vortex dynamics, such as turbulence and transition. 

vsfFOAM is a free, open-source computational fluid dynamics package released by
YYGroup for VSF calculations. It provides a post-processing tool <vsfPseudoEvo> 
to obtain the VSF via solving the pseudo-transport equation based on velocity 
field. Three solvers, <vsfIcoFoam>, <vsfPimpleFoam>, and <vsfRhoPimpleFoam> are 
included to calculate the VSF evolution with the two-time method for 
incompressible and compressible flows.

# Dependence

vsfFOAM is built on [OpenFOAM](https://openfoam.org/). The current version has been validated on 
OpenFOAM v10.

# Installation

0. Load the OpenFOAM environment
1. Download the package, put <vsfFOAM> at $FOAM_INST_DIR
2. Execute the script Allwmake to compile the program

# How to use

To obtain the VSF evolution, simply setup the case as OpenFOAM simulations. 
Additional files for VSF calculations include the initial field <VSF> and 
a dictionary file <system/vsfDict>. 

Check out the example in <vsfFOAM/tutorials/>. The script <run.sh> describes 
how to run the program.

# License

vsfFOAM is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.  See the file =COPYING= in this directory or 
[[http://www.gnu.org/licenses/]], for a description of the GNU General Public
License terms under which you can copy the files.


# References

[1] [Y. Yang, Theory and applications of the vortex-surface field, Chinese 
    Science Bulletin, 65, 483-495, 2020 (In Chinese)
    ](https://doi.org/10.1360/TB-2019-0596)
    
[2] [S. Xiong and Y. Yang, Identifying the tangle of vortex tubes in 
    homogeneous isotropic turbulence, Journal of Fluid Mechanics, 874, 
    952-978, 2019 
    ](https://doi.org/10.1017/jfm.2019.487)
    
[3] [Y. Zhao, Y. Yang, and S. Chen, Vortex reconnection in the late transition 
    in channel flow, Journal of Fluid Mechanics, 802, R4, 2016
    ](https://doi.org/10.1017/jfm.2016.492)
    
[4] [Y. Yang and D. I. Pullin, Evolution of vortex-surface fields in viscous 
    Taylor-Green and Kida-Pelz flows, Journal of Fluid Mechanics, 685, 146-164,
    2011
    ](https://doi.org/10.1017/jfm.2011.287)
    
[5] [Y. Yang and D. I. Pullin, On Lagrangian and vortex-surface fields in flows 
    with Taylor-Green and Kida-Pelz initial conditions, Journal of Fluid 
    Mechanics, 661, 446-481, 2010
    ](https://doi.org/10.1017/S0022112010003125)
