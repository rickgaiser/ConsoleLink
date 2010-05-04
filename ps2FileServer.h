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


#ifndef PS2FILESERVER_H
#define PS2FILESERVER_H


#include <QObject>
#include <QWidget>
#include <QString>
#include <QFile>
#include <QTimer>
#include <QTcpSocket>
#include "ps2Screenshot.h"


#define MAX_OPEN_FILES 50
struct SFileOperation
{
    bool used;
    QFile file;
};


//---------------------------------------------------------------------------
// PS2 File Server:
//   Using a TCP connection (PC needs to make the connection) the PS2 can
//   access a filesystem on the PC.
class CPS2FileServer
 : public QWidget
{
  Q_OBJECT

public:
  CPS2FileServer(QWidget * parent = 0);
  virtual ~CPS2FileServer();

  void setIP(const QString & ip);
  void setScreenshotReceiver(CScreenshotReceiver * scr);
  void connectToConsole();
  void setPath(const QString & path);

  void reset();

signals:
  void connected();
  void disconnected();

private slots:
  void checkConnection();
  void tcpConnected();
  void tcpDisconnected();
  void tcpRead();

private:
  // PS2 Command Requests
  void ps2RequestOpen    (char * data, int size);
  void ps2RequestClose   (char * data, int size);
  void ps2RequestRead    (char * data, int size);
  void ps2RequestWrite   (char * data, int size);
  void ps2RequestLSeek   (char * data, int size);
  void ps2RequestOpenDir (char * data, int size);
  void ps2RequestCloseDir(char * data, int size);
  void ps2RequestReadDir (char * data, int size);
  void ps2RequestRemove  (char * data, int size);
  void ps2RequestMkDir   (char * data, int size);
  void ps2RequestRmDir   (char * data, int size);

  // Reply for PS2 Command Requests
  void ps2ReplyOpen    (int result);
  void ps2ReplyClose   (int result);
  void ps2ReplyRead    (int result, int size);
  void ps2ReplyWrite   (int result);
  void ps2ReplyLSeek   (int result);
  void ps2ReplyOpenDir (int result);
  void ps2ReplyCloseDir(int result);
  void ps2ReplyReadDir (int result, unsigned int mode, unsigned int attr, unsigned int size, unsigned char *ctime, unsigned char *atime, unsigned char *mtime, unsigned int hisize, char *name);
  void ps2ReplyRemove  (int result);
  void ps2ReplyMkDir   (int result);
  void ps2ReplyRmDir   (int result);

private:
  QTcpSocket sockTcp_;
  QString ip_;
  QTimer tmCheckConnection_;
  QString path_;

  CScreenshotReceiver * pScreenshotReceiver_;
  SFileOperation files_[MAX_OPEN_FILES];
};


#endif
