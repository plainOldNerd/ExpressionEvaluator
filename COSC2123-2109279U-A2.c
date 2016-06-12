#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID "%s on line %d is an invalid expression \n"

typedef struct node
{
    char appears;
    int value;
    struct node * next;
} node;

typedef struct
{
    node * head;
    node * tail;
} list;

int evalOrInval( list * expresList, node * start, node * end,  
        int a, int b, int c, int * changed )
{
    int length = 0;
    node * current = start;

    while( current != end->next )
    {
        ++length;
        current = current->next;
    }

    if( length <= 7 )
    {
        int i = 0;
        char basic[8];
        node * tmpEndPtr = end->next, * current = start, 
             * previous = NULL;

        while( current != end->next )
        {
            basic[i++] = current->appears;
            current = current->next;
        }
        basic[i] = '\0';
        /*  later, to free some malloc'd nodes, we need to start from 
         *  start->next
         */
        current = start->next;

        if( length == 1 )
        {
            switch( start->appears )
            {
                case 'a':
                    {
                        if( start->value == -1 )
                            return a;
                        else
                            return start->value;
                    }
                case 'b':
                    return b;
                case 'c':
                    return c;
                default:
                    return -1;
            }
        }
        if( length == 3 )
        {
            char d;

            if( sscanf( basic, "(%c)", &d ) == 1 )
            {
                switch( d )
                {
                    case 'a':
                        {
                            if( start->next->value == -1 )
                                start->value = a;
                            else
                                start->value = start->next->value;
                            break;
                        }
                    case 'b':
                        {
                            start->value = b;
                            break;
                        }
                    case 'c':
                        {
                            start->value = c;
                            break;
                        }
                    default:
                        return -1;
                }
                start->appears = 'a';

                while( current != end->next )
                {
                    previous = current;
                    current = current->next;
                    free( previous );
                }
                start->next = tmpEndPtr;
                if( !start->next )
                    expresList->tail = start;

                *changed = 1;
                return start->value;
            }
            else
                return -1;
        }
        if( length == 5 )
        {
            char d;

            if( sscanf( basic, "((%c))", &d ) == 1 )
            {
                switch( d )
                {
                    case 'a':
                        {
                            if( start->next->next->value == -1 )
                                start->value = a;
                            else
                                start->value = start->next->next->value;
                            break;
                        }
                    case 'b':
                        {
                            start->value = b;
                            break;
                        }
                    case 'c':
                        {
                            start->value = c;
                            break;
                        }
                    default:
                        return -1;
                }
                start->appears = 'a';

                while( current != end->next )
                {
                    previous = current;
                    current = current->next;
                    free( previous );
                }
                start->next = tmpEndPtr;
                if( !start->next )
                    expresList->tail = start;

                *changed = 1;
                return start->value;
            }
            else
                return -1;
        }
        if( length == 6 )
        {
            int intd, inte;
            char chard, chare;

            if( sscanf( basic, "(%c)(%c)", &chard, &chare) == 2 )
            {
                switch( chard )
                {
                    case 'a':
                        {
                            if( start->next->value == -1 )
                                intd = a;
                            else
                                intd = start->next->value;
                            break;
                        }
                    case 'b':
                        {
                            intd = b;
                            break;
                        }
                    case 'c':
                        {
                            intd = c;
                            break;
                        }
                    default:
                        return -1;
                }
                switch( chare )
                {
                    case 'a':
                        {
                            if( start->next->next->next->next->value == -1 )
                                inte = a;
                            else
                            {
                                inte = 
                                    start->next->next->next->next->value;
                            }
                            break;
                        }
                    case 'b':
                        {
                            inte = b;
                            break;
                        }
                    case 'c':
                        {
                            inte = c;
                            break;
                        }
                    default:
                        return -1;
                }
                start->appears = 'a';
                start->value = intd*inte;

                while( current != end->next )
                {
                    previous = current;
                    current = current->next;
                    free( previous );
                }
                start->next = tmpEndPtr;
                if( !start->next )
                    expresList->tail = start;

                *changed = 1;
                return start->value;
            }
            else
                return -1;
        }
        if( length == 7 )
        {
            int intd, inte;
            char chard, chare;

            if( sscanf( basic, "(%c)+(%c)", &chard, &chare) == 2 )
            {
                switch( chard )
                {
                    case 'a':
                        {
                            if( start->next->value == -1 )
                                intd = a;
                            else
                                intd = start->next->value;
                            break;
                        }
                    case 'b':
                        {
                            intd = b;
                            break;
                        }
                    case 'c':
                        {
                            intd = c;
                            break;
                        }
                    default:
                        return -1;
                }
                switch( chare )
                {
                    case 'a':
                        {
                            if( start->next->
                                    next->next->next->next->value == -1 )
                                inte = a;
                            else
                            {
                                inte = 
                                    start->next->
                                    next->next->next->next->value;
                            }
                            break;
                        }
                    case 'b':
                        {
                            inte = b;
                            break;
                        }
                    case 'c':
                        {
                            inte = c;
                            break;
                        }
                    default:
                        return -1;
                }
                start->appears = 'a';
                start->value = intd+inte;

                while( current != end->next )
                {
                    previous = current;
                    current = current->next;
                    free( previous );
                }
                start->next = tmpEndPtr;
                if( !start->next )
                    expresList->tail = start;

                *changed = 1;
                return start->value;
            }
            if( sscanf( basic, "(((%c)))", &chard ) == 1 )
            {
                switch( chard )
                {
                    case 'a':
                        {
                            if( start->next->next->next->value == -1 )
                                start->value = a;
                            else
                                start->value = start->next->next->
                                    next->value;
                            break;
                        }
                    case 'b':
                        {
                            start->value = b;
                            break;
                        }
                    case 'c':
                        {
                            start->value = c;
                            break;
                        }
                    default:
                        return -1;
                }
                start->appears = 'a';

                while( current != end->next )
                {
                    previous = current;
                    current = current->next;
                    free( previous );
                }
                start->next = tmpEndPtr;
                if( !start->next )
                    expresList->tail = start;

                *changed = 1;
                return start->value;
            }
            else
                return -1;
        }

        return -1;
    }
    else
    {
        int numOpens = 0, numCloses = 0;
        node * current = start, * previous = NULL, * newStart = NULL,
             * newEnd = NULL;

        /*  find the matching brackets, so we have at least 2 of each of
         *  opening and closing
         */
        while( numOpens < 2 && current != end->next )
        {
            do
            {
                if( current->appears == '(' )
                {
                    if( numOpens == 0 )
                        newStart = current;
                    ++numOpens;
                }
                if( current->appears == ')' )
                {
                    ++numCloses;
                    if( numCloses == numOpens )
                        newEnd = current;
                }
                if( current != end && current->appears != '+' )
                    previous = current;

                current = current->next;
            } while( current && 
                    ( numOpens > numCloses || current->appears == '+' ) );

            if( numOpens < 2 )
            {
                numOpens = 0;
                numCloses = 0;
                newStart = NULL;
                newEnd = NULL;
            }
        }
        /*  if newEnd is NULL then we never found 2 opening and 2 closing
         *  matching brackets in a string of more than 7 length (a compound
         *  word)
         */
        if( !newEnd )
            return -1;

        /*  if the outermost brackets are the matching brackets then we need
         *  to strip them away and evaluate the substring within
         */
        if( newStart == start && newEnd == end )
        {
            return evalOrInval( expresList, start->next, previous,
                    a, b, c, changed );
        }
        else
        {
            return evalOrInval( expresList, newStart, newEnd,
                    a, b, c, changed );
        }
    }
}

