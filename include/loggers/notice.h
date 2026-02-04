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

#ifndef AXOLOGL_NOTICE_H
#define AXOLOGL_NOTICE_H
#include "logger.h"

namespace axologl::logger
{
    class NoticeLogger : public Logger
    {
        const LogLevel logLevel = Notice;
        const std::string prefix = "NOTICE";
        const std::string ansiCode;

    protected:
        std::string getPrefix() override
        {
            return prefix;
        }

        std::string getAnsiCode() override
        {
            return ansiCode;
        }

        LogLevel getLogLevel() override
        {
            return logLevel;
        }
    };
}
#endif //AXOLOGL_NOTICE_H
