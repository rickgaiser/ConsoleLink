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


#include "ps2FileServer.h"
#include "debug.h"
#include "hostlink.h"
#include "byteorder.h"
#include <QMessageBox>
#include <QFile>
#include <unistd.h>
#include <fcntl.h>


#define TCP_BUFFER_SIZE (4 * 1024)
#define SCREENSHOT_MAGIC 12345678


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
CPS2FileServer::CPS2FileServer(QWidget *parent)
  : QWidget(parent)
  , sockTcp_(this)
  , ip_("")
  , tmCheckConnection_(this)
  , pScreenshotReceiver_(NULL)
 {
   for(int i(0); i < MAX_OPEN_FILES; i++)
     files_[i].used = false;

   connect(&sockTcp_,           SIGNAL(readyRead()),    this, SLOT(tcpRead()));
   connect(&sockTcp_,           SIGNAL(connected()),    this, SLOT(tcpConnected()));
   connect(&sockTcp_,           SIGNAL(disconnected()), this, SLOT(tcpDisconnected()));
   connect(&tmCheckConnection_, SIGNAL(timeout()),      this, SLOT(tcpCheckConnection()));
}

//----------------------------------------------------------------------------
CPS2FileServer::~CPS2FileServer()
{
}

//----------------------------------------------------------------------------
void
CPS2FileServer::setIP(const QString & ip)
{
  ip_ = ip;
}

//----------------------------------------------------------------------------
void
CPS2FileServer::setScreenshotReceiver(CScreenshotReceiver * scr)
{
  pScreenshotReceiver_ = scr;
}

//----------------------------------------------------------------------------
void
CPS2FileServer::setPath(const QString & path)
{
  path_ = path;
}

//----------------------------------------------------------------------------
void
CPS2FileServer::connectToConsole()
{
  if(ip_ != "")
  {
    // Connect
    sockTcp_.connectToHost(ip_, 0x4711);

    // Check connection periodically
    tmCheckConnection_.start(1000);
  }
  else
  {
    QMessageBox::warning(this, "Internal ERROR", "Internal ERROR, IP-Adres not entered\n");
    tmCheckConnection_.stop();
  }
}

//----------------------------------------------------------------------------
void
CPS2FileServer::checkConnection()
{
  if(sockTcp_.state() != QAbstractSocket::ConnectedState)
  {
    // Try to reconnect
    sockTcp_.connectToHost(ip_, 0x4711);
  }
}

//----------------------------------------------------------------------------
void
CPS2FileServer::tcpConnected()
{
  emit connected();
}

//----------------------------------------------------------------------------
void
CPS2FileServer::tcpDisconnected()
{
  emit disconnected();
}

//----------------------------------------------------------------------------
void
CPS2FileServer::tcpRead()
{
  char * buffer = new char[TCP_BUFFER_SIZE];

  if(sockTcp_.bytesAvailable())
  {
    int size = sockTcp_.read(buffer, TCP_BUFFER_SIZE);

    pko_pkt_hdr * hdr = (pko_pkt_hdr *)buffer;
    switch(ntohl(hdr->cmd))
    {
      case PS2LINK_REQUEST_OPEN:     ps2RequestOpen(buffer, size);     break;
      case PS2LINK_REQUEST_CLOSE:    ps2RequestClose(buffer, size);    break;
      case PS2LINK_REQUEST_READ:     ps2RequestRead(buffer, size);     break;
      case PS2LINK_REQUEST_WRITE:    ps2RequestWrite(buffer, size);    break;
      case PS2LINK_REQUEST_LSEEK:    ps2RequestLSeek(buffer, size);    break;
      case PS2LINK_REQUEST_OPENDIR:  ps2RequestOpenDir(buffer, size);  break;
      case PS2LINK_REQUEST_CLOSEDIR: ps2RequestCloseDir(buffer, size); break;
      case PS2LINK_REQUEST_READDIR:  ps2RequestReadDir(buffer, size);  break;
      case PS2LINK_REQUEST_REMOVE:   ps2RequestRemove(buffer, size);   break;
      case PS2LINK_REQUEST_MKDIR:    ps2RequestMkDir(buffer, size);    break;
      case PS2LINK_REQUEST_RMDIR:    ps2RequestRmDir(buffer, size);    break;
      default:
        qDebug("Unknown Command: 0x%x\n", ntohl(hdr->cmd));

    };
  }

  delete buffer;
}

//----------------------------------------------------------------------------
void
CPS2FileServer::reset()
{
  // Close all opened files
  for(int i(0); i < MAX_OPEN_FILES; i++)
  {
    if(files_[i].used == true)
    {
      files_[i].file.close();
      files_[i].used = false;
    }
  }
}

