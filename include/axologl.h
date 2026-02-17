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
    class Axologl final
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
                enableNxLink(opts);
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

        void enableNxLink(const NxLinkOptions& opts) {
            if (!nxlinkEnabled)
            {
                nxlinkEnabled = true;
                socketInitializeDefault();
                nxlinkConnectToHost(opts.redirectStdout, opts.redirectStderr);
            }
        }

        void disableNxLink() {
            if (nxlinkEnabled)
            {
                socketExit();
                nxlinkEnabled = false;
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

        void log(std::string text, const std::string* ansiCode = nullptr)
        {
            this->rawLogger.log(text, ansiCode);
        }
    };

    inline std::unique_ptr<Axologl> _axologl = nullptr;
    inline std::unique_ptr<FileLogger> _fileLogger = nullptr;
    inline LogLevel _logLevel;
    inline bool _ansi = false;
    inline bool _logfileEnabled = false;
    inline std::string _logPath;

    /**
     * Configure Axologl for use with the specified options. This should be called as early as possible.
     *
     * @param options A set of options to initialize Axologl with
     */
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
            _fileLogger = std::make_unique<FileLogger>(options.logPath);
            _logfileEnabled = _fileLogger && _fileLogger->ready();
        }

        _axologl = std::make_unique<Axologl>(options.nxLinkOpts);
        if (!_logfileEnabled)
        {
            _axologl->error("Unable to create file logger; file logging disabled!");
        }
    }

    /**
     * Perform clean-up related to the library. This should be called before `consoleExit()`.
     */
    inline void teardown()
    {
        _axologl.reset();
    }

    /**
     * Prints the current Axologl configuration
     */
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

    inline void enableNxLink(const NxLinkOptions& opts)
    {
        _axologl->enableNxLink(opts);
    }
    
    inline void disableNxLink()
    {
        _axologl->disableNxLink();
    }

    inline void setLogLevel(const LogLevel level)
    {
        _logLevel = level;
    }

    /**
     * Log a plain, unprefixed message
     *
     * @param text
     * @param color (Optional) An ANSI color code to colorize the message
     */
    inline void log(const std::string& text, const std::string* color = nullptr)
    {
        _axologl->log(text, color);
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

    /**
     * Log an unprefixed message in green (if ANSI colours are enabled)
     *
     * @param text
     */
    inline void success(const std::string& text)
    {
        const std::string green = "\033[32m";
        _axologl->log(text, &green);
    }

    /**
     * Log an unprefixed message in red (if ANSI colours are enabled)
     *
     * @param text
     */
    inline void failure(const std::string& text)
    {
        const std::string red = "\033[31m";
        _axologl->log(text, &red);
    }
}
#endif //AXOLOGL_AXOLOGL_H
