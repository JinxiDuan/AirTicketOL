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

void sleepcp(int milliseconds)
{ //跨平台sleep函数
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

class Flight
{
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
           double Pri)
    {
        strcpy_s(FlightNo, No.c_str());
        strcpy_s(CraftType, CraftT.c_str());
        strcpy_s(Departcity, Departc.c_str());
        strcpy_s(Arrivcity, Arrivc.c_str());
        strcpy_s(DepartTime, DepartT.c_str());
        strcpy_s(ArrivTime, ArrivT.c_str());
        SeatsNum = SeatsN;
        Price = Pri;
    }

    void Display()
    {
        cout << FlightNo << "  " << Departcity << "到" << Arrivcity << "  起飞：" << DepartTime << "  落地：" << ArrivTime
             << "  执飞：" << CraftType << "  余票：" << SeatsNum << "  " << Price << "元" << endl;
    }

    bool IfFlightNo(string Num)
    {
        if (FlightNo == Num)
            return true;
        else
            return false;
    }

    Status ChangeFlightNo(string Num)
    {
        if (Num.empty())
        {
            return ABNORMAL;
        }
        else
        {
            strcpy_s(FlightNo, Num.c_str());
            return OK;
        }
    }

    char *ReturnFliNO()
    {
        return FlightNo;
    }

    bool IfDepartCity(string City)
    {
        if (Departcity == City)
            return true;
        else
            return false;
    }

    Status ChangeDepartC(string City)
    {
        if (City.empty())
        {
            return ABNORMAL;
        }
        else
        {
            strcpy_s(Departcity, City.c_str());
            return OK;
        }
    }

    bool IfArrivCity(string City)
    {
        if (Arrivcity == City)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    Status ChangeArrivC(string City)
    {
        if (City.empty())
        {
            return ABNORMAL;
        }
        else
        {
            strcpy_s(Arrivcity, City.c_str());
            return OK;
        }
    }

    Status ChangeDepartT(string Time)
    {
        if (Time.empty())
        {
            return ABNORMAL;
        }
        else
        {
            strcpy_s(DepartTime, Time.c_str());
            return true;
        }
    }

    Status ChangeArrivalT(string Time)
    {
        if (Time.empty())
        {
            return ABNORMAL;
        }
        else
        {
            strcpy_s(ArrivTime, Time.c_str());
            return OK;
        }
    }

    Status ChangeCraftT(string craftT)
    {
        if (craftT.empty())
        {
            return ABNORMAL;
        }
        else
        {
            strcpy_s(CraftType, craftT.c_str());
            return OK;
        }
    }

    Status ChangeSeatNum(int seats)
    {
        if (seats < 0)
        {
            return ABNORMAL;
        }
        else
        {
            SeatsNum = seats;
            return OK;
        }
    }

    void Seatsplus()
    {
        SeatsNum++;
    }

    void Saeatsdec()
    {
        SeatsNum--;
    }

    int ReturnSeats()
    {
        return SeatsNum;
    }

    char *ReturnDepartC()
    {
        return Departcity;
    }

    char *ReturnArrivC()
    {
        return Arrivcity;
    }

    Status ChangePrice(double price)
    {
        if (price < 0)
        {
            return ABNORMAL;
        }
        else
        {
            Price = price;
            return OK;
        }
    }
};

class Customer
{
private:
    char username[20];
    char password[20];

public:
    Customer() {}

    Customer(string name, string passw)
    {
        strcpy_s(username, name.c_str());
        strcpy_s(password, passw.c_str());
    } //注册之前要检测用户名与密码长度是否合规
    bool Checkusername(string name)
    {
        //用户查重
        if (name == username)
            return true;
        else
            return false;
    }

    bool Checkpassword(string passw)
    {
        if (passw == password)
            return true;
        else

            return false;
    }

    Status Changepasswrd(string newpswd)
    {
        if (newpswd.empty())
        {
            return ABNORMAL;
        }
        else
        {
            strcpy_s(password, newpswd.c_str());
            return OK;
        }
    }

    Status ChangeUsername(string name)
    {
        if (name.empty())
        {
            return ABNORMAL;
        }
        else
        {
            strcpy_s(username, name.c_str());
            return OK;
        }
    }
};

typedef struct TicketsperFli
{
    char FliNumber[20];
    int Tickets;
} TPF;

typedef struct BookInfo
{
    char Username[20];
    TPF tpf[MAXSIZE];
    int NumOfTPF;
};

Status AddFlight()
{
    string FlightN, craftT, Departc, Arrivc, DepartT, ArrivT;
    int SeatsN = 0;
    double Pri = 0;
    cout << "请输入航班号：";
    cin >> FlightN;

    cout << "请输入起飞城市：";
    cin >> Departc;

    cout << "请输入降落城市：";
    cin >> Arrivc;

    cout << "请输入起飞时间：";
    cin >> DepartT;

    cout << "请输入到达时间：";
    cin >> ArrivT;

    cout << "请输入执飞机型：";
    cin >> craftT;

    cout << "请输入座位数：";
    cin >> SeatsN;

    cout << "请输入票价：";
    cin >> Pri;

    Flight fli1(FlightN, craftT, Departc, Arrivc, DepartT, ArrivT, SeatsN, Pri);

    fstream outfile("flinfo.dat", ios::binary | ios::out | ios::in);
    if (!outfile)
    {
        cerr << "打开出错!" << endl;
        abort(); //若文件不存在或文件满
    }

    int i = 0;
    outfile.seekg(0, ios::beg);
    outfile.read((char *)&i, sizeof(int));
    outfile.seekg(((sizeof(int)) + (i * sizeof(Flight))), ios::beg);

    fli1.Display(); //可删除
    outfile.write((char *)&fli1, sizeof(fli1));

    i++;
    outfile.seekg(0, ios::beg);
    outfile.write((char *)&i, sizeof(int)); //航班数加1
    outfile.seekg(0, ios::beg);
    outfile.read((char *)&i, sizeof(int));

    outfile.close();
    return OK;
}

Status ShowAllFli()
{
    Flight fli2;
    int NumOfFly = 0;
    ifstream infile("flinfo.dat", ios::binary | ios::in);
    if (!infile)
    {
        cerr << "打开出错!" << endl;
        abort();
    }
    infile.seekg(0, ios::beg);
    infile.read((char *)&NumOfFly, sizeof(int));
    if (NumOfFly == 0)
        return ABNORMAL;
    infile.seekg(sizeof(int), ios::beg);
    cout << "\n所有航班信息如下：\n\n";
    for (int i = 0; i < NumOfFly; i++)
    {
        infile.read((char *)&fli2, sizeof(Flight));
        cout << "   " << i + 1 << ".  ";
        fli2.Display();
        cout << endl;
    }
    infile.close();
    return OK;
}

bool IfEmptyFile(fstream &fstest)
{
    int i;
    fstest.seekg(0, ios::end);
    i = fstest.tellg();
    if (i == 0)
        return true;
    else
        return false;
}

bool CheckFliNum(int n)
{
    int i = 0;
    ifstream infile("flinfo.dat", ios::in | ios::binary);
    infile.read((char *)&i, sizeof(int));
    infile.close();
    if (n <= i)
        return true;
    else
        return false;
}

Status DeleteFli(int n)
{
    int i = 0, temp = 0;
    Flight *fli, flileft;
    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.read((char *)&i, sizeof(int));
    i--;
    fsfile.seekg(0, ios::beg);
    fsfile.write((char *)&i, sizeof(int)); //使得保存在文件中记录航班数量的int类型减一
    if ((i + 1) == n)
    {
        fsfile.close();
        return OK;
    }
    else
    {
        fli = new Flight[i + 1];
        fsfile.seekg(sizeof(int), ios::beg);

        for (int k = 0; k < i + 1; k++)
        {
            fsfile.read((char *)&fli[temp], sizeof(Flight));
            temp++;
        } //将整个序列读取到数组中

        fsfile.seekg(sizeof(int), ios::beg);

        for (int j = 0; j < i + 1; j++)
        {
            //fli[j].Display();
            if (j == n - 1)
                continue;
            fsfile.write((char *)&fli[j], sizeof(Flight));
        }               //将数组中的数据截断输入到文件中
        delete[] fli;   //释放临时数组
        fsfile.close(); //关闭文件
        return OK;
    }
}

Status ModifyDepartC(int n)
{
    Flight fli2;
    string DepartC;
    n--;
    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.read((char *)&fli2, sizeof(Flight));
    cout << "请输入需要替换为的起飞城市:";
    cin >> DepartC;
    fli2.ChangeDepartC(DepartC);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.write((char *)&fli2, sizeof(Flight));
    return OK;
}

Status ModifyLandC(int n)
{
    Flight fli2;
    string LandC;
    n--;
    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.read((char *)&fli2, sizeof(Flight));
    cout << "请输入需要替换为的降落城市:";
    cin >> LandC;
    fli2.ChangeArrivC(LandC);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.write((char *)&fli2, sizeof(Flight));
    return OK;
}

Status ModifyCraft(int n)
{
    Flight fli2;
    string CraftT;
    n--;
    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.read((char *)&fli2, sizeof(Flight));
    cout << "请输入需要替换为的执飞机型:";
    cin >> CraftT;
    fli2.ChangeCraftT(CraftT);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.write((char *)&fli2, sizeof(Flight));
    return OK;
}

Status ModifyPrice(int n)
{
    Flight fli2;
    double Pri;
    n--;
    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.read((char *)&fli2, sizeof(Flight));
    cout << "请输入更改后的价格:";
    cin >> Pri;
    fli2.ChangePrice(Pri);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.write((char *)&fli2, sizeof(Flight));
    return OK;
}

Status ModifyTime(int n)
{
    Flight fli2;
    string DepartT, ArrivT;
    n--;
    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.read((char *)&fli2, sizeof(Flight));
    cout << "请输入更改后的的起飞时间:";
    cin >> DepartT;
    cout << "请输入更改后的的降落时间:";
    cin >> ArrivT;
    fli2.ChangeDepartT(DepartT);
    fli2.ChangeArrivalT(ArrivT);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.write((char *)&fli2, sizeof(Flight));
    return OK;
}

Status ModifyFliNo(int n)
{
    Flight fli2;
    string FliNo;
    n--;
    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.read((char *)&fli2, sizeof(Flight));
    cout << "请输入更改后的航班号:";
    cin >> FliNo;
    fli2.ChangeFlightNo(FliNo);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.write((char *)&fli2, sizeof(Flight));
    return OK;
}

Status ModifySeats(int n)
{
    Flight fli2;
    int Seats;
    n--;
    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.read((char *)&fli2, sizeof(Flight));
    cout << "请输入更改后的座位数:";
    cin >> Seats;
    fli2.ChangeSeatNum(Seats);
    fsfile.seekg((sizeof(int)) + (n * sizeof(Flight)), ios::beg);
    fsfile.write((char *)&fli2, sizeof(Flight));
    return OK;
}

bool CheckSameName(string name, int &loca)
{
    int n;
    Customer cus;
    fstream user("userinfo.dat", ios::in | ios::out | ios::binary);
    user.seekg(0, ios::beg);
    user.read((char *)&n, sizeof(int));
    if (n == 0)
    {
        user.close();
        return false;
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            user.read((char *)&cus, sizeof(cus));
            if (cus.Checkusername(name))
            {
                loca = i;
                user.close();
                return true;
            }
        }
        user.close();
        return false;
    }
}

