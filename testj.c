#include "document.h"
#include "writer.h"
#include "stringbuffer.h"
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>

#define TRUE 1
#define FALSE 0
#define N 100000

using namespace rapidjson;

//字符串删除
//每次从当前的str中搜寻子串，没有找到就返回NULL，
//找到就返回子串在str中的尾部的下一个指针
char* match(char *str, char *want){
	while(*want != '\0'){
		//如果str先到达尾部，也会是NULL
        	if(*str++ != *want++){
			return NULL;
		}
	}
    	return str;
}
 
int del_substr(char *str, char *substr){
	char *next;
    	while(*str != '\0' ){
		next = match(str, substr);
        	//找到substr
        	if(next != NULL){
			break;
		}
        	str++;
	}
    	//如果str指向了尾部，说明没有找到
    	if(*str == '\0'){
		return FALSE;
	}
    	//将查找到的子串的尾部拷贝到查找到的子传的首部
    	while(*str != '\0'){
        	*str++ = *next++;
	}
    	return TRUE;
}

//字符串特定子串删除（宽字符）
//每次从当前的str中搜寻子串，没有找到就返回NULL，
//找到就返回子串在str中的尾部的下一个指针
wchar_t* wmatch(wchar_t *str, wchar_t *want){
        while(*want != '\0'){
                //如果str先到达尾部，也会是NULL
                if(*str++ != *want++){
                        return NULL;
                }
        }
        return str;
}

int wdel_substr(wchar_t *str, wchar_t *substr){
        wchar_t *next;
        while(*str != '\0' ){
                next = wmatch(str, substr);
                //找到substr
                if(next != NULL){
                        break;
                }
                str++;
        }
        //如果str指向了尾部，说明没有找到
        if(*str == '\0'){
                return FALSE;
        }
        //将查找到的子串的尾部拷贝到查找到的子传的首部
        while(*str != '\0'){
                *str++ = *next++;
        }
        return TRUE;
}

//字符串替换
void str_replace(char * cp, int n, char * str)
{
        int lenofstr;
        int i;
        char * tmp;
        lenofstr = strlen(str);
        //str3比str2短，往前移动
        if(lenofstr < n)
        {
                tmp = cp+n;
                while(*tmp)
                {
                        *(tmp-(n-lenofstr)) = *tmp; //n-lenofstr是移动的距离
                        tmp++;
                }
                *(tmp-(n-lenofstr)) = *tmp; //move '\0'
        }
        else
                //str3比str2长，往后移动
                if(lenofstr > n)
                {
                        tmp = cp;
                        while(*tmp) tmp++;
                        while(tmp>=cp+n)
                        {
                                *(tmp+(lenofstr-n)) = *tmp;
                                tmp--;
                        }
                }
        strncpy(cp,str,lenofstr);
}

//字符串替换（宽字符）
void wstr_replace(wchar_t * cp, int n, wchar_t * str)
{
        int lenofstr;
        int i;
        wchar_t * tmp;
        lenofstr = wcslen(str);
        //str3比str2短，往前移动
        if(lenofstr < n)
        {
                tmp = cp+n;
                while(*tmp)
                {
                        *(tmp-(n-lenofstr)) = *tmp; //n-lenofstr是移动的距离
                        tmp++;
                }
                *(tmp-(n-lenofstr)) = *tmp; //move '\0'
        }
        else
                //str3比str2长，往后移动
                if(lenofstr > n)
                {
                        tmp = cp;
                        while(*tmp) tmp++;
                        while(tmp>=cp+n)
                        {
                                *(tmp+(lenofstr-n)) = *tmp;
                                tmp--;
                        }
                }
        wcsncpy(cp,str,lenofstr);
}


//删除指定Unicode编码的字符
void del_uni(wchar_t str[]){
	wchar_t* u0=(wchar_t *)malloc(50);
	char* s0="\uFFF0";
	mbstowcs(u0, s0, 10);
	wdel_substr(str,u0);

	char* s1="\uFFF1";
        mbstowcs(u0, s1, 10);
        wdel_substr(str,u0);

	char* s2="\uFFF2";
        mbstowcs(u0, s2, 10);
        wdel_substr(str,u0);

	char* s3="\uFFF3";
        mbstowcs(u0, s3, 10);
        wdel_substr(str,u0);

	char* s4="\uFFF4";
        mbstowcs(u0, s4, 10);
        wdel_substr(str,u0);

	char* s5="\uFFF5";
        mbstowcs(u0, s5, 10);
        wdel_substr(str,u0);

	char* s6="\uFFF6";
        mbstowcs(u0, s6, 10);
        wdel_substr(str,u0);

	char* s7="\uFFF7";
        mbstowcs(u0, s7, 10);
        wdel_substr(str,u0);

	char* s8="\uFFF8";
        mbstowcs(u0, s8, 10);
        wdel_substr(str,u0);

	char* s9="\uFFF9";
        mbstowcs(u0, s9, 10);
        wdel_substr(str,u0);

	char* sa="\uFFFA";
        mbstowcs(u0, sa, 10);
        wdel_substr(str,u0);

	char* sb="\uFFFB";
        mbstowcs(u0, sb, 10);
        wdel_substr(str,u0);

	char* sc="\uFFFC";
        mbstowcs(u0, sc, 10);
        wdel_substr(str,u0);

	char* sd="\uFFFD";
        mbstowcs(u0, sd, 10);
        wdel_substr(str,u0);

	char* se="\uFFFE";
        mbstowcs(u0, se, 10);
        wdel_substr(str,u0);

	char* sf="\uFFFF";
        mbstowcs(u0, sf, 10);
        wdel_substr(str,u0);
	
	free(u0);
	u0 = NULL;
	
}

