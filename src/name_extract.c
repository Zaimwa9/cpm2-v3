#include "header.h"

char *ft_name(char *src)
{
  int i;
  int j;
  char *dest;

  i = 0;
  while (src[i])
    i++;
  while (src[i] != '/')
  {
    i--;
    j++;
  }
  dest = (char*)malloc(sizeof(char) * j + 1);
  j = 0;
  while (src[i])
    dest[j++] = src[++i];
  dest[j + 1] = '\0';
  return (dest);
}

char *ft_filetype(char *src)
{
  int i, size, flag, j;
  char *type;

  i = 0;
  j = 0;
  while (src[i])
    i++;
  size = i;
  while (src[i] != '/')
  {
    if (src[i] == '.')
      {
        flag = size - i;
        break;
      }
    i--;
  }
  type = (char*)malloc(sizeof(char) * flag + 1);
  if (flag == 0)
    type[0] = '\0';
  else
  {
    while (src[i + j])
      {
        type[j] = src[i + j];
        j++;
      }
  }
  type[j + 1] = '\0';
  return (type);
}