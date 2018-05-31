// project_library.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<fstream>
#include<iostream>
#include<string.h>
#include<iomanip>
#include<ctype.h>
#include<time.h>
#include<stdlib.h>
#include <math.h>
#include<ctime>
using namespace std;
struct user_info {
	char name[50];
	char birth[16];
	char social_ID[15];
	char address[100]; // c?u trúc c?a d?a ch?: tên du?ng/ phu?ng/ qu?n(huy?n)/ thành ph?.
	char sex[8];
	char stt[9];
	int ptruser;
};
struct user {
	char username[50];
	char pwd[50];
	int ptr;
};
struct date
{
	int ngay;
	int thang;
	int nam;
};
struct thongtinthedocgia
{
	char madocgia[10];
	char ho_tendem[30];
	char ten[10];
	char CMND[11];
	char gioitinh[5];

	date ngaysinh;
	char email[50];
	date ngaylapthe;
	char diachi[100];

	date ngayhethanthe;

};

struct thongtinsach
{
	char masach[50];
	char tensach[50];
	char tacgia[50];
	char nxb[50];
	date ngayxb;
	char theloai[50];
	int giasach;
	int soquyensach;
	int slcon;
};


struct nodedocgia
{
	thongtinthedocgia data;
	struct nodedocgia *pnext;
};

struct listdg
{
	nodedocgia *phead;
	nodedocgia *ptail;
	int sl;
};
//Chuc nang quan li doc gia
void indate(date a)
{
	printf("%d/%d/%d\n", a.ngay, a.thang, a.nam);
}
void nhapngay(date &a)
{
	printf("Nhap ngay:\n");
	scanf("%d", &a.ngay);
	printf("Nhap thang:\n");
	scanf("%d", &a.thang);
	printf("Nhap nam:\n");
	scanf("%d", &a.nam);
}
bool timmsdg(listdg a, char ms[10])
{
	nodedocgia *p = a.phead;
	for (; p != NULL; p = p->pnext)
	{
		if (_stricmp(p->data.madocgia, ms) == 0)
			return true;
	}
	delete p;
	return false;

}
thongtinthedocgia nhapthongtindocgia(listdg &a)
{
	fflush(stdin);
	thongtinthedocgia n;
	printf("Them mot doc gia vao thu vien\n");
	printf("Nhap ma doc gia: ");
	scanf("%s",&n.madocgia);
	cin.ignore();
	printf("Nhap ho va ten dem: ");
	gets_s(n.ho_tendem,30);
	printf("Nhap ten: ");
	scanf("%s",&n.ten);
	fflush(stdin);
	printf("Nhap CMND: ");
	scanf("%s", &n.CMND);
	cin.ignore();
	printf("Nhap gioi tinh: ");
	scanf("%s",&n.gioitinh);
	cin.ignore();
	printf("Nhap email: ");
	gets_s(n.email);
	printf("Nhap dia chi: ");
	gets_s(n.diachi);
	printf("Nhap ngay lap the:\n");
	nhapngay(n.ngaylapthe);
	n.ngayhethanthe.ngay = n.ngaylapthe.ngay;
	n.ngayhethanthe.thang = n.ngaylapthe.thang;
	n.ngayhethanthe.nam = n.ngaylapthe.nam + 4;
	printf("Ngay het han the: ");
	indate(n.ngayhethanthe);
	fflush(stdin);
	printf("Nhap ngay thang nam sinh:\n");
	nhapngay(n.ngaysinh);

	return n;


}
void addsldg(listdg a)
{
	FILE *f = fopen("Sl_docgia.txt", "w");
	fprintf(f, "%d", a.sl);
	fclose(f);
}

nodedocgia* createnodedg(listdg &a)
{
	nodedocgia *p = new nodedocgia;
	if (p == NULL)
	{
		printf("Loi khong du bo nho\n");
		return NULL;
	}
	else
	{
		p->data = nhapthongtindocgia(a);
		p->pnext = NULL;
	}
	return p;

}
void create_head_tail_sl_dg(listdg &a)
{
	a.phead = a.ptail = NULL;
	a.sl = 0;
}
void adddocgia(listdg &a)
{
	nodedocgia *p = new nodedocgia[1];

	p = createnodedg(a);
	if (a.phead == NULL)
		a.phead = a.ptail = p;
	else
	{
		a.ptail->pnext = p;
		a.ptail = p;

	}
	a.sl = a.sl + 1;
	FILE *f = fopen("Listdocgia.bin", "a");
	fwrite(&p->data, sizeof(thongtinthedocgia), 1, f);
	fclose(f);
	addsldg(a);

}
nodedocgia* newnodedocgia(thongtinthedocgia a)
{
	nodedocgia *p = new nodedocgia;
	p->data = a;
	p->pnext = NULL;
	return p;

}

void adddocgia_file(listdg &a)
{

	create_head_tail_sl_dg(a);

	FILE *p = fopen("Sl_docgia.txt", "r");
	fscanf(p, "%d", &a.sl);
	fclose(p);
	FILE *f = fopen("Listdocgia.bin", "r");
	if (f == NULL)
	{
		printf("Khong mo duoc file\n");
		exit(0);
	}
	thongtinthedocgia data;
	fread(&data, sizeof(thongtinthedocgia), 1, f);

	while (feof(f) == 0)
	{

		nodedocgia *x = newnodedocgia(data);
		if (a.phead == NULL)
			a.phead = a.ptail = x;
		else
		{
			a.ptail->pnext = x;
			a.ptail = x;
		}
		fread(&data, sizeof(thongtinthedocgia), 1, f);


	}
	fclose(f);
}





struct nodebook
{
	thongtinsach data;
	nodebook *pnext;

};
struct listbook
{
	nodebook *phead;
	nodebook *ptail;
	int sl;

};


int namnhuan(int nam)
{
	if ((nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0)) return 366;
	else return 365;
}
int songaytrongthang(int thang, int nam)
{
	int songay;
	switch (thang)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		songay = 31; break;
	case 2:
		if (namnhuan(nam) == 366)
		{
			songay = 29;
			break;
		}
		else
		{
			songay = 28;
			break;
		}
	default:
		songay = 30; break;
	}
	return songay;
}
int songaytudaunam(date a)
{
	int songay = 0;
	for (int i = 1; i < a.thang; i++)
		songay = songay + songaytrongthang(i, a.nam);
	songay = songay + a.ngay;
	return songay;
}


void indanhsachdocgia()
{
	FILE *f = fopen("Listdocgia.bin", "r");
	thongtinthedocgia p;
	printf("Danh sach doc gia\n");
	printf("Ma doc gia\t\tHo va ten\t\t Gioi tinh\n");
	fread(&p, sizeof(thongtinthedocgia), 1, f);

	while (feof(f) == 0)
	{
		printf("%s%29s %s%18s\n", p.madocgia, p.ho_tendem, p.ten, p.gioitinh);
		fread(&p, sizeof(thongtinthedocgia), 1, f);

	}
	fclose(f);

}
nodedocgia* timdocgiatheocmnd(listdg a, char cmnd[])
{
	if (a.phead != NULL)
	{
		nodedocgia *p = new nodedocgia;
		p = a.phead;
		for (; p != NULL; p = p->pnext)
		{
			if (strcmp(p->data.CMND, cmnd) == 0)
			{
				return p;
			}
		}
		return NULL;
	}
	if (a.phead == NULL)
	{
		printf("Chua co doc gia nao trong danh sach\n");
		return NULL;
	}
}

