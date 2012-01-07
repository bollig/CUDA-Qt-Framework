// From: http://lists.trolltech.com/qt-interest/2005-06/thread00166-0.html
// Dont know why Qt isnt packaging this in their trunk yet....

//################
//# qdebugstream.h  #
//################

#ifndef Q_DEBUG_STREAM_H
#define Q_DEBUG_STREAM_H

#include <iostream>
#include <streambuf>
#include <string>

#include "qplaintextedit.h"

class QDebugStream : public std::basic_streambuf<char>
{
    public:
    QDebugStream(std::ostream &stream, QPlainTextEdit* text_edit) : m_stream(stream)
    {
        log_window = text_edit;
        m_old_buf = stream.rdbuf();
        stream.rdbuf(this);
    }
    ~QDebugStream()
    {
        // output anything that is left
        if (!m_string.empty())
            log_window->appendPlainText(m_string.c_str());

        m_stream.rdbuf(m_old_buf);
    }

    protected:
    virtual int_type overflow(int_type v)
    {
        if (v == '\n')
        {
            log_window->appendPlainText(m_string.c_str());
            m_string.erase(m_string.begin(), m_string.end());
        }
        else
            m_string += v;

        return v;
    }

    virtual std::streamsize xsputn(const char *p, std::streamsize n)
    {
        m_string.append(p, p + n);

        int pos = 0;
        while (pos != std::string::npos)
        {
            pos = m_string.find('\n');
            if (pos != std::string::npos)
            {
                std::string tmp(m_string.begin(), m_string.begin() + pos);
                log_window->appendPlainText(tmp.c_str());
                m_string.erase(m_string.begin(), m_string.begin() + pos + 1);
                //log_window->viewport()->repaint();
            }
        }

        return n;
    }

    private:
    std::ostream &m_stream;
    std::streambuf *m_old_buf;
    std::string m_string;
    QPlainTextEdit* log_window;
};

#endif
