#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstdlib>
#include <string>
#include <ctime>
#include <stdio.h>

#ifdef _WIN32

#include <windows.h>

#else
#include <unistd.h>
#endif // _WIN32

using namespace std;

void sleepcp(int milliseconds) //��ƽ̨sleep����
{
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif // _WIN32
}

#define OK 0
#define ABNORMAL -1
#define MAXSIZE 100
typedef int Status;

class Flight {
private:
    char FlightNo[50];
    char CraftType[50];
    char Departcity[50];
    char Arrivcity[50];
    char DepartTime[50];
    char ArrivTime[50];
    int SeatsNum;
    double Price;

public:
    Flight() {}

    Flight(string No, string CraftT, string Departc, string Arrivc, string DepartT, string ArrivT, int SeatsN,
           double Pri) {
        strcpy_s(FlightNo, No.c_str());
        strcpy_s(CraftType, CraftT.c_str());
        strcpy_s(Departcity, Departc.c_str());
        strcpy_s(Arrivcity, Arrivc.c_str());
        strcpy_s(DepartTime, DepartT.c_str());
        strcpy_s(ArrivTime, ArrivT.c_str());
        SeatsNum = SeatsN;
        Price = Pri;
    }

    void Display() {
        cout << FlightNo << "  " << Departcity << "��" << Arrivcity << "  ��ɣ�" << DepartTime << "  ��أ�" << ArrivTime
             << "  ִ�ɣ�" << CraftType << "  ��Ʊ��" << SeatsNum << "  " << Price << "Ԫ" << endl;
    }

    bool IfFlightNo(string Num) {
        if (FlightNo == Num)
            return true;
        else
            return false;
    }

    Status ChangeFlightNo(string Num) {
        if (Num.empty()) {
            return ABNORMAL;
        } else {
            strcpy_s(FlightNo, Num.c_str());
            return OK;
        }
    }

    char *ReturnFliNO() {
        return FlightNo;
    }

    bool IfDepartCity(string City) {
        if (Departcity == City)
            return true;
        else
            return false;
    }

    Status ChangeDepartC(string City) {
        if (City.empty()) {
            return ABNORMAL;
        } else {
            strcpy_s(Departcity, City.c_str());
            return OK;
        }
    }

    bool IfArrivCity(string City) {
        if (Arrivcity == City) {
            return true;
        } else {
            return false;
        }
    }

    Status ChangeArrivC(string City) {
        if (City.empty()) {
            return ABNORMAL;
        } else {
            strcpy_s(Arrivcity, City.c_str());
            return OK;
        }
    }

    Status ChangeDepartT(string Time) {
        if (Time.empty()) {
            return ABNORMAL;
        } else {
            strcpy_s(DepartTime, Time.c_str());
            return true;
        }
    }

    Status ChangeArrivalT(string Time) {
        if (Time.empty()) {
            return ABNORMAL;
        } else {
            strcpy_s(ArrivTime, Time.c_str());
            return OK;
        }
    }

    Status ChangeCraftT(string craftT) {
        if (craftT.empty()) {
            return ABNORMAL;
        } else {
            strcpy_s(CraftType, craftT.c_str());
            return OK;
        }
    }

    Status ChangeSeatNum(int seats) {
        if (seats < 0) {
            return ABNORMAL;
        } else {
            SeatsNum = seats;
            return OK;
        }
    }

    void Seatsplus() {
        SeatsNum++;
    }

    void Saeatsdec() {
        SeatsNum--;
    }

    int ReturnSeats() {
        return SeatsNum;
    }

    char *ReturnDepartC() {
        return Departcity;
    }

    char *ReturnArrivC() {
        return Arrivcity;
    }


    Status ChangePrice(double price) {
        if (price < 0) {
            return ABNORMAL;
        } else {
            Price = price;
            return OK;
        }
    }
};

class Customer {
private:
    char username[20];
    char password[20];

public:
    Customer() {}

    Customer(string name, string passw) {
        strcpy_s(username, name.c_str());
        strcpy_s(password, passw.c_str());
    } //ע��֮ǰҪ����û��������볤���Ƿ�Ϲ�
    bool Checkusername(string name) { //�û�����
        if (name == username)
            return true;
        else
            return false;
    }

    bool Checkpassword(string passw) {
        if (passw == password)
            return true;
        else

            return false;
    }

    Status Changepasswrd(string newpswd) {
        if (newpswd.empty()) {
            return ABNORMAL;
        } else {
            strcpy_s(password, newpswd.c_str());
            return OK;
        }
    }

    Status ChangeUsername(string name) {
        if (name.empty()) {
            return ABNORMAL;
        } else {
            strcpy_s(username, name.c_str());
            return OK;
        }
    }
};

typedef struct TicketsperFli {
    char FliNumber[20];
    int Tickets;
} TPF;

typedef struct BookInfo {
    char Username[20];
    TPF tpf[MAXSIZE];
    int NumOfTPF;
};

