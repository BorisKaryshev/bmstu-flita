#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#ifndef _BYCHAR
    #ifndef _BUFFER
        #define _BUFFER
    #endif
#endif

#define BUFF_SIZE (1024*10)

void FindLoops(const char *infile, const char *outfile) {
    FILE *pinfile = fopen(infile, "r");
    FILE *poutfile = fopen(outfile, "w");
    FILE *ploops = fopen("loops.txt", "w");

    fputs("graph graphname {\n", poutfile);
    
#ifdef _BUFFER
    char buffer[BUFF_SIZE+1];
    size_t length = fread(buffer, 1, BUFF_SIZE, pinfile);
    
    int pos = 0;

    while(1) {
        for(;buffer[pos] != '\n' && pos < length && buffer[pos] != EOF; pos++);

        if(buffer[pos] == '\n' || buffer[pos] == EOF) {
            pos++;
            break;
        } else {
            pos = 0;
            length = fread(buffer, 1, BUFF_SIZE, pinfile);
        }
    }

    int pos_from = -1, i = 1;
    while(pos != length || length >= BUFF_SIZE-1) {
        if (buffer[pos] == '\n' && pos_from != -1) {
            fprintf(poutfile, "\t%d -- %d [color = red];\n", pos_from, pos_from);
            fprintf(ploops, "Founded loop at vertex %d\n", pos_from);
            pos_from = -1;
            i = 1;
        } else if (buffer[pos] == '1' && pos_from == -1){
            pos_from = i;
        } else if (buffer[pos] == '1') {
            fprintf(poutfile, "\t%d -- %d;\n", pos_from, i);
            pos_from = -1;
            i = 1;
            pos++;    
            while(1) {
                for(;buffer[pos] != '\n' && pos < length && buffer[pos] != EOF; pos++);

                if(buffer[pos] == '\n' || buffer[pos] == EOF) {
                    break;
                } else {
                    pos = 0;
                    length = fread(buffer, 1, BUFF_SIZE, pinfile);
                }
            }  
        }

        if (buffer[pos] >= '0' && buffer[pos] <= '9')
            i++;
        
        if (pos == length) {
            pos = 0;
            length = fread(buffer, 1, BUFF_SIZE, pinfile);
        } else
            pos++;
    }
#undef _BUFFER
#endif
#ifdef _BYCHAR
    char c;
    while((c = fgetc(pinfile)) != '\n');

    int pos_from = -1, i = 1;
    while((c = fgetc(pinfile)) != EOF) {
        if (c == '\n' && pos_from != -1) {
            fprintf(poutfile, "\t%d -- %d [color = red];\n", pos_from, pos_from);
            fprintf(ploops, "Founded loop at vertex %d\n", pos_from);
            pos_from = -1;
            i = 1;
        } else if (c == '1' && pos_from == -1){
            pos_from = i;
        } else if (c == '1') {
            fprintf(poutfile, "\t%d -- %d;\n", pos_from, i);
            pos_from = -1;
            i = 1;
            while((c = fgetc(pinfile)) != '\n');
        }

        if (c >= '0' && c <= '9')
            i++;
        
    }
#undef _BYCHAR
#endif

    fputs("}", poutfile);

    fclose(pinfile);
    fclose(poutfile);
    fclose(ploops);
}

int main() {
    clock_t end, begin = clock();
    FindLoops("input.txt", "output.dot");
    end = clock();

    printf("It took %f seconds\n", difftime(end, begin)/CLOCKS_PER_SEC);
    return 0;
}