void xoathongtindocgia(listdg &a)
{
	printf("Xoa thong tin doc gia\n");
	printf("Nhap CMND\n");
	char cmnd[11];
	scanf("%s", &cmnd);
	nodedocgia* x = new nodedocgia;
	x = timdocgiatheocmnd(a, cmnd);

	while (x == NULL)
	{
		printf("Khong tim thay CMND\n");
		printf("Nhap lai CMND\n");
		scanf("%s", &cmnd);
	}
	if (x == a.phead)
	{
		a.phead = x->pnext;
		x->pnext = NULL;
		delete x;
	}
	else
		if (x == a.ptail)
		{
			nodedocgia *ptailsau = a.phead;
			for (; ptailsau->pnext != a.ptail; ptailsau = ptailsau->pnext);
			ptailsau->pnext = NULL;
			a.ptail = ptailsau;
			delete x;
			delete ptailsau;
		}
		else
		{
			nodedocgia *vitritruoc = a.phead;
			nodedocgia *vitrisau = x->pnext;
			for (; vitritruoc->pnext != x; vitritruoc = vitritruoc->pnext);
			vitritruoc->pnext = vitrisau;
			x->pnext = NULL;

			delete x;

		}
	a.sl--;

	printf("Xoa thanh cong\n");
	FILE *f = fopen("Listdocgia.bin", "w");

	nodedocgia *recover = a.phead;
	for (; recover != NULL; recover = recover->pnext)
	{
		fwrite(&recover->data, sizeof(thongtinthedocgia), 1, f);

	}
	fclose(f);
	FILE *slsach = fopen("Sl_docgia.txt", "w");
	fprintf(slsach, "%d", a.sl);
	fclose(slsach);
}
void suathongtindocgia(listdg &a)
{

	char cm[11];
	printf("Nhap CMND\n");
	scanf("%s", &cm);
	nodedocgia * x = new nodedocgia;
	x = timdocgiatheocmnd(a, cm);
	while (x == NULL)
	{
		printf("Khong tim thay CMND\n");
		printf("Nhap lai\n");
		scanf("%s", &cm);
	}
	printf("Sua thong tin doc gia\n");
	fflush(stdin);

	printf("Nhap ho va ten dem\n");
	scanf("%s",&x->data.ho_tendem);
	printf("Nhap ten: ");
	scanf("%s",&x->data.ten);
	printf("Nhap ngay thang nam sinh\n");
	nhapngay(x->data.ngaysinh);
	cin.ignore();
	printf("Nhap CMND\n");
	scanf("%s", &x->data.CMND);
	printf("Nhap gioi tinh\n");
	scanf("%s",&x->data.gioitinh);
	printf("Nhap email\n");
	scanf("%s",&x->data.email);
	printf("Nhap dia chi\n");
	scanf("%s",&x->data.diachi);
	FILE *f = fopen("Listdocgia.bin", "w");

	nodedocgia *recover = a.phead;
	for (; recover != NULL; recover = recover->pnext)
	{
		fwrite(&recover->data, sizeof(thongtinthedocgia), 1, f);

	}
	fclose(f);
}
thongtinthedocgia* timtheohoten(listdg a)
{

	printf("Nhap ho ten can tim\n");
	char str1[30];
	char str2[10];
	printf("Nhap ho va ten dem\n");
	cin.ignore();
	gets_s(str1, 30);
	printf("Nhap ten\n");
	fflush(stdin);
	gets_s(str2, 10);
	thongtinthedocgia *p = new thongtinthedocgia;
	FILE *f = fopen("Listdocgia.bin", "rb");
	fseek(f, 0, SEEK_SET);
	while (!feof(f) && fread(p, sizeof(thongtinthedocgia), 1, f))
	{
		if (strcmp(str1, p->ho_tendem) == 0 && strcmp(str2, p->ten) == 0)
			return p;
	}
	return NULL;
}
void sapxepdanhsachdocgiatheoten(listdg &a)
{
	for (nodedocgia *i = a.phead; i->pnext != a.ptail; i = i->pnext)
	{
		for (nodedocgia * j = i->pnext; j != NULL; j = j->pnext)
			if (_stricmp(i->data.ten, j->data.ten) > 0)
			{
				thongtinthedocgia doi = i->data;
				i->data = j->data;
				j->data = doi;
			}
	}
}
//Chuc nang quan li sach
thongtinsach nhapthongtinsach(listbook &b)
{
	thongtinsach n;
	fflush(stdin);
	printf("Them mot sach vao thu vien\n");
	printf("Nhap ma sach\n");
	cin.ignore();
	gets_s(n.masach);
	printf("Nhap ten sach\n");
	gets_s(n.tensach);
	printf("Nhap tac gia\n");
	gets_s(n.tacgia);
	printf("Nhap NXB\n");
	gets_s(n.nxb);
	fflush(stdin);
	printf("Nhap ngay xuat ban\n");
	nhapngay(n.ngayxb);
	fflush(stdin);
	printf("Nhap the loai\n");
	cin.ignore();
	gets_s(n.theloai);
	printf("Nhap gia sach\n");
	fflush(stdin);
	scanf("%d", &n.giasach);
	printf("Nhap so luong sach\n");
	scanf("%d", &n.soquyensach);
	n.slcon = n.soquyensach;
	return n;
}
nodebook *createnodebook(listbook &b)
{
	nodebook *p = new nodebook;
	if (p == NULL)
	{
		printf("Loi khong du bo nho\n");
		return NULL;
	}
	else
	{
		p->data = nhapthongtinsach(b);
		p->pnext = NULL;
	}
	return p;
}
nodebook* newnodebook(thongtinsach a)
{
	nodebook *p = new nodebook;
	p->data = a;
	p->pnext = NULL;
	return p;

}

void addslbook(listbook b)
{
	FILE *f = fopen("Sl_sach.txt", "w");
	fprintf(f, "%d", b.sl);
	fclose(f);
}
void create_head_tail_sl_book(listbook &a)
{
	a.phead = a.ptail = NULL;
	a.sl = 0;
}

