/*
 * ConsoleLink, Communication for your Game Console
 * Copyright (C) 2010 Maximus32 <Maximus32@bricks-os.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307 USA
 */


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_settings.h"
#include "ui_about.h"
#include "debug.h"
#include <QFileDialog>


struct SPS2PixelFormat
{
  const char * name;
  int value;
};

struct SPS2Resolution
{
  const char * name;
  int width;
  int height;
};

const SPS2Resolution resolutions[] =
{
  {"NTSC-NI",  640,  224},
  {"NTSC",     640,  448},
  {"PAL-NI",   640,  256},
  {"PAL",      640,  512},
  {"480P",     720,  480},
  {"720P",    1280,  720},
  {"1080i",   1920, 1080}
};
const int resolution_count   = sizeof(resolutions) / sizeof(SPS2Resolution);
const int resolution_default = 0;

const SPS2PixelFormat pixelFormats[] =
{
  {"PSMCT16",  0x02},
  {"PSMCT16S", 0x0a},
  {"PSMCT24",  0x01},
  {"PSMCT32",  0x00}
};
const int pixelFormat_count   = sizeof(pixelFormats) / sizeof(SPS2PixelFormat);
const int pixelFormat_default = 2;


//---------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
 : QMainWindow(parent)
 , ui_(new Ui::MainWindow)
 , uiSettings_(new Ui::DialogSettings)
 , uiAbout_(new Ui::Dialog)
 , dialogSettings_()
 , dialogAbout_()
 , cPS2Command_(this)
 , cPS2FileServer_(this)
 , pScreenshot_(NULL)
 , settings_(new QSettings("Bricks-OS", "ConsoleLink"))
 , tmCheckFile_(this)
{
  // Initialize ui's
  ui_->setupUi(this);
  uiAbout_->setupUi(&dialogAbout_);
  uiSettings_->setupUi(&dialogSettings_);
  // Initialize debugging output
  pOutput = ui_->textBrowser;

  // ----------
  // Connections
  // ----------
  // File menu
  QObject::connect(ui_->actionSettings,        SIGNAL(triggered()),    this, SLOT(settings()));
  QObject::connect(ui_->actionExit,            SIGNAL(triggered()),    this, SLOT(on_exit()));
  // Device menu
  QObject::connect(ui_->actionRun,             SIGNAL(triggered()),    this, SLOT(on_run()));
  QObject::connect(ui_->actionReset,           SIGNAL(triggered()),    this, SLOT(on_reset()));
  QObject::connect(ui_->actionPowerOff,        SIGNAL(triggered()),    this, SLOT(on_shutdown()));
  QObject::connect(ui_->actionSuspend,         SIGNAL(triggered()),    this, SLOT(on_suspend()));
  QObject::connect(ui_->actionResume,          SIGNAL(triggered()),    this, SLOT(on_resume()));
  QObject::connect(ui_->actionScreenshot,      SIGNAL(triggered()),    this, SLOT(on_screenshot()));
  QObject::connect(ui_->btnScreenshot,         SIGNAL(clicked()),      this, SLOT(on_screenshot()));
  QObject::connect(ui_->btnSave,               SIGNAL(clicked()),      this, SLOT(on_save()));
  // About menu
  QObject::connect(ui_->actionAbout,           SIGNAL(triggered()),    this, SLOT(about()));
  // Open file
  QObject::connect(ui_->btnOpen,               SIGNAL(clicked()),      this, SLOT(on_fileOpen()));
  // Settings dialog
  QObject::connect(uiSettings_->ok,            SIGNAL(clicked()),      this, SLOT(on_DialogSettings_accepted()));
  // PS2
  QObject::connect(&cPS2FileServer_,           SIGNAL(connected()),    this, SLOT(on_connected()));
  QObject::connect(&cPS2FileServer_,           SIGNAL(disconnected()), this, SLOT(on_disconnected()));
  // Screenshots
  QObject::connect(&cScreenshotReceiver_,      SIGNAL(screenshotUpdated(const QImage &)), this, SLOT(on_screenshotUpdate(const QImage &)));
  QObject::connect(&cScreenshotReceiver_,      SIGNAL(screenshotDone(const QImage &)), this, SLOT(on_screenshotUpdate(const QImage &)));
  QObject::connect(ui_->cbWH,                  SIGNAL(currentIndexChanged (int)), this, SLOT(widthHeightChange(int)));
  QObject::connect(ui_->rbOneOne,              SIGNAL(released()),     this, SLOT(renderScreenshot()));
  QObject::connect(ui_->rbOneTwo,              SIGNAL(released()),     this, SLOT(renderScreenshot()));
  QObject::connect(ui_->rbFourThree,           SIGNAL(released()),     this, SLOT(renderScreenshot()));
  QObject::connect(ui_->rbSixteenNine,         SIGNAL(released()),     this, SLOT(renderScreenshot()));
  // File change check timer
  //QObject::connect(&tmCheckFile_,              SIGNAL(timeout()),      this, SLOT(checkFile()));
  //tmCheckFile_.start(1000);

  // Load settings
  ip_               = settings_->value("ps2/ip", "192.168.0.10").toString();
  bClearOnReset_    = settings_->value("log/clear_on_reset", true).toBool();
  bClearOnShutdown_ = settings_->value("log/clear_on_shutdown", false).toBool();
  sFileName_        = settings_->value("last_loaded_file", "").toString();
  sFilePath_        = settings_->value("last_loaded_path", "").toString();

  // Configure PS2 classes
  cPS2Command_.setIP(ip_);
  cPS2FileServer_.setIP(ip_);
  cPS2FileServer_.setScreenshotReceiver(&cScreenshotReceiver_);
  cPS2FileServer_.setPath(sFilePath_);

  ui_->fileName->setText(sFilePath_ + QString('/') + sFileName_);
  ui_->tabWidget->setCurrentIndex(0);
  ui_->rbOneOne->setChecked(true);
  ui_->leBasePointer->setText("000000");
  ui_->leWidth->setText("640");
  ui_->leHeight->setText("224");

  for(int i(0); i < pixelFormat_count; i++)
  {
    ui_->cbFormat->addItem(pixelFormats[i].name);
  }
  ui_->cbFormat->setCurrentIndex(pixelFormat_default);

  for(int i(0); i < resolution_count; i++)
  {
    QString str;
    QTextStream(&str)<<resolutions[i].name<<" ("<<resolutions[i].width<<"x"<<resolutions[i].height<<")";
    ui_->cbWH->addItem(str);
  }
  ui_->cbWH->setCurrentIndex(resolution_default);

  // Initially show disconnected status
  on_disconnected();

  // Start
  cPS2Command_.connectToConsole();
  cPS2FileServer_.connectToConsole();

  qDebug("ConsoleLink running\n");
}