Status AddFlight() {
    string FlightN, craftT, Departc, Arrivc, DepartT, ArrivT;
    int SeatsN = 0;
    double Pri = 0;
    cout << "�����뺽��ţ�";
    cin >> FlightN;

    cout << "��������ɳ��У�";
    cin >> Departc;

    cout << "�����뽵����У�";
    cin >> Arrivc;

    cout << "���������ʱ�䣺";
    cin >> DepartT;

    cout << "�����뵽��ʱ�䣺";
    cin >> ArrivT;

    cout << "������ִ�ɻ��ͣ�";
    cin >> craftT;

    cout << "��������λ����";
    cin >> SeatsN;

    cout << "������Ʊ�ۣ�";
    cin >> Pri;

    Flight fli1(FlightN, craftT, Departc, Arrivc, DepartT, ArrivT, SeatsN, Pri);

    fstream outfile("flinfo.dat", ios::binary | ios::out | ios::in);
    if (!outfile) {
        cerr << "�򿪳���!" << endl;
        abort(); //���ļ������ڻ��ļ���
    }

    int i = 0;
    outfile.seekg(0, ios::beg);
    outfile.read((char *) &i, sizeof(int));
    outfile.seekg(((sizeof(int)) + (i * sizeof(Flight))), ios::beg);

    fli1.Display(); //��ɾ��
    outfile.write((char *) &fli1, sizeof(fli1));

    i++;
    outfile.seekg(0, ios::beg);
    outfile.write((char *) &i, sizeof(int)); //��������1
    outfile.seekg(0, ios::beg);
    outfile.read((char *) &i, sizeof(int));

    outfile.close();
    return OK;
}

Status ShowAllFli() {
    Flight fli2;
    int NumOfFly = 0;
    ifstream infile("flinfo.dat", ios::binary | ios::in);
    if (!infile) {
        cerr << "�򿪳���!" << endl;
        abort();
    }
    infile.seekg(0, ios::beg);
    infile.read((char *) &NumOfFly, sizeof(int));
    if (NumOfFly == 0)
        return ABNORMAL;
    infile.seekg(sizeof(int), ios::beg);
    cout << "\n���к�����Ϣ���£�\n\n";
    for (int i = 0; i < NumOfFly; i++) {
        infile.read((char *) &fli2, sizeof(Flight));
        cout << "   " << i + 1 << ".  ";
        fli2.Display();
    }
    infile.close();
    return OK;
}

bool IfEmptyFile(fstream &fstest) {
    int i;
    fstest.seekg(0, ios::end);
    i = fstest.tellg();
    if (i == 0)
        return true;
    else
        return false;
}

bool CheckFliNum(int n) {
    int i = 0;
    ifstream infile("flinfo.dat", ios::in | ios::binary);
    infile.read((char *) &i, sizeof(int));
    infile.close();
    if (n <= i)
        return true;
    else
        return false;
}

Status DeleteFli(int n) {
    int i = 0, temp = 0;
    Flight *fli, flileft;
    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.read((char *) &i, sizeof(int));
    i--;
    fsfile.seekg(0, ios::beg);
    fsfile.write((char *) &i, sizeof(int)); //ʹ�ñ������ļ��м�¼����������int���ͼ�һ
    if ((i + 1) == n) {
        fsfile.close();
        return OK;
    } else {
        fli = new Flight[i + 1];
        fsfile.seekg(sizeof(int), ios::beg);

        for (int k = 0; k < i + 1; k++) {
            fsfile.read((char *) &fli[temp], sizeof(Flight));
            temp++;
        } //���������ж�ȡ��������

        fsfile.seekg(sizeof(int), ios::beg);

        for (int j = 0; j < i + 1; j++) {
            //fli[j].Display();
            if (j == n - 1)
                continue;
            fsfile.write((char *) &fli[j], sizeof(Flight));
        }               //�������е����ݽض����뵽�ļ���
        delete[] fli;   //�ͷ���ʱ����
        fsfile.close(); //�ر��ļ�
        return OK;
    }
}

Status ModifyDepartC(int n) {
    Flight fli2;
    string DepartC;
    n--;
    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.read((char *) &fli2, sizeof(Flight));
    cout << "��������Ҫ�滻Ϊ����ɳ���:";
    cin >> DepartC;
    fli2.ChangeDepartC(DepartC);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.write((char *) &fli2, sizeof(Flight));
    return OK;
}

Status ModifyLandC(int n) {
    Flight fli2;
    string LandC;
    n--;
    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.read((char *) &fli2, sizeof(Flight));
    cout << "��������Ҫ�滻Ϊ�Ľ������:";
    cin >> LandC;
    fli2.ChangeArrivC(LandC);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.write((char *) &fli2, sizeof(Flight));
    return OK;
}

Status ModifyCraft(int n) {
    Flight fli2;
    string CraftT;
    n--;
    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.read((char *) &fli2, sizeof(Flight));
    cout << "��������Ҫ�滻Ϊ��ִ�ɻ���:";
    cin >> CraftT;
    fli2.ChangeCraftT(CraftT);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.write((char *) &fli2, sizeof(Flight));
    return OK;
}

Status ModifyPrice(int n) {
    Flight fli2;
    double Pri;
    n--;
    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.read((char *) &fli2, sizeof(Flight));
    cout << "��������ĺ�ļ۸�:";
    cin >> Pri;
    fli2.ChangePrice(Pri);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.write((char *) &fli2, sizeof(Flight));
    return OK;
}

Status ModifyTime(int n) {
    Flight fli2;
    string DepartT, ArrivT;
    n--;
    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.read((char *) &fli2, sizeof(Flight));
    cout << "��������ĺ�ĵ����ʱ��:";
    cin >> DepartT;
    cout << "��������ĺ�ĵĽ���ʱ��:";
    cin >> ArrivT;
    fli2.ChangeDepartT(DepartT);
    fli2.ChangeArrivalT(ArrivT);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.write((char *) &fli2, sizeof(Flight));
    return OK;
}

Status ModifyFliNo(int n) {
    Flight fli2;
    string FliNo;
    n--;
    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.read((char *) &fli2, sizeof(Flight));
    cout << "��������ĺ�ĺ����:";
    cin >> FliNo;
    fli2.ChangeFlightNo(FliNo);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.write((char *) &fli2, sizeof(Flight));
    return OK;
}

