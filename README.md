# stoched
Welcome to __stoched__, an application developed at Princeton University for modeling stochastic systems modeled by rate equations and simulating reactions from them!

Getting started information for __stoched__ (including build instructions) is located in its interior doc/README.md file.

### Introduction

The platform is a fast, compiled code tool with an extremely simple interface aimed towards scientists with minimal programming 
experience. While other tools for stochastic modeling and simulation exist, none have non-programmer-friendly interfaces 
and few are specialized to those systems modeled by rate equations alone. We take user-friendly modeling languages 
developed for Bayesian inference (BUGS/JAGS and Stan) as guides.

Stoched implements the Gillespie algorithm to perform exact simulations. Also, more scalable approximate algorithms derived from the 
Gillespie algorithm are useful for large systems. These algorithms have historically been used to solve problems 
in molecular dynamics; today, they are applied to a wide variety of stochastic modeling problems. 

### Platforms
- Linux
- Mac OS X
- Windows

### Requirements

Serial Implementation
- None

Parallel Implementation (optional)
- [Open MPI] (https://www.open-mpi.org/) 

#### Requirements for Contributors
- [Flex/Bison] (https://www.gnu.org/software/bison/)
- [Google Test](https://github.com/google/googletest) (located in interior lib/ folder; must be built)

###License

Permission to use, copy, modify, and distribute this software and its documentation under the terms of the GNU General Public License is hereby granted. No representations are made about the suitability of this software for any purpose. It is provided "as is" without express or implied warranty. See the GNU General Public License for more details.

Documents produced by Stoched are derivative works derived from the input used in their production; they are not affected by this license.







