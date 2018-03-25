/*一些bug
 * 命名了一个叫sp的数组 可以在变量名+& 不过增加解析的难度
 *
 *
 */




#include <bits/stdc++.h>

#define STACK_SIZE (1<<30)
#define PUSH (sp=(void*)((char *)(sp)+8))
#define POP  (sp=(void*)((char *)(sp)-8))
#define GET_INT(p) 	(*(int *)(p))
#define GET_LONG(p) (*(long *)(p))
#define SET_INT(p,val) ((*(int *)(p))=(val))
#define SET_LONG(p,val) ((*(long *)(p))=(val))
#define GET_TYPE(p) (Map[Hash(p)]) //为switch
#define LEA(p,x) ((void*)((char*)(p)+(x))) //得到指针偏移x个 字节 后指针
#define REGIS(p,x) ((void*)((long*)(p)+(x))) //得到指针偏移 8*x字节的指针 因为long是8个字节 8个字节8个字节偏移

//为了switch
#define PLUS 1 //+
#define SUB  2
#define MULTIPLY 3
#define DIV  4
#define MOD  5
#define BIG  6
#define SMALL 7
#define EQUAL 8
#define BIGEQU 9
#define SMALEQU 10
#define EQUEQU 11
#define PUSHSTACK 12
#define ADD 13 //add
#define JT 14
#define JF 15
#define CALL 16
#define RET 17
#define JUMP 18 // >
#define LOG_OR 19
#define LOG_AND 20
#define OR 21
#define XOR 22
#define AND 23
#define NOTEQU 24
#define MOVE_LEFT 25
#define MOVE_RIGHT 26
#define ADDAR 27
#define BUF_SIZE 128
using namespace std;
vector<char *>v;
unordered_map<long,int>Map;
unordered_map<string,vector<void*>> symbol_list;
unordered_map<string,vector<void*>> array_list;
stack<long>s;
char buf[BUF_SIZE];
void *bp,*sp,*regis;
long ltmpnum,rtmpnum,a,j;
long pc;



long Hash(const char *);
void *find(string str){//找到变量名第一个有效的指针
    vector<void*> &tmpv=symbol_list[str];
    int id=(int)tmpv.size()-1;
    while(id>=0&&tmpv[id]>=sp){
        tmpv.pop_back();
        id--;
    }
    return tmpv[id];
}
void add(string str){//添加变量名的指针
    if(!symbol_list.count(str)) {
        symbol_list[str].push_back(sp);
        return ;
    }
    vector<void*> &tmpv=symbol_list[str];
    int id=(int)tmpv.size()-1;
    while(id>=0&&tmpv[id]>=sp){
        tmpv.pop_back();
        id--;
    }
    tmpv.push_back(sp);
}
void addar(string str){
    if(!array_list.count(str)) {
        array_list[str].push_back(sp);
        return ;
    }
    vector<void*> &tmpv=array_list[str];
    int id=(int)tmpv.size()-1;
    while(id>=0&&tmpv[id]>=sp){
        tmpv.pop_back();
        id--;
    }
    tmpv.push_back(sp);
}
void *findar(string str){
    vector<void*> &tmpv=array_list[str];
    int id=(int)tmpv.size()-1;
    while(id>=0&&tmpv[id]>=sp){
        tmpv.pop_back();
        id--;
    }
    return tmpv[id];
}
char* get_identifier(char *buf);

char* get_identifier(char *buf){
    //printf("oooo\n");
    char *ret=(char *)malloc(BUF_SIZE);
    char *tmp=ret;
    if(isalpha(*buf)){

        while(isalnum(*buf)){

            *tmp=*buf;
            buf++;
            tmp++;
        }
    }
    *tmp=0;
    //printf("%s\n",ret);
    return ret;
}
long Hash(const char* str){//
    long res=0;
    while(*str){
        res=res*10007+*str;
        str++;
    }
    return res;
}

