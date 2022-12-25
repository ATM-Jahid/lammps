# Utility functions
function(list_to_bulletpoints result)
    list(REMOVE_AT ARGV 0)
    set(temp "")
    foreach(item ${ARGV})
        set(temp "${temp}* ${item}\n")
    endforeach()
    set(${result} "${temp}" PARENT_SCOPE)
endfunction(list_to_bulletpoints)

function(validate_option name values)
    string(TOLOWER ${${name}} needle_lower)
    string(TOUPPER ${${name}} needle_upper)
    list(FIND ${values} ${needle_lower} IDX_LOWER)
    list(FIND ${values} ${needle_upper} IDX_UPPER)
    if(${IDX_LOWER} LESS 0 AND ${IDX_UPPER} LESS 0)
        list_to_bulletpoints(POSSIBLE_VALUE_LIST ${${values}})
        message(FATAL_ERROR "\n########################################################################\n"
                            "Invalid value '${${name}}' for option ${name}\n"
                            "\n"
                            "Possible values are:\n"
                            "${POSSIBLE_VALUE_LIST}"
                            "########################################################################")
    endif()
endfunction(validate_option)

# helper function to check for usable omp.h header
function(check_omp_h_include)
  find_package(OpenMP COMPONENTS CXX QUIET)
  if(OpenMP_CXX_FOUND)
    set(CMAKE_REQUIRED_FLAGS ${OpenMP_CXX_FLAGS})
    set(CMAKE_REQUIRED_INCLUDES ${OpenMP_CXX_INCLUDE_DIRS})
    set(CMAKE_REQUIRED_LINK_OPTIONS ${OpenMP_CXX_FLAGS})
    set(CMAKE_REQUIRED_LIBRARIES ${OpenMP_CXX_LIBRARIES})
    check_include_file_cxx(omp.h _have_omp_h)
  else()
    set(_have_omp_h FALSE)
  endif()
  set(HAVE_OMP_H_INCLUDE ${_have_omp_h} PARENT_SCOPE)
endfunction()

# helper function for getting the most recently modified file or folder from a glob pattern
function(get_newest_file path variable)
  file(GLOB _dirs ${path})
  set(_besttime 2000-01-01T00:00:00)
  set(_bestfile "<unknown>")
  foreach(_dir ${_dirs})
    file(TIMESTAMP ${_dir} _newtime)
    if(_newtime IS_NEWER_THAN _besttime)
      set(_bestfile ${_dir})
      set(_besttime ${_newtime})
    endif()
  endforeach()
  if(_bestfile STREQUAL "<unknown>")
    message(FATAL_ERROR "Could not find valid path at: ${path}")
  endif()
  set(${variable} ${_bestfile} PARENT_SCOPE)
endfunction()

function(get_lammps_version version_header variable)
    file(STRINGS ${version_header} line REGEX LAMMPS_VERSION)
    set(MONTHS x Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec)
    string(REGEX REPLACE "#define LAMMPS_VERSION \"([0-9]+) ([A-Za-z]+) ([0-9]+)\"" "\\1" day "${line}")
    string(REGEX REPLACE "#define LAMMPS_VERSION \"([0-9]+) ([A-Za-z]+) ([0-9]+)\"" "\\2" month "${line}")
    string(REGEX REPLACE "#define LAMMPS_VERSION \"([0-9]+) ([A-Za-z]+) ([0-9]+)\"" "\\3" year "${line}")
    string(STRIP ${day} day)
    string(STRIP ${month} month)
    string(STRIP ${year} year)
    list(FIND MONTHS "${month}" month)
    string(LENGTH ${day} day_length)
    string(LENGTH ${month} month_length)
    if(day_length EQUAL 1)
        set(day "0${day}")
    endif()
    if(month_length EQUAL 1)
        set(month "0${month}")
    endif()
    set(${variable} "${year}${month}${day}" PARENT_SCOPE)
endfunction()

