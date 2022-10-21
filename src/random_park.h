/* -*- c++ -*- ----------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   https://www.lammps.org/, Sandia National Laboratories
   The LAMMPS Developers, developers@lammps.org

   Copyright (2003) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under
   the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

#ifndef LMP_RANPARK_H
#define LMP_RANPARK_H

#include "pointers.h"

namespace LAMMPS_NS {

class RanPark : protected Pointers {
 public:
  RanPark(class LAMMPS *, int);
  double uniform();
  double gaussian();
  void reset(int);
  void reset(int, double *);
  int state();

 private:
  int seed, save;
  double second;
};

}    // namespace LAMMPS_NS

#endif
