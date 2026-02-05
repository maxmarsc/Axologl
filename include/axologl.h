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

#include "file.h"
#include "types.h"
#include "loggers/debug.h"
#include "loggers/info.h"
#include "loggers/notice.h"
#include "loggers/warn.h"
#include "loggers/error.h"
#include "loggers/fatal.h"
#include "loggers/raw.h"

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
        logger::RawLogger rawLogger;
        bool nxlinkEnabled = false;

    public:
        explicit Axologl(const NxLinkOptions& opts)
        {
            if (opts.enable)
            {
                nxlinkEnabled = true;
                socketInitializeDefault();
                nxlinkConnectToHost(opts.redirectStdout, opts.redirectStderr);
            }
            debug("Axologl Initialised!");
        }

        ~Axologl()
        {
            debug("Axologl shutting down...");
            if (nxlinkEnabled)
            {
                socketExit();
            }
        }

        [[nodiscard]] bool getNxlinkEnabled() const
        {
            return nxlinkEnabled;
        }

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

        void log(std::string text)
        {
            this->rawLogger.log(text);
        }
    };

    inline Axologl* _axologl = nullptr;
    inline FileLogger* _fileLogger = nullptr;
    inline LogLevel _logLevel;
    inline bool _ansi = false;
    inline bool _logfileEnabled = false;
    inline std::string _logPath;

    inline void configure(const AxologlOptions& options)
    {
        if (_axologl != nullptr)
        {
            _axologl->error("Axologl has already been configured!");
            _axologl->error("If you need to change the configuration options, make use of the `set<option>` commands.");
            return;
        }

        _logLevel = options.logLevel;
        _ansi = options.ansiOutput;

        if (!options.logPath.empty())
        {
            _logPath = options.logPath;
            try
            {
                _fileLogger = new FileLogger(options.logPath);
                _logfileEnabled = true;
            }
            catch (const std::exception& e)
            {
                _axologl->error("Unable to create file logger; disabling file logging");
                _axologl->error(e.what());
            }
        }

        _axologl = new Axologl(options.nxLinkOpts);
    }

    inline void teardown()
    {
        delete _axologl;
    }

    inline void printConfiguration()
    {
        _axologl->debug("Axologl Configuration:");
        _axologl->debug("Log Level: " + std::to_string(_logLevel));
        const std::string nxlinkStatus = "nxlink: ";
        _axologl->debug(nxlinkStatus + (_axologl->getNxlinkEnabled() ? "enabled" : "disabled"));
        const std::string ansiStatus = "ANSI Output: ";
        _axologl->debug(ansiStatus + (_ansi ? "enabled" : "disabled"));
        if (_logfileEnabled)
        {
            _axologl->debug("Logging to file: " + _logPath);
        }
        else
        {
            _axologl->debug("Logging to file not enabled");
        }
    }

    inline void enableAnsi()
    {
        _ansi = true;
    }

    inline void disableAnsi()
    {
        _ansi = false;
    }

    inline void setLogLevel(const LogLevel level)
    {
        _logLevel = level;
    }

    inline void log(const std::string& text)
    {
        _axologl->log(text);
    }

    inline void debug(const std::string& text)
    {
        _axologl->debug(text);
    }

    inline void info(const std::string& text)
    {
        _axologl->info(text);
    }

    inline void notice(const std::string& text)
    {
        _axologl->notice(text);
    }

    inline void warn(const std::string& text)
    {
        _axologl->warn(text);
    }

    inline void error(const std::string& text)
    {
        _axologl->error(text);
    }

    inline void fatal(const std::string& text)
    {
        _axologl->fatal(text);
    }
}
#endif //AXOLOGL_AXOLOGL_H
