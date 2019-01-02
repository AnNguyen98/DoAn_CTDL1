#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

const int MAX_SIZE = 1000;
static int sizeHoaDon;
enum DonGia{
    A   = 400,
    B   = 300,
    K   = 250,
    N   = 0,
};
struct Date{
    int day, month, year;
};
struct HoaDonKhachHang{
    string  maHoaDon, tenKhachHang, soCMND;
    bool    gioiTinh;
    string  soPhong;
    char    loaiPhong;
    DonGia  donGia;
    Date    ngayDen, ngayDi;
    int     soNgayOKH   ;
    long    tienPhong ;
};
bool namNhuan(int year);
int  dayOfMonths(int month, int year);
int  soNgayO(Date ngayDen, Date ngayDi);
void nhapDate(Date &date);
void nhapHoaDon(HoaDonKhachHang &);
void menu(HoaDonKhachHang *arrHoaDon);
void aqualNull(HoaDonKhachHang &hoaDon);
void readData(const string path, HoaDonKhachHang *arrHoaDon);
void deleteMinh(HoaDonKhachHang *list);
void insertHoaDon(HoaDonKhachHang *list);
void bubbleSort(HoaDonKhachHang *list);
Date convertDate(string a);
HoaDonKhachHang convertHoaDon(string a);
void writeData(const string path, HoaDonKhachHang *arrHoaDon);
void showArrHoaDon(HoaDonKhachHang *arrHoaDon);
int  getSize(string);
void swap(HoaDonKhachHang &hoaDon1, HoaDonKhachHang &hoaDon2);
int findIndex(HoaDonKhachHang *list,HoaDonKhachHang newHoaDon);
string lastName(string name);
void showDoanhThu(HoaDonKhachHang *arrHoaDon);
void searchAndShow(HoaDonKhachHang *arrHoaDon);
bool containString(string lastName1, string name2);
string convertMoney(long money);

