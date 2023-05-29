#include<iostream>
#include<iomanip>				//thu vien de co the in ra tien trieu
#include<string>				//thu vien de so sanh hai chuoi
#include<windows.h>				//thu vien de tao am thanh
#include<unistd.h>				// chay sleep
#include <stdio.h>
using namespace std;

void menu1();
void menu2();
void menu3();
struct SList1;
struct SList2;
struct SList3;
struct Date {						//struct ngay thang nam
	int date, month, year;
};
bool KtraDate(int date,int month,int year){
    if (year<0 || month<=0 || month> 12 || date<=0 || date> 31) return false;
    if(month==1 || month ==3 || month == 5 || month ==7 || month ==8 || month ==10 || month==12){
        if(date <= 31) return true;
    }
    if(month==4 || month ==6 || month == 9 || month ==11){
        if(date <= 30) return true;
    }  
    if(month==2){
		if(year %4 ==0 && year !=0){
        	if(date <= 29) return true;
    	}  
    	else{
        	if(date <= 28) return true;
    	}
	}
}
void ktraSoLuong(int &k){
	while(k<=0){
		cout<<setw(136)<<"So luong ban nhap khong hop le! Vui long nhap lai:"<<endl;
		cout << setw(92)<<"Nhap so luong: " ;
		cin>>k;
	}
	
}
void NhapDate(Date &d) {			//ham nhap ngay
		cout<<endl;
		cout <<setw(83)<< "-Ngay:";
		cin >> d.date;
		cout<<endl;
		cout <<setw(84)<<"-Thang:";
		cin >> d.month;
		cout<<endl;
		cout <<setw(82)<<"-Nam:";
		cin >> d.year;
		if(KtraDate(d.date,d.month,d.year)==false){
			cout<<setw(114)<<"Date khong hop le! Moi ban nhap lai: ";
			NhapDate(d);
		}
}
void XuatDate(Date d) {
	cout << d.date << "/" << d.month << "/" << d.year <<endl;
}
bool DKSDT(string a){
    int s=0;
    char c[10];
    for(int i=0;i<10;i++){
        c[i]=a[i];
    }
    for(int i=0;i<10;i++){
        if(int(c[i]<48) || int(c[i])>57){
            s=s+1;
        }
    }
    if(s==0){
        return true;
    }
    else return false;
    
}
void checkSDT(string &m){
	while(DKSDT(m)==false || m.length()!=10){
    	cout<<setw(113)<<"SDT khong hop le! Moi ban nhap lai!\n";
    	fflush(stdin);
	    cout<<setw(87)<<"Nhap SDT: ";
	    getline(cin,m);
	}
}
//TODO: CLASS NGUOI
class Nguoi {
	private:
		string SDT,Diachi;
		Date NgaySinh;
	public:										//them ham khoi tao
		Nguoi (){
			this->SDT=" ";
			this->Diachi=" ";
			this->NgaySinh.date=0;
			this->NgaySinh.month=0;
			this->NgaySinh.year=0;
		}
		~Nguoi(){}
		Date getns() {							//ham lay ngay sinh
			Date t;
			t.date=NgaySinh.date;
			t.month=NgaySinh.month;
			return t;
		}
		void Nhapthongtin() {					//ham nhap 1 nguoi
			cout<<endl;
			cout << setw(93)<<"Nhap ngay sinh: ";
			NhapDate(NgaySinh);
			fflush(stdin);
			cout <<setw(87)<<"Nhap SDT: " ;
			getline(cin,SDT);
			checkSDT(SDT);
			cout <<setw(91)<<"Nhap dia chi: ";
			getline(cin,Diachi);
		}
		void Xuatthongtin() {					//ham xuat 1 nguoi
			cout << "\n\t\t\t\t\t\t\t\t\t\tNgay Sinh: ";
			XuatDate(NgaySinh);
			cout << "\t\t\t\t\t\t\t\t\t\tSo dien thoai: " << SDT << endl ;
			cout << "\t\t\t\t\t\t\t\t\t\tDia chi: " << Diachi <<endl;
		}
		friend void GhiFileKhachHang(SList1 l);
		friend void GhiFileNhanVien(SList2 sl);
		friend void GhiFileNguyenLieu(SList3 l);
		virtual float GiaTien()=0;				//ham thuan ao tinh tien	//tinh truu tuong,dong goi
};

//TODO: CLASS KHACH HANG
class KhachHang: public Nguoi {//muc dich ke thua private
	private:
		int SoLuong;
		string MKH,*MatHang = new string[20];
		Date NgayMua;
	public:		//thieu ham tao va huy
		KhachHang(){
			this->SoLuong=0;
			this->MKH=" ";
			this->NgayMua.date=0;
			this->NgayMua.month=0;
			this->NgayMua.year=0;
		}
		~KhachHang(){}
		string getMKH();
		Date getnm();
		friend istream & operator >> (istream &is, KhachHang &k );
		friend ostream & operator << (ostream &os, KhachHang &k );
		friend void GhiFileKhachHang(SList1 l);
		float GiaTien();
};

string KhachHang::getMKH() {					//ham lay mkh
	return MKH;
}

Date KhachHang::getnm() {						//ham lay ngay mua
	Date t;
	t.date=NgayMua.date;
	t.month=NgayMua.month;
	return t;
}

istream & operator >> (istream &is, KhachHang &k ) {			//nhap 1 khach hang ghi vao file
	fflush(stdin);
	cout<<setw(97)<<"Nhap ma khach hang: ";
	getline(is,k.MKH);
	k.Nhapthongtin();
	cout << setw(92)<<"Nhap ngay mua: " ;
	NhapDate(k.NgayMua);
	fflush(stdin);
	cout << setw(92)<<"Nhap so luong: " ;
	is >> k.SoLuong ;
	ktraSoLuong(k.SoLuong);
	for (int i=0;i < k.SoLuong;i++) {				// mat hang la kieu mang do 1 nguoi co the mua nhieu mon
		fflush(stdin);
		cout << setw(91)<<"Nhap mat hang " << i+1 <<":";
		getline(is,k.MatHang[i]);
	}
	return is;
}