Status RegisterUser(string name, string password)
{
    int i = 0;
    Customer cus(name, password);
    fstream user("userinfo.dat", ios::in | ios::out | ios::binary);
    user.seekg(0, ios::beg);
    user.read((char *)&i, sizeof(int));

    user.seekg(((sizeof(int)) + (i * sizeof(Customer))), ios::beg);
    user.write((char *)&cus, sizeof(Customer)); //写入用户

    i++;
    user.seekg(0, ios::beg);
    user.write((char *)&i, sizeof(int)); //用户数加一
    user.close();
    return OK;
} //注册之前要检测用户名与密码长度是否合规

bool Login(int n, string password)
{
    Customer cuser;
    fstream user("userinfo.dat", ios::in | ios::out | ios::binary);
    user.seekg(((sizeof(int)) + (n * sizeof(Customer))), ios::beg);
    user.read((char *)&cuser, sizeof(Customer));
    if (cuser.Checkpassword(password))
    {
        user.close();
        return true;
    }
    else
    {
        user.close();
        return false;
    }
}

bool SearchFliNo(string FliNo, int &theposi)
{
    int i;
    Flight tempfli;
    fstream fliserch("flinfo.dat", ios::in | ios::out | ios::binary);
    fliserch.seekg(0, ios::beg);
    fliserch.read((char *)&i, sizeof(int));
    for (int j = 0; j <= i; j++)
    {
        fliserch.read((char *)&tempfli, sizeof(Flight));
        if (tempfli.IfFlightNo(FliNo))
        {
            theposi = j;
            fliserch.close();
            return true;
        }
    }
    fliserch.close();
    return false;
}

