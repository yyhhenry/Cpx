#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <cstdlib>
using namespace std;
typedef long long LL;
bool texit=0;
template <typename T>
std::string toString(T x){
	std::stringstream sst;
	sst.clear();
	sst<<x;
	return sst.str();
}
class val;
typedef LL vptr;
std::map<LL,LL>lab;
std::vector<val>res;
LL top;
std::vector<std::map<std::string,LL> >mem;
std::vector<LL>plc;
std::vector<LL>dcal;
std::vector<val>space;
LL dep;
std::string pro;
std::vector<LL>sys_sta;
int pptr;
class val{
private:
	int cnt;
	int t;
	LL _0;
	bool _1;
	double _2;
	std::string _3;
	vptr _4;
	void lto_int(){
		if(t==1)_0=_1;
		else if(t==2)_0=_2;
		else if(t==3){
			std::stringstream sst;
			sst.clear();
			sst.str(_3);
			sst>>_0;
		}
		t=0;
	}
	void lto_bool(){
		if(t==0)_1=_0;
		else if(t==2)_1=_2;
		else if(t==3){
			if(_3=="true")_1=1;
			else if(_3=="false")_1=0;
			else _1=to_int()._0;
		}
		t=1;
	}
	void lto_double(){
		if(t==1)_2=_1;
		else if(t==0)_2=_0;
		else if(t==3){
			std::stringstream sst;
			sst.clear();
			sst.str(_3);
			sst>>_2;
		}
		t=2;
	}
	void lto_string(){
		if(t==0)_3=toString(_0);
		else if(t==1)_3=toString(_1);
		else if(t==2)_3=toString(_2);
		t=3;
	}
public:
	LL len(){
		return to_string()._3.length();
	}
	vptr gvptr(){
		return _4;
	}
	LL gint(){
		return _0;
	}
	val(){
		t=0;
		_0=0;
		cnt=0;
	}
	val to_int(){
		val ans=*this;
		ans.lto_int();
		return ans;
	}
	val to_bool(){
		val ans=*this;
		ans.lto_bool();
		return ans;
	}
	val to_double(){
		val ans=*this;
		ans.lto_double();
		return ans;
	}
	val to_string(){
		val ans=*this;
		ans.lto_string();
		return ans;
	}
	bool boolval(){
		return to_bool()._1;
	}
	void print(){
		if(t==0)printf("%lld",_0);
		else if(t==1)printf("%d",_1);
		else if(t==2)printf("%lf",_2);
		else if(t==3)printf("%s",_3.data());
	}
	void putint(LL x){
		t=0;
		_0=x;
	}
	void putbool(bool x){
		t=1;
		_1=x;
	}
	void putdouble(double x){
		t=2;
		_2=x;
	}
	void putstring(std::string x){
		t=3;
		_3=x;
	}
	void putvptr(vptr x){
		t=4;
		_4=x;
	}
	val operator+(val b){
		val ans;
		if(t==3&&b.t==3){
			ans.t=3;
			ans._3=_3+b._3;
		}else if(t==3){
			ans.t=3;
			ans._3=_3;
			if(b.t==0)ans._3+=toString(b._0);
			else if(b.t==1)ans._3+=toString(b._1);
			else if(b.t==2)ans._3+=toString(b._2);
		}else if(b.t==3){
			ans.t=3;
			ans._3=b._3[to_int()._0];
		}else if(b.t==4){
			ans.putvptr(b._4+to_int()._0);
		}else if(t==4){
			ans.putvptr(_4+b.to_int()._0);
		}else if(t==2||b.t==2){
			ans.t=2;
			ans._2=0;
			if(t==0)ans._2+=_0;
			else if(t==1)ans._2+=_1;
			else if(t==2)ans._2+=_2;
			if(b.t==0)ans._2+=b._0;
			else if(b.t==1)ans._2+=b._1;
			else if(b.t==2)ans._2+=b._2;
		}else{
			ans.t=0;
			ans._0=0;
			if(t==0)ans._0+=_0;
			else if(t==1)ans._0+=_1;
			if(b.t==0)ans._0+=b._0;
			else if(b.t==1)ans._0+=b._1;
		}
		return ans;
	}
	val operator-(val b){
		val ans;
		if(t==3){
			ans.t=3;
			ans._3="";
			if(b.t==0)ans._3.push_back(_3[b._0]);
			else if(b.t==1)ans._3.push_back(_3[b._1]);
			else if(b.t==2)ans._3.push_back(_3[(LL)(b._2)]);
		}else if(t==2||b.t==2){
			ans.t=2;
			ans._2=0;
			if(t==0)ans._2+=_0;
			else if(t==1)ans._2+=_1;
			else if(t==2)ans._2+=_2;
			if(b.t==0)ans._2-=b._0;
			else if(b.t==1)ans._2-=b._1;
			else if(b.t==2)ans._2-=b._2;
		}else{
			ans.t=0;
			ans._0=0;
			if(t==0)ans._0+=_0;
			else if(t==1)ans._0+=_1;
			if(b.t==0)ans._0-=b._0;
			else if(b.t==1)ans._0-=b._1;
		}
		return ans;
	}
	val operator*(val b){
		val ans;
		if(t==2||b.t==2){
			ans.t=2;
			ans._2=(to_double()._2)*(b.to_double()._2);
		}else{
			ans.t=0;
			ans._0=(to_int()._0)*(b.to_int()._0);
		}
		return ans;
	}
	val operator/(val b){
		val ans;
		if(t==2||b.t==2){
			ans.t=2;
			ans._2=(to_double()._2)/(b.to_double()._2);
		}else{
			ans.t=0;
			ans._0=(to_int()._0)/(b.to_int()._0);
		}
		return ans;
	}
	val operator%(val b){
		val ans;
		ans.t=0;
		ans._0=(to_int()._0)%(b.to_int()._0);
		return ans;
	}
	val operator&&(val b){
		val ans;
		ans.t=1;
		ans._1=(to_bool()._1)&&(b.to_bool()._1);
		return ans;
	}
	val operator||(val b){
		val ans;
		ans.t=1;
		ans._1=(to_bool()._1)||(b.to_bool()._1);
		return ans;
	}
	val operator!(){
		val ans;
		ans.putbool(!(to_bool()._1));
		return ans;
	}
	friend class val_ptr;
	val operator<(val b){
		val ans;
		if(t==3&&b.t==3){
			ans.putbool(_3<b._3);
		}else if(t==2||b.t==2){
			ans.putbool(to_double()._2<b.to_double()._2);
		}else{
			ans.putbool(to_int()._0<b.to_int()._0);
		}
		return ans;
	}
	val operator<=(val b){
		val ans;
		if(t==3&&b.t==3){
			ans.putbool(_3<=b._3);
		}else if(t==2||b.t==2){
			ans.putbool(to_double()._2<=b.to_double()._2);
		}else{
			ans.putbool(to_int()._0<=b.to_int()._0);
		}
		return ans;
	}
	val operator>(val b){
		val ans;
		if(t==3&&b.t==3){
			ans.putbool(_3>b._3);
		}else if(t==2||b.t==2){
			ans.putbool(to_double()._2>b.to_double()._2);
		}else{
			ans.putbool(to_int()._0>b.to_int()._0);
		}
		return ans;
	}
	val operator>=(val b){
		val ans;
		if(t==3&&b.t==3){
			ans.putbool(_3>=b._3);
		}else if(t==2||b.t==2){
			ans.putbool(to_double()._2>=b.to_double()._2);
		}else{
			ans.putbool(to_int()._0>=b.to_int()._0);
		}
		return ans;
	}
	val operator==(val b){
		val ans;
		if(t==3&&b.t==3){
			ans.putbool(_3==b._3);
		}else if(t==2||b.t==2){
			ans.putbool(to_double()._2==b.to_double()._2);
		}else{
			ans.putbool(to_int()._0==b.to_int()._0);
		}
		return ans;
	}
	val operator!=(val b){
		val ans;
		if(t==3&&b.t==3){
			ans.putbool(_3!=b._3);
		}else if(t==2||b.t==2){
			ans.putbool(to_double()._2!=b.to_double()._2);
		}else{
			ans.putbool(to_int()._0!=b.to_int()._0);
		}
		return ans;
	}
	friend LL gint();
	friend double gdouble();
	friend bool gbool();
};
void init(){
	top=0;
	dep=1;
	mem.resize(dep);
	mem[0].clear();
	dcal.push_back(dep);
	plc.clear();
	space.clear();
}
void lbrc(){
	mem.push_back(std::map<std::string,LL>());
	dep++;
	mem[dep-1]=mem[dep-2];
	plc.push_back(space.size());
}
void lcal(){
	mem.push_back(std::map<std::string,LL>());
	dep++;
	dcal.push_back(dep);
	plc.push_back(space.size());
}
void rcal(){
	if(dep==1||dcal.size()==0){
		texit=1;
		return;
	}
	LL trdep=dcal[dcal.size()-1];
	while(dep>=trdep){
		mem[dep-1].clear();
		mem.pop_back();
		dep--;
		space.resize(plc[plc.size()-1]);
		plc.pop_back();
	}
	dcal.pop_back();
}
void rbrc(){
	mem[dep-1].clear();
	mem.pop_back();
	dep--;
	space.resize(plc[plc.size()-1]);
	plc.pop_back();
}
void pop_to(std::string ss){
	if(mem[dep-1].count(ss)){
		space[mem[dep-1][ss]]=res[top-1];
	}else{
		mem[dep-1][ss]=space.size();
		space.push_back(res[top-1]);
	}
}
int gtc(){
	if(pptr<pro.length())return pro[pptr++];
	else return EOF;
}
int gnc(){
	if(pptr<pro.length())return pro[pptr];
	else return EOF;
}
std::string gts(){
	std::string ans="";
	while(!isgraph(pro[pptr])&&pptr<pro.length())pptr++;
	while(isgraph(pro[pptr])&&pptr<pro.length())ans+=pro[pptr++];
	return ans;
}
LL gint(){
	val x;
	x.putstring(gts());
	return x.to_int()._0;
}
double gdouble(){
	val x;
	x.putstring(gts());
	return x.to_double()._2;
}
bool gbool(){
	val x;
	x.putstring(gts());
	return x.to_bool()._1;
}
std::string gstring(){
	while(gtc()!='\"');
	std::string ans="";
	while(1){
		char c=gtc();
		if(c=='\\'){
			char d=gtc();
			if(d=='\\'){
				ans+='\\';
			}else if(d=='n'){
				ans+='\n';
			}else if(d=='t'){
				ans+='\t';
			}else if(d=='\"'){
				ans+='\"';
			}
		}else if(c=='\"'){
			break;
		}else{
			ans+=c;
		}
	}
	return ans;
}
void pushval(){
	res.push_back(val());
	top++;
	std::string ss=gts();
	if(ss=="int_val"){
		res[top-1].putint(gint());
	}else if(ss=="double_val"){
		res[top-1].putdouble(gdouble());
	}else if(ss=="bool_val"){
		res[top-1].putbool(gbool());
	}else if(ss=="string_val"){
		res[top-1].putstring(gstring());
	}else if(ss=="var"){
		res[top-1]=space[mem[dep-1][gts()]];
	}else if(ss=="null"){
		
	}
}
int main(int argc,char**argv){
	init();
	if(argc!=2){
		fprintf(stderr,"请正确键入运行文件名。\n");
		return 0; 
	}
	FILE*fin=fopen(argv[1],"r");
	while(1){
		char c=fgetc(fin);
		if(c==EOF)break;
		pro+=c;
	}
	pptr=0;
	while(gnc()!=EOF){
		LL v=pptr;
		std::string ss=gts();
		if(ss=="label"){
			lab[gint()]=v;
		}
		while(1){
			char c=gtc();
			if(c==EOF||c=='\n')break;
		}
	}
	pptr=0;
	lab[0]=pro.length();
	sys_sta.push_back(0);
	while(gnc()!=EOF&&!texit){
		std::string ss=gts();
		if(ss=="label"){
			gint();
		}else if(ss=="goto"){
			pptr=lab[gint()];
		}else if(ss=="push"){
			pushval();
		}else if(ss=="pop"){
			res.pop_back();
			top--;
		}else if(ss=="top"){
			pop_to(gts());
		}else if(ss=="print"){
			res[top-1].print();
		}else if(ss=="{"){
			lbrc();
		}else if(ss=="}"){
			rbrc();
		}else if(ss=="+"){
			res[top-2]=res[top-2]+res[top-1];
			top--;
			res.pop_back();
		}else if(ss=="-"){
			res[top-2]=res[top-2]-res[top-1];
			top--;
			res.pop_back();
		}else if(ss=="*"){
			res[top-2]=res[top-2]*res[top-1];
			top--;
			res.pop_back();
		}else if(ss=="/"){
			res[top-2]=res[top-2]/res[top-1];
			top--;
			res.pop_back();
		}else if(ss=="%"){
			res[top-2]=res[top-2]%res[top-1];
			top--;
			res.pop_back();
		}else if(ss=="<"){
			res[top-2]=res[top-2]<res[top-1];
			top--;
			res.pop_back();
		}else if(ss=="<="){
			res[top-2]=res[top-2]<=res[top-1];
			top--;
			res.pop_back();
		}else if(ss==">"){
			res[top-2]=res[top-2]>res[top-1];
			top--;
			res.pop_back();
		}else if(ss==">="){
			res[top-2]=res[top-2]>=res[top-1];
			top--;
			res.pop_back();
		}else if(ss=="=="){
			res[top-2]=res[top-2]==res[top-1];
			top--;
			res.pop_back();
		}else if(ss=="!="){
			res[top-2]=res[top-2]==res[top-1];
			top--;
			res.pop_back();
		}else if(ss=="ifgoto"){
			res[top-1]=res[top-1].to_bool();
			LL vvx=lab[gint()];
			if(res[top-1].boolval()){
				pptr=vvx;
			}
			top--;
			res.pop_back();
		}else if(ss=="array"){
			LL xxc=space.size();
			space.resize(xxc+res[top-1].to_int().gint());
			res[top-1].putvptr(xxc);
		}else if(ss=="[]"){
			res[top-1]=space[res[top-1].gvptr()];
		}else if(ss=="to_int"){
			res[top-1]=res[top-1].to_int();
		}else if(ss=="to_double"){
			res[top-1]=res[top-1].to_double();
		}else if(ss=="to_bool"){
			res[top-1]=res[top-1].to_bool();
		}else if(ss=="to_string"){
			res[top-1]=res[top-1].to_string();
		}else if(ss=="top_ptr"){
			space[res[top-1].gvptr()]=res[top-2];
			res.pop_back();
			top--;
		}else if(ss=="nextInt"){
			LL xxs;
			scanf("%lld",&xxs);
			res.push_back(val());
			res[top].putint(xxs);
			top++;
		}else if(ss=="nextDouble"){
			double xxs;
			scanf("%lf",&xxs);
			res.push_back(val());
			res[top].putdouble(xxs);
			top++;
		}else if(ss=="next"){
			std::string xxs;
			std::cin>>xxs;
			res.push_back(val());
			res[top].putstring(xxs);
			top++;
		}else if(ss=="nextLine"){
			std::string xxs;
			getline(cin,xxs);
			res.push_back(val());
			res[top].putstring(xxs);
			top++;
		}else if(ss=="nextChar"){
			std::string xxs=" ";
			xxs[0]=getchar();
			res.push_back(val());
			res[top].putstring(xxs);
			top++;
		}else if(ss=="lengthOf"){
			res[top-1].putint(res[top-1].len());
		}else if(ss=="call"){
			sys_sta.push_back(gint());
			pptr=lab[gint()];
			lcal();
		}else if(ss=="return"){
			pptr=lab[sys_sta[sys_sta.size()-1]];
			sys_sta.pop_back();
			rcal();
		}
	}
	return 0;
}
