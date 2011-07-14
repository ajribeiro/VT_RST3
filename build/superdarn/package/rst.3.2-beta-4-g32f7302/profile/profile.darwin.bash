# profile-darwin.bash
# ===================

export OSTYPE="darwin"
export SYSTEM="darwin"
export EDITOR="emacs -nw"

#####################################################################
#                                                                   #
# Set HOMEPATH Directory if missing                                 #
#                                                                   #
#####################################################################

if [ -z "${HOMEPATH}" ]
then
  export HOMEPATH="/Applications/rst"
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

export WWWPATH="/www/doc"
export URLBASE="/doc"

export LIBPATH="${HOMEPATH}/lib"
export BINPATH="${HOMEPATH}/bin"
export DLMPATH="${HOMEPATH}/dlm"
export IPATH="${HOMEPATH}/include"

export USR_CODEBASE="${HOMEPATH}/usr/codebase"
export USR_LIBPATH="${HOMEPATH}/usr/lib"
export USR_BINPATH="${HOMEPATH}/usr/bin"
export USR_IPATH="${HOMEPATH}/usr/include"

export PATH="${PATH}:/opt/local/bin:${BUILD}/base/bin:${BUILD}/base/script:${HOMEPATH}/bin:${HOMEPATH}/usr/bin:${HOMEPATH}/script:${HOME}/bin:${HOME}/script:/Applications/itt/idl/bin:${CDF_PATH}/bin"

#####################################################################
#                                                                   #
# Location of pnmtopng                                              #
#                                                                   #
#####################################################################

export PNMTOPNG="/opt/local/bin/pnmtopng"

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

export NETCDF_PATH="/opt/local/"

# pathname for the CDF software

export CDF_PATH="/Applications/cdf"

# IDL header directory

export IDL_IPATH="/Applications/itt/idl/external/include"

#####################################################################
#                                                                   #
# Library directories                                               #
#                                                                   #
#####################################################################

export DYLD_LIBRARY_PATH=.:/Applications/cdf/lib

#####################################################################
#                                                                   #
# IDL Configuration                                                 #
#                                                                   #
#####################################################################


export IDL_PATH="+/${HOMEPATH}/idl/lib:+/Applications/itt"
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



