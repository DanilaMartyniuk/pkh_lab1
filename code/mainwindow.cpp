#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "custom_events.h"
#include <QColorDialog>
#include <QColor>
#include <QPalette>
#include <QString>
#include <QEvent>
#include <cmath>
#include "color_convertions.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPalette pal = QPalette();
    ui->frame->setAutoFillBackground(true);
    pal.setColor(QPalette::Window,Qt::white);
    ui->frame->setPalette(pal);
    ui->frame->show();
    ui->label->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this);
    if(color.isValid())
    {
        QPalette pal = QPalette();
        pal.setColor(QPalette::Window,color);
        ui->frame->setPalette(pal);
        ui->frame->show();
        if (ui->actionRGB->isChecked())
        {
            ui->verticalSlider->setValue(color.red());
            ui->verticalSlider_2->setValue(color.green());
            ui->verticalSlider_3->setValue(color.blue());
            ui->verticalSlider_4->setValue(0);
        }

        if (ui->actionCMYK->isChecked())
        {
            ui->verticalSlider->setValue(color.cyan());
            ui->verticalSlider_2->setValue(color.magenta());
            ui->verticalSlider_3->setValue(color.yellow());
            ui->verticalSlider_4->setValue(color.black());

        }

        if (ui->actionHSV->isChecked())
        {
            ui->verticalSlider->setValue(color.hsvHue());
            ui->verticalSlider_2->setValue(color.hsvSaturation());
            ui->verticalSlider_3->setValue(color.value());
            ui->verticalSlider_4->setValue(0);

        }

        if (ui->actionHSL->isChecked())
        {
            ui->verticalSlider->setValue(color.hslHue());
            ui->verticalSlider_2->setValue(color.hslSaturation());
            ui->verticalSlider_3->setValue(color.lightness());
            ui->verticalSlider_4->setValue(0);

        }

        if (ui->actionXYZ->isChecked())
        {
            double *xyz = RGBtoXYZ(color);
            ui->val_1->setText(QString::number(xyz[0]));
            ui->val_2->setText(QString::number(xyz[1]));
            ui->val_3->setText(QString::number(xyz[2]));
            ui->val_4->setText(QString::number(0));
            ui->verticalSlider->setValue(xyz[0]);
            ui->verticalSlider_2->setValue(xyz[1]);
            ui->verticalSlider_3->setValue(xyz[2]);
            ui->verticalSlider_4->setValue(0);
        }

        if (ui->actionLAB->isChecked())
        {
            double *xyz = RGBtoXYZ(color);
            double *lab = XYZtoLAB(xyz);
            ui->val_1->setText(QString::number(lab[0]));
            ui->val_2->setText(QString::number(lab[1]));
            ui->val_3->setText(QString::number(lab[2]));
            ui->val_4->setText(QString::number(0));
            ui->verticalSlider->setValue(lab[0]);
            ui->verticalSlider_2->setValue(lab[1]);
            ui->verticalSlider_3->setValue(lab[2]);
            ui->verticalSlider_4->setValue(0);
        }
        QCoreApplication::postEvent(this, new colorChanged(color));
    }
}

void MainWindow::on_lineEdit_editingFinished()
{
    QColor color = ui->lineEdit->text();
    if(color.isValid())
    {
    QPalette pal = QPalette(color);
    ui->frame->setPalette(pal);
    ui->frame->show();
    if (ui->actionRGB->isChecked())
    {
        ui->verticalSlider->setValue(color.red());
        ui->verticalSlider_2->setValue(color.green());
        ui->verticalSlider_3->setValue(color.blue());
        ui->verticalSlider_4->setValue(0);
        ui->label->setVisible(false);
    }

    if (ui->actionCMYK->isChecked())
    {
        ui->verticalSlider->setValue(color.cyan());
        ui->verticalSlider_2->setValue(color.magenta());
        ui->verticalSlider_3->setValue(color.yellow());
        ui->verticalSlider_4->setValue(color.black());
        ui->label->setVisible(false);
    }

    if (ui->actionHSV->isChecked())
    {
        ui->verticalSlider->setValue(color.hsvHue());
        ui->verticalSlider_2->setValue(color.hsvSaturation());
        ui->verticalSlider_3->setValue(color.value());
        ui->verticalSlider_4->setValue(0);
        ui->label->setVisible(false);
    }

    if (ui->actionHSL->isChecked())
    {
        ui->verticalSlider->setValue(color.hslHue());
        ui->verticalSlider_2->setValue(color.hslSaturation());
        ui->verticalSlider_3->setValue(color.lightness());
        ui->verticalSlider_4->setValue(0);
        ui->label->setVisible(false);
    }

    if (ui->actionXYZ->isChecked())
    {
        double *xyz = RGBtoXYZ(color);
        ui->val_1->setText(QString::number(xyz[0]));
        ui->val_2->setText(QString::number(xyz[1]));
        ui->val_3->setText(QString::number(xyz[2]));
        ui->val_4->setText(QString::number(0));
        ui->label->setVisible(false);
    }

    if (ui->actionLAB->isChecked())
    {
        double *xyz = RGBtoXYZ(color);
        double *lab = XYZtoLAB(xyz);
        ui->val_1->setText(QString::number(lab[0]));
        ui->val_2->setText(QString::number(lab[1]));
        ui->val_3->setText(QString::number(lab[2]));
        ui->val_4->setText(QString::number(0));
        ui->label->setVisible(false);
    }
    QCoreApplication::postEvent(this, new colorChanged(color));
    }
}


