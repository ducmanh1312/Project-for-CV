#include <iostream>
// IN:
// OUT:
#include <cmath>
#define FOR(i, start, end) for (int i = start; i <= end; i++)

using namespace std;

typedef struct SinhVien
{
    char ten[30];
    int age;
    float dtb = 0;
} SV;

void nhap(SV &sv);
void nhapN(SV a[], int n);
void xuat(SV sv);
void xuatN(SV a[], int n);
void tinhDTB(SV &sv);
void sapxep(SV a[], int n);
void xeploai(SV a);
void xeploaiN(SV a[], int n);
void xuatFile(SV a[], int n, char fileName[]);

int main()
{
    int key;
    bool DaNhap = false;
    char fileName[] = "DSSV.txt";
    int n;
    while (true)
    {
        system("cls");
        printf("******************************************\n");
        printf("**    CHUONG TRINH QUAN LY SINH VIEN    **\n");
        printf("**      1. Nhap du lieu                 **\n");
        printf("**      2. In danh sach sinh vien       **\n");
        printf("**      3. Sap xep sinh vien theo DTB   **\n");
        printf("**      4. Xep loai sinh vien           **\n");
        printf("**      5. Xuat DS sinh vien            **\n");
        printf("**      0. Thoat                        **\n");
        printf("******************************************\n");
        printf("**       Nhap lua chon cua ban          **\n");
        cin >> key;
    }
    switch (key)
    {
    case 1:
        printf("\nBan da chon nhap DS sinh vien!");
        

        break;

    default:
        break;
    }
}

void nhap(SV &sv)
{
    cout << "\nNhap ten: ";
    fflush(stdin);
    getline(cin, sv.ten);
    cout << "\nNhap tuoi: ";
    cin >> sv.age;
}

/*

*/