ostream & operator << (ostream &os, KhachHang &k ) {	//nap chong toan tu xuat 1 kh
	os<<"\n\t\t\t\t\t\t\t\t\t\tMa khach hang: "<<k.MKH;
	k.Xuatthongtin();
	os << "\t\t\t\t\t\t\t\t\t\tNgay mua: ";
	XuatDate(k.NgayMua);
	os << "\t\t\t\t\t\t\t\t\t\tSo luong: " << k.SoLuong << endl ;
	for (int i=0; i < k.SoLuong; i++) {
			os << "\t\t\t\t\t\t\t\t\t\tTen mon " << i+1 << ":" << k.MatHang[i] << endl;
	}
	return os;
}

int SoSanh(Date a,Date b) {							//so sanh ngay sinh va ngay mua
	if(a.date==b.date && a.month==b.month)
		return 1;
	return 0;
}

int SS(Date d1,Date d2){
	if(d1.date==d2.date && d1.month==d2.month && d1.year==d2.year){
		return 1;
	}
	else return 0;
}
string Uppercase(string a){
	for( int i=0;i<a.length();i++){
		if(a[i]>=97 && a[i]<=122){
			a[i]=a[i]-32;
		}
	}
	return a;	
}
bool checkstring(string a, string b){
	if(Uppercase(a) == Uppercase(b)){
		return true;
	}
	else
		return false;
}
float KhachHang::GiaTien() {						//ham tinh tien 1 kh
	string x1 = "CAFE DEN", x2 = "COLD BREW", x3 = "BAC SIU",x4 = "CAFE SUA", x5 = "CAPPUCCINO",x6 = "AMERICANO", x7 = "TRA MATCHA";
	string x8 = "TRA VAI", x9 = "TRA HAT SEN", x10 = "HONG TRA LATTE", x11 = "TRA DAO CAM SA", x12 = "TRA SUA MAC CA", x13 = "TRA VIET QUOC", x14 = "TRA SUA OOLONG";
	float *Gia = new float[SoLuong];				// cap phat bo nho dong cho mang gia
	float Tong = 0;
	for ( int i=0; i < SoLuong; i++) {
		if(checkstring(MatHang[i],x1) || checkstring(MatHang[i],x2)){
			Gia[i] = 35000;
		}
		else if(checkstring(MatHang[i],x3) || checkstring(MatHang[i],x4)){
					Gia[i] = 38000;
				}
		else if(checkstring(MatHang[i],x5) || checkstring(MatHang[i],x6)){
			Gia[i] = 40000;
		}
		else if(checkstring(MatHang[i],x7) || checkstring(MatHang[i],x8)){
			Gia[i] = 55000;
		}
		else if(checkstring(MatHang[i],x9) || checkstring(MatHang[i],x10)){
			Gia[i] = 50000;
		}	
		else if(checkstring(MatHang[i],x11) || checkstring(MatHang[i],x12)){
			Gia[i] = 59000;
		}			
		else if(checkstring(MatHang[i],x13) || checkstring(MatHang[i],x14)){
			Gia[i] = 60000;
		}	
		else 
			Gia[i]=0;	
	}
	for (int i=0; i < SoLuong; i++) {				//cau lenh tinh tong trong truong hop 1 nguoi mua 2 mat hang khac nhau
			Tong += Gia[i];	
	}
	if (SoSanh(getns(),getnm())) {
		cout << "\n\t\t\t\t\t\t\t\t\t\t(Uu dai 15% nhan dip sinh nhat):";
		return Tong-((Tong*15)/100);
	}
	else {
		return Tong;
	}
	delete [] Gia;
}

struct Node  {							//struct node khach hang
	KhachHang data;
	Node *next;
};

struct SList1 {							//struct danh sach khach hang
	Node *head;
	Node *tail;
	long size;
};

void SList1rong (SList1 &l)  {			//ham tao danh sach rong
	l.head = NULL;
	l.tail = NULL;
	l.size = 0;
}

Node* Taonode1() {						//ham tao mot node
	KhachHang v;
	Node* p = new Node;
	cin >> v;
	p->data = v ;	
	p->next = NULL;	
	return p;
}
bool SearchMKH(SList1 l,string m){
	Node *p=l.head;
	while(p!=NULL){
		if(p->data.getMKH()==m)
			return true;
		p=p->next;
	}
	return false;
}
void Themcuoi1 (SList1 &l, Node *p) {		//ham them mot node vao cuoi danh sach
		if (l.size == 0) {
			l.head = p;
			l.tail = p;
		}
		else {
			if(SearchMKH(l,p->data.getMKH())){
				cout<<"\n\t\t\t\t\t\t\t\t\t\tMA KHACH HANG BI TRUNG\n";
				cout<<"\n\t\t\t\t\t\t\t\t\t\tMoi nhap lai!\n";
				Node *q=Taonode1();
				Themcuoi1(l,q);
			}
			else{
				l.tail->next = p;
				l.tail = p;	  
			}		
		}
		l.size = l.size + 1;
}

