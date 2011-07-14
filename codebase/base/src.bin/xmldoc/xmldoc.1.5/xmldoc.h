/* xmldoc.h
   ======== 
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/





struct xmldoc {
  struct XMLdocdata *doc;
  struct ScriptData *script;
  struct XMLDBtable *table;

  struct {
    char *path;
    char delim;
  } tree;

  struct {
    int num;
    char **txt;
  } match;

  struct {
    int (*check)(char *,struct XMLDBbuffer *,void *data);
    void *data;
  } compare;

  struct {
    int type;
    struct XMLDBbuffer *buf;
  } sc;

  struct {
    int iflg;
    struct {
      int num;
      char **txt;
    } search;
    struct {
      int num;
      char **txt;
    } replace;
    struct {
      int num;
      char **txt;
    } ignore;
    struct {
      int num;
      char **txt;
    } remove;
  } map;


 struct {
    struct {
      int num;
      char **txt;
    } search;
    struct {
      int num;
      char **txt;
    } replace;
  } external;



};
