/*
 * UNH CS620 Assignment 0
 *    convert a decimal number to binary
 *
 * NOTE:
 *    due to ambiguities in the specification,
 *    I implemented the program to only look at the
 *    first token on the line. For example, these inputs
 *    will produce the associated result
 *       
 *        input           result
 *
 *       202 dog  -> convert 202 to binary
 *       dog 202  -> invalid input
 *       111 quit -> convert 111 to binary
 *       quit 111 -> quit
 *
 * Carick Wienke
 * 2011.01.28
 */

#include <stdio.h>
#include <string.h>

#define QUIT (-1)
#define INVALID (-2)

#define STR_LEN (30)
#define BIN_LEN (11)


// forward declarations

   // checks the string and returns the integer value
   // if the string represents an integer between 0-2047
   // otherwise it returns INVALID or QUIT
int convert_input( char* );

   // returns the value of the first token on an 
   // input line from stdin, or the status information
   // {INVALID,QUIT}
int get_input();

   // converts the integer to binary and prints it
void to_binary( int );

int main( int argc, char** argv )
{
   int input_val = get_input();

   while( input_val != QUIT )
   {
      if( input_val == INVALID )
         printf( "  !! Invalid input.\n" );
      else
         to_binary( input_val ); 

      input_val = get_input();
   }

   return 0;
}

   // returns the value of the first token on an 
   // input line from stdin, or the status information
   // {INVALID,QUIT}
int get_input()
{
   printf( "Enter an integer between 0 and 2047: " );
   
   char line[ STR_LEN ] = {0};
   fgets( line, STR_LEN, stdin );
   
   int len = strlen( line );
   
   if( line[ len - 1 ] != '\n' )
   {
         // clear the rest of the line

      int x; // dummy variable
      x = getchar();

      while( x != '\n' && x != EOF )
         x = getchar();
   }
   
   return convert_input( line );
}

   // checks the string and returns the integer value
   // if the string represents an integer between 0-2047
   // otherwise it returns INVALID or QUIT
int convert_input( char* input )
{
   char *token;
   token = strtok( input, " \n\t" );
   if( token == NULL )
      return INVALID;

   int val;
   int status = sscanf( token, "%d", &val );

   if( status == 1 )
      return ( 0 <= val && val < 2048 ? val : INVALID );
   else if( !strcmp( token, "quit" ) )
      return QUIT;
   else
      return INVALID;
}

   // converts the integer to binary and prints it
void to_binary( int dec_val )
{
   int cur_val = dec_val;

   char bin_val[ BIN_LEN ] = {0};
   
   int mask = 1 << 10;
   int index = 0;
   while( mask > 0 )
   {
      if( cur_val >= mask )
      {
         bin_val[ index ] = '1';
         cur_val -= mask;
      }
      else
         bin_val[ index ] = '0';

      ++index;
      mask >>= 1;
   }

   printf( "   %d = 0b%s\n", dec_val, bin_val );
}
