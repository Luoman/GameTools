#include <QDesktopWidget>
#include <QApplication>

#include "WindowCreate.h"
#include "Convert.hh"
#include "mainwindow.h"

#include <iostream>

WindowCreate::WindowCreate(QWidget *parent) :
    QDialog(parent)
{
//    QDesktopWidget *a = qApp->desktop();

    setFixedSize(200, 130);
//    move(a->width() / 2 - width() / 2, a->height() / 2 - height() / 2 - 25);
    m_pCreate = new QPushButton("Create", this);
    m_pCancel = new QPushButton("Cancel", this);
    m_pLWidth = new QLabel("Width : ", this);
    m_pLHeight = new QLabel("Height : ", this);
    m_pLName = new QLabel("Project Name : ", this);
    m_pWidth = new QComboBox(this);
    m_pHeight = new QComboBox(this);
    m_pGrid = new QGridLayout(this);
    m_pProjectName = new QLineEdit("untitled", this);
    m_pGrid->addWidget(m_pLWidth, 0, 0);
    m_pGrid->addWidget(m_pWidth, 0, 1);
    m_pGrid->addWidget(m_pLHeight, 1, 0);
    m_pGrid->addWidget(m_pHeight, 1, 1);
    m_pGrid->addWidget(m_pLName, 2, 0);
    m_pGrid->addWidget(m_pProjectName, 2, 1);
    m_pGrid->addWidget(m_pCreate, 4, 1);
    m_pGrid->addWidget(m_pCancel, 4, 0);
    setWindowTitle("Create Map");
    for (int i = 3 ;i < 20; ++i)
    {
        m_pWidth->addItem(QString(intToString(i * ROOM_WIDTH).c_str()));
        m_pHeight->addItem(QString(intToString(i * ROOM_HEIGHT).c_str()));
    }
    connect(m_pCancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_pCreate, SIGNAL(clicked()), this, SLOT(create()));
}

WindowCreate::~WindowCreate()
{
    delete m_pCreate;
    delete m_pCancel;
}

void WindowCreate::create()
{
    m_bCreate = true;
    close();
}

void WindowCreate::setCreate(bool create)
{
    m_bCreate = create;
}

bool WindowCreate::getCreate() const
{
    return (m_bCreate);
}

int WindowCreate::getWidth() const
{
    return (stringToInt(m_pWidth->currentText().toStdString()));
}

int WindowCreate::getHeight() const
{
    return (stringToInt(m_pHeight->currentText().toStdString()));
}

std::string WindowCreate::getProjectName() const
{
    std::cout << m_pProjectName->text().toStdString() << std::endl;
    return (m_pProjectName->text().toStdString());
}
