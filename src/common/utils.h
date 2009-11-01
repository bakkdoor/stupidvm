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

#ifndef UTILS_H
#define UTILS_H

typedef int Bool;
#define true 1
#define false 0

/**
   Return the length/size (in bytes) of a given FILE.
   
   @param file The file to get the length/size of.
   @return The length/size (in bytes) of a file.
 */
unsigned long file_length(FILE *fp);

#define BUF_SIZE 255

/**
   Read a line from a FILE and return it.
   
   @param f The FILE from which to read.
   @return The line (a string) read from the FILE or NULL if EOF.
 */
char* read_line(FILE *f);

/**
   Print out an error message to STDERR.
   
   @param message The error message to print out.
 */
void errormsg(char *message);

/**
   Indicates, if a string is empty (whitespace only).
   
   @param string The string to check.
   @return true, if string is whitespace only, false otherwise.
 */
Bool empty_string(char *string);

#endif