bool SearchFliC(string Departc, string Arrivc, int **Fliarr, int &n)
{
    int i = 0;
    n = 0;
    Flight tempfli;
    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.seekg(0, ios::beg);
    fsfile.read((char *)&i, sizeof(int));
    *Fliarr = new int[i];
    for (int j = 0; j < i; j++)
    {
        fsfile.read((char *)&tempfli, sizeof(Flight));
        if (tempfli.IfDepartCity(Departc) && tempfli.IfArrivCity(Arrivc))
        {
            *(*Fliarr + n) = j;
            n++;
        }
    }

    if (n > 0)
    {
        fsfile.close();
        return true;
    }
    else
    {
        fsfile.close();
        return false;
    }
}

bool SearchFliRC(string City, int **Fliarr, int &n)
{
    int i = 0;
    n = 0;
    Flight tempfli;
    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.seekg(0, ios::beg);
    fsfile.read((char *)&i, sizeof(int));
    *Fliarr = new int[i];
    for (int j = 0; j < i; j++)
    {
        fsfile.read((char *)&tempfli, sizeof(Flight));
        if (tempfli.IfDepartCity(City) || tempfli.IfArrivCity(City))
        {
            *(*Fliarr + n) = j;
            n++;
        }
    }
    if (n > 0)
    {
        fsfile.close();
        return true;
    }
    else
    {
        fsfile.close();
        return false;
    }
}

void ShowthisFli(int posi, int n)
{
    Flight fli;
    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.seekg((sizeof(int)) + (posi * sizeof(Flight)), ios::beg);
    fsfile.read((char *)&fli, sizeof(Flight));
    cout << "  " << n + 1 << ".  ";
    fli.Display();
    fsfile.close();
}

void ShowthisFli(int posi, int n, string fliNo)
{
    Flight fli;

    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);

    fsfile.seekg((sizeof(int)) + (posi * sizeof(Flight)), ios::beg);

    fsfile.read((char *)&fli, sizeof(Flight));

    if (fli.ReturnFliNO() == fliNo)
    {
        cout << "  " << n + 1 << ".  ";
        fli.Display();
        fsfile.close();
    }
    else
    {
        return;
    }
}

static void inputPassword(string &str, int size)
{
    //隐藏密码实现
    size++;
    char c;
    int count = 0;
    char *password = new char[size]; // 动态申请空间
    while ((c = _getch()) != '\r')
    {

        if (c == 8)
        {
            // 退格
            if (count == 0)
            {
                continue;
            }
            putchar('\b'); // 回退一格
            putchar(' ');  // 输出一个空格将原来的*隐藏
            putchar('\b'); // 再回退一格等待输入
            count--;
        }

        if (count == size - 1)
        {
            // 最大长度为size-1
            continue;
        }

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
        {
            // 密码只可包含数字和字母
            putchar('*'); // 接收到一个字符后, 打印一个*
            password[count] = c;
            count++;
        }
    }
    password[count] = '\0';
    str = password;
    delete[] password; // 释放空间
    cout << endl;
}

