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


#include "ps2Screenshot.h"
#include "byteorder.h"


typedef struct
{
  unsigned short bpp;    // bits per pixel
  unsigned short width;  // screenshot width
  unsigned short height; // screenshot height
} __attribute__((packed)) ps2_screenshot_header;


//----------------------------------------------------------------------------
CScreenshotReceiver::CScreenshotReceiver()
 : screenshot_(NULL)
 , bytesLeft_(0)
 , screenshotStart_(false)
 , screenshotHeader_(false)
{
}

//----------------------------------------------------------------------------
CScreenshotReceiver::~CScreenshotReceiver()
{
  if(screenshot_ != NULL)
    delete screenshot_;
}

//----------------------------------------------------------------------------
void
CScreenshotReceiver::screenshotStart()
{
  currentSSWidth_ = 0;
  currentSSHeight_ = 0;
  bytesLeft_ = 0;
  lastLine_ = 0;

  // Accept incomming screenshot data
  screenshotStart_ = true;
  // We need a header first
  screenshotHeader_ = false;
}

//----------------------------------------------------------------------------
void
CScreenshotReceiver::screenshotData(unsigned char * data, int size)
{
  if(screenshotStart_ == false)
  {
    qDebug("screenshotData: ERROR: No screenshot active");
    return;
  }

  if(screenshotHeader_ == false)
  {
    // Wait for header
    if(size == sizeof(ps2_screenshot_header))
    {
      // header found!
      ps2_screenshot_header * pHDR = (ps2_screenshot_header *)data;

      // Extract information
      iWidth_     = ntohs(pHDR->width);
      iHeight_    = ntohs(pHDR->height);
      iPixelSize_ = ntohs(pHDR->bpp) / 8;

      // Allocate new screenshot
      if(screenshot_ != NULL)
        delete screenshot_;
      screenshot_ = new QImage(iWidth_, iHeight_, QImage::Format_ARGB32);

      // Fill white
      screenshot_->fill(0xffffffff);

      screenshotHeader_ = true;
    }
  }
  else
  {
    // Draw splitted pixels from previous data stream, if any
    if(bytesLeft_ > 0)
    {
/*
      switch(bytesLeft_)
      {
        case 1:
          halfPixel_ = halfPixel_ | (data[2] << 24) | (data[1] << 16) | (data[0] << 8);
          break;
        case 2:
          halfPixel_ = halfPixel_ | (data[1] << 24) | (data[0] << 16);
          break;
        case 3:
          halfPixel_ = halfPixel_ | (data[0] << 24);
          break;
      };
*/
      this->screenshotPutPixel(0, 0, 0, 0);
    }
    int byteScip = (iPixelSize_ - bytesLeft_) % iPixelSize_;
    int pixels = (size - byteScip) / iPixelSize_;
    bytesLeft_ = (size - byteScip) % iPixelSize_;

    // Save splitted pixels at the end of the data stream
    if(bytesLeft_ > 0)
    {
/*
      switch(bytesLeft_)
      {
        case 1:
          halfPixel_ = (data[size-1] << 0);
          break;
        case 2:
          halfPixel_ = (data[size-2] << 0) | (data[size-1] << 8);
          break;
        case 3:
          halfPixel_ = (data[size-3] << 0) | (data[size-2] << 8) | (data[size-1] << 16);
          break;
      };
*/
    }

    // Draw pixels
    switch(iPixelSize_)
    {
      case 2:
      {
        unsigned short * pPixels = (unsigned short *)(&data[byteScip]);
        unsigned short px;
        unsigned char r, g, b, a;
        for(int i(0); i < pixels; i++)
        {
          px = pPixels[i];
          r = (px & 0x001f) << 3;
          g = (px & 0x03e0) >> 2;
          b = (px & 0x7c00) >> 7;
          a = 0xff;

          this->screenshotPutPixel(r, g, b, a);
        }
        break;
      }
      case 3:
      {
        unsigned char * pPixels = (unsigned char *)(&data[byteScip]);
        unsigned char r, g, b, a;
        for(int i(0); i < pixels; i++)
        {
          r = pPixels[i*3];
          g = pPixels[i*3+1];
          b = pPixels[i*3+2];
          a = 0xff;

          this->screenshotPutPixel(r, g, b, a);
        }
        break;
      }
      case 4:
      {
        unsigned int * pPixels = (unsigned int *)(&data[byteScip]);
        unsigned int px;
        unsigned char r, g, b, a;
        for(int i(0); i < pixels; i++)
        {
          px = pPixels[i];
          r = (px & 0x000000ff);
          g = (px & 0x0000ff00) >>  8;
          b = (px & 0x00ff0000) >> 16;
          a = 0xff;

          this->screenshotPutPixel(r, g, b, a);
        }
        break;
      }
    };

    // Show on screen
    if(currentSSHeight_ != lastLine_)
    {
      lastLine_ = currentSSHeight_;

      emit screenshotUpdated(*screenshot_);
    }
  }
}

//----------------------------------------------------------------------------
void
CScreenshotReceiver::screenshotEnd()
{
  // Stop processing screenshot data
  screenshotStart_ = false;

  emit screenshotDone(*screenshot_);
}

//----------------------------------------------------------------------------
void
CScreenshotReceiver::screenshotPutPixel(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
  screenshot_->setPixel(currentSSWidth_, currentSSHeight_, (a<<24) | (r<<16) | (g<<8) | b);

  currentSSWidth_++;
  if(currentSSWidth_ >= iWidth_)
  {
    currentSSWidth_ = 0;
    currentSSHeight_++;
    if(currentSSHeight_ >= iHeight_)
    {
      // End?
      currentSSHeight_ = 0;
    }
  }
}