bool MainWindow::event(QEvent *event)
{
    if(event -> type() == colorChanged::type)
     {
         QColor tmp = static_cast<colorChanged*>(event)->color.rgb();
         QColor color = static_cast<colorChanged*>(event)->color.rgb();
         if (tmp.isValid())
         {
             ui->rgb_red->setText(QString::number(tmp.red()));
             ui->rgb_blue->setText(QString::number(tmp.blue()));
             ui->rgb_green->setText(QString::number(tmp.green()));
         }

         tmp = static_cast<colorChanged*>(event)->color.toCmyk();
         if (tmp.isValid())
         {
             ui->cmyk_cyan->setText(QString::number(tmp.cyan()));
             ui->cmyk_magenta->setText(QString::number(tmp.magenta()));
             ui->cmyk_yellow->setText(QString::number(tmp.yellow()));
             ui->cmyk_key->setText(QString::number(tmp.black()));
         }

         tmp = static_cast<colorChanged*>(event)->color.toHsv();
         if (tmp.isValid())
         {
             ui->hsv_hue->setText(QString::number(tmp.hsvHue()));
             ui->hsv_value->setText(QString::number(tmp.value()));
             ui->hsv_saturation->setText(QString::number(tmp.hsvSaturation()));
         }

         if (ui->actionRGB->isChecked())
         {
             ui->val_1->setText(QString::number(color.red()));
             ui->val_2->setText(QString::number(color.green()));
             ui->val_3->setText(QString::number(color.blue()));
             ui->val_4->setText(QString::number(0));
         }

         if (ui->actionCMYK->isChecked())
         {
             ui->val_1->setText(QString::number(color.cyan()));
             ui->val_2->setText(QString::number(color.magenta()));
             ui->val_3->setText(QString::number(color.yellow()));
             ui->val_4->setText(QString::number(color.black()));

         }

         if (ui->actionHSV->isChecked())
         {
             ui->val_1->setText(QString::number(color.hsvHue()));
             ui->val_2->setText(QString::number(color.hsvSaturation()));
             ui->val_3->setText(QString::number(color.value()));
             ui->val_4->setText(QString::number(0));

         }

         if (ui->actionHSL->isChecked())
         {
             ui->val_1->setText(QString::number(color.hslHue()));
             ui->val_2->setText(QString::number(color.hslSaturation()));
             ui->val_3->setText(QString::number(color.lightness()));
             ui->val_4->setText(QString::number(0));

         }

         if (ui->actionXYZ->isChecked())
         {
             ui->val_1->setText(QString::number(ui->verticalSlider->value()));
             ui->val_2->setText(QString::number(ui->verticalSlider_2->value()));
             ui->val_3->setText(QString::number(ui->verticalSlider_3->value()));
             ui->val_4->setText(QString::number(0));
         }

         if (ui->actionLAB->isChecked())
         {
             ui->val_1->setText(QString::number(ui->verticalSlider->value()));
             ui->val_2->setText(QString::number(ui->verticalSlider_2->value()));
             ui->val_3->setText(QString::number(ui->verticalSlider_3->value()));
             ui->val_4->setText(QString::number(0));
         }

     }
    return QWidget::event(event);
}



