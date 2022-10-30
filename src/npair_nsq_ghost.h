/* -*- c++ -*- ----------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   https://www.lammps.org/, Sandia National Laboratories
   Steve Plimpton, sjplimp@sandia.gov

   Copyright (2003) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under
   the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

#ifdef NPAIR_CLASS
// clang-format off
typedef NPairNsqGhost<0> NPairFullNsqGhost;
NPairStyle(full/nsq/ghost,
           NPairFullNsqGhost,
           NP_FULL | NP_NSQ | NP_NEWTON | NP_NEWTOFF | NP_GHOST | NP_ORTHO | NP_TRI);

typedef NPairNsqGhost<1> NPairHalfNsqGhostNewtoff;
NPairStyle(half/nsq/ghost/newtoff,
           NPairHalfNsqGhostNewtoff,
           NP_HALF | NP_NSQ | NP_NEWTOFF | NP_GHOST | NP_ORTHO | NP_TRI);
// clang-format on
#else

#ifndef LMP_NPAIR_NSQ_GHOST_H
#define LMP_NPAIR_NSQ_GHOST_H

#include "npair.h"

namespace LAMMPS_NS {

template<int HALF>
class NPairNsqGhost : public NPair {
 public:
  NPairNsqGhost(class LAMMPS *);
  void build(class NeighList *) override;
};

}    // namespace LAMMPS_NS

#endif
#endif

/* ERROR/WARNING messages:

E: Neighbor list overflow, boost neigh_modify one

UNDOCUMENTED

*/
