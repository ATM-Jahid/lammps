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
FixStyle(drude,FixDrude);
// clang-format on
#else

#ifndef LMP_FIX_DRUDE_H
#define LMP_FIX_DRUDE_H

#include "fix.h"
#include <set>

#define NOPOL_TYPE 0
#define CORE_TYPE 1
#define DRUDE_TYPE 2

namespace LAMMPS_NS {

class FixDrude : public Fix {
 public:
  int *drudetype;
  tagint *drudeid;
  bool is_reduced;

  FixDrude(class LAMMPS *, int, char **);
  ~FixDrude() override;
  int setmask() override;
  void init() override;

  void grow_arrays(int nmax) override;
  void copy_arrays(int i, int j, int delflag) override;
  void set_arrays(int i) override;
  int pack_exchange(int i, double *buf) override;
  int unpack_exchange(int nlocal, double *buf) override;
  int pack_border(int n, int *list, double *buf) override;
  int unpack_border(int n, int first, double *buf) override;

 private:
  int rebuildflag;
  std::set<tagint> *partner_set;

  void build_drudeid();
  static void ring_search_drudeid(int size, char *cbuf, void *ptr);
  static void ring_build_partner(int size, char *cbuf, void *ptr);
  void rebuild_special() override;
  static void ring_remove_drude(int size, char *cbuf, void *ptr);
  static void ring_add_drude(int size, char *cbuf, void *ptr);
  static void ring_copy_drude(int size, char *cbuf, void *ptr);
};

}    // namespace LAMMPS_NS

#endif
#endif
