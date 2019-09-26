#include <stdio.h>
#include <stdlib.h> 


int main()
{
   
    int c=0;
    char file_name[256] = "file1.txt";
    char buf[512];
    FILE *f = fopen(file_name, "r");
    int n=0;
    int lineNumber = 6*n;

static const char filename[] = "file1.txt";
FILE *file = fopen(filename, "r");
int count = 0;
if ( file != NULL )
{
    char line[256]; 
    c=lineNumber;
    while (fgets(line, sizeof line, file) != NULL) 
    {
        if (count == lineNumber)
        {
            
            printf("%s", line);
            
            
            c++;
            if (c >=lineNumber+5){
                exit(0);
            }
        }
        else
        {
            count++;
        }
    }
    fclose(file);
}
    else
    {
        printf("File does not exist");
    }
       
        fclose(f);
    }
