#ifndef WINDOWCREATE_H
#define WINDOWCREATE_H

#include <QDialog>
#include <QPushButton>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

class WindowCreate : public QDialog
{
    Q_OBJECT
public:
    explicit WindowCreate(QWidget *parent = 0);
    ~WindowCreate();

signals:
    
public slots:
    void create();

public:
    void setCreate(bool create);

public:
    bool getCreate() const;
    int getWidth() const;
    int getHeight() const;
    std::string getProjectName() const;

private:
    QGridLayout *m_pGrid;
    QPushButton *m_pCreate, *m_pCancel;
    QComboBox *m_pWidth, *m_pHeight;
    QLabel  *m_pLName, *m_pLWidth, *m_pLHeight;
    QLineEdit   *m_pProjectName;
    bool m_bCreate;
};

#endif // WINDOWCREATE_H
