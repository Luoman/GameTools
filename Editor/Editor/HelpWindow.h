#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include        <QDialog>
#include        <QTextEdit>
#include        <QVBoxLayout>

class           HelpWindow : public QDialog
{
    Q_OBJECT
public:
    explicit HelpWindow(QWidget *parent = 0);
    ~HelpWindow();
signals:
    
public slots:
    
private:
    QTextEdit       *m_pText;
    QVBoxLayout     *m_pVBox;
};

#endif // HELPWINDOW_H
