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


#ifndef PS2COMMAND_H
#define PS2COMMAND_H


#include <QObject>
#include <QWidget>
#include <QString>
#include <QtNetwork\QUdpSocket>


//---------------------------------------------------------------------------
// PS2 Command and Debug interface
//   PS2 Uses UDP messages at port 0x4712 for
//   - receiving commands
//   - sending debug information
class CPS2Command
 : public QWidget
{
  Q_OBJECT

public:
  CPS2Command(QWidget * parent = 0);
  virtual ~CPS2Command();

  void setIP(const QString & ip);
  void connectToConsole();

  // PS2 Commands
  void cmdExecIOP(const QString & filename);
  void cmdExecEE(const QString & filename);
  void cmdScreenshot(unsigned int base, unsigned int width, unsigned int height, unsigned short psm);
  void cmdReset();
  void cmdSuspend();
  void cmdResume();
  void cmdPowerOff();

private slots:
  void udpRead();

private:
  void connectUDP();

private:
  QUdpSocket sockUdp_;
  QString ip_;
};


#endif
