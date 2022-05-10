#include "comments.h"


int main (int argc, char **argv){

char name1[MAX_CHAR];
char name2[MAX_CHAR];
char line[MAX_CHAR];
char name_of_file[MAX_CHAR];
char after_hash_mark[MAX_CHAR];
int i;
FILE *include_p;
char *cp;
int d;
char *dot;
int j,length, line_len;
FILE *fpc ,*fpc1, *fpc2;
/*pointers to the files -c, .c1, .c2*/


if(argc!=2)
{	
	return 1;
}

dot = strrchr(argv[1], '.'); 

/*checking if the name of the file ends in '.c'*/
if (!dot || (*++dot)!='c'||(*++dot)!='\0')
{
	printf("this name is illegal, the program name should end with '.c'\n");
	return 1;
}



if((fpc=fopen(*++argv,"r"))==NULL)
{
	printf("Cannot open file %s.",*argv);
	return 1;
}


strcpy(name1,*argv);
cp=strrchr(name1,'.');
*++cp='c';
*++cp='1';
(*++cp)='\0';
	if((fpc1=fopen(name1,"w+"))==NULL)
		{
		  printf("Cannot open the new file- %s.",name1);
		  fclose (fpc);
		}
	else
	        {
			delete_comments(fpc,fpc1); /*rewrite the file without the comments*/
		 
		}

rewind(fpc1);
strcpy(name2,*argv);
cp=strrchr(name2,'.');
*++cp='c';
*++cp='2';
(*++cp)='\0';
	if((fpc2=fopen(name2,"w+"))==NULL)
		{
		  printf("Cannot open the new file- %s.",name2);
		  fclose (fpc1);
		}
	else
	      {
							
		while((d=fgetc(fpc1))!=EOF)
		{
			if(d=='#')
			 {
			  fgets(line,MAX_CHAR,fpc1);
			  line_len=strlen(line);
			  if((strchr(line,'\n'))!=NULL)
			     *(strchr(line,'\n'))='\0';
			  if((sscanf(line,"%s %s",after_hash_mark,name_of_file))==2)
			  {
			     if(!strcmp("include", after_hash_mark))
				{
				      /*copy the name without the quatation marks*/
					length=strlen(name_of_file);
					if(name_of_file[0]!='\"'||name_of_file[length-1]!='\"')
					   {
						printf("name of include file is not ligall\n");
						fprintf(fpc2,"#include  %s\n",name_of_file);
					    }
					else {
						for(j=0;j<length-1;j++)
						{
						  name_of_file[j]=name_of_file[j+1];
						  name_of_file[length-1]='\0';
						}
						
						include_p=fopen(name_of_file,"r");
						if(!include_p)
						{
						  printf("could not open the include file\n");
						  fprintf(fpc2,"#include  \"%s\"\n",name_of_file);
						}
						else{
							while((i=fgetc(include_p))!=EOF)
								{
								fputc(i,fpc2);
								}
			   			    }
			}
		}
	} 
		         
		         
			else 
			{
					fseek(fpc1,-line_len,SEEK_CUR);
					fputc('#',fpc2);
			}
		}
		      
		       else
		        {
		          fputc(d,fpc2);
		        }
		}
		

	      }
return 0;
}
