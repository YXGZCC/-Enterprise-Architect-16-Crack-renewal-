#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <cstdio>
#include <lmcons.h>

int main()
{
    int a,b = 0;
    // 弹出提示框
    int result = MessageBox(NULL, _T("欢迎使用我公开发布的第一个c++程序，此程序仅供学习交流使用，完全免费，请于下载后24小时内删除，禁止用于商业行为，有能力请支持正版，谢谢^-^. by源星光子\n同意协议请点击“确定”，不同意请点“取消”退出程序"), _T("简短的用户协议"), MB_OKCANCEL);
    if (result == IDCANCEL) {
        exit(0); // 如果用户点击了"Cancel"按钮，就退出程序
    }
    MessageBox(NULL, _T("正式开始之前，请先关闭EA软件，再点击“确定"), _T("注意事项"), MB_OK);


    // 删除注册表
    const TCHAR *lpszSubKey = _T("Software\\Classes\\SOFTWARE\\Kane");
    DWORD lRet = RegDeleteKey(HKEY_CURRENT_USER, lpszSubKey);
    if (lRet == ERROR_SUCCESS) {
        a=1;
        MessageBox(NULL, _T("步骤1：删除EA相关注册表成功！"), _T("tips"), MB_OK);
    }
    else {
        MessageBox(NULL,_T("步骤1：删除EA相关注册表失败！"),_T("tips"),MB_OK);
    }

    // 获取当前登录的用户名
    char username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    GetUserNameA(username, &username_len);

    // 构造文件路径
    char filePath[513];
    sprintf(filePath, "C:\\Users\\%s\\AppData\\Roaming\\Sparx Systems\\EA\\fkey.dat", username);

    // 删除指定的文件
    if (remove(filePath) == 0) {
        b=1;
        MessageBox(NULL, _T("步骤2：key文件删除成功！"), _T("tips"), MB_OK);
    }
    else {
        MessageBox(NULL, _T("步骤2：key文件删除失败！"), _T("tips"), MB_OK);
    }


    if (a == 1 && b == 1) {
        MessageBox(NULL, _T("重置试用时间成功！"), _T("tips"), MB_OK);
        MessageBox(NULL, _T("程序执行完毕，请继续学习吧！（建议选择终极版，再点击继续试用）"), _T("tips"), MB_OK);
    }
    else {
        MessageBox(NULL, _T("程序发生部分/全部错误，重置试用时间可能失败！\n-反馈错误方式：邮箱：yxgzcc@qq.com  b站up主：源星光子"), _T("tips"), MB_OK);

    }


    return 0;
}