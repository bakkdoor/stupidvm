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
   returns 3-element array of string containing the values of:
   - opcode (instruction command name)
   - operand 1 (or 0, if not given)
   - operand 2 (or 0, if not given)
   
   @param line Line of characters in a file to be parsed.

   @return Array of strings that map to either instruction names,
   literal values or markers.
 */
char** instruction_words(char *line) {
  char **words;
  char *pch;
  int i = 0;
  
  words = malloc(sizeof(char*) * 3);

  pch = strtok(line, " ");
  while(pch != NULL) {
    words[i] = pch;
    pch = strtok(NULL, ", ");
    i++;
  }
  
  /* fill up any missing operands with 0 */
  for(; i < 3; i++) {
    words[i] = (char)0;
  }

  return words;
}

/**
   @brief Returns a list of InstructionWords by parsing a given .sasm
   file.
   
   @param source The source .sasm FILE handle to be parsed.
   @return List of InstructionWords containing the parsed words &
   identifiers.
 */
InstructionWords* build_instruction_words(FILE *source) {
  char *line;
  char **read_words;
  InstructionWords *first, *current;
    
  /* initialize InstructionWords list */
  first = malloc(sizeof(InstructionWords));
  current = first; /* last points to first on init */
  current->next = NULL;

  while( (line = read_line(source)) ) {
    /* 
       only write lines without a '#' in it (these lines are added
       by cpp and are ignored), also ignore lines with ';' (comments)  
    */
    if(!strchr(line, '#') && !strchr(line, ';') && !empty_string(line)) {
      read_words = instruction_words(line);
      current->opcode = read_words[0];
      current->op1 = read_words[1];
      current->op2 = read_words[2];    
      
      current->next = malloc(sizeof(InstructionWords));
      current->next->next = NULL;
      /* move pointer forward in list for next loop */
      current = current->next;
      
      free(read_words);
    }
  }
  return first;
}

/**
   @brief Compiles a list of InstructionWords to a given file.
   
   @param first Pointer to first element of InstructionWords list.
   @param destination FILE handle to destination file to compile
   binary bytecode to.
 */
void compile_instruction_words(InstructionWords *first, FILE *destination) {
  InstructionWords *current = first;
  MarkerList *markers = build_marker_list(first);
  Instruction ins;
  Marker *found_marker;
  
  /* 
     Loop through all InstructionWords and build Instructions.
     Also replace all occurances of markers by their adress values.
     Finally, write each Instruction out to the destination file.
  */
  while(current && current->opcode) {
    /* 
       if our opcode is a marker, ignore this instance and continue
       with next
    */
    if(!is_marker(current->opcode)) {
      ins.opcode = opcode_from_string(current->opcode);
      
      if(current->op1 && is_identifier(current->op1)) {
        found_marker = find_marker(current->op1, markers);
        ins.op1 = (Operand)found_marker->address;
      } else {
        ins.op1 = current->op1 ? (Operand)atoi(current->op1) : (Operand)0;
      }
      
      if(current->op2 && is_identifier(current->op2)) {
        found_marker = find_marker(current->op2, markers);
        ins.op2 = (Operand)found_marker->address;
      } else {
        ins.op2 = current->op2 ? (Operand)atoi(current->op2) : (Operand)0;
      }
      
      printf("."); /* some output for the user to see */
      
      /* write instruction to destination */
      fwrite(&ins, sizeof(Instruction), 1, destination);
    }
    
    current = current->next;
  }
}

/**
   @brief Returns true, if string looks like marker, e.g.: "marker42:"
   
   Meaning, an identifier, ending with a colon.
   If string doesn't look like a marker, returns false.

   @param string The string to check, if it looks like a marker.
   @return true, if it looks like a marker, false otherwise.
 */
Bool is_marker(char *string) {
  int i;
  int length = strlen(string);
  for(i = 0; i < length; i++) {
    /* all characters up to the last need to be alphanumeric */
    if(i < (length - 1)) {
      if(!isalnum(string[i])) {
        return false;
      }
    } else {  /* the last character needs to be a colon */
      if(string[i] == ':') {
        return true;
      }
    }
  }
  return false;
}

/**
   @brief Indicates, if a string is an identifier (opposed to a
   literal value).
   
   @param string The string to be checked.
   @return true, if string is an identifier, false otherwise.
 */
Bool is_identifier(char *string) {
  int i;
  int length = strlen(string);
  Bool is_ident = true;
  for(i = 0; i < length; i++) {
    /* first character needs to be alpha */
    if(i == 0 && !isalpha(string[i])) {
        return false;
    }
    
    /* all other characters need to be alphanumeric */
    if(!isalnum(string[i])) {
      is_ident = false;
    }
  }
  return is_ident;
}

/**
   @brief Creates a List of Markers (MarkerList) based upon a list of
   InstructionWords.
   
   Basically, we loop through all InstructionWords in words and look
   for markers. If we find one, we add it to the MarkerList and return
   that in the end.
   
   @param words The list of InstructionWords to be processed.
   @return A MarkerList containing all markers found in words.
 */
MarkerList* build_marker_list(InstructionWords *words) {
  int instruction_counter = 0;
  InstructionWords *current_words = words;
  MarkerList *first_marker, *current_marker;
  first_marker = malloc(sizeof(MarkerList));
  current_marker = first_marker;

  if(current_words) {
    do {
      if(current_words->opcode) {
        /* check if opcode looks like a marker */
        if(is_marker(current_words->opcode)) {
          current_marker->marker.name = current_words->opcode;
          current_marker->marker.address = instruction_counter;
          /* increment pointer */
          current_marker->next = malloc(sizeof(MarkerList));
          current_marker = current_marker->next;
        }
      }

      /* increment pointer for next loop */
      current_words = current_words->next;
      instruction_counter++;
    } while(current_words->next);
  }

  return first_marker;
}

/**
   @brief Look for a marker with a given name within a MarkerList.
   
   @param name The name of the marker we're looking for.
   @param first Pointer to the first element in the MarkerList.
   @return Pointer to the Marker, if we found one, NULL otherwise.
 */
Marker* find_marker(char *name, MarkerList *first) {
  MarkerList *current = first;
  if(current) {
    while(current) {
      if(strncmp(current->marker.name, name, strlen(current->marker.name) - 1) == 0) {
        return &current->marker;
      }
      current = current->next;
    }
  }
  
  return NULL;
}

/**
   @brief free() all elements in a given list of InstructionWords.
   
   @param first Pointer to the first element in list of InstructionWords.
 */
void free_list(InstructionWords *first) {
  InstructionWords *last = first;
  InstructionWords *current = first;
  while(current->next) {
    last = current;
    current = current->next;
    free(last);
  }
  free(current);
}