//----------------------------------------------------------------------------
// PS2 Command Requests
//----------------------------------------------------------------------------
void
CPS2FileServer::ps2RequestOpen(char * data, int size)
{
  //qDebug("ps2RequestOpen");

  pko_pkt_open_req * cmd = (pko_pkt_open_req *)data;
  cmd->flags = ntohl(cmd->flags);
  //qDebug("ps2RequestOpen: Trying to open \"%s\" flags=0x%x", cmd->path, cmd->flags);

  // Handle the "screenshot.ps2" string separately, becoude we do not write it to a file,
  // but display is on screen
  if(QString(cmd->path) == "screenshot.ps2")
  {
    if(pScreenshotReceiver_ != NULL)
    {
      pScreenshotReceiver_->screenshotStart();
      ps2ReplyOpen(SCREENSHOT_MAGIC);
    }
    else
    {
      ps2ReplyOpen(-1);
    }

    return;
  }

  // Get a free file slot
  SFileOperation * pFileOps = NULL;
  int iHandle;
  for(iHandle = 0; iHandle < MAX_OPEN_FILES; iHandle++)
  {
    if(files_[iHandle].used == false)
    {
      pFileOps = &files_[iHandle];
      break;
    }
  }

  // Open the file
  // NOTE: flags are ignored for now, files are opened read/write
  if(pFileOps != NULL)
  {
    // Convert flags
    QIODevice::OpenMode flags = 0;
    if(cmd->flags & O_RDONLY) flags |= QIODevice::ReadOnly;
    if(cmd->flags & O_WRONLY) flags |= QIODevice::WriteOnly;

    // Correct file path
    pFileOps->file.setFileName(path_ + QString('/') + cmd->path);

    // Open file
    pFileOps->file.open(QIODevice::ReadWrite);

    if(pFileOps->file.handle() == -1)
    {
      debug("ConsoleLink: Failed to open file!\n");
      pFileOps->used = false;
      iHandle = -1;
    }
  }
  else
  {
    debug("ConsoleLink: Max open files limit reached!\n");
    iHandle = -1;
  }

  //qDebug("ps2RequestOpen: Opened with id=%d", iHandle);

  // Reply with the result
  ps2ReplyOpen(iHandle);
}

//----------------------------------------------------------------------------
void
CPS2FileServer::ps2RequestClose(char * data, int size)
{
  //qDebug("ps2RequestClose");

  pko_pkt_close_req * cmd = (pko_pkt_close_req *)data;
  cmd->fd = ntohl(cmd->fd);
  //qDebug("ps2RequestClose: Trying to close fd=%d", cmd->fd);

  if(cmd->fd == SCREENSHOT_MAGIC)
  {
    if(pScreenshotReceiver_ != NULL)
      pScreenshotReceiver_->screenshotEnd();

    ps2ReplyClose(0);
    return;
  }

  if((cmd->fd >= 0) && (cmd->fd < MAX_OPEN_FILES))
  {
      // Close the file
      files_[cmd->fd].file.close();
      files_[cmd->fd].used = false;
  }
  else
  {
    debug("ConsoleLink: Failed to close file!\n");
  }

  // Reply with the result
  ps2ReplyClose(0);
}

//----------------------------------------------------------------------------
void
CPS2FileServer::ps2RequestRead(char * data, int size)
{
  //qDebug("ps2RequestRead");

  int iBytesRead = -1;
  char * buffer = NULL;

  pko_pkt_read_req * cmd = (pko_pkt_read_req *)data;
  cmd->fd = ntohl(cmd->fd);
  cmd->nbytes = ntohl(cmd->nbytes);
  //qDebug("ps2RequestRead: Trying to read size=%d from fd=%d", cmd->nbytes, cmd->fd);

  if(cmd->fd == SCREENSHOT_MAGIC)
  {
    // ERROR!!!
    ps2ReplyRead(0, 0);
    return;
  }

  if((cmd->fd >= 0) && (cmd->fd < MAX_OPEN_FILES))
  {
    buffer = new char[cmd->nbytes];

    // Read requested data
    iBytesRead = files_[cmd->fd].file.read(buffer, cmd->nbytes);
  }
  else
  {
    debug("ConsoleLink: Failed to read from file!\n");
  }

  //qDebug("ps2RequestRead: %d bytes read", iBytesRead);

  // Reply with the result
  ps2ReplyRead(iBytesRead, iBytesRead);

  if(buffer != NULL)
  {
    // Send the data
    sockTcp_.write(buffer, iBytesRead);

    delete buffer;
  }
}