Status ModifySeats(int n) {
    Flight fli2;
    int Seats;
    n--;
    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.read((char *) &fli2, sizeof(Flight));
    cout << "��������ĺ����λ��:";
    cin >> Seats;
    fli2.ChangeSeatNum(Seats);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.write((char *) &fli2, sizeof(Flight));
    return OK;
}

bool CheckSameName(string name, int &loca) {
    int n;
    Customer cus;
    fstream user("userinfo.dat", ios::in | ios::out | ios::binary);
    user.seekg(0, ios::beg);
    user.read((char *) &n, sizeof(int));
    if (n == 0) {
        user.close();
        return false;
    } else {
        for (int i = 0; i < n; i++) {
            user.read((char *) &cus, sizeof(cus));
            if (cus.Checkusername(name)) {
                loca = i;
                user.close();
                return true;
            }
        }
        user.close();
        return false;
    }
}

Status RegisterUser(string name, string password) {
    int i = 0;
    Customer cus(name, password);
    fstream user("userinfo.dat", ios::in | ios::out | ios::binary);
    user.seekg(0, ios::beg);
    user.read((char *) &i, sizeof(int));

    user.seekg(((sizeof(int)) + (i * sizeof(Customer))), ios::beg);
    user.write((char *) &cus, sizeof(Customer)); //д���û�

    i++;
    user.seekg(0, ios::beg);
    user.write((char *) &i, sizeof(int)); //�û�����һ
    user.close();
    return OK;
} //ע��֮ǰҪ����û��������볤���Ƿ�Ϲ�

bool Login(int n, string password) {
    Customer cuser;
    fstream user("userinfo.dat", ios::in | ios::out | ios::binary);
    user.seekg(((sizeof(int)) + (n * sizeof(Customer))), ios::beg);
    user.read((char *) &cuser, sizeof(Customer));
    if (cuser.Checkpassword(password)) {
        user.close();
        return true;
    } else {
        user.close();
        return false;
    }
}

bool SearchFliNo(string FliNo, int &theposi) {
    int i;
    Flight tempfli;
    fstream fliserch("flinfo.dat", ios::in | ios::out | ios::binary);
    fliserch.seekg(0, ios::beg);
    fliserch.read((char *) &i, sizeof(int));
    for (int j = 0; j <= i; j++) {
        fliserch.read((char *) &tempfli, sizeof(Flight));
        if (tempfli.IfFlightNo(FliNo)) {
            theposi = j;
            fliserch.close();
            return true;
        }
    }
    fliserch.close();
    return false;
}

bool SearchFliC(string Departc, string Arrivc, int **Fliarr, int &n) {
    int i = 0;
    n = 0;
    Flight tempfli;
    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.seekg(0, ios::beg);
    fsfile.read((char *) &i, sizeof(int));
    *Fliarr = new int[i];
    for (int j = 0; j < i; j++) {
        fsfile.read((char *) &tempfli, sizeof(Flight));
        if (tempfli.IfDepartCity(Departc) && tempfli.IfArrivCity(Arrivc)) {
            *(*Fliarr + n) = j;
            n++;
        }
    }
    if (n > 0) {
        fsfile.close();
        return true;
    } else {
        fsfile.close();
        return false;
    }
}

bool SearchFliRC(string City, int **Fliarr, int &n) {
    int i = 0;
    n = 0;
    Flight tempfli;
    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.seekg(0, ios::beg);
    fsfile.read((char *) &i, sizeof(int));
    *Fliarr = new int[i];
    for (int j = 0; j < i; j++) {
        fsfile.read((char *) &tempfli, sizeof(Flight));
        if (tempfli.IfDepartCity(City) || tempfli.IfArrivCity(City)) {
            *(*Fliarr + n) = j;
            n++;
        }
    }
    if (n > 0) {
        fsfile.close();
        return true;
    } else {
        fsfile.close();
        return false;
    }
}

void ShowthisFli(int posi, int n) {
    Flight fli;
    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.seekg((sizeof(int)) + (posi * sizeof(Flight)), ios::beg);
    fsfile.read((char *) &fli, sizeof(Flight));
    cout << "  " << n + 1 << ".  ";
    fli.Display();
    fsfile.close();
}

void ShowthisFli(int posi, int n, string fliNo) {
    Flight fli;

    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);

    fsfile.seekg((sizeof(int)) + (posi * sizeof(Flight)), ios::beg);

    fsfile.read((char *) &fli, sizeof(Flight));

    if (fli.ReturnFliNO() == fliNo) {
        cout << "  " << n + 1 << ".  ";
        fli.Display();
        fsfile.close();
    } else {
        return;
    }
}

static void inputPassword(string &str, int size) {
    //��������ʵ��
    size++;
    char c;
    int count = 0;
    char *password = new char[size]; // ��̬����ռ�
    while ((c = _getch()) != '\r') {

        if (c == 8) {
            // �˸�
            if (count == 0) {
                continue;
            }
            putchar('\b'); // ����һ��
            putchar(' ');  // ���һ���ո�ԭ����*����
            putchar('\b'); // �ٻ���һ��ȴ�����
            count--;
        }
        if (count == size - 1) {
            // ��󳤶�Ϊsize-1
            continue;
        }
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
            // ����ֻ�ɰ������ֺ���ĸ
            putchar('*'); // ���յ�һ���ַ���, ��ӡһ��*
            password[count] = c;
            count++;
        }
    }
    password[count] = '\0';
    str = password;
    delete[] password; // �ͷſռ�
    cout << endl;
}

bool BookUserExited(string username, int &userposi) {
    int allbooknum = 0;
    BookInfo bkif;
    fstream bookinfo("bookinfo.dat", ios::in | ios::out | ios::binary);//��Ԥ���ļ�
    bookinfo.seekg(0, ios::beg);
    bookinfo.read((char *) &allbooknum, sizeof(int));//��ȡԤ������
    for (int i = 0; i < allbooknum; i++) {//�������
        bookinfo.read((char *) &bkif, sizeof(BookInfo));
        if (username == bkif.Username) {
            bookinfo.close();
            userposi = i;
            return true;
        }
    }
    bookinfo.close();
    userposi = -1;
    return false;
}