bool BookUserExited(string username, int &userposi)
{
    int allbooknum = 0;
    BookInfo bkif;
    fstream bookinfo("bookinfo.dat", ios::in | ios::out | ios::binary); //打开预定文件
    bookinfo.seekg(0, ios::beg);
    bookinfo.read((char *)&allbooknum, sizeof(int)); //读取预定数量
    for (int i = 0; i < allbooknum; i++)
    {
        //逐个检验
        bookinfo.read((char *)&bkif, sizeof(BookInfo));
        if (username == bkif.Username)
        {
            bookinfo.close();
            userposi = i;
            return true;
        }
    }
    bookinfo.close();
    userposi = -1;
    return false;
}

bool BookNoExited(BookInfo bkif, string fliNo, int &tpfposi)
{
    for (int i = 0; i < bkif.NumOfTPF; i++)
    {
        if (bkif.tpf[i].FliNumber == fliNo)
        {
            tpfposi = i;
            return true;
        }
    }
    tpfposi = -1;
    return false;
}

void book(int *thisposi, int n, string username);

void book(int thisposi, string username)
{ //订票菜单
    BookInfo bookhere;
    int NumOfTicbked = 0;
    int bookn = 0;
    int sentinel = 0;
    int *thesePosi;
    Flight fli;
    char whether;
    cout << "\n是否订票？[Y/N]:";
    cin >> whether;
    while (sentinel == 0)
    {
        if (whether == 'Y' || whether == 'y')
        {
            sentinel = 1;
        }
        else if (whether == 'N' || whether == 'n')
        {
            cout << "正在返回上一步..." << endl;
            return;
        }
        else
        {
            cout << "输入错误，请重新输入:";
            cin >> whether;
        }
    }
    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.seekg((sizeof(int)) + (thisposi * sizeof(Flight)), ios::beg);
    fsfile.read((char *)&fli, sizeof(Flight));
    cout << "请输入订票张数：";
    cin >> NumOfTicbked;
    if (fli.ReturnSeats() >= NumOfTicbked)
    { //有余票

        int ExitedBookposi; //存在的用户预定位置
        if (BookUserExited(username, ExitedBookposi))
        {
            //用户之前预定过票
            BookInfo bkif2;
            int TPFposi;
            fstream bookinfo("bookinfo.dat", ios::in | ios::out | ios::binary);
            bookinfo.seekg((sizeof(int)) + (ExitedBookposi * sizeof(BookInfo)), ios::beg);
            bookinfo.read((char *)&bkif2, sizeof(BookInfo));
            if (BookNoExited(bkif2, fli.ReturnFliNO(), TPFposi))
            {
                //用户之前预定过该趟航班
                for (int i = 0; i < NumOfTicbked; i++)
                {
                    bkif2.tpf[TPFposi].Tickets++;
                    fli.Saeatsdec();
                }
            }
            else
            {
                //用户未预定过该趟航班
                strcpy_s(bkif2.tpf[NumOfTicbked].FliNumber, fli.ReturnFliNO());
                bkif2.tpf[NumOfTicbked].Tickets = NumOfTicbked;
                fli.ChangeSeatNum(fli.ReturnSeats() - NumOfTicbked);
            }
            fsfile.seekg((sizeof(int)) + (thisposi * sizeof(Flight)), ios::beg);
            fsfile.write((char *)&fli, sizeof(Flight));
            fsfile.close();
            bookinfo.seekg((sizeof(int)) + (ExitedBookposi * sizeof(BookInfo)), ios::beg);
            bookinfo.write((char *)&bkif2, sizeof(BookInfo));
            bookinfo.close();
        }
        else
        {
            //该用户之前未使用过预定系统
            strcpy_s(bookhere.Username, username.c_str());
            strcpy_s(bookhere.tpf[0].FliNumber, fli.ReturnFliNO());
            bookhere.tpf[0].Tickets = NumOfTicbked;
            bookhere.NumOfTPF = 1;
            fli.ChangeSeatNum(fli.ReturnSeats() - NumOfTicbked);

            fstream bookinfo("bookinfo.dat", ios::in | ios::binary | ios::out);

            bookinfo.seekg(0, ios::beg);
            bookinfo.read((char *)&bookn, sizeof(int));

            bookinfo.seekg(0, ios::end);
            bookinfo.write((char *)&bookhere, sizeof(BookInfo));

            bookn++;
            bookinfo.seekg(0, ios::beg);
            bookinfo.write((char *)&bookn, sizeof(int));
            fsfile.seekg((sizeof(int)) + (thisposi * sizeof(Flight)), ios::beg);
            fsfile.write((char *)&fli, sizeof(Flight));
            fsfile.close();
            bookinfo.close();
        }
        cout << "\n订票成功!";
    }
    else
    { //无余票
        Flight flihere;
        string DepartC, ArrivC;
        int n = 0;
        DepartC = fli.ReturnDepartC();
        ArrivC = fli.ReturnArrivC();
        SearchFliC(DepartC, ArrivC, &thesePosi, n);
        cout << "\n为您推荐以下同起降城市航班：\n\n";

        for (int tempno = 0; tempno < n; tempno++)
        {
            ShowthisFli(thesePosi[tempno], tempno, fli.ReturnFliNO());
        }
        fsfile.close();
        book(thesePosi, n, username);
    }
}

