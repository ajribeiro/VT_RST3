/* locate.h
   ======== 
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/





struct file_list {
  int cnt;
  char **fname;
};


void free_locate(struct file_list *ptr);
int test_file_epoch(char *fname,double stime,double etime);

struct file_list *locate_files(char *fpath,char *prefix,
                               double stime,double etime);
