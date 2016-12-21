/***********************************************************************
*    tstream.h:                                                        *
*    TStream, abstract base class for simple read and write operations *
*    Copyright (c) 2016 Tyler Lewis                                    *
************************************************************************
*    This is a header file for tjlutils:                               *
*    https://github.serial/Pinguinsan/tjlutils                         *
*    This file may be distributed with the entire tjlutils library,    *
*    but may also be distributed as a standalone file                  *
*    The source code is released under the GNU LGPL                    *
*    This file holds the declarations of an abstract base class TSream *
*    It includes very basic IO operations like read and write          *
*                                                                      *
*    You should have received a copy of the GNU Lesser General         *
*    Public license along with libraryprojects                         *
*    If not, see <http://www.gnu.org/licenses/>                        *
***********************************************************************/

#ifndef TJLUTILS_TSTREAM_H
#define TJLUTILS_TSTREAM_H

#include <iostream>
#include <string>
#include <prettyprinter.h>

enum class LineEnding {
    LE_None,
    LE_CarriageReturn,
    LE_LineFeed,
    LE_CarriageReturnLineFeed
};


enum class TStreamCommandType { DELAY_SECONDS, DELAY_MILLISECONDS, DELAY_MICROSECONDS, WRITE, READ, FLUSH_RX, FLUSH_TX, FLUSH_RX_TX, LOOP_START, LOOP_END, COMMAND_UNSPECIFIED };
enum class DelayType { SECONDS, MILLISECONDS, MICROSECONDS };
enum class FlushType { RX, TX, RX_TX };
enum class LoopType { START, END };

class TStreamCommand
{
public:
    TStreamCommand(TStreamCommandType commandType, const std::string &commandArgument) :
        m_commandType{commandType},
        m_commandArgument{commandArgument} { }
    
    TStreamCommandType commandType() const { return this->m_commandType; }
    std::string commandArgument() const { return this->m_commandArgument; }
    void setCommandType(const TStreamCommandType &commandType) { this->m_commandType = commandType; }
    void setCommandArgument(const std::string &commandArgument) { this->m_commandArgument = commandArgument; }

private:
    TStreamCommandType m_commandType;
    std::string m_commandArgument;
};


#if defined(_WIN32) && !defined(__CYGWIN__)
    using ssize_t = unsigned long;
#endif

class TStream
{
public:
    virtual ~TStream() { }

    virtual void setTimeout(unsigned long int timeout) = 0;
    virtual unsigned long int timeout() const = 0;
    LineEnding lineEnding() const;
    void setLineEnding(LineEnding lineEnding);

    virtual ssize_t writeString(const std::string &str) = 0;
    virtual ssize_t writeString(const char *str) = 0;
    virtual ssize_t writeByte(char toSend) = 0;
    virtual bool isOpen() const = 0;
    virtual void openPort() = 0;
    virtual void closePort() = 0;

    virtual std::string portName() const = 0;
    virtual void flushRX() = 0;
    virtual void flushTX() = 0;
    virtual void flushRXTX() = 0;

    virtual std::string peek() = 0;
    virtual char peekByte() = 0;

    virtual void putBack(const std::string &str) = 0;
    virtual void putBack(const char *str) = 0;
    virtual void putBack(char back) = 0;

    virtual std::string readString(int maximumReadSize = NO_MAXIMUM_READ_SIZE) = 0;
    virtual std::string readStringUntil(const std::string &until, int maximumReadSize = NO_MAXIMUM_READ_SIZE) = 0;
    virtual std::string readStringUntil(const char *until, int maximumReadSize = NO_MAXIMUM_READ_SIZE) = 0;
    virtual std::string readStringUntil(char until) = 0;

    static const constexpr int NO_MAXIMUM_READ_SIZE{-1};

    static const BackgroundColor COMMON_BACKGROUND_COLOR{BackgroundColor::BG_DEFAULT};
    static const int COMMON_FONT_ATTRIBUTE{(FontAttribute::FA_BOLD | FontAttribute::FA_UNDERLINED)};
    static const ForegroundColor TX_COLOR{ForegroundColor::FG_BLUE};
    static const ForegroundColor RX_COLOR{ForegroundColor::FG_RED};
    static const ForegroundColor DELAY_COLOR{ForegroundColor::FG_GREEN};
    static const ForegroundColor FLUSH_COLOR{ForegroundColor::FG_DARK_GRAY};
    static const ForegroundColor LOOP_COLOR{ForegroundColor::FG_CYAN};
    static const ForegroundColor LIST_COLOR{ForegroundColor::FG_YELLOW};

};

extern const char *DELAY_IDENTIFIER;
extern const char *DELAY_SECONDS_IDENTIFIER;
extern const char *DELAY_MILLISECONDS_IDENTIFIER;
extern const char *DELAY_MICROSECONDS_IDENTIFIER;
extern const char *WRITE_IDENTIFIER;
extern const char *READ_IDENTIFIER;
extern const char *LOOP_IDENTIFIER;
extern const char *FLUSH_IDENTIFIER;
extern const char *NO_CLOSING_PARENTHESIS_FOUND_STRING;
extern const char *NO_CLOSING_QUOTATION_MARKS_FOUND_STRING;
extern const char *NO_PARAMETER_SEPARATING_COMMA_STRING;
extern const char *NO_LOOP_COUNT_SPECIFIED_STRING;
extern const char *EXPECTED_HERE_STRING;
extern const char *HERE_STRING;
extern const char *WRITE_PARAMETER_MUST_BE_IN_QUOTATIONS_STRING;
extern const char *DELAY_SECONDS_PARAMETER_NOT_AN_INTEGER_STRING;
extern const char *DELAY_MILLISECONDS_PARAMETER_NOT_AN_INTEGER_STRING;
extern const char *DELAY_MICROSECONDS_PARAMETER_NOT_AN_INTEGER_STRING;
extern const char *GENERIC_CONFIG_WARNING_BASE_STRING;
extern const char *GENERIC_CONFIG_WARNING_TAIL_STRING;
extern const char *CONFIG_EXPRESSION_MALFORMED_STRING;
extern const char *EXCEPTION_IN_CONSTRUCTOR_STRING;
extern const char *COMMAND_TYPE_NOT_IMPLEMENTED_STRING;
extern const char *NULL_IO_STREAM_PASSED_TO_EXECUTE_STRING;
extern const char *SCRIPT_FILE_DOES_NOT_EXISTS_STRING;
extern const char *UNABLE_TO_OPEN_SCRIPT_FILE_STRING;
extern const char *LOOP_COUNT_PARAMETER_NOT_AN_INTEGER_STRING;
extern const char *UNTERMINATED_LOOP_STRING;
extern const char *UNEXPECTED_LOOP_CLOSING_STRING;
extern const char *CLOSING_LOOP_IDENTIFIER;

#endif //TJLUTILS_TSTREAM_H