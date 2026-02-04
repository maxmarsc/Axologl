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

#ifndef AXOLOGL_AXOLOGL_H
#define AXOLOGL_AXOLOGL_H
#include <string>
#include <iostream>
#include <switch.h>

#include "types.h"
#include "loggers/debug.h"
#include "loggers/info.h"
#include "loggers/notice.h"
#include "loggers/warn.h"
#include "loggers/error.h"
#include "loggers/fatal.h"

namespace axologl
{
    class Axologl
    {
        logger::DebugLogger debugLogger;
        logger::InfoLogger infoLogger;
        logger::NoticeLogger noticeLogger;
        logger::WarningLogger warnLogger;
        logger::ErrorLogger errorLogger;
        logger::FatalLogger fatalLogger;

    public:
        void debug(std::string text)
        {
            this->debugLogger.log(text);
        }

        void info(std::string text)
        {
            this->infoLogger.log(text);
        }

        void notice(std::string text)
        {
            this->noticeLogger.log(text);
        }

        void warn(std::string text)
        {
            this->warnLogger.log(text);
        }

        void error(std::string text)
        {
            this->errorLogger.log(text);
        }

        void fatal(std::string text)
        {
            this->fatalLogger.log(text);
        }
    };

    inline Axologl* axologl = nullptr;
    inline LogLevel logLevel;
    inline bool nxlinkEnabled = false;
    inline bool nxlinkErr = false;
    inline bool nxlinkOut = false;
    inline bool ansi = false;
    inline bool logfileEnabled = false;
    inline std::string logPath;

    inline void configure(const AxologlOptions& options)
    {
        if (axologl != nullptr)
        {
            axologl->error("Axologl has already been configured!");
            axologl->error("If you need to change the configuration options, make use of the `set<option>` commands.");
            return;
        }

        axologl = new Axologl();

        logLevel = options.logLevel;
        nxlinkEnabled = options.nxLinkOpts.enable;
        nxlinkErr = options.nxLinkOpts.redirectStderr;
        nxlinkOut = options.nxLinkOpts.redirectStdout;
        ansi = options.ansiOutput;

        if (nxlinkEnabled)
        {
            socketInitializeDefault();
            nxlinkConnectToHost(nxlinkOut, nxlinkErr);
        }

        if (!options.logPath.empty())
        {
            logPath = options.logPath;
            logfileEnabled = true;
        }
    }

    inline void teardown()
    {
        if (nxlinkEnabled)
        {
            socketExit();
        }
    }

    inline void printConfiguration()
    {
        axologl->debug("Axologl Configuration:");
        axologl->debug("Log Level: " + std::to_string(logLevel));
        const std::string nxlinkStatus = "nxlink: ";
        axologl->debug(nxlinkStatus + (nxlinkEnabled ? "enabled" : "disabled"));
        const std::string ansiStatus = "ANSI Output: ";
        axologl->debug(ansiStatus + (ansi ? "enabled" : "disabled"));
        if (logfileEnabled)
        {
            axologl->debug("Logging to file: " + logPath);
        }
        else
        {
            axologl->debug("Logging to file not enabled");
        }
    }

    inline void enableAnsi()
    {
        ansi = true;
    }

    inline void disableAnsi()
    {
        ansi = false;
    }

    inline void setLevel(const LogLevel level)
    {
        logLevel = level;
    }

    inline void debug(const std::string& text)
    {
        axologl->debug(text);
    }

    inline void info(const std::string& text)
    {
        axologl->info(text);
    }

    inline void notice(const std::string& text)
    {
        axologl->notice(text);
    }

    inline void warn(const std::string& text)
    {
        axologl->warn(text);
    }

    inline void error(const std::string& text)
    {
        axologl->error(text);
    }

    inline void fatal(const std::string& text)
    {
        axologl->fatal(text);
    }
}
#endif //AXOLOGL_AXOLOGL_H
