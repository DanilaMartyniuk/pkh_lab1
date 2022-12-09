#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    bool event(QEvent *event) override;
private slots:
    void on_pushButton_clicked();

    void on_lineEdit_editingFinished();

    void on_actionRGB_triggered();

    void on_actionCMYK_triggered();

    void on_actionHSV_triggered();

    void on_actionHSL_triggered();

    void on_actionXYZ_triggered();

    void on_actionLAB_triggered();

    void on_verticalSlider_sliderMoved(int position);

    void on_verticalSlider_2_sliderMoved(int position);

    void on_verticalSlider_3_sliderMoved(int position);

    void on_verticalSlider_4_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