void book(int *thisposi, int n, string username)
{ //多种票类订票菜单
    Flight flirsrved;
    BookInfo bookinfo;
    int BookNo;
    int NumOfTicbked;
    int ExitedBookposi;
    char whether;
    int sentinel = 0;
    cout << "\n是否订票？[Y/N]:";
    cin >> whether;
    while (sentinel == 0)
    {
        if (whether == 'Y' || whether == 'y')
        {
            sentinel = 1;
        }
        else if (whether == 'N' || whether == 'n')
        {
            cout << "正在返回上一步..." << endl;
            return;
        }
        else
        {
            cout << "输入错误，请重新输入:";
            cin >> whether;
        }
    }
retry:
    cout << "\n请输入需要订票的序号：";
    cin >> BookNo;
    BookNo--; //序号为实际位置-1

    cout << "请输入订票张数：";
    cin >> NumOfTicbked;

    fstream fsfile("flinfo.dat", ios::in | ios::out | ios::binary);
    fsfile.seekg((sizeof(int)) + (thisposi[BookNo] * sizeof(Flight)), ios::beg);
    fsfile.read((char *)&flirsrved, sizeof(Flight));

    //    strcpy_s(bookinfo.Username, username.c_str());
    //    strcpy_s(bookinfo.tpf[0].FliNumber, flirsrved.ReturnFliNO());
    //    bookinfo.tpf[0].Tickets = NumOfTicbked;

    if (flirsrved.ReturnSeats() >= NumOfTicbked)
    { //有余票
        fstream bookinfo("bookinfo.dat", ios::in | ios::out | ios::binary);
        if (BookUserExited(username, ExitedBookposi))
        { //用户使用过预定系统
            BookInfo bkif2;
            int TPFposi;
            bookinfo.seekg((sizeof(int)) + (ExitedBookposi * sizeof(BookInfo)), ios::beg);
            bookinfo.read((char *)&bkif2, sizeof(BookInfo));
            if (BookNoExited(bkif2, flirsrved.ReturnFliNO(), TPFposi))
            {
                for (int i = 0; i < NumOfTicbked; i++)
                {
                    bkif2.tpf[TPFposi].Tickets++;
                    flirsrved.Saeatsdec();
                }
            }
            else
            {
                strcpy_s(bkif2.tpf[NumOfTicbked].FliNumber, flirsrved.ReturnFliNO());
                bkif2.tpf[NumOfTicbked].Tickets = NumOfTicbked;
                flirsrved.ChangeSeatNum(flirsrved.ReturnSeats() - NumOfTicbked);
            }
            fsfile.seekg((sizeof(int)) + (thisposi[BookNo] * sizeof(Flight)), ios::beg);
            fsfile.write((char *)&flirsrved, sizeof(Flight));
            fsfile.close();
            bookinfo.seekg((sizeof(int)) + (ExitedBookposi * sizeof(BookInfo)), ios::beg);
            bookinfo.write((char *)&bkif2, sizeof(BookInfo));
            bookinfo.close();
        }
        else
        {
            BookInfo bookhere;
            strcpy_s(bookhere.Username, username.c_str());
            strcpy_s(bookhere.tpf[0].FliNumber, flirsrved.ReturnFliNO());
            bookhere.tpf[0].Tickets = NumOfTicbked;
            bookhere.NumOfTPF = 1;
            flirsrved.ChangeSeatNum(flirsrved.ReturnSeats() - NumOfTicbked);

            bookinfo.seekg(0, ios::beg);
            int bookn;
            bookinfo.read((char *)&bookn, sizeof(int));

            bookinfo.seekg(0, ios::end);
            bookinfo.write((char *)&bookhere, sizeof(BookInfo));

            bookn++;
            bookinfo.seekg(0, ios::beg);
            bookinfo.write((char *)&bookn, sizeof(int));
            fsfile.seekg((sizeof(int)) + (thisposi[BookNo] * sizeof(Flight)), ios::beg);
            fsfile.write((char *)&flirsrved, sizeof(Flight));
            fsfile.close();
            bookinfo.close();
        }

        cout << "\n订票成功!";
    }
    else
    { //无余票
        sentinel = 0;
        cout << "\n您选择的航班余票暂时不足，是否选择列表内其他航班[Y/N]\n\n";
        while (sentinel == 0)
        {
            if (whether == 'Y' || whether == 'y')
            {
                goto retry;
            }
            else if (whether == 'N' || whether == 'n')
            {
                cout << "正在返回上一步..." << endl;
                return;
            }
            else
            {
                cout << "输入错误，请重新输入:";
                cin >> whether;
            }
        }
    }
}

bool showallBookinfo(BookInfo userbk)
{
    int posi;
    for (int i = 0; i < userbk.NumOfTPF; i++)
    {
        SearchFliNo(userbk.tpf[i].FliNumber, posi);
        ShowthisFli(posi, i);
        cout << " 您已订票" << userbk.tpf[i].Tickets << "张";
    }
}

