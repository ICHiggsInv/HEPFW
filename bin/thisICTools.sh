# This script if for the bash like shells, see thisictools.csh for csh like shells.
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

if [ -n "${ICTOOLSSYS}" ] ; then
   old_ictoolssys=${ICTOOLSSYS}
fi

if [ "x${BASH_ARGV[0]}" = "x" ]; then
    if [ ! -f thisICTools.sh ]; then
        echo ERROR: must "cd where/ICTools/is" before calling ". thisICTools.sh" for this version of bash!
        ICTOOLSSYS=; export ICTOOLSSYS
        return 1
    fi
    ICTOOLSSYS="$PWD"; export ICTOOLSSYS
else
    # get param to "."
    thisictools=$(dirname ${BASH_ARGV[0]})
    ICTOOLSSYS=$(cd ${thisictools}/..;pwd); export ICTOOLSSYS
fi

if [ -n "${old_ictoolssys}" ] ; then
   if [ -n "${PATH}" ]; then
      drop_from_path $PATH ${old_ictoolssys}/bin
      PATH=$newpath
   fi
   if [ -n "${LD_LIBRARY_PATH}" ]; then
      drop_from_path $LD_LIBRARY_PATH ${old_ictoolssys}/lib
      LD_LIBRARY_PATH=$newpath
   fi
   if [ -n "${DYLD_LIBRARY_PATH}" ]; then
      drop_from_path $DYLD_LIBRARY_PATH ${old_ictoolssys}/lib
      DYLD_LIBRARY_PATH=$newpath
   fi
   if [ -n "${SHLIB_PATH}" ]; then
      drop_from_path $SHLIB_PATH ${old_ictoolssys}/lib
      SHLIB_PATH=$newpath
   fi
   if [ -n "${LIBPATH}" ]; then
      drop_from_path $LIBPATH ${old_ictoolssys}/lib
      LIBPATH=$newpath
   fi
   if [ -n "${PYTHONPATH}" ]; then
      drop_from_path $PYTHONPATH ${old_ictoolssys}/lib
      PYTHONPATH=$newpath
   fi
#    if [ -n "${MANPATH}" ]; then
#       drop_from_path $MANPATH ${old_ictoolssys}/man
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
   PATH=$ICTOOLSSYS/bin; export PATH
else
   PATH=$ICTOOLSSYS/bin:$PATH; export PATH
fi

if [ -z "${LD_LIBRARY_PATH}" ]; then
   LD_LIBRARY_PATH=$ICTOOLSSYS/lib; export LD_LIBRARY_PATH       # Linux, ELF HP-UX
else
   LD_LIBRARY_PATH=$ICTOOLSSYS/lib:$LD_LIBRARY_PATH; export LD_LIBRARY_PATH
fi

if [ -z "${DYLD_LIBRARY_PATH}" ]; then
   DYLD_LIBRARY_PATH=$ICTOOLSSYS/lib; export DYLD_LIBRARY_PATH   # Mac OS X
else
   DYLD_LIBRARY_PATH=$ICTOOLSSYS/lib:$DYLD_LIBRARY_PATH; export DYLD_LIBRARY_PATH
fi

if [ -z "${SHLIB_PATH}" ]; then
   SHLIB_PATH=$ICTOOLSSYS/lib; export SHLIB_PATH                 # legacy HP-UX
else
   SHLIB_PATH=$ICTOOLSSYS/lib:$SHLIB_PATH; export SHLIB_PATH
fi

if [ -z "${LIBPATH}" ]; then
   LIBPATH=$ICTOOLSSYS/lib; export LIBPATH                       # AIX
else
   LIBPATH=$ICTOOLSSYS/lib:$LIBPATH; export LIBPATH
fi

if [ -z "${PYTHONPATH}" ]; then
   PYTHONPATH=$ICTOOLSSYS/lib; export PYTHONPATH
else
   PYTHONPATH=$ICTOOLSSYS/lib:$PYTHONPATH; export PYTHONPATH
fi

# if [ -z "${MANPATH}" ]; then
#    MANPATH=`dirname $ICTOOLSSYS/man/man1`:${default_manpath}; export MANPATH
# else
#    MANPATH=`dirname $ICTOOLSSYS/man/man1`:$MANPATH; export MANPATH
# fi

# if [ "x`root-config --arch | grep -v win32gcc | grep -i win32`" != "x" ]; then
#   ROOTSYS="`cygpath -w $ICTOOLSSYS`"
# fi

unset old_ictoolssys
unset thisictools
