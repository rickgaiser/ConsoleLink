/*********************************************************************
 * Copyright (C) 2003 Tord Lindstrom (pukko@home.se)
 * This file is subject to the terms and conditions of the PS2Link License.
 * See the file LICENSE in the main directory of this distribution for more
 * details.
 */

#define PKO_PORT                    0x4711
#define PKO_CMD_PORT	            0x4712
#define PKO_PRINTF_PORT	            0x4712

#define PS2LINK_REQUEST_OPEN	    0xBABE0111
#define PS2LINK_REQUEST_CLOSE	    0xBABE0121
#define PS2LINK_REQUEST_READ	    0xBABE0131
#define PS2LINK_REQUEST_WRITE	    0xBABE0141
#define PS2LINK_REQUEST_LSEEK	    0xBABE0151
#define PS2LINK_REQUEST_OPENDIR	    0xBABE0161
#define PS2LINK_REQUEST_CLOSEDIR    0xBABE0171
#define PS2LINK_REQUEST_READDIR	    0xBABE0181
#define PS2LINK_REQUEST_REMOVE	    0xBABE0191
#define PS2LINK_REQUEST_MKDIR	    0xBABE01A1
#define PS2LINK_REQUEST_RMDIR	    0xBABE01B1

#define PS2LINK_RESPONSE_OPEN	    0xBABE0112
#define PS2LINK_RESPONSE_CLOSE	    0xBABE0122
#define PS2LINK_RESPONSE_READ	    0xBABE0132
#define PS2LINK_RESPONSE_WRITE	    0xBABE0142
#define PS2LINK_RESPONSE_LSEEK	    0xBABE0152
#define PS2LINK_RESPONSE_OPENDIR    0xBABE0162
#define PS2LINK_RESPONSE_CLOSEDIR   0xBABE0172
#define PS2LINK_RESPONSE_READDIR    0xBABE0182
#define PS2LINK_RESPONSE_REMOVE	    0xBABE0192
#define PS2LINK_RESPONSE_MKDIR	    0xBABE01A2
#define PS2LINK_RESPONSE_RMDIR	    0xBABE01B2

#define PS2LINK_COMMAND_RESET	    0xBABE0201
#define PS2LINK_COMMAND_EXECIOP     0xBABE0202
#define PS2LINK_COMMAND_EXECEE	    0xBABE0203
#define PS2LINK_COMMAND_POWEROFF    0xBABE0204
#define PS2LINK_COMMAND_SCRDUMP     0xBABE0205
#define PS2LINK_COMMAND_NETDUMP     0xBABE0206
#define PS2LINK_COMMAND_DUMPMEM     0xBABE0207
#define PS2LINK_COMMAND_STARTVU     0xBABE0208
#define PS2LINK_COMMAND_STOPVU	    0xBABE0209
#define PS2LINK_COMMAND_DUMPREG     0xBABE020A
#define PS2LINK_COMMAND_GSEXEC	    0xBABE020B
#define PS2LINK_COMMAND_WRITEMEM    0xBABE020C
#define PS2LINK_COMMAND_IOPEXCEP    0xBABE020D
#define PS2LINK_COMMAND_SCREENSHOT  0xBABE020E
#define PS2LINK_COMMAND_SUSPEND     0xBABE020F
#define PS2LINK_COMMAND_RESUME      0xBABE0210

#define PKO_MAX_PATH                256


typedef struct
{
    unsigned int cmd;
    unsigned short len;
} __attribute__((packed)) pko_pkt_hdr;

typedef struct
{
    unsigned int cmd;
    unsigned short len;
    int retval;
} __attribute__((packed)) pko_pkt_file_rly;

typedef struct
{
    unsigned int cmd;
    unsigned short len;
    int flags;
    char path[PKO_MAX_PATH];
} __attribute__((packed)) pko_pkt_open_req;

typedef struct
{
    unsigned int cmd;
    unsigned short len;
    int fd;
} __attribute__((packed)) pko_pkt_close_req;

