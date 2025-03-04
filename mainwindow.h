#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QPushButton>
#include <QMap>
#include <QStatusBar>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
private:
    QTabWidget *tabWidget;

    // 版本配置数据结构
    struct VersionConfig {
        QString regKey;    // 注册表项名称
        QString fileName;  // 文件名
        QString filePath;  // 文件路径模板
    };

    QMap<QString, VersionConfig> versionConfigs;

    // 控件
    QPushButton *ea15Btn;
    QPushButton *ea16Btn;
    QPushButton *ea17Btn;

    void setupTab(QWidget *tab, QPushButton *&btn, const QString &version);
    void deleteVersionData(const QString &version);
    void setupStatusBar(); // 设置底部状态栏
};
#endif // MAINWINDOW_H