bool BookNoExited(BookInfo bkif, string fliNo, int &tpfposi) {
    for (int i = 0; i < bkif.NumOfTPF; i++) {
        if (bkif.tpf[i].FliNumber == fliNo) {
            tpfposi = i;
            return true;
        }
    }
    tpfposi = -1;
    return false;
}

void book(int *thisposi, int n, string username);

void book(int thisposi, string username) //��Ʊ�˵�
{
    BookInfo bookhere;
    int NumOfTicbked = 0;
    int bookn = 0;
    int sentinel = 0;
    int *thesePosi;
    Flight fli;
    char whether;
    cout << "\n�Ƿ�Ʊ��[Y/N]:";
    cin >> whether;
    while (sentinel == 0) {
        if (whether == 'Y' || whether == 'y') {
            sentinel = 1;
        } else if (whether == 'N' || whether == 'n') {
            cout << "���ڷ�����һ��..." << endl;
            return;
        } else {
            cout << "�����������������:";
            cin >> whether;
        }
    }
    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.seekg((sizeof(int)) + (thisposi * sizeof(Flight)), ios::beg);
    fsfile.read((char *) &fli, sizeof(Flight));
    cout << "�����붩Ʊ������";
    cin >> NumOfTicbked;
    if (fli.ReturnSeats() >= NumOfTicbked) //����Ʊ
    {

        int ExitedBookposi;//���ڵ��û�Ԥ��λ��
        if (BookUserExited(username, ExitedBookposi)) {//�û�֮ǰԤ����Ʊ
            BookInfo bkif2;
            int TPFposi;
            fstream bookinfo("bookinfo.dat", ios::in | ios::out | ios::binary);
            bookinfo.seekg((sizeof(int)) + (ExitedBookposi * sizeof(BookInfo)), ios::beg);
            bookinfo.read((char *) &bkif2, sizeof(BookInfo));
            if (BookNoExited(bkif2, fli.ReturnFliNO(), TPFposi)) {//�û�֮ǰԤ�������˺���
                for (int i = 0; i < NumOfTicbked; i++) {
                    bkif2.tpf[TPFposi].Tickets++;
                    fli.Saeatsdec();
                }
            } else {//�û�δԤ�������˺���
                strcpy_s(bkif2.tpf[NumOfTicbked].FliNumber, fli.ReturnFliNO());
                bkif2.tpf[NumOfTicbked].Tickets = NumOfTicbked;
                fli.ChangeSeatNum(fli.ReturnSeats() - NumOfTicbked);
            }
            fsfile.seekg((sizeof(int)) + (thisposi * sizeof(Flight)), ios::beg);
            fsfile.write((char *) &fli, sizeof(Flight));
            fsfile.close();
            bookinfo.seekg((sizeof(int)) + (ExitedBookposi * sizeof(BookInfo)), ios::beg);
            bookinfo.write((char *) &bkif2, sizeof(BookInfo));
            bookinfo.close();
        } else {//���û�֮ǰδʹ�ù�Ԥ��ϵͳ
            strcpy_s(bookhere.Username, username.c_str());
            strcpy_s(bookhere.tpf[0].FliNumber, fli.ReturnFliNO());
            bookhere.tpf[0].Tickets = NumOfTicbked;
            bookhere.NumOfTPF = 1;
            fli.ChangeSeatNum(fli.ReturnSeats() - NumOfTicbked);

            fstream bookinfo("bookinfo.dat", ios::in | ios::binary | ios::out);

            bookinfo.seekg(0, ios::beg);
            bookinfo.read((char *) &bookn, sizeof(int));

            bookinfo.seekg(0, ios::end);
            bookinfo.write((char *) &bookhere, sizeof(BookInfo));

            bookn++;
            bookinfo.seekg(0, ios::beg);
            bookinfo.write((char *) &bookn, sizeof(int));
            fsfile.seekg((sizeof(int)) + (thisposi * sizeof(Flight)), ios::beg);
            fsfile.write((char *) &fli, sizeof(Flight));
            fsfile.close();
            bookinfo.close();
        }
        cout << "\n��Ʊ�ɹ�!";
    } else //����Ʊ
    {
        Flight flihere;
        string DepartC, ArrivC;
        int n = 0;
        DepartC = fli.ReturnDepartC();
        ArrivC = fli.ReturnArrivC();
        SearchFliC(DepartC, ArrivC, &thesePosi, n);
        cout << "\nΪ���Ƽ�����ͬ�𽵳��к��ࣺ\n\n";
        for (int tempno = 0; tempno < n; tempno++) {
            ShowthisFli(thesePosi[tempno], tempno, fli.ReturnFliNO());
        }
        fsfile.close();
        book(thesePosi, n, username);
    }
}

