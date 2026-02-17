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

#ifndef AXOLOGL_DEBUG_H
#define AXOLOGL_DEBUG_H
#include "types.h"
#include "logger.h"

namespace axologl::logger
{
    class DebugLogger : public Logger
    {
        static constexpr LogLevel logLevel = Debug;
        static constexpr std::string_view prefix = "DEBUG";
        static constexpr std::string_view ansiCode = "\033[35m";

    protected:
        std::string_view getPrefix() override
        {
            return prefix;
        }

        std::string_view getAnsiCode() override
        {
            return ansiCode;
        }

        LogLevel getLogLevel() override
        {
            return logLevel;
        }
    };
}

#endif //AXOLOGL_DEBUG_H
