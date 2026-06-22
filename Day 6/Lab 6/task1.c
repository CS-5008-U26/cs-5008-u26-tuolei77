/* This program reads the first 20 cities from uscities.csv.
 * It prints the sum of their populations and the northernmost city.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct city_struct {

    char *name;
    char *nameASCII;
    char *postalCode;
    char *stateName;
    char *FIPS;
    char *countyName;
    double latitude;
    double longitude;
    int population;

} city;


/* 删除字符串末尾的换行符 */
void killNewline (char *str) {
    int len = strlen(str);  // 获取字符串长度

    if (len > 0 && str[len - 1] == '\n') {  // 如果最后一个字符是换行符
        str[len - 1] = '\0';  // 用'\0'替换，截断字符串
    }
}

/* 删除字符串两端的引号 */
void killQuotes (char *str) {
    int len = strlen(str);  // 获取字符串长度

    if (len >= 2 && str[0] == '"' && str[len - 1] == '"') {  // 如果首尾都是引号
        str[len - 1] = '\0';          // 删除末尾引号
        memmove(str, str + 1, len - 1);  // 把整个字符串向左移一位，覆盖开头引号
    }
}

/* 从start开始读取下一个分隔符隔开的字段，存入out，返回指向下一个字段起始位置的指针 */
char *getNextField (char *start, char separator, char *out) {

    if (start == NULL || *start == '\0') {  // 特殊情况：没有更多字段了
        return NULL;
    }

    char *sepPointer = strchr(start, separator);  // 找到下一个分隔符的位置

    if (sepPointer == NULL) {  // 没找到分隔符，说明这是最后一个字段

        strcpy(out, start);      // 把剩余整个字符串复制到out
        killQuotes(out);         // 去掉引号
        return start + strlen(start);  // 返回指向字符串末尾'\0'的指针

    } else {  // 找到了分隔符

        strncpy(out, start, sepPointer - start);  // 复制从start到分隔符之间的内容到out
        out[sepPointer - start] = '\0';            // 手动加'\0'结尾，因为strncpy不保证
        killQuotes(out);                           // 去掉引号
        return sepPointer + 1;  // 返回分隔符后一位，即下一个字段的起始位置

    }
}

city *stringToCity (char *textLine) {

    char fieldBuffer[1000];  // 临时缓冲区，存每次读出来的一个字段
    char *p = textLine;      // 指针p指向当前行的起始位置
    int fieldNum = 0;        // 记录当前读到第几个字段
    city *c = malloc(sizeof(city));  // 在堆上分配一个city struct，返回指针

    while (p != NULL) {  // p为NULL说明没有更多字段了

        p = getNextField(p, ',', fieldBuffer);  // 读下一个逗号分隔的字段，存入fieldBuffer，p移动到下一字段起始位置
        if (p == NULL) {
            break;  // 没有更多字段，退出循环
        }
        fieldNum++;  // 字段编号+1
        switch (fieldNum) {
            case 1: c->name = strdup(fieldBuffer); break;       // 城市名，复制字符串存入struct
            case 2: c->nameASCII = strdup(fieldBuffer); break;  // ASCII城市名
            case 3: c->postalCode = strdup(fieldBuffer); break; // 州缩写
            case 4: c->stateName = strdup(fieldBuffer); break;  // 州名
            case 5: c->FIPS = strdup(fieldBuffer); break;       // 县FIPS码
            case 6: c->countyName = strdup(fieldBuffer); break; // 县名
            case 7: c->latitude = atof(fieldBuffer); break;     // 纬度，字符串转double
            case 8: c->longitude = atof(fieldBuffer); break;    // 经度，字符串转double
            case 9: c->population = atoi(fieldBuffer);          // 人口，字符串转int
        }
        if (fieldNum >= 9) {
            break;  // 9个字段都读完了，退出循环
        }
    }
    return c;  // 返回填好数据的city指针
}

city** readCityList (char *filename) {
    
    city **cityArray = malloc(20 * sizeof(city*));  // 在堆上分配20个city指针的数组
    FILE *f = fopen(filename, "r");  // 打开文件

    if (f == NULL) {  // 文件打不开，打印错误并返回
        printf("文件不存在！\n");
        free(cityArray);
        return NULL;
    }

    char buffer[20000];  // 缓冲区，存每一行的文本

    fgets(buffer, 20000, f);  // 跳过第一行（列名）

    for (int i = 0; i < 20; i++) {  // 读取接下来20行
        fgets(buffer, 20000, f);    // 读一行
        killNewline(buffer);         // 删除末尾换行符
        cityArray[i] = stringToCity(buffer);  // 解析这行，创建city struct，存入数组
    }

    fclose(f);  // 关闭文件
    return cityArray;  // 返回指针数组
}

/* 释放一个city struct及其所有堆上分配的字符串字段 */
void freeCity (city *c) {
    free(c->name);        // 释放城市名
    free(c->nameASCII);   // 释放ASCII城市名
    free(c->postalCode);  // 释放州缩写
    free(c->stateName);   // 释放州名
    free(c->FIPS);        // 释放县FIPS码
    free(c->countyName);  // 释放县名
    free(c);              // 最后释放struct本身
}

int main () {

    // 读取前20个城市
    city **cityArray = readCityList("uscities.csv");

    if (cityArray == NULL) {
    return 1;  // 文件读取失败，退出程序
}

    // 打印20个城市的名字和人口
    for (int i = 0; i < 20; i++) {
        printf("%s, population %d\n", cityArray[i]->name, cityArray[i]->population);
    }

    // 从控制台读取用户输入
    char buffer[100];
    while (1) {
        printf("Enter a city number: ");
        fgets(buffer, 100, stdin);  // 读取一行输入

        int num = atoi(buffer);  // 转换为整数，如果直接回车atoi返回0

        if (num <= 0 || num > 20) {  // 超出范围或直接回车，退出
            break;
        }

        // 打印对应城市信息，num-1因为数组从0开始
        printf("%s %s, population %d\n",
            cityArray[num - 1]->name,
            cityArray[num - 1]->postalCode,
            cityArray[num - 1]->population);
    }

    // 释放所有city struct
    for (int i = 0; i < 20; i++) {
        freeCity(cityArray[i]);
    }
    free(cityArray);  // 释放指针数组本身

    return 0;
}