void book(int *thisposi, int n, string username) //����Ʊ�ඩƱ�˵�
{
    Flight flirsrved;
    BookInfo bookinfo;
    int BookNo;
    int NumOfTicbked;
    int ExitedBookposi;
    char whether;
    int sentinel = 0;
    cout << "\n�Ƿ�Ʊ��[Y/N]:";
    cin >> whether;
    while (sentinel == 0) {
        if (whether == 'Y' || whether == 'y') {
            sentinel = 1;
        } else if (whether == 'N' || whether == 'n') {
            cout << "���ڷ�����һ��..." << endl;
            return;
        } else {
            cout << "�����������������:";
            cin >> whether;
        }
    }
    retry:
    cout << "\n��������Ҫ��Ʊ����ţ�";
    cin >> BookNo;
    BookNo--;//���Ϊʵ��λ��-1

    cout << "�����붩Ʊ������";
    cin >> NumOfTicbked;

    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.seekg((sizeof(int)) + (thisposi[BookNo] * sizeof(Flight)), ios::beg);
    fsfile.read((char *) &flirsrved, sizeof(Flight));


    //    strcpy_s(bookinfo.Username, username.c_str());
    //    strcpy_s(bookinfo.tpf[0].FliNumber, flirsrved.ReturnFliNO());
    //    bookinfo.tpf[0].Tickets = NumOfTicbked;

    if (flirsrved.ReturnSeats() >= NumOfTicbked) //����Ʊ
    {
        fstream bookinfo("bookinfo.dat", ios::in | ios::out | ios::binary);
        if (BookUserExited(username, ExitedBookposi)) //�û�ʹ�ù�Ԥ��ϵͳ
        {
            BookInfo bkif2;
            int TPFposi;
            bookinfo.seekg((sizeof(int)) + (ExitedBookposi * sizeof(BookInfo)), ios::beg);
            bookinfo.read((char *) &bkif2, sizeof(BookInfo));
            if (BookNoExited(bkif2, flirsrved.ReturnFliNO(), TPFposi)) {
                for (int i = 0; i < NumOfTicbked; i++) {
                    bkif2.tpf[TPFposi].Tickets++;
                    flirsrved.Saeatsdec();
                }
            } else {
                strcpy_s(bkif2.tpf[NumOfTicbked].FliNumber, flirsrved.ReturnFliNO());
                bkif2.tpf[NumOfTicbked].Tickets = NumOfTicbked;
                flirsrved.ChangeSeatNum(flirsrved.ReturnSeats() - NumOfTicbked);
            }
            fsfile.seekg((sizeof(int)) + (thisposi[BookNo] * sizeof(Flight)), ios::beg);
            fsfile.write((char *) &flirsrved, sizeof(Flight));
            fsfile.close();
            bookinfo.seekg((sizeof(int)) + (ExitedBookposi * sizeof(BookInfo)), ios::beg);
            bookinfo.write((char *) &bkif2, sizeof(BookInfo));
            bookinfo.close();
        } else {
            BookInfo bookhere;
            strcpy_s(bookhere.Username, username.c_str());
            strcpy_s(bookhere.tpf[0].FliNumber, flirsrved.ReturnFliNO());
            bookhere.tpf[0].Tickets = NumOfTicbked;
            bookhere.NumOfTPF = 1;
            flirsrved.ChangeSeatNum(flirsrved.ReturnSeats() - NumOfTicbked);


            bookinfo.seekg(0, ios::beg);
            int bookn;
            bookinfo.read((char *) &bookn, sizeof(int));

            bookinfo.seekg(0, ios::end);
            bookinfo.write((char *) &bookhere, sizeof(BookInfo));

            bookn++;
            bookinfo.seekg(0, ios::beg);
            bookinfo.write((char *) &bookn, sizeof(int));
            fsfile.seekg((sizeof(int)) + (thisposi[BookNo] * sizeof(Flight)), ios::beg);
            fsfile.write((char *) &flirsrved, sizeof(Flight));
            fsfile.close();
            bookinfo.close();
        }


        cout << "\n��Ʊ�ɹ�!";
    } else //����Ʊ
    {
        sentinel = 0;
        cout << "\n��ѡ��ĺ�����Ʊ��ʱ���㣬�Ƿ�ѡ���б�����������[Y/N]\n\n";
        while (sentinel == 0) {
            if (whether == 'Y' || whether == 'y') {
                goto retry;
            } else if (whether == 'N' || whether == 'n') {
                cout << "���ڷ�����һ��..." << endl;
                return;
            } else {
                cout << "�����������������:";
                cin >> whether;
            }
        }
    }
}

bool showallBookinfo(BookInfo userbk) {
    int posi;
    for (int i = 0; i < userbk.NumOfTPF; i++) {
        SearchFliNo(userbk.tpf[i].FliNumber, posi);
        ShowthisFli(posi, i);
        cout << " ���Ѷ�Ʊ" << userbk.tpf[i].Tickets << "��";
    }
}


