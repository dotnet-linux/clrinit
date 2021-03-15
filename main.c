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

size_t simple_strlen(
    const char* string_start)
{
    const char* string_end = string_start;
    while (*string_end) ++string_end;
    return string_end - string_start;
}

void simple_printf(
    const char* string)
{
    const int stderr_fd = 2;
    write(stderr_fd, string, simple_strlen(string));
}

int main()
{
    // Clear the screen.
    simple_printf("\033[H\033[J");

    if (-1 == mount(
        "udev",
        "/dev",
        "devtmpfs",
        MS_NOSUID | MS_NOEXEC | MS_RELATIME,
        "size=10240k,mode=755"))
    {
        simple_printf("clrinit: Failed to mount /dev.\n");
    }

    if (-1 == mount(
        "proc",
        "/proc",
        "proc",
        MS_NOSUID | MS_NOEXEC | MS_RELATIME | MS_NODEV,
        NULL))
    {
        simple_printf("clrinit: Failed to mount /proc.\n");
    }

    if (-1 == mount(
        "sysfs",
        "/sys",
        "sysfs",
        MS_NOSUID | MS_NOEXEC | MS_RELATIME | MS_NODEV,
        NULL))
    {
        simple_printf("clrinit: Failed to mount /sys.\n");
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