void addbook_file(listbook &b)
{

	create_head_tail_sl_book(b);

	FILE *p = fopen("Sl_sach.txt", "r");
	fscanf(p, "%d", &b.sl);
	fclose(p);
	FILE *f = fopen("Listsach.bin", "r");
	if (f == NULL)
	{
		printf("Khong mo duoc file\n");
		exit(0);
	}
	thongtinsach data;
	fread(&data, sizeof(thongtinsach), 1, f);

	while (feof(f) == 0)
	{

		nodebook *x = newnodebook(data);
		if (b.phead == NULL)
			b.phead = b.ptail = x;
		else
		{
			b.ptail->pnext = x;
			b.ptail = x;
		}
		fread(&data, sizeof(thongtinsach), 1, f);


	}
	fclose(f);
}
void addbook(listbook &b)
{

	nodebook *p = new nodebook[1];

	p = createnodebook(b);
	if (b.phead == NULL)
		b.phead = b.ptail = p;
	else
	{
		b.ptail->pnext = p;
		b.ptail = p;

	}
	b.sl = b.sl + 1;
	FILE *f = fopen("Listsach.bin", "a");
	fwrite(&p->data, sizeof(thongtinsach), 1, f);
	fclose(f);
	addslbook(b);

}
// co van de khoang cach
void indssach()
{

	FILE *f = fopen("Listsach.bin", "r");

	cout << "\n \n                 DANH SACH CAC DAU SACH CO TRONG THU VIEN ";
	cout << "\n  ÉÍÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍÍÍÍÑÍÍÍÍÍÑÍÍÍÍÍ»";
	cout << "\n  ºMa Sach ³                Ten Sach                ³  The Loai   ³ TSL º";
	cout << "\n  ÌÍÍÍÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍØÍÍÍÍÍ¹";
	thongtinsach p;
	fread(&p, sizeof(thongtinsach), 1, f);
	while (feof(f) == 0)
	{
		cout << "\n  º" << p.masach << setw(10 - strlen(p.masach) + 1) << "³" << p.tensach << setw(50 - strlen(p.tensach) + 1) << "³" << p.theloai << setw(50 - strlen(p.theloai) + 1) << "³" << setw(5) << p.soquyensach << "³" << setw(5) << "º";
		fread(&p, sizeof(thongtinsach), 1, f);
	}

	cout << "\n  ÈÍÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍÍÍÍÍÏÍÍÍÍÍÏÍÍÍÍÍ¼";

	fclose(f);

}
void indssach2()
{

	FILE *f = fopen("Listsach.bin", "r");

	printf("Ma so sach\t\tTen sach\t\tSo luong sach\tSo luong hien co\n");


	thongtinsach p;
	fread(&p, sizeof(thongtinsach), 1, f);
	while (feof(f) == 0)
	{

		printf("%s%32s%18d%18d\n", p.masach, p.tensach, p.soquyensach, p.slcon);

		fread(&p, sizeof(thongtinsach), 1, f);

	}



	fclose(f);

}
// co van de
nodebook* timtheotensach(listbook b)
{

	printf("Nhap ten sach can tim\n");
	cin.ignore();
	char *str1 = new char[50];
	gets_s(str1,50);
	nodebook *p = new nodebook;

	p = b.phead;
	for (; p != NULL; p = p->pnext)
	{
		if (_stricmp(str1, p->data.tensach) == 0)
		{
			return p;
		}

	}
	return NULL;
}
nodebook* timtheoIBSN(listbook b, char *masach)
{

	nodebook *p = new nodebook;
	p = b.phead;
	for (; p != NULL; p = p->pnext)
	{
		if (_stricmp(masach, p->data.masach) == 0)
			return p;
	}
	return NULL;
}
void xoathongtinsach(listbook &b)
{
	printf("Xoa thong tin sach\n");

	printf("Nhap ma sach can tim\n");
	cin.ignore();
	char *str1 = new char[50];
	gets_s(str1, 30);
	nodebook* x = timtheoIBSN(b, str1);

	while (x == NULL)
	{
		printf("Khong tim thay ma sach\n");
		int n;
		printf("Nhan 1 de thoat chuong trinh, nhan 2 de nhap lai ma sach\n");
		scanf("%d", &n);
		fflush(stdin);
		switch (n)
		{
		case 1:exit(0);
		case 2:gets_s(str1, 30); break;

		}
		x = timtheoIBSN(b, str1);
	}
	if (x == b.phead)
	{
		b.phead = x->pnext;
		x->pnext = NULL;
		delete x;
	}
	else
		if (x == b.ptail)
		{
			nodebook *ptailsau = b.phead;
			for (; ptailsau->pnext != b.ptail; ptailsau = ptailsau->pnext);
			ptailsau->pnext = NULL;
			b.ptail = ptailsau;

			delete x;
			delete ptailsau;
		}
		else
		{
			nodebook *vitritruoc = b.phead;
			nodebook *vitrisau = x->pnext;
			for (; vitritruoc->pnext != x; vitritruoc = vitritruoc->pnext);
			vitritruoc->pnext = vitrisau;
			x->pnext = NULL;
			b.sl--;

			delete x;

		}
	b.sl--;

	printf("Xoa thanh cong\n");
	FILE *f = fopen("Listsach.bin", "w");

	nodebook *recover = b.phead;
	for (; recover != NULL; recover = recover->pnext)
	{
		fwrite(&recover->data, sizeof(thongtinsach), 1, f);

	}
	fclose(f);
	FILE *slsach = fopen("Sl_sach.txt", "w");
	fprintf(slsach, "%d", b.sl);
	fclose(slsach);
}
void suathongtinsach(listbook &b)
{

	printf("Sua thong tin sach\n");
	printf("Nhap ma sach can tim\n");
	cin.ignore();
	char *str1 = new char[50];
	gets_s(str1, 30);
	nodebook* x = timtheoIBSN(b, str1);

	while (x == NULL)
	{
		printf("Khong tim thay ma sach\n");
		printf("Nhap lai ma sach\n");
		gets_s(str1, 30);
	}

	printf("Nhap ma sach\n");
	gets_s(x->data.masach);
	printf("Nhap ten sach\n");
	gets_s(x->data.tensach);
	printf("Nhap tac gia\n");
	gets_s(x->data.tacgia);
	printf("Nhap NXB\n");
	gets_s(x->data.nxb);
	fflush(stdin);
	printf("Nhap ngay xuat ban\n");
	nhapngay(x->data.ngayxb);
	cin.ignore();
	printf("Nhap the loai\n");
	gets_s(x->data.theloai);
	printf("Nhap gia sach\n");
	cin.ignore();
	scanf("%d", &x->data.giasach);
	printf("Nhap so luong sach\n");
	cin.ignore();
	scanf("%d", &x->data.soquyensach);
	FILE *f = fopen("Listsach.bin", "w");

	nodebook *recover = b.phead;
	for (; recover != NULL; recover = recover->pnext)
	{
		fwrite(&recover->data, sizeof(thongtinsach), 1, f);

	}
	fclose(f);

}
//Chuc nang lap phieu muon/tra sach
struct phieumuon
{
	char madocgia[10];
	date ngaymuon;
	date ngaytradukien;
	thongtinsach sachmuon;
	int soluongmuon;
};
struct nodephieumuon
{
	phieumuon data;
	nodephieumuon *pnext;
};
struct listphieumuon
{
	nodephieumuon *phead;
	nodephieumuon *ptail;
	int sl;
};
void nhapIBSN_sachduocmuon(listbook a, char *IBSN[])
{
	IBSN = new char*[a.sl];

	nodebook *x = a.phead;
	for (int i = 0; x != NULL; x = x->pnext)
	{
		IBSN[i] = new char[50];
		strcpy(IBSN[i], x->data.masach);
	}

}
struct phieutra
{
	char madocgia[10];
	date ngaymuon;
	date ngaytradukien;
	date ngaytrathucte;
	int songaymuon;
	int tienphat;
	int matsach;
	thongtinsach sachmuon;
	int soquyentra;
	int soluongmuon;
};

struct nodephieutra
{

	phieutra data;
	nodephieutra *pnext;
};
struct listphieutra
{
	nodephieutra *phead;
	nodephieutra *ptail;
	int sl;
};
void create_head_tail_phieumuon(listphieumuon &p)
{
	p.phead = p.ptail = NULL;
	p.sl = 0;
}
void create_head_tail_phieutra(listphieutra &t)
{
	t.phead = t.ptail = NULL;
	t.sl = 0;
}
void addslphieumuon(listphieumuon p)
{
	FILE *f = fopen("Sl_phieumuon.txt", "w");
	fprintf(f, "%d", p.sl);
	fclose(f);
}
int sachdamuon(thongtinsach a[], int sosachkhacnhaumuon, char tensachmuon[50])
{

	for (int i = 0; i < sosachkhacnhaumuon; i++)
		if (_stricmp(a[i].tensach, tensachmuon) == 0)
			return i;
	return -1;
}