void ui() //�˵�UI
{
    string TypeFliNo, TypeDepartC, TypeArrivC;
    int Fnum = 0, posi1 = 0, posi2 = 0, lastposi = 0, soposi = 0, relatedFlin = 0, *theseposi;
    char m, n, p, q, i, j, k;
    string Nam, newNam;
    string Passwd, newPasswd;
    string defAdmPasswd = "666666"; //����ԱĬ������666666

    lb1:
    //cout << endl;
    cout << "          @@     @@      @@    @@@@@@@@@    @@@@@@@@@@\n";
    cout << "          @@     @@      @@    @@           @@        \n";
    cout << "          @@     @@      @@    @@           @@        \n";
    cout << "          @@     @@      @@    @@@@@@@@@    @@@@@@@@@ \n";
    cout << "          @@     @@      @@    @@           @@        \n";
    cout << "    @@    @@      @@    @@     @@           @@        \n";
    cout << "     @@@@@@        @@@@@@      @@           @@@@@@@@@@\n";
    cout << "\n               ��ӭ���뽴�˺��ն�Ʊϵͳ��\n";
    cout << "\n********************��ѡ���û����********************\n";
    cout << "\n\t\t1.����Ա��¼\n\n";
    cout << "\t\t2.�˿͵�¼\n\n";
    cout << "\t\t3.�˳���ϵͳ\n\n";
    cout << "����������ѡ��";
    cin >> m;
    switch (m) {
        case '1': //����Ա���

            cout << "\n���������Ա���룺��Ĭ��6��6��"; //�������ԱĬ������666666
            inputPassword(Passwd, 6);

            if (Passwd == defAdmPasswd) //������ȷ
            {
                cout << "\n��¼�ɹ������ڽ������Ա�˵�...\n\n";
                sleepcp(1000);
                system("cls"); //����

                lb3:
                cout << "\n            �����˺��ն�Ʊϵͳ-����Ա�˵���\n";
                cout << "\n*****************��ѡ����Ҫ���еĲ���*****************\n";
                cout << "\n\t\t1.�鿴���к�����Ϣ���޸�\n\n";
                cout << "\t\t2.��������Ϣ\n\n";
                cout << "\t\t3.������һ��\n\n";
                cout << "����������ѡ��";
                cin >> p;
                switch (p) {
                    case '1':
                        //��ӡ���к�����Ϣ
                        if (ShowAllFli() == -1) {
                            cout << "�޺�����Ϣ�����������롣";
                            sleepcp(2000);
                            system("cls");
                            goto lb3;
                        }

                        cout << "\n��������Ҫ���в�������ţ�";
                        //int Fnum = 0;
                        cin >> Fnum;

                        if (CheckFliNum(Fnum)) {
                            //system("cls");
                            lb5:
                            cout << "\n*****************��ѡ����Ҫ�޸Ļ�ɾ���Ĳ���*****************\n";
                            cout << "\n\t\t1.ɾ������\n\n";
                            cout << "\t\t2.�޸ĺ�����ɳ���\n\n";
                            cout << "\t\t3.�޸ĺ��ཱུ�����\n\n";
                            cout << "\t\t4.�޸Ļ���\n\n";
                            cout << "\t\t5.�޸Ļ�Ʊ�۸�\n\n";
                            cout << "\t\t6.�޸���ʱ��\n\n";
                            cout << "\t\t7.�޸ĺ����\n\n";
                            cout << "\t\t8.�޸�ʣ����λ\n\n";
                            cout << "\t\t9.������һ��\n\n";
                            cout << "����������ѡ��";
                            cin >> i;
                            switch (i) {
                                case '1':
                                    DeleteFli(Fnum);
                                    cout << "\nɾ���ɹ������ڷ��ع���Ա�˵�...";
                                    sleepcp(1 * 1000);
                                    system("cls");
                                    goto lb3;

                                case '2':
                                    ModifyDepartC(Fnum);
                                    cout << "\n�޸ĳɹ���";
                                    sleepcp(1 * 1000);
                                    system("cls");
                                    goto lb5;

                                case '3':
                                    ModifyLandC(Fnum);
                                    cout << "\n�޸ĳɹ���";
                                    sleepcp(1 * 1000);
                                    system("cls");
                                    goto lb5;

                                case '4':
                                    ModifyCraft(Fnum);
                                    cout << "\n�޸ĳɹ���";
                                    sleepcp(1 * 1000);
                                    system("cls");
                                    goto lb5;

                                case '5':
                                    ModifyPrice(Fnum);
                                    cout << "\n�޸ĳɹ���";
                                    sleepcp(1 * 1000);
                                    system("cls");
                                    goto lb5;

                                case '6':
                                    ModifyTime(Fnum);
                                    cout << "\n�޸ĳɹ���";
                                    sleepcp(1 * 1000);
                                    system("cls");
                                    goto lb5;

                                case '7':
                                    ModifyFliNo(Fnum);
                                    cout << "\n�޸ĳɹ���";
                                    sleepcp(1 * 1000);
                                    system("cls");
                                    goto lb5;

                                case '8':
                                    ModifySeats(Fnum);
                                    cout << "\n�޸ĳɹ���";
                                    sleepcp(1 * 1000);
                                    system("cls");
                                    goto lb5;

                                case '9': //������һ��
                                    system("cls");
                                    goto lb3;

                                default:
                                    cout << "\n��������ȷѡ��";
                                    sleepcp(1 * 1000);
                                    system("cls");
                                    goto lb5;
                            }
                        }
                            //�����������������󣬻ص�֮ǰ
                        else {
                            cout << "\n��������ȷ�ĺ�����ţ�";
                            sleepcp(2000);
                            system("cls");
                            goto lb3;
                        }

                    case '2': //��������Ϣ
                        AddFlight();

                        cout << "\n������Ϣ¼��ɹ����������ع���Ա�˵���";
                        sleepcp(2000);
                        system("cls");
                        goto lb3;

                    case '3': //������һ�������ʼ
                        system("cls");
                        goto lb1;

                    default: //ѡ����������
                        cout << "\n��������ȷѡ��";
                        sleepcp(1 * 1000);
                        system("cls");
                        goto lb3;
                }
            } else //�������
            {
                cout << "\n������� �����µ�¼��\n";
                sleepcp(2000);
                system("cls");
                goto lb1;
            }

        case '2': //�˿����
            system("cls");
        lb2:
            cout << "\n             �����˺��ն�Ʊϵͳ-�˿Ͳ˵���\n";
            cout << "\n*****************��ѡ����Ҫ���еĲ���*****************\n";
            cout << "\n\t\t1.ע�����û�\n\n";
            cout << "\t\t2.�����˻���¼\n\n";
            cout << "\t\t3.������һ��\n\n";

            cout << "����������ѡ��";
            cin >> n;
            switch (n) {
                case '1':
                ReRegis:
                    cout << "\n���������û���:";
                    cin >> newNam;
                    if (CheckSameName(newNam, posi1)) {
                        cout << "�˻��Ѵ��ڣ���ѡ��1.ֱ�ӵ�¼��2.�����û�����";
                        int Choice = 0;
                        cin >> Choice;
                        if (Choice == 1) {
                            lastposi = posi1;
                            goto DirecLog;
                        } else {
                            goto ReRegis;
                        }
                    }
                    cout << "\n������������:";
                    inputPassword(newPasswd, 20);
                    RegisterUser(newNam, newPasswd);
                    cout << "\nע��ɹ������ڷ��س˿͵�¼���档\n";
                    sleepcp(3000);
                    system("cls");
                    goto lb2;

                case '2':
                Relog:
                    cout << "\n�������û���:";
                    cin >> Nam;
                    //�����ļ��Ƿ��д����û������������
                    /* code */
                    if (!CheckSameName(Nam, posi2)) //���û�и��û������ӡδע�ᣬ���ص�֮ǰ
                    {
                        cout << "\n���û�δע�ᣡ��ѡ��1.ע�����˺Ż�2.���������û�����";
                        int Choi2 = 0;
                        cin >> Choi2;
                        if (Choi2 == 1) {
                            goto ReRegis;
                        } else {
                            goto Relog;
                        }
                    } else {
                        lastposi = posi2;
                    }
                DirecLog:
                    cout << "\n����������:";
                    inputPassword(Passwd, 20);
                    //�ж���������
                    /* code */
                    if (Login(lastposi, Passwd)) //���������ȷ�����¼�ɹ�
                    {
                        cout << "\n��¼�ɹ���\n\n";
                        sleepcp(1 * 1000);
                        system("cls");
                        lb4:
                        cout << "\n**************��ѡ����Ҫ���еĲ���**************\n";
                        cout << "\n\t\t1.��ѯ������Ϣ��Ʊ\n\n";
                        cout << "\t\t2.�鿴��Ʊ��Ϣ����Ʊ\n\n";
                        cout << "\t\t3.������һ��\n\n";
                        cout << "����������ѡ��";
                        cin >> q;
                        switch (q) {
                            case '1':
                                system("cls");
                            lb6:
                                cout << "\n**************��ѡ����Ҫ���еĲ���**************\n";
                                cout << "\n\t\t1.���뺽��Ų�ѯ\n\n";
                                cout << "\t\t2.������ɺͽ�����в�ѯ\n\n";
                                cout << "\t\t3.���뺽��Ż����ģ����ѯ\n\n";
                                cout << "\t\t4.������һ��\n\n";
                                cout << "����������ѡ��";
                                cin >> j;
                                switch (j) {
                                    case '1': {
                                        cout << "\n�����뺽��ţ�";
                                        cin >> TypeFliNo;
                                        if (SearchFliNo(TypeFliNo, soposi)) //���Բ��ҵ������Ϣ
                                        {
                                            cout << "\n���ҵ����º�����Ϣ��\n\n";
                                            //��ʾ��غ���
                                            ShowthisFli(soposi, 0);

                                            book(soposi, Nam); //��Ʊ�˵�
                                        } else {
                                            cout << "\n���޴˺��࣡���ڷ�����һ��...";
                                            sleepcp(1 * 1000);
                                            system("cls");
                                        }
                                        goto lb6;
                                    }
                                    case '2': {
                                        cout << "\n��������ɳ��У�";
                                        cin >> TypeDepartC;
                                        cout << "\n�����뽵����У�";
                                        cin >> TypeArrivC;
                                        if (SearchFliC(TypeDepartC, TypeArrivC, &theseposi, relatedFlin)) //���Բ��ҵ������Ϣ
                                        {
                                            cout << "\n���ҵ����º�����Ϣ��\n\n";
                                            for (int tempno = 0; tempno < relatedFlin; tempno++) {
                                                ShowthisFli(theseposi[tempno], tempno);
                                            }//��ʾ��غ���

                                            /* code */

                                            book(theseposi, relatedFlin, Nam); //��Ʊ�˵�
                                        } else {
                                            cout << "\n���޴˺��࣡";
                                            sleepcp(1 * 1000);
                                            system("cls");

                                        }
                                        goto lb6;
                                    }
                                    case '3': {
                                        string NoorCity;
                                        int FliRn;
                                        int *ReturnPosi;
                                        cout << "\n�����뺽��Ż��йس��У�";
                                        cin >> NoorCity;
                                        if (NoorCity.c_str()[0] < 0) {
                                            if (SearchFliRC(NoorCity, &ReturnPosi, FliRn)) {
                                                cout << "\n���ҵ����º�����Ϣ��\n\n";
                                                for (int tempno2 = 0; tempno2 < FliRn; tempno2++) {
                                                    ShowthisFli(ReturnPosi[tempno2], tempno2);
                                                }

                                                book(ReturnPosi, FliRn, Nam);
                                            } else {
                                                cout << "\n���޴˺��࣡";
                                                sleepcp(1 * 1000);
                                                system("cls");
                                            }
                                        } else {
                                            if (SearchFliNo(NoorCity, FliRn)) //���Բ��ҵ������Ϣ
                                            {
                                                cout << "\n���ҵ����º�����Ϣ��\n\n";
                                                //��ʾ��غ���
                                                ShowthisFli(FliRn, 0);

                                                book(FliRn, Nam); //��Ʊ�˵�
                                            } else {
                                                cout << "\n���޴˺��࣡���ڷ�����һ��...";
                                                sleepcp(1 * 1000);
                                                system("cls");
                                            }
                                        }
                                        goto lb6;
                                    }
                                    case '4': {//������һ��
                                        system("cls");
                                        goto lb4;
                                    }
                                    default: {//ѡ����������
                                        cout << "\n��������ȷѡ��";
                                        sleepcp(1 * 1000);
                                        system("cls");
                                        goto lb6;
                                    }
                                }
                            case '2':
                                int n;
                                if (BookUserExited(Nam, n)) {
                                    BookInfo thisUserbk;
                                    fstream bookinfo("bookinfo.dat", ios::in | ios::out | ios::binary);
                                    bookinfo.seekg((sizeof(int)) + (n * sizeof(BookInfo), ios::beg));
                                    bookinfo.read((char *) &thisUserbk, sizeof(BookInfo));

                                    if (thisUserbk.NumOfTPF > 0) {

                                        cout << "\n���Ķ�Ʊ��Ϣ���£�\n";
                                        showallBookinfo(thisUserbk);
                                        cout << "\n�Ƿ���Ҫ��Ʊ��(1.�ǣ�2.��) ";
                                        cin >> k;
                                        if (k == 1) {
                                            int TickNo;
                                            RetypeNo:
                                            cout << "��������Ҫ��Ʊ����ţ�";
                                            cin >> TickNo;
                                            if (TickNo <= thisUserbk.NumOfTPF + 1) {
                                                int RefundNum;
                                                RetypeTi:
                                                cout << "��������Ҫ��Ʊ��������";
                                                cin >> RefundNum;
                                                if (RefundNum < thisUserbk.tpf[TickNo - 1].Tickets) {
                                                    thisUserbk.tpf[TickNo - 1].Tickets -= RefundNum;
                                                    cout << "\n��Ʊ�ɹ���";
                                                    sleepcp(1 * 1000);
                                                    system("cls");
                                                } else if (RefundNum = thisUserbk.tpf[TickNo - 1].Tickets) {
                                                    for(int i=TickNo-1;i<thisUserbk.NumOfTPF;i++){
                                                        thisUserbk.tpf[i]=thisUserbk.tpf[i+1];
                                                    }
                                                    thisUserbk.NumOfTPF--;
                                                } else {
                                                    cout << "�˶����������Ѷ����������������룡" << endl;
                                                    goto RetypeTi;
                                                }
                                                int RefuPosi;
                                                Flight refufli;
                                                SearchFliNo(thisUserbk.tpf[TickNo - 1].FliNumber,RefuPosi);
                                                fstream fliinfo("flinfo.dat",ios::in|ios::out|ios::binary);
                                                fliinfo.seekg((sizeof(int)) + (RefuPosi * sizeof(Flight)));
                                                fliinfo.read((char*)&refufli,sizeof(Flight));
                                                refufli.ChangeSeatNum(refufli.ReturnSeats()+RefundNum);
                                                fliinfo.seekg((sizeof(int)) + (RefuPosi * sizeof(Flight)));
                                                fliinfo.write((char*)&refufli,sizeof(Flight));
                                                fliinfo.close();
                                                bookinfo.seekg((sizeof(int)) + (n * sizeof(BookInfo), ios::beg));
                                                bookinfo.write((char*)&thisUserbk,sizeof(BookInfo));
                                                bookinfo.close();
                                            } else {
                                                cout << "��Ų����ڣ���������ȷ��ţ�" << endl;
                                                goto RetypeNo;
                                            }
                                            goto lb2;
                                        } else if (k == 2) {
                                            system("cls");
                                            goto lb6;
                                        } else {
                                            system("cls");
                                            goto lb2;
                                        }
                                    }
                                }
                                cout<<"����δ����Ʊ��Ϊ��������һ��...";
                                system("cls");
                                goto lb4;
                            case '3': //������һ��
                                system("cls");
                                goto lb2;

                            default: //ѡ����������
                                cout << "\n��������ȷѡ��";
                                sleepcp(1 * 1000);
                                system("cls");
                                goto lb4;
                        }
                    } else //�����������򷵻�
                    {
                        cout << "\n������������µ�¼��";
                        goto lb2;
                    }
                    break;

                case '3': //������һ��
                    system("cls");
                    goto lb1;
                default: //ѡ����������
                    cout << "\n��������ȷѡ��";
                    sleepcp(1 * 1000);
                    system("cls");
                    goto lb2;
            }
            break;
        case '3': //�˳�����ϵͳ
            cout << "\n��ӭ�´�ʹ�ã��ټ���\n";
            sleepcp(1000);
            break;
        default: //ѡ����������
            cout << "\n��������ȷѡ��";
            sleepcp(1000);
            system("cls");
            goto lb1;
    }
}