//----------------------------------------------------------------------------
void
CPS2FileServer::ps2RequestWrite(char * data, int size)
{
  //qDebug("ps2RequestWrite");

  //int iBytesRead = -1;
  int iBytesWrite = -1;
  char * buffer = NULL;

  pko_pkt_write_req * cmd = (pko_pkt_write_req *)data;
  cmd->fd = ntohl(cmd->fd);
  cmd->nbytes = ntohl(cmd->nbytes);
  cmd->len = ntohs(cmd->len);
  int bytesleft = cmd->nbytes;
  //qDebug("ps2RequestWrite: Trying to write size=%d to fd=%d", cmd->nbytes, cmd->fd);

  if(cmd->fd == SCREENSHOT_MAGIC)
  {
    if(pScreenshotReceiver_ != NULL)
    {
      pScreenshotReceiver_->screenshotData((unsigned char *)&data[cmd->len], cmd->nbytes);
      ps2ReplyWrite(cmd->nbytes);
    }
    else
    {
      ps2ReplyWrite(0);
    }
    return;
  }

  if((cmd->fd >= 0) && (cmd->fd < MAX_OPEN_FILES))
  {
    if((unsigned int)size > cmd->len)
    {
      // Data already in buffer
      int iWriteSize = size - cmd->len;
      if(iWriteSize > bytesleft)
        iWriteSize = bytesleft;

      iBytesWrite = files_[cmd->fd].file.write(&data[cmd->len], iWriteSize);
      bytesleft -= iBytesWrite;
    }
/*
    if(bytesleft > 0)
    {
      buffer = new char[bytesleft];

      //while(bytes > 0)
      //{
        // Receive data
        iBytesRead = sockTcp_.read(buffer, bytesleft);

        // Write data
        iBytesWrite = files_[cmd->fd].file.write(buffer, iBytesRead);
        bytesleft -= iBytesWrite;
      //}
    }
*/
  }
  else
  {
    debug("ConsoleLink: Failed to write to file!\n");
  }

  //qDebug("ps2RequestWrite: %d bytes written", cmd->nbytes - bytesleft);

  // Reply with the result
  ps2ReplyWrite(cmd->nbytes - bytesleft);

  if(buffer != NULL)
    delete buffer;
}

//----------------------------------------------------------------------------
void
CPS2FileServer::ps2RequestLSeek(char * data, int size)
{
  //qDebug("ps2RequestLSeek");

  qint64 newPos = 0;
  pko_pkt_lseek_req * cmd = (pko_pkt_lseek_req *)data;
  cmd->fd     = ntohl(cmd->fd);
  cmd->offset = ntohl(cmd->offset);
  cmd->whence = ntohl(cmd->whence);

  if((cmd->fd >= 0) && (cmd->fd < MAX_OPEN_FILES))
  {
    switch(cmd->whence)
    {
      case SEEK_SET: newPos = cmd->offset; break;
      case SEEK_CUR: newPos = files_[cmd->fd].file.pos() + cmd->offset; break;
      case SEEK_END: newPos = files_[cmd->fd].file.size() + cmd->offset; break;
    }

    files_[cmd->fd].file.seek(cmd->offset);
  }
  else
  {
    debug("ConsoleLink: LSeek Failed!\n");
  }

  // Reply with the result
  ps2ReplyLSeek(newPos);
}

//----------------------------------------------------------------------------
void
CPS2FileServer::ps2RequestOpenDir(char * data, int size)
{
  debug("ConsoleLink: ps2RequestOpenDir not implemented!\n");

  //ps2ReplyOpenDir();
}

//----------------------------------------------------------------------------
void
CPS2FileServer::ps2RequestCloseDir(char * data, int size)
{
  debug("ConsoleLink: ps2RequestCloseDir not implemented!\n");

  //ps2ReplyCloseDir();
}

//----------------------------------------------------------------------------
void
CPS2FileServer::ps2RequestReadDir(char * data, int size)
{
  debug("ConsoleLink: ps2RequestReadDir not implemented!\n");

  //ps2ReplyReadDir();
}

//----------------------------------------------------------------------------
void
CPS2FileServer::ps2RequestRemove(char * data, int size)
{
  debug("ConsoleLink: ps2RequestRemove not implemented!\n");

  //ps2ReplyRemove();
}

//----------------------------------------------------------------------------
void
CPS2FileServer::ps2RequestMkDir(char * data, int size)
{
  debug("ConsoleLink: ps2RequestMkDir not implemented!\n");

  //ps2ReplyMkDir();
}

//----------------------------------------------------------------------------
void
CPS2FileServer::ps2RequestRmDir(char * data, int size)
{
  debug("ConsoleLink: ps2RequestRmDir not implemented!\n");

  //ps2ReplyRmDir();
}

