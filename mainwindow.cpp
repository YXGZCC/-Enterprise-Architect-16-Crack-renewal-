#include "mainwindow.h"
#include <windows.h>        // Windows API（注册表操作需要）
#include <QMessageBox>      // QMessageBox 用于消息框
#include <QFile>            // QFile 用于文件操作
#include <QDir>             // QDir 用于目录操作
#include <QFileInfo>        // QFileInfo 用于文件信息检查
#include <QTabWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QDesktopWidget>   // 获取屏幕信息
#include <QStatusBar>
#include <QUrl>
#include <QDesktopServices>
#include <QGuiApplication> // 用于 QGuiApplication
#include <QScreen>         // 用于 QScreen


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 初始化版本配置
    versionConfigs = {
        {"EA15", {"Huna", "fkey.dat", "/AppData/Roaming/Sparx Systems/EA/%1"}},
        {"EA16", {"KANE", "fkey.dat", "/AppData/Roaming/Sparx Systems/EA/%1"}},
        {"EA17", {"Hopo", "pkey.dat", "/AppData/Roaming/Sparx Systems/EA/%1"}}
    };

    // 设置主窗口大小（按屏幕比例）
    QScreen *screen = QGuiApplication::primaryScreen(); // 获取主屏幕
    if (screen) {
        QRect screenGeometry = screen->availableGeometry(); // 获取屏幕可用区域
        int width = screenGeometry.width() * 0.6;  // 窗口宽度为屏幕宽度的60%
        int height = screenGeometry.height() * 0.7; // 窗口高度为屏幕高度的70%
        resize(width, height);
    }


    // 创建主界面
    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);

    // EA15 Tab
    QWidget *ea15Tab = new QWidget();
    setupTab(ea15Tab, ea15Btn, "EA15");
    tabWidget->addTab(ea15Tab, "EA15");

    // EA16 Tab
    QWidget *ea16Tab = new QWidget();
    setupTab(ea16Tab, ea16Btn, "EA16");
    tabWidget->addTab(ea16Tab, "EA16");

    // EA17 Tab
    QWidget *ea17Tab = new QWidget();
    setupTab(ea17Tab, ea17Btn, "EA17");
    tabWidget->addTab(ea17Tab, "EA17");

    tabWidget->setStyleSheet(
        "QTabBar::tab {"
        "  min-width: 140px;"      // 设置标签的最小宽度
        "  min-height: 50px;"      // 设置标签的最小高度
        "  font-size: 33px;"       // 设置字体大小
        "  padding: 10px;"         // 设置内边距
        "}"
        "QTabBar::tab:selected {"
        "  background: #2196F3;"   // 选中标签的背景颜色
        "  color: white;"          // 选中标签的文字颜色
        "}"
        "QTabBar::tab:!selected {"
        "  background: #E0E0E0;"   // 未选中标签的背景颜色
        "  color: black;"          // 未选中标签的文字颜色
        "}"
    );


    // 连接信号槽
    connect(ea15Btn, &QPushButton::clicked, this, [this]{ deleteVersionData("EA15"); });
    connect(ea16Btn, &QPushButton::clicked, this, [this]{ deleteVersionData("EA16"); });
    connect(ea17Btn, &QPushButton::clicked, this, [this]{ deleteVersionData("EA17"); });

    // 设置底部状态栏
    setupStatusBar();
}

void MainWindow::setupTab(QWidget *tab, QPushButton *&btn, const QString &version)
{
    QVBoxLayout *layout = new QVBoxLayout(tab);
    QLabel *infoLabel = new QLabel(QString("正在操作 %1 版本，请注意核对EA版本信息。\t点击下方蓝色按钮即可继续⬇⬇⬇").arg(version), tab);
    infoLabel->setStyleSheet("font-size: 36px;");


    btn = new QPushButton(QString("重置%1的授权信息").arg(version), tab);
    btn->setStyleSheet("QPushButton {"
                      "  min-width: 120px;"
                      "  height: 50px;"
                      "  background: #2196F3;"
                      "  color: white;"
                      "  border-radius: 5px;"
                      "  font-size: 30px;"
                      "}"
                      "QPushButton:hover {"
                      "  background: #1976D2;"
                      "}");

    QLabel *helpLabel = new QLabel(QString("操作帮助："));
    helpLabel->setStyleSheet("font-size: 48px;");

    QLabel *helpInfoLabel = new QLabel(QString("Q：提示文件不存在？\nA：1.可能没启动过EA本体。\n   2.已经执行过一次脚本之后又马上再次执行了脚本。\n（启动EA本体之后才会生成注册表项和文件。本脚本的目的是帮助你快速删除它们，以重置试用时间。）"));
    helpInfoLabel->setStyleSheet("font-size: 25px;");

//    QLabel *helpInfoLabel = new QLabel(QString("Q：。）"));
//    helpInfoLabel->setStyleSheet("font-size: 25px;");

    layout->addWidget(infoLabel);
    layout->addWidget(btn);
    layout->addWidget(helpLabel);
    layout->addWidget(helpInfoLabel);
    layout->addStretch();
}