int main() {
    int NumOfFlight = 0, NumOfUsers = 0, NumOfBookings = 0;
    fstream flightinfo("flinfo.dat", ios::in | ios::out | ios::binary);
    if (!flightinfo) {
        flightinfo.open("flinfo.dat", ios::out);
        flightinfo.close();
        flightinfo.open("flinfo.dat", ios::in | ios::out | ios::binary);
    }

    if (IfEmptyFile(flightinfo)) {
        flightinfo.write((char *) &NumOfFlight, sizeof(int));
    }
    flightinfo.close();

    fstream userinfo("userinfo.dat", ios::in | ios::out | ios::binary);
    if (!userinfo) {
        userinfo.open("userinfo.dat", ios::out);
        userinfo.close();
        userinfo.open("userinfo.dat", ios::in | ios::out | ios::binary);
    }
    if (IfEmptyFile(userinfo)) {
        userinfo.write((char *) &NumOfUsers, sizeof(int));
    }
    userinfo.close();

    fstream bookinfo("bookinfo.dat", ios::in | ios::out | ios::binary);
    if (!bookinfo) {
        bookinfo.open("bookinfo.dat", ios::out);
        bookinfo.close();
        bookinfo.open("bookinfo.dat", ios::in | ios::out | ios::binary);
    }
    if (IfEmptyFile(bookinfo)) {
        bookinfo.write((char *) &NumOfBookings, sizeof(int));
    }
    bookinfo.close();

    ui();

    system("pause");

    return 0;
}
