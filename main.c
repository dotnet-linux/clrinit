/*
 * PROJECT:   MinClr (.NET/Linux)
 * FILE:      main.c
 * PURPOSE:   Implementation for clrinit
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "nolibc.h"

void simple_printf(
    const char* string)
{
    const int stdout_fd = 1;
    write(stdout_fd, string, strlen(string));
}

int main()
{
    if (-1 == mount(
        "udev",
        "/dev",
        "devtmpfs",
        MS_NOSUID | MS_NOEXEC | MS_RELATIME,
        "size=10240k,mode=755") && errno != EBUSY)
    {
        simple_printf("clrinit: Failed to mount /dev.\n");
    }

    if (-1 == mount(
        "proc",
        "/proc",
        "proc",
        MS_NOSUID | MS_NOEXEC | MS_RELATIME | MS_NODEV,
        NULL) && errno != EBUSY)
    {
        simple_printf("clrinit: Failed to mount /proc.\n");
    }

    if (-1 == mount(
        "sysfs",
        "/sys",
        "sysfs",
        MS_NOSUID | MS_NOEXEC | MS_RELATIME | MS_NODEV,
        NULL) && errno != EBUSY)
    {
        simple_printf("clrinit: Failed to mount /sys.\n");
    }

    if (-1 == mount(
        "tmpfs",
        "/tmp",
        "tmpfs",
        0,
        NULL))
    {
        simple_printf("clrinit: Failed to mount /tmp to tmpfs.\n");
    }

    const char* envp[] =
    {
        "DOTNET_ROOT=/opt/minclr/dotnet",
        "PATH=/opt/minclr/dotnet:/usr/sbin:/usr/bin:/sbin:/bin",
        "TERM=xterm-256color",
        NULL
    };

    const char* argv[] =
    {
        "/opt/minclr/dotnet/dotnet",
        "/opt/minclr/runtime/MinClr.Init.dll",
        NULL
    };

    execve(argv[0], (char* const*)argv, (char* const*)envp);

    simple_printf("clrinit: Failed to start MinClr.Init.\n");

    return 0;
}