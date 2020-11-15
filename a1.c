#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


void listFile(const char *path,int recursiv,int value,int has_perm_execute)
{
    DIR *dir=NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;
    

    dir = opendir(path);
    if(dir == NULL) {
        return;
    }
    

    

    while((entry = readdir(dir)) != NULL) {
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
            if(lstat(fullPath, &statbuf) == 0) {
            	if(value!=-1){
            		if(S_ISREG(statbuf.st_mode)!=0 || S_ISLNK(statbuf.st_mode)!=0){
            			if(statbuf.st_size > value){
                			printf("%s\n", fullPath);
            			}
            			if(S_ISDIR(statbuf.st_mode)){
                					if(recursiv==1)
                						
                    					listFile(fullPath,recursiv,value,has_perm_execute);
                    				
                    			
                    				}
            		}
            }
            	if(has_perm_execute==1 && value == -1){
            		if((statbuf.st_mode & S_IXUSR)==S_IXUSR){
            			if(S_ISDIR(statbuf.st_mode)){
                					if(recursiv==1){
                						
                    					listFile(fullPath,recursiv,value,has_perm_execute);
                    				printf("%s\n", fullPath);
                    			}
                    				else
                    				printf("%s\n", fullPath);
                    				}
                    			     if(S_ISREG(statbuf.st_mode)!=0 || S_ISLNK(statbuf.st_mode)!=0 ){
                    			     	printf("%s\n", fullPath);
                    			     }
                    			    

                					}
                				}
                if(has_perm_execute==0 && value == -1) {
                	                	if(S_ISDIR(statbuf.st_mode)) {
                					if(recursiv==1){
                    					listFile(fullPath,recursiv,value,has_perm_execute);
                					 printf("%s\n", fullPath);
                					}
                    				else
                    				printf("%s\n", fullPath);
                    				}
                    			     if(S_ISREG(statbuf.st_mode)){
                    			     	printf("%s\n", fullPath);
                    			     }
                    			     if(S_ISLNK(statbuf.st_mode)){
                    			     	printf("%s\n", fullPath);
                    			     }

                				
                }
            }


         }
         else 
	perror("ERROR\n"); 
                				
     }
    
    
    closedir(dir);
}
void findFile(const char *path)
{
	DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;
    char magic[20];
	char name[20];
	int offset=0;
	int size=0;
	char finalrand[20];
   	int k=0;
   	int fd=-1,header_size=0,version=0,nr_sectiuni=0,tip_sectiune=0;

    dir = opendir(path);
    if(dir == NULL) {
    	printf("ERROR\ninvalid directory path\n");
        return;
    }
 while((entry = readdir(dir)) != NULL) {
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
            if(lstat(fullPath, &statbuf) == 0) { 

            	if(S_ISREG(statbuf.st_mode)!=0 || S_ISLNK(statbuf.st_mode)!=0){
                  
            	fd=open(fullPath,O_RDONLY);
     							
 			if(fd!=-1)
			{
   
     			read(fd,magic,4);
     			magic[4]='\0';
     			if(strcmp(magic,"8Tl1")!=0)
     			{

     				continue;
     			}

     			read(fd,&header_size,2);
     			read(fd,&version,4);

     			if(version<109 || version>218)

     			{
					

     				continue;
     			}
     	
     
     				read(fd,&nr_sectiuni,1);

     			if(nr_sectiuni<5 || nr_sectiuni>18)

     			{
     				
     				continue;
     			}
     
					for(int i=0;i<nr_sectiuni;i++)
					{
     					read(fd,&name,16);
     					name[16]='\0';
     					read(fd,&tip_sectiune,2);

     					if(tip_sectiune!=81 && tip_sectiune!=35 && tip_sectiune!=29 && tip_sectiune!=80 && tip_sectiune!=41)
     					{
     		

     						continue;
     					}

     					read(fd,&offset,4);
     						read(fd,&size,4);

     				

						int breakfor = 0;
						
						
						
						
     					
     					lseek(fd,offset,SEEK_SET);

     					for(int j=0;j<size;j++)
     					{
     						read(fd,&finalrand,1);
     					  finalrand[1]='\0';
							if(strcmp(finalrand,"\x0a")==0)
							{

							k++;

							}
							if(k>15) {
				           			
                    	printf("%s\n", fullPath);		
							
						
							breakfor = 1;
						
							break;
						    }


     					} 
     					k=0;
     					
     					lseek(fd,11+26*i,SEEK_SET);	
     					if(breakfor) break;
            						
                    }
                    	
                    }
                    
        		}

        		else findFile(fullPath);
        		
                }
                close(fd);
  		}
    
    }
    closedir(dir);	
} 
     		

