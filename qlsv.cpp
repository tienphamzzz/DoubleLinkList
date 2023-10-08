#include<iostream>
#include<fstream>
#include<string>
#include <sstream>

using namespace std;

//Tạo lớp Node mẫu
template <class T>
class Node {
public:
    T data;
    Node* prev;
    Node* next;

    Node(T value) : data(value), prev(nullptr), next(nullptr) {} //Hàm tạo 1 biến với biến đầu vào là value có kiểu T

    bool operator==(const Node<T>& other) {
        return data == other.data;
    }

    void operator=(const Node<T>& other) {
        data = other.data;
        prev = other.prev;
        next = other.next;
    }

};

//Tạo lớp DanhSachLienKetKep mẫu
template <class T>
class DanhSachLienKetKep {

    Node<T>* head;
    Node<T>* tail;

public:
    DanhSachLienKetKep() : head(nullptr), tail(nullptr) {} //Hàm tạo khởi tạo giá trị ban đầu của head và tail là nullptr

    // Hàm thêm một phần tử vào cuối danh sách
    void ThemPhanTu(T value) {
        Node<T>* newNode = new Node<T>(value); //Tạo 1 biến newNode có kiểu Node<T> với giá trị value
        if (head == nullptr) {
            head = tail = newNode;
        } else { //Nếu head khác nullptr thì thêm phần tử newNode vào cuối danh sách (Sau tail hiện tại)
            tail->next = newNode; //Phần tử tiếp theo của tail bây giờ là newNode
            newNode->prev = tail; //Phần tử trước đó của newNode bây giờ là tail
            tail = newNode; //Cập nhật lại tail bây giờ là newNode
        }
    }

    // Hàm hiển thị toàn bộ danh sách
    void HienThiDanhSach() {
        Node<T>* current = head;
        while (current != nullptr) {
            cout << current->data << endl;
            current = current->next;
        }
        cout << endl;
    }

    // Hàm tìm kiếm phần tử trong danh sách
    Node<T>* TimPhanTu(T value) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    // Hàm xóa một phần tử khỏi danh sách
    void XoaPhanTu(T value) {
        Node<T>* nodeToRemove = TimPhanTu(value);
        if (nodeToRemove == nullptr) {
            cout << "Khong tim thay phan tu de xoa." << endl;
        } else {
            if (nodeToRemove == head) {
                head = head->next;
                head->prev = nullptr;
            } else if (nodeToRemove == tail) {
                tail = tail->prev;
                tail->next = nullptr;
            } else {
                nodeToRemove->prev->next = nodeToRemove->next; //Phần tử trước đó của nodeToRemove bây giờ là phần tử tiếp theo của nodeToRemove
                nodeToRemove->next->prev = nodeToRemove->prev; //Phần tử tiếp theo của nodeToRemove bây giờ là phần tử trước đó của nodeToRemove
            }
            delete nodeToRemove;
        }
    }

    // Hàm cập nhật thông tin của một phần tử
    void CapNhatPhanTu(T value, T newValue) {
        Node<T>* nodeToUpdate = TimPhanTu(value);
        if (nodeToUpdate == nullptr) {
            cout << "Khong tim thay phan tu de cap nhat." << endl;
        } else {
            nodeToUpdate->data = newValue;
        }
    }

    // Hàm đọc dữ liệu từ file
    void DocFile(string fileName) {
        XoaDanhSach();
        ifstream fileIn(fileName, ios::in); // Mở file để đọc
        if (fileIn.fail()) { // Nếu mở file thất bại
            cout << "Khong the mo file." << endl;
        } else {
            while(fileIn.eof() == false){ // Nếu chưa kết thúc file
                int maSV;
                string hoTen;
                string ngaySinh;
                string gioiTinh;
                string lop;
                fileIn >> maSV;
                fileIn.ignore();
                getline(fileIn, hoTen);
                getline(fileIn, ngaySinh);
                getline(fileIn, gioiTinh);
                getline(fileIn, lop);
                T value(maSV, hoTen, ngaySinh, gioiTinh, lop);
                ThemPhanTu(value);
            }   
        }
    }

    void GhiFile(string fileName) {
        ofstream fileOut(fileName, ios::out); //Mở file để ghi
        if (fileOut.fail()) { //Nếu mở file thất bại
            cout << "Khong the mo file." << endl;
        } else {
            Node<T>* current = head;
            while (current != nullptr) {
                fileOut << current->data << endl;
                current = current->next;
            }
            fileOut.close();
            cout << "Ghi file thanh cong!" << endl;
        }
    }

    void XoaDanhSach() {
        while (head != nullptr) {
            Node<T>* nodeToRemove = head;
            head = head->next;
            delete nodeToRemove;
        }
    }

    ~DanhSachLienKetKep() {
        while (head != nullptr) {
            Node<T>* nodeToRemove = head;
            head = head->next;
            delete nodeToRemove;
        }
    }
};

class SinhVien {
    public:
    int maSV;
    string hoTen;
    string ngaySinh;
    string gioiTinh;
    string lop;

    SinhVien() {
        maSV = 0;
        hoTen = "";
        ngaySinh = "";
        gioiTinh = "";
        lop = "";
    }
    
