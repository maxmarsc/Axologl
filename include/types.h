/*
 *     Axologl - A simple logging library designed to integrate with libnx
 *     Copyright (C) 2026. Xerat0nin
 *
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef AXOLOGL_TYPES_H
#define AXOLOGL_TYPES_H

#include <string>

#include <switch.h>

namespace axologl
{
    enum LogLevel
    {
        Debug,
        Info,
        Notice,
        Warning,
        Error,
        Fatal,
        Raw
    };

    /**
     * @struct NxLinkOptions
     *
     * @brief A collection of configuration options for nxlink
     *
     * @param enable            Whether to enable nxlink
     * @param redirectStdout    Whether to forward `stdout` to nxlink host
     * @param redirectStderr    Whether to forward `stderr` to nxlink host
     */
    struct NxLinkOptions
    {
        mutable bool enable = false;
        mutable bool redirectStdout = false;
        mutable bool redirectStderr = false;
    };

    struct FileLoggerOptions
    {
        bool enable = false;
        bool logStdout = false;
        bool logStderr = false;
    };

    /**
     * @struct AxologlOptions
     *
     * @brief A collection of configuration-time options for Axologl
     *
     * @param logLevel      The logging level to use by default
     * @param nxLinkOpts    A collection of options to configure nxlink
     * @param ansiOutput    Whether ANSI colours should be used
     * @param logPath       Where Axologl should write logs to
     */
    struct AxologlOptions
    {
        mutable LogLevel logLevel = Warning;
        mutable NxLinkOptions nxLinkOpts;
        mutable bool ansiOutput = true;
        mutable std::string logPath;
        mutable PrintConsole* console = nullptr;
    };
}

#endif //AXOLOGL_TYPES_H