void MainWindow::on_actionRGB_triggered()
{
    ui->textBrowser->setText("Выбранное пространство: RGB");
    QPalette pal = ui->frame->palette();
    QColor color = pal.color(QPalette::Window);

    if (ui->actionLAB->isChecked())
    {
        double *lab = new double[3];
        lab[0] = ui->val_1->text().toDouble();
        lab[1] = ui->val_2->text().toDouble();
        lab[2] = ui->val_3->text().toDouble();
        double *xyz = LABtoXYZ(lab);
        int *rgb = XYZtoRGB(xyz[0], xyz[1],xyz[2]);
        color = QColor(rgb[0],rgb[1],rgb[2]);
        pal.setColor(QPalette::Window, color);
        ui->val_1->setText(QString::number(rgb[0]));
        ui->val_2->setText(QString::number(rgb[1]));
        ui->val_3->setText(QString::number(rgb[2]));
        ui->val_4->setText(QString::number(0));
        ui->verticalSlider->setValue(rgb[0]);
        ui->verticalSlider_2->setValue(rgb[1]);
        ui->verticalSlider_3->setValue(rgb[2]);
        ui->verticalSlider_4->setValue(0);
        if(color.isValid())
        {
            ui->frame->setPalette(pal);
            ui->frame->show();
            QCoreApplication::postEvent(this, new colorChanged(color));
        }
    }

    if (ui->actionXYZ->isChecked())
    {
        int *rgb = XYZtoRGB(ui->verticalSlider->value(),ui->verticalSlider_2->value(),ui->verticalSlider_3->value());
        color = QColor(rgb[0],rgb[1],rgb[2]);
        pal.setColor(QPalette::Window, color);
        ui->val_1->setText(QString::number(rgb[0]));
        ui->val_2->setText(QString::number(rgb[1]));
        ui->val_3->setText(QString::number(rgb[2]));
        ui->val_4->setText(QString::number(0));
        ui->verticalSlider->setValue(rgb[0]);
        ui->verticalSlider_2->setValue(rgb[1]);
        ui->verticalSlider_3->setValue(rgb[2]);
        ui->verticalSlider_4->setValue(0);
        if(color.isValid())
        {
            ui->frame->setPalette(pal);
            ui->frame->show();
            QCoreApplication::postEvent(this, new colorChanged(color));
        }

    }
    if (!ui->actionXYZ->isChecked() && !ui->actionLAB->isChecked())
    {
        color = color.toRgb();
        pal.setColor(QPalette::Window, color);
        ui->frame->setPalette(pal);
        ui->frame->show();
        ui->verticalSlider->setValue(color.red());
        ui->verticalSlider_2->setValue(color.green());
        ui->verticalSlider_3->setValue(color.blue());
        ui->verticalSlider_4->setValue(0);
        QCoreApplication::postEvent(this, new colorChanged(color));

    }
    ui->actionHSL->setChecked(false);
    ui->actionHSV->setChecked(false);
    ui->actionCMYK->setChecked(false);
    ui->actionLAB->setChecked(false);
    ui->actionXYZ->setChecked(false);
    ui->verticalSlider->setRange(0,255);
    ui->verticalSlider_2->setRange(0,255);
    ui->verticalSlider_3->setRange(0,255);
    ui->verticalSlider_4->setEnabled(false);
    ui->val_4->setEnabled(false);
    ui->comm_4->setEnabled(false);
    ui->comm_1->setText(QString("Red"));
    ui->comm_2->setText(QString("Green"));
    ui->comm_3->setText(QString("Blue"));
}

void MainWindow::on_actionCMYK_triggered()
{
    ui->textBrowser->setText("Выбранное пространство: CMYK");
    QPalette pal = ui->frame->palette();
    QColor color = pal.color(QPalette::Window);

    if (ui->actionLAB->isChecked())
    {
        double *lab = new double[3];
        lab[0] = ui->val_1->text().toDouble();
        lab[1] = ui->val_2->text().toDouble();
        lab[2] = ui->val_3->text().toDouble();
        double *xyz = LABtoXYZ(lab);
        int *rgb = XYZtoRGB(xyz[0], xyz[1],xyz[2]);
        color = QColor(rgb[0],rgb[1],rgb[2]);
        pal.setColor(QPalette::Window, color);
        ui->val_1->setText(QString::number(rgb[0]));
        ui->val_2->setText(QString::number(rgb[1]));
        ui->val_3->setText(QString::number(rgb[2]));
        ui->val_4->setText(QString::number(0));
        ui->verticalSlider->setValue(rgb[0]);
        ui->verticalSlider_2->setValue(rgb[1]);
        ui->verticalSlider_3->setValue(rgb[2]);
        ui->verticalSlider_4->setValue(0);
        if(color.isValid())
        {
            ui->frame->setPalette(pal);
            ui->frame->show();
            QCoreApplication::postEvent(this, new colorChanged(color));
        }
    }

    if (ui->actionXYZ->isChecked())
    {
        int *rgb = XYZtoRGB(ui->verticalSlider->value(),ui->verticalSlider_2->value(),ui->verticalSlider_3->value());
        color = QColor(rgb[0],rgb[1],rgb[2]);
        pal.setColor(QPalette::Window, color);
        ui->val_1->setText(QString::number(rgb[0]));
        ui->val_2->setText(QString::number(rgb[1]));
        ui->val_3->setText(QString::number(rgb[2]));
        ui->val_4->setText(QString::number(0));
        ui->verticalSlider->setValue(rgb[0]);
        ui->verticalSlider_2->setValue(rgb[1]);
        ui->verticalSlider_3->setValue(rgb[2]);
        ui->verticalSlider_4->setValue(0);
        if(color.isValid())
        {
            ui->frame->setPalette(pal);
            ui->frame->show();
            QCoreApplication::postEvent(this, new colorChanged(color));
        }

    }
    if (!ui->actionXYZ->isChecked() && !ui->actionLAB->isChecked())
    {
        color = color.toCmyk();
        ui->verticalSlider->setValue(color.cyan());
        ui->verticalSlider_2->setValue(color.magenta());
        ui->verticalSlider_3->setValue(color.yellow());
        ui->verticalSlider_4->setValue(color.black());
        pal.setColor(QPalette::Window, color);
        ui->frame->setPalette(pal);
        ui->frame->show();
        QCoreApplication::postEvent(this, new colorChanged(color));
    }
    ui->actionHSL->setChecked(false);
    ui->actionHSV->setChecked(false);
    ui->actionRGB->setChecked(false);
    ui->actionLAB->setChecked(false);
    ui->actionXYZ->setChecked(false);
    ui->verticalSlider->setRange(0,255);
    ui->verticalSlider_2->setRange(0,255);
    ui->verticalSlider_3->setRange(0,255);
    ui->verticalSlider_4->setEnabled(true);
    ui->val_4->setEnabled(true);
    ui->comm_4->setEnabled(true);
    ui->verticalSlider_4->setRange(0,255);
    ui->comm_1->setText(QString("Cyan"));
    ui->comm_2->setText(QString("Magenta"));
    ui->comm_3->setText(QString("Yellow"));
}

