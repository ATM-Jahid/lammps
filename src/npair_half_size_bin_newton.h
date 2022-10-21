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

#ifdef NPAIR_CLASS
// clang-format off
NPairStyle(half/size/bin/newton,
           NPairHalfSizeBinNewton,
           NP_HALF | NP_SIZE | NP_BIN | NP_NEWTON | NP_ORTHO);
// clang-format on
#else

#ifndef LMP_NPAIR_HALF_SIZE_BIN_NEWTON_H
#define LMP_NPAIR_HALF_SIZE_BIN_NEWTON_H

#include "npair.h"

namespace LAMMPS_NS {

class NPairHalfSizeBinNewton : public NPair {
 public:
  NPairHalfSizeBinNewton(class LAMMPS *);
  void build(class NeighList *) override;
};

}    // namespace LAMMPS_NS

#endif
#endif
