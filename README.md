ICTools
=======

This a set of tools developed by me (J.Pela) to use on my physics analysis. But there is no reason they cannot be used for other purposes.

It is built over CERN C++ based framework ROOT and you will need to have it installed and its sourced available to compile against.

***** Compilations Instructions *****

1) Getting and compiling ROOT sources 
NOTE: There may be packages for you linux distro that do this for you):

Corrent version of ICTools was compiled and tested with ROOT v5.34.14, I recommend using this version of better.

wget ftp://root.cern.ch/root/root_v5.34.14.source.tar.gz
tar -xvf root_v5.34.14.source.tar.gz
cd root
./configure
. bin/thisroot.sh
make install
cd ..

If all went well you should have root compiled and setup. If you want to have it set up automatically when you start a command prompt (and you use bash) add to you .bashrc

source <path to ROOT>/bin/thisroot.sh

2) Latest release of ICTools from github.com
NOTE: For this example using ICTools v0.2. There may be actually a more recent version online:

wget https://github.com/joaopela/ICTools/archive/v0.2.tar.gz
tar -xvf v0.2.tar.gz
cd ICTools-0.2/lib/
make all

And you are done!

***** Usage Instructions *****

* To setup an instalation of ICTools as the current one you can use the command <>. This will setup the appropriate paths so the built binaries and libraries become easilly usable by you.

source <path to ICTools>/ICTools/bin/thisICTools.(c)sh

* You can setup your bash or csh bases command line to automatically use a specific version of ICTools by:

Adding to your .bashrc:
source <path to ICTools>/bin/thisICTools.sh

* After setting up ICTools you can easilly compile and link you code using the provided scripts:

For compilation:

For linking:

***** Code developement using ICTools *****

You can use ICTools as the basis for your project compilation. ICTools source code is located inside ICTools/src and it follows a package/subpackage structure. Inside each subpackage source files should be located inside the "src" directory, headers should be inside "interface" and sources intended to become executable should be inside directory "exe"

When you run make on the whole ICTools package any sources found following this structure will be compiled correctly taking into account dependencies.

NOTE: If you which to include headers from ICTools you can use the path "package/subpackage/interface/class.h" since the project makefile is aware if this include base by default. 

***** Developing ICTools *****

Are you interested in adding code to ICTools, send me an email explaining what you want to contribute to, so we can coordinate. And after that just send me your pull request via github.com :D