int main( void )
{
    FILE * expres = fopen( "expressions.txt", "r" );
    int line=1, a, b, c, changed=1;
    char expression[81];  /*  This assumes the expression will be 80
                              characters or less  */
    list expresList;
    node * current;

    while( fgets( expression, 81, expres ) )
    {
        int numOpens=0, numCloses=0, numAdds=0, numMults=0, padded = 0;

        /*  Lines alternate between {a, b, c} values and expressions */
        if( line%2 == 1 )
        {
            if( sscanf( expression, "a=%d, b=%d, c=%d", &a, &b, &c ) != 3 )
                printf( "Line %d is invalid. \n", line );
        }
        else
        {
            int charAt=0;

            expresList.head = NULL;
            current = NULL;

            /*  A new line character will be something of a nuisance
             *  later */
            if( expression[strlen(expression)-1] == '\n' )
                expression[strlen(expression)-1] = '\0';

            /*  I was originally thinking that a valid expression must start
             *  with an opening bracket
             */
            if( strlen(expression) == 1 )
            {
                char d = expression[0];

                expression[0] = '(';
                expression[1] = d;
                expression[2] = ')';
                expression[3] = '\0';
                padded = 1;
            }

            if( expression[0] != '(' || 
                    expression[strlen(expression)-1] != ')' )
            {
                printf( INVALID, expression, line );
                printf( "\n" );
                ++line;
                continue;
            }

            /*  Here, changed doesn't actually mean changed, it's just to
             *  check if every [character, next character] combination was
             *  valid, or if the switch forced an early termination of the
             *  loop.
             */
            changed = 1;
            while( expression[charAt] )
            {
                switch( expression[charAt] )
                {
                    case '(':
                        {
                            if( !( expression[charAt+1] == '(' ||
                                        expression[charAt+1] == 'a' ||
                                        expression[charAt+1] == 'b' ||
                                        expression[charAt+1] == 'c' ) )
                            {
                                printf( INVALID, expression, line );
                                printf( "\n" );
                                charAt = strlen( expression );
                                changed = 0;
                                break;
                            }
                            else
                            {
                                ++numOpens;
                            }
                            break;
                        }
                    case 'a':
                    case 'b':
                    case 'c':
                        {
                            if( expression[charAt+1] != ')'  )
                            {
                                printf( INVALID, expression, line );
                                printf( "\n" );
                                charAt = strlen( expression );
                                changed = 0;
                                break;
                            }
                            break;
                        }
                    case ')':
                        {
                            /* Remember that we have already ensured that
                             * the last character is a closing parentheses.
                             */
                            if( !( expression[charAt+1] == ')' ||
                                        expression[charAt+1] == '(' ||
                                        expression[charAt+1] == '+' ||
                                        expression[charAt+1] == '\0' ) )
                            {
                                printf( INVALID, expression, line );
                                printf( "\n" );
                                charAt = strlen( expression );
                                changed = 0;
                                break;
                            }
                            if( expression[charAt+1] == '(' )
                                ++numMults;
                            ++numCloses;
                            if( numCloses > numOpens )
                            {
                                printf( INVALID "due to too many "
                                        "closing parentheses.\n", 
                                        expression, line );
                                printf( "\n" );
                                charAt = strlen( expression );
                                changed = 0;
                                break;
                            }
                            break;
                        }
                    case '+':
                        {
                            if( expression[charAt+1] != '(' )
                            {
                                printf( INVALID, expression, line );
                                printf( "\n" );
                                charAt = strlen( expression );
                                changed = 0;
                                break;
                            }
                            ++numAdds;
                            break;
                        }
                    default:
                        {
                            printf( "Line %d contains invalid characters."
                                    "\n", line );
                            printf( "\n" );
                            charAt = strlen( expression );
                            changed = 0;
                            break;
                        }
                }  /*  end switch   */

                if( 1 )
                    /*  This saves declaring a pointer unnecessarilly,
                     *  earlier in the code.
                     */
                {
                    node * nextNode = malloc( sizeof(node) );
                    if( !nextNode )
                    {
                        perror( "Not enough memory, sorry. \n" );
                        return EXIT_FAILURE;
                    }
                    nextNode->appears = expression[charAt];
                    nextNode->value = -1;
                    nextNode->next = NULL;

                    if( !expresList.head )
                    {
                        expresList.head = nextNode;
                    }
                    else
                        current->next = nextNode;
                    current = nextNode;
                    expresList.tail = nextNode;
                }

                ++charAt;
            }
            /* end while( expression[charAt] )  */

            if( !changed )
            {
                ++line;
                continue;
            }
            if( numOpens != numCloses )
            {
                printf( INVALID "due to too many opening parentheses.\n",
                        expression, line );
                printf( "\n" );
                ++line;
                continue;
            }
            /*  Note that the only point of the recent "if(!changed)"
             *  statement is to skip the numOpens!=numCloses statement, so
             *  that the following if can NOT be put in an else statement
             *  earlier.
             */
            if( changed )
            {
                int validity;
                /*  Now we need to call recursively the function to evaluate
                 *  the string.
                 */
                while( changed )
                {
                    changed = 0;
                    validity = evalOrInval( &expresList, 
                            expresList.head, expresList.tail, 
                            a, b, c, &changed );

                    if( validity == -1 )
                    {
                        printf( INVALID, expression, line );
                        printf( "\n" );
                        continue;
                    }
                }
                if( validity != -1 )
                {
                    if( padded )
                    {
                        printf( "%c ", expression[1] );
                    }
                    else
                    {
                        printf( "%s ", expression );
                    }
                    printf( "evaluates to %d using values a=%d, "
                            "b=%d, and c=%d \n", validity,
                            a, b, c);
                    printf( "\n" );
                }
            }
        }

        if( line%2 == 0 )
        {
            current = expresList.head;
            while( current )
            {
                node * previous = current;
                current = current->next;
                free( previous );
            }
        }

        ++line;
    }

    fclose( expres );
    return EXIT_SUCCESS;
}
