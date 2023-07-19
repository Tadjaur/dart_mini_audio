#ifndef __UTIL__C__
#define __UTIL__C__

#include <stdlib.h>

int __len(char *string, int start)
{
    if (string[start] == '\0')
        return start;
    start++;
    return __len(string, start);
}
int len(char *string)
{
    return __len(string, 0);
}


char *to_str(int value)
{
    char *dt = (char *)calloc(20, sizeof(char));
    snprintf(dt, 20, "%i", value);
    return dt;
}

void c_log(char *data)
{
    printf("'%s'\n", data);
}

char *concat(char *a, char *b)
{
    int rlen = 0, len_a = len(a), len_b = len(b);
    int tlen = len_a + len_b;
    char *r = (char *)calloc(tlen+1, sizeof(char));
    char *head = r;
    while (1)
    {
        if (rlen < len_a)
        {
            *r = *a++;
        }
        else if (rlen < tlen)
        {
            *r = *b++;
        }
        else
        {
            *r = '\0';
            break;
        }
        (void)*r++;
        rlen++;
    }
    return head;
}

char *concat_n(char *string_vec[], int count)
{
    int i;
    char *data = "";
    if (count == 0)
        return "";
    if (count == 1)
        return string_vec[0];
    for (i = 0; i < count; i++)
    {
        char *old = data;
        data = concat(old, string_vec[i]);
        if (i > 0)
            free(old);
    }
    return data;
}

#endif  //!__UTIL__C__