void ui()
{ //菜单UI
    string TypeFliNo, TypeDepartC, TypeArrivC;
    int Fnum = 0, posi1 = 0, posi2 = 0, lastposi = 0, soposi = 0, relatedFlin = 0, *theseposi;
    char m, n, p, q, i, j, k;
    string Nam, newNam;
    string Passwd, newPasswd;
    string defAdmPasswd = "666666"; //管理员默认密码666666

lb1:
    cout << endl;
    cout << "          @@     @@      @@    @@@@@@@@@    @@@@@@@@@@\n";
    cout << "          @@     @@      @@    @@           @@        \n";
    cout << "          @@     @@      @@    @@           @@        \n";
    cout << "          @@     @@      @@    @@@@@@@@@    @@@@@@@@@ \n";
    cout << "          @@     @@      @@    @@           @@        \n";
    cout << "    @@    @@      @@    @@     @@           @@        \n";
    cout << "     @@@@@@        @@@@@@      @@           @@@@@@@@@@\n";
    cout << "\n               欢迎进入酱菜航空订票系统！\n";
    cout << "\n********************请选择用户身份********************\n";
    cout << "\n\t\t1.管理员登录\n\n";
    cout << "\t\t2.乘客登录\n\n";
    cout << "\t\t3.退出该系统\n\n";
    cout << "请输入您的选择：";
    cin >> m;
    switch (m)
    {
    case '1': //管理员身份

        cout << "\n请输入管理员密码："; //输入管理员默认密码666666
        inputPassword(Passwd, 20);

        if (Passwd == defAdmPasswd)
        { //密码正确
            cout << "\n登录成功！正在进入管理员菜单...\n\n";
            sleepcp(1000);
            system("cls"); //清屏

        lb3:
            cout << "\n            【酱菜航空订票系统-管理员菜单】\n";
            cout << "\n*****************请选择您要进行的操作*****************\n";
            cout << "\n\t\t1.查看所有航班信息或修改\n\n";
            cout << "\t\t2.增添航班信息\n\n";
            cout << "\t\t3.返回上一步\n\n";
            cout << "请输入您的选择：";
            cin >> p;
            switch (p)
            {
            case '1':
                //打印所有航班信息
                if (ShowAllFli() == -1)
                {
                    cout << "无航班信息！请重新输入。";
                    sleepcp(2000);
                    system("cls");
                    goto lb3;
                }

                cout << "\n请输如需要进行操作的序号：";
                //int Fnum = 0;
                cin >> Fnum;

                if (CheckFliNum(Fnum))
                {
                    //system("cls");
                    cout << "\n*****************请选择您要修改或删除的操作*****************\n";
                    cout << "\n\t\t1.删除航班\n\n";
                    cout << "\t\t2.修改航班起飞城市\n\n";
                    cout << "\t\t3.修改航班降落城市\n\n";
                    cout << "\t\t4.修改机型\n\n";
                    cout << "\t\t5.修改机票价格\n\n";
                    cout << "\t\t6.修改起降时间\n\n";
                    cout << "\t\t7.修改航班号\n\n";
                    cout << "\t\t8.修改剩余座位\n\n";
                    cout << "\t\t9.返回上一步\n\n";
                    cout << "请输入您的选择：";
                    cin >> i;
                    switch (i)
                    {
                    case '1':
                        DeleteFli(Fnum);
                        cout << "\n删除成功！正在返回管理员菜单...";
                        sleepcp(1 * 1000);
                        system("cls");
                        goto lb3;

                    case '2':
                        ModifyDepartC(Fnum);
                        cout << "\n修改成功！正在返回管理员菜单...";
                        sleepcp(1 * 1000);
                        system("cls");
                        goto lb3;

                    case '3':
                        ModifyLandC(Fnum);
                        cout << "\n修改成功！正在返回管理员菜单...";
                        sleepcp(1 * 1000);
                        system("cls");
                        goto lb3;

                    case '4':
                        ModifyCraft(Fnum);
                        cout << "\n修改成功！正在返回管理员菜单...";
                        sleepcp(1 * 1000);
                        system("cls");
                        goto lb3;

                    case '5':
                        ModifyPrice(Fnum);
                        cout << "\n修改成功！正在返回管理员菜单...";
                        sleepcp(1 * 1000);
                        system("cls");
                        goto lb3;

                    case '6':
                        ModifyTime(Fnum);
                        cout << "\n修改成功！正在返回管理员菜单...";
                        sleepcp(1 * 1000);
                        system("cls");
                        goto lb3;

                    case '7':
                        ModifyFliNo(Fnum);
                        cout << "\n修改成功！正在返回管理员菜单...";
                        sleepcp(1 * 1000);
                        system("cls");
                        goto lb3;

                    case '8':
                        ModifySeats(Fnum);
                        cout << "\n修改成功！正在返回管理员菜单...";
                        sleepcp(1 * 1000);
                        system("cls");
                        goto lb3;

                    case '9': //返回上一步
                        system("cls");
                        goto lb3;

                    default:
                        cout << "\n请输入正确选择！";
                        sleepcp(1 * 1000);
                        system("cls");
                        goto lb3;
                    }
                }
                //如果航班序号输入有误，回到之前
                else
                {
                    cout << "\n请输入正确的航班序号！";
                    sleepcp(2000);
                    system("cls");
                    goto lb3;
                }

            case '2': //增添航班信息
                AddFlight();

                cout << "\n航班信息录入成功！即将返回管理员菜单！";
                sleepcp(2000);
                system("cls");
                goto lb3;

            case '3': //返回上一步，即最开始
                system("cls");
                goto lb1;

            default: //选项输入有误
                cout << "\n请输入正确选择！";
                sleepcp(1 * 1000);
                system("cls");
                goto lb3;
            }
        }
        else
        { //密码错误
            cout << "\n密码错误！ 请重新登录！\n";
            sleepcp(2000);
            system("cls");
            goto lb1;
        }

    case '2': //乘客身份
        system("cls");
    lb2:
        cout << "\n             【酱菜航空订票系统-乘客菜单】\n";
        cout << "\n*****************请选择您要进行的操作*****************\n";
        cout << "\n\t\t1.注册新用户\n\n";
        cout << "\t\t2.已有账户登录\n\n";
        cout << "\t\t3.返回上一步\n\n";

        cout << "请输入您的选择：";
        cin >> n;
        switch (n)
        {
        case '1':
        ReRegis:
            cout << "\n请输入新用户名:";
            cin >> newNam;
            if (CheckSameName(newNam, posi1))
            {
                cout << "账户已存在，请选择：（1.直接登录或2.更换用户名）";
                int Choice = 0;
                cin >> Choice;
                if (Choice == 1)
                {
                    lastposi = posi1;
                    goto DirecLog;
                }
                else
                {
                    goto ReRegis;
                }
            }
            cout << "\n请输入新密码:";
            inputPassword(newPasswd, 20);
            RegisterUser(newNam, newPasswd);
            cout << "\n注册成功！正在返回乘客登录界面。\n";
            sleepcp(3000);
            system("cls");
            goto lb2;

        case '2':
        Relog:
            cout << "\n请输入用户名:";
            cin >> Nam;
            //查找文件是否有此人用户名，有则继续
            /* code */
            if (!CheckSameName(Nam, posi2))
            { //如果没有该用户名则打印未注册，并回到之前
                cout << "\n该用户未注册！请选择：（1.注册新账号或2.重新输入用户名）";
                int Choi2 = 0;
                cin >> Choi2;
                if (Choi2 == 1)
                {
                    goto ReRegis;
                }
                else
                {
                    goto Relog;
                }
            }
            else
            {
                lastposi = posi2;
            }
        DirecLog:
            cout << "\n请输入密码:";
            inputPassword(Passwd, 20);
            //判断密码正误
            /* code */
            if (Login(lastposi, Passwd))
            { //如果密码正确，则登录成功
                cout << "\n登录成功！\n\n";
                sleepcp(1 * 1000);
                system("cls");
            lb4:
                cout << "\n**************请选择您要进行的操作**************\n";
                cout << "\n\t\t1.查询航班信息或订票\n\n";
                cout << "\t\t2.查看订票信息或退票\n\n";
                cout << "\t\t3.返回上一步\n\n";
                cout << "请输入您的选择：";
                cin >> q;
                switch (q)
                {
                case '1':
                    system("cls");
                lb6:
                    cout << "\n**************请选择您要进行的操作**************\n";
                    cout << "\n\t\t1.输入航班号查询\n\n";
                    cout << "\t\t2.输入起飞和降落城市查询\n\n";
                    cout << "\t\t3.输入航班号或城市模糊查询\n\n";
                    cout << "\t\t4.返回上一步\n\n";
                    cout << "请输入您的选择：";
                    cin >> j;
                    switch (j)
                    {
                    case '1':
                    {
                        cout << "\n请输入航班号：";
                        cin >> TypeFliNo;
                        if (SearchFliNo(TypeFliNo, soposi))
                        { //可以查找到相关信息
                            cout << "\n查找到以下航班信息：\n\n";
                            //显示相关航班
                            ShowthisFli(soposi, 0);

                            book(soposi, Nam); //订票菜单
                        }
                        else
                        {
                            cout << "\n查无此航班！正在返回上一步...";
                            sleepcp(1 * 1000);
                            system("cls");
                        }
                        goto lb6;
                    }
                    case '2':
                    {
                        cout << "\n请输入起飞城市：";
                        cin >> TypeDepartC;
                        cout << "\n请输入降落城市：";
                        cin >> TypeArrivC;
                        if (SearchFliC(TypeDepartC, TypeArrivC, &theseposi, relatedFlin))
                        { //可以查找到相关信息
                            cout << "\n查找到以下航班信息：\n\n";
                            for (int tempno = 0; tempno < relatedFlin; tempno++)
                            {
                                ShowthisFli(theseposi[tempno], tempno);
                            } //显示相关航班

                            /* code */

                            book(theseposi, relatedFlin, Nam); //订票菜单
                        }
                        else
                        {
                            cout << "\n查无此航班！";
                            sleepcp(1 * 1000);
                            system("cls");
                        }
                        goto lb6;
                    }
                    case '3':
                    {
                        string NoorCity;
                        int FliRn;
                        int *ReturnPosi;
                        cout << "\n请输入航班号或有关城市：";
                        cin >> NoorCity;
                        if (NoorCity.c_str()[0] < 0)
                        {
                            if (SearchFliRC(NoorCity, &ReturnPosi, FliRn))
                            {
                                cout << "\n查找到以下航班信息：\n\n";
                                for (int tempno2 = 0; tempno2 < FliRn; tempno2++)
                                {
                                    ShowthisFli(ReturnPosi[tempno2], tempno2);
                                }

                                book(ReturnPosi, FliRn, Nam);
                            }
                            else
                            {
                                cout << "\n查无此航班！";
                                sleepcp(1 * 1000);
                                system("cls");
                            }
                        }
                        else
                        {
                            if (SearchFliNo(NoorCity, FliRn))
                            { //可以查找到相关信息
                                cout << "\n查找到以下航班信息：\n\n";
                                //显示相关航班
                                ShowthisFli(FliRn, 0);

                                book(FliRn, Nam); //订票菜单
                            }
                            else
                            {
                                cout << "\n查无此航班！正在返回上一步...";
                                sleepcp(1 * 1000);
                                system("cls");
                            }
                        }
                        goto lb6;
                    }
                    case '4':
                    {
                        //返回上一步
                        system("cls");
                        goto lb4;
                    }
                    default:
                    {
                        //选项输入有误
                        cout << "\n请输入正确选择！";
                        sleepcp(1 * 1000);
                        system("cls");
                        goto lb6;
                    }
                    }
                case '2':
                    int n;
                    if (BookUserExited(Nam, n))
                    {
                        BookInfo thisUserbk;
                        fstream bookinfo("bookinfo.dat", ios::in | ios::out | ios::binary);
                        bookinfo.seekg((sizeof(int)) + (n * sizeof(BookInfo), ios::beg));
                        bookinfo.read((char *)&thisUserbk, sizeof(BookInfo));

                        if (thisUserbk.NumOfTPF > 0)
                        {

                            cout << "\n您的订票信息如下：\n";
                            showallBookinfo(thisUserbk);
                            cout << "\n是否需要退票？(1.是；2.否) ";
                            cin >> k;
                            if (k == 1)
                            {
                                int TickNo;
                            RetypeNo:
                                cout << "请输入您要退票的序号：";
                                cin >> TickNo;
                                if (TickNo <= thisUserbk.NumOfTPF + 1)
                                {
                                    int RefundNum;
                                RetypeTi:
                                    cout << "请输入需要退票的张数：";
                                    cin >> RefundNum;
                                    if (RefundNum < thisUserbk.tpf[TickNo - 1].Tickets)
                                    {
                                        thisUserbk.tpf[TickNo - 1].Tickets -= RefundNum;
                                        cout << "\n退票成功！";
                                        sleepcp(1 * 1000);
                                        system("cls");
                                    }
                                    else if (RefundNum = thisUserbk.tpf[TickNo - 1].Tickets)
                                    {
                                        for (int i = TickNo - 1; i < thisUserbk.NumOfTPF; i++)
                                        {
                                            thisUserbk.tpf[i] = thisUserbk.tpf[i + 1];
                                        }
                                        thisUserbk.NumOfTPF--;
                                    }
                                    else
                                    {
                                        cout << "退订张数大于已定数量，请重新输入！" << endl;
                                        goto RetypeTi;
                                    }
                                    int RefuPosi;
                                    Flight refufli;
                                    SearchFliNo(thisUserbk.tpf[TickNo - 1].FliNumber, RefuPosi);
                                    fstream fliinfo("flinfo.dat", ios::in | ios::out | ios::binary);
                                    fliinfo.seekg((sizeof(int)) + (RefuPosi * sizeof(Flight)));
                                    fliinfo.read((char *)&refufli, sizeof(Flight));
                                    refufli.ChangeSeatNum(refufli.ReturnSeats() + RefundNum);
                                    fliinfo.seekg((sizeof(int)) + (RefuPosi * sizeof(Flight)));
                                    fliinfo.write((char *)&refufli, sizeof(Flight));
                                    fliinfo.close();
                                    bookinfo.seekg((sizeof(int)) + (n * sizeof(BookInfo), ios::beg));
                                    bookinfo.write((char *)&thisUserbk, sizeof(BookInfo));
                                    bookinfo.close();
                                }
                                else
                                {
                                    cout << "序号不存在，请输入正确序号！" << endl;
                                    goto RetypeNo;
                                }
                                goto lb2;
                            }
                            else if (k == 2)
                            {
                                system("cls");
                                goto lb6;
                            }
                            else
                            {
                                system("cls");
                                goto lb2;
                            }
                        }
                    }
                    cout << "您还未定过票，为您返回上一步...";
                    system("cls");
                    goto lb4;
                case '3': //返回上一步
                    system("cls");
                    goto lb2;

                default: //选项输入有误
                    cout << "\n请输入正确选择！";
                    sleepcp(1 * 1000);
                    system("cls");
                    goto lb4;
                }
            }
            else
            { //如果密码错误，则返回
                cout << "\n密码错误！请重新登录。";
                goto lb2;
            }
            break;

        case '3': //返回上一步
            system("cls");
            goto lb1;
        default: //选项输入有误
            cout << "\n请输入正确选择！";
            sleepcp(1 * 1000);
            system("cls");
            goto lb2;
        }
        break;
    case '3': //退出航空系统
        cout << "\n欢迎下次使用！再见。\n";
        sleepcp(1000);
        break;
    default: //选项输入有误
        cout << "\n请输入正确选择！";
        sleepcp(1000);
        system("cls");
        goto lb1;
    }
}

