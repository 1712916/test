#include<stdio.h>
#include<conio.h>
#include <fcntl.h> //_O_U16TEXT
#include <io.h>    //_setmode()
#include <string.h>
#include<malloc.h>
#include<wchar.h>
#pragma warning (disable: 4996)
#include <stdlib.h>

struct SinhVien
{
	wchar_t	MSSV[10];
	wchar_t HoVaTen[30];
	wchar_t Khoa[30];
	int		Khoa_s;
	wchar_t	NgaySinh[11];
	wchar_t AnhCaNhan[30];
	wchar_t Email[50];
	wchar_t MoTa[1000];
	wchar_t SoThich[500];

};
wchar_t** gantungdong(FILE *fp,int &n)
{
	n=0;
	wchar_t **a = (wchar_t**)malloc(sizeof(wchar_t*));
	while(!feof(fp))
	{
		a[n]=(wchar_t*)malloc(1700*sizeof(wchar_t));
		fgetws(a[n],1700,fp);
		if(!feof(fp))
		{
			n++;
			a=(wchar_t**)realloc(a,(n+1)*sizeof(wchar_t*));
		}
	}
	
	return a;
}
void huychuoi(wchar_t **b, int n)
{
	for(int i=0;i<n;i++)
	{
		free(b[i]);
	}
	free(b);
}
wchar_t* chen(wchar_t** a,int diachi)
{	
	wchar_t* gan = (wchar_t*)malloc(255 * sizeof(wchar_t));
	wcscpy(gan, a[diachi]);
	wcscpy(a[diachi] + 1, gan);
	a[diachi][0] = L'\"';
	wcscpy(a[diachi] + wcslen(a[diachi]), L"\"");
	free(gan);
	return a[diachi];
}
wchar_t* truonghopdacbiet(wchar_t**b, int diachi, int n)
{	
	int x = diachi + 1;
	do
	{	if(x==n)
		{
			return b[diachi];
		}
		if(wcscmp(b[x], L",") == 0)
		{
			return b[diachi];
		}
		if(b[x-1][wcslen(b[x-1])-1]==L' '|| wcscmp(b[x-1],L" ")==0)
		{
			b[x]=chen(b,x);
		}
		wcscpy(b[diachi] + wcslen(b[diachi]), b[x]);
		x++;
		if(x==n)
		{
			return b[diachi];
		}
	} while (wcscmp(b[x], L",") != 0);
	return b[diachi];

}
SinhVien* laythongtin(wchar_t a[])
{
        int i=0;
        wchar_t **b = (wchar_t **)malloc(sizeof(wchar_t*));
        wchar_t *p;
        p = wcstok(a,L"\"" ); 
		//
        while(p != NULL)
        {		
				b[i]=(wchar_t *)malloc(1000*sizeof(wchar_t));
				wcscpy(b[i],p);
				p = wcstok(NULL,L"\""); 
				if(p!=NULL)
				{	
					i++;
					b=(wchar_t**)realloc(b,(i+1)*sizeof(wchar_t*));
				}
        }
		SinhVien* 	A = (SinhVien*)malloc(sizeof(SinhVien));
		wcscpy(A->MSSV,b[0]);
		wcscpy(A->HoVaTen,b[2]);
		wcscpy(A->Khoa,b[4]);
		A->Khoa_s=_wtoi(b[6]);
		wcscpy(A->NgaySinh,b[8]);
		wcscpy(A->AnhCaNhan,b[10]);
		wcscpy(A->Email,b[12]);
		int endmota_startsothich;
		int index=14;
		while(1)
		{
			if(wcscmp(b[index],L",")==0)
			{
				endmota_startsothich=index+1;
				break;
			}
			index++;
		}
		wcscpy(A->MoTa,truonghopdacbiet(b,14,i));
		wcscpy(A->SoThich,truonghopdacbiet(b ,endmota_startsothich,i));
		huychuoi(b,i);
        return A;
}
void infile(wchar_t a[])
{	
		SinhVien* A=laythongtin(a);
		wchar_t filename[50];
		wcscpy(filename,A->MSSV);
		wcscat(filename,L".html");
		FILE* fo=_wfopen(filename,L"wt,ccs=UTF-8");
		fwprintf(fo,L"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n");
		fwprintf(fo,L"<html xmlns=\"http://www.w3.org/1999/xhtml\">\n");
		fwprintf(fo,L"	<head>\n");
		fwprintf(fo,L"		<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n");
		fwprintf(fo,L"		<link rel=\"stylesheet\" type=\"text/css\" href=\"personal.css\" />\n");
		fwprintf(fo,L"		<title>HCMUS - %ls</title>\n",A->HoVaTen);
		fwprintf(fo,L"	</head>\n");
		fwprintf(fo,L"	<body>\n");
		fwprintf(fo,L"		<div class=\"Layout_container\">\n");
		fwprintf(fo,L"			<!-- Begin Layout Banner Region -->\n");
		fwprintf(fo,L"			<div class=\"Layout_Banner\" >\n");
		fwprintf(fo,L"				<div><img id=\"logo\" src=\"Images/logo.jpg\" height=\"105\" /></div>\n"); 
		fwprintf(fo,L"				<div class=\"Header_Title\">TRƯỜNG ĐẠI HỌC KHOA HỌC TỰ NHIÊN </div>\n");
		fwprintf(fo,L"			</div>\n");
		fwprintf(fo,L"			<!-- End Layout Banner Region -->\n");
		fwprintf(fo,L"			<!-- Begin Layout MainContents Region -->\n");
		fwprintf(fo,L"			<div class=\"Layout_MainContents\">\n");
		fwprintf(fo,L"				<!-- Begin Below Banner Region -->\n");
		fwprintf(fo,L"				<div class=\"Personal_Main_Information\">\n");
		fwprintf(fo,L"					<!-- Begin Thông tin cá nhân  ----------------------------------------------------------------------------------------- -->\n");
		fwprintf(fo,L"					<div class=\"Personal_Location\">\n");
		fwprintf(fo,L"						<img src=\"Images/LogoFooter.jpg\" width=\"27\" height=\"33\" />\n"); 
		fwprintf(fo,L"						<span class=\"Personal_FullName\">%ls - %ls</span>\n",A->HoVaTen, A->MSSV);
		fwprintf(fo,L"						<div class=\"Personal_Department\">%ls</div>\n",A->Khoa);
		fwprintf(fo,L"						<br />\n");
		fwprintf(fo,L"						<div class=\"Personal_Phone\">\n"); 
 		fwprintf(fo,L"							Email: %ls\n",A->Email); 
		fwprintf(fo,L"						</div>\n");
		fwprintf(fo,L"						<br />\n");
		fwprintf(fo,L"						<br />\n");
		fwprintf(fo,L"					</div>\n");
		fwprintf(fo,L"					<!-- End Thông tin cá nhân ----------------------------------------------------------------------------------------- -->\n");
		fwprintf(fo,L"					<div class=\"Personal_HinhcanhanKhung\">\n");
		fwprintf(fo,L"						<img src=\"Images/%ls\" class=\"Personal_Hinhcanhan\" />\n",A->AnhCaNhan);
		fwprintf(fo,L"					</div>\n");
		fwprintf(fo,L"				</div>\n");
		fwprintf(fo,L"				<!-- End Below Banner Region -->\n");
		fwprintf(fo,L"				<!-- Begin MainContents Region -->\n");
		fwprintf(fo,L"				<div class=\"MainContain\">\n");
		fwprintf(fo,L"\n");
		fwprintf(fo,L"					<!-- Begin Top Region -->\n");
		fwprintf(fo,L"\n");
		fwprintf(fo,L"					<div class=\"MainContain_Top\">\n");
		fwprintf(fo,L"\n");
		fwprintf(fo,L"						<div class=\"InfoGroup\">Thông tin cá nhân</div>\n");
		fwprintf(fo,L"                        <div>\n");
		fwprintf(fo,L"                            <ul class=\"TextInList\">\n");
		fwprintf(fo,L"                                <li>Họ và tên: %ls</li>\n",A->HoVaTen);
		fwprintf(fo,L"								  <li>MSSV: %ls</li>\n",A->MSSV);
		fwprintf(fo,L"								  <li>Sinh viên khoa: %ls</li>\n",A->Khoa);
		fwprintf(fo,L"								  <li>Ngày sinh: %ls</li>\n",A->NgaySinh);
		fwprintf(fo,L"								  <li>Email: %ls</li>\n",A->Email);
		fwprintf(fo,L"							  </ul>\n");
		fwprintf(fo,L"						</div>\n");
		fwprintf(fo,L"                        <div class=\"InfoGroup\">Sở thích</div>\n");
		fwprintf(fo,L"                        <div>\n");
		fwprintf(fo,L"                            <ul class=\"TextInList\">\n");
		fwprintf(fo,L"                                <li>%ls</li>\n",A->SoThich);
		fwprintf(fo,L"							</ul>\n");
		fwprintf(fo,L"						</div>\n");
		fwprintf(fo,L"						<div class=\"InfoGroup\">Mô tả</div>\n");
		fwprintf(fo,L"						<div class=\"Description\">\n");
		fwprintf(fo,L"                            %ls\n",A->MoTa);
		fwprintf(fo,L"						</div>\n");
		fwprintf(fo,L"\n");
		fwprintf(fo,L"					</div>\n");
		fwprintf(fo,L"				</div>\n");
		fwprintf(fo,L"			</div>\n");
		fwprintf(fo,L"\n");
		fwprintf(fo,L"\n");
		fwprintf(fo,L"			<!-- Begin Layout Footer -->\n");
		fwprintf(fo,L"			<div class=\"Layout_Footer\">\n");
		fwprintf(fo,L"				<div class=\"divCopyright\">\n");
		fwprintf(fo,L"					<br />\n");
		fwprintf(fo,L"					<img src=\"Images/LogoFooter_gray.jpg\" width=\"34\" height=\"41\" /><br />\n");
		fwprintf(fo,L"					<br />\n");
		fwprintf(fo,L"					@%d</br>\n",A->Khoa_s);
		fwprintf(fo,L"					Đồ án giữa kỳ</br>\n");
		fwprintf(fo,L"				Kĩ thuật lập trình</br>\n");
		fwprintf(fo,L"				TH2018/04</br>\n");
		fwprintf(fo,L"				1712916 - Ngô Tấn Vịnh</br>\n");
		fwprintf(fo,L"				</div>\n");
		fwprintf(fo,L"			</div>\n");
		fwprintf(fo,L"			<!-- End Layout Footer -->\n");
		fwprintf(fo,L"		</div>\n");
		fwprintf(fo,L"	</body>\n");
		fwprintf(fo,L"</html>\n");
		fclose(fo);
		free(A);

}
void main()
{		
	//--------------------------------
	_setmode(_fileno(stdout), _O_U16TEXT); //needed for output
    _setmode(_fileno(stdin), _O_U16TEXT); //needed for input
	//----------------
	
	wchar_t** a;
	wchar_t filenameinput[50]=L"tep";
	wcscat(filenameinput,L".csv");
	SinhVien *A;
	int n;	
	//----------------
	FILE* fp=_wfopen(filenameinput,L"r,ccs=UTF-8"); // mở tệp
	//----------------
	 
	//----------------
	a=gantungdong(fp,n); wprintf(L"Tổng số sinh viên có trong tệp hiện tại là:%d\n",n);
	A=(SinhVien*)malloc(n*sizeof(SinhVien));
	for(int i=0;i<n;i++)
	{	
		infile(a[i]);
	}
	//~~~~~~~~~~~~~~~~
	wprintf(L"Đọc xong file!\nĐã ghi thông tin lên file html!!!!\n");
	//
	getch();
	huychuoi(a,n);; // đã free a
	fclose(fp);
}

