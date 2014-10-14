# This script if for the bash like shells, see thisHEPFW.csh for csh like shells (not done yet).
#
# This script was adapted from a the one present on the main ROOT distribution 
# initially made by Fons Rademakers

drop_from_path()
{
   # Assert that we got enough arguments
   if test $# -ne 2 ; then
      echo "drop_from_path: needs 2 arguments"
      return 1
   fi

   p=$1
   drop=$2

   newpath=`echo $p | sed -e "s;:${drop}:;:;g" \
                          -e "s;:${drop};;g"   \
                          -e "s;${drop}:;;g"   \
                          -e "s;${drop};;g"`
}

if [ -n "${HEPFWSYS}" ] ; then
   old_hepfwsys=${HEPFWSYS}
fi

if [ "x${BASH_ARGV[0]}" = "x" ]; then
    if [ ! -f thisHEPFW,sh ]; then
        echo ERROR: must "cd where/HEPFW/is" before calling ". thisHEPFW,sh" for this version of bash!
        HEPFWSYS=; export HEPFWSYS
        return 1
    fi
    HEPFWSYS="$PWD"; export HEPFWSYS
else
    # get param to "."
    thishepfw=$(dirname ${BASH_ARGV[0]})
    HEPFWSYS=$(cd ${thishepfw}/..;pwd); export HEPFWSYS
fi

if [ -n "${old_hepfwsys}" ] ; then
   if [ -n "${PATH}" ]; then
      drop_from_path $PATH ${old_hepfwsys}/bin
      PATH=$newpath
   fi
   if [ -n "${LD_LIBRARY_PATH}" ]; then
      drop_from_path $LD_LIBRARY_PATH ${old_hepfwsys}/lib
      LD_LIBRARY_PATH=$newpath
   fi
   if [ -n "${DYLD_LIBRARY_PATH}" ]; then
      drop_from_path $DYLD_LIBRARY_PATH ${old_hepfwsys}/lib
      DYLD_LIBRARY_PATH=$newpath
   fi
   if [ -n "${SHLIB_PATH}" ]; then
      drop_from_path $SHLIB_PATH ${old_hepfwsys}/lib
      SHLIB_PATH=$newpath
   fi
   if [ -n "${LIBPATH}" ]; then
      drop_from_path $LIBPATH ${old_hepfwsys}/lib
      LIBPATH=$newpath
   fi
   if [ -n "${PYTHONPATH}" ]; then
      drop_from_path $PYTHONPATH ${old_hepfwsys}/lib
      PYTHONPATH=$newpath
   fi
#    if [ -n "${MANPATH}" ]; then
#       drop_from_path $MANPATH ${old_hepfwsys}/man
#       MANPATH=$newpath
#    fi
fi

# if [ -z "${MANPATH}" ]; then
#    # Grab the default man path before setting the path to avoid duplicates 
#    if `which manpath > /dev/null 2>&1` ; then
#       default_manpath=`manpath`
#    else
#       default_manpath=`man -w 2> /dev/null`
#    fi
# fi

if [ -z "${PATH}" ]; then
   PATH=$HEPFWSYS/bin; export PATH
else
   PATH=$HEPFWSYS/bin:$PATH; export PATH
fi

if [ -z "${LD_LIBRARY_PATH}" ]; then
   LD_LIBRARY_PATH=$HEPFWSYS/lib; export LD_LIBRARY_PATH       # Linux, ELF HP-UX
else
   LD_LIBRARY_PATH=$HEPFWSYS/lib:$LD_LIBRARY_PATH; export LD_LIBRARY_PATH
fi

if [ -z "${DYLD_LIBRARY_PATH}" ]; then
   DYLD_LIBRARY_PATH=$HEPFWSYS/lib; export DYLD_LIBRARY_PATH   # Mac OS X
else
   DYLD_LIBRARY_PATH=$HEPFWSYS/lib:$DYLD_LIBRARY_PATH; export DYLD_LIBRARY_PATH
fi

if [ -z "${SHLIB_PATH}" ]; then
   SHLIB_PATH=$HEPFWSYS/lib; export SHLIB_PATH                 # legacy HP-UX
else
   SHLIB_PATH=$HEPFWSYS/lib:$SHLIB_PATH; export SHLIB_PATH
fi

if [ -z "${LIBPATH}" ]; then
   LIBPATH=$HEPFWSYS/lib; export LIBPATH                       # AIX
else
   LIBPATH=$HEPFWSYS/lib:$LIBPATH; export LIBPATH
fi

if [ -z "${PYTHONPATH}" ]; then
   PYTHONPATH=$HEPFWSYS/lib; export PYTHONPATH
else
   PYTHONPATH=$HEPFWSYS/lib:$PYTHONPATH; export PYTHONPATH
fi

# if [ -z "${MANPATH}" ]; then
#    MANPATH=`dirname $HEPFWSYS/man/man1`:${default_manpath}; export MANPATH
# else
#    MANPATH=`dirname $HEPFWSYS/man/man1`:$MANPATH; export MANPATH
# fi

# if [ "x`root-config --arch | grep -v win32gcc | grep -i win32`" != "x" ]; then
#   ROOTSYS="`cygpath -w $HEPFWSYS`"
# fi

unset old_hepfwsys
unset thishepfw