void MainWindow::on_actionHSV_triggered()
{
    ui->textBrowser->setText("Выбранное пространство: HSV");
    QPalette pal = ui->frame->palette();
    QColor color = pal.color(QPalette::Window);

    if (ui->actionLAB->isChecked())
    {
        double *lab = new double[3];
        lab[0] = ui->val_1->text().toDouble();
        lab[1] = ui->val_2->text().toDouble();
        lab[2] = ui->val_3->text().toDouble();
        double *xyz = LABtoXYZ(lab);
        int *rgb = XYZtoRGB(xyz[0], xyz[1],xyz[2]);
        color = QColor(rgb[0],rgb[1],rgb[2]);
        pal.setColor(QPalette::Window, color);
        ui->val_1->setText(QString::number(rgb[0]));
        ui->val_2->setText(QString::number(rgb[1]));
        ui->val_3->setText(QString::number(rgb[2]));
        ui->val_4->setText(QString::number(0));
        ui->verticalSlider->setValue(rgb[0]);
        ui->verticalSlider_2->setValue(rgb[1]);
        ui->verticalSlider_3->setValue(rgb[2]);
        ui->verticalSlider_4->setValue(0);
        if(color.isValid())
        {
            ui->frame->setPalette(pal);
            ui->frame->show();
            QCoreApplication::postEvent(this, new colorChanged(color));
        }
    }

    if (ui->actionXYZ->isChecked())
    {
        int *rgb = XYZtoRGB(ui->verticalSlider->value(),ui->verticalSlider_2->value(),ui->verticalSlider_3->value());
        color = QColor(rgb[0],rgb[1],rgb[2]);
        pal.setColor(QPalette::Window, color);
        ui->val_1->setText(QString::number(rgb[0]));
        ui->val_2->setText(QString::number(rgb[1]));
        ui->val_3->setText(QString::number(rgb[2]));
        ui->val_4->setText(QString::number(0));
        ui->verticalSlider->setValue(rgb[0]);
        ui->verticalSlider_2->setValue(rgb[1]);
        ui->verticalSlider_3->setValue(rgb[2]);
        ui->verticalSlider_4->setValue(0);
        if(color.isValid())
        {
            ui->frame->setPalette(pal);
            ui->frame->show();
            QCoreApplication::postEvent(this, new colorChanged(color));
        }

    }
    if (!ui->actionXYZ->isChecked() && !ui->actionLAB->isChecked())
    {
        color = color.toHsv();
        ui->verticalSlider->setValue(color.hsvHue());
        ui->verticalSlider_2->setValue(color.hsvSaturation());
        ui->verticalSlider_3->setValue(color.value());
        ui->verticalSlider_4->setValue(0);
        pal.setColor(QPalette::Window, color);
        ui->frame->setPalette(pal);
        ui->frame->show();
        QCoreApplication::postEvent(this, new colorChanged(color));
    }
    ui->actionHSL->setChecked(false);
    ui->actionCMYK->setChecked(false);
    ui->actionRGB->setChecked(false);
    ui->actionLAB->setChecked(false);
    ui->actionXYZ->setChecked(false);
    ui->verticalSlider->setRange(0, 359);
    ui->verticalSlider_2->setRange(0,255);
    ui->verticalSlider_3->setRange(0,255);
    ui->verticalSlider_4->setEnabled(false);
    ui->val_4->setEnabled(false);
    ui->comm_4->setEnabled(false);
    ui->comm_1->setText(QString("Hue"));
    ui->comm_2->setText(QString("Saturation"));
    ui->comm_3->setText(QString("Lightness"));
}

