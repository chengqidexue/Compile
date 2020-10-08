#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <memory.h>
#define MAXSIZE 1024 
#define RESERVESIZE 6           //保留字的数目
#define BEGIN 0                 //BEGIN
#define END 1                   //END
#define FOR 2                   //FOR
#define IF  3                   //IF
#define THEN 4                  //THEN
#define ELSE 5                  //ELSE
#define IDENTITY 6              //标识符
#define UNSIGNED 7              //无符号常数
#define COLON   8               //冒号：
#define PLUS    9               //加号+
#define STAR    10              //乘号*
#define  COMMA  11              //逗号,
#define LPARENTHESIS 12         //左括号(
#define RPARENTHESIS 13         //右括号)
#define ASSIGN 14               //赋值符号:=

/**
 * 保留字及其输出形式
 */
char reservedWords[RESERVESIZE][20] = {              
    "BEGIN",                                          
    "END",                                              
    "FOR",                                             
    "IF",                                             
    "THEN",                                            
    "ELSE"                                             
};
char reservedOut[RESERVESIZE][20] = {
    "Begin",
    "End",
    "For",
    "If",
    "Then",
    "Else"
};

/**
 * 判断是否是字母
 */
int isLetter(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    {
        return 1;
    }
    return 0;
}

/**
 *判断是否是数字 
 */
int isDigit(char c) {
    if (c >= '0' && c <= '9')
    {
        return 1;
    }
    return 0;
}

/**
 * 反复调用getchar(),直到ch进入一个非空白符，读到的非空白符会退回去
 * */
void getNbc(FILE *fp)
{
    char c;
    c = fgetc(fp);
    while ((c == ' ') || (c == '\n') || (c == '\r') || (c == '\t'))
    {
        c = fgetc(fp);
    }
    ungetc(c, fp);
}

/**
 * 判断token中的字符串是保留字还是标识符
 * return -1:表示标识符
 *        0-RESERVESIZE-1：表示保留字
 */
int reserve(char *token) {
    int i;
    for ( i = 0; i < RESERVESIZE; i++)
    {
        if (strcmp(reservedWords[i], token) == 0)
        {
            return i;
        }
    }
    return -1;
}

/**
 * 连接函数
 */
void mystrcat(char str[], char c) {
    int len = strlen(str);
    str[len] = c;
    str[len + 1] = '\0';
}

/**
 * 字符串转换为数字
 */
int myatoi(char *token) {
    int ans = 0;
    char *p = token;
    while (*p != '\0')
    {
        ans = ans * 10 + (*p - '0');
        p++;
    }
    return ans;
}

/**
 * 输出函数
 **/
void myprint(int type, char *token) {

    //保留字
    if (type < RESERVESIZE)
    {
        printf("%s\n", reservedOut[type]);
    }

    //标识符
    else if (type == IDENTITY)
    {
        printf("Ident(%s)\n", token);
    }
    
    //无符号整数类型
    else if (type == UNSIGNED)
    {
        int out = myatoi(token);
        printf("Int(%d)\n", out);
    } 

    //冒号:
    else if (type == COLON)
    {
        printf("Colon\n");
    }
    
    //加号+
    else if (type == PLUS)
    {
        printf("Plus\n");
    }

    //乘号*
    else if (type == STAR)
    {
        printf("Star\n");
    }

    //逗号,
    if (type == COMMA)
    {
        printf("Comma\n");
    }
    
    //左括号(
    if (type == LPARENTHESIS)
    {
        printf("LParenthesis\n");
    }

    //右括号)
    if (type == RPARENTHESIS)
    {
        printf("RParenthesis\n");
    }
    
    //赋值号:=
    if (type == ASSIGN)
    {
        printf("Assign\n");
    }
}

char ch;                //存入当前读入的字符
char token[MAXSIZE];    //存放单词字符串

int main(int argc, char const *argv[])
{
    char inputFilePath[MAXSIZE];
    strcpy(inputFilePath, argv[1]);
    FILE *fp;
    fp = fopen(inputFilePath, "r");
    // fp = fopen("input.txt", "r");
    while (1)
    {
        memset(token, '\0', MAXSIZE);
        getNbc(fp);
        ch = fgetc(fp);
        if (isLetter(ch))
        {
            while (isLetter(ch) || isDigit(ch))
            {
                mystrcat(token, ch);
                ch = fgetc(fp);
            }
            ungetc(ch, fp);
            int flag = reserve(token);
            if (flag == -1)
            {
                myprint(IDENTITY, token);
            }
            else {
                myprint(flag, token);
            }
            continue;
        }
        else if (isDigit(ch))
        {
            while (isDigit(ch))
            {
                mystrcat(token, ch);
                ch = fgetc(fp);
            }
            ungetc(ch, fp);
            myprint(UNSIGNED, token);
            continue;
        }
        else if (ch == '+')
        {
            myprint(PLUS, token);
        } 
        else if (ch == '*')
        {
            myprint(STAR, token);
        }
        else if (ch == ',')
        {
            myprint(COMMA, token);
        }
        else if(ch == '(')
        {
            myprint(LPARENTHESIS, token);
        }
        else if (ch == ')')
        {
            myprint(RPARENTHESIS, token);
        }
        else if (ch == ':')
        {
            ch = fgetc(fp);
            if (ch == '=')
            {
                myprint(ASSIGN, token);
            }
            else {
                ungetc(ch, fp);
                myprint(COLON, token);
            }  
        }
        else if (ch == EOF)
        {
            break;
        }
        else {
            printf("Unknown\n");
            break;
        }                
    }
    return 0;
}