//---------------------------------------------------------------------------
MainWindow::~MainWindow()
{
  delete ui_;
  delete uiSettings_;
  delete uiAbout_;
  delete settings_;

  if(pScreenshot_ != NULL)
    delete pScreenshot_;
}

//---------------------------------------------------------------------------
void
MainWindow::about()
{
  dialogAbout_.show();
}

//---------------------------------------------------------------------------
void
MainWindow::settings()
{
  // Load settings
  uiSettings_->ip->setText(ip_);
  uiSettings_->cbClearOnReset->setChecked(bClearOnReset_);
  uiSettings_->cbClearOnShutdown->setChecked(bClearOnShutdown_);

  dialogSettings_.show();
}

//---------------------------------------------------------------------------
void
MainWindow::on_DialogSettings_accepted()
{
  debug("Setting IP to: ");
  debug(uiSettings_->ip->text() + "\n");
  settings_->setValue("ps2/ip", uiSettings_->ip->text());

  //cPS2Command_.disconnect();
  //cPS2FileServer_.disconnect();
  cPS2Command_.setIP(uiSettings_->ip->text());
  cPS2FileServer_.setIP(uiSettings_->ip->text());
  //cPS2Command_.connect();
  //cPS2FileServer_.connect();

  bClearOnReset_ = uiSettings_->cbClearOnReset->checkState();
  settings_->setValue("log/clear_on_reset", bClearOnReset_);

  bClearOnShutdown_ = uiSettings_->cbClearOnShutdown->checkState();
  settings_->setValue("log/clear_on_shutdown", bClearOnShutdown_);
}

//---------------------------------------------------------------------------
void
MainWindow::on_run()
{
  QString sFile;

  cPS2FileServer_.setPath(sFilePath_);
  cPS2Command_.cmdExecEE(sFileName_);
}

//---------------------------------------------------------------------------
void
MainWindow::on_reset()
{
  if(bClearOnReset_ == true)
    ui_->textBrowser->clear();

  cPS2Command_.cmdReset();
  cPS2FileServer_.reset();
}

//---------------------------------------------------------------------------
void
MainWindow::on_shutdown()
{
  if(bClearOnShutdown_ == true)
    ui_->textBrowser->clear();

  cPS2Command_.cmdPowerOff();
  cPS2FileServer_.reset();
}

