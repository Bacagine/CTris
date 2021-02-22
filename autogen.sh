#!/bin/sh
# 
# autogen.sh: Create the files and configure script needed to
# compile the software
# 
# Developed by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
# 
# Data: 22/Feb/2021

autoheader
autoreconf --install
automake