//删除指定ASCII编码的字符
void del_asc(char str[]){
	for(int i = 0;str[i]!='\0'; i++){
		if(str[i]>=0 && str[i]<32 && str[i]!='\t' && str[i]!='\n'){
			char d[]={str[i],'\0'};
			del_substr(str,d);
		}
	}
}

//空格替换
void blank_re(char str[]){
	char* b1="\u0020";
	char* b2="\u00A0";
	char* b3="\u3000";
	
	char* p=strstr(str,b2);
        while(p){
                //每找到一个str2，就用str3来替换
                str_replace(p,strlen(b2),b1);
                p = p+strlen(b1);
                p = strstr(p,b2);
        }

	p=strstr(str,b3);
        while(p){
                //每找到一个str2，就用str3来替换
                str_replace(p,strlen(b3),b1);
                p = p+strlen(b1);
                p = strstr(p,b3);
        }



}
//字符串中特定子串的替换
char *strrpc(char *str,char *oldstr,char *newstr){
    char bstr[strlen(str)];//转换缓冲区
    memset(bstr,0,sizeof(bstr));
 
    for(int i = 0;i < strlen(str);i++){
        if(!strncmp(str+i,oldstr,strlen(oldstr))){//查找目标字符串
            strcat(bstr,newstr);
            i += strlen(oldstr) - 1;
        }else{
        	strncat(bstr,str + i,1);//保存一字节进缓冲区
	    }
    }
 
    strcpy(str,bstr);
    return str;
} 

//去除多行空格和多个连续空格
void blank_con(char body[]){
	char con[]="<p></p><p></p>";
        char* blank=strstr(body,con);
        char* n="  ";
	char* bn=strstr(body,n);
	char* newc="<p></p>";
	char* newn=" ";

	while(blank!=NULL && bn!=NULL){
		strrpc(body,con,newc);
		strrpc(body,n,newn);
		blank=strstr(body,con);
		bn=strstr(body,n);
	}
}

//半角转全角
void half_convert(wchar_t str[]){
	int c1 = 1;
        int c2 =1;

        //替换"
        char* wdel2="&quot;";
        char* wt="\"";
        wchar_t del2[9];
        wchar_t t[9];
        mbstowcs(del2, wdel2, 10);
        mbstowcs(t, wt, 10);


        wchar_t* p=wcsstr(str,del2);
        while(p){
                if(*(p+6)>127 && *(p-1)>127){
                        //每找到一个str2，就用str3来替换
                        wstr_replace(p,wcslen(del2),t);
                        p = p+wcslen(t);
                }
                else{
                        p++;
                }
                p = wcsstr(p,del2);

        }
	
	//替换;

        char* wdel3="&amp;";
        char* wt1=";";
        wchar_t del3[9];
        wchar_t t1[9];
        mbstowcs(del3, wdel3, 10);
        mbstowcs(t1, wt1, 10);

        wchar_t* p3=wcsstr(str,del3);
        while(p3){
                if(*(p3+5)>127 && *(p3-1)>127){
                        //每找到一个str2，就用str3来替换
                        wstr_replace(p3,wcslen(del3),t1);

                        p3 = p3+wcslen(t1);
                }
                else{
                        p3++;
                }
                p3 = wcsstr(p3,del3);

        }
	
	for(int i=1;str[i+1];i++){
                if(str[i-1]>127 && str[i+1]>127){


                        if(str[i] == 44){
                                str[i] += 65248;//逗号
                        }
                        if(str[i] == 46){
                                str[i] = 0x3002;//句号
                        }
                        if(str[i] == 60){
                                str[i] = 0x300a;//书名号左
                        }
                        if(str[i] == 62){
                                str[i] = 0x300b;//书名号右
                        }
                        if(str[i] == 63){
                                str[i] += 65248;//问号
                        }
                        if(str[i] == 33){
                                str[i] += 65248;//感叹号
                        }
                        if(str[i] == 59){
                                str[i] += 65248;//分号
                        }
                        if(str[i] == 58){
                                str[i] += 65248;//冒号
                        }
                        if(str[i] == 34){
                                if(c1 % 2 == 1){//第一个双引号
                                        str[i] = 0x201c;
                                }
                                if(c1 % 2 == 0){//第二个双引号
                                        str[i] = 0x201d;
                                }
                                c1++;
                        }
			if(str[i] == 39){
                                if(c2 % 2 == 1){//第一个单引号
                                        str[i] = 0x2018;
                                }
                                if(c2 % 2 == 0){//第二个单引号
                                        str[i] = 0x2019;
                                }
                                c2++;
                        }
                        if(str[i] == 40){//左括号
                                str[i] = 0xFF08;
                        }
                        if(str[i] == 41){//右括号
                                str[i] = 0xFF09;
                        }
                        if(str[i] == 91){//左方括号
                                str[i] = 0x3014;
                        }
                        if(str[i] == 93){//右方括号
                                str[i] = 0x3015;
                        }
                        if(str[i] == 45){//破折号
                                str[i] = 0x2014;
                        }
                }
                if(str[i]==12288){
                        str[i] = 32;//空格转换
                }
                if(str[i]==160){
                        str[i] = 32;//空格转换
                }
        }
}