void MainWindow::setupStatusBar()
{
    // 创建底部状态栏
    QStatusBar *statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    // 添加作者信息
    QLabel *authorLabel = new QLabel(this);
    authorLabel->setText(
        R"(
        <p>
            <span style="font-size:20px; color:#000;">作者博客（仅限国内IP访问）：</span>
            <a href="https://www.yxgz.cc" style="text-decoration:none; color:#2196F3;">小源的blog</a>
            &nbsp;&nbsp;&nbsp;
            <span style="font-size:20px; color:#000;">B站账号：</span>
            <a href="https://space.bilibili.com/289521519" style="text-decoration:none; color:#2196F3;">@源星光子</a>
            &nbsp;&nbsp;&nbsp;
            <a href="https://github.com/YXGZCC/-Enterprise-Architect-16-Crack-renewal-" style="text-decoration:none; color:#2196F3;">GitHub项目</a>
            &nbsp;&nbsp;&nbsp;
            <a href="https://www.bilibili.com/video/BV1Qx421U7VW/" style="text-decoration:none; color:#2196F3;">B站原理视频</a>
            <span style="font-size:20px; color:#000;">蓝色部分均可点击跳转</span>
        </p>
        )"
    );
    authorLabel->setOpenExternalLinks(true);

    authorLabel->setOpenExternalLinks(true);

    authorLabel->setOpenExternalLinks(true); // 启用外部链接点击跳转
    statusBar->addPermanentWidget(authorLabel);
}

void MainWindow::deleteVersionData(const QString &version)
{
    if (!versionConfigs.contains(version)) {
        QMessageBox::critical(this, "错误", "无效的版本配置");
        return;
    }

    VersionConfig config = versionConfigs[version];

    // ================= 准备检测信息 =================
    QString regPath = QString("HKEY_CURRENT_USER\\Software\\Classes\\SOFTWARE\\%1").arg(config.regKey);
    QString filePath = QDir::homePath() + config.filePath.arg(config.fileName);
    QFileInfo fileInfo(filePath);

    // 检测注册表存在性
    bool regExists = false;
    HKEY hKey;
    LONG regCheck = RegOpenKeyExW(
        HKEY_CURRENT_USER,
        QString("Software\\Classes\\SOFTWARE\\%1").arg(config.regKey).toStdWString().c_str(),
        0,
        KEY_READ | KEY_WOW64_64KEY,  // 只读检测
        &hKey
    );

    if (regCheck == ERROR_SUCCESS) {
        regExists = true;
        RegCloseKey(hKey);
    }

    // ================= 创建确认对话框 =================
    QMessageBox confirmBox(this);
    confirmBox.setWindowTitle("确认删除操作");
    confirmBox.setIcon(QMessageBox::Question);
    confirmBox.setTextFormat(Qt::RichText);

    QString message = QString(
        "<style>"
        "td { padding: 2px 10px; }"
        ".exists { color: #2e7d32; }"
        ".not-exists { color: #c62828; }"
        "</style>"
        "<b>即将执行删除操作：</b>"
        "<table>"
        "<tr><td>注册表项：</td><td><code>%1</code></td>"
            "<td class='%2'>%3</td></tr>"
        "<tr><td>目标文件：</td><td><code>%4</code></td>"
            "<td class='%5'>%6</td></tr>"
        "</table>"
        "<br>确认要执行删除操作吗？"
    )
    .arg(regPath.toHtmlEscaped())
    .arg(regExists ? "exists" : "not-exists").arg(regExists ? "存在" : "不存在")
    .arg(filePath.toHtmlEscaped())
    .arg(fileInfo.exists() ? "exists" : "not-exists").arg(fileInfo.exists() ? "存在" : "不存在");

    confirmBox.setText(message);
    QPushButton *confirmBtn = confirmBox.addButton("确认删除", QMessageBox::AcceptRole);
    QPushButton *cancelBtn = confirmBox.addButton("取消", QMessageBox::RejectRole);
    confirmBox.setDefaultButton(cancelBtn);

    // ================= 执行删除操作 =================
    confirmBox.exec();

    // 通过 clickedButton() 判断用户点击了哪个按钮
    if (confirmBox.clickedButton() != confirmBtn) {
        // 如果点击的不是“确认删除”，直接返回
        return;
    }

    // 删除注册表（如果存在）
    bool regDeleted = false;
    if (regExists) {
        LONG result = RegOpenKeyExW(
            HKEY_CURRENT_USER,
            QString("Software\\Classes\\SOFTWARE\\%1").arg(config.regKey).toStdWString().c_str(),
            0,
            KEY_WRITE | KEY_WOW64_64KEY,
            &hKey
        );

        if (result == ERROR_SUCCESS) {
            regDeleted = (RegDeleteKeyW(hKey, L"") == ERROR_SUCCESS);
            RegCloseKey(hKey);
        }
    }

    // 删除文件（如果存在）
    bool fileDeleted = false;
    QString fileError;
    if (fileInfo.exists()) {
        QFile file(filePath);
        if (!(fileDeleted = file.remove())) {
            fileError = file.errorString();
        }
    }

    // ================= 显示操作结果 =================
    QStringList results;

    // 注册表结果
    if (regExists) {
        results << QString("注册表：%1").arg(regDeleted ? "删除成功" : "删除失败");
    } else {
        results << "注册表：不存在，无需操作";
    }

    // 文件结果
    if (fileInfo.exists()) {
        results << QString("文件：%1").arg(fileDeleted ? "删除成功" : QString("删除失败 - %1").arg(fileError));
    } else {
        results << "文件：不存在，无需操作";
    }

    QMessageBox resultBox(this);
    resultBox.setWindowTitle("操作结果");
    resultBox.setIcon(regDeleted && fileDeleted ? QMessageBox::Information : QMessageBox::Warning);
    resultBox.setText(QString("<b>%1 操作结果：</b>").arg(version));
    resultBox.setInformativeText(results.join("<br>"));
    resultBox.exec();
}

MainWindow::~MainWindow()
{
}