function(check_for_autogen_files source_dir)
    message(STATUS "Running check for auto-generated files from make-based build system")
    file(GLOB SRC_AUTOGEN_FILES ${source_dir}/style_*.h)
    file(GLOB SRC_AUTOGEN_PACKAGES ${source_dir}/packages_*.h)
    list(APPEND SRC_AUTOGEN_FILES ${SRC_AUTOGEN_PACKAGES} ${source_dir}/lmpinstalledpkgs.h ${source_dir}/lmpgitversion.h)
    list(APPEND SRC_AUTOGEN_FILES ${SRC_AUTOGEN_PACKAGES} ${source_dir}/mliap_model_python_couple.h ${source_dir}/mliap_model_python_couple.cpp)
    foreach(_SRC ${SRC_AUTOGEN_FILES})
      get_filename_component(FILENAME "${_SRC}" NAME)
      if(EXISTS ${source_dir}/${FILENAME})
        message(FATAL_ERROR "\n########################################################################\n"
                              "Found header file(s) generated by the make-based build system\n"
                              "\n"
                              "Please run\n"
                              "make -C ${source_dir} purge\n"
                              "to remove\n"
                              "########################################################################")
      endif()
    endforeach()
endfunction()

macro(pkg_depends PKG1 PKG2)
  if(PKG_${PKG1} AND NOT (PKG_${PKG2} OR BUILD_${PKG2}))
    message(FATAL_ERROR "The ${PKG1} package needs LAMMPS to be build with the ${PKG2} package")
  endif()
endmacro()

# CMake-only replacement for bin2c and xxd
function(GenerateBinaryHeader varname outfile infile)
    message("Creating ${outfile}...")
    file(WRITE ${outfile} "// CMake generated file\n")

    file(READ ${infile} content HEX)
    string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," content "${content}")
    string(REGEX REPLACE ",$" "" content "${content}")
    file(APPEND ${outfile} "const unsigned char ${varname}[] = { ${content} };\n")
    file(APPEND ${outfile} "const unsigned int ${varname}_size = sizeof(${varname});\n")
endfunction(GenerateBinaryHeader)

# fetch missing potential files
function(FetchPotentials pkgfolder potfolder)
  if(EXISTS "${pkgfolder}/potentials.txt")
    file(STRINGS "${pkgfolder}/potentials.txt" linelist REGEX "^[^#].")
    foreach(line ${linelist})
      string(FIND ${line} " " blank)
      math(EXPR plusone "${blank}+1")
      string(SUBSTRING ${line} 0 ${blank} pot)
      string(SUBSTRING ${line} ${plusone} -1 sum)
      if(EXISTS "${LAMMPS_POTENTIALS_DIR}/${pot}")
        file(MD5 "${LAMMPS_POTENTIALS_DIR}/${pot}" oldsum)
      endif()
      if(NOT sum STREQUAL oldsum)
        message(STATUS "Downloading external potential ${pot} from ${LAMMPS_POTENTIALS_URL}")
        string(MD5 TMP_EXT "${CMAKE_BINARY_DIR}")
        file(DOWNLOAD "${LAMMPS_POTENTIALS_URL}/${pot}.${sum}" "${CMAKE_BINARY_DIR}/${pot}.${TMP_EXT}"
          EXPECTED_HASH MD5=${sum} SHOW_PROGRESS)
        file(COPY "${CMAKE_BINARY_DIR}/${pot}.${TMP_EXT}" DESTINATION "${LAMMPS_POTENTIALS_DIR}")
        file(RENAME "${LAMMPS_POTENTIALS_DIR}/${pot}.${TMP_EXT}" "${LAMMPS_POTENTIALS_DIR}/${pot}")
      endif()
    endforeach()
  endif()
endfunction(FetchPotentials)

# set CMAKE_LINUX_DISTRO and CMAKE_DISTRO_VERSION on Linux
if((CMAKE_SYSTEM_NAME STREQUAL "Linux") AND (EXISTS /etc/os-release))
  file(STRINGS /etc/os-release distro REGEX "^NAME=")
  string(REGEX REPLACE "NAME=\"?([^\"]*)\"?" "\\1" distro "${distro}")
  file(STRINGS /etc/os-release disversion REGEX "^VERSION_ID=")
  string(REGEX REPLACE "VERSION_ID=\"?([^\"]*)\"?" "\\1" disversion "${disversion}")
  set(CMAKE_LINUX_DISTRO ${distro})
  set(CMAKE_DISTRO_VERSION ${disversion})
endif()