int main(){
    string path = "/Users/macbook/CLionProjects/DoAn_CTDL/data.txt";
    sizeHoaDon = getSize(path);
    HoaDonKhachHang *arrHoaDon = new HoaDonKhachHang[MAX_SIZE];
    readData(path,arrHoaDon);
    menu(arrHoaDon);
    return 0;
}
void menu(HoaDonKhachHang *arrHoaDon){
    int index;
    do {
        cout << "\n\n-----------------------------------------------MENU------------------------------------------\n";
        cout << "1 . In danh sách các thông tin của tất cả các đối tượng (có bổ sung cột số thứ tự) ." << endl;
        cout << "2 . Chèn mẫu tin sao cho mảng vẫn được sắp theo thứ tự." << endl;
        cout << "3 . Xoa cac hoa don co khach hang ten Minh ." << endl;
        cout << "4 . Tìm kiếm mẫu tin theo các tiêu chí (tên, giới tính, loại phòng)." << endl;
        cout << "5 . Sắp xếp Theo thứ tự tăng dần/ giảm dần." << endl;
        cout << "6 . In ra bảng thống kê theo loại phòng  gồm các cột: loại phòng, tổng tiền." << endl;
        cout << "0 . Exit ." << endl;
        cout << "---------------------------------------------------------------------------------------------\n";

        do {
            cout << "\nNhap lua chon cua ban: ";
            cin >> index;
            if (index < 0 || index >6){
                cout << "\nBan da nhap sai moi ban nhap lai: ";
            }

        } while (index < 0 || index >6);
        switch(index){
            case 0:
                cout << "Da luu data!!\n";
                writeData("/Users/macbook/CLionProjects/DoAn_CTDL/data.txt",arrHoaDon);
                delete[] arrHoaDon;
                cout << "0 . Exit.\n" << endl;
                exit(0);
                break;
            case 1:
                cout << "1 . In danh sách các thông tin của tất cả các đối tượng (có bổ sung cột số thứ tự) .\n" << endl;
                showArrHoaDon(arrHoaDon);
                break;
            case 2:
                cout << "2 . Chèn mẫu tin sao cho mảng vẫn được sắp theo thứ tự.\n" << endl;
                insertHoaDon(arrHoaDon);
                break;
            case 3:
                cout << "3 . Xoa cac hoa don co khach hang ten Minh .\n" << endl;
                deleteMinh(arrHoaDon);
                break;
            case 4:
                cout << "4 . Tìm kiếm mẫu tin theo các tiêu chí (tên, giới tính, loại phòng).\n" << endl;
                searchAndShow(arrHoaDon);
                break;
            case 5:
                cout << "5 . Sắp xếp Theo thứ tự tăng dần." << endl;
                bubbleSort(arrHoaDon);
                showArrHoaDon(arrHoaDon);
                break;
            case 6:
                cout << "6 . In ra bảng thống kê theo loại phòng  gồm các cột: loại phòng, tổng tiền.\n" << endl;
                showDoanhThu(arrHoaDon);
                break;
        }
    }while(index != 0);
}
void showSearch(HoaDonKhachHang hoaDon, int i){
    int index = (i + 1 < 10 ) ? 14:13;
    cout << " "<< i + 1 << setw(index) ;
    cout << hoaDon.maHoaDon << setw(8 + hoaDon.tenKhachHang.size());
    string gioiTinh = (hoaDon.gioiTinh) ? "Nam" : "Nu";
    cout << hoaDon.tenKhachHang << setw(30 - hoaDon.tenKhachHang.size() - hoaDon.soCMND.size());
    cout << gioiTinh << setw(14);
    cout << hoaDon.soPhong << setw(14) << hoaDon.soNgayOKH << setw(16) << convertMoney(hoaDon.tienPhong) << "  (VND)" << endl;
}
void searchAndShow(HoaDonKhachHang *arrHoaDon){
    readData("/Users/macbook/CLionProjects/DoAn_CTDL/data.txt",arrHoaDon);
    int index, dem = 0;
    cout << "Ban muon tim kiem theo thuoc tinh: 1 - Ten khach hang, 2 - Gioi tinh , 3 - Loai phong ." << endl;
    cin >> index;
    if(index == 1){
        cout << "Moi ban nhan ten hoac ho ten muon tim.\n";
        cin.ignore();
        string tenKhachHang;
        getline(cin, tenKhachHang);
        cout << "\n\n" << setw(65) << "Ket qua search\n\n";
        cout << "STT" << setw(15) << "Ma Hoa don" << setw(19) << "Ten Khach hang" << setw(14)
             << "Gioi tinh" << setw(13) << "So phong" << setw(14) << "So ngay o" << setw(15) << "Tien Phong"<< endl;
        for(int i=0; i< sizeHoaDon; i++){
            if(containString(tenKhachHang, arrHoaDon[i].tenKhachHang)){
                dem ++;
                showSearch(arrHoaDon[i], i);
            }
        }
        if(dem == 0) cout << "Khong tim thay ket qua phu hop !!!\n";
    }
    else if(index == 2){
        int gioiTinh;
        cout << "Tim kiem theo gioi tinh, moi ban chon 1 - Nam, 0 - Nu.\n";
        cin >> gioiTinh;
        cout << "\n\n" << setw(65) << "Ket qua search\n\n";
        cout << "STT" << setw(15) << "Ma Hoa don" << setw(19) << "Ten Khach hang" << setw(14)
             << "Gioi tinh" << setw(13) << "So phong" << setw(14) << "So ngay o" << setw(15) << "Tien Phong"<< endl;
        for(int i=0; i< sizeHoaDon; i++){
            if(arrHoaDon[i].gioiTinh == gioiTinh){
                showSearch(arrHoaDon[i], i);
                dem ++;
            }
        }
        if(dem == 0) cout << "Khong tim thay ket qua phu hop !!!\n";
    }
    else if(index == 3){
        char loaiPhong;
        cout << "Tim kiem theo loai phong , moi ban nhap A, B, K .\n";
        cin >> loaiPhong;                                               //Bat them nhap chu thuong hay chu hoa
        cout << "\n\n" << setw(65) << "Ket qua search\n\n";
        cout << "STT" << setw(15) << "Ma Hoa don" << setw(19) << "Ten Khach hang" << setw(14)
             << "Gioi tinh" << setw(13) << "So phong" << setw(14) << "So ngay o" << setw(15) << "Tien Phong"<< endl;
        for(int i=0; i< sizeHoaDon; i++){
            if(tolower(arrHoaDon[i].loaiPhong) == tolower(loaiPhong)){
                showSearch(arrHoaDon[i], i);
                dem ++;
            }
        }
        if(dem == 0) cout << "Khong tim thay ket qua phu hop !!!\n";
    }
    else{
        cout << "Ban chon sai vui long chon lai.\n";
    }

}
string dateToString(Date date){
    string dt, d, m, y;
    d = to_string(date.day);
    m = to_string(date.month);
    y = to_string(date.year);
    dt = d + "/" + m + "/" + y;
    return dt;
}
void writeData(const string path, HoaDonKhachHang *arrHoaDon){
    ofstream outfile;
    outfile.open(path);
    string gt,ngayDen, ngayDi;
    //convert STT
    outfile << sizeHoaDon <<"\n";
    for (int i = 0; i < sizeHoaDon; i++)
    {
        ngayDen = dateToString(arrHoaDon[i].ngayDen);
        ngayDi = dateToString(arrHoaDon[i].ngayDi);
        string gt = arrHoaDon[i].gioiTinh ? "1":"0";
        outfile << arrHoaDon[i].maHoaDon <<","<< arrHoaDon[i].tenKhachHang << "," << arrHoaDon[i].soCMND << ","
        << gt << "," << arrHoaDon[i].soPhong << "," << arrHoaDon[i].loaiPhong << "," << ngayDen  << "," << ngayDi<<"\n";
    }
    outfile.close();
}
void insertHoaDon(HoaDonKhachHang *arrHoaDon){
    if(sizeHoaDon < MAX_SIZE ){
        bubbleSort(arrHoaDon);
        HoaDonKhachHang newHoaDon;
        nhapHoaDon(newHoaDon);
        int index = findIndex(arrHoaDon,newHoaDon);
        cout << "Index = " << index << ", size = " << sizeHoaDon << endl;
        if(index == sizeHoaDon) arrHoaDon[sizeHoaDon] = newHoaDon;
        else {
            for(int i=sizeHoaDon ; i > index; i--){
                arrHoaDon[i] = arrHoaDon[i-1];
            }
            arrHoaDon[index] = newHoaDon;
        }
        sizeHoaDon ++;
        cout << "Insert thanh cong!\n";
    } else{
        cout << "Insert that bai!\n";
    }
}
void nhapDate(Date &date){
    bool checkDate = true;
    do{
        cout << "Nhap ngay : ";
        cin >> date.day;
        cout << "Nhap thang : ";
        cin >> date.month;
        cout << "Nhap nam : ";
        cin >> date.year;
        checkDate = date.day > dayOfMonths(date.month, date.year) || date.day < 0 || date.year < 0 || date.month < 0;
        if(checkDate) cout << "Ngay, thang khong hop le !!!\n";
    }while(checkDate);
}
void nhapHoaDon(HoaDonKhachHang &newHoaDon){
    cout << "Nhap vao hoa don moi :\n";
    cin.ignore();
    cout << "Ma hoa don : ";
    getline(cin,newHoaDon.maHoaDon);
    cout << "Ten khach hang : ";
    getline(cin,newHoaDon.tenKhachHang);
    cout << "So CMND : ";
    getline(cin,newHoaDon.soCMND);
    cout << "Gioi tinh : ";
    cin >> newHoaDon.gioiTinh;
    //Check input phong
    bool isSoPhong;
    do{
        string soPhong = "";
        cout << "Nhap so phong : ";
        getline(cin,soPhong);
        cout << "soPhong : " << soPhong << "\n";
        isSoPhong = soPhong[0] == 'a' || soPhong[0] == 'A' || soPhong[0] == 'B' || soPhong[0] == 'b';
        if(isSoPhong)   newHoaDon.soPhong = soPhong;
        else            cout << "Ban nhap thieu ma ten phong (A/B).\n";
    }while(!isSoPhong);
    char temp = newHoaDon.soPhong[0];
    if(temp == 'A' || temp == 'a')      {newHoaDon.donGia = A; newHoaDon.loaiPhong = 'A';}
    else if(temp == 'B' || temp == 'b') {newHoaDon.donGia = B; newHoaDon.loaiPhong = 'B';}
    else    {newHoaDon.donGia = K; newHoaDon.loaiPhong = 'K';}
    cout << "Nhap ngay den cua khach hang :\n";
    nhapDate(newHoaDon.ngayDen);
    cout << "Nhap ngay di cua khach hang : \n";
    nhapDate(newHoaDon.ngayDi);
    newHoaDon.soNgayOKH   = soNgayO(newHoaDon.ngayDen,newHoaDon.ngayDi);
    newHoaDon.tienPhong = newHoaDon.donGia * newHoaDon.soNgayOKH;
}
int findIndex(HoaDonKhachHang *list,HoaDonKhachHang newHoaDon){
    int index = 0;
    if(newHoaDon.tienPhong <= list[0].tienPhong) index = 0;
    if(newHoaDon.tienPhong >= list[sizeHoaDon - 1].tienPhong) index = sizeHoaDon;
    else{
        for(int i=0; i< sizeHoaDon - 1 ; i++){
            if(newHoaDon.tienPhong >= list[i].tienPhong) index = i + 1;
        }
    }
    return index;
}
void deleteMinh(HoaDonKhachHang *list){
    bool isContain;
    int dem = 0;
    for(int i=0; i<sizeHoaDon; i++){
        isContain = containString("minh",list[i].tenKhachHang);
        if(isContain){
            dem ++;
            string name = list[i].tenKhachHang;
            for(int j=i ; j < sizeHoaDon; j++){
                list[i] = list[i+1];
                aqualNull(list[sizeHoaDon - 1]);                //Xem lai
            }
            sizeHoaDon -- ;
            cout << "Da xoa "<< dem << " - " <<name <<"\n";
        }
    }
    if(dem == 0){
        cout << "Khong co khach hang ten Minh.!!\n";
    }
}
string lastName(string name){
    string lastName = "";
    int indexLastName;
    for(int  i=0; i<name.size(); i++){
        if(name[i] == ' ' ) indexLastName = i + 1;
    }
    for(int i=indexLastName; i<name.size(); i++){
        lastName += tolower(name[i]);
    }
    return lastName;
}
bool containString(string name1, string name2){
    bool result, haveSpace = false;
    for(int i=0; i<name1.size(); i++){
        if(name1[i] == ' ') haveSpace = true;
    }
    if(!haveSpace){
        string temp = lastName(name2);
        string lastNameLowerCase = "";
        for(int i=0; i<name1.size(); i++){
            lastNameLowerCase += tolower(name1[i]);
        }
        result = temp == lastNameLowerCase;
    }else{
        result = name1 == name2;
    }
    return result;
}
void aqualNull(HoaDonKhachHang &hoaDon){
    hoaDon.maHoaDon = "";
    hoaDon.tenKhachHang = "";
    hoaDon.soCMND = "";
    hoaDon.gioiTinh = false;
    hoaDon.soPhong = "";
    hoaDon.donGia  = N;
    hoaDon.ngayDen.day = 0;
    hoaDon.ngayDen.month = 0;
    hoaDon.ngayDen.year = 0;
    hoaDon.ngayDi.day = 0;
    hoaDon.ngayDi.month = 0;
    hoaDon.ngayDi.year = 0;
    hoaDon.soNgayOKH = 0;
    hoaDon.tienPhong = 0;
}
void swap(HoaDonKhachHang &hoaDon1, HoaDonKhachHang &hoaDon2){
    HoaDonKhachHang temp = hoaDon1;
    hoaDon1 = hoaDon2;
    hoaDon2 = temp;
}
void bubbleSort(HoaDonKhachHang *arrHoaDon){
    for(int i= 0; i< sizeHoaDon - 1 ; i++){
        for(int j = 0; j< sizeHoaDon -1 - i ; j++){
            if(arrHoaDon[j].tienPhong > arrHoaDon[j+1].tienPhong)
                swap(arrHoaDon[j], arrHoaDon[j+1]);
        }
    }
}
void readData(const string path, HoaDonKhachHang *arrHoaDon) {
    string line;
    ifstream myfile (path);
    if (myfile.is_open()){
        int i = 0;
        getline (myfile,line);
        while ( getline (myfile,line)){
            arrHoaDon[i] = convertHoaDon(line);
            i ++;
        }
        myfile.close();
    }else cout << "Can't not open fie!!\n";
}
int getSize(string path){
    ifstream infile;
    string n;
    infile.open(path);
    int size = 0;
    if(infile.is_open()){
        infile >> n;
        stringstream SIZE(n);
        SIZE >> size;
        infile.close();
    } else{
        cout << "Error getsize!!\n";
    }
    return size;
}
bool namNhuan(int year){
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}
int dayOfMonths(int month, int year){
    switch(month){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            return namNhuan(year) ? 29 : 28;
        default:
            cout << "Thang khong hop le!!!\n";
            return 0;
    }
}
int soNgayO(Date ngayDen, Date ngayDi){
    int soNgay = 0;
    if(ngayDen.year == ngayDi.year){
        if(ngayDen.month == ngayDi.month){
            soNgay += ngayDi.day - ngayDen.day;
        }else{
            soNgay += dayOfMonths(ngayDen.month,ngayDen.year) - ngayDen.day + ngayDi.day;
            for(int i=ngayDen.month + 1; i<ngayDi.month ; i++)
                soNgay += dayOfMonths(i,ngayDen.year);
        }
    }
    if(ngayDen.year != ngayDi.year){
        if(ngayDen.day == ngayDi.day && ngayDen.month == ngayDi.month){
            for(int j=ngayDen.year; j< ngayDi.year ; j++)
                soNgay += namNhuan(j) ? 366 : 365;
        }
        else{
            soNgay += dayOfMonths(ngayDen.month,ngayDen.year) - ngayDen.day + ngayDi.day;
            for(int i=ngayDen.month + 1; i<= 12 ; i++)
                soNgay += dayOfMonths(i,ngayDen.year);
            for(int i=1; i< ngayDi.month ; i++)
                soNgay += dayOfMonths(i,ngayDen.year);
            for(int j=ngayDen.year + 1; j< ngayDi.year ; j++)
                soNgay += namNhuan(j) ? 366 : 365;
        }
    }
    return soNgay;
}
void showDoanhThu(HoaDonKhachHang *arrHoaDon){
    int tongTienPhongLoaiA = 0, tongTienPhongLoaiB = 0, tongTienPhongKhac = 0, tongTienCacPhong = 0;
    for(int i=0 ; i< sizeHoaDon; i++){
        if(arrHoaDon[i].loaiPhong == 'A' || arrHoaDon[i].loaiPhong == 'a')
            tongTienPhongLoaiA += arrHoaDon[i].tienPhong;
        else if(arrHoaDon[i].loaiPhong == 'B' || arrHoaDon[i].loaiPhong == 'b')
            tongTienPhongLoaiB += arrHoaDon[i].tienPhong;
        else
            tongTienPhongKhac += arrHoaDon[i].tienPhong;
    }
    tongTienCacPhong = tongTienPhongKhac + tongTienPhongLoaiA + tongTienPhongLoaiB;
    cout << "\tLoai phong \t" << "\tTong tien \n";
    cout << "\t    A" << setw(20) << convertMoney(tongTienPhongLoaiA) << "(VND)" << endl;
    cout << "\t    B" << setw(20) << convertMoney(tongTienPhongLoaiB) << "(VND)"<< endl;
    cout << "\t    Khac" << setw(17) << convertMoney(tongTienPhongKhac) << "(VND)"<< endl;
    cout << "\n\tTong cac phong thu duoc : \t" << convertMoney(tongTienCacPhong) << "(VND)"<< endl;
}
//Convert Date
Date convertDate(string a){
    string arrDate[3];
    Date date;
    int j=0;
    for(int i=0; i< 3; i++){
        string s= "";
        for(; j<a.size(); j++){
            string temp(1,a[j]);
            if(a[j] != '/')   s += temp;
            else             { j++; break;}
        }
        arrDate[i] = s ;
    }
    int day , month, year;
    stringstream DAY(arrDate[0]);
    DAY >> day;
    stringstream MONTH(arrDate[1]);
    MONTH >> month;
    stringstream YEAR(arrDate[2]);
    YEAR >> year;
    date.day = day;
    date.month = month;
    date.year = year;
    return date;
}
HoaDonKhachHang convertHoaDon(string a){
    HoaDonKhachHang hoaDon;
    int j=0;
    string arr[8];
    for(int i=0; i< 8; i++){
        string s= "";
        for(; j<a.size(); j++){
            string temp(1,a[j]);
            if(a[j] != ',' && a[j] != ';')   s += temp;
            else             { j++; break;}
        }
        arr[i] = s ;
    }
    hoaDon.maHoaDon = arr[0];
    hoaDon.tenKhachHang = arr[1];
    hoaDon.soCMND = arr[2];
    int gt;
    stringstream GT(arr[3]);
    GT >> gt;
    hoaDon.gioiTinh = gt;
    hoaDon.soPhong = arr[4];
    if(arr[5] == "A" || arr[5] == "a" ) {hoaDon.loaiPhong = 'A' ; hoaDon.donGia = A; }
    if(arr[5] == "B" || arr[5] == "b") {hoaDon.loaiPhong = 'B' ; hoaDon.donGia = B; }
    if(arr[5] == "K" || arr[5] == "k") {hoaDon.loaiPhong = 'K' ; hoaDon.donGia = K; }
    //Convert string to Date
    hoaDon.ngayDen = convertDate(arr[6]);
    hoaDon.ngayDi = convertDate(arr[7]);
    hoaDon.soNgayOKH   = soNgayO(hoaDon.ngayDen,hoaDon.ngayDi);
    hoaDon.tienPhong = hoaDon.donGia * hoaDon.soNgayOKH;
    return hoaDon;
}
string convertMoney(long money){
    string mooStr = to_string(money), resultMon = "", temp= "";
    int j=0;
    for(int i=mooStr.size()-1; i>=0; i--){
        if(j == 3) {temp += ","; j = 0 ;}
        temp += mooStr[i]; j++;
    }
    for(int i=temp.size()-1; i>=0; i--){
        resultMon += temp[i];
    }
    return resultMon;
}
void showArrHoaDon(HoaDonKhachHang *arrHoaDon){
    cout << "\n\n  " << setw(80) << " Bang thong tin khach hang cua thang\n\n";
    cout << "STT" << setw(15) << "Ma Hoa don" << setw(19) << "Ten Khach hang" << setw(12) << "So CMND" << setw(14)
    << "Gioi tinh" << setw(13) << "So phong" << setw(15) << "Loai phong" << setw(12) << "Don Gia" << setw(14)
    << "So ngay o" << setw(15) << "Tien Phong"<< endl;
    for(int i=0; i< sizeHoaDon ; i++){
        HoaDonKhachHang hoaDon = arrHoaDon[i];
        int index = (i + 1 < 10 ) ? 14:13;
        cout << " "<< i + 1<< setw(index) ;
        cout << hoaDon.maHoaDon << setw(8 + hoaDon.tenKhachHang.size());
        cout << hoaDon.tenKhachHang << setw(20 - hoaDon.tenKhachHang.size() + hoaDon.soCMND.size());
        string gioiTinh = (hoaDon.gioiTinh) ? "Nam" : "Nu";
        cout << hoaDon.soCMND << setw(13 - hoaDon.soCMND.size() + gioiTinh.size());
        cout << gioiTinh << setw(22 - gioiTinh.size() - hoaDon.soPhong.size());
        cout << hoaDon.soPhong << setw(12);
        cout << hoaDon.loaiPhong << setw(15);
        cout << hoaDon.donGia << setw(14) << hoaDon.soNgayOKH << setw(16) << convertMoney(hoaDon.tienPhong) << "  (VND)" << endl;
    }
}