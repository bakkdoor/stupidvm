/*
    This file is part of stupidvm.

    stupidvm is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    stupidvm is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with stupidvm.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "includes.h"

/**
   Return the length/size (in bytes) of a given FILE.
   
   @param file The file to get the length/size of.
   @return The length/size (in bytes) of a file.
 */
unsigned long file_length(FILE *file) {  
  unsigned long fl;

  fseek(file, 0, SEEK_END);
  fl = ftell(file);
  fseek(file, 0, SEEK_SET);

  return fl;
}

#define BUF_SIZE 255

/**
   Read a line from a FILE and return it.
   
   @param f The FILE from which to read.
   @return The line (a string) read from the FILE or NULL if EOF.
 */
char* read_line(FILE *f)
{
  /* static to remember if a previous call set EOF for given file */
  static int c = 0; 
  static int lineCount = 0;
  int buf_size = BUF_SIZE;
  int i = 0;
  char *line;
  
  if(c==EOF) {
    c=0; 
    lineCount=0; 
    return NULL;
  }
  
  line = (char*) calloc(buf_size, sizeof(char));
    
  while ((c = fgetc(f)) != EOF && c != '\n') {
    if(i >= buf_size) {
      buf_size += (BUF_SIZE + 1);
      line = (char*) realloc(line, buf_size*sizeof(char));
    }
    line[i++] = c;
  }
  
  /* handle special case of empty file ...*/
  if(lineCount++ == 0 && c == EOF) {
    free(line); 
    return NULL;
  }
  
  /* add terminal 0 byte */
  line[i] = '\0';
  return realloc(line, i+1); 
}

/**
   Print out an error message to STDERR.
   
   @param message The error message to print out.
 */
void errormsg(char *message) {
  fprintf(stderr, "ERROR: %s\n", message);
}

/**
   Indicates, if a string is empty (whitespace only).
   
   @param string The string to check.
   @return true, if string is whitespace only, false otherwise.
 */
Bool empty_string(char *string) {
  int i;
  for(i = 0; i < strlen(string); i++) {
    if(isalnum(string[i])) {
      return false;
    }
  }

  /* no characters or numbers found -> must be only whitespace */
  return true;
}
