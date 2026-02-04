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

#ifndef AXOLOGL_LOGGER_H
#define AXOLOGL_LOGGER_H

#include <iostream>
#include <string>

#include <types.h>

namespace axologl
{
    extern bool ansi;
    extern LogLevel logLevel;

    class Logger
    {
        std::string ansiReset = "\033[0m";

        void format(std::string& text)
        {
            text.insert(0, 1, ' ');
            text.insert(0, 1, ']');
            text.insert(0, this->getPrefix());
            text.insert(0, 1, '[');
        }

        void colorize(std::string& text)
        {
            text.insert(0, this->getAnsiCode());
            text.append(this->ansiReset);
        }

        bool shouldLog()
        {
            return (this->getLogLevel() >= logLevel);
        }

        void logToFile(const std::string& text);

        static void logToStdout(const std::string& text)
        {
            std::cout << text << std::endl;
        }

        static void logToStderr(const std::string& text)
        {
            std::cerr << text << std::endl;
        }

    protected:
        virtual std::string getPrefix();
        virtual std::string getAnsiCode();
        virtual LogLevel getLogLevel();

    public:
        virtual ~Logger() = default;

        void log(std::string& text)
        {
            if (shouldLog())
            {
                format(text);
                if (ansi) colorize(text);
                logToStdout(text);
                logToStderr(text);
            }
        }
    };
}

#endif //AXOLOGL_LOGGER_H