void MainWindow::on_actionHSL_triggered()
{
    QPalette pal = ui->frame->palette();
    QColor color = pal.color(QPalette::Window);
    ui->textBrowser->setText("Выбранное пространство: HSL");

    if (ui->actionLAB->isChecked())
    {
        double *lab = new double[3];
        lab[0] = ui->val_1->text().toDouble();
        lab[1] = ui->val_2->text().toDouble();
        lab[2] = ui->val_3->text().toDouble();
        double *xyz = LABtoXYZ(lab);
        int *rgb = XYZtoRGB(xyz[0], xyz[1],xyz[2]);
        color = QColor(rgb[0],rgb[1],rgb[2]);
        pal.setColor(QPalette::Window, color);
        ui->val_1->setText(QString::number(rgb[0]));
        ui->val_2->setText(QString::number(rgb[1]));
        ui->val_3->setText(QString::number(rgb[2]));
        ui->val_4->setText(QString::number(0));
        ui->verticalSlider->setValue(rgb[0]);
        ui->verticalSlider_2->setValue(rgb[1]);
        ui->verticalSlider_3->setValue(rgb[2]);
        ui->verticalSlider_4->setValue(0);
        if(color.isValid())
        {
            ui->frame->setPalette(pal);
            ui->frame->show();
            QCoreApplication::postEvent(this, new colorChanged(color));
        }
    }

    if (ui->actionXYZ->isChecked())
    {
        int *rgb = XYZtoRGB(ui->verticalSlider->value(),ui->verticalSlider_2->value(),ui->verticalSlider_3->value());
        color = QColor(rgb[0],rgb[1],rgb[2]);
        pal.setColor(QPalette::Window, color);
        ui->val_1->setText(QString::number(rgb[0]));
        ui->val_2->setText(QString::number(rgb[1]));
        ui->val_3->setText(QString::number(rgb[2]));
        ui->val_4->setText(QString::number(0));
        ui->verticalSlider->setValue(rgb[0]);
        ui->verticalSlider_2->setValue(rgb[1]);
        ui->verticalSlider_3->setValue(rgb[2]);
        ui->verticalSlider_4->setValue(0);
        if(color.isValid())
        {
            ui->frame->setPalette(pal);
            ui->frame->show();
            QCoreApplication::postEvent(this, new colorChanged(color));
        }
    }
    if (!ui->actionXYZ->isChecked() && !ui->actionLAB->isChecked())
    {
        color = color.toHsl();
        ui->verticalSlider->setValue(color.hslHue());
        ui->verticalSlider_2->setValue(color.hslSaturation());
        ui->verticalSlider_3->setValue(color.lightness());
        ui->verticalSlider_4->setValue(0);
        pal.setColor(QPalette::Window, color);
        ui->frame->setPalette(pal);
        ui->frame->show();
        QCoreApplication::postEvent(this, new colorChanged(color));
    }
    ui->actionHSV->setChecked(false);
    ui->actionCMYK->setChecked(false);
    ui->actionRGB->setChecked(false);
    ui->actionLAB->setChecked(false);
    ui->actionXYZ->setChecked(false);
    ui->verticalSlider->setRange(0, 359);
    ui->verticalSlider_2->setRange(0,255);
    ui->verticalSlider_3->setRange(0,255);
    ui->verticalSlider_4->setEnabled(false);
    ui->val_4->setEnabled(false);
    ui->comm_4->setEnabled(false);
    ui->comm_1->setText(QString("Hue"));
    ui->comm_2->setText(QString("Saturation"));
    ui->comm_3->setText(QString("Brightness"));
}

