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


#include "ps2Command.h"
#include "debug.h"
#include "hostlink.h"
#include "byteorder.h"
#include <QMessageBox>


//----------------------------------------------------------------------------
CPS2Command::CPS2Command(QWidget * parent)
 : QWidget(parent)
 , sockUdp_(this)
 , ip_("")
{
  connect(&sockUdp_, SIGNAL(readyRead()),    this, SLOT(udpRead()));
}

//----------------------------------------------------------------------------
CPS2Command::~CPS2Command()
{
}

//----------------------------------------------------------------------------
void
CPS2Command::setIP(const QString & ip)
{
  ip_ = ip;
}

//----------------------------------------------------------------------------
void
CPS2Command::connectToConsole()
{
  if(ip_ == "")
  {
    QMessageBox::warning(this, "Internal ERROR", "Internal ERROR, IP-Adres not entered\n");
    return;
  }

  // Connect to UDP port
  //  - Debugging from PS2
  //  - Commands to PS2
  if(sockUdp_.bind(0x4712) == false)
    QMessageBox::warning(this, "UDP Port not valid", "Unable to bind to the UDP port\n");
  //sockUdp_.connectToHost(ip_, 0x4712);
}

//----------------------------------------------------------------------------
// Incomming UDP data is only used for debugging information
void
CPS2Command::udpRead()
{
  while(sockUdp_.hasPendingDatagrams())
  {
    QByteArray datagram;
    datagram.resize(sockUdp_.pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;

    sockUdp_.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

    debug(datagram.data());
  }
}

//----------------------------------------------------------------------------
// PS2 Commands
//----------------------------------------------------------------------------
void
CPS2Command::cmdExecIOP(const QString & filename)
{
  pko_pkt_execiop_req cmd;

  cmd.cmd  = htonl(PS2LINK_COMMAND_EXECIOP);
  cmd.len  = htons(sizeof(cmd));
  cmd.argc = htonl(1);
  // Copy string
  for(int i(0); i < filename.length(); i++)
    cmd.argv[i] = filename.toAscii()[i];
  // Add NULL
  cmd.argv[filename.length()] = 0;

  sockUdp_.writeDatagram((const char *)&cmd, sizeof(cmd), QHostAddress(ip_), 0x4712);
}

//----------------------------------------------------------------------------
void
CPS2Command::cmdExecEE(const QString & filename)
{
  QString file = QString("host:") + filename;

  pko_pkt_execee_req cmd;

  cmd.cmd  = htonl(PS2LINK_COMMAND_EXECEE);
  cmd.len  = htons(sizeof(cmd));
  cmd.argc = htonl(1);
  // Copy string
  for(int i(0); i < file.length(); i++)
    cmd.argv[i] = file.toAscii()[i];
  // Add NULL
  cmd.argv[file.length()] = 0;

  sockUdp_.writeDatagram((const char *)&cmd, sizeof(cmd), QHostAddress(ip_), 0x4712);
}

//----------------------------------------------------------------------------
void
CPS2Command::cmdScreenshot(unsigned int base, unsigned int width, unsigned int height, unsigned short psm)
{
  pko_pkt_screenshot_req cmd;

  cmd.cmd    = htonl(PS2LINK_COMMAND_SCREENSHOT);
  cmd.len    = htons(sizeof(cmd));
  cmd.base   = htonl(base);
  cmd.width  = htonl(width);
  cmd.height = htonl(height);
  cmd.psm    = htons(psm);

  // FIXME: If I don't send 2 extra bytes, the last 2 bytes will be messed up?!
  sockUdp_.writeDatagram((const char *)&cmd, sizeof(cmd) + 2, QHostAddress(ip_), 0x4712);
}

//----------------------------------------------------------------------------
void
CPS2Command::cmdReset()
{
  pko_pkt_reset_req cmd;

  cmd.cmd = htonl(PS2LINK_COMMAND_RESET);
  cmd.len = htons(sizeof(cmd));

  sockUdp_.writeDatagram((const char *)&cmd, sizeof(cmd), QHostAddress(ip_), 0x4712);
}

//----------------------------------------------------------------------------
void
CPS2Command::cmdSuspend()
{
  pko_pkt_hdr cmd;

  cmd.cmd = htonl(PS2LINK_COMMAND_SUSPEND);
  cmd.len = htons(sizeof(cmd));

  sockUdp_.writeDatagram((const char *)&cmd, sizeof(cmd), QHostAddress(ip_), 0x4712);
}

//----------------------------------------------------------------------------
void
CPS2Command::cmdResume()
{
  pko_pkt_hdr cmd;

  cmd.cmd = htonl(PS2LINK_COMMAND_RESUME);
  cmd.len = htons(sizeof(cmd));

  sockUdp_.writeDatagram((const char *)&cmd, sizeof(cmd), QHostAddress(ip_), 0x4712);
}

//----------------------------------------------------------------------------
void
CPS2Command::cmdPowerOff()
{
  pko_pkt_poweroff_req cmd;

  cmd.cmd = htonl(PS2LINK_COMMAND_POWEROFF);
  cmd.len = htons(sizeof(cmd));

  sockUdp_.writeDatagram((const char *)&cmd, sizeof(cmd), QHostAddress(ip_), 0x4712);
}

//----------------------------------------------------------------------------
// SCR DUMP?

//----------------------------------------------------------------------------
// NET DUMP?

//----------------------------------------------------------------------------
// DUMP MEM?

//----------------------------------------------------------------------------
// Start VU

//----------------------------------------------------------------------------
// Stop VU

//----------------------------------------------------------------------------
// Dump REGS?

//----------------------------------------------------------------------------
// Exec GS?

//----------------------------------------------------------------------------
// Write mem?

//----------------------------------------------------------------------------
// IOP Exception?