void addslphieutra(listphieutra t)
{
	FILE *f = fopen("Sl_phieutra.txt", "w");
	fprintf(f, "%d", t.sl);
	fclose(f);
}
nodephieumuon* newnodephieumuon(phieumuon a)
{
	nodephieumuon *p = new nodephieumuon;
	p->data = a;
	p->pnext = NULL;
	return p;

}
nodephieutra* newnodephieutra(phieutra a)
{
	nodephieutra *p = new nodephieutra;
	p->data = a;
	p->pnext = NULL;
	return p;

}
nodephieumuon* timtheomadocgia(listphieumuon p, char madocgia[])
{
	if (p.phead != NULL)

	{
		nodephieumuon *x = p.phead;
		for (; x != NULL; x = x->pnext)
		{
			if (_stricmp(x->data.madocgia, madocgia) == 0)
				return x;
		}
		return NULL;
	}
	else
	{
		printf("Chua co doc gia nao trong danh sach\n");

	}
}
void addphieumuon_file(listphieumuon &ph)
{
	create_head_tail_phieumuon(ph);

	FILE *p = fopen("Sl_phieumuon.txt", "r");
	fscanf(p, "%d", &ph.sl);
	fclose(p);
	FILE *f = fopen("Listphieumuon.bin", "r");
	if (f == NULL)
	{
		printf("Khong mo duoc file\n");
		exit(0);
	}
	phieumuon data;
	fread(&data, sizeof(phieumuon), 1, f);

	while (feof(f) == 0)
	{

		nodephieumuon *x = newnodephieumuon(data);
		if (ph.phead == NULL)
			ph.phead = ph.ptail = x;
		else
		{
			ph.ptail->pnext = x;
			ph.ptail = x;
		}
		fread(&data, sizeof(phieumuon), 1, f);
	}
	fclose(f);
}
void addphieutra_file(listphieutra &pt)
{
	create_head_tail_phieutra(pt);

	FILE *p = fopen("Sl_phieutra.txt", "r");
	fscanf(p, "%d", &pt.sl);
	fclose(p);
	FILE *f = fopen("Listphieutra.bin", "r");
	if (f == NULL)
	{
		printf("Khong mo duoc file\n");
		exit(0);
	}
	phieutra data;
	fread(&data, sizeof(phieutra), 1, f);

	while (feof(f) == 0)
	{

		nodephieutra *x = newnodephieutra(data);
		if (pt.phead == NULL)
			pt.phead = pt.ptail = x;
		else
		{
			pt.ptail->pnext = x;
			pt.ptail = x;
		}
		fread(&data, sizeof(phieutra), 1, f);


	}
	fclose(f);
}

