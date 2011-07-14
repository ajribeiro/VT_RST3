#!/bin/bash

set -e
SEP="+"

# make.rst
# ========
# R.J.Barnes
#
# Purpose:
#
# Builds a copy of an rst repository
#
# Syntax:
#
# make.rst project package
#
# Description:
#
# Builds a copy of an rst repository

##############################################################################

prj=${1}
pkg=${2}

##############################################################################

#  Test for valid command line

##############################################################################

if test -z "${pkg}"
then
  echo "make.rst project package"
  exit 1
fi

package=${BUILD}/${prj}/package/${pkg}

if test ! -d ${package}
then
  echo "Failed to locate package"
  exit 1
fi

ver="rst"
yrval=`date +%Y`

rpkg=${HOMEPATH}/rpkg.tmp

rm -fr ${rpkg}
mkdir -p ${rpkg}

##############################################################################

#  Checkout an element

##############################################################################

makeelement() {

  element=${1}
 
  echo ${element}
  git clone ${HOMEPATH}/${element} ${rpkg}/rst/${element}
  return 0
 
}

##############################################################################

#  Generate inventory

##############################################################################

makeinventory() {
 pwd=${PWD}
 cd ${rpkg}/rst
 find .
 cd ${pwd}
 return 0
}


##############################################################################

#  Create tar file

##############################################################################

maketar () {
  pwd=${PWD}
  cd ${rpkg}
  tar -cvf rpkg.tar rst
  cd ${pwd}
  return 0

}

##############################################################################

#  Replace text tags

##############################################################################

addtag () {
  fname=${1}
  cat ${fname} | addtext -t "\$version\$" -r "${ver}" | \
  addtext -t "\$project\$" -r "${prj}" | \
  addtext -t "\$package\$" -r "${pkg}" | \
  addtext  -t "\$date\$" -r "${yrval}"
  return 0
}

##############################################################################

#  Build directory structure and extract package information

##############################################################################

mkdir -p ${rpkg}/tmp
mkdir -p ${rpkg}/rst
mkdir -p ${rpkg}/rst/.rst

echo "+ Extracting package information"
echo "+--------------------------------------------"

git --git-dir ${BUILD}/${prj}/package/${pkg}/.git archive HEAD | \
    tar -C ${rpkg}/tmp -xvf - 

echo "+--------------------------------------------"

##############################################################################

#  Start generating the distribution from the id list

##############################################################################

if test ! -s "${rpkg}/tmp/id.txt"
then
  echo "Failed to locate package elements"
  exit 1
fi

echo "+ Extracting package elements"
echo "+--------------------------------------------"

ellst=`cat ${rpkg}/tmp/id.txt | tr " " "${SEP}" `

for el in ${ellst}
do
  tmp=`echo ${el} | tr "${SEP}" " "`
  prm=${tmp%%#*} 
  if test -z "${prm}"; then continue; fi
  makeelement ${prm} 
done

echo "+--------------------------------------------"


##############################################################################

#  Generate housekeeping

##############################################################################

echo "+ Generating houskeeping"
echo "+--------------------------------------------"

mkdir -p ${rpkg}/rst/log
makeinventory | tee -a ${rpkg}/rst/log/${prj}-${pkg}.${ver}.inventory

echo "+--------------------------------------------"

##############################################################################

#  Copy profile

##############################################################################

echo "+ Copying package profiles"
echo "+--------------------------------------------"

flist=`find "${rpkg}/tmp/profile" -type f`
for fname in ${flist}
do
   ftail=${fname##*/profile.}
   cp -v ${fname} ${rpkg}/rst/.rst/profile.${prj}-${pkg}.${ftail}
done

echo "+--------------------------------------------"

##############################################################################

#  Copy extra files

##############################################################################

echo "+ Copying extra files"
echo "+--------------------------------------------"

if test -d ${rpkg}/tmp/extra
then
   cp -vr ${rpkg}/tmp/extra/* ${rpkg}/rst
fi

echo "+--------------------------------------------"

##############################################################################

#  Package up the archive

##############################################################################

echo "+ Creating package archive"
echo "+--------------------------------------------"

tarlist="rpkg.tar"

maketar

flist=`find "${rpkg}/tmp" -name "rpkg.*.sh" \
        -o -name "rpkg.*.txt"`
 
for fname in ${flist}
 do
  addtag ${fname} > ${rpkg}/${fname##*/}
   
  if test "${fname##*.}" = "sh"
   then
     chmod a+x ${rpkg}/${fname##*/}
   fi
   tarlist="${tarlist} ${fname##*/}"
done

if test -f "${rpkg}/tmp/README.txt"
then 
  addtag "${rpkg}/tmp/README.txt" > \
      ${rpkg}/README.${prj}-${pkg}.${ver}.txt
      tarlist="${tarlist} README.${prj}-${pkg}.${ver}.txt"

fi
if test -f "${rpkg}/tmp/LICENSE.txt"
then
  addtag "${rpkg}/tmp/LICENSE.txt" > \
  ${rpkg}/LICENSE.${prj}-${pkg}.${ver}.txt
  tarlist="${tarlist} LICENSE.${prj}-${pkg}.${ver}.txt"
fi

echo "+--------------------------------------------"

############################################################################

# Make self-extracting archive

############################################################################

echo "+ Making final package"
echo "+--------------------------------------------"

let lnecnt="`cat ${BUILD}/base/script/rpkg.se | wc -l`"
let lnecnt=$lnecnt+1

cat ${BUILD}/base/script/rpkg.se | addtext -t "\$lnecnt\$" \
   -r "${lnecnt}" \
    > ${prj}-${pkg}.${ver}.sh

tar -cvz -C ${rpkg} ${tarlist} >> ${prj}-${pkg}.${ver}.sh
chmod a+x ${prj}-${pkg}.${ver}.sh

echo "+--------------------------------------------"

rm -fr ${rpkg}
exit 0