void MainWindow::on_actionXYZ_triggered()
{
    QPalette pal = ui->frame->palette();
    QColor color = pal.color(QPalette::Window);
    if (!ui->actionLAB->isChecked())
    {
        double *xyz = RGBtoXYZ(color);
        ui->verticalSlider->setValue(int(xyz[0]));
        ui->verticalSlider_2->setValue(int(xyz[1]));
        ui->verticalSlider_3->setValue(int(xyz[2]));
        ui->verticalSlider_4->setValue(0);
        ui->val_1->setText(QString::number(xyz[0]));
        ui->val_2->setText(QString::number(xyz[1]));
        ui->val_3->setText(QString::number(xyz[2]));
    }
    if (ui->actionLAB->isChecked())
    {
        double *lab = new double[3];
        lab[0] = ui->val_1->text().toDouble();
        lab[1] = ui->val_2->text().toDouble();
        lab[2] = ui->val_3->text().toDouble();
        double *xyz = LABtoXYZ(lab);
        ui->verticalSlider->setValue(int(xyz[0]));
        ui->verticalSlider_2->setValue(int(xyz[1]));
        ui->verticalSlider_3->setValue(int(xyz[2]));
        ui->verticalSlider_4->setValue(0);
        ui->val_1->setText(QString::number(xyz[0]));
        ui->val_2->setText(QString::number(xyz[1]));
        ui->val_3->setText(QString::number(xyz[2]));
    }
    ui->textBrowser->setText("Выбранное пространство: XYZ");
    ui->actionHSV->setChecked(false);
    ui->actionCMYK->setChecked(false);
    ui->actionRGB->setChecked(false);
    ui->actionLAB->setChecked(false);
    ui->actionHSL->setChecked(false);
    ui->verticalSlider->setRange(0, 255);
    ui->verticalSlider_2->setRange(0,255);
    ui->verticalSlider_3->setRange(0,255);
    ui->verticalSlider_4->setEnabled(false);
    ui->val_4->setEnabled(false);
    ui->comm_4->setEnabled(false);
    ui->comm_1->setText(QString("X"));
    ui->comm_2->setText(QString("Y"));
    ui->comm_3->setText(QString("Z"));
}

void MainWindow::on_actionLAB_triggered()
{

    QPalette pal = ui->frame->palette();
    QColor color = pal.color(QPalette::Window);
    if(!ui->actionXYZ->isChecked())
    {
        double *xyz = RGBtoXYZ(color);
        double *lab = XYZtoLAB(xyz);
        ui->verticalSlider->setValue(int(lab[0]));
        ui->verticalSlider_2->setValue(int(lab[1]));
        ui->verticalSlider_3->setValue(int(lab[2]));
        ui->verticalSlider_4->setValue(0);
        ui->val_1->setText(QString::number(lab[0]));
        ui->val_2->setText(QString::number(lab[1]));
        ui->val_3->setText(QString::number(lab[2]));
    }

    if(ui->actionXYZ->isChecked())
    {
        double *xyz = new double[3];
        xyz[0] = ui->val_1->text().toDouble();
        xyz[1] = ui->val_2->text().toDouble();
        xyz[2] = ui->val_3->text().toDouble();
        double *lab = XYZtoLAB(xyz);
        ui->verticalSlider->setValue(int(lab[0]));
        ui->verticalSlider_2->setValue(int(lab[1]));
        ui->verticalSlider_3->setValue(int(lab[2]));
        ui->verticalSlider_4->setValue(0);
        ui->val_1->setText(QString::number(lab[0]));
        ui->val_2->setText(QString::number(lab[1]));
        ui->val_3->setText(QString::number(lab[2]));
    }

    ui->textBrowser->setText("Выбранное пространство: LAB");
    ui->actionHSV->setChecked(false);
    ui->actionCMYK->setChecked(false);
    ui->actionRGB->setChecked(false);
    ui->actionXYZ->setChecked(false);
    ui->actionHSL->setChecked(false);
    ui->verticalSlider->setRange(0, 100);
    ui->verticalSlider_2->setRange(-128,127);
    ui->verticalSlider_3->setRange(-128,127);
    ui->verticalSlider_4->setEnabled(false);
    ui->val_4->setEnabled(false);
    ui->comm_4->setEnabled(false);
    ui->comm_1->setText(QString("lightness"));
    ui->comm_2->setText(QString("A"));
    ui->comm_3->setText(QString("B"));
}

