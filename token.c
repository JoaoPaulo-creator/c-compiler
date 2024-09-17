#include "compiler.h"

bool token_is_keyword(struct token *token, const char *value) {
  return token->type == TOKEN_TYPE_NUMBER && S_EQ(token->sval, value);
}