int main()
{
    int NumOfFlight = 0, NumOfUsers = 0, NumOfBookings = 0;
    fstream flightinfo("flinfo.dat", ios::in | ios::out | ios::binary);
    if (!flightinfo)
    {
        flightinfo.open("flinfo.dat", ios::out);
        flightinfo.close();
        flightinfo.open("flinfo.dat", ios::in | ios::out | ios::binary);
    }

    if (IfEmptyFile(flightinfo))
    {
        flightinfo.write((char *)&NumOfFlight, sizeof(int));
    }
    flightinfo.close();

    fstream userinfo("userinfo.dat", ios::in | ios::out | ios::binary);
    if (!userinfo)
    {
        userinfo.open("userinfo.dat", ios::out);
        userinfo.close();
        userinfo.open("userinfo.dat", ios::in | ios::out | ios::binary);
    }
    if (IfEmptyFile(userinfo))
    {
        userinfo.write((char *)&NumOfUsers, sizeof(int));
    }
    userinfo.close();

    fstream bookinfo("bookinfo.dat", ios::in | ios::out | ios::binary);
    if (!bookinfo)
    {
        bookinfo.open("bookinfo.dat", ios::out);
        bookinfo.close();
        bookinfo.open("bookinfo.dat", ios::in | ios::out | ios::binary);
    }
    if (IfEmptyFile(bookinfo))
    {
        bookinfo.write((char *)&NumOfBookings, sizeof(int));
    }
    bookinfo.close();

    ui();

    system("pause");

    return 0;
}
