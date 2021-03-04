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



void del_uni(wchar_t str[]){
	wchar_t* u0=new wchar_t[20];
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
	
}

void del_asc(char str[]){
	for(int i = 0;str[i]!='\0'; i++){
		if(str[i]>=0 && str[i]<32 && str[i]!='\t' && str[i]!='\n'){
			char d[]={str[i],'\0'};
			del_substr(str,d);
		}
	}
}

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

void half_convert(wchar_t str[]){
	for(int i=0;str[i];i++){
		if(str[i]<127 && str[i]>33 && str[i]!=60 && str[i]!=62 && str[i]!=47 && str[i]!=92){
			str[i] += 65248;
		}
		if(str[i]==12288){
			str[i] = 32;
		}
		if(str[i]==160){
                        str[i] = 32;
                }
		if(str[i]>=65296 && str[i]<=65305){
			str[i] -= 65248;
		}
		if(str[i]>=65313 && str[i]<=65338){
                        str[i] -= 65248;
                }
		if(str[i]>=65345 && str[i]<=65370){
                        str[i] -= 65248;
                }
	}
	//printf("1\n");
	for(int i=1;str[i+1];i++){
		if(str[i-1]<=48 && str[i+1]<=57 && str[i]>65280){
			str[i] -= 65248;
		}
		if(str[i-1]<=65 && str[i+1]<=90 && str[i]>65280){
                        str[i] -= 65248;
                }
		if(str[i-1]<=97 && str[i+1]<=122 && str[i]>65280){
                        str[i] -= 65248;
                }
	}
}

void full_convert(char str[]){
        for(int i=0;str[i];i++){
                if(str[i]>65280 && str[i]<65375){
                        str[i] -= 65248;
                }
                if(str[i]==12288){
                        str[i] = 32;
                }
                if(str[i]==160){
                        str[i] = 32;
                }
                
        }
        
}


void editstr(char str[],char* lang){
	//char* gstr= "修改后修改后修改后修改后修改后修改后修改后修改后修改后修改后修改后修改后修改后修改后修改后修改后修改后修改后修改后修改后修改后修改后修改后修改后修改后修改后修改后修改后修改后修改后修改后修改后";
	//strcpy(str,gstr);
	//char *pmb = (char *)malloc(10000);
        //strcpy(pmb,str);
	char* z="zh";
	char* e="en";
	char* del1="\n";
	char* del2="&quot;";
	
	//删除换行符
	del_substr(str,del1);
	del_substr(str,del2);
	char* t="\"";
	char* p=strstr(str,del2);
        while(p){
		//每找到一个str2，就用str3来替换
                str_replace(p,strlen(del2),t);
                p = p+strlen(t);
                p = strstr(p,del2);
	}


	//空格替换
	

	//连续空行空格
	blank_con(str);

	if(strcmp(lang,z)==0){
		wchar_t *pwcs = (wchar_t *)malloc(20000);
        	//printf("转换回宽字符字符串\n");
        	mbstowcs(pwcs, str, 20000);
        	//setlocale(LC_ALL, "zh-CN");
        	//printf("%ls\n",pwcs);

		//文本处理
		//unicode
		del_uni(pwcs);

		//标点符号
		half_convert(pwcs);



        	//printf("转换为多字节字符串\n");
        	wcstombs(str, pwcs,20000);
        	//printf("%s\n",str);
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
int exejson(FILE* fd,FILE* ft)
{
	

	
	setlocale(LC_ALL, "");
	//printf("%s\n",filename);
	//打开JSON数据文件
	//FILE* fd=fopen(filename,"r");
	//if(fd==NULL)
	//{
	//	printf("error\n");
	//	printf("%s\n",filename);
	//	return -1;
	//}
	//char outname[100]="/home/yyh/workspace/res";
	//strcat(outname,filename);
	//printf("%s\n",outname);
	//FILE* ft = fopen(outname,"w");

	int c=1;
	//读取文件中的数据
	//char buf[5000]="0";

	Document d;

	//char* pc=new char[10000];
	char* pc=(char *)malloc(20000*sizeof(char));
	//char* la=new char[10];
	char* la=(char *)malloc(10*sizeof(char));
	while(c<N+1){
		char* pc=(char *)malloc(4194304);
		char* la=(char *)malloc(10);
		char json[3194303];
		fgets(json,sizeof(json),fd);

		//char* json = buf;

    		d.Parse(json);

		// 2. 利用 DOM 作出修改。
    		Value& s = d["body"];
		Value& l = d["lang"];
    		//s.SetString("要修改的内容文本");
		
		
		const char* sv = s.GetString();
		
		const char* lv = l.GetString();
                

		strcpy(pc,sv);
		strcpy(la,lv);
		editstr(pc,la);
		
		s.SetString(StringRef(pc));

		//setlocale(LC_ALL, "zh-CN");//将本地环境设置为简体中文。

		//printf("%s\n",s.GetString());
		//printf("%s\n",l.GetString());

		// 3. 把 DOM 转换（stringify）成 JSON。
    		StringBuffer buffer;
    		Writer<StringBuffer> writer(buffer);
    		d.Accept(writer);
 
    		// Output
    		//printf("%s\n",buffer.GetString());
		
        	if(ft==NULL){
			return -1;
		}
	        //写入
		fprintf(ft,"%s\n",buffer.GetString());

		printf("c=%d\n",c++);
		
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
	

	//char load_file[256];
        char* name=(char *)malloc(100*sizeof(char));
	char* n = "files.txt";
	FILE *tp=fopen(n,"rb");
	char* st="100000 ";
        if(tp==NULL)
        {
                printf("can not load file!");
                return -1;
        }
	int c=1;
	//char buf[5000]="0";
	//char* pc=(char *)malloc(20000*sizeof(char));
	while(c<111)
        {
                fgets(name,100,tp);


		if(c>1){
			//name="100000 /data/raw/2021-01-20_7.json";
			//char* fn=(char *)malloc(100*sizeof(char));
			del_substr(name,st);
			//right(fn,name,28);

			//strcat(fn,st);
			//const char* cn=(const char *)malloc(100*sizeof(char));
			//cn=fn;
			//打开JSON数据文件
			//char fn[] = "/data/raw/2021-01-20_7.json";
		        //printf("%d\n",strlen(fn));
			//printf("%d\n",fn[26]);
			//printf("%d\n",strlen(name));
			//printf("%d\n",name[26]);
			name[27]='\0';
			FILE* fd=fopen(name,"r");
        		if(fd==NULL)
        		{
                		printf("error\n");
                		printf("%s\n",name);
                		return -1;
        		}
        		char outname[100]="/home/yyh/workspace/res";
        		strcat(outname,name);
        		//printf("%s\n",outname);
        		FILE* ft = fopen(outname,"w");

			//printf("%s\n",name);

			exejson(fd,ft);
			
		}
			printf("%d\n",c++);
			
			
	}
	//name="/data/raw/2021-01-20_7.json";
	//exejson(name);
	fclose(tp);

	
}