static int ngaytrongthang[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int ktnamnhuan(int nam)
{
	if ((nam % 4 == 0 && nam % 100 != 0) || nam % 400 == 0)
		return 1;
	return 0;

}
int tinhkhoangcach_ngay_daunam(date a)
{
	int kc = 0;
	if (a.thang == 1)
		return a.ngay - 1;
	else
	{
		if (ktnamnhuan(a.nam) == 1)
			ngaytrongthang[2] = 29;
		for (int i = 1; i < a.thang; i++)
			kc = kc + ngaytrongthang[i];
		kc = kc + a.ngay - 2;
		return kc;

	}
}
int khoangcach2nam(int nam1, int nam2)
{
	int kc = 0;
	if (nam1 < nam2)
	{
		for (int i = nam1; i < nam2; i++)
			if (ktnamnhuan(i) == 1)
			{
				kc = kc + 366;
			}
			else
				kc = kc + 365;
	}
	else
	{
		if (nam2 > nam1)
		{
			for (int i = nam2; i < nam1; i++)
				if (ktnamnhuan(i) == 1)
				{
					kc = kc + 366;
				}
				else
					kc = kc + 365;
		}
		else
			if (nam1 = nam2)
				return 0;
	}
	return kc;
}
int tinhkhoangcach2ngay(date a, date b)
{
	int x = tinhkhoangcach_ngay_daunam(a);
	int y = tinhkhoangcach_ngay_daunam(b);
	int z = khoangcach2nam(a.nam, b.nam);
	return abs(x - y) + z;
}
void taophieumuonsach(listphieumuon &p, listdg a, listbook b)
{
	printf("Tao phieu muon sach\n");
	thongtinthedocgia *x = new thongtinthedocgia;
	x = timtheohoten(a);
	while (x == NULL)
	{
		printf("Khong tim thay ho ten\n");
		int n;
		printf("Nhan 1 de tao the doc gia va nhan 2 de nhap lai ho ten, nhan 3 de thoat\n");
		scanf("%d", &n);
		switch (n)
		{
		case 1: {
			adddocgia(a);
			printf("Nhap lai ho ten de tao phieu muon sach\n");
			x = timtheohoten(a);
			break;
		}

		case 2:
		{

			x = timtheohoten(a); break;
		}
		case 3:
			exit(0);
			break;
		}

	}
	nodephieumuon *h = new nodephieumuon;
	fflush(stdin);
	strcpy(h->data.madocgia, x->madocgia);
	printf("Nhap ngay muon\n");
	nhapngay(h->data.ngaymuon);
	printf("Nhap ngay tra du kien\n");
	nhapngay(h->data.ngaytradukien);
	fflush(stdin);
	printf("Nhap ten sach muon\n");
	nodebook *book = timtheotensach(b);//Ten sach la h->data.tensachmuon
	while (book == NULL)
	{
		printf("Khong tim thay sach\n");
		printf("Nhap lai ten sach\n");
		book = timtheotensach(b);
	}
	while (book->data.slcon == 0)
	{
		printf("Sach da het,xin muon sach khac\n");
		printf("Nhap lai ten sach\n");
		book = timtheotensach(b);
		while (book == NULL)
		{
			printf("Khong tim thay sach\n");
			printf("Nhap lai ten sach\n");
			book = timtheotensach(b);
		}
	}
	h->data.sachmuon = book->data;//Dua thong tin sach muon vao trong phieu muon sach

	printf("Nhap so sach muon\n");
	scanf("%d", &h->data.soluongmuon);
	while (h->data.soluongmuon > book->data.slcon)
	{
		printf("Nhap lai so sach muon\n");
		scanf("%d", &h->data.soluongmuon);
	}
	book->data.slcon = book->data.slcon - h->data.soluongmuon;//Muon  nen phai giam bot so luong quyen sach trong thu vien di 


	h->pnext = NULL;

	if (p.phead == NULL)
		p.phead = p.ptail = h;
	else
	{
		p.ptail->pnext = h;
		p.ptail = h;

	}

	p.sl++;
	FILE *f = fopen("Listphieumuon.bin", "a");
	fwrite(&h->data, sizeof(phieumuon), 1, f);
	fclose(f);
	FILE *f1 = fopen("Listsach.bin", "w");

	nodebook *recover = b.phead;
	for (; recover != NULL; recover = recover->pnext)
	{
		fwrite(&recover->data, sizeof(thongtinsach), 1, f1);

	}
	fclose(f1);
	addslphieumuon(p);

	delete[]recover;
	delete[]x;

	delete[]book;

}
void taophieutrasach(listphieutra &p2, listphieumuon muon, listbook &b)
{

	char *madocgia = new char[10];
	printf("Nhap ma doc gia\n");
	cin.ignore();
	gets_s(madocgia, 10);
	nodephieumuon*p = new nodephieumuon;
	p = timtheomadocgia(muon, madocgia);
	nodephieutra *h = new nodephieutra;
	h->data.ngaytradukien = p->data.ngaytradukien;
	strcpy(h->data.madocgia, p->data.madocgia);
	h->data.soluongmuon = p->data.soluongmuon;
	h->data.ngaymuon = p->data.ngaymuon;
	h->data.sachmuon = p->data.sachmuon;//Dua thong tin sach muon tu phieu muon vao phieu tra sach
	p2.sl++;
	printf("Ngay muon:");
	indate(h->data.ngaymuon);
	printf("Ngay tra du kien:");
	indate(h->data.ngaytradukien);
	printf("Ngay tra thuc te:\n");
	nhapngay(h->data.ngaytrathucte);

	printf("So ngay muon: %d\n", tinhkhoangcach2ngay(h->data.ngaymuon, h->data.ngaytrathucte));
	h->data.songaymuon = tinhkhoangcach2ngay(h->data.ngaymuon, h->data.ngaytrathucte);
	printf("Ban co mat sach khong? Nhan so tren ban phim de tra loi cau hoi:\n");
	printf("1.Mat sach\n");
	printf("2.Khong mat sach\n");
	scanf("%d", &h->data.matsach);
	nodebook *book = new nodebook;
	book = timtheotensach(b);
	if (book == NULL)
	{
		printf("Khong tim thay sach\n");
	}
	else
	{
		int x;
		if (h->data.matsach == 1)
		{
			printf("Ban mat bao nhieu quyen sach\n");
			scanf("%d", &x);
			printf("So quyen tra\n");
			scanf("%d", &h->data.soquyentra);
			while (x + h->data.soquyentra > h->data.soluongmuon)
			{
				printf("Nhap lai so luong sach mat\n");
				scanf("%d", &x);
			}
			h->data.soluongmuon = h->data.soluongmuon - x - h->data.soquyentra;
			book->data.soquyensach = book->data.soquyensach - x;
			book->data.slcon = book->data.slcon + h->data.soquyentra;
			h->data.tienphat = h->data.sachmuon.giasach*x * 2;
			printf("Ban phai tra 200 phan tram gia tien cua sach do lam mat sach, gia tien phat la :%d\n", h->data.tienphat);

			if (tinhkhoangcach2ngay(h->data.ngaymuon, h->data.ngaytrathucte) > 7)
			{
				printf("So quyen tra\n");
				scanf("%d", &h->data.soquyentra);

				printf("Ban da muon qua 7 ngay\n");
				h->data.tienphat = h->data.tienphat + (tinhkhoangcach2ngay(h->data.ngaymuon, h->data.ngaytrathucte) - 7) * 5000;
				printf("Ban bi phat 5000d moi ngay, tong cong la %d", (tinhkhoangcach2ngay(h->data.ngaymuon, h->data.ngaytrathucte) - 7) * 5000);
			}

			printf("Tong tien phat la =%d\n", h->data.tienphat);
		}
		else
		{
			h->data.tienphat = 0;
			printf("So quyen tra\n");
			scanf("%d", &h->data.soquyentra);
			h->data.soluongmuon = h->data.soluongmuon - h->data.soquyentra;
			if (tinhkhoangcach2ngay(h->data.ngaymuon, h->data.ngaytrathucte) > 7)
			{

				printf("Ban da muon qua 7 ngay\n");
				h->data.tienphat = h->data.tienphat + (tinhkhoangcach2ngay(h->data.ngaymuon, h->data.ngaytrathucte) - 7) * 5000;
				printf("Ban bi phat 5000d moi ngay, tong cong la %d", h->data.tienphat);
			}
			printf("Ten sach tra la %s\n", h->data.sachmuon.tensach);
			nodebook *book2 = timtheotensach(b);
			book2->data.slcon = book2->data.slcon + h->data.soquyentra;

			printf("Tong tien phat la =%d\n", h->data.tienphat);
		}
		h->pnext = NULL;
		if (p2.phead == NULL)
			p2.phead = p2.ptail = h;
		else
		{
			p2.ptail->pnext = h;
			p2.ptail = h;

		}

	}

	FILE *f = fopen("Listphieutra.bin", "a");
	fwrite(&h->data, sizeof(phieutra), 1, f);
	fclose(f);
	addslphieutra(p2);

	FILE *f1 = fopen("Listsach.bin", "w");

	nodebook *recover = b.phead;
	for (; recover != NULL; recover = recover->pnext)
	{
		fwrite(&recover->data, sizeof(thongtinsach), 1, f1);

	}
	fclose(f1);

	delete p;
	delete h;

}

void update_info(user *info_add, user_info *p)
{
	FILE *fp = fopen("user_info.bin", "a");
	while (getchar() != '\n');
	printf("Ho ten: \n");
	gets_s(p->name);
	fflush(stdin);
	printf("Ngay sinh: \n");
	gets_s(p->birth);
	fflush(stdin);
	printf("Dia chi(ghi theo dinh dang: (Ten duong/phuong/quan(huyen)/thanh pho): \n");
	gets_s(p->address);
	fflush(stdin);
	printf("So CMND: \n");
	gets_s(p->social_ID);
	fflush(stdin);
	printf("Gioi Tinh: \n");
	gets_s(p->sex);
	strcpy(p->stt, "active");
	printf("Cap nhat thong tin thanh cong!\n");
	fwrite(p, sizeof(user_info), 1, fp);
	info_add->ptr = ftell(fp);
	fclose(fp);
}
void print_info(user *p, user_info *info)
{
	FILE *f = fopen("user_info.bin", "rb");
	fseek(f, p->ptr - sizeof(user_info), SEEK_SET);
	fread(info, sizeof(user_info), 1, f);
	printf("\t\tTen: %16s\n", info->name);
	printf("\t\tNgay sinh: %16s\n", info->birth);
	printf("\t\tSo CMNN: %16s\n", info->address);
	printf("\t\tDia chi: %16s\n", info->social_ID);
	printf("\t\tGioi tinh: %16s\n", info->sex);
	printf("\t\tTrang thai: %16s\n", info->stt);
	fclose(f);
}
void phanquyen()
{
	user *p = new user;
	char uName[30];
	printf("Nhap ten nguoi muon phan quyen:\n");
	scanf("%s", &uName);
	FILE *f = fopen("user.bin", "rb");
	fseek(f, 0, SEEK_SET);
	int check = 0;
	while (!feof(f) && fread(p, sizeof(user), 1, f))
	{
		printf("%s\n", p->username);
		if (strcmp(p->username, uName) == 0)
		{
			check = 1;
			break;
		}
	}
	if (check == 0)
	{
		printf("Khong co nguoi dung nao ten %s,thu lai\n", uName);
		phanquyen();
	}
	if (check == 1)
	{
		char chucvu[20];
		printf("Nhap chuc vu(ChuyenVien|QuanLy): ");
		scanf("%s", &chucvu);
		printf("%s", chucvu);
		if (strcmp(chucvu, "ChuyenVien") == 0)
		{
			FILE *fcv = fopen("chuyenvien.bin", "a");
			fwrite(p->username, 10 * sizeof(char), 1, fcv);
			printf("Phan quyen thanh cong user: %s chuc vu Chuyen Vien\n", p->username);
		}
		if (strcmp(chucvu, "QuanLy") == 0)
		{
			FILE *fql = fopen("quanly.bin", "a");
			fwrite(p->username, 10* sizeof(char), 1, fql);
			printf("Phan quyen thanh cong user: %s chuc vu Quan Ly\n", p->username);
		}
	}
}
void reg(user *p, user_info *info)
{
	char pass[50];
	FILE *f = fopen("user.bin", "a");
	if (f == NULL)
	{
		printf("Open error!");
		return;
	}
	printf("Nhap username: \n");
	scanf("%s", p->username);
	printf("Nhap password: \n");
	scanf("%s", p->pwd);
	printf("Xac nhan password: \n");
	scanf("%s", &pass);
	if (strcmp(p->pwd, pass) == 0)
	{
		printf("Tao nguoi dung thanh cong!\n");
	}
	while (strcmp(p->pwd, pass) != 0)
	{
		printf("Password khong trung!, vui long thu lai.\n");
		printf("Nhap username: \n");
		scanf("%s", &p->username);
		printf("Nhap password: \n");
		scanf("%s", &p->pwd);
		printf("Xac nhan password: \n");
		scanf("%s", &pass);
	}

	printf("Vui long cap nhat thong tin ca nhan: \n");
	update_info(p, info);
	fwrite(p, sizeof(user), 1, f);
	info->ptruser = ftell(f);
	char c;
	printf("Ban co muon xem lai thong tin(Y|N): \n");
	scanf("%s", &c);
	if (c == 'Y')
	{
		print_info(p, info);

	}
	printf("quay lai va phan quyen cho nguoi dung vua tao \n");
	fclose(f);
}
bool login(user *p, int argc, char* argv[])
{
	FILE *f = fopen("user.bin", "rb");
	if (f == NULL)
	{
		printf("Da xay ra loi!");
		return false;
	}
	fseek(f, 0, SEEK_SET);
	while (!feof(f) && fread(p, sizeof(user), 1, f))
	{

		if (strcmp(p->username, argv[1]) == 0 && strcmp(p->pwd, argv[2]) == 0)
		{
			fclose(f);
			return true;
		}
	}
	fclose(f);
	return false;
}
void logout(user *p)
{
	printf("Da dang xuat\n");
	delete p;
}

void change_pass(user *p, user_info *info)
{
	FILE *f = fopen("user.bin", "wb");
	char pass_old[50];
	char pass_new[50];
	fseek(f, info->ptruser - sizeof(user), SEEK_SET);
	fread(p, sizeof(user), 1, f);
	printf("Nhap password cu\n");
	scanf("%s", &pass_old);
	if (strcmp(p->pwd, pass_old) == 0)
	{
		printf("Nhap password moi: \n");
		scanf("%s", &pass_new);
		strcpy(p->pwd, pass_new);
		fwrite(p, sizeof(user), 1, f);
		printf("Doi password thanh cong!");
	}
	else
	{
		printf("Password khong dung, vui long thu lai!\n");
		change_pass(p, info);
	}
	fclose(f);

}
void count_reader()
{
	int reader_count;
	FILE *f = fopen("Listdocgia.bin", "rb");
	fseek(f, 0, SEEK_END);
	int add = ftell(f) + 1;
	reader_count = add / sizeof(thongtinthedocgia);
	printf("Co %8d doc gia\n", reader_count);
	fclose(f);
}
void count_reader_sex()
{
	thongtinthedocgia *p = new thongtinthedocgia;
	int male = 0;
	int female = 0;
	FILE *f = fopen("Listdocgia.bin", "rb");
	if (f == NULL)
	{
		printf("Da xay ra loi!\n");
	}
	fseek(f, 0, SEEK_SET);
	while (!feof(f) && fread(p, sizeof(thongtinthedocgia), 1, f))
	{
		if (_stricmp(p->gioitinh, "Nam") == 0)
		{
			male++;
		}
		else if (_stricmp(p->gioitinh, "Nu") == 0)
			female++;
	}
	printf("Co %d Nam, %d Nu\n", male, female);
	fclose(f);
	delete p;
}
void Tim_Phan_Tu_Phan_Biet(char **str, char **s, int n, int &m)
{
	m = 0;
	s[m] = str[0]; // ph?n t? d?u tiên c?a m?ng a chính là ph?n t? phân bi?t
	m++; // s? lu?ng ph?n t? m?ng b tang lên 1 don v?

		 // vòng l?p duy?t t?ng ph?n t? c?a m?ng a
	for (int i = 1; i < n; i++)
	{
		// duy?t t?ng ph?n t? c?a m?ng a, duy?t t? v? trí i - 1 d?n 0
		// <=> duy?t t? v? trí i-1 v? d?u m?ng, d? tìm xem a[i] tru?c dó có t?n t?i hay chua
		// n?u a[i] mà duy?t v? tru?c dó mà chua có t?n t?i thì a[i] chính là ph?n t? phân bi?t
		bool Kiem_Tra = true; // gi? s? a[i] s? là ph?n t? phân bi?t
		for (int j = i - 1; j >= 0; j--)
		{
			// n?u a[i] b?ng a[j] <=> a[i] dã có t?n t?i tru?c dó 
			if (strcmp(str[i], str[j]) == 0)
			{
				Kiem_Tra = false; // c?p nh?t l?i a[i] không ph?i là ph?n t? phân bi?t
				break; // d?ng vi?c ki?m tra
			}
		}
		if (Kiem_Tra == true)
		{
			s[m] = str[i]; // dua ph?n t? phân bi?t vào m?ng b
			m++; // s? lu?ng ph?n t? m?ng b tang lên 1 don v?
		}
	}
}
void Xu_Li(char **str, char **s, int n, int &m)
{
	// BU?C 1: ÐI TÌM PH?N T? PHÂN BI?T
	Tim_Phan_Tu_Phan_Biet(str, s, n, m);

	// BU?C 2: ÐI TÌM S? L?N XU?T HI?N C?A T?NG PH?N T? PHÂN BI?T TRONG M?NG A
	// vòng l?p l?y t?ng ph?n t? c?a m?ng b- m?ng ch?a ph?n t? phân bi?t
	// d? duy?t v?i toàn b? m?ng a <=> duy?t v?i vòng l?p for bên trong
	for (int i = 0; i < m; i++)
	{
		int dem = 0;
		// duy?t t?ng ph?n t? c?a m?ng b v?i toàn b? m?ng a d? tìm s? l?n xu?t hi?n
		for (int j = 0; j < n; j++)
		{
			if (s[i] == str[j])
			{
				dem++; // s? l?n xu?t hi?n c?a ph?n t? b[i] tang lên 1 
			}
		}
		cout << "\nco " << dem << " sach the loai " << str[i];;
	}
}
void count_cate()
{

	thongtinsach *book = new thongtinsach;
	FILE *f = fopen("Listsach.bin", "rb");
	fseek(f, 0, SEEK_END);
	int n = (ftell(f) + 1) / sizeof(thongtinsach);
	int m;
	char **str = new char*[n];
	for (int j = 0; j < n; j++)
	{
		str[j] = new char[30];
	}
	char **s = new char*[n];
	for (int j = 0; j < n; j++)
	{
		s[j] = new char[30];
	}
	int i = 0;
	rewind(f);
	while (!feof(f) && fread(book, sizeof(thongtinsach), 1, f) && i<n)
	{
		strcpy(str[i], book->theloai);
		i++;
	}
	Xu_Li(str, s, n, m);

	for (int t = 0; t<n; t++)
	{
		delete[] str[t];
	}
	delete[] str;

}
void book_being_lended()
{
	FILE *f = fopen("Listsach.bin", "rb");
	thongtinsach *b = new thongtinsach;
	while (!feof(f) && fread(b, sizeof(thongtinsach), 1, f))
	{
		printf("\nSach %16s dang duoc muon %8d quyen", b->tensach, b->soquyensach - b->slcon);
	}
	delete b;
	fclose(f);
}
void return_late()
{
	listphieutra t;
	listphieumuon p;
	addphieumuon_file(p);
	addphieutra_file(t);
	nodephieumuon *p1 = p.phead;
	nodephieutra *t1 = t.phead;
	date now;
	nhapngay(now);
	int m = 0;
	for (; p1 != NULL; p1 = p1->pnext)
	{
		int check = 0;
		for (t1 = t.phead; t1 != NULL; t1 = t1->pnext)
		{
			if ((strcmp(p1->data.madocgia, t1->data.madocgia) == 0) && tinhkhoangcach2ngay(p1->data.ngaymuon, t1->data.ngaymuon) == 0 && strcmp(t1->data.sachmuon.tensach, p1->data.sachmuon.tensach) == 0)
			{
				if (tinhkhoangcach2ngay(t1->data.ngaymuon, t1->data.ngaytrathucte) > 7)
				{
					printf("Doc gia co ma %s tra sach %s tre %d ngay\n", t1->data.madocgia, t1->data.sachmuon.tensach, (tinhkhoangcach2ngay(p1->data.ngaymuon, t1->data.ngaytrathucte) - 7));
					check = 1;
				}

			}

		}
		if (check == 0)
		{
			if (tinhkhoangcach2ngay(now, p1->data.ngaymuon) > 7)
			{
				printf("Nhap ngay muon kiem tra\n");
				printf("Doc gia co ma %s tra sach %s tre %d ngay so voi ngay da nhap\n", p1->data.madocgia, p1->data.sachmuon.tensach, (tinhkhoangcach2ngay(now, p1->data.ngaymuon) - 7));
				check = 1;
				m = check;
			}
		}
		
	}
	if (m == 0)
	{
		printf("Khong co doc gia nao tra muon");
	}

}


int thongkesoluongsach(listbook b)
{
	nodebook *tong = b.phead;
	int dem = 0;
	for (; tong != NULL; tong = tong->pnext)
		dem = dem + tong->data.soquyensach;
	return dem;
}
int thongkesoluongsachcon(listbook b)
{
	nodebook *con = b.phead;
	int dem = 0;
	for (; con != NULL; con = con->pnext)
		dem = dem + con->data.slcon;
	return dem;
}
void thongke_tongsach_sachcon(listbook b)
{
	printf("So luong sach trong thu vien la %8d\n", thongkesoluongsach(b));
	printf("So luong sach con trong thu vien la %8d\n", thongkesoluongsachcon(b));

}
int main(int argc, char *argv[])
{
	
	user *p = new user;
	user_info *info = new user_info;
	thongtinthedocgia *r = new thongtinthedocgia;
	if (login(p, argc, argv) == true)
	{
		printf("Dang nhap thanh cong\n");
		char ten[15];
		int check = 0;
		FILE *fcv = fopen("chuyenvien.bin", "rb");
		fseek(fcv, 0, SEEK_SET);
		while (!feof(fcv) && fread(&ten, 10 * sizeof(char), 1, fcv))
		{
			if (strcmp(p->username, ten) == 0)
			{
				check = 1;
				break;
			}
		}
		if (check == 1)
		{
		ChuyenVien:
			int a100;
			printf("1.Dang Xuat\n");
			printf("2.Doi mat khau\n");
			printf("3.Cap nhat thong tin ca nhan\n");
			printf("4.Tao nguoi dung\n");
			printf("5.Them doc gia\n");
			printf("6.Chinh sua thong tin doc gia\n");
			printf("7.Tim kiem doc gia theo CMND\n");
			printf("8.Xem danh sach doc gia\n");
			printf("9.Tim sach theo ma sach\n");
			printf("10.Tim sach theo ten sach\n");
			printf("11.Thong ke sach duoc muon\n");
			printf("12.Thong ke so doc gia tra muon\n");
			scanf("%d", &a100);
			listdg a;
			FILE *f = fopen("Listdocgia.bin", "r");

			if (f == NULL)
			{
				create_head_tail_sl_dg(a);

			}
			else
			{
				adddocgia_file(a);

			}
			listbook b;
			FILE *f1 = fopen("Listsach.bin", "r");
			if (f1 == NULL)
			{
				create_head_tail_sl_book(b);

			}
			else
			{
				addbook_file(b);

			}
			switch (a100)
			{
			case 1:
			{

				logout(p);
				break;
			}
			case 2:
			{

				change_pass(p, info);
				break;
			}
			case 3:
			{

				update_info(p, info);
				break;
			}
			case 4:
			{

				reg(p, info);
				break;
			}
			//thêm d?c gi?
			case 5:
			{

				adddocgia(a);
				break;
			}
			//chinh sua thong tin doc gia

			case 6:
			{

				suathongtindocgia(a);
				break;
			}
			//tim kiem doc gia theo CMND
			case 7:
			{
				char *str = new char[15];
				printf("Nhap chung minh nhan dan cua doc gia can tim\n");
				gets_s(str, 15);
				nodedocgia* x = new nodedocgia;
				x = timdocgiatheocmnd(a, str);
				printf("Ho va ten : %s %s\n", x->data.ho_tendem, x->data.ten);
				printf("Gioi tinh : %s\n", x->data.gioitinh);
				delete[]str;
				break;
			}
			//xem danh sach doc gia
			case 8:
			{
				indanhsachdocgia();
				break;
			}
			//tim kiem theo ma sach
			case 9:
			{
				char *str1 = new char[15];
				printf("Nhap ma sach cua sach can tim\n");
				gets_s(str1, 15);

				nodebook*y = timtheoIBSN(b, str1);
				printf("Ten sach : %s\n", y->data.tensach);
				printf("Tac gia : %s\n", y->data.tacgia);
				printf("Gia sach : %d\n", y->data.giasach);

				delete[]str1;
				break;

			}
			//tim theo ten sach

			//tim kiem theo ten sach
			case 10:
			{
				char *str2 = new char[15];
				printf("Nhap ma sach can tim\n");
				gets_s(str2, 15);

				nodebook*y2 = timtheoIBSN(b, str2);
				printf("Ten sach : %s\n", y2->data.tensach);
				printf("Tac gia : %s\n", y2->data.tacgia);
				printf("Gia sach : %d\n", y2->data.giasach);
				delete[]str2;
				break;
			}
			//thong ke sach duoc muon
			case 11:
			{
				book_being_lended();
				break;
			}
			//thong ke so doc gia tra muon 
			case 12:
			{
				return_late();
				break;

			}

			default:
			{
				break;
			}

			}
			if (a100 != 1)
			{
				printf("\n\n\n");
				goto ChuyenVien;
			}
			fclose(f);
			fclose(f1);
		}
		if (check == 0)
		{
			FILE *fql = fopen("quanly.bin", "rb");
			fseek(fql, 0, SEEK_SET);
			while (!feof(fql) && fread(&ten, 10 * sizeof(char), 1, fql))
			{
				if (strcmp(p->username, ten) == 0)
				{
					check = 2;
					break;
				}
			}
		}
		if (check == 2)
		{
		QuanLy:
			int a;
			printf("1.Dang Xuat\n");
			printf("2.Doi mat khau\n");
			printf("3.Cap nhat thong tin ca nhan\n");
			printf("4.Tao nguoi dung\n");

			scanf("%d", &a);
			switch (a)
			{
			case 1:
			{

				logout(p);
				break;
			}
			case 2:
			{

				change_pass(p, info);
				break;
			}
			case 3:
			{

				update_info(p, info);
				break;
			}
			default:
			{

				break;
			}
			}
			if (a != 1)
			{
				printf("\n\n\n");
				goto QuanLy;
			}

		}
		if (check == 0)
		{
		Admin:
			int a100;
			printf("1.Dang Xuat\n");
			printf("2.Doi mat khau\n");
			printf("3.Cap nhat thong tin ca nhan\n");
			printf("4.Tao nguoi dung\n");
			printf("5.Phan quyen\n");
			printf("6.Thong ke so luong sach theo the loai\n");
			printf("7.Thong ke so luong doc gia\n");
			printf("8.Thong ke so luong doc gia theo gioi tinh\n");
			printf("9.Thong ke so sach dang duoc muon\n");
			printf("10.Them doc gia\n");
			printf("11.Chinh sua thong tin doc gia\n");
			printf("12.Tim kiem doc gia theo CMND\n");
			printf("13.Xem danh sach doc gia\n");
			printf("14.Tim sach theo ten sach\n");
			printf("15.Tim sach theo ma sach\n");
			printf("16.Thong ke so doc gia tra sach muon\n");
			printf("17.Xoa thong tin 1 doc gia\n");
			printf("18.Xem danh sach sach trong thu vien\n");

			printf("19.Them sach\n");
			printf("20.Chinh sua thong tin sach\n");
			printf("21.Xoa thong tin sach\n");
			printf("22.Lap phieu muon sach\n");
			printf("23.Lap phieu tra sach\n");
			printf("24.Thong ke so luong sach trong thu vien\n");



			scanf("%d", &a100);
			listphieutra t;
			FILE *f11 = fopen("Listphieutra.bin", "r");

			if (f11 == NULL)
			{
				create_head_tail_phieutra(t);

			}
			else
			{
				addphieutra_file(t);

			}
			listphieumuon p10;
			FILE *f10 = fopen("Listphieumuon.bin", "r");

			if (f10 == NULL)
			{
				create_head_tail_phieumuon(p10);

			}
			else
			{
				addphieumuon_file(p10);

			}

			listdg a;
			FILE *f = fopen("Listdocgia.bin", "r");

			if (f == NULL)
			{
				create_head_tail_sl_dg(a);

			}
			else
			{
				adddocgia_file(a);

			}
			listbook b;
			FILE *f1 = fopen("Listsach.bin", "r");
			if (f1 == NULL)
			{
				create_head_tail_sl_book(b);

			}
			else
			{
				addbook_file(b);

			}
			switch (a100)
			{
			case 1:
			{
				logout(p);
				break;
			}
			case 2:
			{

				change_pass(p, info);
				break;
			}
			case 3:
			{

				update_info(p, info);
				break;
			}
			case 4:
			{

				reg(p, info);
				break;
			}
			case 5:
			{

				phanquyen();
				break;
			}
			case 6:
			{

				count_cate();
				break;
			}
			case 7:
			{

				count_reader();
				break;
			}
			case 8:
			{

				count_reader_sex();
				break;
			}
			case 9:
			{

				book_being_lended();
				break;
			}
			//them doc gia
			case 10:
			{
				adddocgia(a);

				break;
			}
			//chinh sua thong tin doc gia

			case 11:
			{
				suathongtindocgia(a);

				break;
			}
			//tìm kiem doc gia theo cmnn

			case 12:
			{
				char str3[15];
				printf("Nhap chung minh nhan dan cua doc gia can tim\n");
				scanf("%s", &str3);
				nodedocgia* x2 = new nodedocgia;
				x2 = timdocgiatheocmnd(a, str3);
				if (x2 == NULL)
					printf("khong tim thay doc gia nao\n");
				else
				{
					printf("Ho va ten : %s %s\n", x2->data.ho_tendem, x2->data.ten);
					printf("Gioi tinh : %s\n", x2->data.gioitinh);
				}
				delete[]x2;
				break;

			}
			//xem danh sach doc gia

			case 13:
			{
				indanhsachdocgia();

				break;

			}
			//tìm sách theo ten sach

			case 14:
			{


				nodebook *y4 = new nodebook;
				y4 = timtheotensach(b);
				if (y4 == NULL)
				{
					printf("Khong tim thay sach\n");
				}
				else
				{
					printf("Ten sach : %s\n", y4->data.tensach);
					printf("Tac gia : %s\n", y4->data.tacgia);
					printf("Gia sach : %d\n", y4->data.giasach);
				}
				delete y4;
				break;

			}
			//tìm kiem sach theo ma sach

			case 15:
			{
				char *str4 = new char[15];
				printf("Nhap ma sach cua sach can tim\n");
				cin.ignore();
				gets_s(str4, 15);

				nodebook*y3 = new nodebook;
				y3 = timtheoIBSN(b, str4);
				if (y3 == NULL)
				{
					printf("Khong tim thay sach\n");
				}
				else
				{
					printf("Ten sach : %s\n", y3->data.tensach);
					printf("Tac gia : %s\n", y3->data.tacgia);
					printf("Gia sach : %d\n", y3->data.giasach);
				}
				delete[]str4;
				delete[]y3;
				break;

			}

			//thong ke so doc gia tra sach muon
			case 16:
			{
				return_late();
				break;

			}
			//xoá thông tin 1 doc gia

			case 17:
			{
				xoathongtindocgia(a);
				break;

			}
			//Xem danh sách các sách trong thu vien

			case 18:
			{
				indssach2();
				break;

			}
			//Thêm sách

			case 19:
			{
				addbook(b);
				break;

			}
			//Chinh sua thong tin mot quyen sach

			case 20:
			{
				suathongtinsach(b);
				break;

			}
			//Xóa thông tin sách

			case 21:
			{
				xoathongtinsach(b);
				break;

			}
			//Lap phieu muon sach

			case 22:
			{
				taophieumuonsach(p10, a, b);
				break;
			}
			//Lap phieu tra sach

			case 23:
			{
				taophieutrasach(t, p10, b);

				break;

			}
			//Thong ke so luong sach trong thu vien
			case 24:
			{
				thongke_tongsach_sachcon(b);
				break;

			}
			default:
			{
				printf("Nhap loi\n");
				break;
			}
			}
			if (a100 != 1)
			{
				printf("\n\n\n");
				goto Admin;
			}
			fclose(f11);
			fclose(f10);
			fclose(f);
			fclose(f1);





		}
	}

	else
	{
		printf("Dang nhap khong thanh cong. Enter de thu lai\n");
	}
	
	_getch();
	return 0;
}


