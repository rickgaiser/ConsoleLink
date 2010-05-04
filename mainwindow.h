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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QString>
#include <QTimer>
#include <QSettings>
#include "ps2Command.h"
#include "ps2FileServer.h"
#include "ps2Screenshot.h"


namespace Ui
{
  class MainWindow;
  class DialogSettings;
  class Dialog;
};


class MainWindow
 : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_run();
  void on_reset();
  void on_shutdown();
  void on_screenshot();
  void on_save();
  void on_exit();

  void on_fileOpen();
  void widthHeightChange(int index);

  void on_DialogSettings_accepted();
  void about();
  void settings();
  void checkFile();

  void on_connected();
  void on_disconnected();
  void on_suspend();
  void on_resume();

  void on_screenshotUpdate(const QImage & screenshot);
  void renderScreenshot();

private:
  Ui::MainWindow * ui_;
  Ui::DialogSettings * uiSettings_;
  Ui::Dialog * uiAbout_;
  QDialog dialogSettings_;
  QDialog dialogAbout_;
  CPS2Command     cPS2Command_;
  CPS2FileServer  cPS2FileServer_;
  CScreenshotReceiver cScreenshotReceiver_;
  QImage * pScreenshot_;

  // Settings
  QSettings * settings_;
  QString ip_;
  bool bClearOnReset_;
  bool bClearOnShutdown_;

  QString sFileName_;
  QString sFilePath_;
  QTimer tmCheckFile_;
};

#endif
