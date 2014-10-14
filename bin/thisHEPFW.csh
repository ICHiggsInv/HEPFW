# Source this script to set up the ROOT build that this script is part of.
#
# Conveniently an alias like this can be defined in ~/.cshrc:
#   alias hepfw "source bin/hepfw.sh"
#
# This script if for the csh like shells, see hepfw.sh for bash like shells.
#
# Author: Fons Rademakers, 18/8/2006

if ($?HEPFWSYS) then
set old_hepfw="$HEPFWSYS"
endif

# $_ should be source .../thisHEPFW.csh
set ARGS=($_)
if ("$ARGS" != "") then
set hepfw="`dirname ${ARGS[2]}`"
else
# But $_ might not be set if the script is source non-interactively.
# In [t]csh the sourced file is inserted 'in place' inside the
# outer script, so we need an external source of information
# either via the current directory or an extra parameter.
if ( -e thisHEPFW.csh ) then
set hepfw=${PWD}
else if ( -e bin/thisHEPFW.csh ) then 
set hepfw=${PWD}/bin
else if ( "$1" != "" ) then
if ( -e ${1}/bin/thisHEPFW.csh ) then
set hepfw=${1}/bin
else if ( -e ${1}/thisHEPFW.csh ) then
set hepfw=${1}
else 
echo "thisHEPFW.csh: ${1} does not contain a ROOT installation"
endif 
else
echo 'Error: The call to "source where_hepfw_is/bin/thisHEPFW.csh" can not determine the location of the ROOT installation'
echo "because it was embedded another script (this is an issue specific to csh)."
echo "Use either:"
echo "   cd where_hepfw_is; source bin/thisHEPFW.csh"
echo "or"
echo "   source where_hepfw_is/bin/thisHEPFW.csh where_hepfw_is" 
endif
endif

if ($?hepfw) then 

setenv HEPFWSYS "`(cd ${hepfw}/..;pwd)`"

if ($?old_hepfw) then
setenv PATH `echo $PATH | sed -e "s;:$old_hepfw/bin:;:;g" \
-e "s;:$old_hepfw/bin;;g"   \
-e "s;$old_hepfw/bin:;;g"   \
-e "s;$old_hepfw/bin;;g"`
if ($?LD_LIBRARY_PATH) then
setenv LD_LIBRARY_PATH `echo $LD_LIBRARY_PATH | \
sed -e "s;:$old_hepfw/lib:;:;g" \
-e "s;:$old_hepfw/lib;;g"   \
-e "s;$old_hepfw/lib:;;g"   \
-e "s;$old_hepfw/lib;;g"`
endif
if ($?DYLD_LIBRARY_PATH) then
setenv DYLD_LIBRARY_PATH `echo $DYLD_LIBRARY_PATH | \
sed -e "s;:$old_hepfw/lib:;:;g" \
-e "s;:$old_hepfw/lib;;g"   \
-e "s;$old_hepfw/lib:;;g"   \
-e "s;$old_hepfw/lib;;g"`
endif
if ($?SHLIB_PATH) then
setenv SHLIB_PATH `echo $SHLIB_PATH | \
sed -e "s;:$old_hepfw/lib:;:;g" \
-e "s;:$old_hepfw/lib;;g"   \
-e "s;$old_hepfw/lib:;;g"   \
-e "s;$old_hepfw/lib;;g"`
endif
if ($?LIBPATH) then
setenv LIBPATH `echo $LIBPATH | \
sed -e "s;:$old_hepfw/lib:;:;g" \
-e "s;:$old_hepfw/lib;;g"   \
-e "s;$old_hepfw/lib:;;g"   \
-e "s;$old_hepfw/lib;;g"`
endif
if ($?PYTHONPATH) then
setenv PYTHONPATH `echo $PYTHONPATH | \
sed -e "s;:$old_hepfw/lib:;:;g" \
-e "s;:$old_hepfw/lib;;g"   \
-e "s;$old_hepfw/lib:;;g"   \
-e "s;$old_hepfw/lib;;g"`
endif
if ($?MANPATH) then
setenv MANPATH `echo $MANPATH | \
sed -e "s;:$old_hepfw/man:;:;g" \
-e "s;:$old_hepfw/man;;g"   \
-e "s;$old_hepfw/man:;;g"   \
-e "s;$old_hepfw/man;;g"`
endif
endif


if ($?MANPATH) then
# Nothing to do
else
# Grab the default man path before setting the path to avoid duplicates 
if ( -X manpath ) then
set default_manpath = `manpath`
else
set default_manpath = `man -w`
endif
endif

set path = ($HEPFWSYS/bin $path)

if ($?LD_LIBRARY_PATH) then
setenv LD_LIBRARY_PATH $HEPFWSYS/lib:$LD_LIBRARY_PATH      # Linux, ELF HP-UX
else
setenv LD_LIBRARY_PATH $HEPFWSYS/lib
endif

if ($?DYLD_LIBRARY_PATH) then
setenv DYLD_LIBRARY_PATH $HEPFWSYS/lib:$DYLD_LIBRARY_PATH  # Mac OS X
else
setenv DYLD_LIBRARY_PATH $HEPFWSYS/lib
endif

if ($?SHLIB_PATH) then
setenv SHLIB_PATH $HEPFWSYS/lib:$SHLIB_PATH                # legacy HP-UX
else
setenv SHLIB_PATH $HEPFWSYS/lib
endif

if ($?LIBPATH) then
setenv LIBPATH $HEPFWSYS/lib:$LIBPATH                      # AIX
else
setenv LIBPATH $HEPFWSYS/lib
endif

if ($?PYTHONPATH) then
setenv PYTHONPATH $HEPFWSYS/lib:$PYTHONPATH
else
setenv PYTHONPATH $HEPFWSYS/lib
endif

if ($?MANPATH) then
setenv MANPATH `dirname $HEPFWSYS/man/man1`:$MANPATH
else
setenv MANPATH `dirname $HEPFWSYS/man/man1`:$default_manpath
endif

endif # if ("$hepfw" != "")

set thishepfw=
set old_hepfw=

