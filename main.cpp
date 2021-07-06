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

void sleepcp(int milliseconds) //跨平台sleep函数
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
        strcpy(FlightNo, No.c_str());
        strcpy(CraftType, CraftT.c_str());
        strcpy(Departcity, Departc.c_str());
        strcpy(Arrivcity, Arrivc.c_str());
        strcpy(DepartTime, DepartT.c_str());
        strcpy(ArrivTime, ArrivT.c_str());
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
            strcpy(FlightNo, Num.c_str());
            return OK;
        }
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
            strcpy(Departcity, City.c_str());
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
            strcpy(Arrivcity, City.c_str());
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
            strcpy(DepartTime, Time.c_str());
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
            strcpy(ArrivTime, Time.c_str());
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
            strcpy(CraftType, craftT.c_str());
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
    string username;
    string password;

public:
    bool Checkusername(string name)
    { //用户查重
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
            password = newpswd;
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
            username = name;
            return OK;
        }
    }
};

typedef struct BookInfo
{
    string Username;
    string *FliNo = new string[MAXSIZE];
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

    cout << "之前" << i << endl; //可删除
    i++;
    outfile.seekg(0, ios::beg);
    outfile.write((char *)&i, sizeof(int)); //航班数加1
    outfile.seekg(0, ios::beg);
    outfile.read((char *)&i, sizeof(int));
    cout << "之后" << i << endl; //可删除

    outfile.close();
    return OK;
}

void ShowAllFli()
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
    infile.seekg(sizeof(int), ios::beg);
    for (int i = 0; i < NumOfFly; i++)
    {
        infile.read((char *)&fli2, sizeof(Flight));
        cout << "   " << i + 1 << ".  ";
        fli2.Display();
        cout << endl;
    }
    infile.close();
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

static void inputPassword(string &str, int size)
{
    //隐藏密码实现
    size++;
    char c;
    int count = 0;
    char *password = new char[size]; // 动态申请空间
    while ((c = getch()) != '\r')
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

void book() //订票菜单
{
    cout << "\n请输入需要订票的序号：";
    //cin>>xxx
    /* code */
    if (true /* code */) //有余票
    {
        /* code */
        cout << "\n订票成功!";
    }
    else //无余票
    {
        cout << "\n为您推荐以下同起降城市航班：\n\n";
        /* code */
    }
}

void ui() //菜单UI
{

    int Fnum = 0;
    char m, n, p, q, i, j, k;
    string Nam, newNam;
    string Passwd, newPasswd;
    string defAdmPasswd = "666666"; //管理员默认密码666666

lb1:
    cout << endl;
    cout << "          @@     @@      @@    @@@@@@@@@    @@@@@@@@@@\n";
    cout << "          @@     @@      @@    @@           @@       \n";
    cout << "          @@     @@      @@    @@           @@       \n";
    cout << "          @@     @@      @@    @@@@@@@@@    @@@@@@@@@\n";
    cout << "          @@     @@      @@    @@           @@       \n";
    cout << "    @@    @@      @@    @@     @@           @@       \n";
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

        cout << "\n请输入管理员密码：（默认6个6）"; //输入管理员默认密码666666
        inputPassword(Passwd, 6);

        if (Passwd == defAdmPasswd) //密码正确
        {
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
                cout << "\n所有航班信息如下：\n\n";
                //打印所有航班信息
                ShowAllFli();

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
        else //密码错误
        {
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
            cout << "\n请输入新用户名:";
            cin >> newNam;
            cout << "\n请输入新密码:";
            inputPassword(newPasswd, 6);
            //写入用户信息到文件中
            /* code */
            cout << "\n注册成功！正在返回乘客登录界面。\n";
            sleepcp(3000);
            system("cls");
            goto lb2;

        case '2':
            cout << "\n请输入用户名:";
            cin >> Nam;
            //查找文件是否有此人用户名，有则继续
            /* code */
            if (false /* code */) //如果没有该用户名则打印未注册，并回到之前
            {
                cout << "\n该用户未注册！请重新登录。";
                sleepcp(1 * 1000);
                system("cls");
                goto lb2;
            }

            cout << "\n请输入密码:";
            inputPassword(Passwd, 6);
            //判断密码正误
            /* code */
            if (true /* code */) //如果密码正确，则登录成功
            {
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
                    cout << "\t\t3.输入城市模糊查询\n\n";
                    cout << "\t\t4.返回上一步\n\n";
                    cout << "请输入您的选择：";
                    cin >> j;
                    switch (j)
                    {
                    case '1':
                        cout << "\n请输入航班号：";
                        //cin >> xxx;
                        if (true /* code */) //可以查找到相关信息
                        {
                            cout << "\n查找到以下航班信息：\n\n";
                            //显示相关航班
                            /* code */

                            book(); //订票菜单
                        }
                        else
                        {
                            cout << "\n查无此航班！正在返回上一步...";
                            sleepcp(1 * 1000);
                            system("cls");
                            goto lb6;
                        }

                    case '2':
                        cout << "\n请输入起飞和降落城市：";
                        //cin >> xxx;
                        if (true /* code */) //可以查找到相关信息
                        {
                            cout << "\n查找到以下航班信息：\n\n";
                            //显示相关航班
                            /* code */

                            book(); //订票菜单
                        }
                        else
                        {
                            cout << "\n查无此航班！";
                            sleepcp(1 * 1000);
                            system("cls");
                            goto lb6;
                        }

                    case '3':
                        cout << "\n请输入城市：";
                        //cin >> xxx;
                        if (true /* code */) //可以查找到相关信息
                        {
                            cout << "\n查找到以下航班信息：\n\n";
                            //显示相关航班
                            /* code */

                            book(); //订票菜单
                        }
                        else
                        {
                            cout << "\n查无此航班！正在返回上一步...";
                            sleepcp(1 * 1000);
                            system("cls");
                            goto lb6;
                        }

                    case '4': //返回上一步
                        system("cls");
                        goto lb4;

                    default: //选项输入有误
                        cout << "\n请输入正确选择！";
                        sleepcp(1 * 1000);
                        system("cls");
                        goto lb6;
                    }

                    break;
                case '2':
                    cout << "\n您的订票信息如下：\n";
                    /* code */
                    cout << "\n是否需要退票？(1.是；2.否) ";
                    cin >> k;
                    if (k == 1)
                    {
                        /* code */
                        cout << "\n退票成功！";
                        sleepcp(1 * 1000);
                        system("cls");
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
            else //如果密码错误，则返回
            {
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
    int NumOfFlight = 0;
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

    ui();

    system("pause");
    return 0;
}
