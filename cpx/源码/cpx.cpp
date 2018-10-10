#include "lex"
#include <sstream>
#include <map>
int labels_cnt=0,top=0;
std::string hwnd(){
	labels_cnt++;
	std::stringstream sst;
	sst.clear();
	sst<<labels_cnt;
	return sst.str();
}
std::map<std::string,std::string>deflab;
int main(int argc,char**argv){
	if(argc!=3){
		fprintf(stderr,"请正确键入源文件名。\n");
		return 0;
	}
	freopen(argv[1],"r",stdin);
	freopen(argv[2],"w",stdout);
	lex();
	listype x;
	x.type=TYPE_EOF;
	type_stack.push_back(x);
	cal_stack.resize(type_stack.size());
	int n=type_stack.size();
	for(int i=0;i<n;cal_stack[top++]=type_stack[i++]){
		bool did=1;
		listype nex=type_stack[i];
		while(did){
			did=0;
			if(!did&&top>6){
				listype&a=cal_stack[top-7],&b=cal_stack[top-6],&c=cal_stack[top-5];
				listype&d=cal_stack[top-4],&e=cal_stack[top-3],&f=cal_stack[top-2];
				listype&g=cal_stack[top-1];
				if(a.type==TYPE_FOR&&b.ans=="("&&c.type==TYPE_EXP&&d.type==TYPE_EXP
					&&e.type==TYPE_EXP&&f.ans==")"&&g.type==TYPE_COM){
					top-=6;
					c.ans+="\npop";
					e.ans+="\npop";
					a.type=TYPE_COM;
					std::string l1=hwnd();
					std::string l2=hwnd();
					std::string l3=hwnd();
					a.ans="{\n"+c.ans+"\nlabel "+l1+"\n"+d.ans+
					"\nifgoto "+l2+"\ngoto "+l3+"\nlabel "+l2+"\n"+
					g.ans+"\n"+e.ans+"\ngoto "+l1+"\nlabel "+l3+"\n}";
					did=1;
				}
			}
			if(!did&&top>5){
				listype&a=cal_stack[top-6],&b=cal_stack[top-5],&c=cal_stack[top-4];
				listype&d=cal_stack[top-3],&e=cal_stack[top-2],&f=cal_stack[top-1];
				if(a.ans=="("&&b.type==TYPE_INT&&c.ans==")"
				&&d.ans=="("&&e.type==TYPE_EXP&&f.ans==")"){
					top-=5;
					a.type=TYPE_EXP;
					a.ans=e.ans+"\nto_int";
					did=1;
				}else if(a.ans=="("&&b.type==TYPE_DOUBLE&&c.ans==")"
				&&d.ans=="("&&e.type==TYPE_EXP&&f.ans==")"){
					top-=5;
					a.type=TYPE_EXP;
					a.ans=e.ans+"\nto_double";
					did=1;
				}else if(a.ans=="("&&b.type==TYPE_STRING&&c.ans==")"
				&&d.ans=="("&&e.type==TYPE_EXP&&f.ans==")"){
					top-=5;
					a.type=TYPE_EXP;
					a.ans=e.ans+"\nto_string";
					did=1;
				}else if(a.ans=="("&&b.type==TYPE_BOOL&&c.ans==")"
				&&d.ans=="("&&e.type==TYPE_EXP&&f.ans==")"){
					top-=5;
					a.type=TYPE_EXP;
					a.ans=e.ans+"\nto_bool";
					did=1;
				}
			}
			if(!did&&top>4){
				listype&a=cal_stack[top-5],&b=cal_stack[top-4],
				&c=cal_stack[top-3],&d=cal_stack[top-2],&e=cal_stack[top-1];
				if(a.type==TYPE_IF&&b.type==TYPE_EXP&&c.type==TYPE_COM
				&&d.type==TYPE_ELSE&&e.type==TYPE_COM){
					top-=4;
					a.type=TYPE_COM;
					std::string l1=hwnd();
					std::string l2=hwnd();
					a.ans="{\n"+b.ans+"\nifgoto "+l1+"\n"+e.ans+"\ngoto "
						+l2+"\nlabel "+l1+"\n"+c.ans+"\nlabel "+l2+"\n}";
					did=1;
				}else if(a.type==TYPE_FOR&&b.type==TYPE_EXP&&c.type==TYPE_EXP&&
					d.type==TYPE_EXP&&e.type==TYPE_COM){
					top-=4;
					b.ans+="\npop";
					d.ans+="\npop";
					a.type=TYPE_COM;
					std::string l1=hwnd();
					std::string l2=hwnd();
					std::string l3=hwnd();
					a.ans="{\n"+b.ans+"\nlabel "+l1+"\n"+c.ans+
					"\nifgoto "+l2+"\ngoto "+l3+"\nlabel "+l2+"\n"+
					e.ans+"\n"+d.ans+"\ngoto "+l1+"\nlabel "+l3+"\n}";
					did=1;
				}else if(a.type==TYPE_DEF&&b.type==TYPE_NAME
				&&c.ans=="("&&d.ans==")"&&e.type==TYPE_COM){
					top-=4;
					a.type=TYPE_COM;
					std::string l1=hwnd();
					std::string l2=hwnd();
					deflab[b.ans]=l2;
					a.ans="goto "+l1+"\nlabel "+l2+"\n"
					+e.ans+"\npush null\nreturn\nlabel "+l1;
					did=1;
				}
			}
			if(!did&&top>3){
				listype&a=cal_stack[top-4],&b=cal_stack[top-3],
				&c=cal_stack[top-2],&d=cal_stack[top-1];
				if(a.type==TYPE_ARRS&&b.ans=="["&&c.type==TYPE_EXP
				&&d.ans=="]"&&nex.ans!="="){
					top-=3;
					a.type=TYPE_ARRS;
					a.ans=c.ans+"\n"+a.ans+"\n+\n[]";
					did=1;	
				}else if(a.type==TYPE_NAME&&b.ans=="["&&c.type==TYPE_EXP
				&&d.ans=="]"&&nex.ans!="="){
					top-=3;
					a.type=TYPE_ARRS;
					a.ans=c.ans+"\npush var "+a.ans+"\n+\n[]";
					did=1;	
				}else if(a.type==TYPE_ARRS&&b.ans=="["&&c.type==TYPE_EXP
				&&d.ans=="]"&&nex.ans=="="){
					top-=3;
					a.type=TYPE_ARRP;
					a.ans=c.ans+"\n"+a.ans+"\n+";
					did=1;	
				}else if(a.type==TYPE_NAME&&b.ans=="["&&c.type==TYPE_EXP
				&&d.ans=="]"&&nex.ans=="="){
					top-=3;
					a.type=TYPE_ARRP;
					a.ans=c.ans+"\npush var "+a.ans+"\n+";
					did=1;	
				}else if(a.type==TYPE_DEF&&b.type==TYPE_NAME&&c.ans=="("
				&&d.type==TYPE_NAME){
					top-=3;
					std::string l1=hwnd();
					deflab[b.ans]=l1;
					a.type=TYPE_DEF_HEAD;
					a.ans="label "+l1+"\ntop "+d.ans+"\npop";
					did=1;
				}
			}
			if(!did&&top>2){
				listype&a=cal_stack[top-3],&b=cal_stack[top-2],&c=cal_stack[top-1];
				if(a.type==TYPE_IF&&b.type==TYPE_EXP&&c.type==TYPE_COM&&nex.type!=TYPE_ELSE){
					top-=2;
					a.type=TYPE_COM;
					std::string l1=hwnd();
					std::string l2=hwnd();
					a.ans="{\n"+b.ans+"\nifgoto "+l1+"\ngoto "+l2+"\nlabel "
						+l1+"\n"+c.ans+"\nlabel "+l2+"\n}";
					did=1;
				}else if((b.ans=="=="||b.ans=="!="||b.ans=="<"||b.ans==">"||b.ans=="<="
				||b.ans==">=")&&nex.ans!="+"&&nex.ans!="-"&&nex.ans!="*"&&nex.ans!="/"
				&&nex.ans!="%"&&nex.ans!="["&&a.type==TYPE_EXP&&c.type==TYPE_EXP){
					top-=2;
					a.type=TYPE_EXP;
					a.ans=a.ans+"\n"+c.ans+"\n"+b.ans;
					did=1;
				}
				if(b.ans=="||"&&nex.ans!="+"&&nex.ans!="-"&&nex.ans!="*"&&nex.ans!="/"
				&&nex.ans!="%"&&nex.ans!="["&&a.type==TYPE_EXP&&c.type==TYPE_EXP
				&&nex.ans!="&&"&&nex.ans!="="&&nex.ans!="=="&&nex.ans!="!="&&nex.ans!="<"
				&&nex.ans!=">"&&nex.ans!="<="&&nex.ans!=">="){
					top-=2;
					a.type=TYPE_EXP;
					a.ans=a.ans+"\n"+c.ans+"\n||";
					did=1;
				}else if(b.ans=="&&"&&nex.ans!="+"&&nex.ans!="-"&&nex.ans!="*"&&nex.ans!="/"
				&&nex.ans!="%"&&nex.ans!="["&&a.type==TYPE_EXP&&c.type==TYPE_EXP
				&&nex.ans!="="&&nex.ans!="=="&&nex.ans!="!="&&nex.ans!="<"
				&&nex.ans!=">"&&nex.ans!="<="&&nex.ans!=">="){
					top-=2;
					a.type=TYPE_EXP;
					a.ans=a.ans+"\n"+c.ans+"\n&&";
					did=1;
				}else if(b.ans=="*"&&nex.ans!="["&&a.type==TYPE_EXP&&c.type==TYPE_EXP){
					top-=2;
					a.type=TYPE_EXP;
					a.ans=a.ans+"\n"+c.ans+"\n*";
					did=1;
				}else if(b.ans=="%"&&nex.ans!="["&&a.type==TYPE_EXP&&c.type==TYPE_EXP){
					top-=2;
					a.type=TYPE_EXP;
					a.ans=a.ans+"\n"+c.ans+"\n%";
					did=1;
				}else if(b.ans=="/"&&nex.ans!="["&&a.type==TYPE_EXP&&c.type==TYPE_EXP){
					top-=2;
					a.type=TYPE_EXP;
					a.ans=a.ans+"\n"+c.ans+"\n/";
					did=1;
				}else if(b.ans=="+"&&nex.ans!="*"&&nex.ans!="/"&&nex.ans!="%"
					&&nex.ans!="["&&a.type==TYPE_EXP&&c.type==TYPE_EXP){
					top-=2;
					a.type=TYPE_EXP;
					a.ans=a.ans+"\n"+c.ans+"\n+";
					did=1;
				}else if(b.ans=="-"&&nex.ans!="*"&&nex.ans!="/"&&nex.ans!="%"
					&&nex.ans!="["&&a.type==TYPE_EXP&&c.type==TYPE_EXP){
					top-=2;
					a.type=TYPE_EXP;
					a.ans=a.ans+"\n"+c.ans+"\n-";
					did=1;
				}else if(a.ans=="("&&c.ans==")"&&b.type==TYPE_EXP){
					top-=2;
					a=b;
					did=1;
				}else if(a.type==TYPE_NAME&&b.ans=="="&&(c.type==TYPE_EXP||c.type==TYPE_SETMEM)
					&&nex.ans!="="&&nex.ans!="+"&&nex.ans!="-"&&nex.ans!="*"&&nex.ans!="/"
					&&nex.ans!="%"&&nex.ans!="["){
					top-=2;
					a.type=TYPE_SETMEM;
					a.ans=c.ans+"\ntop "+a.ans;
					did=1;
				}else if(a.type==TYPE_ARRP&&b.ans=="="&&(c.type==TYPE_EXP||c.type==TYPE_SETMEM)
					&&nex.ans!="="&&nex.ans!="+"&&nex.ans!="-"&&nex.ans!="*"&&nex.ans!="/"
					&&nex.ans!="%"&&nex.ans!="["){
					top-=2;
					a.type=TYPE_SETMEM;
					a.ans=c.ans+"\n"+a.ans+"\ntop_ptr";
					did=1;
				}else if(a.ans=="{"&&c.ans=="}"&&(b.type==TYPE_COM||b.type==TYPE_COMS)){
					top-=2;
					a.type=TYPE_COM;
					a.ans="{\n"+b.ans+"\n}";
					did=1;
				}else if(a.type==TYPE_WHILE&&b.type==TYPE_EXP&&c.type==TYPE_COM){
					top-=2;
					a.type=TYPE_COM;
					std::string l1=hwnd();
					std::string l2=hwnd();
					std::string l3=hwnd();
					a.ans="{\nlabel "+l1+"\n"+b.ans+"\nifgoto "+l2+"\ngoto "+
					l3+"\nlabel "+l2+"\n"+c.ans+"\ngoto "+l1+"\nlabel "+l3+"\n}";
					did=1;
				}else if(a.type==TYPE_DEF_HEAD&&b.ans==","&&c.type==TYPE_NAME){
					top-=2;
					a.ans+="\ntop "+c.ans+"\npop";
					did=1;
				}else if(a.type==TYPE_DEF_HEAD&&b.ans==")"&&c.type==TYPE_COM){
					top-=2;
					a.type=TYPE_COM;
					std::string l1=hwnd();
					a.ans="goto "+l1+"\n"+a.ans+"\n"
					+c.ans+"\npush null\nreturn\nlabel "+l1;
					did=1;
				}else if(a.type==TYPE_NAME&&b.ans=="("
				&&c.type==TYPE_EXP&&(nex.ans==","||nex.ans==")")){
					top-=2;
					a.type=TYPE_CALL_HEAD;
					std::string l1=hwnd();
					a.ans=c.ans+"\ncall "+l1+" "+deflab[a.ans]+"\nlabel "+l1;
					did=1;
				}else if(a.type==TYPE_RETURN&&b.type==TYPE_EXP&&c.ans==";"){
					top-=2;
					a.type=TYPE_COM;
					a.ans=b.ans+"\nreturn";
					did=1;
				}else if(a.type==TYPE_CALL_HEAD&&b.ans==","
				&&c.type==TYPE_EXP&&(nex.ans==","||nex.ans==")")){
					top-=2;
					a.ans=c.ans+"\n"+a.ans;
					did=1;
				}else if((top==3||cal_stack[top-4].type!=TYPE_DEF)&&a.type==TYPE_NAME
				&&b.ans=="("&&c.ans==")"){
					top-=2;
					a.type=TYPE_EXP;
					std::string l1=hwnd();
					a.ans="\ncall "+l1+" "+deflab[a.ans]+"\nlabel "+l1;
					did=1;
				}
			}
			if(!did&&top>1){
				listype&a=cal_stack[top-2],&b=cal_stack[top-1];
				if(a.ans=="!"&&b.type==TYPE_BOOL_VAL&&(nex.ans!="="&&nex.ans!="=="
					&&nex.ans!="<"&&nex.ans!=">"&&nex.ans!="<="&&nex.ans!=">="&&
					nex.ans!="!="&&nex.ans!="+"&&nex.ans!="-"&&nex.ans!="*"&&nex.ans!="/"
					&&nex.ans!="%"&&nex.ans!="!="&&nex.ans!="[")){
					top--;
					a.type=TYPE_BOOL_VAL;
					a.ans=b.ans+"\n!";
					did=1;
				}else if((a.type==TYPE_COM||a.type==TYPE_COMS)&&b.type==TYPE_COM){
					top--;
					a.type=TYPE_COMS;
					a.ans+="\n"+b.ans;
					did=1;
				}else if(a.type==TYPE_SETMEM&&b.ans==";"){
					top--;
					a.type=TYPE_COM;
					a.ans+="\npop";
					did=1;
				}else if(a.type==TYPE_LABEL&&a.ans=="+"&&nex.ans!="*"&&nex.ans!="/"&&nex.ans!="%"
					&&nex.ans!="["&&b.type==TYPE_EXP){
					top--;
					a=b;
					did=1;
				}else if(a.type==TYPE_LABEL&&a.ans=="-"&&nex.ans!="*"&&nex.ans!="/"&&nex.ans!="%"
					&&nex.ans!="["&&b.type==TYPE_EXP){
					top--;
					a=b;
					a.ans="push int_val 0\n"+a.ans+"\n-";
					did=1;
				}else if(a.ans=="."&&b.type==TYPE_EXP&&nex.ans!="["&&nex.ans!="("){
					top--;
					a=b;
					a.ans+="\nprint";
					did=1;
				}else if(a.type==TYPE_ARRAY&&b.type==TYPE_EXP){
					top--;
					a.type=TYPE_EXP;
					a.ans=b.ans+"\narray";
					did=1;
				}else if(a.type==TYPE_CALL_HEAD&&b.ans==")"){
					top--;
					a.type=TYPE_EXP;
					did=1;
				}else if(a.type==TYPE_LENGTHOF&&b.type==TYPE_EXP&&nex.ans!="["){
					top--;
					a.type=TYPE_EXP;
					a.ans=b.ans+"\nlengthOf";
					did=1;
				}
			}
			if(!did&&top>0){
				listype&a=cal_stack[top-1];
				if(a.type==TYPE_TRUE){
					a.type=TYPE_BOOL_VAL;
					a.ans="push bool_val 1";
					did=1;
				}else if(a.type==TYPE_FALSE){
					a.type=TYPE_BOOL_VAL;
					a.ans="push bool_val 0";
					did=1;
				}else if(a.type==TYPE_NAME&&nex.ans!="="&&nex.ans!="["&&nex.ans!="("){
					a.type=TYPE_EXP;
					a.ans="push var "+a.ans;
					did=1;
				}else if(a.type==TYPE_ARRS&&nex.ans!="="&&nex.ans!="["){
					a.type=TYPE_EXP;
					did=1;
				}else if(a.ans==";"){
					a.type=TYPE_COM;
					a.ans="";
					did=1;
				}
			}
		}
	}
	puts(cal_stack[0].ans.data());
	//for(int i=1;i<top;i++)printf("errcnt %d:%d\n%s\n\n",i
	//,cal_stack[i].type,cal_stack[i].ans.data());
	return 0;
}
