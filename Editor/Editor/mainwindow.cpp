#include        <QFileDialog>
#include        <QProgressBar>

#include        "mainwindow.h"
#include        "ui_mainwindow.h"

#include        "MapDisplay.hh"
#include        "TextureArea.h"
#include        "RoomDisplay.h"
#include        "Convert.hh"
#include        "XMLParse.hh"

#include        <Windows.h>

#include        <iostream>
#include        <fstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_pFileMenu = new QMenu("File");
    m_pHelpMenu = new QMenu("Help");
    m_pExitAction = new QAction("&Exit", this);
    m_pSaveAction = new QAction("&Save", this);
    m_pSaveAsAction = new QAction("Save as ...", this);
    m_pOpenAction = new QAction("&Open", this);
    m_pCreateAction = new QAction("&New", this);

    ui->setupUi(this);
    m_sTitle = " - Zelda Editor Dungeon Map";
    m_sProjectName = "Untitled.zme";
    m_sPath = "./Projects/";
    setWindowTitle(QString(m_sProjectName.substr(0, m_sProjectName.size() - 4).c_str()) + QString(m_sTitle.c_str()));
    setMinimumSize(650, 720);
    m_pWindowCreate = new WindowCreate(this);
    ImageManager::getSingleton()->setPath("./Pictures");
    ImageManager::getSingleton()->createListImage();
    m_pTextureArea = new TextureArea(parent, ui);
    ui->textureArea_bis->setWidget(m_pTextureArea);
    m_pMap = new MapDisplay(parent, ui, this);
    m_pMap->initialize(ROOM_WIDTH * 3, ROOM_HEIGHT * 3);
    m_pHelpWindow = new HelpWindow;
    ui->mapArea->setWidget(m_pMap);
    ui->menuBar->addMenu(m_pFileMenu);
    ui->menuBar->addMenu(m_pHelpMenu);
    m_pFileMenu->addAction(m_pOpenAction);
    m_pFileMenu->addAction(m_pCreateAction);
    m_pFileMenu->addAction(m_pSaveAction);
    m_pFileMenu->addAction(m_pSaveAsAction);
    m_pFileMenu->addAction(m_pExitAction);
    m_pCreateAction->setShortcut(QKeySequence("Ctrl+N"));
    m_pOpenAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pExitAction->setShortcut(QKeySequence("Ctrl+Q"));
    m_pSaveAsAction->setShortcut(QKeySequence("Ctrl+Alt+S"));
    m_pSaveAction->setShortcut(QKeySequence("Ctrl+S"));

    m_pSaveProgress = new QProgressBar(this);
    m_pLState = new QLabel("None", this);

    m_pSaveProgress->hide();
    ui->statusBar->addWidget(m_pLState);
    ui->statusBar->addWidget(m_pSaveProgress);

    ui->mainToolBar->hide();
    ui->imageMonster->setPixmap(ImageManager::getSingleton()->getMonsterImage("beetle"));
    ui->tabEdit->hide();
    connect(ui->tabMap, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    connect(ui->tabEdit, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));
    connect(ui->tabMap, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));
    connect(m_pExitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(m_pSaveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(m_pSaveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(m_pCreateAction, SIGNAL(triggered()), this, SLOT(createProject()));
    connect(m_pOpenAction, SIGNAL(triggered()), this, SLOT(openProject()));


    connect(ui->objectBox, SIGNAL(clicked(bool)), this, SLOT(boxObjectChecked(bool)));
    connect(ui->monsterBox, SIGNAL(clicked(bool)), this, SLOT(boxMonsterChecked(bool)));
    connect(ui->doorBox, SIGNAL(clicked(bool)), this, SLOT(boxDoorChecked(bool)));
    connect(ui->eventBox, SIGNAL(clicked(bool)), this, SLOT(boxEventChecked(bool)));
    connect(ui->objectType, SIGNAL(currentIndexChanged(QString)), this, SLOT(objectTypeChanged(QString)));
    connect(ui->monsterType, SIGNAL(currentIndexChanged(QString)), this, SLOT(monsterTypeChanged(QString)));
    connect(ui->eventType, SIGNAL(currentIndexChanged(QString)), this, SLOT(eventTypeChanged(QString)));
    connect(ui->applyButton, SIGNAL(clicked()), this, SLOT(apply()));
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(displayInfosBox()));
    connect(ui->defaultButton, SIGNAL(clicked()), this, SLOT(reset()));
    connect(m_pHelpMenu, SIGNAL(aboutToShow()), this, SLOT(helpMenu()));
}

MainWindow::~MainWindow()
{
    delete m_pFileMenu;
    delete m_pHelpMenu;
    delete m_pExitAction;
    delete m_pSaveAction;
    delete m_pSaveAsAction;
    delete m_pOpenAction;
    delete m_pCreateAction;
    delete m_pMap;
    delete m_pTextureArea;
    delete m_pWindowCreate;
    delete m_pSaveProgress;
    delete m_pLState;
    delete m_pHelpWindow;
    delete ui;
}

void            MainWindow::helpMenu()
{
    m_pHelpWindow->exec();
}

void            MainWindow::saveAs()
{
    QString     saveFile = QFileDialog::getSaveFileName(this, "Save", "./Projects", tr("Project Files (*.zme)"));
    int         nb;

    if (saveFile.isEmpty() == false)
    {
        m_bSave = false;
        m_sProjectName = saveFile.toStdString();
        if ((nb = m_sProjectName.rfind("/")) > 0)
        {
            m_sPath = m_sProjectName.substr(0, nb + 1);
            m_sProjectName = m_sProjectName.substr(nb + 1, m_sProjectName.size() - nb);
        }
        else
            m_sPath = "./";
//        std::cout << "Save File : " << m_sProjectName << " - path : "  << m_sPath << std::endl;
        setWindowTitle(QString(m_sProjectName.substr(0, m_sProjectName.size() - 4).c_str()) + QString(m_sTitle.c_str()));
        save();
    }
}

void            MainWindow::closeEvent(QCloseEvent *)
{
    bool        ret;

    if (m_bSave == false)
    {
        ret = confirmPopup(this, QString("The project has been modified."), QString("Do you want to save your changes?"), QMessageBox::No, QMessageBox::Save);
        if (ret == true)
            save();
    }
}

void            MainWindow::openProject()
{
    QString projectFile = QFileDialog::getOpenFileName(this, tr("Open Project"), "./Projects", tr("Project Files (*.zme)"));
    int         nb;
    XMLParse    xml;
    Map         *map;

    if (projectFile.isEmpty() == false)
    {
        m_sProjectName = projectFile.toStdString();
        if ((nb = m_sProjectName.rfind("/")) > 0)
        {
            m_sPath = m_sProjectName.substr(0, nb + 1);
            m_sProjectName = m_sProjectName.substr(nb + 1, m_sProjectName.size() - nb);
        }
        else
            m_sPath = "./";
        m_pSaveProgress->show();
        m_pLState->setText(QString("Loading file : ") + QString(m_sPath.c_str()) + QString(m_sProjectName.c_str()));
        m_pSaveProgress->setValue(30);
        if ((map = xml.unserialize(m_sPath, m_sProjectName)) == NULL)
        {
            m_pSaveProgress->hide();
            m_pLState->setText(QString("Fail open file : ") + QString(m_sPath.c_str()) + QString(m_sProjectName.c_str()));
            confirmPopup(this, QString("Impossible to open file"), QString("File " + QString(m_sProjectName.c_str()) + ".zme is corrupted"), QMessageBox::Cancel, QMessageBox::Ok);
            return ; // popup
        }
        m_pSaveProgress->setValue(80);
        closeAllTab();
        setWindowTitle(QString(m_sProjectName.substr(0, m_sProjectName.size() - 4).c_str()) + QString(m_sTitle.c_str()));
        m_pMap->initialize(map->getWidth(), map->getHeight(), map);
        m_pSaveProgress->setValue(100);
        m_pSaveProgress->hide();
        m_pLState->setText(QString("Success open file : ") + QString(m_sPath.c_str()) + QString(m_sProjectName.c_str()));
//        std::cout << "Open File : " << m_sProjectName << " - path : "  << m_sPath << std::endl;
        m_bSave = true;
    }
}

void            MainWindow::closeAllTab()
{
    int         count;

    count = ui->tabMap->count();
    while (count > 0)
        ui->tabMap->removeTab(count--);
}

void            MainWindow::createProject()
{
    bool    ret;

    m_pWindowCreate->exec();
    if (m_pWindowCreate->getCreate() == true)
    {
        m_pWindowCreate->setCreate(false);
        if (m_bSave == false)
        {
            ret = confirmPopup(this, QString("The project has been modified."), QString("Do you want to save your changes?"), QMessageBox::No, QMessageBox::Save);
            if (ret == true)
                save();
        }
        m_sProjectName = m_pWindowCreate->getProjectName() + ".zme";
        setWindowTitle(QString(m_sProjectName.substr(0, m_sProjectName.size() - 4).c_str()) + QString(m_sTitle.c_str()));
        m_pMap->initialize(m_pWindowCreate->getWidth(), m_pWindowCreate->getHeight());
    }
}

void            MainWindow::save()
{
    std::ofstream   out;
    XMLParse        parse;
    bool            ret;

    if (m_bSave == false)
    {
        m_pSaveProgress->show();
//        std::cout << "Save File : " << m_sProjectName << " - path : "  << m_sPath << std::endl;
        m_pLState->setText(QString("Save"));
        m_pSaveProgress->setValue(30);
        ret = parse.serialize(m_sPath, m_sProjectName, m_pMap->getMap());
        if (ret == true)
        {
//            std::cout << "SAVE SUCCESS" << std::endl;
            m_pSaveProgress->setValue(100);
            m_bSave = true;
            m_pLState->setText(QString("Success save : ") + QString(m_sPath.c_str()) + QString(m_sProjectName.c_str()));
        }
        else
        {
//            std::cout << "SAVE FAILED" << std::endl;
            m_pLState->setText(QString("Failed save : ") + QString(m_sPath.c_str()) + QString(m_sProjectName.c_str()));
        }
    }
    m_pSaveProgress->hide();
}

bool            MainWindow::confirmPopup(QWidget *parent, QString &text, QString &infoText, QMessageBox::StandardButton button1, QMessageBox::StandardButton button2)
{
    QMessageBox msgBox(parent);

    msgBox.setWindowTitle("");
    msgBox.setText(text);
    msgBox.setInformativeText(infoText);
    msgBox.setStandardButtons(button1 | button2);
    int ret = msgBox.exec();

    if (ret == button1)
        return (false);
    return (true);
}

void            MainWindow::closeTab(int currentTab)
{
    std::cout << currentTab << std::endl;
    if (currentTab == 0)
        return ;

    std::pair<QScrollArea *, RoomDisplay *> pair;

    ui->tabMap->removeTab(currentTab);
//    pair = m_mTabs[currentTab];

//    delete pair.first;
//    delete pair.second;
    m_mTabs.erase(currentTab);
}

void            MainWindow::createTab(Room *room)
{
    QScrollArea *area = new QScrollArea;
    RoomDisplay *rd = new RoomDisplay(this, ui, this);
    std::string sRoom = "ROOM (" + intToString(room->getPosX()) + ", " + intToString(room->getPosY()) + ")";

    m_mTabs[ui->tabMap->count() - 1] = std::make_pair(area, rd);
    area->setGeometry(0, 0, ROOM_WIDTH * (RES * 0.5), ROOM_HEIGHT * (RES * 0.5));
    area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    area->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    area->setFocusPolicy(Qt::NoFocus);
    rd->initialize(area, room);
    area->setWidget(rd);
    ui->tabMap->addTab(area, QString(sRoom.c_str()));
    ui->tabMap->setCurrentIndex(ui->tabMap->count() - 1);
    ui->currentPos->setText(QString(std::string("Current pos (" + intToString(rd->getCurrentBoxPos().x())+ "," + intToString(rd->getCurrentBoxPos().y()) + ")").c_str()));
}

void            MainWindow::tabChanged(int)
{
    if (ui->tabMap->currentIndex() > 0)
    {
        QScrollArea *area = reinterpret_cast<QScrollArea *>(ui->tabMap->widget(ui->tabMap->currentIndex()));
        RoomDisplay *rd = reinterpret_cast<RoomDisplay *>(area->widget());

        rd->update();
        ui->currentPos->setText(QString(std::string("Current pos (" + intToString(rd->getCurrentBoxPos().x())+ "," + intToString(rd->getCurrentBoxPos().y()) + ")").c_str()));
        displayInfosBox();
    }
    ui->tabEdit->show();
    if (ui->tabMap->currentIndex() == 0)
        ui->tabEdit->hide();
}

void            MainWindow::boxObjectChecked(bool state)
{
    if (state == true)
    {
        if (ui->monsterBox->isChecked() == true)
            ui->monsterBox->setChecked(false);
        else if (ui->doorBox->isChecked() == true)
            ui->doorBox->setChecked(false);
        else if (ui->eventBox->isChecked() == true)
            ui->eventBox->setChecked(false);
    }
//    else
//        ui->monsterBox->setChecked(true);
}

void            MainWindow::boxMonsterChecked(bool state)
{
    if (state == true)
    {
        if (ui->objectBox->isChecked() == true)
            ui->objectBox->setChecked(false);
        else if (ui->doorBox->isChecked() == true)
            ui->doorBox->setChecked(false);
        else if (ui->eventBox->isChecked() == true)
            ui->eventBox->setChecked(false);
    }
//    else
//        ui->objectBox->setChecked(true);
}

void            MainWindow::boxDoorChecked(bool state)
{
    if (state == true)
    {
        QScrollArea *area;
        RoomDisplay *rd;
        Room        *r;
        QPoint      pos;

        area = reinterpret_cast<QScrollArea *>(ui->tabMap->widget(ui->tabMap->currentIndex()));
        rd = reinterpret_cast<RoomDisplay *>(area->widget());
        r = rd->getRoom();
        pos = rd->getCurrentBoxPos();
        if ((pos.x() == 17 && pos.y() == 6) || (pos.x() == 9 && pos.y() == 0) || (pos.x() == 9 && pos.y() == 12) || (pos.x() == 0 && pos.y() == 6))
        {
            if (ui->monsterBox->isChecked() == true)
                ui->monsterBox->setChecked(false);
            else if (ui->objectBox->isChecked() == true)
                ui->objectBox->setChecked(false);
            else if (ui->eventBox->isChecked() == true)
                ui->eventBox->setChecked(false);
        }
        else
            ui->doorBox->setChecked(false);
    }
//    else
//        ui->objectBox->setChecked(true);
}

void            MainWindow::boxEventChecked(bool state)
{
    if (state == true)
    {
        if (ui->monsterBox->isChecked() == true)
            ui->monsterBox->setChecked(false);
        else if (ui->objectBox->isChecked() == true)
            ui->objectBox->setChecked(false);
        else if (ui->doorBox->isChecked() == true)
            ui->doorBox->setChecked(false);
    }
//    else
//        ui->objectBox->setChecked(true);
}

void            MainWindow::objectTypeChanged(QString value)
{
    ui->contentLabelChest->hide();
    ui->contentChest->hide();
    ui->visibleObject->hide();
    if (value == "key")
        ui->visibleObject->show();
    else if (value == "chest")
    {
        ui->contentLabelChest->show();
        ui->contentChest->show();
        ui->visibleObject->show();
    }
}

void            MainWindow::monsterTypeChanged(QString value)
{
    ui->imageMonster->setPixmap(ImageManager::getSingleton()->getMonsterImage(value.toStdString()));
}

void            MainWindow::eventTypeChanged(QString value)
{
    ui->labelCondition->hide();
    ui->condition->hide();
    if (value == "switch")
    {
        ui->labelCondition->show();
        ui->condition->show();
    }
}

void            MainWindow::checkPreviousState(Room *room, QPoint &pos)
{
    if (room->getState(pos.x(), pos.y()) == "event")
    {

    }
    else if (room->getState(pos.x(), pos.y()) == "door")
    {
        if (pos.x() == 9 && pos.y() == 0)
            room->removeDoor('n');
        else if (pos.x() == 9 && pos.y() == 12)
            room->removeDoor('s');
        else if (pos.x() == 0 && pos.y() == 6)
            room->removeDoor('w');
        else if (pos.x() == 17 && pos.y() == 6)
            room->removeDoor('e');
    }
}

void            MainWindow::apply()
{
    QScrollArea *area;
    RoomDisplay *rd;
    Room        *r;
    QPoint      pos;

    if (ui->tabMap->currentIndex() == 0)
        return ;
    area = reinterpret_cast<QScrollArea *>(ui->tabMap->widget(ui->tabMap->currentIndex()));
    rd = reinterpret_cast<RoomDisplay *>(area->widget());
    r = rd->getRoom();
    pos = rd->getCurrentBoxPos();
    checkPreviousState(r, pos);
    m_bSave = false;
    if (ui->objectBox->isChecked() == true)
    {
        Object          &obj = r->getObject(pos.x(), pos.y());

        obj.setVisible(ui->visibleObject->isChecked());
        obj.setType(ui->objectType->currentText().toStdString());
        obj.setItem(ui->contentChest->currentText().toStdString());
        r->setState("object", pos.x(), pos.y());
        m_sPreviousState = "object";
    }
    else if (ui->monsterBox->isChecked() == true)
    {
        Monster         &monster = r->getMonster(pos.x(), pos.y());

        monster.setName(ui->monsterType->currentText().toStdString());
        r->setState("monster", pos.x(), pos.y());
        m_sPreviousState = "monster";
    }
    else if (ui->doorBox->isChecked() == true)
    {
        char         loc;

        if (pos.x() == 9 && pos.y() == 0)
            loc = 'n';
        else if (pos.x() == 9 && pos.y() == 12)
            loc = 's';
        else if (pos.x() == 0 && pos.y() == 6)
            loc = 'w';
        else if (pos.x() == 17 && pos.y() == 6)
            loc = 'e';
        r->setDoor(loc, new Door(loc, ui->doorState->currentText().toStdString().c_str()));
        m_sPreviousState = "door";
        ui->doorBox->setChecked(false);
        r->setState("door", pos.x(), pos.y());
    }
    else if (ui->eventBox->isChecked() == true)
    {
        Event           &event = r->getEvent();

        r->setPosEvent(pos.x(), pos.y());
        if (ui->currentPosBox->isChecked() == false)
        {
            ui->eventNorthDoor->setChecked(false);
            ui->eventSouthDoor->setChecked(false);
            ui->eventWestDoor->setChecked(false);
            ui->eventEastDoor->setChecked(false);
            event.getDoors().clear();
            event.setPosX(pos.x());
            event.setPosY(pos.y());
        }
        else
        {
            if (ui->eventEastDoor->isChecked() == true)
                event.setDoor('e');
            if (ui->eventWestDoor->isChecked() == true)
                event.setDoor('w');
            if (ui->eventNorthDoor->isChecked() == true)
                event.setDoor('n');
            if (ui->eventSouthDoor->isChecked() == true)
                event.setDoor('s');
            event.setPosX(-1);
            event.setPosY(-1);
        }
        event.setName(ui->eventType->currentText().toStdString());
        event.setCondition(ui->condition->currentText().toStdString());
        r->setState("event", pos.x(), pos.y());
        m_sPreviousState = "event";
    }
    else
        r->setState("none", pos.x(), pos.y());
    displayInfosBox();
}

void            MainWindow::displayInfosBox()
{
    QScrollArea *area;
    RoomDisplay *rd;
    Room        *r;
    QPoint      pos;

    if (ui->tabMap->currentIndex() == 0)
        return ;
    ui->monsterBox->setChecked(false);
    ui->doorBox->setChecked(false);
    ui->eventBox->setChecked(false);
    ui->objectBox->setChecked(false);
    area = reinterpret_cast<QScrollArea *>(ui->tabMap->widget(ui->tabMap->currentIndex()));
    rd = reinterpret_cast<RoomDisplay *>(area->widget());
    r = rd->getRoom();
    pos = rd->getCurrentBoxPos();
    if (r->getState(pos.x(), pos.y()) == "object")
    {
        Object          &obj = r->getObject(pos.x(), pos.y());

        ui->visibleObject->setChecked(false);
        ui->objectType->setCurrentIndex(ui->objectType->findText(QString(obj.getType().c_str())));
        if (obj.getType() == "key" || obj.getType() == "chest")
        {
            if (obj.getVisible() == true)
                 ui->visibleObject->setChecked(true);
            if (obj.getType() == "chest")
                ui->contentChest->setCurrentIndex(ui->contentChest->findText(QString(obj.getItem().c_str())));

        }
        objectTypeChanged(QString(obj.getType().c_str()));
        ui->objectBox->setChecked(true);
    }
    else if (r->getState(pos.x(), pos.y()) == "event")
    {
        Event               &event = r->getEvent();

        ui->currentPosBox->setChecked(false);
        ui->eventType->setCurrentText(QString(event.getName().c_str()));
        if (event.getName() == "switch")
        {
            ui->condition->setCurrentText(QString(event.getCondition().c_str()));
            eventTypeChanged(QString(event.getName().c_str()));
        }
        if (event.getDoors().size() > 0)
        {
            ui->currentPosBox->setChecked(true);
            std::list<char>::iterator       it = event.getDoors().begin();

            for (; it != event.getDoors().end(); ++it)
            {
                if (*it == 'n')
                    ui->eventNorthDoor->setChecked(true);
                else if (*it == 's')
                    ui->eventSouthDoor->setChecked(true);
                else if (*it == 'w')
                    ui->eventWestDoor->setChecked(true);
                else if (*it == 'e')
                    ui->eventEastDoor->setChecked(true);
            }
        }
        ui->eventBox->setChecked(true);
    }
    else if (r->getState(pos.x(), pos.y()) == "monster")
    {
        Monster         &monster = r->getMonster(pos.x(), pos.y());

        ui->monsterType->setCurrentText(QString(monster.getName().c_str()));
        monsterTypeChanged(QString(monster.getName().c_str()));
        ui->monsterBox->setChecked(true);
    }
    else if (r->getState(pos.x(), pos.y()) == "door")
    {
        std::string            state;

        if (pos.x() == 9 && pos.y() == 0)
        {
            ui->doorNorth->setChecked(true);
            state = r->getDoor('n')->getState();
        }
        else if (pos.x() == 9 && pos.y() == 12)
        {
            ui->doorSouth->setChecked(true);
            state = r->getDoor('s')->getState();
        }
        else if (pos.x() == 0 && pos.y() == 6)
        {
            ui->doorWest->setChecked(true);
            state = r->getDoor('w')->getState();
        }
        else if (pos.x() == 17 && pos.y() == 6)
        {
            ui->doorEast->setChecked(true);
            state = r->getDoor('e')->getState();
        }
        ui->doorState->setCurrentText(QString(state.c_str()));
        ui->doorBox->setChecked(true);
    }
    else
    {
        if (m_sPreviousState == "object")
            ui->objectBox ->setChecked(true);
        else if (m_sPreviousState == "monster")
            ui->monsterBox ->setChecked(true);
        else if (m_sPreviousState == "event")
            ui->eventBox->setChecked(true);
    }
}

void                MainWindow::reset()
{
    ui->doorBox->setChecked(false);
    ui->eventBox->setChecked(false);
    ui->monsterBox->setChecked(false);
    ui->objectBox->setChecked(false);
}