//---------------------------------------------------------------------------
void
MainWindow::on_screenshot()
{
  bool ok;
  unsigned int iBasePointer = ui_->leBasePointer->text().toInt(&ok, 16);
  unsigned int iWidth       = ui_->leWidth->text().toInt(&ok, 10);
  unsigned int iHeight      = ui_->leHeight->text().toInt(&ok, 10);
  unsigned short iPSM       = pixelFormats[ui_->cbFormat->currentIndex()].value;

  cPS2Command_.cmdScreenshot(iBasePointer, iWidth, iHeight, iPSM);
}

//---------------------------------------------------------------------------
void
MainWindow::on_save()
{
  if(pScreenshot_ != NULL)
  {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Screenshot"), sFilePath_, tr("Images (*.bmp *.png *.jpg)"));
    pScreenshot_->save(fileName);
  }
}

//---------------------------------------------------------------------------
void
MainWindow::on_exit()
{
  qApp->exit(0);
}

//---------------------------------------------------------------------------
void
MainWindow::on_fileOpen()
{
  // Ask user for file
  QString sFile = QFileDialog::getOpenFileName(this, tr("Open PS2 Executable"), sFilePath_, tr("Executable Files (*.elf)"));

  if(sFile.isNull() == false)
  {
    // Save new filename
    sFileName_ = sFile.section('/', -1, -1);
    sFilePath_ = sFile.section('/', 0, -2);

    // Save for the next reboot
    settings_->setValue("last_loaded_file", sFileName_);
    settings_->setValue("last_loaded_path", sFilePath_);

    // Display the text
    ui_->fileName->setText(sFilePath_ + QString('/') + sFileName_);
  }
}

//---------------------------------------------------------------------------
void
MainWindow::widthHeightChange(int index)
{
  ui_->leWidth->setText(QString().sprintf("%d", resolutions[index].width));
  ui_->leHeight->setText(QString().sprintf("%d", resolutions[index].height));
}

//---------------------------------------------------------------------------
void
MainWindow::checkFile()
{
}

//---------------------------------------------------------------------------
void
MainWindow::on_connected()
{
  ui_->txtStatus->setText("  CONNECTED  ");
  ui_->txtStatus->setStyleSheet("QLabel { background-color: green }");
}

//---------------------------------------------------------------------------
void
MainWindow::on_disconnected()
{
  ui_->txtStatus->setText("  DISCONNECTED  ");
  ui_->txtStatus->setStyleSheet("QLabel { background-color: red }");
}
//---------------------------------------------------------------------------
void
MainWindow::on_suspend()
{
  cPS2Command_.cmdSuspend();
}

//---------------------------------------------------------------------------
void
MainWindow::on_resume()
{
  cPS2Command_.cmdResume();
}

//---------------------------------------------------------------------------
void
MainWindow::on_screenshotUpdate(const QImage & screenshot)
{
  if(pScreenshot_ != NULL)
    delete pScreenshot_;

  pScreenshot_ = new QImage(screenshot);

  renderScreenshot();
}

//---------------------------------------------------------------------------
void
MainWindow::renderScreenshot()
{
  if(pScreenshot_ != NULL)
  {
    if(ui_->rbOneOne->isChecked() == true)
    {
      ui_->lblScreenshot->setPixmap(QPixmap::fromImage(*pScreenshot_));
    }
    else if(ui_->rbOneTwo->isChecked() == true)
    {
      int iNewWidth  = pScreenshot_->width();
      int iNewHeight = pScreenshot_->height() * 2;
      ui_->lblScreenshot->setPixmap(QPixmap::fromImage(pScreenshot_->scaled(iNewWidth, iNewHeight, Qt::IgnoreAspectRatio)));
    }
    else if(ui_->rbFourThree->isChecked() == true)
    {
      int iNewWidth  = pScreenshot_->width();
      int iNewHeight = pScreenshot_->height();
      if((iNewWidth * 3) < (iNewHeight * 4))
      {
        // Stretch horizontally
        iNewWidth = (iNewHeight * 4) / 3;
      }
      else
      {
        // Stretch vertically
        iNewHeight = (iNewWidth * 3) / 4;
      }
      ui_->lblScreenshot->setPixmap(QPixmap::fromImage(pScreenshot_->scaled(iNewWidth, iNewHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    }
    else if(ui_->rbSixteenNine->isChecked() == true)
    {
      int iNewWidth  = pScreenshot_->width();
      int iNewHeight = pScreenshot_->height();
      if((iNewWidth * 9) < (iNewHeight * 16))
      {
        // Stretch horizontally
        iNewWidth = (iNewHeight * 16) / 9;
      }
      else
      {
        // Stretch vertically
        iNewHeight = (iNewWidth * 9) / 16;
      }
      ui_->lblScreenshot->setPixmap(QPixmap::fromImage(pScreenshot_->scaled(iNewWidth, iNewHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    }
  }
}
