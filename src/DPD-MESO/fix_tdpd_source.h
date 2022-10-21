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

#ifdef FIX_CLASS
// clang-format off
FixStyle(tdpd/source,FixTDPDSource);
// clang-format on
#else

#ifndef LMP_FIX_TDPDSOURCE_H
#define LMP_FIX_TDPDSOURCE_H

#include "fix.h"

namespace LAMMPS_NS {

class FixTDPDSource : public Fix {
 public:
  FixTDPDSource(class LAMMPS *, int, char **);
  int setmask() override;
  void init() override;
  void post_force(int) override;

 protected:
  int option;
  int cc_index;
  double center[3], radius, dLx, dLy, dLz;
  double value;
};

}    // namespace LAMMPS_NS

#endif
#endif
