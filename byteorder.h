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


#ifndef BYTEORDER_H
#define BYTEORDER_H


#ifdef BIG_ENDIAN
inline unsigned int   htonl(unsigned int   x) { return x; }
inline unsigned short htons(unsigned short x) { return x; }
#else
inline unsigned int htonl(unsigned int x)
{
    return
        ((x & 0x000000ff) << 24 ) |
        ((x & 0x0000ff00) <<  8 ) |
        ((x & 0x00ff0000) >>  8 ) |
        ((x & 0xff000000) >> 24 );
}
inline unsigned short htons(unsigned short x)
{
    return
        ((x & 0x00ff) << 8 ) |
        ((x & 0xff00) >> 8 );
}
#endif

#define ntohl htonl
#define ntohs htons


#endif
