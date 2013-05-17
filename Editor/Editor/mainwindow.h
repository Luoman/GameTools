#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class           MapDisplay;
class           TextureArea;
class           RoomDisplay;

#include        <QMainWindow>
#include        <QMessageBox>
#include        <QProgressBar>
#include        <QScrollArea>

#include        "WindowCreate.h"
#include        "ImageManager.h"
#include        "Room.hh"
#include        "HelpWindow.h"

# define        RES             32
# define        ROOM_WIDTH      18
# define        ROOM_HEIGHT     13

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
public:
    void                createTab(Room *);
    void                closeAllTab();
    void                checkPreviousState(Room *room, QPoint &pos);
public slots:
// event menuBar
    void                saveAs();
    void                save();
    void                openProject();
    void                createProject();
    void                closeEvent(QCloseEvent *);

// event tab
    void                closeTab(int);
    void                tabChanged(int);

// event group box
    void                boxObjectChecked(bool);
    void                boxMonsterChecked(bool);
    void                boxDoorChecked(bool);
    void                boxEventChecked(bool);

// event combobox
    void                objectTypeChanged(QString);
    void                monsterTypeChanged(QString);
    void                eventTypeChanged(QString);

// button
    void                apply();
    void                displayInfosBox();
    void                reset();

    void                helpMenu();

public:
    bool                confirmPopup(QWidget *parent, QString &text, QString &infoText, QMessageBox::StandardButton button1 = QMessageBox::Cancel, QMessageBox::StandardButton button2 = QMessageBox::Ok);

private:
    Ui::MainWindow      *ui;
    MapDisplay          *m_pMap;
    TextureArea         *m_pTextureArea;
    WindowCreate        *m_pWindowCreate;
    HelpWindow          *m_pHelpWindow;
    std::string         m_sProjectName, m_sPath, m_sTitle;
    std::string         m_sPreviousState;

public:
    bool                m_bSave;

private: // QtObjects
    QProgressBar        *m_pSaveProgress;
    QLabel              *m_pLState;
    QMenu               *m_pFileMenu;
    QMenu               *m_pHelpMenu;
    QAction             *m_pExitAction;
    QAction             *m_pSaveAction;
    QAction             *m_pSaveAsAction;
    QAction             *m_pOpenAction;
    QAction             *m_pCreateAction;

private:
    std::map<int, std::pair<QScrollArea *, RoomDisplay *> > m_mTabs;
};

#endif // MAINWINDOW_H
