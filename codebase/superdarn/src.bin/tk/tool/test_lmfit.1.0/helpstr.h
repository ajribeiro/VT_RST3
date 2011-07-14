/* hlpstr.h
   ========
   Author: R.J.Barnes
*/

/*
 $License$
*/


char *hlpstr[]={
"make_lmfit - Creates a fit or fitacf format file from a raw (dat) or radwacf format file.\n",
"make_lmfit --help\n",
"make_lmfit rawname fitname\n",
"make_lmfit -new [rawacfname]\n",

"--help\tprint the help message and exit.\n",
"rawname\tfilename of the raw (dat) format file.\n",
"fitname\tfilename of the fit format file to create.\n",
"-new\tinput file is in  rawacf file format and the output should be in fitacf file format.\n",
"rawacfname\tfilename of the rawacf format file. If this is omitted the file is read from standard input.\n",

NULL};