    SinhVien(int maSV, string hoTen, string ngaySinh, string gioiTinh, string lop) {
        this->maSV = maSV;
        this->hoTen = hoTen;
        this->ngaySinh = ngaySinh;
        this->gioiTinh = gioiTinh;
        this->lop = lop;
    }

    friend ostream& operator<<(ostream& os, const SinhVien& sv) {
        os << sv.maSV << " " << sv.hoTen << " " << sv.ngaySinh << " " << sv.gioiTinh << " " << sv.lop;
        return os;
    }

    friend istream& operator>>(istream& is, SinhVien& sv) {
    // Đọc dữ liệu từ tệp và gán vào các thành viên của lớp SinhVien
    is >> sv.maSV >> sv.hoTen >> sv.ngaySinh >> sv.gioiTinh >> sv.lop;
    return is;
    }

    bool operator==(const SinhVien& other) {
        return (maSV == other.maSV || hoTen == other.hoTen);
    }

    void operator=(const SinhVien& other) {
        maSV = other.maSV;
        hoTen = other.hoTen;
        ngaySinh = other.ngaySinh;
        gioiTinh = other.gioiTinh;
        lop = other.lop;
    }

};

int main(){
    DanhSachLienKetKep<SinhVien> dslk;
    dslk.DocFile("sinhvien.txt");
    bool isContinue = true;
    int choice;

        

    do{

        cout << "1. Them sinh vien\n";
        cout << "2. Xoa sinh vien\n";
        cout << "3. Cap nhat thong tin sinh vien\n";
        cout << "4. Hien thi danh sach sinh vien\n";
        cout << "5. Tim kiem sinh vien\n";
        cout << "6. Nhap danh sach sinh vien tu file\n";
        cout << "7. Ghi danh sach sinh vien vao file\n";
        cout << "8. Thoat\n";
        cout << "Nhap lua chon: ";

        cin >> choice;
        cin.ignore();

        switch(choice){
            case 1:{
                SinhVien sv;
                cout << "Nhap ma sinh vien: " << endl;
                cin >> sv.maSV;
                cin.ignore();
                cout << "Nhap ho ten: " << endl;
                getline(cin, sv.hoTen);
                cout << "Nhap ngay sinh: " << endl;
                cin >> sv.ngaySinh;
                cout << "Nhap gioi tinh: " << endl;
                cin >> sv.gioiTinh;
                cout << "Nhap lop: " << endl;
                cin >> sv.lop;
                dslk.ThemPhanTu(sv);
                cout << "Them thanh cong!" << endl;
                break;
            }
            case 2:{
                int maSV;
                cout << "Nhap ma sinh vien can xoa: " << endl;
                cin >> maSV;
                dslk.XoaPhanTu(SinhVien(maSV, "", "", "", ""));
                cout << "Xoa thanh cong!" << endl;
                break;
            }
            case 3:{
                int maSV;
                cout << "Nhap ma sinh vien can cap nhat: " << endl;
                cin >> maSV;
                SinhVien sv;
                cout << "Nhap ma sinh vien: " << endl;
                cin >> sv.maSV;
                cin.ignore();
                cout << "Nhap ho ten: " << endl;
                getline(cin, sv.hoTen);
                cout << "Nhap ngay sinh: " << endl;
                cin >> sv.ngaySinh;
                cout << "Nhap gioi tinh: " << endl;
                cin >> sv.gioiTinh;
                cout << "Nhap lop: " << endl;
                cin >> sv.lop;
                dslk.CapNhatPhanTu(SinhVien(maSV, "", "", "", ""), sv);
                cout << "Cap nhat thanh cong!" << endl;
                break;
            }
            case 4:{
                cout << "Danh sach sinh vien: " << endl;
                dslk.HienThiDanhSach();
                break;
            }
            case 5:{
                string hoTen;
                cout << "Nhap ho ten sinh vien can tim: " << endl;
                // cin.ignore();
                getline(cin, hoTen);
                Node<SinhVien>* result = dslk.TimPhanTu(SinhVien(0, hoTen, "", "", ""));
                if(result != nullptr){
                    cout << "Tim thay sinh vien: " << endl;
                    cout << result->data << endl;
                } else {
                    cout << "Khong tim thay sinh vien." << endl;
                }
                break;
            }
            case 6:{
                string fileName;
                cout << "Nhap ten file can doc: " << endl;
                cin >> fileName;
                dslk.DocFile(fileName);
                cout << "Doc file thanh cong!" << endl;
                break;
            }
            case 7:{
                string fileName;
                cout << "Nhap ten file can ghi: " << endl;
                cin >> fileName;
                dslk.GhiFile(fileName);
                break;
            }
            case 8:
                cout << "Tam biet!" << endl;
                isContinue = false;
                break;
            default:
                cout << "Nhap sai. Vui long nhap lai!" << endl;
                break;
        }
        do{
            int choice2;
            cout << "Ban co muon tiep tuc khong? (1: Co, 0: Khong): ";
            cin >> choice2;
            switch(choice2){
                case 0:
                    isContinue = false;
                    break;
                case 1:
                    isContinue = true;
                    system("cls");
                    break;
                default:
                    system("cls");
                    cout << "Nhap sai. Vui long nhap lai!" << endl;
                    break;
            }
        } while(isContinue != 0 && isContinue != 1);

    } while(isContinue);

    return 0;
}