//----------------------------------------------------------------------------
// Reply for PS2 Command Requests
//----------------------------------------------------------------------------
void
CPS2FileServer::ps2ReplyOpen(int result)
{
  pko_pkt_file_rly reply;

  reply.cmd    = htonl(PS2LINK_RESPONSE_OPEN);
  reply.len    = htons(sizeof(reply));
  reply.retval = htonl(result);

  sockTcp_.write((const char *)&reply, sizeof(reply));
}

//----------------------------------------------------------------------------
void
CPS2FileServer::ps2ReplyClose(int result)
{
  pko_pkt_file_rly reply;

  reply.cmd    = htonl(PS2LINK_RESPONSE_CLOSE);
  reply.len    = htons(sizeof(reply));
  reply.retval = htonl(result);

  sockTcp_.write((const char *)&reply, sizeof(reply));
}

//----------------------------------------------------------------------------
void
CPS2FileServer::ps2ReplyRead(int result, int size)
{
  pko_pkt_read_rly reply;

  reply.cmd    = htonl(PS2LINK_RESPONSE_READ);
  reply.len    = htons(sizeof(reply));
  reply.retval = htonl(result);
  reply.nbytes = htonl(size);

  sockTcp_.write((const char *)&reply, sizeof(reply));
}

//----------------------------------------------------------------------------
void
CPS2FileServer::ps2ReplyWrite(int result)
{
  pko_pkt_file_rly reply;

  reply.cmd    = htonl(PS2LINK_RESPONSE_WRITE);
  reply.len    = htons(sizeof(reply));
  reply.retval = htonl(result);

  sockTcp_.write((const char *)&reply, sizeof(reply));
}

//----------------------------------------------------------------------------
void
CPS2FileServer::ps2ReplyLSeek(int result)
{
  pko_pkt_file_rly reply;

  reply.cmd    = htonl(PS2LINK_RESPONSE_LSEEK);
  reply.len    = htons(sizeof(reply));
  reply.retval = htonl(result);

  sockTcp_.write((const char *)&reply, sizeof(reply));
}

//----------------------------------------------------------------------------
void
CPS2FileServer::ps2ReplyOpenDir(int result)
{
  pko_pkt_file_rly reply;

  reply.cmd    = htonl(PS2LINK_RESPONSE_OPENDIR);
  reply.len    = htons(sizeof(reply));
  reply.retval = htonl(result);

  sockTcp_.write((const char *)&reply, sizeof(reply));
}

//----------------------------------------------------------------------------
void
CPS2FileServer::ps2ReplyCloseDir(int result)
{
  pko_pkt_file_rly reply;

  reply.cmd    = htonl(PS2LINK_RESPONSE_CLOSEDIR);
  reply.len    = htons(sizeof(reply));
  reply.retval = htonl(result);

  sockTcp_.write((const char *)&reply, sizeof(reply));
}

//----------------------------------------------------------------------------
void
CPS2FileServer::ps2ReplyReadDir(int result, unsigned int mode, unsigned int attr, unsigned int size, unsigned char *ctime, unsigned char *atime, unsigned char *mtime, unsigned int hisize, char *name)
{
  pko_pkt_dread_rly reply;

  reply.cmd    = htonl(PS2LINK_RESPONSE_READDIR);
  reply.len    = htons(sizeof(reply));
  reply.retval = htonl(result);
  // FIXME

  sockTcp_.write((const char *)&reply, sizeof(reply));
}

//----------------------------------------------------------------------------
void
CPS2FileServer::ps2ReplyRemove(int result)
{
  pko_pkt_file_rly reply;

  reply.cmd    = htonl(PS2LINK_RESPONSE_REMOVE);
  reply.len    = htons(sizeof(reply));
  reply.retval = htonl(result);

  sockTcp_.write((const char *)&reply, sizeof(reply));
}

//----------------------------------------------------------------------------
void
CPS2FileServer::ps2ReplyMkDir(int result)
{
  pko_pkt_file_rly reply;

  reply.cmd    = htonl(PS2LINK_RESPONSE_MKDIR);
  reply.len    = htons(sizeof(reply));
  reply.retval = htonl(result);

  sockTcp_.write((const char *)&reply, sizeof(reply));
}

//----------------------------------------------------------------------------
void
CPS2FileServer::ps2ReplyRmDir(int result)
{
  pko_pkt_file_rly reply;

  reply.cmd    = htonl(PS2LINK_RESPONSE_RMDIR);
  reply.len    = htons(sizeof(reply));
  reply.retval = htonl(result);

  sockTcp_.write((const char *)&reply, sizeof(reply));
}
