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


#ifndef SCREENSHOT_H
#define SCREENSHOT_H


#include <QObject>
#include <QImage>


//----------------------------------------------------------------------------
class CScreenshotReceiver
 : public QObject
{
  Q_OBJECT

public:
  CScreenshotReceiver();
  virtual ~CScreenshotReceiver();

  void screenshotStart();
  void screenshotData(unsigned char * data, int size);
  void screenshotEnd();

signals:
  void screenshotUpdated(const QImage & screenshot);
  void screenshotDone(const QImage & screenshot);

private:
  void screenshotPutPixel(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

private:
  QImage * screenshot_;

  int iWidth_;
  int iHeight_;
  int iPixelSize_;

  int currentSSWidth_;
  int currentSSHeight_;
  int bytesLeft_;
  int halfPixel_;
  int lastLine_;

  bool screenshotStart_;
  bool screenshotHeader_;
};


#endif
