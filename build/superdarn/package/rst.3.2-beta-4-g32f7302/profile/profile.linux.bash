# profile.linux.bash
# ==================

export OSTYPE="linux"
export SYSTEM="linux"
export EDITOR="emacs -nw"


#####################################################################
#                                                                   #
# Set HOMEPATH Directory if missing                                 #
#                                                                   #
#####################################################################

if [ -z "${HOMEPATH}" ]
then
  export HOMEPATH="${HOME}/rst"
fi

#####################################################################
#                                                                   #
# Directory Paths                                                   #
#                                                                   #
#####################################################################

export BUILD="${HOMEPATH}/build"
export CODEBASE="${HOMEPATH}/codebase"
export LOGPATH="${HOMEPATH}/log"
export DOCPATH="${HOMEPATH}/doc"

export WWWPATH="/www/superdarn/htdocs/doc"
export URLBASE="/doc"

export LIBPATH="${HOMEPATH}/lib"
export BINPATH="${HOMEPATH}/bin"
export DLMPATH="${HOMEPATH}/dlm"
export IPATH="${HOMEPATH}/include"

export USR_CODEBASE="${HOMEPATH}/usr/codebase"
export USR_LIBPATH="${HOMEPATH}/usr/lib"
export USR_BINPATH="${HOMEPATH}/usr/bin"
export USR_IPATH="${HOMEPATH}/usr/include"

export PATH="${PATH}:${BUILD}/base/bin:${BUILD}/base/script:${HOMEPATH}/bin:${HOMEPATH}/usr/bin:${HOMEPATH}/script"

export LD_LIBRARY_PATH="${LIBPATH}:${USR_LIBPATH}"

#####################################################################
#                                                                   #
# Location of pnmtopng                                              #
#                                                                   #
#####################################################################

export PNMTOPNG="/usr/bin/pnmtopng"

#####################################################################
#                                                                   #
# Makefiles                                                         #
#                                                                   #
#####################################################################

export MAKECFG=${BUILD}/base/make/makecfg
export MAKEBIN=${BUILD}/base/make/makebin
export MAKELIB=${BUILD}/base/make/makelib
export MAKEDLM=${BUILD}/base/make/makedlm

#####################################################################
#                                                                   #
# Compilation directives                                            #
#                                                                   #
#####################################################################

# Libraries for TCPIP

export TCPIPLIBS=" "

# Path of the X11 packages

export XPATH="/usr/X11R6"

# Compile netCDF software

export NETCDF_PATH="/usr"

# pathname for the CDF software

export CDF_PATH="/usr/local/cdf"

# IDL header directory

export IDL_IPATH="/usr/local/itt/idl/external/include"

#####################################################################
#                                                                   #
# IDL Configuration                                                 #
#                                                                   #
#####################################################################

export IDL_PATH="+/usr/local/itt:+/${HOMEPATH}/idl/lib"
export IDL_DLM_PATH=${DLMPATH}:${IDL_DLM_PATH}
export IDL_STARTUP="${HOMEPATH}/idl/startup.pro"

#####################################################################
#                                                                   #
# Font Data Tables                                                  #
#                                                                   #
#####################################################################

export FONTPATH=${HOMEPATH}"/tables/base/fonts"
export FONTDB=${HOMEPATH}"/tables/base/fonts/fontdb.xml"

#####################################################################
#                                                                   #
# Coastline tables                                                  #
#                                                                   #
#####################################################################

export MAPDATA=${HOMEPATH}"/tables/general/map_data"
export BNDDATA=${HOMEPATH}"/tables/general/bnd_data"
export MAPOVERLAY=${HOMEPATH}"/tables/general/overlay.dat"

#####################################################################
#                                                                   #
# SuperDARN Environment                                             #
#                                                                   #
#####################################################################

export ISTP_PATH="/data/istp"

export SD_HDWPATH="${HOMEPATH}/tables/superdarn/hdw/"
export SD_RADAR="${HOMEPATH}/tables/superdarn/radar.dat"

export AACGM_DAT_PREFIX=${HOMEPATH}"/tables/analysis/aacgm/aacgm_coeffs"
export IGRF_PATH=${HOMEPATH}"/tables/analysis/mag/"
export SD_MODEL_TABLE=${HOMEPATH}"/tables/superdarn/model"

#####################################################################
#                                                                   #
# SuperDARN ROS Environment                                         #
#                                                                   #
#####################################################################

export SD_RAW_PATH="/data/ros/rawacf"
export SD_FIT_PATH="/data/ros/fitacf"
export SD_IQ_PATH="/data/ros/iqdat"
export SD_ERRLOG_PATH="/data/ros/errlog";
