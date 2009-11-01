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


/*
   List type for instruction words read in from .sasm file
   Each list element points to a next element (or NULL).

   If element A.next points to element B, then element A was read in
   first and B will be compiled after A (and also run in this order,
   when executed by the vm).
*/
typedef struct instruction_words {
  char *opcode;
  char *op1;
  char *op2;
  struct instruction_words *next;
} InstructionWords;


/*
  A Marker marks a certain point in sasm code.

  It is used, for example for marking the beginning of a procedure or
  loop. Markers are used as jump destinations. They translate directly
  to the number (adress) of instruction, they're marking when compiled
  to bytecode. So in the compiled bytecode, only absolute adresses
  appear, all markers are lost.
*/
typedef struct {
  char *name;
  unsigned int address;
} Marker;


/*
  Simple list type for markers, since we usually want to deal with
  more than one marker at a time, when compiling a programm.
*/
typedef struct marker_list {
  Marker marker;
  struct marker_list *next;
} MarkerList;

/* 
   function definitions start here
*/

/**
   returns 3-element array of string containing the values of:
   - opcode (instruction command name)
   - operand 1 (or 0, if not given)
   - operand 2 (or 0, if not given)
   
   @param line Line of characters in a file to be parsed.

   @return Array of strings that map to either instruction names,
   literal values or markers.
 */
char** instruction_words(char *line);

/**
   @brief Returns a list of InstructionWords by parsing a given .sasm
   file.
   
   @param source The source .sasm FILE handle to be parsed.
   @return List of InstructionWords containing the parsed words &
   identifiers.
 */
InstructionWords* build_instruction_words(FILE *source);

/**
   @brief Compiles a list of InstructionWords to a given file.
   
   @param first Pointer to first element of InstructionWords list.
   @param destination FILE handle to destination file to compile
   binary bytecode to.
 */
void compile_instruction_words(InstructionWords *first, FILE *destination);

/**
   @brief Returns true, if string looks like marker, e.g.: "marker42:"
   
   Meaning, an identifier, ending with a colon.
   If string doesn't look like a marker, returns false.

   @param string The string to check, if it looks like a marker.
   @return true, if it looks like a marker, false otherwise.
 */
Bool is_marker(char *string);

/**
   @brief Indicates, if a string is an identifier (opposed to a
   literal value).
   
   @param string The string to be checked.
   @return true, if string is an identifier, false otherwise.
 */
Bool is_identifier(char *string);

/**
   @brief Creates a List of Markers (MarkerList) based upon a list of
   InstructionWords.
   
   Basically, we loop through all InstructionWords in words and look
   for markers. If we find one, we add it to the MarkerList and return
   that in the end.
   
   @param words The list of InstructionWords to be processed.
   @return A MarkerList containing all markers found in words.
 */
MarkerList* build_marker_list(InstructionWords *words);

/**
   @brief Look for a marker with a given name within a MarkerList.
   
   @param name The name of the marker we're looking for.
   @param first Pointer to the first element in the MarkerList.
   @return Pointer to the Marker, if we found one, NULL otherwise.
 */
Marker* find_marker(char *name, MarkerList *first);

/* 
   list operations on InstructionWords 
*/

/**
   @brief free() all elements in a given list of InstructionWords.
   
   @param first Pointer to the first element in list of InstructionWords.
 */
void free_list(InstructionWords *first);
