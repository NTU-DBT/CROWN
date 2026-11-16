#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pg_query.h"

int main(void) {
  int passed = 1;
  PgQueryParseResult distinct =
      pg_query_parse("SELECT DISTINCT category FROM sample;");

  if (distinct.error != NULL || distinct.parse_tree == NULL ||
      strstr(distinct.parse_tree, "\"SelectStmt\"") == NULL) {
    fputs("SELECT DISTINCT did not produce a SelectStmt\n", stderr);
    if (distinct.error != NULL && distinct.error->message != NULL) {
      fprintf(stderr, "parser error: %s\n", distinct.error->message);
    }
    passed = 0;
  } else {
    puts("SELECT DISTINCT parsed successfully");
  }
  pg_query_free_parse_result(distinct);

  PgQueryParseResult malformed = pg_query_parse("SELECT FROM ;");
  if (malformed.error == NULL) {
    fputs("malformed SQL unexpectedly parsed successfully\n", stderr);
    passed = 0;
  } else {
    printf("malformed SQL rejected: %s\n",
           malformed.error->message == NULL ? "(no message)"
                                            : malformed.error->message);
  }
  pg_query_free_parse_result(malformed);

  if (!passed) {
    return EXIT_FAILURE;
  }

  puts("both parse results freed");
  return EXIT_SUCCESS;
}
