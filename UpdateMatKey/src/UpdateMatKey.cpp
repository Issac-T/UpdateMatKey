// UpdateMatKey.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

const char filepath[] = "E:\\软件安装包\\Magics 24\\Materialise Magics 24.0 Crack\\magics24.matkey";

int main()
{
    //1.复制剪贴板内容（系统信息ID）
    HWND hWnd = NULL;
    string newid;

    OpenClipboard(hWnd);//打开剪贴板
    if (IsClipboardFormatAvailable(CF_TEXT))
    {
        HANDLE h = GetClipboardData(CF_TEXT);//获取剪切板数据
        newid = (char*)GlobalLock(h);
        GlobalUnlock(h);
    }
    CloseClipboard();//关闭剪贴板

    //2.打开matkey文件并替换系统信息ID
    string id_start = "<SystemID>";
    string id_end = "</SystemID>";
    string id_string = "";
    string my_string = newid;
    string file_content;

    ifstream file_in(filepath);

    if (!file_in) {
        cout << "Error opening file!" << endl;
        return 1;
    }
    // 查找旧IDstring
    while (getline(file_in, file_content))
    {
        size_t start_pos = file_content.find(id_start);
        if (start_pos != string::npos)
        {
            size_t end_pos = file_content.find(id_end, start_pos + id_start.size());
            if (end_pos != string::npos)
            {
                id_string = file_content.substr(start_pos + id_start.size(), end_pos - start_pos - id_start.size());
                break;
            }
        }
    }
    //执行替换
    size_t start_pos = file_content.find(id_start);
    while (start_pos != string::npos) {
        size_t end_pos = file_content.find(id_end, start_pos);
        if (end_pos == string::npos) {
            cerr << "文件格式不正确！" << endl;
            return 1;
        }
        file_content.replace(start_pos + id_start.size(), end_pos - start_pos - id_start.size(), my_string);
        start_pos = file_content.find(id_start, start_pos + my_string.size());
    }
    file_in.close();

    // 输出保存新文件
    ofstream file_out(filepath);
    file_out << file_content;
    file_out.close();

    //3.复制matkey文件全路径名称至剪贴板
    OpenClipboard(hWnd);//打开剪切板
    EmptyClipboard();//清空剪切板
    HANDLE hHandle = GlobalAlloc(GMEM_FIXED, 1000);//分配内存
    char* pData = (char*)GlobalLock(hHandle);//锁定内存，返回申请内存的首地址
    strcpy_s(pData, 1000, filepath);//或strcpy(pData, "this is a ClipBoard Test.");
    SetClipboardData(CF_TEXT, hHandle);//设置剪切板数据
    GlobalUnlock(hHandle);//解除锁定
    CloseClipboard();//关闭剪切板
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