void MainWindow::on_verticalSlider_sliderMoved(int position)
{
    ui->val_1->setText(QString::number(position));
    QPalette pal = ui->frame->palette();
    QColor color = pal.color(QPalette::Window);
    if(ui->actionRGB->isChecked())
    {
        color.setRed(position);
        pal.setColor(QPalette::Window, color);
        ui->frame->setPalette(pal);
        if(color.isValid())
        {
            ui->label->setVisible(false);
        }
        ui->frame->show();
        QCoreApplication::postEvent(this, new colorChanged(color));
    }
    if(ui->actionCMYK->isChecked())
    {
        color.setCmyk(position, ui->verticalSlider_2->value(),ui->verticalSlider_3->value(),ui->verticalSlider_4->value());
        pal.setColor(QPalette::Window, color);
        ui->frame->setPalette(pal);
        if(color.isValid())
        {
            ui->label->setVisible(false);
        }
        ui->frame->show();
        QCoreApplication::postEvent(this, new colorChanged(color));
    }
    if(ui->actionHSV->isChecked())
    {
        color.setHsv(position, ui->verticalSlider_2->value(),ui->verticalSlider_3->value());
        pal.setColor(QPalette::Window, color);
        ui->frame->setPalette(pal);
        if(color.isValid())
        {
            ui->label->setVisible(false);
        }
        ui->frame->show();
        QCoreApplication::postEvent(this, new colorChanged(color));
    }
    if(ui->actionHSL->isChecked())
    {
        color.setHsl(position, ui->verticalSlider_2->value(),ui->verticalSlider_3->value());
        pal.setColor(QPalette::Window, color);
        ui->frame->setPalette(pal);
        if(color.isValid())
        {
            ui->label->setVisible(false);
        }
        ui->frame->show();
        QCoreApplication::postEvent(this, new colorChanged(color));
    }
    if(ui->actionXYZ->isChecked())
    {
        int *rgb = XYZtoRGB(ui->verticalSlider->value(),ui->verticalSlider_2->value(), ui->verticalSlider_3->value());
        color.setRgb(rgb[0],rgb[1],rgb[2]);
        pal.setColor(QPalette::Window, color);
        if(!color.isValid())
        {
            ui->label->setVisible(true);
        }
        if(color.isValid())
        {
            ui->label->setVisible(false);
        }
        ui->frame->setPalette(pal);
        ui->frame->show();
        QCoreApplication::postEvent(this, new colorChanged(color));
    }
    if(ui->actionLAB->isChecked())
    {
        double *lab = new double[3];
        lab[0] = ui->verticalSlider->value();
        lab[1] = ui->verticalSlider_2->value();
        lab[2] = ui->verticalSlider_3->value();
        double *xyz = LABtoXYZ(lab);
        int *rgb = XYZtoRGB(xyz[0],xyz[1],xyz[2]);
        color.setRgb(rgb[0],rgb[1],rgb[2]);
        pal.setColor(QPalette::Window, color);
        if(!color.isValid())
        {
            ui->label->setVisible(true);
        }
        if(color.isValid())
        {
            ui->label->setVisible(false);
        }
        ui->frame->setPalette(pal);
        ui->frame->show();
        QCoreApplication::postEvent(this, new colorChanged(color));
    }
}

void MainWindow::on_verticalSlider_2_sliderMoved(int position)
{
    ui->val_2->setText(QString::number(position));
    QPalette pal = ui->frame->palette();
    QColor color = pal.color(QPalette::Window);
    if(ui->actionRGB->isChecked())
    {
        color.setGreen(position);
        pal.setColor(QPalette::Window, color);
        ui->frame->setPalette(pal);
        if(color.isValid())
        {
            ui->label->setVisible(false);
        }
        ui->frame->show();

        QCoreApplication::postEvent(this, new colorChanged(color));
    }
    if(ui->actionCMYK->isChecked())
    {
        color.setCmyk(ui->verticalSlider->value(),position,ui->verticalSlider_3->value(),ui->verticalSlider_4->value());
        pal.setColor(QPalette::Window, color);
        ui->frame->setPalette(pal);
        if(color.isValid())
        {
            ui->label->setVisible(false);
        }
        ui->frame->show();
        QCoreApplication::postEvent(this, new colorChanged(color));
    }
    if(ui->actionHSV->isChecked())
    {
        color.setHsv(ui->verticalSlider->value(),position,ui->verticalSlider_3->value());
        pal.setColor(QPalette::Window, color);
        ui->frame->setPalette(pal);
        if(color.isValid())
        {
            ui->label->setVisible(false);
        }
        ui->frame->show();
        QCoreApplication::postEvent(this, new colorChanged(color));
    }
    if(ui->actionHSL->isChecked())
    {
        color.setHsl(ui->verticalSlider->value(),position,ui->verticalSlider_3->value());
        pal.setColor(QPalette::Window, color);
        ui->frame->setPalette(pal);
        if(color.isValid())
        {
            ui->label->setVisible(false);
        }
        ui->frame->show();
        QCoreApplication::postEvent(this, new colorChanged(color));
    }
    if(ui->actionXYZ->isChecked())
    {
        int *rgb = XYZtoRGB(ui->verticalSlider->value(),ui->verticalSlider_2->value(), ui->verticalSlider_3->value());
        color.setRgb(rgb[0],rgb[1],rgb[2]);
        pal.setColor(QPalette::Window, color);
        if(!color.isValid())
        {
            ui->label->setVisible(true);
        }
        if(color.isValid())
        {
            ui->label->setVisible(false);
        }
        ui->frame->setPalette(pal);
        ui->frame->show();
        QCoreApplication::postEvent(this, new colorChanged(color));

    }
    if(ui->actionLAB->isChecked())
    {
        double *lab = new double[3];
        lab[0] = ui->verticalSlider->value();
        lab[1] = ui->verticalSlider_2->value();
        lab[2] = ui->verticalSlider_3->value();
        double *xyz = LABtoXYZ(lab);
        int *rgb = XYZtoRGB(xyz[0],xyz[1],xyz[2]);
        color.setRgb(rgb[0],rgb[1],rgb[2]);
        pal.setColor(QPalette::Window, color);
        if(!color.isValid())
        {
            ui->label->setVisible(true);
        }
        if(color.isValid())
        {
            ui->label->setVisible(false);
        }
        ui->frame->setPalette(pal);
        ui->frame->show();
        QCoreApplication::postEvent(this, new colorChanged(color));
    }
}