void SuaDoi1(SList1 l)						//ham chinh sua 1 khach hang trong danh sach
{	
	Node *p=l.head;
	if(p == NULL)
	{
		cout << "\n\t\t\t\t\t\t\t\t\t\t\t\7Danh sach rong.";
		cout << "\n\t\t\t\t\t\t\t\t\t\tNHAN PHIM 1 DE NHAP DANH SACH.";
	}
	if(p != NULL)
	{
		string m;
		cout<<setw(99)<<"Nhap ma khach hang can sua doi: ";
		fflush(stdin);
		getline(cin,m);
		int dem = 0;
		while(p != NULL)
		{
			if(Uppercase(p->data.getMKH()) == Uppercase(m))
			{
				Beep(523,500); 			 //lenh tao am thanh
	    		cin.get(); 
				cin >> p->data;
				dem++;
			}
			p=p->next;
		}
		if(dem == 0)
		{
			cout << "\n\t\t\t\t\t\t\t\t\t\t\7Khong co khach hang trong danh sach";
			cout << "\n\t\t\t\t\t\t\t\t\t\tNHAN PHIM 2 DE TIM LAI.";
		}
	}
}

void XuatDSKH (SList1 l)  {				//ham xuat mot danh sach
	Node* p = l.head;
	if(p == NULL) {
		cout << "\n\t\t\t\t\t\t\t\t\t\t\t\7Danh sach rong.";
		cout << "\n\t\t\t\t\t\t\t\t\t\tNHAN PHIM 1 DE NHAP DANH SACH.";	
	}
	if(p != NULL) {
		int i=0;
		cout << endl << "\t\t\t\t\t\t\t\t\t\t\tDANH SACH KHACH HANG:";
		while (p != NULL) {
			cout << endl << "\t\t\t\t\t\t\t\t\t\t--------------------------------\n";
			cout << "\n\t\t\t\t\t\t\t\t\t\t\tKHACH HANG THU " << i+1 << endl;
			cout << (p->data);
			i++;
			p = p->next;
		}
		cout << endl;
		Beep(523,500);  
	    cin.get();
	} 
	delete p;
}

void Hoadon (SList1 &l) {				//ham in hoa don 1 kh dua vao tim kiem mkh
	string x;
	fflush(stdin);
	cout <<setw(99)<< "Ma khach hang can tim:";
	getline(cin,x);
	Node* p = l.head;
	if(p==NULL) {
		cout << "\n\t\t\t\t\t\t\t\t\t\t\t\7Danh sach dang trong.";
		cout << "\n\t\t\t\t\t\t\t\t\t\tNHAN PHIM 1 DE THEM DANH SACH.";
	}
	else {
		int dem=0;
		while (p != NULL) {	
			if(Uppercase(x)==Uppercase(p->data.getMKH())) {
				Beep(523,500);  
	    		cin.get(); 
				cout << p->data;
				cout << "\t\t\t\t\t\t\t\t\t\tGia Tien thanh toan: " << p->data.GiaTien() << "VND";
				dem++;
			}
			p = p->next;
		}
		if(dem==0) {
			cout << "\n\t\t\t\t\t\t\t\t\t\t\7Khong co khach hang trong danh sach";
			cout << "\n\t\t\t\t\t\t\t\t\t\tNHAN PHIM 3 DE TIM LAI.";
		}
	}
}

