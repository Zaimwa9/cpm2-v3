#include "header.h"
struct      stat st = {0};
int ft_strlen(char *str)
{
  int i = 0;

  while (str[i])
    i++;
  return (i);
}

int match(regex_t *pexp, char *to_find)
{
	regmatch_t matches[MAX_MATCHES];

  // rm_so => starting occurence; rm_eo => ending occurence. Both integers
  if (regexec(pexp, to_find, MAX_MATCHES, matches, 0) == 0)
  {
		if (matches[0].rm_so == 0 && ft_strlen(to_find) == matches[0].rm_eo)
      return (1);
  }
  return (0);  
}

int reg_compile(char *to_find)
{
  int rv;
  regex_t exp;
  int result;

  if (to_find[0] == '.' && to_find[1] != '.')
    rv = regcomp(&exp,"^(./[^/ ]*)+/?$", REG_EXTENDED);
  else if (to_find[0] == '.' && to_find[1] == '.')
    rv = regcomp(&exp,"^(../[^/ ]*)+/?$", REG_EXTENDED);
  else
    rv = regcomp(&exp,"^(/[^/ ]*)+/?$", REG_EXTENDED);
  if (rv != 0)
    printf("compilation failed %d \n", rv);
  result = match(&exp, to_find);
  regfree(&exp);
  return (result);
}