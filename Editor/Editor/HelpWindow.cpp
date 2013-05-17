#include    <fstream>

#include "HelpWindow.h"

HelpWindow::HelpWindow(QWidget *parent) :
    QDialog(parent)
{
    m_pText = new QTextEdit(this);
    m_pVBox = new QVBoxLayout;
    std::ifstream   in;
    std::string     line;

    setWindowTitle("Help");
    m_pText->setReadOnly(true);
    m_pVBox->addWidget(m_pText);
    setMinimumSize(600, 480);
    in.open("./Help/help.html");
    if (in.is_open() == true)
    {
        while (in.eof() == false)
        {
            std::getline(in, line);
            m_pText->setText(QString(m_pText->toHtml() + QString(line.c_str())));
        }
        in.close();
    }
    else
        m_pText->setText(QString("<h1>Help file not found</h1>"));
    setLayout(m_pVBox);
}

HelpWindow::~HelpWindow()
{
    delete m_pText;
    delete m_pVBox;
}