void MainWindow::on_verticalSlider_3_sliderMoved(int position)
{
    ui->val_3->setText(QString::number(position));
    QPalette pal = ui->frame->palette();
    QColor color = pal.color(QPalette::Window);
    if(ui->actionRGB->isChecked())
    {
        color.setBlue(position);
        pal.setColor(QPalette::Window, color);
        ui->frame->setPalette(pal);
        ui->frame->show();
        if(color.isValid())
        {
            ui->label->setVisible(false);
        }
        QCoreApplication::postEvent(this, new colorChanged(color));
    }
    if(ui->actionCMYK->isChecked())
    {
        color.setCmyk(ui->verticalSlider->value(),ui->verticalSlider_2->value(),position,ui->verticalSlider_4->value());
        pal.setColor(QPalette::Window, color);
        ui->frame->setPalette(pal);
        if(color.isValid())
        {
            ui->label->setVisible(false);
        }
        ui->frame->show();
        QCoreApplication::postEvent(this, new colorChanged(color));
    }
    if(ui->actionHSV->isChecked())
    {
        color.setHsv(ui->verticalSlider->value(),ui->verticalSlider_2->value(),position);
        pal.setColor(QPalette::Window, color);
        ui->frame->setPalette(pal);
        if(color.isValid())
        {
            ui->label->setVisible(false);
        }
        ui->frame->show();
        QCoreApplication::postEvent(this, new colorChanged(color));
    }
    if(ui->actionHSL->isChecked())
    {
        color.setHsl(ui->verticalSlider->value(),ui->verticalSlider_2->value(),position);
        pal.setColor(QPalette::Window, color);
        ui->frame->setPalette(pal);
        if(color.isValid())
        {
            ui->label->setVisible(false);
        }
        ui->frame->show();
        QCoreApplication::postEvent(this, new colorChanged(color));
    }
    if(ui->actionXYZ->isChecked())
    {
        int *rgb = XYZtoRGB(ui->verticalSlider->value(),ui->verticalSlider_2->value(), ui->verticalSlider_3->value());
        color.setRgb(rgb[0],rgb[1],rgb[2]);
        pal.setColor(QPalette::Window, color);
        if(!color.isValid())
        {
            ui->label->setVisible(true);
        }
        if(color.isValid())
        {
            ui->label->setVisible(false);
        }
        ui->frame->setPalette(pal);
        ui->frame->show();
        QCoreApplication::postEvent(this, new colorChanged(color));

    }
    if(ui->actionLAB->isChecked())
    {
        double *lab = new double[3];
        lab[0] = ui->verticalSlider->value();
        lab[1] = ui->verticalSlider_2->value();
        lab[2] = ui->verticalSlider_3->value();
        double *xyz = LABtoXYZ(lab);
        int *rgb = XYZtoRGB(xyz[0],xyz[1],xyz[2]);
        color.setRgb(rgb[0],rgb[1],rgb[2]);
        pal.setColor(QPalette::Window, color);
        if(!color.isValid())
        {
            ui->label->setVisible(true);
        }
        if(color.isValid())
        {
            ui->label->setVisible(false);
        }
        ui->frame->setPalette(pal);
        ui->frame->show();
        QCoreApplication::postEvent(this, new colorChanged(color));

    }
}

void MainWindow::on_verticalSlider_4_sliderMoved(int position)
{
    ui->val_3->setText(QString::number(position));
    QPalette pal = ui->frame->palette();
    QColor color = pal.color(QPalette::Window);
    color.setCmyk(ui->verticalSlider->value(),ui->verticalSlider_2->value(),ui->verticalSlider_3->value(),position);
    pal.setColor(QPalette::Window, color);
    if(color.isValid())
    {
        ui->label->setVisible(false);
    }
    ui->frame->setPalette(pal);
    ui->frame->show();
    QCoreApplication::postEvent(this, new colorChanged(color));
}