void GhiFileKhachHang(SList1 l) {					//ghi danh sach vao tep
	int i=1;
	FILE *file = fopen("KhachHang.txt","w");
	Node *p=l.head; 
	fprintf(file,"\t\t\t\t\t=====================================\n");
	fprintf(file,"\t\t\t\t\t=        DANH SACH KHACH HANG       =\n");
	fprintf(file,"\t\t\t\t\t=====================================\n\n\n");
	while(p != NULL) {
		fprintf(file,"\n\n");
		fprintf(file,"\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		fprintf(file,"\t\t\t\t~                 KHACH HANG THU: %2d                 ~\n",i);
		fprintf(file,"\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		fprintf(file,"\t\t\t\t             Ma khach hang: %s\n",p->data.MKH.c_str());
		fprintf(file,"\t\t\t\t             Ngay sinh: %2d/%2d/%4d\n",p->data.NgaySinh.date,p->data.NgaySinh.month,p->data.NgaySinh.year);
		fprintf(file,"\t\t\t\t             SDT: %s\n",p->data.SDT.c_str());
		fprintf(file,"\t\t\t\t             Ngay mua: %2d/%2d/%4d\n",p->data.NgayMua.date,p->data.NgayMua.month,p->data.NgayMua.year);
		fprintf(file,"\t\t\t\t             So luong: %d\n",p->data.SoLuong);
		for(int j=0;j<p->data.SoLuong;j++) {
			fprintf(file,"\t\t\t\t\t\t\t\t\t%1s\n",p->data.MatHang[j].c_str());
		}
		i++;
		p = p->next;
	}
	fclose(file);
	Beep(523,500);
	cin.get();
	cout << "\n\t\t\t\t\t\t\t\t\t\tGHI FILE KHACH HANG THANH CONG!!!";
	
}
//TODO: NHANVIEN //sap xep tang dan theo luong
class NhanVien:public Nguoi {
	private:
		string name,loainhanvien;
        int soluonggio;
    public:
		NhanVien(){
			this->name="";
			this->loainhanvien="";
			this->soluonggio=0;
		}
		~NhanVien(){
		}
     	friend istream & operator >> (istream &is, NhanVien & n);
		friend ostream & operator << (ostream &os, NhanVien & n);
		friend void GhiFileNhanVien(SList2 sl);
        float GiaTien();
        string getname();
};

string NhanVien::getname() {			//ham lay ten nhan vien
    return name;
}

float NhanVien::GiaTien() {				//ham tinh luong 1 nhan vien
    float ftienluong = 1;
    string a = "FULL TIME";
    string b = "PART TIME";
    if(checkstring(loainhanvien,a)) {
        ftienluong = ( 27000*soluonggio*7);
       
    }
    else if(checkstring(loainhanvien,b)) {
        ftienluong = (17000*soluonggio*7);
    }
    return ftienluong;    
}

istream & operator >> (istream &is, NhanVien & n){			//nhap 1 nhan vien ghi vao file
    fflush(stdin);
    cout << setw(93)<<"Nhap ho va ten :";
    getline(is,n.name);
    n.Nhapthongtin();
    cout << setw(97)<<"Nhap loai nhan vien:";
    getline(is,n.loainhanvien);
    cout << setw(95)<<"Nhap so luong gio:";
    is >> n.soluonggio;
	ktraSoLuong(n.soluonggio);
    return is;
}

ostream& operator << (ostream &os, NhanVien & n) {		//nap chong toan tu xuat 1 nhan vien
    os<<"\t\t\t\t\t\t\t\t\t\tHo va ten :"<<n.name;
    n.Xuatthongtin();
    os<<"\t\t\t\t\t\t\t\t\t\tLoai nhan vien :"<<n.loainhanvien<<endl;
    os<<"\t\t\t\t\t\t\t\t\t\tSo luong gio:"<<n.soluonggio<<endl;
    return os;
}

struct Node2 {				//struct node nhan vien
    NhanVien data2;
    Node2* next2;
};

struct SList2 {				//struct danh sach nhan vien
    Node2* head2;
    Node2* tail2;
    long size2;
};

void SList2rong(SList2 &sl) {		//ham tao danh sach nhan vien rong
    sl.head2 = NULL;
    sl.tail2 = NULL;
    sl.size2 = 0;
}

Node2* TaoNode2() {					//tao node nhan vien
	NhanVien v;
    Node2 *p2 = new Node2 ;
	cin >> v;
    p2->data2 = v;
    p2->next2= NULL;
    return p2;
}

void addLast(SList2 &sl , Node2 *p2) {   		//ham them nhan vien vao danh sach
    if(sl.size2 == 0) {
       sl. head2 = p2 ;
       sl. tail2 = p2;
    }
    else {
        sl.tail2 ->next2 = p2;
        sl.tail2 = p2 ;
    }
    sl.size2 =sl.size2+1;
}

void searchbyName(SList2 sl) {					//ham tim kiem nhan vien theo ten
    string fname;
	fflush(stdin);
    cout<<setw(101)<<"Ten nhan vien muon tim :";
    getline(cin,fname);
    Node2*p2 = sl.head2;
    if(p2 == NULL) {
    	cout << "\n\t\t\t\t\t\t\t\t\t\t\t\7Danh sach dang trong.";
    	cout << "\n\n\t\t\t\t\t\t\t\t\t\tNHAN PHIM 1 DE THEM DANH SACH.";
	}
	else {
		int dem=0;
	    while ( p2!= NULL) {
		    if(Uppercase(fname) == Uppercase(p2->data2.getname())) {
				Beep(523,500);  
	    		cin.get();	
		        cout<<endl<<(p2->data2);
		        dem++;
		  	}
		    p2 = p2-> next2;    
	    }
	    if (dem==0) {
	    	cout<<"\n\t\t\t\t\t\t\t\t\t\t\7Khong tim thay nhan vien.";
	    	cout<<"\n\t\t\t\t\t\t\t\t\t\tNHAN PHIM 5 DE TIM LAI.";
	    }
	}
}

void MaxLuong(SList2 sl) {				//ham tim nhan vien luong cao nhat
	
	Node2* p2 = sl.head2;
	if(p2==NULL)
    {
    	cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\7Danh sach dang trong.";
    	cout<<"\n\t\t\t\t\t\t\t\t\t\tNHAN PHIM 1 DE THEM DANH SACH.";
	}
	else {
		NhanVien max = p2->data2;
		Node2* q2 = p2->next2;
		while(q2 != NULL) {
			if(max.GiaTien() < q2->data2.GiaTien()) {
				max = q2->data2;
			}
			q2 = q2->next2;
		}
		Beep(523,500);
	    cin.get();
		cout<<endl;
		cout << "\t\t\t\t\t\t\t\t\t\t______________________________ "<<endl;
		cout << "\t\t\t\t\t\t\t\t\t\tNhan vien co luong cao nhat la: "<<endl;
		cout << max;
		cout<< std::setprecision(20);
		cout<<"\t\t\t\t\t\t\t\t\t\tLuong: "<<max.GiaTien() <<"VND";		
	}	
}

void SuaDoi2(SList2 sl)				//ham chinh sua 1 nhan vien trong danh sach
{	
	Node2 *p2=sl.head2;
	if(p2 == NULL)
	{
		cout << "\n\t\t\t\t\t\t\t\t\t\t\t\7Danh sach rong.";
		cout << "\n\t\t\t\t\t\t\t\t\t\tNHAN PHIM 1 DE NHAP DANH SACH.";
	}
	if(p2 != NULL)
	{
		string m;
		cout<<setw(109)<<"Nhap ten nhan vien can sua doi: ";
		fflush(stdin);
		getline(cin,m);
		int dem = 0;
		while(p2 != NULL)
		{
			if(Uppercase(p2->data2.getname()) == Uppercase(m))
			{
				Beep(523,500);
	    		cin.get(); 
				cin >> p2->data2;
				dem++;
			}
			p2 = p2->next2;
		}
		if(dem == 0)
		{
			cout << "\n\t\t\t\t\t\t\t\t\t\t\7Khong nhan vien trong danh sach";
			cout << "\n\t\t\t\t\t\t\t\t\t\tNHAN PHIM 2 DE TIM LAI.";
		}
	}
}

void XuatDSNV(SList2 sl) {				//ham xuat danh sach nhan vien
	Node2* p2 = sl.head2;
	if(p2==NULL) {
		cout<<"\n\t\t\t\t\t\t\t\t\t\t\tDanh sach rong.";
		cout<<"\n\t\t\t\t\t\t\t\t\t\tNHAN PHIM 1 DE NHAP DANH SACH.";
		cout<<"\7";
	}
	if(p2 != NULL) {
		int i=0;
		cout<<endl<<"\t\t\t\t\t\t\t\t\t\t\tDANH SACH NHAN VIEN:";
		while (p2 != NULL) {
			cout<<endl<<"\t\t\t\t\t\t\t\t\t\t--------------------------------\n";
			cout<<"\n\t\t\t\t\t\t\t\t\t\t\tNHAN VIEN THU "<<i+1<<endl;
			cout<<(p2->data2);
			i++;
			p2 = p2->next2;
		}
		Beep(523,500);
	    cin.get(); 
		cout << endl;
	}
	delete p2;
}
void GhiFileNhanVien(SList2 sl) {			//ghi file nhan vien
	int i=1;
	FILE *file = fopen("NhanVien.txt","w");
	Node2 *p2=sl.head2; 
	fprintf(file,"\t\t\t\t\t=====================================\n");
	fprintf(file,"\t\t\t\t\t=        DANH SACH NHAN VIEN        =\n");
	fprintf(file,"\t\t\t\t\t=====================================\n\n\n");
	while(p2 != NULL) {
		fprintf(file,"\n\n");
		fprintf(file,"\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		fprintf(file,"\t\t\t\t~               NHAN VIEN THU: %2d                    ~\n",i);
		fprintf(file,"\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		fprintf(file,"\t\t\t\t          Ho va ten: %s\n",p2->data2.name.c_str());
		fprintf(file,"\t\t\t\t          Ngay sinh: %2d/%2d/%4d\n",p2->data2.NgaySinh.date,p2->data2.NgaySinh.month,p2->data2.NgaySinh.year);
		fprintf(file,"\t\t\t\t          SDT: %s\n",p2->data2.SDT.c_str());
		fprintf(file,"\t\t\t\t          Dia chi: %15s\n",p2->data2.Diachi.c_str());
		fprintf(file,"\t\t\t\t          Loai nhan vien: %15s\n",p2->data2.loainhanvien.c_str());
		fprintf(file,"\t\t\t\t          Gio lam: %1d\n",p2->data2.soluonggio);
		p2 = p2->next2;
		i++;
	}
	fclose(file);
	Beep(523,500);
	cin.get();
	cout << "\n\t\t\t\t\t\t\t\t\t\tGHI FILE NHAN VIEN THANH CONG!!!";
}

void wpay (SList2 sl) {					//ham dua ra luong nhan vien trong danh sach dua theo ten
    string x;
    int dem=0;
    fflush (stdin);
    cout<<setw(105)<<"Nhap ten nhan vien can tim :";
    getline(cin,x);
    Node2 *p2 = sl.head2;
    while (p2 != NULL) {
        if(Uppercase(x)==Uppercase(p2->data2.getname())){    
            cout<< std::setprecision(20);
            cout<<p2->data2;
            cout<<"\t\t\t\t\t\t\t\t\t\tLuong: "<<p2->data2.GiaTien() <<"d";
            dem++;
        }
		p2=p2->next2;
    }
    if(dem==0) {
			cout<<"\n\t\t\t\t\t\t\t\t\t\tKhong tim thay nhan vien.";
			cout<<"\n\t\t\t\t\t\t\t\t\t\tNHAN PHIM 4 DE TIM LAI.";
	}
    Beep(523,500);
    cin.get(); 
}

//TODO:CLASS NGUYEN LIEU
class NguyenLieu {
    private: 
    	Date d;
        int Coffee,Tra,Sua,Da,LyDung;
    public:
    	NguyenLieu()
    	{
    		d.date=d.month=d.year=0;
    		Coffee=Tra=Sua=Da=LyDung=0;
    	}
		~NguyenLieu(){
		}
    	Date getdate(){
    		return d;
		}
        friend istream &operator >> ( istream &in, NguyenLieu &nl);
        friend ostream &operator << ( ostream &out, NguyenLieu nl);
        float GiaMotNgay();    
		friend void GhiFileNguyenLieu(SList3 l);  
};
void ktraSoNgay(int &k){
	while(k<=0){
		cout<<setw(127)<<"So ngay ban nhap khong hop le! Vui long nhap lai: ";
		cin>>k;
	}
	
}
void ktraSoLuongNL(int &k){
	while(k<=0){
		cout<<setw(127)<<"So luong ban nhap khong hop le! Vui long nhap lai:";
		cin>>k;
	}
	
}
istream &operator >> ( istream &in, NguyenLieu &nl){
    NhapDate(nl.d);
    cout<<setw(104)<<"Nhap so luong nguyen lieu: "<<endl;
    cout<<setw(85)<<"Coffee: ";
    in>>nl.Coffee;
	ktraSoLuongNL(nl.Coffee);
    cout<<setw(82)<<"Tra: ";
    in>>nl.Tra;
	ktraSoLuongNL(nl.Tra);
    cout<<setw(82)<<"Sua: ";
    in>>nl.Sua;
	ktraSoLuongNL(nl.Sua);
    cout<<setw(81)<<"Da: ";
    in>>nl.Da;
	ktraSoLuongNL(nl.Da);
    cout<<setw(86)<<"Ly dung: ";
    in>>nl.LyDung;
	ktraSoLuongNL(nl.LyDung);
    return in;
}
ostream &operator << ( ostream &out, NguyenLieu nl){
    out<<"\t\t\t\t\t\t\t\t\t\tDate:";
    XuatDate(nl.d);
    out<<"\t\t\t\t\t\t\t\t\t\tSo luong nguyen lieu da dung: "<<endl;
    out<<"\t\t\t\t\t\t\t\t\t\tCoffee: "<<nl.Coffee<<endl;
    out<<"\t\t\t\t\t\t\t\t\t\tTra: "<<nl.Tra<<endl;
    out<<"\t\t\t\t\t\t\t\t\t\tSua: "<<nl.Sua<<endl;
    out<<"\t\t\t\t\t\t\t\t\t\tDa: "<<nl.Da<<endl;
    out<<"\t\t\t\t\t\t\t\t\t\tLy dung: "<<nl.LyDung<<endl;
    return out;
}
float NguyenLieu::GiaMotNgay() {
    float GiaNguyenLieu;
    GiaNguyenLieu=80000*Coffee + 30000*Tra + 20000*Sua + 10000*Da + 10000*LyDung;
    return GiaNguyenLieu;
}
//ham tao mot struct node
struct Node3 { 
    NguyenLieu data3;
    struct Node3 *next3;
};
//ham tao mot struct list
struct SList3 {
    Node3 *head3;
    Node3 *tail3;
    long size3;
};
// ham list rong
void KhoiTaoListRong( SList3 &l) {
    l.head3 = NULL;
    l.tail3 = NULL;
    l.size3 = 0;
}
// ham tao node 
Node3* KhoiTaoNodeRong () {
	NguyenLieu x;
    Node3 *p= new Node3; // cap phat vung nho cho node p
    if(p == NULL){
        cout<<"Khong du bo nho de cap phat";
        return NULL;
    }
    else {
    	cin >>x;
        p->data3 = x; // truyen gia tri x vao cho data
        p->next3 = NULL; //p chua tro toi node khac
        return p;
    }
}
void ThemVaoCuoi(SList3 &l, Node3 *p){
    if(l.head3 == NULL){
        l.head3=l.tail3=p;
    }
    else{
        l.tail3->next3=p; // cho con tro pTail lien ket voi node p
        l.tail3=p; // cap nhat lai la node cuoi
    }
    l.size3= l.size3 +1;
}
//ham xuat danh sach nguyen lieu
void XuatDSNL(SList3 l) {				
	Node3* p =l.head3;
	if(p==NULL) {
		cout<<"\n\t\t\t\t\t\t\t\t\t\t\tDanh sach rong.";
		cout<<"\n\t\t\t\t\t\t\t\t\t\t\7NHAN PHIM 1 DE NHAP DANH SACH.";
	}
	if(p != NULL) {
		int i=0;
		cout<<endl<<"\t\t\t\t\t\t\t\t\t\t\tDANH SACH NGUYEN LIEU:";
		while (p != NULL) {
			cout<<endl<<"\t\t\t\t\t\t\t\t\t\t--------------------------------\n";
			cout<<"\n\t\t\t\t\t\t\t\t\t\t\tNGAY THU "<<i+1<<endl;
			cout<<(p->data3);
			i++;
			p = p->next3;
		}
		cout << endl;
		Beep(523,500);
	    cin.get(); 
		}
	delete p;
}
//ham ghi file nguyen lieu
void GhiFileNguyenLieu(SList3 l) {			//ghi file nguyen lieu
	FILE *file = fopen("NguyenLieu.txt","w");
	Node3 *p=l.head3; 
		fprintf(file,"\t\t\t\t\t=====================================\n");
		fprintf(file,"\t\t\t\t\t=        DANH SACH NGUYEN LIEU      =\n");
		fprintf(file,"\t\t\t\t\t=====================================\n\n\n");
	while(p != NULL) {
		fprintf(file,"\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		fprintf(file,"\t\t\t\t~                     Ngay: %2d/%2d/%4d               ~\n",p->data3.d.date,p->data3.d.month,p->data3.d.year);
		fprintf(file,"\t\t\t\t~   STT    |   Ten nguyen lieu    |      So luong    ~\n");
		fprintf(file,"\t\t\t\t~    1     |         Cafe         |        %.2f      ~\n",p->data3.Coffee);
		fprintf(file,"\t\t\t\t~    2     |         Tra          |        %.2f      ~\n",p->data3.Tra);
		fprintf(file,"\t\t\t\t~    3     |         Sua          |        %.2f      ~\n",p->data3.Sua);
		fprintf(file,"\t\t\t\t~    4     |         Da           |        %.2f      ~\n",p->data3.Da);
		fprintf(file,"\t\t\t\t~    5     |         Ly dung      |        %.2f      ~\n",p->data3.LyDung);
		fprintf(file,"\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		p = p->next3;
	}
	fclose(file);
	Beep(523,500);
	cin.get();
	cout << "\n\t\t\t\t\t\t\t\t\t\tGHI FILE NGUYEN LIEU THANH CONG!!!";
}
void TongTien(SList3 l){
	float Tong=0;
	Node3 *p=l.head3;
	if(p==NULL){
		cout << "\n\t\t\t\t\t\t\t\t\t\t\t\7Danh sach dang rong.";
		cout << "\n\n\t\t\t\t\t\t\t\t\t\tNHAN PHIM 1 DE THEM DANH SACH.";
	}
	else {
		while(p!=NULL){
			Tong = Tong + p->data3.GiaMotNgay();
			p=p->next3;
		}
		Beep(523,500);  
		cin.get();
		cout<< std::setprecision(20);
		cout << "\n\t\t\t\t\t\t\t\t\t\tTong tien nguyen lieu la: " <<Tong<<"VND";
	}	
}
void SuaDoi3(SList3 l)				//ham chinh sua 1 ngay trong danh sach
{	
	Node3 *p=l.head3;
	if(p == NULL)
	{
		cout << "\n\t\t\t\t\t\t\t\t\t\t\t\7Danh sach rong.";
		cout << "\n\t\t\t\t\t\t\t\t\t\tNHAN PHIM 1 DE NHAP DANH SACH.";
	}
	if(p != NULL)
	{
		Date m;
		cout<<setw(102)<<"Nhap Date can chinh sua: ";
		NhapDate(m);
		int dem = 0;
		while(p != NULL)
		{
			if(SS(p->data3.getdate(),m)==1)
			{
				Beep(523,500);
	    		cin.get(); 
				cin >> p->data3;
				dem++;
			}
			p = p->next3;
		}
		if(dem == 0)
		{
			cout << "\n\t\t\t\t\t\t\t\t\t\t\7Khong co ngay trong danh sach";
			cout << "\n\t\t\t\t\t\t\t\t\t\tNHAN PHIM 2 DE TIM LAI.";
		}
	}
}
//ham tao tieu de
void TieuDe() {
	cout<<endl<<endl;
	cout<<setw(120)<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl; 
	cout<<setw(120)<<"@                                                          @"<<endl; 
	cout<<setw(120)<<"@                                                          @"<<endl; 
	cout<<setw(120)<<"@          **     **  *****  **   **  **  **               @"<<endl; 
	cout<<setw(120)<<"@          ** * * **  **     ** * **  **  **               @"<<endl; 
	cout<<setw(120)<<"@          **  *  **  *****  **  ***  **  **               @"<<endl; 
	cout<<setw(120)<<"@          **     **  **     **   **  **  **               @"<<endl; 
	cout<<setw(120)<<"@          **     **  *****  **   **   ****                @"<<endl; 
	cout<<setw(120)<<"@                                                          @"<<endl; 
	cout<<setw(120)<<"@                                                          @"<<endl; 
	cout<<setw(120)<<"@   Cafe den      :  35K           Cold brew     :   35K   @"<<endl; 
	cout<<setw(120)<<"@   Bac siu       :  38K           Cafe sua      :   38K   @"<<endl; 
	cout<<setw(120)<<"@   Cappuccino    :  40K           Americano     :   40K   @"<<endl; 
	cout<<setw(120)<<"@   Tra matcha    :  55K           Tra vai       :   55K   @"<<endl; 
	cout<<setw(120)<<"@   Tra hat sen   :  50K           Hong tra latte:   50K   @"<<endl; 
	cout<<setw(120)<<"@   Tra dao cam sa:  59K           Tra sua mac ca:   59K   @"<<endl; 
	cout<<setw(120)<<"@   Tra viet quoc :  60K           Tra sua oolong:   60K   @"<<endl; 
	cout<<setw(120)<<"@                                                          @"<<endl; 
	cout<<setw(120)<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl<<endl<<endl;
}

void menuChung() {
	system("cls");
	int n;
	cout<<endl<<endl<<endl;
	cout<<setw(135)<<"........................................................................................."<<endl;	
	cout<<setw(135)<<".%%%%%%..%%%%%%..%%%%%%..%%%%..%%%...%%%......%%%%%...%%%%%..%%%%%%.%%%%%%.%%%%%%.%%%%%%."<<endl;	
	cout<<setw(135)<<".%%...%%.%%...%%.%%.....%%..%%.%%%%.%%%%.....%%%..%%.%%...%%.%%.....%%.....%%.....%%....."<<endl;	
	cout<<setw(135)<<".%%...%%.%%%%%%..%%%%%..%%%%%%.%%..%..%%.....%%%.....%%...%%.%%%%%..%%%%%..%%%%%..%%%%%.."<<endl;	
	cout<<setw(135)<<".%%...%%.%%...%%.%%.....%%..%%.%%.....%%.....%%%..%%.%%...%%.%%.....%%.....%%.....%%....."<<endl;	
	cout<<setw(135)<<".%%%%%%..%%...%%.%%%%%%.%%..%%.%%.....%%......%%%%%...%%%%%..%%.....%%.....%%%%%%.%%%%%%."<<endl;	
	cout<<setw(135)<<"........................................................................................."<<endl;	
	cout<<setw(95)<<"NHAN PHIM"<<endl;
	cout<<setw(97)<<"1.Khach hang."<<endl;
	cout<<setw(96)<<"2.Nhan vien."<<endl;
	cout<<setw(98)<<"3.Nguyen lieu."<<endl;
	cout<<setw(105)<<"Nhap doi tuong muon xu ly: ";
	cin>>n;
	if(n==1) {
		system("cls");
		menu1();
	}
	else if(n==2) {
		system("cls");
		menu2();
	}
	else if(n==3) {
		system("cls");
		menu3();
	}
	else {
		cout<<"\n\n\t\t\t\t\t\t\t\t\t\t\t\7MOI BAN NHAN LAI:";
		sleep(1); 			//keo dai time hien thi dong chu
		menuChung();
	}
}

void menu1() {
	system("cls");
	int luachon;
	SList1 l;
	SList1rong(l);
	TieuDe();
    cout<<endl<<endl;
	cout<<setw(120)<<"=========================================================="<<endl; 
	cout<<setw(120)<<"=               Nhap 1: Nhap DS khach hang.              ="<<endl; 
	cout<<setw(120)<<"=               Nhap 2: Chinh sua khach hang.            ="<<endl; 
	cout<<setw(120)<<"=               Nhap 3: Xuat DS khach hang.              ="<<endl; 
	cout<<setw(120)<<"=               Nhap 4: Ghi file khach hang.             ="<<endl; 
	cout<<setw(120)<<"=               Nhap 5: Hoa don cua 1 khach.             ="<<endl; 
	cout<<setw(120)<<"=               Nhap 6: Tro ve menu chinh.               ="<<endl; 
	cout<<setw(120)<<"=               Nhap 7: Thoat chuong trinh.              ="<<endl; 
	cout<<setw(120)<<"=========================================================="<<endl; 
	fflush(stdin);
	cout<<setw(92)<<"Nhap lua chon: ";
	while (1) {
		cout<<endl<<setw(93)<<"Nhap chuc nang: ";
		cin>>luachon;
		if(luachon==1) {
			int n,i=0;
			cout<<setw(102)<<"Nhap so luong khach hang:";
			cin>>n;
			ktraSoLuong(n);
			for(int j=0;j<n;j++) {
				cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\tKHACH HANG THU "<<++i<<":"<<endl;
				Node *p=Taonode1();
				Themcuoi1(l,p);
			}
		}
		else if(luachon==2) {
			SuaDoi1(l);
		}
		else if(luachon==3) {
			XuatDSKH(l);
		}
		else if(luachon==4) {
			GhiFileKhachHang(l);
		}
		else if(luachon==5) {
			Hoadon(l);
		}
		else if(luachon==6) {
			system("cls");
			menuChung();
		}
		else if(luachon==7) {
			exit(0);
		}
		else {
			cout<<endl;
			cout<<setw(136)<<"\n\t\t\t\t\t\t\tLua chon khong hop le.Vui long chon lai!";
		}
	}
}

void menu2() {
	system("cls");
	int luachon;
	SList2 sl;
	SList2rong(sl);
    cout<<endl;
	cout<<setw(120)<<"=========================================================="<<endl; 
	cout<<setw(120)<<"=               Nhap 1: Nhap DS nhan vien.               ="<<endl; 
	cout<<setw(120)<<"=               Nhap 2: Chinh sua nhan vien.             ="<<endl; 
	cout<<setw(120)<<"=               Nhap 3: Xuat DS nhan vien.               ="<<endl; 
	cout<<setw(120)<<"=               Nhap 4: Ghi file nhan vien.              ="<<endl; 
	cout<<setw(120)<<"=               Nhap 5: Tim kiem nhan vien.              ="<<endl; 
	cout<<setw(120)<<"=               Nhap 6: Xuat luong nhan vien.            ="<<endl; 
	cout<<setw(120)<<"=               Nhap 7: Luong nhan vien cao nhat.        ="<<endl;  
	cout<<setw(120)<<"=               Nhap 8: Tro ve menu chinh.               ="<<endl; 
	cout<<setw(120)<<"=               Nhap 9: Thoat chuong trinh.              ="<<endl; 
	cout<<setw(120)<<"=========================================================="<<endl; 
	cout<<setw(92)<<"Nhap lua chon: ";
	while (1) {
		cout<<endl<<setw(93)<<"Nhap chuc nang: ";
		cin>>luachon;
		if(luachon==1) {
			int n,i=0;
			cout<<setw(101)<<"Nhap so luong nhan vien:";
			cin>>n;
			ktraSoLuong(n);
			for(int j=0;j<n;j++) {
				cout<<endl;
				cout<<setw(95)<<"NHAN VIEN THU "<<++i<<":"<<endl;
				Node2 *p3=TaoNode2();
				addLast(sl,p3);
			}
		}
		else if(luachon==2) {
			SuaDoi2(sl);
		}
		else if(luachon==3) {
			XuatDSNV(sl);
		}
		else if(luachon==4) {
			GhiFileNhanVien(sl);
		}
		else if(luachon==5) {
			searchbyName(sl);
		}
		else if(luachon==6) {
			wpay(sl);
		}
		else if(luachon==7) {
			MaxLuong(sl);
		}
	
		else if(luachon==8) {
			system("cls");
			menuChung();
		}
		else if(luachon==9) {
			exit(0);
		}
		else {
			cout<<endl;
			cout<<setw(136)<<"\n\t\t\t\t\t\t\tLua chon khong hop le. Vui long chon lai!";
		}
	}
}

void menu3() {
	system("cls");
	int luachon;
	SList3 l;
	KhoiTaoListRong(l);
    cout<<endl;
	cout<<setw(120)<<"=========================================================="<<endl; 
	cout<<setw(120)<<"=               Nhap 1: Nhap DS nguyen lieu.             ="<<endl; 
	cout<<setw(120)<<"=               Nhap 2: Chinh sua nguyen lieu.           ="<<endl; 
	cout<<setw(120)<<"=               Nhap 3: Xuat DS nguyen lieu.             ="<<endl; 
	cout<<setw(120)<<"=               Nhap 4: Ghi file nguyen lieu.            ="<<endl; 
	cout<<setw(120)<<"=               Nhap 5: Tong tien nguyen lieu.           ="<<endl; 
	cout<<setw(120)<<"=               Nhap 6: Tro ve menu chinh.               ="<<endl; 
	cout<<setw(120)<<"=               Nhap 7: Thoat chuong trinh.              ="<<endl; 
	cout<<setw(120)<<"=========================================================="<<endl; 

	cout<<setw(92)<<"Nhap lua chon: ";
	while (1) {
		cout<<endl<<setw(93)<<"Nhap chuc nang: ";
		cin>>luachon;
		if(luachon==1) {
			int n,i=0;
			cout<<setw(110)<<"Nhap so ngay su dung nguyen lieu:";
			cin>>n;
			ktraSoNgay(n);
			for(int j=0;j<n;j++) {
				cout<<endl;
				cout<<setw(89)<<"\t\tNGUYEN LIEU NGAY THU "<<++i<<":"<<endl;
				Node3 *p=KhoiTaoNodeRong();
				ThemVaoCuoi(l,p);
			}
		}
		else if(luachon==2) {
			SuaDoi3(l);
		}
		else if(luachon==3) {
			XuatDSNL(l);
		}
		else if(luachon==4) {
			GhiFileNguyenLieu(l);
		}
		else if(luachon==5) {
			TongTien(l);
		}
		else if(luachon==6) {
			system("cls");
			menuChung();
		}
		else if(luachon==7) {
			exit(0);
		}
		else {
			cout<<endl;
			cout<<setw(136)<<"\n\t\t\t\t\t\t\t\t\t\t\t\tLua chon khong hop le. Vui long chon lai!";
		}
	}
}

int main() {
	system("color b0"); //thiet lap mau nen va mau chu //a-s:nen //0-7:mau chu
	menuChung();
}