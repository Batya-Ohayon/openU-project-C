#include "comments.h"

extern FILE * fpc;
extern FILE * fpc1;

void delete_comments(FILE *fpc, FILE *fpc1)
{
  int state= OUT;
  int c;
	while((c=fgetc(fpc))!=EOF)
		{
		    switch(state)
			{  
			   case OUT:
				if(c=='/')
				   state=LEFT_SLASH;
				else{
				     fputc(c,fpc1);
				     if(c=='\"')
				     state=IN_STRING;
		       	             }
				break;
		           case LEFT_SLASH:
				if(c=='*')
				   state=IN_COMMENT;
				else {
				    fputc('/',fpc1);
				    fputc(c,fpc1);
			 	    state=OUT;
				    }
				break;
			   case IN_COMMENT:
				if(c=='*')
				   state=RIGHT_STAR;
				break;
			   case RIGHT_STAR:
				if(c=='/')
				   state=OUT;
				else if(c!='*')
				   state=IN_COMMENT;
				break;
			   case IN_STRING:
				if(c=='\"')
				   state=OUT;
  				fputc(c,fpc1);
				break;
			}
		}
}
