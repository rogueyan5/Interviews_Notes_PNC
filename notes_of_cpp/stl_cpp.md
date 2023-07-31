# 一、标准库类型string
## 1.1 定义和初始化
```cpp
string s1;              //默认初始化，s1是一个空串
string s2(s1);          //s2是s1的副本
string s2 = s1;         //等价于s2(s1)，s2是s1的副本
string s3("value");     //s3是字面值“value”的副本，除了字面值最后的那个空字符
string s3 = "value";    //等价于s3("value),s3是字面值“value”的副本
string s4(n, 'c');      //把s4初始化为由连续n个字符c组成的串
```
## 1.2 string支持的操作
- **getline()，读入一行字符串**
```cpp
//第一种用法
istream& getline(char* s, streamsize n);
istream& getline(char* s, streamsize n, char delim);
//此种方法是从istream中读取至多n个字符（包括结束标记符）保存到s对应的数组中。即使还没读够n个字符，如果遇到delim标识符或字数达到限制，则读取终止，delim标识符会被读取，但是不会被保存到s对应的数组中

//第二种用法
istream& getline(istream&  is, string& str, char delim);
istream& getline(istream&& is, string& str, char delim);
istream& getline(istream&  is, string& str);
istream& getline(istream&& is, string& str);
//用法和第一种类似，但是读取的istream是作为参数is传入函数的。读取的字符串保存到string类型的str中
```
getline()函数从给定的输入流中读入内容，直到遇到换行符为止（换行符也会被读入），将所读取的内容存入到对应的string对象中去。
- 字面值和string对象相加
标准库运行将字符字面值和字符串字面值转换成string对象，所以在需要string对象的地方就可以使用这两种字面值来替代。当把string对象和字符字面值即字符串字面值混在一条语句中使用时，必须**确保每个加法运算符的两侧运算对象至少有一个string**
```cpp
string s4 = s1 + ",";       //正确
string s5 = "hello" + ","   //错误，两个均不是string
```
- **字符串剪切**

string类本身没有提供切割的方法，可以使用stl提供的封装进行实现或通过C函数实现。
1. substr()函数

substr()时C++语言函数，主要功能是复制子字符串，要求从指定位置开始，并具有特定的长度。如果没有指定长度__count或__count+__off超出了源字符串的长度，则子字符串将延续到字符串的结尾。
```cpp
substr(size_t pos = 0, size_t len = npos) const;
//pos:要复制的第一个字符所在的索引  len:复制的子串的长度

//exp
std::string str = "we think in generalities, but we live in details";

std::string str2 = str.substr(3, 5);        //str2 = "think"
std::size_t pos = str.find("live");         //position of "live" in str
std::string str3 = str.substr(pos);         //get from "live" to the end
```
2. strtok()函数

strtok()函数用来将字符串分割成一个个的片段，参数s指向将要被分隔的字符串，参数delim为分隔的字符串，当strtok()在参数s的字符串中发现到参数delim的分隔字符时，则会将该字符改为“\0”字符，在第一次调用时strtok()必须给予参数s字符串，之后的调用则将参数设置成NULL，每次调用成功则返回被分隔片段的指针。
```cpp
char sentence[] = "This is a sentence with 7 tokens";
char *tokenPtr = strtok(sentence, " ");
 while(tokenPtr!=nullptr) {
    cout << tokenPtr << "\n";
    tokenPtr = strtok(nullptr, " ");
 }
 ```

 3. boost库中的split()函数
```cpp
std::string s = "sss/ddd,ggg";
std::vector<string> vStr;
boost::split(Vstr, s, boost::is_any_of(",/"), boost::token_compress_on);
//split()函数将s按条件分割并存入了vector中
```
- **对string中的字符进行处理**

```cpp
isalnum(c)              //当c是字符或数字时为真
isalpha(c)              //当c时字母时为真
iscntrl(c)              //当c是控制字符时为真
isdigit(c)              //当c是数字时为真
isgraph(c)              //当c不是空格但可打印时为真
islower(c)              //当c是小写字母时为真
ispunct(c)              //当c时标点符号时为真
isprint(c)              //的那个c是可打印字符时为真
isspace(c)              //当c时空白时为真，包括空格、横向制表符、纵向制表符、回车符时为真
isupper(c)              //是大写字母时为真
isxdigit(c)             //是十六进制的数字为真
tolower(c)              //转换为小写
toupper(c)              //转换为大写
```

- **strcpy()函数**


# 二、vector
## 2.1 概述
- vector是可变大小的数组
- 特点：
  - 支持快速随机访问。在尾部之外的位置插入或者删除元素可能很慢
  - 元素保存在连续的内存空间中，因此通过下标取值非常快
  - 在容器中间位置添加或删除元素非常耗时
  - 一旦vector内存不足，重新申请内存后，和原vector相关的指针、引用、迭代器都失效。内存重分配耗时很长。
- 通常情况下使用vector是较好的选择，如果没有特殊要求优先使用vector:<br>
vector:可变大小数组，支持随机快速访问，在尾部之外的位置插入或删除元素可能很慢
deque:双端队列，支持随机快速访问，在头尾插入或删除元素很快<br>
list:双向链表，只支持双向顺序访问，在list中任何位置插入和删除的速度都很快<br>
forward_list:单向链表，只支持单项顺序访问，在链表任意位置进行插入和删除的速度都很快<br>
array:固定大小数组，支持快速随机访问，不能添加或删除元素<br>
string:和vector类似的容器，但专门用于保存字符，随机访问快，在尾部插入或删除元素速度快<br>

# 2.2 vector定义
vector定义在<stl_vector.h> <vector.h>头文件中




# 三、list


# 四、deque


# 五、stack

# 六、queue

# 七、priority_queue

# 八、tree

# 九、set

# 十、map