void parseFile(const char *path)
{
	char magic[20];
	char name[20];
	int offset=0;
	int size=0;
   
    
    
    int fd=-1,header_size=0,version=0,nr_sectiuni=0,tip_sectiune=0;
	 fd=open(path,O_RDONLY);
     
 if(fd>=0)
	{
   
     	read(fd,&magic,4);
     	magic[4]='\0';
     	if(strcmp(magic,"8Tl1")!=0)
     	{
     			printf("ERROR\nwrong magic");
     			return ;
     	}

     	read(fd,&header_size,2);
     	read(fd,&version,4);

     	if(version<109 || version>218)

     	{
     		printf("ERROR\nwrong version");
     		return ;
     	}
     	
     
     	read(fd,&nr_sectiuni,1);

     	if(nr_sectiuni<5 || nr_sectiuni>18)

     	{
     		printf("ERROR\nwrong sect_nr");
     		return ;
     	}
     
		for(int i=0;i<nr_sectiuni;i++)
		{
     		read(fd,&name,16);
     		read(fd,&tip_sectiune,2);

     		if(tip_sectiune!=81 && tip_sectiune!=35 && tip_sectiune!=29 && tip_sectiune!=80 && tip_sectiune!=41)
     		{
     			printf("ERROR\nwrong sect_types");
     			return ;
     		}

     		read(fd,&offset,4);
     		read(fd,&size,4);

     	}
        lseek(fd,0,SEEK_SET);
        lseek(fd,11,SEEK_CUR);

		printf("SUCCESS\n");
		printf("version=%d\n",version);
		printf("nr_sections=%d\n",nr_sectiuni);

		for(int i=0;i<nr_sectiuni;i++)
		{
			read(fd,&name,16);
			name[16]='\0';
			read(fd,&tip_sectiune,2);
			read(fd,&offset,4);
     		read(fd,&size,4);
     		printf("section%d: %s %d %d\n",i+1,name,tip_sectiune,size);
		}
		
    }
     
     


    
 }


int main(int argc, char **argv)
{
	
    
        if(strcmp(argv[1], "variant") == 0)
        {
            printf("37005\n");
       }
   
		else if (strcmp(argv[1], "list") == 0) {
			int j = 2;
			int recursiv = 0;
			int value = -1;
			int has_perm_execute=0;
			char *path=NULL;


			while (j<argc) {
				if (strncmp(argv[j], "path=", 5) == 0)
				{
					path = argv[j] + 5;

				}
				else if (strcmp(argv[j], "recursive") == 0)
				{
					recursiv = 1;
				}
				else if (strncmp(argv[j], "size_greater=", 13) == 0)
				{
					value = atoi(argv[j] + 13);

				}
				else if (strncmp(argv[j], "has_perm_execute", 16) == 0)
				{
					has_perm_execute = 1;
				}
				j++;
			}
				printf("SUCCESS\n");
			listFile(path,recursiv,value,has_perm_execute);

}

		else if (strcmp(argv[1],"parse") == 0){
			 int j=2;
			 char *path=NULL;


			while (j<argc) {
				if (strncmp(argv[j], "path=", 5) == 0)
				{
					path = argv[j] + 5;

				}
				j++;
			}
			
			
			parseFile(path);

}
else if (strcmp(argv[1],"findall") == 0){
			 int j=2;
			 char *path=NULL;


			while (j<argc) {
				if (strncmp(argv[j], "path=", 5) == 0)
				{
					path = argv[j] + 5;

				}
				j++;
			}
			printf("SUCCESS\n");
			
			findFile(path);

}

        	
  
    return 0;
}