typedef struct
{
    unsigned int cmd;
    unsigned short len;
    int fd;
    int nbytes;
} __attribute__((packed)) pko_pkt_read_req;

typedef struct
{
    unsigned int cmd;
    unsigned short len;
    int retval;
    int nbytes;
} __attribute__((packed)) pko_pkt_read_rly;

typedef struct
{
    unsigned int cmd;
    unsigned short len;
    int fd;
    int nbytes;
} __attribute__((packed)) pko_pkt_write_req;

typedef struct
{
    unsigned int cmd;
    unsigned short len;
    int fd;
    int offset;
    int whence;
} __attribute__((packed)) pko_pkt_lseek_req;

typedef struct
{
    unsigned int cmd;
    unsigned short len;
    char name[PKO_MAX_PATH];
} __attribute__((packed)) pko_pkt_remove_req;

typedef struct
{
    unsigned int cmd;
    unsigned short len;
    int mode;
    char name[PKO_MAX_PATH];
} __attribute__((packed)) pko_pkt_mkdir_req;

typedef struct
{
    unsigned int cmd;
    unsigned short len;
    char name[PKO_MAX_PATH];
} __attribute__((packed)) pko_pkt_rmdir_req;

typedef struct
{
    unsigned int cmd;
    unsigned short len;
    int fd;
} __attribute__((packed)) pko_pkt_dread_req;

typedef struct
{
    unsigned int cmd;
    unsigned short len;
    int retval;
/* from io_common.h (fio_dirent_t) in ps2lib */
    unsigned int mode;
    unsigned int attr;
    unsigned int size;
    unsigned char ctime[8];
    unsigned char atime[8];
    unsigned char mtime[8];
    unsigned int hisize;
    char name[256];
} __attribute__((packed)) pko_pkt_dread_rly;

////

typedef struct
{
    unsigned int cmd;
    unsigned short len;
} __attribute__((packed)) pko_pkt_reset_req;

typedef struct
{
    unsigned int cmd;
    unsigned short len;
    int  argc;
    char argv[PKO_MAX_PATH];
} __attribute__((packed)) pko_pkt_execee_req;

typedef struct
{
    unsigned int cmd;
    unsigned short len;
    int  argc;
    char argv[PKO_MAX_PATH];
} __attribute__((packed)) pko_pkt_execiop_req;

typedef struct
{
	unsigned int cmd;
	unsigned short len;
	unsigned short size;
	unsigned char file[PKO_MAX_PATH];
} __attribute__((packed)) pko_pkt_gsexec_req;

typedef struct
{
    unsigned int cmd;
    unsigned short len;
} __attribute__((packed)) pko_pkt_poweroff_req;

typedef struct
{
    unsigned int cmd;
    unsigned short len;
    int vpu;
} __attribute__((packed)) pko_pkt_start_vu;

typedef struct
{
    unsigned int cmd;
    unsigned short len;
    int vpu;
} __attribute__((packed)) pko_pkt_stop_vu;

typedef struct
{
    unsigned int cmd;
    unsigned short len;
    unsigned int offset;
    unsigned int size;
    char argv[PKO_MAX_PATH];
} __attribute__((packed)) pko_pkt_mem_io;

typedef struct {
    unsigned int cmd;
    unsigned short len;
    int regs;
    char argv[PKO_MAX_PATH];
} __attribute__((packed)) pko_pkt_dump_regs;

typedef struct {
        unsigned int cmd;
        unsigned short len;
        unsigned int regs[79];
} __attribute__((packed)) pko_pkt_send_regs;

typedef struct {
        unsigned int cmd;
        unsigned short len;
        unsigned int base;
        unsigned int width;
        unsigned int height;
        unsigned short psm;
} __attribute__((packed)) pko_pkt_screenshot_req;

#define PKO_MAX_WRITE_SEGMENT (1460 - sizeof(pko_pkt_write_req))
#define PKO_MAX_READ_SEGMENT  (1460 - sizeof(pko_pkt_read_rly))