void init(){//可以在这里添加
    Map[Hash("+")]=PLUS;
    Map[Hash("-")]=SUB;
    Map[Hash("*")]=MULTIPLY;
    Map[Hash("/")]=DIV;
    Map[Hash("%")]=MOD;
    Map[Hash(">")]=BIG;
    Map[Hash("<")]=SMALL;
    Map[Hash("=")]=EQUAL;
    Map[Hash(">=")]=BIGEQU;
    Map[Hash("<=")]=SMALEQU;
    Map[Hash("==")]=EQUEQU;
    Map[Hash("push")]=PUSHSTACK;
    Map[Hash("add")]=ADD;
    Map[Hash("jt")]=JT;
    Map[Hash("jf")]=JF;
    Map[Hash("call")]=CALL;
    Map[Hash("ret")]=RET;
    Map[Hash("jump")]=JUMP;
    Map[Hash("||")]=LOG_OR;
    Map[Hash("&&")]=LOG_AND;
    Map[Hash("|")]=OR;
    Map[Hash("^")]=XOR;
    Map[Hash("&")]=AND;
    Map[Hash("!=")]=NOTEQU;
    Map[Hash("<<")]=MOVE_LEFT;
    Map[Hash(">>")]=MOVE_RIGHT;
    Map[Hash("addar")]=ADDAR;
}
long get_num(char *p){//得到一个正负的数字 第一个非法返回0 和后面搭配使用
    long ans=0;
    long flag=1;
    if(*p=='+') p++;
    else if(*p=='-') flag=-1,p++;
    else if(!isdigit(*p)) return 0;
    while(isdigit(*p)){
        ans=ans*10+*p-48;
        p++;
    }
    return flag*ans;
}
//有bug a=1+2 有两个tmp_num 现在简单测一测四元式的问题
void *work(char *str,bool type){//解析一个表达式中的一个单元 如+ a b c 解析的是 a 这种  返回的是指向这个变量的指针
    if(!strcmp(str,"bp")) return (void*)&bp;//这里返回的是二级指针 因为要操控的是bp 不是bp指向的值
    if(!strcmp(str,"sp")) return (void*)&sp;//同上
    if(!strcmp(str,"pc")) return (void*)&pc;//返回的指向pc的指针
    long num;
    switch (str[0]){
        case '%'://寄存器
            if(str[1]=='a') return (void *)&a;
            if(str[1]=='j') return (void *)&j;
            num=get_num(str+1);
            return REGIS(regis,num);
            break;
        case '('://解引用
            //printf("offff \n");
            if(str[1]=='s'){
                num=get_num(str+3);//如果没有+ - 返回就是0 不矛盾
                return LEA(sp,num);
            }
            else if(str[1]=='b'){
                num=get_num(str+3);
                return LEA(bp,num);
            }
            else{//
                char *p=get_identifier(str+1);

                num=get_num(str+3+strlen(p));
                void *base=findar(p);
                return LEA(base,8*(*(long*)(REGIS(regis,num))));
            }
            break;
        default://变量或是数字
            if(isalpha(str[0])){
                return find(str);
            }
            else if(isdigit(str[0])){
                if(!type){
                    ltmpnum=get_num(str);
                    return (void*)&ltmpnum;
                }
                else{
                    rtmpnum=get_num(str);
                    return (void*)&rtmpnum;
                }
            }
            break;
    }

}
void calcu(char *first,char *second,char *third,int TYPE){//计算表达式
    long *res=(long*)work(third,0);//第三个参数
    long *ltype=(long*)work(first,0);//第一个参数
    long *rtype=(long*)work(second,1);//第二个参数
    switch (TYPE){//通过work返回的指针可以统一操作
        case PLUS:
            *res=*ltype+*rtype;
            break;
        case SUB:
            *res=*ltype-*rtype;
            break;
        case MULTIPLY:
            *res=(*ltype)*(*rtype);
            break;
        case DIV:
            *res=(*ltype)/(*rtype);
            break;
        case MOD:
            *res=(*ltype)%(*rtype);
            break;
        case BIG:
            *res=*ltype>*rtype;
            break;
        case SMALL:
            *res=*ltype<*rtype;
            break;
        case BIGEQU:
            *res=*ltype>=*rtype;
            break;
        case SMALEQU:
            *res=*ltype<=*rtype;
            break;
        case EQUEQU:
            *res=(*ltype==*rtype);
            break;
        case LOG_OR:
            *res=(*ltype)||(*rtype);
            break;
        case LOG_AND:
            *res=(*ltype)&&(*rtype);
            break;
        case OR:
            *res=(*ltype)|(*rtype);
            break;
        case XOR:
            *res=(*ltype)^(*rtype);
            break;
        case AND:
            *res=(*ltype)&(*rtype);
            break;
        case NOTEQU:
            *res=((*ltype)!=(*rtype));
            break;
        case MOVE_LEFT:
            *res=((*ltype)<<(*rtype));
            break;
        case MOVE_RIGHT:
            *res=((*ltype)>>(*rtype));
            break;
    }
}
void execute(char *buf){//取指令 pc++ 执行指令 //改接口
    //printf("%s\n",buf);
    char str_buf[BUF_SIZE];
    //while(isdigit(*buf)||*buf==' ') buf++;//跳过前面的第几个指令
    sscanf(buf,"%s",str_buf);//从指令里读取操作 如 + - push 等等
    buf+=strlen(str_buf);//buf 指针往后偏移操作数的长度

    char first[BUF_SIZE],second[BUF_SIZE],third[BUF_SIZE];
    long *res,*ltype,*rtype;
    switch (GET_TYPE(str_buf)){
//        case PLUS:
//            sscanf(buf,"%s %s %s",first,second,third);//buf里读参数
//            calcu(first,second,third,PLUS);
//            break;
        case EQUAL:
            //printf("im in\n");
            sscanf(buf,"%s %s",first,second);
            //printf("%s %s\n",first,second);
            ltype=(long*)work(first,0);
            rtype=(long*)work(second,1);
            *ltype=*rtype;
            break;
        case ADD:
            sscanf(buf,"%s",first);
            add(first);
            break;
        case PUSHSTACK:
            PUSH;
            break;
        case JT:
            sscanf(buf,"%s",first);
            if(j){
                res=(long*)work(first,0);
                pc=*res;
            }
            break;
        case JF:
            sscanf(buf,"%s",first);
            if(!j){
                res=(long*)work(first,0);
                pc=*res;
            }
            break;
        case ADDAR:
            sscanf(buf,"%s",first);
            addar(first);
            break;
        case CALL:
            //函数调用 保存寄存器的值 这里开了64个long的
            for(int i=0;i<64;i++) s.push(GET_LONG((long*)regis+i));
            pc=get_num(buf+1);//得到pc
            break;
        case RET:
            //返回寄存器的值
            for(int i=63;i>=0;i--) {
                long *tmp=(long*)regis+i;
                *tmp=s.top();
                s.pop();
            }
            sscanf(buf,"%s",first);
            pc=*(long*)work(first,0);//得到pc
            break;
        case JUMP:
            sscanf(buf,"%s",first);
            res=(long*)work(first,0);
            pc=*res;
            break;
        default:
            sscanf(buf,"%s %s %s",first,second,third);//buf里读参数
            calcu(first,second,third,GET_TYPE(str_buf));
            break;
    }

}
int main() {


    init();
    bp=sp=malloc(STACK_SIZE);
    void *test=bp;
    if(bp==NULL) {
        printf("malloc errro\n");
        exit(-1);
    }
    regis=malloc(8*64);
    pc=1;
    freopen("out.txt","r",stdin);
    //freopen("out","w",stdout);
    while(fgets(buf,BUFSIZ,stdin)!=NULL){//读指令
        char *tmp=(char *)malloc(BUF_SIZE);
        strcpy(tmp,buf);
        //if # 数据区

        if(*tmp=='#'){
            execute(tmp+2);
            free(tmp);
            continue;
        }
        while(isdigit(*tmp)||*tmp==' ') tmp++;
        v.push_back(tmp);
        //printf("%s\n",tmp);
    }
    int cnt=0;
    while(pc){
        std::cout<<pc<<"\n";
        cnt++;
        //printf("sp=%p %ld\nbp=%p %ld\n",sp,sp,bp,bp);
        execute(v[pc++]);
        //printf("sp=%p %ld\nbp=%p %ld\n",sp,sp,bp,bp);
        //if(cnt>=50) break;
    }
    cout<<a<<endl;//输出最后得到的a
    //可以输出排序后的数字
    cout<<"ans"<<endl;
    for(int i=0;i<100;i++){
        printf("%d\n",*(int*)((long*)test+i));
    }
    return 0;
}