void full_convert(char str[]){
        for(int i=0;str[i];i++){
                if(str[i]>65280 && str[i]<65375){
                        str[i] -= 65248;//英文、数字符号转半角
                }
                if(str[i]==12288){
                        str[i] = 32;//空格转换
                }
                if(str[i]==160){
                        str[i] = 32;//空格转换
                }
                
        }
        
}

//对body文本做处理
void editstr(char str[],char* lang){
	
	char* z="zh";
	char* e="en";
	char* del1="\n";
	
	//删除换行符
	del_substr(str,del1);
	
	//连续空行空格
	blank_con(str);

	if(strcmp(lang,z)==0){
		wchar_t *pwcs = (wchar_t *)malloc(4194300);
        	mbstowcs(pwcs, str, 4194300);
        
		//文本处理
		//unicode
		del_uni(pwcs);

		//标点符号
		half_convert(pwcs);        	
        	wcstombs(str, pwcs,4194300);
		free(pwcs);
		pwcs = NULL;
	}
	if(strcmp(lang,e)==0){
		//ascii
		del_asc(str);

		//标点符号
                full_convert(str);


	}

}

//解析json
int exejson(FILE* fd,FILE* ft)
{
	setlocale(LC_ALL, "");
	int c=1;
	Document d;
	while(c<N+1){
		char* pc=(char *)malloc(4194304);
		char* la=(char *)malloc(10);
		char json[3194303];
		fgets(json,sizeof(json),fd);
    		d.Parse(json);

		// 2. 利用 DOM 作出修改。
    		Value& s = d["body"];
		Value& l = d["lang"];
		const char* sv = s.GetString();		
		const char* lv = l.GetString();
                
		strcpy(pc,sv);
		strcpy(la,lv);
		editstr(pc,la);
		
		s.SetString(StringRef(pc));

		// 3. 把 DOM 转换（stringify）成 JSON。
    		StringBuffer buffer;
    		Writer<StringBuffer> writer(buffer);
    		d.Accept(writer);
 
    		// Output		
        	if(ft==NULL){
			return -1;
		}
	        //写入
		fprintf(ft,"%s\n",buffer.GetString());

		//printf("c=%d\n",c++);
		c++;
		free(pc);
		pc = NULL;
		free(la);
		la = NULL;	
	}

	//关闭文件
	fclose(fd);
	fclose(ft);
	d.SetObject();

}
//字符串从右侧开始取一定长度的子串
char *right(char *dst,char *src,int n)
{
	char *p=src;
	char *q=dst;
	int len=strlen(src);
	if(n>len) n=len;
	p+=(len-n);
	while(*(q++)=*(p++));
	return dst;
}

int main(){

        char* name[100];
	char* n = "files.txt";
	FILE *tp=fopen(n,"rb");
	char* st="100000 ";
        if(tp==NULL)
        {
                printf("can not load file!");
                return -1;
        }
	int c=1;
	while(c<112)
        {
                fgets(name,100,tp);
		if(c>1){
			del_substr(name,st);
			name[27]='\0';
			FILE* fd=fopen(name,"r");
        		if(fd==NULL)
        		{
                		printf("error\n");
                		printf("%s\n",name);
                		return -1;
        		}
        		char outname[100]="/data/processed";
        		strcat(outname,name);
        		FILE* ft = fopen(outname,"w");
			exejson(fd,ft);
			
		}
			printf("%d\n",c++);	
	}
	fclose(tp);
}
